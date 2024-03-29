// a testbench for the core.
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#include "timerRoutines.h"
#include <string.h>
#include "Pipes.h"
#include "pipeHandler.h"
#include "console.h"
#include "uarch_debug_utils.h"
#include "uarch_bist.h"
#include "do_val.h"
#include "StartGPBThreads.h"
#include "spi_common.h"
#include <pthread.h>
#include "pthreadUtils.h"
#include "aggregator.h"
#include "processor_link.h"


#define __SLEEP__(x)  usleep(x);

#define PROCESSOR_UNDEFINED    0
#define PROCESSOR_IN_RESET     1
#define PROCESSOR_RUN_STATE    2
#define PROCESSOR_ERROR_STATE  3

int   global_verbose_flag = 0;

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

		pmode  = sock_read_uint8("AJIT_to_ENV_processor_mode");

		//the model is encoded in to the last 2 bits
		pmode=pmode&0x3;

		MUTEX_LOCK(__pmode_mutex__);
		g_pmode = pmode;
		MUTEX_UNLOCK(__pmode_mutex__);	

		__SLEEP__(100);
	}
}
DEFINE_THREAD(listenToPmode);

void putTheProcessorInReset()
{
	fprintf(stderr,"Entered putTheProcessorInReset().\n");

	write_uint8("ENV_to_AJIT_irl", 0);
	write_uint8("ENV_to_AJIT_reset", 1);

	fprintf(stderr,"asserted reset.\n");
	// ensure that it has gone to reset.
	while(1)
	{
		MUTEX_LOCK(__pmode_mutex__);
		uint8_t pmode = g_pmode;
		MUTEX_UNLOCK(__pmode_mutex__);
		if(pmode == PROCESSOR_IN_RESET)
			break;
		__SLEEP__(1000);

		if(pmode != 0)
			fprintf(stderr,"processor-mode=%d\n", pmode);
	}
	fprintf(stderr,"processor put into reset-mode.\n");
	return;
}


void checkErrorStateAndExit(void)
{

	//pb_error is asserted by the cpu when 
	//a "ta 0" instruction is encountered,
	//indicating end of the program.
	while(1)
	{
		MUTEX_LOCK(__pmode_mutex__);
		uint8_t pmode = g_pmode;
		MUTEX_UNLOCK(__pmode_mutex__);

		// bottom two bits of the pmode indicate if the
		// processor is in error.
		uint8_t rval = (0x3 & pmode);

		if(rval == PROCESSOR_ERROR_STATE)
			break;

		__SLEEP__(1000);
	}
	fprintf(stderr, "\nError state detected\n");
	return;
}


void clearCpuIunitRegisters ()
{
	uint32_t idx;
	for(idx= 0; idx < 32; idx++)
	{
		// write 0 into current window.
		dbg_write_iunit_register (idx, 0);

		// write 0 into ASR's.
		dbg_write_asr (idx,0);
	}
}

void setMmuCacheableBit ()
{
	//
	// sta %o0, [%g0] 0x4 
	// write 0x100 into MMU control register.
	// 
	dbg_write_mem(0x4, 0x0, 0x100);
}

// command-line parsing
int opt;
int interrupted_flag = 0;


void Handle_Segfault(int signal)
{
	fprintf(stderr, "Error:  segmentation fault! giving up!!\n");

	//print out the log of last 100
	//messages generated by the cpu
	//before exiting
#ifdef GENERATE_LOGS_IN_TWIN_CPU_TESTBENCH
	print_queue(); 
#endif
	exit(-1);
}



void Handle_Ctrl_C(int signal)
{
	static int count = 0;
	interrupted_flag = 1;

	if(count == 1)
	{
		fprintf(stderr, "second Ctrl-C, exit\n");

		//print out the log of last 100
		//messages generated by the cpu
		//before exiting
#ifdef GENERATE_LOGS_IN_TWIN_CPU_TESTBENCH
		print_queue(); 
#endif

		exit(-1);
	}

	fprintf(stderr, "Ctrl-C, continue.. type once more to kill process!!\n");
	count++;
}

