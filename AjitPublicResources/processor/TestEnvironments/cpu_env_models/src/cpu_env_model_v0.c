// Environment for a CPU only test.
//
// Models
// 	- a byte-addressable array to model the main memory
// 	- threads that model the instruction fetch interface between cpu and memory
// 	- threads that model the data read/write interface between cpu and memory
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
// Modified by: Madhav Desai (June 9 2015)
//      Separated the cpu-only testbench into an environment
//      model and test-program.  The environment model (this
//      file) models everything except the CPU.  The CPU
//      is modeled by the testbench.
//
//      This way, the same environment model can be used
//      in multiple ways.


#include <stdio.h>
#include <assert.h>

#include <stdlib.h>
#include <stdint.h>
#ifdef USE_GNUPTH
#include <pth.h>
#include "GnuPthUtils.h"
#else
#include <pthread.h>
#include "pthreadUtils.h"
#endif
#include <unistd.h>

#include <string.h>
#include "Pipes.h"
#include "Ancillary.h"
#include "pipeHandler.h"
#include "CpuInterface.h"
#include "ASI_values.h"
#include "memory.h"
#include "sparc_stdio.h"
#include "StartIODriverThreads.h"
#include "SocketLib.h"
#include "monitorLogger.h"

int global_verbose_flag = 0;

//
// Main threads to model the environment of the CPU
//

MUTEX_DECL(mem_mutex);

void instructionFetch();
void readWriteData();



DEFINE_THREAD (monitorLogger);
DEFINE_THREAD (instructionFetch);
DEFINE_THREAD (readWriteData);



// The Instruction fetch interface 
// between cpu and memory:
void instructionFetch(void)
{
	uint8_t request_type;
	uint8_t asi;
	uint32_t addr;
	uint8_t mae;
	uint64_t instr64 = 0 ;

	while (1)
	{


		asi          = read_uint8 ("CPU_to_ICACHE_asi");
		addr         = read_uint32("CPU_to_ICACHE_addr");


		// mask out top bit.
		asi = asi & 0x7f;


		if((asi == ASI_SUPERVISOR_INSTRUCTION) ||
				(asi == ASI_USER_INSTRUCTION))
		{
			MUTEX_LOCK(mem_mutex);
			instr64=getDoubleWordInMemory(addr);
			MUTEX_UNLOCK(mem_mutex);
#ifdef VERBOSE
			fprintf(stderr,"Info:instructionFetch asi=%x, addr=%x, instr-pair=%llx.\n", asi, addr, instr64);
#endif

		}
		else
			instr64 = 0;

		write_uint64("ICACHE_to_CPU_instr_pair",instr64);
		write_uint8("ICACHE_to_CPU_mae",0x00);
		write_uint32("ICACHE_to_CPU_fsr",0); // no mmu here.
#ifdef VERBOSE
		fprintf(stderr,"Info:instructionFetch: sent.\n");
#endif

	}
}

//Data read/write interface between 
//cpu and memory:
void readWriteData(void)
{
	uint32_t byte0, byte1, byte2, byte3, data;

	uint8_t request_type;
	uint8_t asi;
	uint32_t addr;
	uint8_t mae;
	uint64_t data64;
	uint8_t byte_mask;

	while (1)
	{

		asi          = read_uint8 ("CPU_to_DCACHE_asi");
		asi = asi & 0x7f;

		addr         = read_uint32("CPU_to_DCACHE_addr");

		// bottom four bits specify the request type.
		request_type = (0xf & read_uint8 ("CPU_to_DCACHE_request_type"));

		byte_mask    = read_uint8 ("CPU_to_DCACHE_byte_mask");
		data64       = read_uint64("CPU_to_DCACHE_data");


		if((request_type==REQUEST_TYPE_READ) ||
				(request_type==REQUEST_TYPE_CCU_CACHE_READ))
		{
			MUTEX_LOCK(mem_mutex);
			data64 = getDoubleWordInMemory(addr);
			MUTEX_UNLOCK(mem_mutex);

			write_uint8 ("DCACHE_to_CPU_mae",0x00);
			write_uint64("DCACHE_to_CPU_data", data64);
#ifdef VERBOSE
			fprintf(stderr,"Info:DcacheReadRequest: asi %x, addr %x, data %llx.\n", asi, addr, data64);
#endif
		}
		else if((request_type == REQUEST_TYPE_WRITE) || 
				(request_type==REQUEST_TYPE_CCU_CACHE_WRITE))
		{
			// All ASI's are put into one memory.
			MUTEX_LOCK(mem_mutex);
			setDoubleWordInMemory(addr, data64, byte_mask);
			MUTEX_UNLOCK(mem_mutex);
			write_uint8 ("DCACHE_to_CPU_mae",0x00);
			write_uint64("DCACHE_to_CPU_data", 0);
#ifdef VERBOSE
			fprintf(stderr,"Info:DcacheWriteRequest: asi %x, addr %x, data %llx.\n", asi, addr, data64);
#endif
		}
		else
		{
			write_uint8 ("DCACHE_to_CPU_mae",0x00);
			write_uint64("DCACHE_to_CPU_data", 0);
			fprintf(stderr,"Warning:Unknown DcacheRequest (%x): asi %x, addr %x, data %llx.\n", 
										request_type, asi, addr, data64);
		}
	}
}


