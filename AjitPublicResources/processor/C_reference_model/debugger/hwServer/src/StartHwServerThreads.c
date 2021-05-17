//StartHwServerThreads.c
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
#include "StartHwServerThreads.h"


void hwServer();
DEFINE_THREAD(hwServer);

void register_debug_pipes()
{

	int depth = 2;
	register_pipe("ENV_to_AJIT_debug_command",    depth, 32,	0);
	register_pipe("AJIT_to_ENV_debug_response",    depth, 32,	0);
	register_pipe("CPU_to_HWSERVER_id",    depth, 8,	0);
	register_pipe("CPU_to_HWSERVER_state",    depth, 64,	0);
	register_pipe("HWSERVER_to_CPU",    depth, 32,	0);

}

void start_debug_threads()
{
	PTHREAD_DECL(hwServer);

	register_debug_pipes();
	
	PTHREAD_CREATE(hwServer);

}

