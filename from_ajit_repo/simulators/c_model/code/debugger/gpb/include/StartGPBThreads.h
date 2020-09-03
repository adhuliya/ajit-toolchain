//StartGPBThreads.h
//
//Routines to start the debug units as a thread,
//and register all pipes used.

#ifndef _START_GPB_THREADS_H_
#define _START_GPB_THREADS_H_
#include "GDBtoAJITbridge.h"


//start debug threads
//  number of port numbers specified in the array should
//  equal the number of cpus.
//
// return 0 on success.
int start_gpb_threads(int number_of_cpus, int *port_numbers);

// start gpb thread for single cpu.
int per_core_start_gpb_thread(int cpu_id, int port_number);

//stop debug threads
void stop_gpb_threads(int number_of_cpus);

// stop gpb thread for single CPU.
void per_core_stop_gpb_thread(int cpu_id);

void register_gpb_pipes(gpbState* gpb);

#endif
