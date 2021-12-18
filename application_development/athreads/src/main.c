#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "dispatch.h"
#include "athread.h"

volatile int mutex_var;
static int COUNTER = 0;

athreadManager global_atm;

// set to 1 when thread 01 can be started.
volatile int start_thread_01 = 0;

void printCounter(int atid, int tid, void* arg)
{
			
	volatile int mutex_ptr = (int) &mutex_var;
	acquire_mutex_using_swap(mutex_ptr);
	ee_printf("CPU %d, athread %d: __dispatch_fn (%d).\n", tid, atid, *((int*) arg));
	COUNTER = *((int*) arg) + 1;
	release_mutex_using_swap(mutex_ptr);
}

void enable_serial()
{
	// enable the serial device.
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE | RX_INTR_ENABLE );
	ee_printf("enabled serial.\n"); 
}

void runLoop(int tid)
{
	void (*__dispatch_fn)(int, int,void*) = &printCounter;

	while(1)
	{
		void* arg;
		int thread_id = athreadGetThreadToRun (&global_atm,
								(void**) &__dispatch_fn, (void**) &arg);

		if(thread_id > 0)
		{
			// The actual computation..
			(*__dispatch_fn)(thread_id, tid,arg);

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

			athreadDispatchThread(&global_atm, thread_id,(void*) __dispatch_fn, 
										(void*) arg);

		}
	}
}



void main_00 () 
{
	void (*__dispatch_fn)(int, int,void*) = &printCounter;

	// initialize the ATHREAD manager.
	athreadInit(&global_atm);

	COUNTER = 0;

	// start 01
	start_thread_01 = 1;

	// allocate and dispatch first thread using ATM.
	int thread_id = athreadAllocateThread(&global_atm);
	if(thread_id > 0)
	{
		while(1)
		{
			int status = athreadDispatchThread(&global_atm, thread_id, 
						(void*) __dispatch_fn, (void*) &COUNTER);
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
	while(!start_thread_01)
	{
		//__ajit_sleep__ (64); // 64 clock cycles.
	}

	runLoop(1);
}

