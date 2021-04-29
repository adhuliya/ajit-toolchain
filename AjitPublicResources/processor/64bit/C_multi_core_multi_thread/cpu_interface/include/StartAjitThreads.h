//StartCpuThreads.h
//
//Routines to start the cpu as a thread,
//and register all pipes used.

#ifndef _START_CPU_THREADS_H_
#define _START_CPU_THREADS_H_
#include "AjitThread.h"

ThreadState* makeThreadState(uint32_t core_id,
					uint32_t thread_id, int isa_mode, int bp_table_size,
					int report_traps, uint32_t init_pc);

//register all pipes
//used by the cpu module
void register_thread_pipes(ThreadState* thread_state);

//start a  thread
ThreadState* start_ajit_thread(ThreadState* s);

#endif
