//StartGPBThreads.c
//
//Routines to start the debug units as a thread,
//and register all pipes used.


#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "GDBtoAJITbridge.h"
#include "StartGPBThreads.h"



DEFINE_THREAD_WITH_ARG(gpb_core,vgpb);

int per_core_start_gpb_thread(uint32_t core_id,  uint32_t thread_id, int port_number)
{
	int ret_val = 0;
	if(port_number > 0)
	{
		gpbState* g = makeGpbState (core_id, thread_id, port_number);
		register_gpb_pipes(g);
		PTHREAD_DECL(gpb_core);
		PTHREAD_CREATE_WITH_ARG(gpb_core,((void*) g));
	}
	else
	{
		fprintf(stderr,"Error: per_thread_start_gpb_thread:  invalid port %d for GDB server (core,thread=%d,%d)\n", port_number, core_id, thread_id);
		ret_val = 1;
	}
	return(ret_val);
}

int start_gpb_threads(uint32_t number_of_cores, uint32_t number_of_threads_per_core, int *port_numbers)
{
	int ret_val = 0;
	int J;
	for(J = 0; J < number_of_cores*number_of_threads_per_core; J++)
	{
		if(port_numbers[J] > 0)
		{
			uint32_t C = J/number_of_threads_per_core;
			uint32_t T = J%number_of_threads_per_core;
			per_core_start_gpb_thread(C,T, port_numbers[J]);
		}
	}
	return(ret_val);
}

void register_gpb_pipes(gpbState* gpb)
{
	int depth = 4096;
	fprintf(stderr,"\nInfo: registering gpb-server pipes for core,thread=%d,%d\n", 
				gpb->core_id, gpb->thread_id);
	register_pipe(gpb->command_pipe,     depth, 32,	0);
	register_pipe(gpb->response_pipe,    depth, 32,	0);
}


