#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "ajit_generic_sys_calls.h"
#include "core_portme.h"
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
			
	uint8_t core_id, thread_id;

	//
	// This is called from user mode, and invokes
	// a trap (ta 16) whose trap handler then reads the asr
	// in supervisor mode.
	//
	uint32_t cid = ajit_sys_read_asr (29);

	Arg* farg = (Arg*) arg;
	int mutex_ptr = (int) &mutex_var;
	acquire_mutex_using_swap(mutex_ptr);
	ee_printf("Run on CPU 0x%x, athread %d: __dispatch_fn (%d).\n", 
				cid, farg->thread_id, farg->COUNTER);
	farg->COUNTER += 1;
	release_mutex_using_swap(mutex_ptr);

}

void __enable_serial__()
{
	mutex_var = 0;

	// enable the serial device.
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE | RX_INTR_ENABLE );

	int mutex_ptr = (int) &mutex_var;
	acquire_mutex_using_swap(mutex_ptr);
	ee_printf("enabled serial, set mutex_var=%d.\n", mutex_var); 
	release_mutex_using_swap(mutex_ptr);

}

void runLoop(int tid)
{

	int mutex_ptr = (int) &mutex_var;
	acquire_mutex_using_swap(mutex_ptr);
	ee_printf("entered runLoop(%d).\n", tid); 
	release_mutex_using_swap(mutex_ptr);

	while(1)
	{
		void* arg = NULL;
		int thread_id = athreadSelectAndRunThread (&global_atm, 0, 0);
	
		if(thread_id > 0)
		{
			acquire_mutex_using_swap(mutex_ptr);
			ee_printf("Finished task on HW THREAD %d.\n", tid); 
			release_mutex_using_swap(mutex_ptr);
		}	

		if(thread_id > 0)
		{
			athreadDestroyThread(&global_atm, thread_id);

			while(1)
			{
				G_ARG.server_id = tid;
				G_ARG.thread_id = thread_id;

				int thread_id = athreadCreateThread(&global_atm, 0, 
						(void*) &printCounter, (void*) &G_ARG);
				if(thread_id > 0)
				{
					break;
				}
			}
		}
	}
}



void main_00 () 
{
	G_ARG.COUNTER = 0;
	G_ARG.server_id = 0;


	// initialize the ATHREAD manager.
	athreadManagerInit(&global_atm);

	// allocate and dispatch first thread using ATM.
	int thread_id = athreadCreateThread(&global_atm, 0, (void*) &printCounter, (void*) &G_ARG);

	// Run loop...
	runLoop(0);
}




void main_01 () 
{
	runLoop(1);
}

