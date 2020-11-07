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
#include "SparcCore.h"
#include "CpuInterface.h"
#include "StartCpuThreads.h"

ProcessorState* makeProcessorState(int cpu_id, int isa_mode, int bp_table_size, int report_traps, uint32_t init_pc)
{
	ProcessorState* s = (ProcessorState*) malloc (sizeof(ProcessorState));
	init (s, cpu_id, isa_mode, bp_table_size,  report_traps, init_pc);
	return(s);
}

void cpu_0 (void* id_ptr)
{
	cpu(id_ptr);
}
DEFINE_THREAD_WITH_ARG (cpu_0, id_ptr);
void cpu_1 (void* id_ptr)
{
	cpu(id_ptr);
}
DEFINE_THREAD_WITH_ARG (cpu_1, id_ptr);
void cpu_2 (void* id_ptr)
{
	cpu(id_ptr);
}
DEFINE_THREAD_WITH_ARG (cpu_2, id_ptr);
void cpu_3 (void* id_ptr)
{
	cpu(id_ptr);
}
DEFINE_THREAD_WITH_ARG (cpu_3, id_ptr);



//register all pipes
//used by the cpu module
void register_cpu_pipes(ProcessorState* cpu_state)
{
	int depth = 2;
	int logger_pipe_depth = 3;

	// There will be separate pipes for each cpu..

	//  This will be defined by the testbench
	//	register_pipe(cpu_state->reset_pipe_name, 		depth, 8,	0);
	register_pipe(cpu_state->error_pipe_name, 		depth, 8,	0);
	
	//BP_IRL is a signal, that allows non-blocking reads to it
	//uint32_t register_port(char* id, int pipe_width, int is_input);
	register_port(cpu_state->ilvl_pipe_name, 8, 1);

	
	// processor mode.
	register_port(cpu_state->mode_pipe_name, 8, 1);

	// logger.
	register_pipe(cpu_state->logger_pipe_name, 		logger_pipe_depth, 32,	0);
}



ProcessorState* start_cpu_thread(ProcessorState* s)
{

	register_cpu_pipes(s);
	register_mmu_pipes(s->mmu_state);

	PTHREAD_DECL(cpu_0);
	PTHREAD_DECL(cpu_1);
	PTHREAD_DECL(cpu_2);
	PTHREAD_DECL(cpu_3);

	void* id_ptr = (void*) s;
	if(s->cpu_id == 0)
		PTHREAD_CREATE_WITH_ARG(cpu_0, id_ptr);
	if(s->cpu_id == 1)
		PTHREAD_CREATE_WITH_ARG(cpu_1, id_ptr);
	if(s->cpu_id == 2)
		PTHREAD_CREATE_WITH_ARG(cpu_2, id_ptr);
	if(s->cpu_id == 3)
		PTHREAD_CREATE_WITH_ARG(cpu_3, id_ptr);

	return(s);
}
