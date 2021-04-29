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
//
//Modified by Neha Karanjkar (28 April 2016)
//	Modified the environment to include Icache, Dcache and Mmu 
//
//Modified by Piyush Soni (8 June 2016)
//	removed all peripherals because now they will be present in FPGA

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
#include "SocketLib.h"
#include "Pipes.h"
#include "Ancillary.h"
#include "pipeHandler.h"

//Hardware Configuration Settings are present in 
//Ajit_Hardware_Configuration.h
#include "Ajit_Hardware_Configuration.h"

int global_verbose_flag = 0;
MUTEX_DECL(__g_mutex__);

//Includes for modeling other components in the environment
//includes required for modeling
//the cpu's environment

#include "sparc_stdio.h"
#include "StartIODriverThreads.h"
#include "Timer.h"
#include "InterruptController.h"
#include "Serial.h"
#include "Console.h"
#include "monitorLogger.h"

//memory initialization routine
int initialize_Memory(char* memory_map_file);
//DEFINE_THREAD (memoryAccess);
//thread to keep reading the log pipe
void monitorLogger(void);
//Function to register the cpu-side pipes if we're using SW version of the cpu
void register_cpu_pipes(int sw_flag, int use_display_driver, int use_kbd_driver);

void serialAccess();
void interruptAccess();
void timerAccess();

DEFINE_THREAD (monitorLogger);
DEFINE_THREAD (serialAccess);
DEFINE_THREAD (interruptAccess);
DEFINE_THREAD (timerAccess);


// start environment threads.
// Returns 1 on success.
// Note : all hardaware configuration settings
// are assumed to be present in Ajit_Hardware_Configuration.h
//
int cpu_env_model(char* memory_map_file, 
			int log_of_memory_size, //<=== unused
			int sw_flag,     
			int use_display_driver, //<=== unused
			int use_kbd_driver,
			int verbose_flag)     //<=== unused
{
	MUTEX_LOCK(__g_mutex__);
	global_verbose_flag = verbose_flag;
	MUTEX_UNLOCK(__g_mutex__);
	
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


	start_serial_threads();
	start_console_threads();
	start_IRC_threads();
	start_timer_threads();

	//register cpu pipes
	register_cpu_pipes(sw_flag, USE_DISPLAY_DRIVER, USE_KBD_DRIVER);


	PTHREAD_DECL(serialAccess);
	PTHREAD_CREATE(serialAccess);
	PTHREAD_DECL(interruptAccess);
	PTHREAD_CREATE(interruptAccess);
	PTHREAD_DECL(timerAccess);
	PTHREAD_CREATE(timerAccess);

	return (1);
}


//We need to register the cpu pipes if we're using SW version of the cpu:
void register_cpu_pipes(int sw_flag, int use_display_driver, int use_kbd_driver)
{
	PTHREAD_DECL(monitorLogger);

	int depth = 2;
	int LOGGER_PIPE_DEPTH=3;

	register_signal("ENV_to_AJIT_reset",8);
	register_signal("ENV_to_AJIT_irl", 8);
	register_pipe  ("ENV_to_AJIT_data", depth,64,0);
	register_pipe  ("ENV_to_AJIT_debug_command",depth, 32,0);

	
	set_pipe_is_written_into("ENV_to_AJIT_reset");
	set_pipe_is_written_into("ENV_to_AJIT_irl");
	set_pipe_is_written_into("ENV_to_AJIT_data");
	set_pipe_is_written_into("ENV_to_AJIT_debug_command");


	register_signal("AJIT_to_ENV_error", 8);
	register_pipe  ("AJIT_to_ENV_debug_response",depth, 32,0);

	register_pipe  ("AJIT_to_ENV_logger",LOGGER_PIPE_DEPTH, 32,0);	
	
	set_pipe_is_read_from("AJIT_to_ENV_error");
	set_pipe_is_read_from("AJIT_to_ENV_debug_response");
	set_pipe_is_read_from("AJIT_to_ENV_logger");

	register_pipe("ENV_to_mem_initialize_instr_pair", 	depth, 64,	0);
	register_pipe("ENV_to_mem_initialize_instr_pair_addr", 	depth, 32,	0);

	set_pipe_is_written_into("ENV_to_mem_initialize_instr_pair");
	set_pipe_is_written_into("ENV_to_mem_initialize_instr_pair_addr");

	register_pipe ("SERIAL_TO_DEVICE_REQUEST_TYPE", depth, 8, 0);
	set_pipe_is_read_from ("SERIAL_TO_DEVICE_REQUEST_TYPE");
	register_pipe ("SERIAL_TO_DEVICE_ADDR", depth, 32, 0);
	set_pipe_is_read_from ("SERIAL_TO_DEVICE_ADDR");
	register_pipe ("SERIAL_TO_DEVICE_DATA", depth, 32, 0);
	set_pipe_is_read_from ("SERIAL_TO_DEVICE_DATA");

	register_pipe  ("DEVICE_TO_SERIAL_RESPONSE", depth, 32, 0);
	set_pipe_is_written_into("DEVICE_TO_SERIAL_RESPONSE");

	register_pipe ("INTERRUPT_TO_DEVICE_REQUEST_TYPE", depth, 8, 0);
	set_pipe_is_read_from ("INTERRUPT_TO_DEVICE_REQUEST_TYPE");
	register_pipe ("INTERRUPT_TO_DEVICE_ADDR", depth, 32, 0);
	set_pipe_is_read_from ("INTERRUPT_TO_DEVICE_ADDR");
	register_pipe ("INTERRUPT_TO_DEVICE_DATA", depth, 32, 0);
	set_pipe_is_read_from ("INTERRUPT_TO_DEVICE_DATA");

	register_pipe  ("DEVICE_TO_INTERRUPT_RESPONSE", depth, 32, 0);
	set_pipe_is_written_into("DEVICE_TO_INTERRUPT_RESPONSE");

	register_pipe ("TIMER_TO_DEVICE_REQUEST_TYPE", depth, 8, 0);
	set_pipe_is_read_from ("TIMER_TO_DEVICE_REQUEST_TYPE");
	register_pipe ("TIMER_TO_DEVICE_ADDR", depth, 32, 0);
	set_pipe_is_read_from ("TIMER_TO_DEVICE_ADDR");
	register_pipe ("TIMER_TO_DEVICE_DATA", depth, 32, 0);
	set_pipe_is_read_from ("TIMER_TO_DEVICE_DATA");

	register_pipe  ("DEVICE_TO_TIMER_RESPONSE", depth, 32, 0);
	set_pipe_is_written_into("DEVICE_TO_TIMER_RESPONSE");
	PTHREAD_CREATE(monitorLogger);
	usleep(100);	
}


