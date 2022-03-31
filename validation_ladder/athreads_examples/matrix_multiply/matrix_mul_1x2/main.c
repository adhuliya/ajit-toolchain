#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "defs.h"
#include "athread.h"


volatile int volatile all_done = 0;

void Mat_mul_main();
double array_A[ORDER][ORDER];
double array_B[ORDER][ORDER];
double array_P[ORDER][ORDER];
athreadManager global_atm;

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
			//cortos_printf("runLoop(%d) finished thread %d.\n", tid, thread_id); 
			athreadDestroyThread(&global_atm, thread_id);
		}

		if(all_done)
			break;
	}
}
void initMatrices(int S, int F)
{
        int I, J;
        for(I = S; I <= F; I++)
        {
                for(J = 0; J < ORDER; J++)
                {
                        array_A[I][J] = 1;
                        array_B[I][J] = 1;
                        array_P[I][J] = 0;
                }
       }
}



void main_00 () 
{
	athreadManagerInit(&global_atm);
	uint64_t t0 = cortos_get_clock_time();
	initMatrices(0,ORDER);	
	Mat_mul_main();
	uint64_t t1 = cortos_get_clock_time();
	uint32_t t00 = t0 & (0xffffffff);
	uint32_t t01 = t1 & (0xffffffff);
	double t = ((double) (t1- t0)) * 1.0e-8;
	cortos_printf ("Time taken by Mat_mul main = %f \n", t);

/*	int I,J;
	for(I = 0; I < ORDER; I+=2)
        {
                for(J = 0; J < ORDER; J++)
                {
                        if(array_P[I][J] != ORDER)
                                cortos_printf("Error: P[%d][%d]=%d   expected %d\n", I, J, array_P[I][J], ORDER);
                }
        }
*/	


	all_done = 1;
}

void main_01 () 
	
{
	runLoop(1);
}
