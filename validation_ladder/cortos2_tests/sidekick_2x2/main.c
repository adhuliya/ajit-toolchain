#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "defs.h"
#include "athread.h"


volatile int volatile init_done = 0;
volatile int volatile all_done = 0;

void sortParallel();
uint32_t array_to_be_sorted[ORDER];
volatile athreadManager volatile global_atm;

void runLoop(int tid)
{

#ifdef DEBUG_MODE
	cortos_printf("entered runLoop(%d).\n", tid); 
#endif

	while(1)
	{
		void* arg = NULL;
		int thread_id = athreadSelectAndRunThread (&global_atm, 0, 0);


		if(thread_id > 0)
		{
#ifdef DEBUG_MODE
			cortos_printf("runLoop(%d) finished thread %d.\n", tid, thread_id); 
#endif

			athreadDestroyThread(&global_atm, thread_id);
		}

		if(all_done)
			break;
	}
}



void main_00 () 
{
	athreadManagerInit(&global_atm);
	init_done = 1;

	int I;
	for(I = 0; I < ORDER; I++)
	{
		array_to_be_sorted[I] = (ORDER - I);	
	}

	sortParallel();

	for(I = 0; I < ORDER; I++)
	{
		cortos_printf("result: %d.\n", array_to_be_sorted[I]);
	}

	all_done = 1;
}




void main_01 () 
{
	while (!init_done);
	runLoop(1);
}

void main_10 () 
{
	while (!init_done);
	runLoop(2);
}

void main_11 () 
{
	while (!init_done);
	runLoop(3);
}
