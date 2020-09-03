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



void gpb_0(void* vgpb)
{
	gpb_core(vgpb);
}

void gpb_1(void* vgpb)
{
	gpb_core(vgpb);
}

void gpb_2(void* vgpb)
{
	gpb_core(vgpb);
}

void gpb_3(void* vgpb)
{
	gpb_core(vgpb);
}

DEFINE_THREAD_WITH_ARG(gpb_0,vgpb);
DEFINE_THREAD_WITH_ARG(gpb_1,vgpb);
DEFINE_THREAD_WITH_ARG(gpb_2,vgpb);
DEFINE_THREAD_WITH_ARG(gpb_3,vgpb);

PTHREAD_DECL(gpb_0);
PTHREAD_DECL(gpb_1);
PTHREAD_DECL(gpb_2);
PTHREAD_DECL(gpb_3);

int per_core_start_gpb_thread(int cpu_id, int port_number)
{
	int ret_val = 0;
	if(port_number > 0)
	{
		gpbState* g = makeGpbState (cpu_id, port_number);
		register_gpb_pipes(g);

		switch(cpu_id) {
			case 0: PTHREAD_CREATE_WITH_ARG(gpb_0,((void*) g));
				break;
			case 1: PTHREAD_CREATE_WITH_ARG(gpb_1,((void*) g));
				break;
			case 2: PTHREAD_CREATE_WITH_ARG(gpb_2,((void*) g));
				break;
			case 3: PTHREAD_CREATE_WITH_ARG(gpb_3,((void*) g));
				break;
			default:
				fprintf(stderr,"Error: per_core_start_gpb_thread:  invalid cpu-id %d\n", cpu_id);
				break;
		}
	}
	else
	{
		fprintf(stderr,"Error: per_core_start_gpb_thread:  invalid port %d for GDB server (core %d)\n", port_number, cpu_id);
		ret_val = 1;
	}
	return(ret_val);
}

int start_gpb_threads(int number_of_cpus, int *port_numbers)
{
	int ret_val = 0;
	if(port_numbers[0] > 0)
	{
		gpbState* g0 = makeGpbState (0, port_numbers[0]);
		register_gpb_pipes(g0);

		PTHREAD_CREATE_WITH_ARG(gpb_0,((void*) g0));
	}
	else
	{
		fprintf(stderr,"Error: illegal port number (%d) for Gdb remote for CPU 0\n",
				port_numbers[0]);
		ret_val = 1;
	}

	if(number_of_cpus > 1) 
	{
		if(port_numbers[1] > 0)
		{
			gpbState* g1 = makeGpbState (1, port_numbers[1]);
			register_gpb_pipes(g1);

			PTHREAD_CREATE_WITH_ARG(gpb_1,((void*) g1));
		}
		else
		{
			fprintf(stderr,"Error: illegal port number (%d) for Gdb remote for CPU 1\n",
					port_numbers[1]);
			ret_val = 1;
		}
	}
	if(number_of_cpus > 2)
	{
		if(port_numbers[2] > 0)
		{
			gpbState* g2 = makeGpbState (2, port_numbers[2]);
			register_gpb_pipes(g2);

			PTHREAD_CREATE_WITH_ARG(gpb_2,((void*) g2));
		}
		else
		{
			fprintf(stderr,"Error: illegal port number (%d) for Gdb remote for CPU 2\n",
					port_numbers[2]);
			ret_val = 1;
		}
	}
	if(number_of_cpus > 3) 
	{
		if (port_numbers[3] > 0)
		{
			gpbState* g3 = makeGpbState (3, port_numbers[3]);
			register_gpb_pipes(g3);

			PTHREAD_CREATE_WITH_ARG(gpb_3,((void*) g3));
		}
		else
		{
			fprintf(stderr,"Error: illegal port number (%d) for Gdb remote for CPU 3\n",
					port_numbers[3]);
			ret_val = 1;
		}
	}
	return(ret_val);
}

void stop_gpb_threads(int number_of_cpus)
{
	PTHREAD_CANCEL(gpb_0);
	if(number_of_cpus > 1)
		PTHREAD_CANCEL(gpb_1);
	if(number_of_cpus > 2)
		PTHREAD_CANCEL(gpb_2);
	if(number_of_cpus > 3)
		PTHREAD_CANCEL(gpb_3);
}

void per_core_stop_gpb_thread(int cpu_id)
{
	switch(cpu_id) {
		case 0: PTHREAD_CANCEL(gpb_0);
			break;
		case 1: PTHREAD_CANCEL(gpb_1);
			break;
		case 2: PTHREAD_CANCEL(gpb_2);
			break;
		case 3: PTHREAD_CANCEL(gpb_3);
			break;
		default:
			fprintf(stderr,"Error: per_core_stop_gpb_thread:  invalid cpu-id %d\n", cpu_id);
			break;
	}
}

void register_gpb_pipes(gpbState* gpb)
{
	int depth = 4096;
	fprintf(stderr,"\nInfo: registering gpb-server pipes for cpu-id %d\n", gpb->cpu_id);
	register_pipe(gpb->command_pipe,     depth, 32,	0);
	register_pipe(gpb->response_pipe,    depth, 32,	0);
}


