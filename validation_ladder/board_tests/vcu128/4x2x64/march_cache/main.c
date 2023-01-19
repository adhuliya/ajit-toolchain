#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "defs.h"
#include "thread_channel.h"

uint32_t global_storage_matrix[ORDER][ORDER];

/*
 *
 *	global_storage_matrix[16][16]
 *
 * 		0	1	2	3	4	5	6	7||	8	9	10	11	12	13	14	15
 *core0	0								 ||	
 *	1                 Thread0                                        ||           Thread1
 * 	2								 ||
 * 	3								 ||
 * 	--------------------------------------------------------------------------------------------------------------------------------------
 *core1	4								 ||
 *	5                 Thread0                                        ||           Thread1
 * 	6                                                                ||
 * 	7                                                                ||
 * 	======================================================================================================================================
 *core2 8                                                                ||
 * 	9                 Thread0                                        ||           Thread1
 * 	10                                                               ||
 * 	11                                                               ||
 * 	--------------------------------------------------------------------------------------------------------------------------------------
 *core3	12                                                               ||
 * 	13                Thread0                                        ||           Thread1
 * 	14                                                               ||
 * 	15                                                               ||
 *
 *
 *
 * */
typedef struct argstruct__ {
        int thid;
} argstruct;

ThreadChannel tc0;
ThreadChannel tc1;
ThreadChannel tc2;
ThreadChannel tc3;

volatile int volatile init_done = 0;

volatile int volatile done[] = {0,0,0,0,0,0,0,0};

volatile int volatile go_flag = 0;

volatile int volatile count[] = {0,0,0,0,0,0,0,0};

volatile double volatile  time[] = {0,0,0,0};

void runMarch(int tid)
{
	
	/*while(!go_flag)
	{
	}*/
 

	uint32_t I,J;
	uint32_t start = (( tid & 0x6)*(ORDER/8)); 
	for(I = start; I < (start+(ORDER/4)); I += 1)
	{
		for(J = ((tid&0x1)*(ORDER/2)) ; J < (tid&0x1)*(ORDER/2)+(ORDER/2); J += 1)
		{
			// two writes
			global_storage_matrix[I][J] = 0;
			global_storage_matrix[I][J] = I+J;
		}
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

	//-->  MEASURE THIS TIME
        runMarch(0);
	//<--  MEASURE THIS TIME

        while(getChannelResponse(&tc0, (void**) &rarg0))
        {
        }

	uint64_t t01 = cortos_get_clock_time();
        time[0] = (double)(t01-t00) * 1.0e-8; 
        //cortos_printf("time taken for core 0 is = %lf \n", time0);


	int I,J;

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
	
	// print time required for each core.
	for(I = 0; I < 4; I++)
	{
		
        	cortos_printf("time taken for core %d is = %lf \n",I, time[I]);
	}
	
	for(I = 0; I < ORDER; I++)
        {
		for(J = 0; J < ORDER; J++)
		{
	                uint32_t R = global_storage_matrix[I][J];
        	        if(R != (I+J))
                	{
                        	cortos_printf("Error: runMarch MEM[%d][%d] = %d, expected %d.\n", I, J, R, (I+J));
	                }	
		}
	}
	/*for(I = 0; I < ORDER; I++)
	{
		for(J = 0; J < ORDER; J++)
		{
			cortos_printf("M[%d][%d] = 0x%4x\t", I,J, global_storage_matrix[I][J]);
		}
		cortos_printf("\n");
	}*/

}

void main_01 ()
{
        void (*__fn) (void*);

        void *__arg;
        while(getChannelJob(&tc0, (void**) &__fn, (void**) &__arg))
        {
        }

	//-->  MEASURE THIS TIME
        (*__fn)(__arg);
	//<--  MEASURE THIS TIME

        tc0.status = CH_COMPLETED;
}

void main_10 () 
{
	// wait till go flag
	while(!go_flag)
	{
	}

	uint64_t t10 = cortos_get_clock_time();
	argstruct sarg1;
        sarg1.thid = 3;
        argstruct* rarg1;
	scheduleChannelJob(&tc1, (void*) &callfn, (void*) &sarg1);

	//-->  MEASURE THIS TIME
	runMarch(2);
	//<--  MEASURE THIS TIME

	while(getChannelResponse(&tc1, (void**) &rarg1))
        {
        }
	uint64_t t11 = cortos_get_clock_time();
	time[1] = (double)(t11-t10) * 1.0e-8;
	//cortos_printf("time taken for core 1 is = %lf \n", time1);
}

void main_11 ()
{
        void (*__fn) (void*);

        void *__arg;
        while(getChannelJob(&tc1, (void**) &__fn, (void**) &__arg))
        {
        }

	//-->  MEASURE THIS TIME
        (*__fn)(__arg);
	//<--  MEASURE THIS TIME

        tc1.status = CH_COMPLETED;
}

void main_20 () 
{
	// wait till go flag
	while(!go_flag)
	{
	}
	uint64_t t20 = cortos_get_clock_time();
	argstruct sarg2;
        sarg2.thid = 5;
        argstruct* rarg2;
        scheduleChannelJob(&tc2, (void*) &callfn, (void*) &sarg2);

	//-->  MEASURE THIS TIME
        runMarch(4);
	//<--  MEASURE THIS TIME

        while(getChannelResponse(&tc2, (void**) &rarg2))
        {
        }

	uint64_t t21 = cortos_get_clock_time();
        time[2] = (double)(t21-t20) * 1.0e-8;
        //cortos_printf("time taken for core 2 is = %lf \n", time2);

}

void main_21 ()
{
        void (*__fn) (void*);

        void *__arg;
        while(getChannelJob(&tc2, (void**) &__fn, (void**) &__arg))
        {
        }

	//-->  MEASURE THIS TIME
        (*__fn)(__arg);
	//<--  MEASURE THIS TIME

        tc2.status = CH_COMPLETED;
}


void main_30 () 
{
	// wait till go flag
	while(!go_flag)
	{
	}

	uint64_t t30 = cortos_get_clock_time();
	argstruct sarg3;
        sarg3.thid = 7;
        argstruct* rarg3;
        scheduleChannelJob(&tc3, (void*) &callfn, (void*) &sarg3);

	//-->  MEASURE THIS TIME
        runMarch(6);
	//<--  MEASURE THIS TIME

        while(getChannelResponse(&tc3, (void**) &rarg3))
        {
        }
	uint64_t t31 = cortos_get_clock_time();
        time[3] = (double)(t31-t30) * 1.0e-8;
        //cortos_printf("time taken for core 3 is = %lf \n", time3);

}

void main_31 ()
{
        void (*__fn) (void*);

        void *__arg;
        while(getChannelJob(&tc3, (void**) &__fn, (void**) &__arg))
        {
        }

	//-->  MEASURE THIS TIME
        (*__fn)(__arg);
	//<--  MEASURE THIS TIME


        tc3.status = CH_COMPLETED;
}

