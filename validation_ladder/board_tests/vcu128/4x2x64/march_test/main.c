#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "defs.h"
#include "thread_channel.h"

uint32_t global_storage_array[ORDER];
uint32_t LA[8][ORDER];
typedef struct argstruct__ {
        int thid;
} argstruct;

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
ThreadChannel tc0;
ThreadChannel tc1;
ThreadChannel tc2;
ThreadChannel tc3;
volatile int volatile init_done = 0;

volatile int volatile done[] = {0,0,0,0,0,0,0,0};

volatile int volatile go_flag = 0;

void runMarch(int tid)
{
	
 
	while(!go_flag)
	{
	}

	uint32_t I;
	for(I = tid; I < ORDER; I += 8)
	{
		// two writes
		global_storage_array[I] = 0;
		global_storage_array[I] = I;
	}

	

	done[tid] = 1;
}


int callfn (void* varg)
{
        argstruct* arg = (argstruct*) varg;
        runMarch (arg->thid);
}

void main_00 () 
{
	initChannel(&tc0, 1);
	initChannel(&tc1, 1);
	initChannel(&tc2, 1);
	initChannel(&tc3, 1);

	go_flag = 1;
	uint64_t t00 = cortos_get_clock_time();
	argstruct sarg0;
        sarg0.thid = 1;
        argstruct* rarg0;
        scheduleChannelJob(&tc0, (void*) &callfn, (void*) &sarg0);
        runMarch(0);
        while(getChannelResponse(&tc0, (void**) &rarg0))
        {
        }

	uint64_t t01 = cortos_get_clock_time();
        double time0 = (double)(t01-t00) * 1.0e-8; 
        cortos_printf("time taken for core 0 is = %lf \n", time0);


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






void main_01 ()
{
        void (*__fn) (void*);

        void *__arg;
        while(getChannelJob(&tc0, (void**) &__fn, (void**) &__arg))
        {
        }

        (*__fn)(__arg);
        tc0.status = CH_COMPLETED;
}

void main_10 () 
{
	uint64_t t10 = cortos_get_clock_time();
	argstruct sarg1;
        sarg1.thid = 3;
        argstruct* rarg1;
	scheduleChannelJob(&tc1, (void*) &callfn, (void*) &sarg1);
	runMarch(2);
	while(getChannelResponse(&tc1, (void**) &rarg1))
        {
        }
	uint64_t t11 = cortos_get_clock_time();
	double time1 = (double)(t11-t10) * 1.0e-8;
	cortos_printf("time taken for core 1 is = %lf \n", time1);
}

void main_11 ()
{
        void (*__fn) (void*);

        void *__arg;
        while(getChannelJob(&tc1, (void**) &__fn, (void**) &__arg))
        {
        }

        (*__fn)(__arg);
        tc1.status = CH_COMPLETED;
}

void main_20 () 
{
	uint64_t t20 = cortos_get_clock_time();
	argstruct sarg2;
        sarg2.thid = 5;
        argstruct* rarg2;
        scheduleChannelJob(&tc2, (void*) &callfn, (void*) &sarg2);
        runMarch(4);
        while(getChannelResponse(&tc2, (void**) &rarg2))
        {
        }

	uint64_t t21 = cortos_get_clock_time();
        double time2 = (double)(t21-t20) * 1.0e-8;
        cortos_printf("time taken for core 2 is = %lf \n", time2);

}

void main_21 ()
{
        void (*__fn) (void*);

        void *__arg;
        while(getChannelJob(&tc2, (void**) &__fn, (void**) &__arg))
        {
        }

        (*__fn)(__arg);
        tc2.status = CH_COMPLETED;
}


void main_30 () 
{
	uint64_t t30 = cortos_get_clock_time();
	argstruct sarg3;
        sarg3.thid = 7;
        argstruct* rarg3;
        scheduleChannelJob(&tc3, (void*) &callfn, (void*) &sarg3);
        runMarch(6);
        while(getChannelResponse(&tc3, (void**) &rarg3))
        {
        }
	uint64_t t31 = cortos_get_clock_time();
        double time3 = (double)(t31-t30) * 1.0e-8;
        cortos_printf("time taken for core 3 is = %lf \n", time3);

}

void main_31 ()
{
        void (*__fn) (void*);

        void *__arg;
        while(getChannelJob(&tc3, (void**) &__fn, (void**) &__arg))
        {
        }

        (*__fn)(__arg);
        tc3.status = CH_COMPLETED;
}

