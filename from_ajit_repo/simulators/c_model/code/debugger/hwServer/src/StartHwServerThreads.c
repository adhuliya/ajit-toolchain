//StartHwServerThreads.c
//
//Routines to start the debug units as a thread,
//and register all pipes used.


#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "hwServerStruct.h"
#include "hwServer.h"
#include "StartHwServerThreads.h"


void hwServer_0 (void* vhs)
{
	hwServerState* hs = (hwServerState*) vhs;
	fprintf(stderr,"\nInfo: starting hw-server for cpu-id %d\n", hs->cpu_id);
	hwServer_core(hs);
}

void hwServer_1 (void* vhs)
{
	hwServerState* hs = (hwServerState*) vhs;
	fprintf(stderr,"\nInfo: starting hw-server for cpu-id %d\n", hs->cpu_id);
	hwServer_core(hs);
}

void hwServer_2 (void* vhs)
{
	hwServerState* hs = (hwServerState*) vhs;
	fprintf(stderr,"\nInfo: starting hw-server for cpu-id %d\n", hs->cpu_id);
	hwServer_core(hs);
}

void hwServer_3 (void* vhs)
{
	hwServerState* hs = (hwServerState*) vhs;
	fprintf(stderr,"\nInfo: starting hw-server for cpu-id %d\n", hs->cpu_id);
	hwServer_core(hs);
}


DEFINE_THREAD_WITH_ARG(hwServer_0, hs_0);
DEFINE_THREAD_WITH_ARG(hwServer_1, hs_1);
DEFINE_THREAD_WITH_ARG(hwServer_2, hs_2);
DEFINE_THREAD_WITH_ARG(hwServer_3, hs_3);

void register_hw_server_pipes(hwServerState* hs)
{

	fprintf(stderr,"\nInfo: registering hw-server pipes for cpu-id %d\n", hs->cpu_id);
	register_pipe(hs->debug_command_pipe_name,    4096, 32,	0);
	register_pipe(hs->debug_response_pipe_name,   4096, 32,	0);
	register_pipe(hs->cpu_to_hwserver_id_pipe_name,    1, 8,	0);
	register_pipe(hs->cpu_to_hwserver_state_pipe_name,    1, 64,	0);
	register_pipe(hs->hwserver_to_cpu_pipe_name,   1, 32,	0);
}

hwServerState* start_hw_server(int cpu_id)
{
	
	assert((cpu_id >= 0) && (cpu_id < 4));
	hwServerState* hs = NULL;

	if(cpu_id == 0)
	{
		PTHREAD_DECL(hwServer_0);
		hwServerState* hs_0 = makeHwServerState(0);
		register_hw_server_pipes (hs_0);
		PTHREAD_CREATE_WITH_ARG(hwServer_0, ((void*) hs_0));
		hs = hs_0;
	}
	else if (cpu_id == 1)
	{
		PTHREAD_DECL(hwServer_1);
		hwServerState* hs_1 = makeHwServerState(1);
		register_hw_server_pipes (hs_1);
		PTHREAD_CREATE_WITH_ARG(hwServer_1, ((void*) hs_1));
		hs = hs_1;
	}
	else if (cpu_id == 2)
	{
		PTHREAD_DECL(hwServer_2);
		hwServerState* hs_2 = makeHwServerState(2);
		register_hw_server_pipes (hs_2);
		PTHREAD_CREATE_WITH_ARG(hwServer_2, ((void*) hs_2));
		hs = hs_2;
	}
	else if (cpu_id == 3)
	{
		PTHREAD_DECL(hwServer_3);
		hwServerState* hs_3 = makeHwServerState(3);
		register_hw_server_pipes (hs_3);
		PTHREAD_CREATE_WITH_ARG(hwServer_3, ((void*) hs_3));
		hs = hs_3;
	}

	return(hs);
}