void print_usage(char* app_name)
{
	fprintf(stderr, "USAGE:   %s -m <mmap-file> [-g -p <gdb-port-number>] [-d -r <results-file> -l <log-file>] [-s] [-w <write-trace-logger-file>] [-S logger-server-ip] [-P logger-server-port] [-M] [-c <console-server-port>] \n", 
			app_name);
	fprintf(stderr, "   -m <mmap-file>     : required, specifies memory-map of processor for this test.\n");
	fprintf(stderr, "   -M      : optional, use the debug-interface to initialize the memory-map.\n");
	fprintf(stderr, "   -f <fpga-resource-file-name>:  FPGA resource file created on host system.. ENV variable AJIT_AXI_RESOURCE_FILE has this...\n");
	fprintf(stderr, "   -d                 : optional, use if doval utility is to be run...\n");
	fprintf(stderr, "   -r <results-file>  : required with -d,  specifies expected register/memory values at end of run.\n");
	fprintf(stderr, "   -l <log-file>      : required with -d, specifies a log-file of the validation checks.\n");
	fprintf(stderr, "   -i, if specified, spins after processor goes into error mode until interrupted.\n");
	fprintf(stderr, "   -s, optional, to run the CPU in single-step mode.\n");
	fprintf(stderr, "   -g, optional, to run the CPU in debug mode.\n");
	fprintf(stderr, "   -p <gdb-port-number>, required with -g, to specify remote debug port.\n");
	fprintf(stderr, "   -c <console-server-port-number>, specify port for console server.\n");
	fprintf(stderr, "   -v optional, verbose-mode on (trace messages will be logged).\n");
	fprintf(stderr, "   -I optional:  initialize all iunit registers to 0x0.\n");
	fprintf(stderr, "   -C optional:  set cacheable bit in MMU control register.\n");
	fprintf(stderr, "   -h optional:  print help message and quit.\n");
	fprintf(stderr, "                                                                         \n");
	fprintf(stderr, "EXAMPLE:  \n");
	fprintf(stderr, "          %s -m add_test.mmap -d -l add_test.log -r add_test.results -t add_test.trace -w add_test.wtrace \n", app_name);

}