void serialAccess(void)
{
	uint8_t request_type;
	uint32_t addr;
	uint32_t data;
	uint32_t response;

	while (1)
	{
		request_type = read_uint8 ("SERIAL_TO_DEVICE_REQUEST_TYPE");
		addr         = read_uint32("SERIAL_TO_DEVICE_ADDR");
		data         = read_uint32("SERIAL_TO_DEVICE_DATA");

		sendRequestToSerial(request_type,addr,data);
		readResponseFromSerial(&response);
		//printf("**** response = %x\n", response);
		write_uint32("DEVICE_TO_SERIAL_RESPONSE", response);
	}
}


void interruptAccess(void)
{
	uint8_t request_type;
	uint32_t addr;
	uint32_t data;
	uint32_t response;

	while (1)
	{
		request_type = read_uint8 ("INTERRUPT_TO_DEVICE_REQUEST_TYPE");
		addr         = read_uint32("INTERRUPT_TO_DEVICE_ADDR");
		data         = read_uint32("INTERRUPT_TO_DEVICE_DATA");

		sendRequestToIRC(request_type,addr,data);
		readResponseFromIRC(&response);
		write_uint32("DEVICE_TO_INTERRUPT_RESPONSE", response);
	}
}


void timerAccess(void)
{
	uint8_t request_type;
	uint32_t addr;
	uint32_t data;
	uint32_t response;

	while (1)
	{
		request_type = read_uint8 ("TIMER_TO_DEVICE_REQUEST_TYPE");
		addr         = read_uint32("TIMER_TO_DEVICE_ADDR");
		data         = read_uint32("TIMER_TO_DEVICE_DATA");

		sendRequestToTimer(request_type,addr,data);
		readResponseFromTimer(&response);
		write_uint32("DEVICE_TO_TIMER_RESPONSE", response);
	}
}

// Algo: form 64 bit instruction pair by reading conseutive 8 bytes, 
// address of this instruction pair is address of first byte,
// If 8 more bytes are not present following the first byte then pad 
// zeros in place of remaining bytes. This is possible if it is end of
// file or if addresses are not consecutive in mmap file.


int initialize_Memory (char* memoryMapFile) {

	FILE * file;
	file = fopen(memoryMapFile, "r");

	if(!file)
	{
		#ifdef SW
		fprintf(stderr,"\n ERROR: file %s could not be opened for reading!\n",memoryMapFile);
		#endif
		return 0;
	}

	#ifdef DEBUG
	printf("\n opened memory map file %s\n",memoryMapFile);
	#endif

	int i=0, j=0, k=0, flag = 0, flag_eof = 0;
	uint32_t instr_pair_addr = 0, addr_var = 0;
	uint32_t data = 0, data_buf = 0;
	uint64_t data64 = 0;

	int file_read=0;

	while (1)
	{
		if (flag == 0) {
			file_read=fscanf(file, "%x", &instr_pair_addr);
			if(feof(file)) break; 
			file_read=fscanf(file, "%x", &data);
			data64 = (uint8_t) data;
		}
		else {
			instr_pair_addr = addr_var;
			data64 = (uint8_t) data_buf;
			flag = 0;
		}

		for (i=0; i<7; i++) {
			file_read=fscanf(file, "%x", &addr_var);

			if(feof(file)) {
				flag_eof = 1;
				break; 
			}

			// check addresses are consecutive
			if (addr_var == (instr_pair_addr + 1 + i)) {
				file_read=fscanf(file, "%x", &data);
				data64 = (data64 << 8) | ((uint8_t) data);
			}

			// if addresses are not consecutive
			else {
				file_read=fscanf(file, "%x", &data_buf);
				for (j=i; j<7; j++) {
					data64 = (data64 << 8) | ((uint8_t) 0);
				}
				flag = 1;
				break;
			}
		}

		if (flag_eof == 1)
			break;
		else {
			fprintf (stderr, "addr = %x, instr_pair = %lx\n", instr_pair_addr, data64);
			write_uint64("ENV_to_mem_initialize_instr_pair", data64);
			write_uint32("ENV_to_mem_initialize_instr_pair_addr", instr_pair_addr);
		}

	}

	for (j=i; j<7; j++) {
		data64 = (data64 << 8) | ((uint8_t) 0);
		k = 1;
	}

	if (k == 1) {
		fprintf (stderr, "addr = %x, instr_pair = %lx\n", instr_pair_addr, data64);
		write_uint64("ENV_to_mem_initialize_instr_pair", data64);
		write_uint32("ENV_to_mem_initialize_instr_pair_addr", instr_pair_addr);
	}

	#ifdef DEBUG
	printf("\n Finished initializing memory from file %s.\
			\nLast address written = %x",memoryMapFile, addr);
	#endif

	fclose(file);
	return 1;
}
