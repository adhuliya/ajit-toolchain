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
#include "ThreadInterface.h"
#include "ThreadLogging.h"
#include "StatsKeeping.h"
#include "DummyDcache.h"
#include "DummyIcache.h"
#include "CacheInterface.h"
#include "Mmu.h"
#include "memory.h"
#include "Timer.h"
#include "InterruptController.h"
#include "Serial.h"
#include "console.h"

#include "StartAjitThreads.h"

#include "StartHwServerThreads.h"
#include "ThreadHWserverInterface.h"
#include "StartGPBThreads.h"
#include "monitorLogger.h"
#include "startMonitorLogger.h"
#include "do_val.h"
#include "bridge.h"


pthread_t   error_threads[MAX_NCORES*MAX_NTHREADS_PER_CORE];
	
	//register_port ("ENV_to_AJIT_reset_3",8,1);
void registerResetPorts(uint32_t NCORES, uint32_t NTHREADS)
{
	int CID,TID;
	for(CID  = 0; CID < NCORES; CID++)
	{
		for(TID=0; TID < NCORES; TID++)
		{
			char reset_buf[1024];
			sprintf(reset_buf,"ENV_to_AJIT_reset_%d_%d", CID,TID);
			register_port (reset_buf,8,1);

			sprintf(reset_buf,"ENV_to_THREAD_irl_%d_%d", CID,TID);
			register_port (reset_buf,8,1);
		}
	}
}

void writeSpecifiedResetValueToAllThreads(uint32_t NCORES, uint32_t NTHREADS, uint8_t reset_val)
{
	int CID,TID;
	for(CID  = 0; CID < NCORES; CID++)
	{
		for(TID=0; TID < NCORES; TID++)
		{
			char reset_buf[1024];
			sprintf(reset_buf,"ENV_to_AJIT_reset_%d_%d", CID,TID);
			write_uint8(reset_buf,reset_val);
		}
	}
}

//Routine to detect and exit upon 
//an error condition in the cpu
int checkErrorStateAndExit_core(ThreadState* thread_state)
{

	//AJIT_to_ENV_error is asserted by the cpu when 
	//a "ta 0" instruction is encountered,
	//indicating end of the program.
	//print a count of total instructions executed
	//by the cpu during the running of the workload
	read_uint8(thread_state->error_pipe_name);

	printThreadStatistics (thread_state);
	return(0);
}

void* checkErrorStateAndExit(void* thread_state)
{
	checkErrorStateAndExit_core((ThreadState*) thread_state);	
	return(NULL);
}
DEFINE_THREAD_WITH_ARG(checkErrorStateAndExit, cs);


void print_usage(char* app_name)
{
	fprintf(stderr, "USAGE: ");
	fprintf(stderr, "   %s -n <number-of-cpus> -m <mmap-file> [-g -p <gdb-port-number>] [-d -r <results-file> -l <log-file>]  [-w <write-trace-logger-file>] [-S <logger-server-ip> -P <logger-server-port>] \n", app_name);
	fprintf(stderr, "   -n <number-of-cores>     : specifies number-of-cores in the processor for this test.\n");
	fprintf(stderr, "                 : default is 1, maximum is 4.\n");
	fprintf(stderr, "   -t <number-of-threads-per-core>     : specifies number-of-threads-per-core in the processor for this test.\n");
	fprintf(stderr, "                 : default is 1, maximum is 2.\n");
	fprintf(stderr, "   -u <32/64>:  use -u 64 to run model in 64-bit mode [default is 32]\n");
	fprintf(stderr, "   -m <mmap-file>     : required, specifies memory-map of processor for this test.\n");
	fprintf(stderr, "   -b <bp-size>, optional,  branch predictor table size (default=16)\n");
	fprintf(stderr, "   -D <dcache-size-in-lines>, optional  (default=512)\n");
	fprintf(stderr, "   -N <icache-size-in-lines>, optional  (default=512)\n");
	fprintf(stderr, "   -B <bridge-target-configuration optional, sets up memory map at bridge\n");
	fprintf(stderr, "   -g, optional, to run the CORE in debug mode.\n");
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
	fprintf(stderr, "   -e <cache-trace-file>, optional, for specifying cache access dump file.\n");
	fprintf(stderr, "                                                                         \n");
	fprintf(stderr, "EXAMPLE:  \n");
	fprintf(stderr, "          %s -m add_test.mmap -d -l add_test.log -r add_test.results -w add_test.wtrace \n", app_name);
}