int main(int argc, char **argv)
{
	int main_ret_val = 0;
	int console_server_port = -1;

	time_t start_t, end_t, total_t;

	signal(SIGINT,  Handle_Ctrl_C);
	signal(SIGTERM, Handle_Segfault);

	// for generating trace
	FILE* trace_file;
	trace_file = NULL;


	int N_ADDR_BITS = 36;


	int trace_on = 0;
	int init_registers = 0;
	int set_cacheable = 0;

	//check arguments
	char* mmap_file_name = NULL;
	char* results_file_name = NULL;
	char* reg_write_file_name = NULL;

	uint8_t   spin_flag   = 0;
	uint8_t   gdb_flag  = 0;
	uint8_t   single_step = 0;
	uint8_t   doval_flag  = 0;
	uint8_t   init_mem_through_debug = 0;

	// support only axi model for now.
	uint8_t   axi_flag = 1;

	uint8_t   gpio_in = 0;

	int pn = -1;
	int spi_slave_cluster_pn = -1;

	char* resource_file_name = NULL;
	char* log_file_name = NULL;

	while ((opt = getopt(argc, argv, "hvidgsm:r:l:p:MICf:")) != -1) {
		switch(opt) {
			case 'h':
				print_usage(argv[0]);
				return(0);
				break;
			case 'v': 
				global_verbose_flag = 1;
				trace_on = 1;
				break;
			case 'i': 
				spin_flag = 1;
				break;
			case 'd':
				doval_flag = 1;
				break;
			case 'g':
				gdb_flag = 1;
				break;
			case 's':
				single_step = 1;
				break;
			case 'm': 
				mmap_file_name = strdup(optarg);
				break;
			case 'f':
				resource_file_name = strdup(optarg);
				break;
			case 'r':
				results_file_name = strdup(optarg);
				break;
			case 'l':
				log_file_name = strdup(optarg);
				break;
			case 'p':
				// debug-port
				pn = atoi(optarg);
				break;
			case 'M':
				init_mem_through_debug = 1;
				break;
			case 'I':
				init_registers = 1;
				break;
			case 'C':
				set_cacheable = 1;
				break;
			default: 
				fprintf(stderr,"Error: unknown option %c\n", opt);
				break;
		}
	}

	// set to 1 to generate pipe-handler log..
	int pipe_handler_debug = 0;
	if(pipe_handler_debug)
		init_pipe_handler_with_log("pipe_handler.log");
	else
		init_pipe_handler();

	// either gdb or doval, not both.
	//
	if(gdb_flag && doval_flag)
	{
		fprintf(stderr,"\nERROR: -g and -d options cannot be used together\n");
		return (1);
	}



	if(resource_file_name == NULL)
	{
		fprintf(stderr,"\nERROR: FPGA resource file not specified\n");
		return (1);
	}

	void* fpga = initialize_axi_link ("default-fpga",resource_file_name);
	if(fpga == NULL)
	{
		fprintf(stderr,"\nERROR: could not initialize FPGA link\n");
		return (1);
	}
	// set the fpga in the aggregator...
	setFpgaInAggregator(fpga);


	if(mmap_file_name == NULL)
	{
		fprintf(stderr,"\n ERROR: memory-map file not specified.\n");
		return(1);
	}
	FILE* mmap_file = fopen(mmap_file_name,"r");
	if(!mmap_file)
	{
		fprintf(stderr,"\n ERROR: memory-map file %s cannot be opened!\n",mmap_file_name);
		return(1);
	}
	else
	{
		fclose(mmap_file);
	}

	// if gdb selected, pn must be specified.
	if (gdb_flag & (pn < 0))
	{
		fprintf(stderr,"\nERROR: gdb remote port number is not specified!\n");
		return(1);
	}


	// write 1 to reset before the other daemons are started.
	register_signal ("ENV_to_AJIT_reset", 8);
	write_uint8("ENV_to_AJIT_reset", 1);

	startAggregatorDaemons();

	fprintf(stderr,"Info: starting console threads.\n");
	startConsoleThreads();

	if(gdb_flag)
	{
		fprintf(stderr,"Info: starting GDB threads.\n");
		start_gpb_threads(pn);
	}


	// start draining pmode.
	//
	// Note: AJIT_to_ENV_processor_mode is a pipe in
	//       the core, but a signal at this level.
	//       This discrepancy should ideally be removed.
	//
	// register_signal("AJIT_to_ENV_processor_mode",8);

	PTHREAD_DECL(listenToPmode);
	PTHREAD_CREATE(listenToPmode);

	// need some delay?
	__SLEEP__(1000);	

	// check for dangling pipes.
	check_for_dangling_pipes();

	//
	// make sure the processor has gone into reset mode.
	//
	putTheProcessorInReset();


	fprintf(stderr,"Info: initializing main memory using memory-map %s\n", mmap_file_name);
	if(init_mem_through_debug) {
		fprintf(stderr,"Info: will use debug interface to initialize memory.\n");
		axi_init_ram_through_debug_interface(fpga, mmap_file_name);
	}
	else
	{
		fprintf(stderr,"Info: will use axi interface to directly initialize memory.\n");
		axi_init_ram(fpga, mmap_file_name);
	}


	// initialize registers
	if(init_registers)
	{
		fprintf(stderr,"Info: will use debug interface to initialize iunit registers to 0.\n");
		clearCpuIunitRegisters();
	}


	// set cacheable
	if(set_cacheable)
	{
		fprintf(stderr,"Info: will use debug interface to set cacheable bit in MMU control register.\n");
		setMmuCacheableBit();
	}

	// need some delay?
	//__SLEEP__(10000);	

	// bring CPU out of reset (lowest bit = 0, rest decided by flags)
	uint8_t reset_value = (single_step << 2) | (gdb_flag << 1);
	fprintf(stderr,"Info: bring CPU out of reset: reset value = 0x%x.\n", reset_value);

	write_uint8("ENV_to_AJIT_reset",reset_value); 
	fprintf(stderr,"Info: processor brought out of reset-mode. Debug-mode=%d, Single-step-mode=%d, Logging-enabled=0\n",gdb_flag, single_step);

	// get run time
	rcStartTimer();
	// listen for CPU error
	checkErrorStateAndExit();
	rcStopTimer();


	double time_diff = rcGetElapsedTime();
	fprintf(stderr,"Total time taken by CPU: %le secs\n", time_diff);


	if(doval_flag)
	{
		// sleep until pipeline is drained..
		usleep (1000000);
		fprintf (stderr, "\n\nValidating : Result file = %s, Log file = %s\n", results_file_name, log_file_name);

		main_ret_val = doval (results_file_name, log_file_name);
		if(main_ret_val == 0)
			fprintf(stderr, "\n\nTests Successful.\n");
		else
			fprintf(stderr, "\n\nERROR: Tests Failed.\n");
	}

	if(spin_flag)
	{
		fprintf(stderr,"PRESS CTRL-C CTRL-C TO CONTINUE.\n");
		while(1) 
		{
			fprintf(stderr,"\n: Error state: type ctrl-C to kill.\n");
			usleep(10000000);
			if(interrupted_flag)
				break;
		}
	}

	if(gdb_flag)
	{
		// stop gdb server bridge
		stop_gpb_threads();
	}

	stopAggregatorDaemons();
	usleep(1000);
	if(axi_flag)
	{
		close_axi_link (fpga);
	}

	PTHREAD_CANCEL(listenToPmode);
	return (main_ret_val);
}

