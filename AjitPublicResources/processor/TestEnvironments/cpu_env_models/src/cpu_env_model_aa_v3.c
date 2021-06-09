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
// Modified from env-v1 model to use v2 caches, mmu. Madhav Desai Sept 15, 2016
//
// Modified from env_v2 model.  Now the core includes the caches and the mmu,
// only the main-memory and peripheral devices are in the environment. Nov. 18, 2016 MPD
//

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
#include "CpuInterface.h"


//Hardware Configuration Settings are present in 
//Ajit_Hardware_Configuration.h
#include "Ajit_Hardware_Configuration.h"

int global_verbose_flag = 0;
MUTEX_DECL(__g_mutex__);


//Includes for modeling other components in the environment
//includes required for modeling
//the cpu's environment
#include "memory.h"
#include "Dcache.h"
#include "Icache.h"
#include "Mmu.h"
#include "sparc_stdio.h"
#include "StartIODriverThreads.h"
#include "Timer.h"
#include "InterruptController.h"
#include "Serial.h"
#include "Console.h"


	

// Main threads to model the environment of the CPU
void memoryAccess();
//memory initialization routine
int initialize_main_memory(char* memory_map_file, int log_of_memory_size, int use_kbd_driver, int use_display_driver);
DEFINE_THREAD (memoryAccess);
//thread to keep reading the log pipe
void monitorLogger(void);
//Function to register the cpu-side pipes if we're using SW version of the cpu
void register_core_pipes(int sw_flag, int use_display_driver, int use_kbd_driver);

DEFINE_THREAD (monitorLogger);





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
			int verbose_flag,
			FILE* logger_trace_file)    
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


	//Initialize memory using a memory map file
	MUTEX_LOCK(__g_mutex__);
	if(initialize_main_memory(memory_map_file, LOG_OF_MEMORY_SIZE,
			USE_KBD_DRIVER, USE_DISPLAY_DRIVER)==0) exit(1);
	MUTEX_UNLOCK(__g_mutex__);


	//register cpu pipes
	register_core_pipes(sw_flag, USE_DISPLAY_DRIVER, USE_KBD_DRIVER);
	
	//Start threads for caches, Mmu and memory
	//start threads for interfacing
	//cpu to the environment:
	PTHREAD_DECL(memoryAccess);
	PTHREAD_CREATE(memoryAccess);

	//Note : The variables od type USE_<COMPONENT>
	//are defined in Ajit_Hardware_Configuration.h
	
	//start keyboard and display driver threads
	if(USE_KBD_DRIVER || USE_DISPLAY_DRIVER) start_IO_driver_threads();

	//Start interrupt controller, timer, and serial device threads
	if(USE_INTERRUPT_CONTROLLER_MODEL) start_IRC_threads();
	if(USE_TIMER_MODEL)  start_timer_threads();
	if(USE_SERIAL_MODEL) start_serial_threads();
	if(USE_SERIAL_MODEL) start_console_threads();



	return (1);
}



//We need to register the cpu pipes if we're using SW version of the cpu:
void register_core_pipes(int sw_flag, int use_display_driver, int use_kbd_driver)
{
	PTHREAD_DECL(monitorLogger);

	int depth = 2;
	int LOGGER_PIPE_DEPTH=3;
	
	register_signal("ENV_to_AJIT_reset",8);
	register_signal("ENV_to_AJIT_irl", 8);
	register_pipe  ("ENV_to_AJIT_data", depth,64,0);
	register_pipe  ("ENV_to_AJIT_debug_command",8, 32,0);

	
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
	
	register_pipe("AJIT_to_ENV_request_type",depth,8,0);
	register_pipe("AJIT_to_ENV_addr",depth,64,0);
	register_pipe("AJIT_to_ENV_data",depth,64,0);
	register_pipe("AJIT_to_ENV_byte_mask",depth,8,0);
	
	set_pipe_is_read_from("AJIT_to_ENV_request_type");
	set_pipe_is_read_from("AJIT_to_ENV_addr");
	set_pipe_is_read_from("AJIT_to_ENV_data");
	set_pipe_is_read_from("AJIT_to_ENV_byte_mask");



	PTHREAD_CREATE(monitorLogger);
	usleep(100);	
}



