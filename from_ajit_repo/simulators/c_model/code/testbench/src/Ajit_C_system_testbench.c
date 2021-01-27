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
//		SDHC

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
#include "Sdhc.h"
#include "sd.h"

#include "StartCpuThreads.h"

#include "StartHwServerThreads.h"
#include "CpuHWserverInterface.h"
#include "StartGPBThreads.h"
#include "monitorLogger.h"
#include "startMonitorLogger.h"
#include "do_val.h"
#include "bridge.h"

ProcessorState* cpu_state_vector[4];

//Routine to detect and exit upon 
//an error condition in the cpu
int checkErrorStateAndExit_core(ProcessorState* cpu_state)
{

	//AJIT_to_ENV_error is asserted by the cpu when 
	//a "ta 0" instruction is encountered,
	//indicating end of the program.
	//print a count of total instructions executed
	//by the cpu during the running of the workload
	read_uint8(cpu_state->error_pipe_name);
	printCpuStatistics (cpu_state);
	return(0);
}

void checkErrorStateAndExit_0(void* cpu_state)
{
	checkErrorStateAndExit_core((ProcessorState*) cpu_state);	
}
DEFINE_THREAD_WITH_ARG(checkErrorStateAndExit_0, cs);

void checkErrorStateAndExit_1(void* cpu_state)
{
	checkErrorStateAndExit_core((ProcessorState*) cpu_state);	
}
DEFINE_THREAD_WITH_ARG(checkErrorStateAndExit_1, cs);

void checkErrorStateAndExit_2(void* cpu_state)
{
	checkErrorStateAndExit_core((ProcessorState*) cpu_state);	
}
DEFINE_THREAD_WITH_ARG(checkErrorStateAndExit_2, cs);

void checkErrorStateAndExit_3(void* cpu_state)
{
	checkErrorStateAndExit_core((ProcessorState*) cpu_state);	
}
DEFINE_THREAD_WITH_ARG(checkErrorStateAndExit_3, cs);

void print_usage(char* app_name)
{
	fprintf(stderr, "USAGE: ");
	fprintf(stderr, "   %s -n <number-of-cpus> -m <mmap-file> [-g -p <gdb-port-number>] [-d -r <results-file> -l <log-file>]  [-w <write-trace-logger-file>] [-S <logger-server-ip> -P <logger-server-port>] \n", app_name);
	fprintf(stderr, "   -n <number-of-cpus>     : specifies number-of-cpus in the processor for this test.\n");
	fprintf(stderr, "                 : default is 1, maximum is 4.\n");
	fprintf(stderr, "   -u <32/64>:  use -u 64 to run model in 64-bit mode [default is 32]\n");
	fprintf(stderr, "   -m <mmap-file>     : required, specifies memory-map of processor for this test.\n");
	fprintf(stderr, "   -b <bp-size>, optional,  branch predictor table size (default=16)\n");
	fprintf(stderr, "   -B <bridge-target-configuration optional, sets up memory map at bridge\n");
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
	fprintf(stderr, "   -v optional, verbose flag for printing lots of junk.\n");
	fprintf(stderr, "   -I <reporting-interval>, optional, for specifying interval at which Instr summary is printed. default is 10000000.\n");
	fprintf(stderr, "   -R <randomization-seed>, optional, for randomizing initial memory values (if omitted, memory will be initialized to 0).\n");
	fprintf(stderr, "   -i <init-pc>, optional, for specifying  initial value of PC (default=0). NPC is PC+4\n");
	fprintf(stderr, "                                                                         \n");
	fprintf(stderr, "EXAMPLE:  \n");
	fprintf(stderr, "          %s -m add_test.mmap -d -l add_test.log -r add_test.results -w add_test.wtrace \n", app_name);
}


void Handle_Segfault(int signal)
{
	fprintf(stderr, "Error:  segmentation fault! giving up!!\n");
	exit(-1);
}


int getCpuId(char n)
{
	int CPU_ID = ( (n == '0') ? 0 : 
				( n == '1') ? 1 : 
					(n == '2') ? 2 : 
						(n=='3') ? 3 : 0);
	return(CPU_ID);
}

