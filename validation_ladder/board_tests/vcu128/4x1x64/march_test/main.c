#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "defs.h"

uint32_t global_storage_array[ORDER];
uint32_t LA[8][ORDER];

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

volatile int volatile done[] = {0,0,0,0};

volatile int volatile go_flag = 0;

void runMarch(int tid)
{
	
 
	while(!go_flag)
	{
	}

	uint32_t I;
	for(I = tid; I < ORDER; I += 4)
	{
		// two writes
		global_storage_array[I] = 0;
		global_storage_array[I] = I;
	}

	done[tid] = 1;
}



void main_00 () 
{
	go_flag = 1;
	uint64_t t00 = cortos_get_clock_time();
	runMarch(0);
	uint64_t t01 = cortos_get_clock_time();
        double time0 = (double)(t01-t00) * 1.0e-8; 
        cortos_printf("time taken for core 0 is = %lf \n", time0);


	int I;

	while(1)
	{
		int all_done = 1;
		for(I = 0; I < 4; I++)
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
                uint32_t R = global_storage_array[I];
                if(R != I)
                {
                        cortos_printf("Error: runMarch MEM[%d] = %d, expected %d.\n", I, R, I);
                }
	}
	for(I = 0; I < ORDER; I++)
	{
		cortos_printf("[%d] = 0x%x\n", I, global_storage_array[I]);
	}
}





void main_10 () 
{
	uint64_t t10 = cortos_get_clock_time();
	runMarch(1);
	uint64_t t11 = cortos_get_clock_time();
	double time1 = (double)(t11-t10) * 1.0e-8;
	cortos_printf("time taken for core 1 is = %lf \n", time1);
}


void main_20 () 
{
	uint64_t t20 = cortos_get_clock_time();
	runMarch(2);
	uint64_t t21 = cortos_get_clock_time();
        double time2 = (double)(t21-t20) * 1.0e-8;
        cortos_printf("time taken for core 2 is = %lf \n", time2);

}


void main_30 () 
{
	uint64_t t30 = cortos_get_clock_time();
	runMarch(3);
	uint64_t t31 = cortos_get_clock_time();
        double time3 = (double)(t31-t30) * 1.0e-8;
        cortos_printf("time taken for core 3 is = %lf \n", time3);

}
