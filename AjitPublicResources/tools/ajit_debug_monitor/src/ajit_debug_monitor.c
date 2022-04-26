// a debug monitor.
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#include "timerRoutines.h"
#include "processor_link.h"
#include "uart_interface.h"
#include "memory.h"
#include "sys_mem.h"
#include "console.h"
#include "rtl2AaMatcher.h"
#include "Pipes.h"
#include "SockPipes.h"
#include "pipeHandler.h"
#include "monitorLogger.h"
#include "uarch_debug_utils.h"
#include "uarch_bist.h"
#include "uarch_debug_interpreter.h"
#include "pthreadUtils.h"
#include "aggregator.h"
#include "spi_common.h"
#include "debugServer.h"
#ifdef SUPPORT_AA2C
#include "chip_afb_bridge_afb_bridge_aa_c_model.h"
#include "chip_core_core.h"
#include "sys_afb_ahb_bridge_afb_ahb_bridge_aa_c_model.h"
#include "sys_peripherals_peripherals.h"
#include "chip_interrupt_stub_interrupt_stub_aa_c_model.h"
#endif


#define __SLEEP__(x)  usleep(x);
int   global_verbose_flag = 0;

FILE* reg_write_file = NULL;
FILE* long_reg_write_file = NULL;
char* logger_server_ip_address = NULL;
int   logger_server_port_number = -1;

int opt;
int interrupted_flag = 0;
int use_socket_to_dut = 0;

extern int uart_verbose_flag;
extern int uart_blocking_flag;
void putTheProcessorInReset()
{
	/*TODO*/
	fprintf(stderr,"Entered putTheProcessorInReset().\n");
	if(use_socket_to_dut)
	{
		fprintf(stderr,"In putTheProcessorInReset(), trying to write irl=0, reset=1 to socket...\n");
		sock_write_uint8("ENV_to_AJIT_irl", 0);
		sock_write_uint8("ENV_to_AJIT_reset", 1);
		fprintf(stderr,"In putTheProcessorInReset(), finished writing irl=0, reset=1 to socket..\n");
	}
	else
	{
		write_uint8("ENV_to_AJIT_irl", 0);
		write_uint8("ENV_to_AJIT_reset", 1);
	}
	fprintf(stderr,"asserted reset.\n");
	return;
}

void Handle_Segfault(int signal)
{
	fprintf(stderr, "Error:  segmentation fault! giving up!!\n");
	exit(-1);
}



void Handle_Ctrl_C(int signal)
{
	static int count = 0;
	interrupted_flag = 1;

	if(count == 1)
	{
		fprintf(stderr, "second Ctrl-C, exit\n");
		exit(-1);
	}

	fprintf(stderr, "Ctrl-C, continue.. type once more to kill process!!\n");
	count++;
}

void print_usage(char* app_name)
{
	fprintf(stderr, "USAGE:   %s [-h] [-H] [-E] [-u serial-dev-name] \n", 
			app_name);
	fprintf(stderr, "   -u <serial-dev>    : optional, specifies serial device to use for debug interface.\n");
	fprintf(stderr, "   -c <console-server-port>    : optional, specifies tcp/ip port for console i/o.\n");
	fprintf(stderr, "   -A                 : optional, use if you are monitoring an Aa2C sim ...\n");
	fprintf(stderr, "   -H                 : optional, use if you are monitoring a VHDL PCIE sim via socket.\n");
	fprintf(stderr, "   -E                 : optional, use if you are using PCIE to connect to hardware...\n");
	fprintf(stderr, "   -b                 : optional, if you want to operate the UART in blocking mode....\n");
	fprintf(stderr, "   -B  <baud-rate>    : optional, baud-rate can be 9600/19200/28800/38400/57600/115200 (default=115200)\n");
	fprintf(stderr, "   -v                 : optional, use to get verbose stuff....\n");
}

MUTEX_DECL_NONSTATIC(__g_mutex__);
MUTEX_DECL_NONSTATIC(__pmode_mutex__);

uint8_t g_pmode = 0;
// drain the blocking pipe and keep updating
// g_pmode flag.
void listenToPmode()
{
	while(1)
	{
		//read the processor_mode pipe,
		//The last 2 bits encode the mode.
		uint8_t pmode;
		if(use_socket_to_dut)
			pmode  = sock_read_uint8("AJIT_to_ENV_processor_mode");
		else
			pmode  = read_uint8("AJIT_to_ENV_processor_mode");

		//the model is encoded in to the last 2 bits
		pmode=pmode&0x3;

		MUTEX_LOCK(__pmode_mutex__);
		g_pmode = pmode;
		MUTEX_UNLOCK(__pmode_mutex__);	

		__SLEEP__(100);
	}
}
DEFINE_THREAD(listenToPmode);
DEFINE_THREAD(monitorLogger);


