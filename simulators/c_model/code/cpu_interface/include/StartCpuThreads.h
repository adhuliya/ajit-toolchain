//StartCpuThreads.h
//
//Routines to start the cpu as a thread,
//and register all pipes used.

#ifndef _START_CPU_THREADS_H_
#define _START_CPU_THREADS_H_
#include "SparcCore.h"

ProcessorState* makeProcessorState(int cpu_id, int isa_mode, int bp_table_size, int report_traps, uint32_t init_pc);

//register all pipes
//used by the cpu module
void register_cpu_pipes(ProcessorState* cpu_state);

//start cpu threads
ProcessorState* start_cpu_thread(ProcessorState* s);
#endif
