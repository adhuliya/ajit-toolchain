//cpu_only_testbench.c
//
// This is a testbench for the C model of the Sparc V8 cpu.
// The testbench contains:
// 	- the Sparc V8 cpu 
// 	- a byte-addressable array to model the main memory
// 	- a threads that models the instruction fetch interface between cpu and memory
// 	- a threads that models the data read/write interface between cpu and memory
// 	- display driver and keyboard driver threads for 
// 	  performing basic polled IO.
//
//
//Author : Sarath Mohan
//Modified by: Neha Karanjkar (4 April 2015)
//	Modification: Removed the resetSparc thread and 
//	registered all pipes before their use explicitly
//	using register_pipe() function. The unregistered 
//	pipes were possibly causing the executable to hang
//	occasionally.
//
//Modofied by : Piyush Soni (29 July 2015)
//	Modofication: Added doval function in testbench.

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include <unistd.h>

#include <string.h>
#include "Pipes.h"
#include "Ancillary.h"
#include "pipeHandler.h"
#include "memory.h"
#include "IO_drivers.h"
#include "sparc_stdio.h"
#include "cpu_env_model.h"
#include "uarch_debug_utils.h"
#include "uarch_bist.h"

#include "do_val.h"


// Main Memory:
// Declare size of memory :
// This information should be 
// in sync with LinkerScript.lnk
// Create 4 GB of memory
#define LOG_MEMORY_SIZE 	32
#define MEMORY_SIZE 		(1<<LOG_MEMORY_SIZE)

void checkErrorStateAndExit(void)
{
	
	//pb_error is asserted by the cpu when 
	//a "ta 0" instruction is encountered,
	//indicating end of the program.
	while(1)
	{
 		uint8_t rval =read_uint8("AJIT_to_ENV_error");
		if(rval == 1)
			break;
		usleep(10000);
	}
	fprintf(stderr, "\nError state detected\n");
	return;
}

// command-line parsing
int opt;


void Handle_Segfault(int signal)
{
	fprintf(stderr, "Error:  segmentation fault! giving up!!\n");
	exit(-1);
}


void print_usage(char* app_name, char option)
{
	if (option == 'n') {
		fprintf(stderr, "Usage: %s -m <mmap-file> [-t <trace-file>] [-b] [-d] [-s]\n", app_name);
		fprintf(stderr, "Eg: %s -m add_test.mmap -t add_test.trace\n", app_name);
	}
	if (option == 'd') {
		fprintf(stderr, "Usage: %s -m <mmap-file> -r <results file> -l <log file [-t <trace-file>] [-b] [-d] [-s]\n", app_name);
		fprintf(stderr, "Eg: %s -m add_test.mmap -r add_test.results -l add_test.log -t add_test.trace\n", app_name);
	}	
	fprintf(stderr, "   if trace-file is not specified, it is assumed to be stderr.\n");
	fprintf(stderr,"    <mem-map-file> is required, trace-file is optional.\n");
	fprintf(stderr,"    use -b to run bist test, -d to generate pipe-debug log\n");
	fprintf(stderr,"    use -s to run the CPU in single-step mode.\n");
}

int main(int argc, char **argv)
{

	int main_ret = 0;

#ifdef DO_VAL
	if (argc < 7)
	{
		print_usage(argv[0], 'd');
		return(1);
	}
	char* rslt_file = NULL;
	char* lg_file = NULL;
#endif

	// for generating trace
	FILE* trace_file;
	trace_file = stderr;

	//check arguments
	char* mmap_file_name = NULL;
	char* trace_file_name  = NULL;

	if (argc < 2)
	{
		print_usage(argv[0], 'n');
		return(1);
	}

	uint8_t run_bist = 0;
	uint8_t debug = 0;
	uint8_t single_step = 0;
	
	while ((opt = getopt(argc, argv, "m:r:l:t:b:d:s")) != -1) {
		switch(opt) {
			case 'm': 
				mmap_file_name = optarg;
				break;

			#ifdef DO_VAL
			case 'r': 
				rslt_file = optarg;
				break;
			case 'l': 
				lg_file = optarg;
				break;
			#endif

			case 't':
				trace_file_name = optarg;
				break;
			case 'b':
				run_bist = 1;
				break;
			case 'd': 
				debug = 1;
				break;
			case 's': 
				single_step = 1;
				break;
			default: 
				fprintf(stderr,"Error: unknown option %c\n", opt);
				break;
		}
	}

	FILE* mmap_file = fopen(mmap_file_name,"r");
	if(!mmap_file)
	{
		fprintf(stderr,"\n ERROR: file %s cannot be opened!\n",mmap_file_name);
		return(1);
	}
	else
	{
		fclose(mmap_file);
	}


	if(trace_file_name != NULL)
	{
		trace_file = fopen(trace_file_name,"w");
		if(trace_file == NULL)
			fprintf(stderr,"Warning: trace-file not found, no trace will be dumped.\n");
	}

	// MUST be initialized..
	if(debug)
		init_pipe_handler_with_log("pipe_handler.log");
	else
		init_pipe_handler();


	// start environment (other threads such as memory, IO drivers)
	// the function should return 1 on success.
	if(cpu_env_model(mmap_file_name, LOG_MEMORY_SIZE, 
				1, // software flag
				0, 	// display-driver
				0 	// use-kbd-driver
			)!=1) 
		return(1);

	// need some delay?
	usleep(1000);	

	//
	// write reset = 2 if single-step-mode is desired.
	//             = 3 if bist is to be run.
	// else 1.
	//   
	//
	write_uint8("ENV_to_AJIT_reset", (run_bist ? 3 : (single_step ? 2 : 1)));


	// start the cpu... Note it is in reset
	sys_cpu_start_daemons(trace_file);

	// wait until all daemons have
	// started..
	usleep(100000);

	// check for dangling pipes.
	check_for_dangling_pipes();

	// asi = 10, test 1KB
	// dont overwrite program memory!
	//
	if(run_bist)
	{
		uint32_t bist_result =	vanilla_mem_bist(8, 10, 1024, trace_file);
		if(bist_result)
		{
			fprintf(stderr,"Error: BIST failed.\n");
			return(1);
		}

		//
		// after bist, move processor to hard-reset mode
		//
		write_uint8("ENV_to_AJIT_reset",1);


		//
		// wait a while..
		//
		usleep(10000);

		//
		// move processor to single-step mode if needed.
		//
		write_uint8("ENV_to_AJIT_reset", (single_step ? 2 : 1));
	}


	//
	// bring CPU out of reset.
	// write reset = 0
	//
	write_uint8("ENV_to_AJIT_reset", 0);

	// listen for CPU error
	checkErrorStateAndExit();

	//
	// processor is in error state.
	// CCU will loop for-ever. let it loop.
	// dump state.
	//
	
	uint32_t psr_val = dbg_dump_iunit_state_registers(trace_file);
	dbg_dump_iunit_registers(trace_file);
	dbg_dump_fpunit_registers(trace_file);
	dbg_dump_memory(10, 0, 16, trace_file);

#ifdef DO_VAL
	printf ("\n\nValidating : Result file = %s, Log file = %s\n", rslt_file, lg_file);
	main_ret = doval (rslt_file, lg_file);
#endif

	// stop cpu
	sys_cpu_stop_daemons();

	// let the trace file be..
	//if((trace_file != NULL) && (trace_file != stderr))
		//fclose(trace_file);

#ifdef DO_VAL
	printf("Testbench return value : %u\n",main_ret);
#endif	
	return (main_ret);
}

