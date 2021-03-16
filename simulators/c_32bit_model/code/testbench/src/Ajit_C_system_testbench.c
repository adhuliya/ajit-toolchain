//Ajit system : C model
//
// The system consists of:
// 	cpu
// 	dummy Icache/Dcache
// 	MMU
// 	memory
// 	memory-mapped peripherals:
// 		Timer
// 		Serial
// 		Interrupt controller

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <assert.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"


#include "Ajit_Hardware_Configuration.h"
#include "Ancillary.h"
#include "CpuInterface.h"
#include "CpuLogging.h"
#include "StatsKeeping.h"
#include "DummyDcache.h"
#include "DummyIcache.h"
#include "Mmu.h"
#include "memory.h"
#include "Timer.h"
#include "InterruptController.h"
#include "Serial.h"
#include "console.h"

#include "StartCacheThreads.h"
#include "StartCpuThreads.h"
#include "StartMmuThreads.h"

#include "StartHwServerThreads.h"
#include "CpuHWserverInterface.h"
#include "StartGPBThreads.h"
#include "monitorLogger.h"
#include "startMonitorLogger.h"
#include "do_val.h"


void print_usage(char* app_name)
{
	fprintf(stderr, "USAGE: ");
	fprintf(stderr, "   %s -m <mmap-file> [-g -p <gdb-port-number>] [-d -r <results-file> -l <log-file>]  [-w <write-trace-logger-file>] [-S <logger-server-ip> -P <logger-server-port>] \n", app_name);
	fprintf(stderr, "   -m <mmap-file>     : required, specifies memory-map of processor for this test.\n");
	fprintf(stderr, "   -g, optional, to run the CPU in debug mode.\n");
	fprintf(stderr, "   -q <number-of-address-bits>, optional, size of memory is 2**<number-of-address-bits>, default is 32.\n");
	fprintf(stderr, "   -p <gdb-port-number>, required with -g, to specify remote debug port.\n");
	fprintf(stderr, "   -d  : optional, use if doval utility is to be run...\n");
	fprintf(stderr, "   -r <results-file>  : required with -d, specifies expected register/memory values at end of run.\n");
	fprintf(stderr, "   -l <log-file>      : required with -d, specifies a log-file of the validation checks.\n");
	fprintf(stderr, "   -w <reg-writes-dump>: optional. if specified, a log of all register and memory writes is generated.\n");
	fprintf(stderr, "   -S <log-server-ip-addr>  : optional, specifies a logging-server-ip-addr to compare write traces.\n");
	fprintf(stderr, "   -P <log-server-ip-port>  : required with -S, specifies a logging-server-port to compare write traces.\n");
	fprintf(stderr, "   -c <console-server-port-number>, specify port for console server.\n");
	fprintf(stderr, "                                                                         \n");
	fprintf(stderr, "EXAMPLE:  \n");
	fprintf(stderr, "          %s -m add_test.mmap -d -l add_test.log -r add_test.results -w add_test.wtrace \n", app_name);
}


void Handle_Segfault(int signal)
{
	fprintf(stderr, "Error:  segmentation fault! giving up!!\n");
	exit(-1);
}


void Handle_Ctrl_C(int signal)
{
	static int count = 0;
	if(count == 1)
	{
		fprintf(stderr, "second Ctrl-C, exit\n");
		exit(-1);
	}
	fprintf(stderr, "Ctrl-C, continue.. type once more to kill process!!\n");
	count++;
}


void bridge(); //thread that functions as a bridge between the MMU and main memory
DEFINE_THREAD(bridge);

void register_bridge_pipes()
{
	int depth = 2;
	register_pipe("AJIT_to_ENV_request_type",	depth, 8,	0);
	register_pipe("AJIT_to_ENV_addr",	 	depth, 64,	0);
	register_pipe("AJIT_to_ENV_data", 		depth, 64,	0);
	register_pipe("AJIT_to_ENV_byte_mask", 		depth, 8,	0);
	register_pipe("ENV_to_AJIT_data", 		depth, 64,	0);
}

void start_bridge_threads()
{
	register_bridge_pipes();
	PTHREAD_DECL(bridge);
	PTHREAD_CREATE(bridge);
}

int checkErrorStateAndExit(void); //thread to check for termination 