void Handle_Ctrl_C(int signal)
{
	int CPU_ID;
	fprintf(stderr, "Ctrl-C, continue.. specify actions.. !!\n");

	fprintf(stderr,"Actions?  [m/i/d/c/q/r]<cpu-id> mmu/icache/dcache/cpu/quit/return: for example m0 \n");
	int quit_flag = 0;
	int continue_flag = 0;
	char c, n;
	while(1)
	{
		c = getchar();
		switch(c)
		{
			case  'm':
				n = getchar();		
				CPU_ID = getCpuId(n);
				printMmuStatistics   (cpu_state_vector[CPU_ID]->mmu_state);
				printStatistics (cpu_state_vector[CPU_ID]->mmu_state->rlut);
				break;
			case  'i':
				n = getchar();		
				CPU_ID = getCpuId(n);
				printCacheStatistics (cpu_state_vector[CPU_ID]->dcache);
				break;
			case  'd':
				n = getchar();		
				CPU_ID = getCpuId(n);
				printCacheStatistics (cpu_state_vector[CPU_ID]->icache);
				break;
			case  'c':
				n = getchar();		
				CPU_ID = getCpuId(n);
				printCpuStatistics (cpu_state_vector[CPU_ID]);
				break;
			case  'q':
				quit_flag = 1;
				fprintf(stderr,"OK quit\n");
				break;
			case  'r':
				continue_flag = 1;
				fprintf(stderr,"OK continuing..\n");
				break;
			default:
				fprintf(stderr,"Unknown option %c\n", c);
				break;
		}

		if(quit_flag || continue_flag)
			break;
	}

	if(quit_flag)
		exit(-1);

	return;
}



int checkErrorStateAndExit(ProcessorState* cpu_state); //thread to check for termination 

//Variables used for logging
FILE* reg_write_file;
FILE* long_reg_write_file;
char* logger_server_ip_address;
int   logger_server_port_number;
int   global_verbose_flag = 0;
char* bridge_targets_file = NULL;


