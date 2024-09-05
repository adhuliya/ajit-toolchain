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
#include "pipeHandler.h"
#include "Pipes.h"
#include "pthreadUtils.h"
#include "uart_interface.h"
#include "uarch_debug_interpreter_ultra_lite.h"
#include "uarch_debug_utils_ultra_lite.h"

#define __SLEEP__(x)  usleep(x);
int   global_verbose_flag = 0;

extern int uart_verbose_flag;
extern int uart_blocking_flag;

void Handle_Segfault(int signal)
{
	fprintf(stderr, "Error:  segmentation fault! giving up!!\n");
	exit(-1);
}



void Handle_Ctrl_C(int signal)
{
	static int count = 0;
	int interrupted_flag = 1;

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
	fprintf(stderr, "USAGE:   %s -u serial-dev-name [-B baudrate] [-v] [-h] \n", app_name);
	fprintf(stderr, "   -B  <baud-rate>    : optional, baud-rate can be 9600/19200/28800/38400/57600/115200 (default=115200)\n");
	fprintf(stderr, "   -v                 : optional, use to get verbose stuff....\n");
	fprintf(stderr, "   -h                 : optional, print help message and quit ....\n");
}

int opt;

void txDaemon ()
{
	while(1)
	{
		uint32_t v = read_uint32("UL_DEBUG_COMMAND_TO_PROCESSOR");
		sendBytesOverUart ((uint8_t*) &v, 4);		

		//usleep (100);
	}
}
DEFINE_THREAD(txDaemon)

void rxDaemon ()
{
	while(1)
	{
		uint32_t v;
		recvBytesOverUart ((uint8_t*) &v, 4, 0);
		write_uint32("UL_DEBUG_RESPONSE_FROM_PROCESSOR", v);

		//usleep (100);
	}
}
DEFINE_THREAD(rxDaemon)


int main(int argc, char **argv)
{

	init_pipe_handler ();
	register_pipe ("UL_DEBUG_COMMAND_TO_PROCESSOR", 4, 32, PIPE_FIFO_MODE);	
	register_pipe ("UL_DEBUG_RESPONSE_FROM_PROCESSOR", 4, 32, PIPE_FIFO_MODE);	

	int baud_rate = 115200;
	time_t start_t, end_t, total_t;

	signal(SIGINT,  Handle_Ctrl_C);
	signal(SIGTERM, Handle_Segfault);

	// use the UART in blocking mode.. faster.
	uart_blocking_flag = 1;

	char* uart_device_name = NULL;
	uart_verbose_flag = 0;

	int uart_flag = 0;
	int mode_specified = 0;
	while ((opt = getopt(argc, argv, "hvu:B:b")) != -1) {
		switch(opt) {
			case 'h':
				print_usage(argv[0]);
				return(0);
				break;
			case 'v': 
				global_verbose_flag = 1;
				uart_verbose_flag = 1;
				break;
			case 'b':
				uart_blocking_flag = 0;
				break;
			case 'u':
				mode_specified = 1;
				uart_flag = 1;
				uart_device_name = strdup(optarg);
				break;
			case 'B':
				baud_rate = atoi (optarg);
				break;
			default: 
				fprintf(stderr,"Error: unknown option %c\n", opt);
				break;
		}
	}

	fprintf(stderr,"Info: UART baud rate specified as %d.\n", baud_rate);

	if(!mode_specified)
	{
		fprintf(stderr,"Error: -u must be specified.\n");
		print_usage(argv[0]);
		return(1);
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
	}

	PTHREAD_DECL(txDaemon);
	//PTHREAD_CREATE(txDaemon);

	PTHREAD_DECL(rxDaemon);
	//PTHREAD_CREATE(rxDaemon);

	startDebugInterpreterUltraLite();

	return (0);
}




