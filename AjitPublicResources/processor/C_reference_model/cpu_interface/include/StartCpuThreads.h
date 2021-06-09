//StartCpuThreads.h
//
//Routines to start the cpu as a thread,
//and register all pipes used.

#ifndef _START_CPU_THREADS_H_
#define _START_CPU_THREADS_H_

//register all pipes
//used by the cpu module
void register_cpu_pipes();
//start cpu threads
void start_cpu_threads();
#endif