void Handle_Segfault(int signal)
{
	fprintf(stderr, "Error:  segmentation fault! giving up!!\n");
	exit(-1);
}


int getThreadId(char n)
{
	int CORE_ID = ( (n == '0') ? 0 : 
				( n == '1') ? 1 : 
					(n == '2') ? 2 : 
						(n=='3') ? 3 : 0);
	return(CORE_ID);
}

int  __query__() 
{
	fprintf(stderr,"type q to exit... something else to continue\n");

	char q = getchar();
	fprintf(stderr," you typed %c\n", q);

	if(q == 'q') 
	{
		return(1);
	}	
	
	return(0);
}

void Handle_Ctrl_C(int signal)
{
	fprintf(stderr, "Ctrl-C.. !!\n");
	exit(-1);
}




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

	// maximum of 8 threads.
	int	gdb_port_num[MAX_NCORES*MAX_NTHREADS_PER_CORE];
	int     gdb_port_index = 0;

	int CT;
	for(CT = 0; CT < MAX_NCORES*MAX_NTHREADS_PER_CORE; CT++)
		gdb_port_num[CT] = -1;

	//doval-related
	uint8_t doval_flag = 0;
	char* 	results_file_name = NULL;
	char* 	log_file_name = NULL;

	//logging-related
	uint8_t log_flag = 0;
	char* 	reg_write_file_name = NULL;
	char*   long_reg_write_file_name = NULL;
	char*   cache_trace_file_name = NULL;
	logger_server_ip_address = NULL;
	logger_server_port_number=-1;
	int opt;

	uint32_t NCOREs=1;
	uint32_t NTHREADs = 1;

	int number_of_address_bits = LOG_OF_MEMORY_SIZE;
	uint32_t bp_table_size = 16;

	//console related
	int console_server_port = -1;

	uint32_t u_mode = 32;
	int randomization_seed = -1;

	uint32_t init_pc = 0;

	uint32_t dcache_number_of_lines = 512;
	uint32_t icache_number_of_lines = 512;

	while ((opt = getopt(argc, argv, "hvdgm:w:r:l:S:P:p:c:q:n:u:I:R:b:i:B:D:N:t:e:")) != -1) {
		switch(opt) {
			case 'i':
				if(strstr(optarg,"0x") == NULL)
					sscanf(optarg,"%d", &init_pc);
				else
					sscanf(optarg,"0x%x",&init_pc);
				fprintf(stderr,"Info: init_pc=0x%x.\n", init_pc);
				break;
			case 'D':
				dcache_number_of_lines = atoi(optarg);
				break;
			case 'N':
				icache_number_of_lines = atoi(optarg);
				break;
			case 'e':
				cache_trace_file_name = strdup(optarg);
				fprintf(stderr,"Info: cache trace file=%s.\n", cache_trace_file_name);
				break;
			case 'n':
				NCOREs = atoi(optarg);
				fprintf(stderr,"Info: number of cores=%d.\n", NCOREs);
				break;
			case 't':
				NTHREADs = atoi(optarg);
				fprintf(stderr,"Info: number of threads per core=%d.\n", NTHREADs);
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

					fprintf(stderr,"Info: gdb port for core,thread=%d,%d is %s.\n", 
							gdb_port_index/NTHREADs,
							gdb_port_index%NTHREADs,
							optarg);

					
					gdb_port_num[gdb_port_index] = atoi(gdb_port_num_str);
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

	if(cache_trace_file_name != NULL)
	{
		FILE* cache_trace_file = NULL;

		if(strcmp(cache_trace_file_name,"stdout") == 0)
			cache_trace_file = stdout;	
		else
			cache_trace_file = fopen(cache_trace_file_name,"w");

		if(cache_trace_file != NULL)
		{
			setCacheTraceFile(cache_trace_file);
		}
		else
		{
			fprintf(stderr,"Error: could not open cache trace file %s\n", cache_trace_file_name);
		}
	}

	registerResetPorts(NCOREs, NTHREADs);

	fprintf(stderr,"Info: branch-predictor table size=%d.\n", bp_table_size);
	fprintf(stderr,"Info: dcache-number-of-lines=0x%x.\n", dcache_number_of_lines);
	fprintf(stderr,"Info: icache-number-of-lines=0x%x.\n", icache_number_of_lines);

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
		addMem ("uppermem", 0x3, 0xFFFF3300, 0xFFFFFFFF);// upper mem (for stack).	
	}



	//check arguments:
	if((u_mode != 32) && (u_mode != 64))
	{
		fprintf(stderr,"\n ERROR: isa-mode of CORE's is %u, but must be either 32 or 64.\n",
					u_mode);
		print_usage(argv[0]);
		return(1);
	}

	if((NCOREs < 0) || (NCOREs > MAX_NCORES))
	{
		fprintf(stderr,"\n ERROR: number-of-cores must be between 0 and %d.\n", MAX_NCORES);
		print_usage(argv[0]);
		return(1);
	}
	if((NTHREADs <= 0) || (NTHREADs > MAX_NTHREADS_PER_CORE))
	{
		fprintf(stderr,"\n ERROR: number-of-threads-per-core must 1 or %d.\n", MAX_NTHREADS_PER_CORE);
		print_usage(argv[0]);
		return(1);
	}

	bridgeSetNcores(NCOREs);
	
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
	if (gdb_flag && (gdb_port_index < NCOREs))
	{
		fprintf(stderr,"\nERROR: gdb remote port numbers are not completely specified!\n");
		return(1);
	}


	//First and foremost, start the pipe handler
	init_pipe_handler();

	// ensure that the pipe handler does not accept
	// an access to an unregistered pipe.
	set_pipe_handler_in_strict_mode();


	// set up the RLUTs
	setupRlutManager(NCOREs, icache_number_of_lines, dcache_number_of_lines);

	
	//Now lets prepare the environment:
	fprintf(stderr,"Info: starting environment threads\n");
	
	//memory
	if(allocateMemory(number_of_address_bits)!=1) return 1;
	if(initializeMemory(mmap_file_name)!=1) return 0;

	registerResetPorts(NCOREs, NTHREADs);
	writeSpecifiedResetValueToAllThreads(NCOREs, NTHREADs, 1);


	int COREID, TID;
	//finally, start the core thread
	CoreState* core_state_vector[MAX_NCORES];
	for(COREID = 0; COREID < MAX_NCORES; COREID++)
		core_state_vector[COREID] = NULL;
	

	// get 1 processor up and running.
	//    (this registers the cpu related pipes).
	for (COREID = 0; COREID < NCOREs; COREID++)
	{
		core_state_vector[COREID] = 
			makeCoreState(COREID, 
						NTHREADs,
						u_mode, bp_table_size, 
						icache_number_of_lines, dcache_number_of_lines,
						global_verbose_flag, init_pc);
		setThreadReportingInterval(core_state_vector[COREID], reporting_interval);

		//HW_server thread, required for doval/gdb
		if(doval_flag || gdb_flag)
		{
			startThreadHardwareServers(core_state_vector[COREID]);
			enableThreadHardwareServers(core_state_vector[COREID], gdb_flag, doval_flag);
		}

		// start the core threads now.
		startCoreThreads(core_state_vector[COREID]);
	}

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


	// get run time
	start_t = time(NULL);
	

	// gdb
	if(gdb_flag)
	{
		fprintf(stderr,"Info: starting GDB threads.\n");
		int gpb_not_ok = start_gpb_threads(NCOREs, NTHREADs, gdb_port_num);
	
		if(gpb_not_ok)
		{
			fprintf(stderr,"Error: in starting GDB remote servers.\n");
			return(1);
		}

	}

	//monitor logger
	if(log_flag)
	{
		for (COREID = 0; COREID < NCOREs; COREID++)
		{
			for(TID = 0; TID < NTHREADs; TID++)
			{
				fprintf(stderr,"Info: starting monitorLogger thread for core,thread=%d,%d.\n", 
								COREID, TID);
				// this also registers the logger pipe.
				core_state_vector[COREID]->threads[TID]->monitor_logger = 
					start_monitor_logger_thread(COREID, TID, 
									reg_write_file_name,
									long_reg_write_file_name,
									logger_server_ip_address,
									logger_server_port_number,
									global_verbose_flag);

				enable_logging_by_thread(core_state_vector[COREID]);
			}
		}
	}

	// bring the CORE's out of reset
	writeSpecifiedResetValueToAllThreads(NCOREs, NTHREADs, 0);

	if(doval_flag)
	{
		int err = 0;
		for(COREID=0; COREID < NCOREs; COREID++)
		{
			for(TID = 0; TID < NTHREADs; TID++)
			{
				ThreadState* ts = core_state_vector[COREID]->threads[TID];
				//send a connect request
				write_uint32(ts->hw_server->debug_command_pipe_name, 0x010E0000); 

				//wait for a 'TA 0' response to indicate end of test.
				uint32_t msg = read_uint32(ts->hw_server->debug_response_pipe_name); 
				if ( msg == 0x54412030 )	
				{
					fprintf(stderr,"\nInfo: doval connected to core,thread=%d,%d\n", 
									COREID, TID);
				}
				else
				{
					fprintf(stderr,"\nERROR: doval connect error to core,thread=%d,%d\n", 
									COREID, TID);
					err = 1;
				}
			}
		}

		if (!err)
		{
			fprintf (stderr, "\n\nValidating : Result file = %s, Log file = %s\n", 
									results_file_name, log_file_name);
			main_ret_val = 
				doval (core_state_vector, results_file_name, log_file_name);
			if(main_ret_val == 0)
				fprintf(stderr, "\n\nTests Successful.\n");
			else
				fprintf(stderr, "\n\nERROR: Tests Failed.\n");

			//send continue
			for(COREID=0; COREID < NCOREs; COREID++)
			{
				for(TID = 0; TID < NTHREADs; TID++)
				{
					ThreadState* ts = core_state_vector[COREID]->threads[TID];
					write_uint32(ts->hw_server->debug_command_pipe_name, 0x01100000);
				}
			}
		}
	}

	// listen for CORE error 
	for(COREID=0; COREID < NCOREs; COREID++)
	{
		for(TID = 0; TID < NTHREADs; TID++)
		{
			
			pthread_create(&(error_threads[COREID*NTHREADs + TID]),
					   NULL, &checkErrorStateAndExit, 
						(void*) (core_state_vector[COREID]->threads[TID]));
		}
	}
	

	int J;
	for(J = 0; J < NCOREs*NTHREADs; J++)
	{
		pthread_join(error_threads[J], NULL);
		fprintf(stderr,"Info: core,thread=%d,%d finished.\n", J/NTHREADs, J%NTHREADs);
	}

	end_t = time(NULL);
	total_t = end_t - start_t;
	fprintf(stderr,"Total time taken by testbench: %ld secs\n", total_t);

	for(COREID = 0; COREID < NCOREs; COREID++)
	{
		printMmuStatistics   (core_state_vector[COREID]->mmu_state);
		printCacheStatistics (core_state_vector[COREID]->icache);
		printCacheStatistics (core_state_vector[COREID]->dcache);
	}
	printRlutStatisticsInManager ();
	return (main_ret_val);
}



