//StartCpuThreads.c

//Routines to start the cpu as a thread,
//and register all pipes used.


#ifdef SW
#include<stdio.h>
#endif
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "CpuInterface.h"
#include "StartCpuThreads.h"


void cpu();
DEFINE_THREAD (cpu);



//register all pipes
//used by the cpu module
void register_cpu_pipes()
{

	int depth = 2;
	int logger_pipe_depth = 3;

	register_pipe("CPU_to_ICACHE_asi",	 	depth, 8,	0);
	register_pipe("CPU_to_ICACHE_addr",	 	depth, 32,	0);
	register_pipe("ICACHE_to_CPU_mae", 		depth, 8,	0);
	register_pipe("ICACHE_to_CPU_instr_pair", 	depth, 64,	0);
	register_pipe("ICACHE_to_CPU_fsr", 		depth, 32,	0);

	register_pipe("CPU_to_DCACHE_asi",	 	depth, 8,	0);
	register_pipe("CPU_to_DCACHE_addr",	 	depth, 32,	0);
	register_pipe("CPU_to_DCACHE_request_type", 	depth, 8,	0);
	register_pipe("CPU_to_DCACHE_byte_mask", 	depth, 8,	0);
	register_pipe("CPU_to_DCACHE_data", 		depth, 64,	0);
	register_pipe("DCACHE_to_CPU_mae", 		depth, 8,	0);
	register_pipe("DCACHE_to_CPU_data", 		depth, 64,	0);

	register_pipe("ENV_to_AJIT_reset_in", 		depth, 8,	0);
	register_pipe("AJIT_to_ENV_error", 		depth, 8,	0);
	
	//BP_IRL is a signal, that allows non-blocking reads to it
	//uint32_t register_port(char* id, int pipe_width, int is_input);
	register_port("ENV_to_AJIT_irl", 8, 1);
	register_port("ENV_to_CPU_irl", 8, 1);

	register_pipe("AJIT_to_ENV_logger", 		logger_pipe_depth, 32,	0);
}



void start_cpu_threads()
{
	register_cpu_pipes();
	PTHREAD_DECL(cpu);
	PTHREAD_CREATE(cpu);
}