//memoryAccess thread
//Data read/write interface between 
//MMU and main memory:
void memoryAccess(void)
{
	uint8_t request_type;
	uint32_t addr;
	uint64_t data64;
	uint8_t byte_mask;

	while (1)
	{
		request_type = 0xf & read_uint8 ("AJIT_to_ENV_request_type");
		//upper 32 bits of address on the
		//system bus are currently ignored
		addr         = read_uint64("AJIT_to_ENV_addr");
		data64       = read_uint64("AJIT_to_ENV_data");
		byte_mask    = read_uint8 ("AJIT_to_ENV_byte_mask");

	
		//Check if this request should be forwarded to the timer...
		if(USE_TIMER_MODEL && addr==ADDR_TIMER_CONTROL_REGISTER)
		{
			//forward this request to the Timer.
			//Depending on addr[2], bits[31:0] or bits[63:32]
			//of data64 are forwarded.
			uint32_t data32;
			uint32_t response;

			if(getBit32(addr,2)==0) 
				data32 = getSlice64(data64,63,32);
			else 
				data32 = getSlice64(data64,31,0);
			
			sendRequestToTimer(request_type,addr,data32);
			
			//timer is required to send an ack on data line
			readResponseFromTimer(&response);
			
			//send the response back to cpu
			if(request_type == REQUEST_TYPE_WRITE) data64=0;
			else if(getBit32(addr,2)==0) 
				data64 = setSlice64(0x00, 63,32, response);
			else 
				data64 = setSlice64(0x00,31,0, response);
			
			write_uint64("ENV_to_AJIT_data", data64);
		}
		
		//Check if this request should be forwarded to the interrupt controller
		else if(USE_INTERRUPT_CONTROLLER_MODEL && addr==ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER)
		{
			//forward this request to the  interrupt controller
			//Depending on addr[2], bits[31:0] or bits[63:32]
			//of data64 are forwarded.
			uint32_t data32;
			uint32_t response;

			if(getBit32(addr,2)==0) 
				data32 = getSlice64(data64,63,32);
			else 
				data32 = getSlice64(data64,31,0);

			sendRequestToIRC(request_type,addr,data32);
			
			//IRC is required to send an ack on data line
			readResponseFromIRC(&response);
			
			//send the response back to cpu
			if(request_type == REQUEST_TYPE_WRITE) data64=0;
			else if(getBit32(addr,2)==0) 
				data64 = setSlice64(0x00, 63,32, response);
			else 
				data64 = setSlice64(0x00,31,0, response);
			
			write_uint64("ENV_to_AJIT_data", data64);
		}
		//check if this access should be forwarded to the serial device
		else if(USE_SERIAL_MODEL && 
				(   addr==ADDR_SERIAL_CONTROL_REGISTER
				 || addr==ADDR_SERIAL_TX_REGISTER 
				 ||  addr==ADDR_SERIAL_RX_REGISTER
				 ))
		{
			//forward this request to the serial device
			//Depending on addr[2], bits[31:0] or bits[63:32]
			//of data64 are forwarded.
			uint32_t data32;
			uint32_t response;
		
			
			if(getBit32(addr,2)==0) 
				data32 = getSlice64(data64,63,32);
			else 
				data32 = getSlice64(data64,31,0);

			sendRequestToSerial(request_type,addr,data32);
			
			//the serial device is required to send an ack on data line
			readResponseFromSerial(&response);
	
			//send the response back to cpu
			if(request_type == REQUEST_TYPE_WRITE) data64=0;
			else if(getBit32(addr,2)==0) 
				data64 = setSlice64(0x00, 63,32, response);
			else 
				data64 = setSlice64(0x00,31,0, response);
			
			write_uint64("ENV_to_AJIT_data", data64);
		}
		else //this is a memory load/store
		{
			if(request_type==REQUEST_TYPE_READ || request_type==REQUEST_TYPE_IFETCH)
			{
				data64 = getDoubleWordInMemory(addr);
				write_uint64("ENV_to_AJIT_data", data64);
			}
			else if(request_type == REQUEST_TYPE_WRITE)
			{
				setDoubleWordInMemory(addr, data64, byte_mask);
				//send back the written doubleword so that
				//a copy can be maintained in 
				//our write-allocate cache if necessary
				data64 = getDoubleWordInMemory(addr);
				write_uint64("ENV_to_AJIT_data", data64);
			}
			else
			{
				//this is an invalid request
#ifdef SW
				fprintf(stderr,"\nERROR: invalid request type %d to memoryAccess thread",request_type);
				exit(1);
#endif
			}
		}

		#ifdef DEBUG
		fprintf(stderr,"\nMEMORY ACCESS THREAD :  received request from MMU  addr=0x%x, req_type=%d, byte_mask=0x%d, data=0x%lx",addr,request_type,byte_mask,data64);
		#endif


	}
}


//initialize main memory
//return 1 on success.
int initialize_main_memory(char* memory_map_file, int log_of_memory_size, 
		int use_kbd_driver, int use_display_driver)
{
	//check if memory map file exists
	FILE * fp1 = fopen(memory_map_file, "r");
	if(!fp1)
	{
		fprintf(stderr,"\n ERROR: file %s cannot be opened!\n",memory_map_file);
		return 0;
	}
	else fclose(fp1);
	//Allocate memory on the heap to model main memory
	if(allocateMemory(log_of_memory_size)!=1) return 0;

	//Initialize memory contents using a memory map file
	if(initializeMemory(memory_map_file)!=1) return 0;

	// Initialize to 0 the memory locations
	// used by keyboard and console drivers as flags:
	if(use_kbd_driver) setByteInMemory(KB_FLAG_ADDRESS, 0x00);
	if(use_display_driver) setByteInMemory(CONSOLE_FLAG_ADDRESS, 0x00);
	return 1;
}