int main(int argc, char **argv)
{
	int main_ret_val = 0;
	uint32_t reporting_interval  = 0; 
	time_t start_t, end_t, total_t;

	signal(SIGINT,  Handle_Ctrl_C);
	signal(SIGTERM, Handle_Segfault);


	//process the arguments:
	char* mmap_file_name  = NULL;

	//gdb-related
	uint8_t	gdb_flag = 0;
	int	gdb_port_num[4];
	int     gdb_port_index = 0;
	gdb_port_num[0] = -1; gdb_port_num[1] = -1; gdb_port_num[2] = -1; gdb_port_num[3] = -1;

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

	int NCPUs=1;

	int number_of_address_bits = LOG_OF_MEMORY_SIZE;
	int bp_table_size = 16;

	//console related
	int console_server_port = -1;

	int u_mode = 32;
	int randomization_seed = -1;

	uint32_t init_pc = 0;

	while ((opt = getopt(argc, argv, "hvdgm:w:r:l:S:P:p:c:q:n:u:I:R:b:i:B:")) != -1) {
		switch(opt) {
			case 'i':
				if(strstr(optarg,"0x") == NULL)
					sscanf(optarg,"%d", &init_pc);
				else
					sscanf(optarg,"0x%x",&init_pc);
				fprintf(stderr,"Info: init_pc=0x%x.\n", init_pc);
				break;
			case 'n':
				NCPUs = atoi(optarg);
				fprintf(stderr,"Info: number of cpus=%d.\n", NCPUs);
				break;
			case 'u':
				u_mode = atoi(optarg);
				fprintf(stderr,"Info: cpu will run in %d-bit mode.\n", u_mode);
				break;
			case 'h':
				print_usage(argv[0]);
				return(0);
				break;
			case 'm': 
				mmap_file_name = strdup(optarg);
				break;

			case 'b': 
				bp_table_size = atoi(optarg);
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

					fprintf(stderr,"Info: gdb port for CPU %d is %s.\n", 
							gdb_port_index%4,
							optarg);

					gdb_port_num[gdb_port_index%4] = atoi(gdb_port_num_str);

					gdb_port_index++;

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
			case  'I':
				reporting_interval = atoi(optarg);
				break;
			case  'R':
				randomization_seed = atoi(optarg);
				srand(randomization_seed);
				setRandomizeFlag(1);
				break;
			case 'B':
				bridge_targets_file = strdup(optarg);
				fprintf(stderr,"Info: bridge targets file is %s\n", bridge_targets_file);
				break;
			default: 
				fprintf(stderr,"Error: unknown option %c\n", opt);
				break;
		}
	}

	fprintf(stderr,"Info: branch-predictor table size=%d.\n", bp_table_size);

	initBridgeTargets();
	if(bridge_targets_file != NULL)
	{
		setupBridgeTargetsAndPeripherals(bridge_targets_file);
	}
	else
	{
		// defaults.
		addMem ("lowermem", 0x3, 0x0, 0xFFFF2FFF);	 // lower mem program + data.
		addPeripheral("irc", 0xFFFF3000, 0xFFFF3008);	 // interrupt controller.
		addPeripheral("timer", 0xFFFF3100, 0xFFFF3108);	 // timer
		addPeripheral("serial", 0xFFFF3200, 0xFFFF32FF); // serial
		addPeripheral("sdhc", 0xFFFF3300, 0xFFFF33FF); //sdhc
		addMem ("uppermem", 0x3, 0xFFFF3400, 0xFFFFFFFF);// upper mem (for stack).	
	}



	//check arguments:
	if((u_mode != 32) && (u_mode != 64))
	{
		fprintf(stderr,"\n ERROR: isa-mode of CPU's is %u, but must be either 32 or 64.\n",
					u_mode);
		print_usage(argv[0]);
		return(1);
	}

	if((NCPUs < 0) || (NCPUs > 4))
	{
		fprintf(stderr,"\n ERROR: number-of-cpus must be between 0 and 4.\n");
		print_usage(argv[0]);
		return(1);
	}
	
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
	if (gdb_flag && (gdb_port_index < NCPUs))
	{
		fprintf(stderr,"\nERROR: gdb remote port numbers are not completely specified!\n");
		return(1);
	}


	//argument-processing done.
	
	//First and foremost, start the pipe handler
	init_pipe_handler();

	
	//Now lets prepare the environment:
	fprintf(stderr,"Info: starting environment threads\n");
	
	//memory
	if(allocateMemory(number_of_address_bits)!=1) return 1;
	if(initializeMemory(mmap_file_name)!=1) return 0;

	register_port ("ENV_to_AJIT_reset_0",8,1);
	register_port ("ENV_to_AJIT_reset_1",8,1);
	register_port ("ENV_to_AJIT_reset_2",8,1);
	register_port ("ENV_to_AJIT_reset_3",8,1);

	write_uint8 ("ENV_to_AJIT_reset_0",1);
	write_uint8 ("ENV_to_AJIT_reset_1",1);
	write_uint8 ("ENV_to_AJIT_reset_2",1);
	write_uint8 ("ENV_to_AJIT_reset_3",1);


	//finally, start the cpu thread
	cpu_state_vector[0] = cpu_state_vector[1] = cpu_state_vector[2] = cpu_state_vector[3] = NULL;

	// get 1 processor up and running.
	//    (this registers the cpu related pipes).
	int CPUID;
	for (CPUID = 0; CPUID < NCPUs; CPUID++)
	{
		cpu_state_vector[CPUID] = makeProcessorState(CPUID, u_mode, bp_table_size, global_verbose_flag, init_pc);
		cpu_state_vector[CPUID]->reporting_interval = reporting_interval;

		//HW_server thread, required for doval/gdb
		if(doval_flag || gdb_flag)
		{
			// registers hw-server and debug pipes.
			cpu_state_vector[CPUID]->hw_server = start_hw_server(CPUID);
			cpu_enable_HW_server(cpu_state_vector[CPUID], gdb_flag, doval_flag);
		}

		// start the cpu now.
		start_cpu_thread(cpu_state_vector[CPUID]);
	}

	//peripherals
	if(USE_INTERRUPT_CONTROLLER_MODEL) start_IRC_threads();
	if(USE_TIMER_MODEL)  start_timer_threads();
	if(USE_SDHC_MODEL) startSdhcThreads(); startSdCardThreads();
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
	//bridge between the MMU and memory:
	register_bridge_pipes (NCPUs);
	start_bridge_daemons  (NCPUs);

	// get run time
	start_t = time(NULL);
	

	//gdb
	if(gdb_flag)
	{
		fprintf(stderr,"Info: starting GDB threads.\n");
		int gpb_not_ok = start_gpb_threads(NCPUs, gdb_port_num);
	
		if(gpb_not_ok)
		{
			fprintf(stderr,"Error: in starting GDB remote servers.\n");
			return(1);
		}

	}

	//monitor logger
	if(log_flag)
	{
		for (CPUID = 0; CPUID < NCPUs; CPUID++)
		{
			fprintf(stderr,"Info: starting monitorLogger thread for cpu %d.\n", CPUID);
			// this also registers the logger pipe.
			cpu_state_vector[CPUID]->monitor_logger = 
				start_monitor_logger_thread(CPUID, reg_write_file_name,
						long_reg_write_file_name,
						logger_server_ip_address,
						logger_server_port_number,
						global_verbose_flag);

			enable_logging_by_cpu(cpu_state_vector[CPUID]);
		}
	}

	// bring the CPU's out of reset
	write_uint8 ("ENV_to_AJIT_reset_0",0);
	write_uint8 ("ENV_to_AJIT_reset_1",0);
	write_uint8 ("ENV_to_AJIT_reset_2",0);
	write_uint8 ("ENV_to_AJIT_reset_3",0);

	if(doval_flag)
	{
		int err = 0;
		for(CPUID=0; CPUID < NCPUs; CPUID++)
		{
			//send a connect request
			write_uint32(cpu_state_vector[CPUID]->hw_server->debug_command_pipe_name, 0x010E0000); 
			//wait for a 'TA 0' response to indicate end of test.
			uint32_t msg = read_uint32(cpu_state_vector[CPUID]->hw_server->debug_response_pipe_name); 
			if ( msg == 0x54412030 )	
			{
				fprintf(stderr,"\nInfo: doval connected to CPU %d\n", CPUID);
			}
			else
			{
				fprintf(stderr,"\nERROR: doval connect error to CPU %d\n", CPUID);
				err = 1;
			}
		}

		if (!err)
		{
			fprintf (stderr, "\n\nValidating : Result file = %s, Log file = %s\n", results_file_name, log_file_name);
			main_ret_val = doval (cpu_state_vector, 
					results_file_name, log_file_name);
			if(main_ret_val == 0)
				fprintf(stderr, "\n\nTests Successful.\n");
			else
				fprintf(stderr, "\n\nERROR: Tests Failed.\n");

			//send continue
			for(CPUID=0; CPUID < NCPUs; CPUID++)
				write_uint32(cpu_state_vector[CPUID]->hw_server->debug_command_pipe_name, 0x01100000);
		}
	}

	// listen for CPU error 
	PTHREAD_DECL(checkErrorStateAndExit_0);
	PTHREAD_DECL(checkErrorStateAndExit_1);
	PTHREAD_DECL(checkErrorStateAndExit_2);
	PTHREAD_DECL(checkErrorStateAndExit_3);

	PTHREAD_CREATE_WITH_ARG(checkErrorStateAndExit_0, ((void*) cpu_state_vector[0]));
	if(NCPUs > 1)
		PTHREAD_CREATE_WITH_ARG(checkErrorStateAndExit_1, ((void*) cpu_state_vector[1]));
	if(NCPUs > 2)
		PTHREAD_CREATE_WITH_ARG(checkErrorStateAndExit_2, ((void*) cpu_state_vector[2]));
	if(NCPUs > 3)
		PTHREAD_CREATE_WITH_ARG(checkErrorStateAndExit_3, ((void*) cpu_state_vector[3]));

	PTHREAD_JOIN(checkErrorStateAndExit_0);
	if(NCPUs > 1)
		PTHREAD_JOIN(checkErrorStateAndExit_1);
	if(NCPUs > 2)
		PTHREAD_JOIN(checkErrorStateAndExit_2);
	if(NCPUs > 3)
		PTHREAD_JOIN(checkErrorStateAndExit_3);


	end_t = time(NULL);


	total_t = end_t - start_t;
	fprintf(stderr,"Total time taken by testbench: %ld secs\n", total_t);
	for(CPUID = 0; CPUID < NCPUs; CPUID++)
	{
		printMmuStatistics   (cpu_state_vector[CPUID]->mmu_state);
		printStatistics (cpu_state_vector[CPUID]->mmu_state->rlut);
		printCacheStatistics (cpu_state_vector[CPUID]->icache);
		printCacheStatistics (cpu_state_vector[CPUID]->dcache);
	}

	if(gdb_flag)
	{
		// stop gdb server bridge
		stop_gpb_threads(NCPUs);
	}

	return (main_ret_val);
}