int main(int argc, char **argv)
{

	int main_ret_val = 0;
	int mode_specified = 0;
	int riffa_flag = 0;
	int aa2c_flag = 0;
	int console_server_port = -1;
	int use_aggregator = 0;
	int baud_rate = 115200;

	time_t start_t, end_t, total_t;

	signal(SIGINT,  Handle_Ctrl_C);
	signal(SIGTERM, Handle_Segfault);

	// for generating trace
	FILE* trace_file;
	trace_file = NULL;
	
	uart_blocking_flag = 0;


	char* mmap_file_name = NULL;
	char* uart_device_name = NULL;
	uart_verbose_flag = 0;

	int uart_flag = 0;
	while ((opt = getopt(argc, argv, "hHEAvu:c:bM:B:")) != -1) {
		switch(opt) {
			case 'h':
				print_usage(argv[0]);
				return(0);
				break;
			case 'M':
				mmap_file_name = strdup(optarg);
				break;
			case 'v': 
				global_verbose_flag = 1;
				//uart_verbose_flag = 1;
				break;
			case 'b':
				uart_blocking_flag = 1;
				break;
			case 'B':
				baud_rate = atoi (optarg);
				break;
			case 'u':
				mode_specified = 1;
				uart_flag = 1;
				uart_device_name = strdup(optarg);
				break;
			case 'H':
				mode_specified = 1;
				use_socket_to_dut = 1;

				// VHDL sim uses aggregator.
				use_aggregator = 1;
				break;
			case 'A':
				mode_specified = 1;
				aa2c_flag = 1;
				break;
			case 'E':
				mode_specified = 1;
				riffa_flag = 1;

				// PCIE sim always uses aggregator.
				use_aggregator = 1;
				break;
			case 'c':
				console_server_port = atoi(optarg);
				break;
			default: 
				fprintf(stderr,"Error: unknown option %c\n", opt);
				break;
		}
	}

	fprintf(stderr,"Info: UART baud rate specified as %d.\n", baud_rate);

	if(!mode_specified)
	{
		fprintf(stderr,"Error: at least one of -H, -E, -A, -u must be specified.\n");
		return(1);
	}

	// set to 1 to generate pipe-handler log..
	int pipe_handler_debug = 0;
	if(pipe_handler_debug)
		init_pipe_handler_with_log("pipe_handler.log");
	else
		init_pipe_handler();

	if(console_server_port > 0)
	{
		fprintf(stderr,"Started console server on port %d\n", console_server_port);
		setConsoleServerPort(console_server_port);
		startConsoleServer();
	}



	if(uart_flag)
	// FPGA hardware connected to debug interface with uart.
	{
		int uart_ok = setupDebugUartLinkWithBaudRate(uart_device_name, baud_rate);	
		if(uart_ok < 0)
		{
			fprintf(stderr,"\n ERROR: uart %s could not be opened.. are you sure you are running this in sudo mode?\n",
					uart_device_name);
			return(1);
		}
		setDebugServerConnectMode(dbg_CONNECT_WITH_UART);

		riffa_flag = 0;
		aa2c_flag = 0;
		use_socket_to_dut = 0;
	}
	else if(riffa_flag)
	// FPGA hardware connected to debug interface with PCIE.
	// need to start console and aggregator on the software side.
	{
#ifdef SUPPORT_RIFFA

		setDebugServerConnectMode(dbg_CONNECT_WITH_PCIE);
		int link_status = set_processor_link (PROCESSOR_RIFFA_LINK);
		assert(link_status == 0);

		aa2c_flag = 0;
		use_socket_to_dut = 0;

		startAggregatorDaemons();

		if(console_server_port > 0)
			startConsoleThreads();

		PTHREAD_DECL(listenToPmode);
		PTHREAD_CREATE(listenToPmode);
#else
		fprintf(stderr,"Sorry!  riffa not supported.\n");
		return(1);
#endif
	}
	else if (aa2c_flag)
	//
	// AA2C model..
	//
	{
#ifdef SUPPORT_AA2C
		allocateMemory(32); 
		if(mmap_file_name != NULL)
		{
			fprintf(stderr,"Info: directly initializing main memory using memory-map %s\n", mmap_file_name);
			initializeMemory(mmap_file_name);
		}
			
		
		fprintf(stderr,"Info: starting aa2c sys threads.\n");

		setSysmemUseSimplifiedAhbPipes(1);

		chip_core_start_daemons(NULL, 0);
		chip_afb_bridge_afb_bridge_start_daemons(NULL,0);
		chip_interrupt_stub_interrupt_stub_start_daemons(NULL,0);

		sys_afb_ahb_bridge_afb_ahb_bridge_start_daemons(NULL,0);
		sys_peripherals_start_daemons(NULL,0);

		if(console_server_port > 0)
			startConsoleThreads();
		startSysmemThreads();

		use_socket_to_dut = 0;
	
		reg_write_file = fopen("ajit_debug_monitor.wtrace","w");
		long_reg_write_file = fopen("ajit_debug_monitor.long.wtrace","w");
	
		PTHREAD_DECL(listenToPmode);
		PTHREAD_CREATE(listenToPmode);

		PTHREAD_DECL(monitorLogger);
		PTHREAD_CREATE(monitorLogger);
#else
		fprintf(stderr,"Sorry, aa2c mode not supported.\n");
		return(1);
#endif
	}
	else if(use_socket_to_dut)
	//
	// VHDL sim model.
	//
	{
		setSysmemSocketFlag(1);

		setDebugServerConnectMode(dbg_CONNECT_WITH_SOCKET);

		setConsoleInSocketMode();
		if(console_server_port > 0)
			startConsoleThreads();

		if(use_aggregator)
			startAggregatorDaemons();

		PTHREAD_DECL(listenToPmode);
		PTHREAD_CREATE(listenToPmode);
	}

	startDebugServer();
	startDebugInterpreter();


#ifdef SUPPORT_RIFFA
	if(riffa_flag)
		close_fpga();
#endif

	return (main_ret_val);
}

