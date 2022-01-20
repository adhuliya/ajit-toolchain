#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "dispatch.h"
#include "athread.h"

extern int mutex_var;
volatile athreadManager volatile global_atm;

typedef struct __Arg {
	int thread_id;
	int server_id;
	int COUNTER;
} Arg;
Arg G_ARG;


void printCounter(void* arg)
{
			
	int mutex_ptr = (int) &mutex_var;
	acquire_mutex_using_swap(mutex_ptr);

	Arg* farg = (Arg*) arg;

	ee_printf("CPU %d, athread %d: __dispatch_fn (%d).\n", farg->server_id, farg->thread_id, farg->COUNTER);
	farg->COUNTER += 1;

	release_mutex_using_swap(mutex_ptr);
}

void __enable_serial__()
{
	mutex_var = 0;

	// enable the serial device.
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE | RX_INTR_ENABLE );
	ee_printf("enabled serial, set mutex_var=%d.\n", mutex_var); 
}

void runLoop(int tid)
{
	void (*__dispatch_fn)(void*) = NULL;

	ee_printf("entered runLoop(%d).\n", tid); 
	while(1)
	{
		void* arg = NULL;
		int thread_id = athreadGetThreadToRun (&global_atm,
								(void**) &__dispatch_fn, (void**) &arg);

		if(thread_id > 0)
		{
			((Arg*) arg)->server_id = tid;

			// The actual computation..
			(*__dispatch_fn)(arg);

			// Closure of the thread.
			athreadReturn(&global_atm, thread_id);
			athreadDeallocateThread (&global_atm, thread_id);
			
			// allocate and dispatch new thread.
			while(1)
			{
				thread_id = athreadAllocateThread(&global_atm);
				if(thread_id > 0)
				{
					break;
				}
			}

			((Arg*) arg)->thread_id = thread_id;
			athreadDispatchThread(&global_atm, thread_id,(void*) __dispatch_fn, 
										(void*) arg);

		}
	}
}



void main_00 () 
{


	void (*__dispatch_fn)(void*) = NULL;
	G_ARG.COUNTER = 0;

	mutex_var = 0;
	ee_printf("entered main_00, set mutex=%d\n", mutex_var);

	// initialize the ATHREAD manager.
	athreadInit(&global_atm);


	// allocate and dispatch first thread using ATM.
	int thread_id = athreadAllocateThread(&global_atm);
	if(thread_id > 0)
	{
		G_ARG.thread_id = thread_id;
		while(1)
		{
			int status = athreadDispatchThread(&global_atm, thread_id, 
						(void*) &printCounter, (void*) &G_ARG);
			if(status)
				ee_printf("Error: main_00 could not dispatch thread.\n");
			else
				break;
		}
	}

	// Run loop...
	runLoop(0);
}




void main_01 () 
{
	runLoop(1);
}

