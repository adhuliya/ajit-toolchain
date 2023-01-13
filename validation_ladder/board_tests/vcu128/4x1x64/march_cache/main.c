#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "defs.h"

uint32_t global_storage_matrix[ORDER][ORDER];

/*
 *
 *	global_storage_matrix[16][16]
 *
 * 		0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15
 *	0								 	
 *	1                 			CORE 0
 * 	2								 
 * 	3								 
 * 	--------------------------------------------------------------------------------------------------------------------------------------
 *	4								 
 *	5                 			CORE 1
 * 	6                                                                
 * 	7                                                                
 * 	======================================================================================================================================
 *	 8                                                                
 * 	9                 			CORE 2
 * 	10                                                               
 * 	11                                                               
 * 	--------------------------------------------------------------------------------------------------------------------------------------
 *	12                                                               
 * 	13                			CORE3
 * 	14                                                               
 * 	15                                                               
 *
 *
 */

volatile int volatile init_done = 0;

volatile int volatile done[] = {0,0,0,0};

volatile int volatile go_flag = 0;

void runMarch(int tid)
{
	
 

	uint32_t I,J;
	uint32_t start = ((tid&0x3)*(ORDER/4)); 
	for(I = start; I < (start+(ORDER/4)); I += 1)
	{
		// TODO
		for(J = 0 ; J < ORDER; J += 1)
		{
			// two writes
			global_storage_matrix[I][J] = 0;
			global_storage_matrix[I][J] = I+J;
			//cortos_printf("written MAT[%d][%d] = %d\n",I,J,I+J);
		}
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


	int I,J;

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
		for(J = 0; J < ORDER; J++)
		{
	                uint32_t R = global_storage_matrix[I][J];
        	        if(R != (I+J))
                	{
                        	cortos_printf("Error: runMarch MEM[%d][%d] = %d, expected %d.\n", I, J, R, (I+J));
	                }	
		}
	}
	for(I = 0; I < ORDER; I++)
	{
		for(J = 0; J < ORDER; J++)
		{
			cortos_printf("M[%d][%d] = %d\t", I,J, global_storage_matrix[I][J]);
		}
		cortos_printf("\n");
	}
}





void main_10 () 
{
	while(!go_flag)
	{
	}
	uint64_t t10 = cortos_get_clock_time();
	runMarch(1);
	uint64_t t11 = cortos_get_clock_time();
	double time1 = (double)(t11-t10) * 1.0e-8;
	cortos_printf("time taken for core 1 is = %lf \n", time1);
}


void main_20 () 
{
	while(!go_flag)
	{
	}
	uint64_t t20 = cortos_get_clock_time();
	runMarch(2);
	uint64_t t21 = cortos_get_clock_time();
        double time2 = (double)(t21-t20) * 1.0e-8;
        cortos_printf("time taken for core 2 is = %lf \n", time2);

}


void main_30 () 
{
	while(!go_flag)
	{
	}
	uint64_t t30 = cortos_get_clock_time();
	runMarch(3);
	uint64_t t31 = cortos_get_clock_time();
        double time3 = (double)(t31-t30) * 1.0e-8;
        cortos_printf("time taken for core 3 is = %lf \n", time3);

}
