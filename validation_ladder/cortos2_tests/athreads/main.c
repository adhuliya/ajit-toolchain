#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "defs.h"
#include "athread.h"


volatile athreadManager volatile global_atm;

typedef struct __Arg {
	int thread_id;
	int server_id;
	int COUNTER;
} Arg;

volatile Arg volatile G_ARG;


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
	cortos_printf("Run on CPU 0x%x, athread %d: __dispatch_fn (%d).\n", 
				cid, farg->thread_id, farg->COUNTER);
	farg->COUNTER += 1;
}

void runLoop(int tid)
{

	uint8_t* cortos_lock_var = cortos_reserveLock(0);

	cortos_printf("entered runLoop(%d).\n", tid); 

	while(1)
	{
		void* arg = NULL;
		int thread_id = athreadSelectAndRunThread (&global_atm, 0, 0);
	
		if(thread_id > 0)
		{
			cortos_printf("Finished task on HW THREAD %d.\n", tid); 
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