//Variables used for logging
FILE* reg_write_file;
FILE* long_reg_write_file;
char* logger_server_ip_address;
int   logger_server_port_number;
int   global_verbose_flag = 0;
MUTEX_DECL_NONSTATIC(__g_mutex__);


int main(int argc, char **argv)
{
	int main_ret_val = 0;
	time_t start_t, end_t, total_t;

	signal(SIGINT,  Handle_Ctrl_C);
        signal(SIGTERM, Handle_Segfault);
	

	//process the arguments:
	char* mmap_file_name  = NULL;
	
	//gdb-related
	uint8_t	gdb_flag = 0;
	int	gdb_port_num = -1;

	//doval-related
	uint8_t doval_flag = 0;
	char* 	results_file_name = NULL;
	char* 	log_file_name = NULL;

	//logging-related
	uint8_t log_flag = 0;
	char* 	reg_write_file_name = NULL;
	char*   long_reg_write_file_name = NULL;
	logger_server_ip_address = NULL;
	logger_server_port_number=-1;
	int opt;

	int number_of_address_bits = LOG_OF_MEMORY_SIZE;

	//console related
	int console_server_port = -1;
	
	while ((opt = getopt(argc, argv, "hvdgm:w:r:l:S:P:p:c:q:")) != -1) {
		switch(opt) {
			case 'h':
				print_usage(argv[0]);
				return(0);
				break;
			case 'm': 
				mmap_file_name = strdup(optarg);
				break;

			case 'q': 
				number_of_address_bits = atoi(optarg);
				fprintf(stderr,"Info: number of address-bits in memory=%d.\n", number_of_address_bits);
				break;

			case 'g':
				gdb_flag = 1;
				break;
			case 'p':
				{
				char* gdb_port_num_str = strdup(optarg);
				gdb_port_num = atoi(gdb_port_num_str);
				break;
				}
			case 'd':
				doval_flag = 1;
				break;
			case 'r':
				results_file_name = strdup(optarg);
				break;
			case 'l':
				log_file_name = strdup(optarg);
				break;
			case 'w':
				log_flag = 1;
				reg_write_file_name = strdup(optarg);
				long_reg_write_file_name = calloc(1, (strlen(reg_write_file_name)+8)*sizeof(char));
				sprintf(long_reg_write_file_name, "%s.long", reg_write_file_name);

				break;

			case 'S':
				log_flag = 1;
				logger_server_ip_address = strdup(optarg);
				break;
			case 'P':
				logger_server_port_number = atoi(optarg);
				break;
			case 'c':
				// console-port
				console_server_port = atoi(optarg);
				break;

			case 'v': 
				global_verbose_flag = 1;
				break;
			default: 
				fprintf(stderr,"Error: unknown option %c\n", opt);
				break;
		}
	}
	
	//check arguments:
	//mem-map file
	if(mmap_file_name == NULL)
	{
		fprintf(stderr,"\n ERROR: memory-map file not specified.\n");
		print_usage(argv[0]);
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

	//logger
	if((logger_server_ip_address != NULL) && (logger_server_port_number < 0))
	{
		fprintf(stderr,"Error: logger-server-ip specified, but logger-server-port not specified.\n");
		return(1);
	}

	// if gdb selected, gdb_port_num must be specified.
	if (gdb_flag && (gdb_port_num < 0))
	{
		fprintf(stderr,"\nERROR: gdb remote port number is not specified!\n");
		return(1);
	}

				
	// register-write logging
	if(reg_write_file_name!= NULL)
	{   
		reg_write_file = fopen(reg_write_file_name,"w");
		if(reg_write_file == NULL)
			fprintf(stderr,"Warning: register-writes-trace-file not found, no trace will be dumped.\n");
		else
		{
			fprintf(reg_write_file,"//============== C model register-write trace =============\n");
			fprintf(reg_write_file,"//=====================================================================\n");
		}
	} 
	//detailed logging (if the -v option is specified along with the -w)
	if(log_flag && global_verbose_flag)
	{   
		long_reg_write_file = fopen(long_reg_write_file_name,"w");
		if(long_reg_write_file_name == NULL)
			fprintf(stderr,"Warning: file %s for long register-writes-trace not found, no trace will be dumped.\n",long_reg_write_file_name);
	} 

	//argument-processing done.
	
	//First and foremost, start the pipe handler
	init_pipe_handler();

	
	//Now lets prepare the environment:
	fprintf(stderr,"Info: starting environment threads\n");
	
	//memory
	if(allocateMemory(number_of_address_bits)!=1) return 1;
	if(initializeMemory(mmap_file_name)!=1) return 0;

	//bridge between the MMU and memory:
	start_bridge_threads();

	//peripherals
	if(USE_INTERRUPT_CONTROLLER_MODEL) start_IRC_threads();
	if(USE_TIMER_MODEL)  start_timer_threads();
	if(USE_SERIAL_MODEL) 
	{
		start_serial_threads();
		fprintf(stderr,"Info: starting console threads.\n");
		if(console_server_port > 0)
		{
			setConsoleServerPort(console_server_port);
			startConsoleServer();
		}
		startConsoleThreads();
	}

	register_cpu_pipes();
	//dummy caches
	start_cache_threads();

	//MMU
	start_mmu_threads();


	//HW_server thread, required for doval/gdb
	if(doval_flag || gdb_flag)
	{
		cpu_enable_HW_server(gdb_flag, doval_flag);
		start_debug_threads();
	}
	//gdb
	if(gdb_flag)
	{
		fprintf(stderr,"Info: starting GDB threads.\n");
		start_gpb_threads(gdb_port_num);
	}
	//monitor logger
	if(log_flag)
	{
		fprintf(stderr,"Info: starting monitorLogger thread.\n");
		start_monitor_logger();
		enable_logging_by_cpu();
	}

	//finally, start the cpu thread
	start_cpu_threads();

	// get run time
	start_t = time(NULL);
	
	
	if(doval_flag)
	{
		//send a connect request
		write_uint32("ENV_to_AJIT_debug_command", 0x010E0000); 
		//wait for a 'TA 0' response to indicate end of test.
		uint32_t msg = read_uint32("AJIT_to_ENV_debug_response"); 
		if ( msg == 0x54412030 )	
		{
			fprintf (stderr, "\n\nValidating : Result file = %s, Log file = %s\n", results_file_name, log_file_name);
			main_ret_val = doval (results_file_name, log_file_name);
			if(main_ret_val == 0)
				fprintf(stderr, "\n\nTests Successful.\n");
			else
				fprintf(stderr, "\n\nERROR: Tests Failed.\n");
			//send continue
			write_uint32("ENV_to_AJIT_debug_command", 0x01100000);
		}
	}

	// listen for CPU error 
	checkErrorStateAndExit();
	end_t = time(NULL);


	total_t = end_t - start_t;
	fprintf(stderr,"Total time taken by CPU: %ld secs\n", total_t);
	printMmuStatistics();

	if(gdb_flag)
	{
		// stop gdb server bridge
		stop_gpb_threads();
	}

	return (main_ret_val);
}
	
	


//Routine to detect and exit upon 
//an error condition in the cpu
int checkErrorStateAndExit(void)
{
	
	//AJIT_to_ENV_error is asserted by the cpu when 
	//a "ta 0" instruction is encountered,
	//indicating end of the program.
	//print a count of total instructions executed
	//by the cpu during the running of the workload
	read_uint8("AJIT_to_ENV_error");
	long instr_count = get_instruction_count();
	printf("\nTotal instructions executed = %ld\n",instr_count);
	usleep(100);
	return(0);
}





//Bridge between the MMU and main memory:
void bridge(void)
{
	uint8_t request_type;
	uint32_t addr;
	uint64_t data64;
	uint8_t byte_mask;

	while (1)
	{
		request_type = read_uint8 ("AJIT_to_ENV_request_type");
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
			if( (request_type==REQUEST_TYPE_IFETCH)
			|| (request_type==REQUEST_TYPE_READ)) 
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
				fprintf(stderr,"\nERROR: invalid request type %d to memoryAccess thread",request_type);
				exit(1);
			}
		}

		#ifdef DEBUG
		fprintf(stderr,"\nMEMORY ACCESS THREAD :  received request from MMU  addr=0x%x, req_type=%d, byte_mask=0x%d, data=0x%lx",addr,request_type,byte_mask,data64);
		#endif
	}
}
