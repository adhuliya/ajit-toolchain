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


void* hwServerThread (void* vhs)
{
	hwServerState* hs = (hwServerState*) vhs;
	fprintf(stderr,"\nInfo: starting hw-server for cpu-id %d\n", hs->thread_id);

	// free-running.
	hwServer_core(hs);

	return(NULL);
}

void register_hw_server_pipes(hwServerState* hs)
{

	fprintf(stderr,"\nInfo: registering hw-server pipes for thread=%d, core=%d\n",
								 hs->thread_id, hs->core_id);
	register_pipe(hs->debug_command_pipe_name,    4096, 32,	0);
	register_pipe(hs->debug_response_pipe_name,   4096, 32,	0);
	register_pipe(hs->thread_to_hwserver_id_pipe_name,    1, 8,	0);
	register_pipe(hs->thread_to_hwserver_state_pipe_name,    1, 64,	0);
	register_pipe(hs->hwserver_to_thread_pipe_name,   1, 32,	0);
}

hwServerState* start_hw_server(uint32_t core_id, uint32_t thread_id)
{
	assert((thread_id >= 0) && (thread_id < 2));
	assert((core_id >= 0) && (core_id < 4));

	hwServerState* hs = makeHwServerState(core_id, thread_id);
	register_hw_server_pipes (hs);

	pthread_t hs_t;
	pthread_create(&hs_t, NULL, &hwServerThread, (void*) hs);

	return(hs);
}

