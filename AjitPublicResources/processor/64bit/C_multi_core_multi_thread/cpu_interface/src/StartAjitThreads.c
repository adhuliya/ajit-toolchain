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
#include "AjitThread.h"
#include "ThreadInterface.h"
#include "StartAjitThreads.h"

ThreadState* makeThreadState(uint32_t core_id,
				uint32_t thread_id, int isa_mode, 
				int bp_table_size, int report_traps, uint32_t init_pc)
{
	ThreadState* s = (ThreadState*) malloc (sizeof(ThreadState));
	init_ajit_thread (s, core_id, thread_id, isa_mode, bp_table_size, report_traps, init_pc);
	return(s);
}

void* root_thread_thread (void* id_ptr)
{
	ajit_thread(id_ptr);
	return(NULL);
}



//register all pipes
//used by the cpu module
void register_thread_pipes(ThreadState* thread_state)
{
	int depth = 2;
	int logger_pipe_depth = 3;

	// There will be separate pipes for each thread..

	//  This will be defined by the testbench
	//	register_pipe(thread_state->reset_pipe_name, 		depth, 8,	0);
	register_pipe(thread_state->error_pipe_name, 		depth, 8,	0);
	
	//BP_IRL is a signal, that allows non-blocking reads to it
	//uint32_t register_port(char* id, int pipe_width, int is_input);
	register_port(thread_state->ilvl_pipe_name, 8, 1);

	
	// processor mode.
	register_port(thread_state->mode_pipe_name, 8, 1);

	// logger.
	register_pipe(thread_state->logger_pipe_name, 		logger_pipe_depth, 32,	0);
}



ThreadState* start_ajit_thread(ThreadState* s)
{
	register_thread_pipes(s);

	pthread_t cpu_t;
	pthread_create(&cpu_t, NULL, &root_thread_thread, (void*) s);

	return(s);
}
