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
#include "StartGPBThreads.h"

void gpb();
void setPortNumber(int);
DEFINE_THREAD(gpb);
PTHREAD_DECL(gpb);

void start_gpb_threads(int port_number)
{
	setPortNumber(port_number);
	PTHREAD_CREATE(gpb);
}

void stop_gpb_threads()
{
    	PTHREAD_CANCEL(gpb);
}

