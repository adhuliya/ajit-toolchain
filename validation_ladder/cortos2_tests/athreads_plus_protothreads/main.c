#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "defs.h"
#include "athread.h"
#include "pt.h"

int global_cortos_lock_var;
volatile athreadManager volatile global_atm;

typedef struct __Arg {
	int arg_id;
	int thread_id;
	int server_id;
	int COUNTER;
	int STEP;
	int yields;

	struct pt __pt;
} Arg;

Arg G0_ARG;
Arg G1_ARG;
Arg G2_ARG;


//
// Ideally this should be static so that when we resume from
// after a yield, the state of the function is preserved exactly
//
// But in this case, this is not required, because of the
// fact that the state of the thread at resumption is
// saved in arg.
//
PT_THREAD(printCounter(void* arg))
{
	Arg* farg = (Arg*) arg;
	cortos_printf("Entered printCounter (arg_id=%d)\n", farg->arg_id);

  	PT_BEGIN(&(farg->__pt));

	// if lock is not available, yield.
	while(1)
	{
		int la = cortos_lock_acquire(global_cortos_lock_var);
		if (la > 0)
			break;
		else
		{
			farg->yields += 1;
			PT_YIELD(&(farg->__pt));
		}
	}

	uint8_t core_id, thread_id;
	//
	// This is called from user mode, and invokes
	// a trap (ta 16) whose trap handler then reads the asr
	// in supervisor mode.
	//
	uint32_t cid = ajit_sys_read_asr (29);


	cortos_printf("Run on CPU 0x%x, athread %d, arg_id=%d, yields=%d: __dispatch_fn (%d).\n", 
				cid, farg->thread_id, farg->arg_id, farg->yields, farg->COUNTER);
	farg->COUNTER += farg->STEP;
	cortos_lock_release(global_cortos_lock_var);

	PT_END(&(farg->__pt));
}


void runLoop(int tid)
{

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
			void* fn;
			void* arg;
			athreadThreadGetArgs(&global_atm, thread_id, &fn, &arg);
			Arg* garg = (Arg*) arg;

			int return_value;
			athreadThreadGetReturnValue(&global_atm, thread_id, &return_value);
			if(return_value == PT_YIELDED)
			{
				cortos_printf("Yielded printCounter (arg_id=%d) on HW THREAD %d\n", 
							garg->arg_id, tid);
			}


			// deallocate it...
			athreadDestroyThread(&global_atm, thread_id);

			while(1)
			// restart it..
			{
				garg->server_id = tid;
				garg->thread_id = thread_id;

				int thread_id = athreadCreateThread(&global_atm, 0, 
							(void*) &printCounter, (void*) garg);
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
	global_cortos_lock_var = cortos_reserveLockVar();

	G0_ARG.arg_id  = 0;
	G0_ARG.COUNTER = 0;
	G0_ARG.STEP = 3;
	G0_ARG.server_id = 0;
	G0_ARG.yields = 0;
	PT_INIT(&(G0_ARG.__pt));

	G1_ARG.arg_id  = 1;
	G1_ARG.COUNTER = 1;
	G1_ARG.STEP = 3;
	G1_ARG.server_id = 0;
	G1_ARG.yields = 0;
	PT_INIT(&(G1_ARG.__pt));

	G2_ARG.arg_id  = 2;
	G2_ARG.COUNTER = 2;
	G2_ARG.STEP = 3;
	G2_ARG.server_id = 0;
	G2_ARG.yields = 0;
	PT_INIT(&(G2_ARG.__pt));

	// initialize the ATHREAD manager.
	athreadManagerInit(&global_atm);

	// allocate and dispatch two thread using ATM.
	int thread_id = athreadCreateThread(&global_atm, 0, (void*) &printCounter, (void*) &G0_ARG);
	thread_id = athreadCreateThread(&global_atm, 0, (void*) &printCounter, (void*) &G1_ARG);
	thread_id = athreadCreateThread(&global_atm, 0, (void*) &printCounter, (void*) &G2_ARG);

	// Run loop...
	runLoop(0);
}




void main_01 () 
{
	runLoop(1);
}