void start_cpu_env_threads(int sw_flag, int use_display_driver, int use_kbd_driver)
{
	PTHREAD_DECL(instructionFetch);
	PTHREAD_DECL(readWriteData);
	PTHREAD_DECL(monitorLogger);

	if(sw_flag)
	{

		int depth = 2;
		int logger_pipe_depth = 3;
		register_pipe("AJIT_to_ENV_logger",	 	logger_pipe_depth, 32,	0);
		set_pipe_is_read_from("AJIT_to_ENV_logger");

		register_pipe("CPU_to_ICACHE_asi",	 	depth, 8,	0);
		set_pipe_is_read_from("CPU_to_ICACHE_asi");

		register_pipe("CPU_to_ICACHE_addr",	 	depth, 32,	0);
		set_pipe_is_read_from("CPU_to_ICACHE_addr");

		register_pipe("ICACHE_to_CPU_mae", 		depth, 8,	0);
		set_pipe_is_written_into("ICACHE_to_CPU_mae");

		register_pipe("ICACHE_to_CPU_instr_pair", 		depth, 64,	0);
		set_pipe_is_written_into("ICACHE_to_CPU_instr_pair");


		register_pipe("CPU_to_DCACHE_asi",	 	depth, 8,	0);
		set_pipe_is_read_from("CPU_to_DCACHE_asi");

		register_pipe("CPU_to_DCACHE_addr",	 	depth, 32,	0);
		set_pipe_is_read_from("CPU_to_DCACHE_addr");

		register_pipe("CPU_to_DCACHE_request_type", 	depth, 8,	0);
		set_pipe_is_read_from("CPU_to_DCACHE_request_type");

		register_pipe("CPU_to_DCACHE_byte_mask", 	depth, 8,	0);
		set_pipe_is_read_from("CPU_to_DCACHE_byte_mask");

		register_pipe("CPU_to_DCACHE_data", 		depth, 64,	0);
		set_pipe_is_read_from("CPU_to_DCACHE_data");

		register_pipe("DCACHE_to_CPU_mae", 		depth, 8,	0);
		set_pipe_is_written_into("DCACHE_to_CPU_mae");

		register_pipe("DCACHE_to_CPU_data", 		depth, 64,	0);
		set_pipe_is_written_into("DCACHE_to_CPU_data");

		register_signal("ENV_to_AJIT_reset",8);
		set_pipe_is_written_into("ENV_to_AJIT_reset");

		register_signal("ENV_to_AJIT_irl", 8);
		set_pipe_is_written_into("ENV_to_AJIT_irl");

		register_signal("AJIT_to_ENV_error", 8);
		set_pipe_is_read_from("AJIT_to_ENV_error");

		register_pipe("ENV_to_AJIT_debug_command", 		depth, 32,	0);
		set_pipe_is_written_into("ENV_to_AJIT_debug_command");

		register_pipe("AJIT_to_ENV_debug_response", 		depth, 32,	0);
		set_pipe_is_read_from("AJIT_to_ENV_debug_response");

	}

	PTHREAD_CREATE(instructionFetch);
	PTHREAD_CREATE(readWriteData);
	PTHREAD_CREATE(monitorLogger);

	if(use_display_driver  || use_kbd_driver) start_IO_driver_threads();

	usleep(100);	
}

//
// start environment threads.
// Returns 1 on success.
//
int cpu_env_model(char* memory_map_file, 
			int log_of_memory_size, 
			int sw_flag,
			int use_display_driver,
			int use_kbd_driver,
			int verbose_flag)
{
	// will this value get to everybody?
	global_verbose_flag = verbose_flag;

	if (memory_map_file == NULL)
	{
		printf("Provide memory-byte-map file as input\n");
		printf("Eg: AJIT_cpu_testbench <memory_map_file>\n");
		exit(1);
	}
	//check if memory map file exists
	FILE * fp1 = fopen(memory_map_file, "r");
	if(!fp1)
	{
		fprintf(stderr,"\n ERROR: memory map-file %s cannot be opened!\n", memory_map_file);
		exit(1);
	}
	else
	{
		fclose(fp1);
	}

	//Allocate memory on the heap to model main memory
	if(allocateMemory(log_of_memory_size)!=1) 
		return(0);

	//Initialize memory contents using a memory map file
	if(initializeMemory(memory_map_file)!=1) 
		return(0);

	// Initialize to 0 the memory locations
	// used by keyboard and console drivers as flags:
	if(use_kbd_driver)
		setByteInMemory(KB_FLAG_ADDRESS, 0x00);

	if(use_display_driver)
		setByteInMemory(CONSOLE_FLAG_ADDRESS, 0x00);


	//declare and start threads:
	start_cpu_env_threads(sw_flag, use_display_driver, use_kbd_driver);

	return (1);
}

