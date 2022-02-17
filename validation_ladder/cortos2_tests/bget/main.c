#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "defs.h"

// will be allocated by using bget.
uint32_t *global_storage_array = NULL;

//
// Each thread does a series of writes 
// to memory.
//
// Thread T writes to locations T, T+8, T+16, ....
//
// Then each thread reads backthe entire array..
//
// 
//
volatile int volatile init_done = 0;

volatile int volatile write_done[] = {0,0,0,0,0,0,0,0};
volatile int volatile done[] = {0,0,0,0,0,0,0,0};

volatile int volatile go_flag = 0;

void runMarch(int tid)
{
	
	cortos_printf("entered runMarch(%d).\n", tid); 
	while(!go_flag)
	{
	}

	cortos_printf("go runMarch(%d).\n", tid); 

	uint32_t I;
	for(I = tid; I < ORDER; I += 8)
	{
		// two writes... I should survive
		global_storage_array[I] = 0;
		global_storage_array[I] = I;
	}

	write_done[tid] = 1;
	
	// check if all writes done...
	while(1)
	{
		int all_writes_done = 1;
		for(I = 0; I < 8; I++)
		{
			if(write_done[I] == 0)
			{
				all_writes_done = 0;
				break;
			}
		}
		if(all_writes_done)
			break;
	}

	cortos_printf("runMarch(%d) after all writes.\n", tid); 


	for(I = 0; I < ORDER; I++)
	{
		uint32_t R = global_storage_array[I];
		if(R != I)
		{
			cortos_printf("Error: runMarch(%d) MEM[%d] = %d, expected %d.\n",
						tid, I, R, I);
		}
	}

	cortos_printf("runMarch(%d) completed.\n", tid);
	done[tid] = 1;
}



void main_00 () 
{
	global_storage_array = cortos_bget(ORDER*sizeof(uint32_t));

	go_flag = 1;
	runMarch(0);

	int I;

	while(1)
	{
		int all_done = 1;
		for(I = 0; I < 8; I++)
		{
			if(done[I] == 0)
			{
				all_done = 0;
				break;
			}
		}
		if(all_done)
			break;
	}

	for(I = 0; I < ORDER; I++)
	{
		cortos_printf("[%d] = 0x%x\n", I, global_storage_array[I]);
	}
}




void main_01 () 
{
	runMarch(1);
}

void main_10 () 
{
	runMarch(2);
}

void main_11 () 
{
	runMarch(3);
}

void main_20 () 
{
	runMarch(4);
}

void main_21 () 
{
	runMarch(5);
}

void main_30 () 
{
	runMarch(6);
}

void main_31 () 
{
	runMarch(7);
}

