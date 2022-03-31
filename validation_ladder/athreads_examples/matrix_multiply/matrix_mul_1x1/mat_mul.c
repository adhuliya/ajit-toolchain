#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "defs.h"
#include "athread.h"

extern uint32_t array_A[ORDER][ORDER];
extern uint32_t array_B[ORDER][ORDER];
extern uint32_t array_P[ORDER][ORDER];
extern athreadManager global_atm;

typedef struct __SortArg {

	uint32_t  thread_id;
	uint32_t* ptrA;
	uint32_t* ptrB;
	uint32_t* ptrP;
	uint32_t  start_Arr;

} SortArg;

int all_threads_completed(int* tptr, int NJ)
{
	int ret_val = 1;
	int I;
	for(I = 0; I < NJ; I++)
	{
		uint32_t ts = athreadThreadStatus(&global_atm, tptr[I]);	
		if ((ts != THREAD_UNALLOCATED) && (ts != THREAD_COMPLETED))
		{
			ret_val = 0;
		}
	}
	return(ret_val);
}

void Mat_mul(void* arg)
{	//cortos_printf("Entered Mat_mul\n");
	SortArg* sarg = (SortArg*) arg;
	int I, J, K;
	int N = ORDER/NJOBS;
	for(I = (sarg->start_Arr); I < ORDER; I +=NJOBS)
	//for(I = 0; I < (ORDER/NJOBS); I ++)
	
	{
                for (J = 0; J < ORDER; J++)
                {	
                        int r = 0;
                        for (K = 0; K < ORDER; K++)
                        {
                                r += sarg->ptrA[(I*ORDER)+K ] * sarg->ptrB[(K*ORDER) + J];
				//cortos_printf("Adding r\n");
                        }
                        sarg->ptrP[(I*ORDER)+J] = r;
                       // cortos_printf("P[%d][%d]=%d \n",I,J,sarg->ptrP[(I*ORDER)+J]);
                }
        }
}

void Mat_mul_main()
{
	SortArg args[NJOBS];
	int     threads[NJOBS];
	int I;

	uint32_t* ptrA = array_A;
	uint32_t* ptrB = array_B;
	uint32_t* ptrP = array_P;
	for(I = 0; I < NJOBS; I++)
	{
		args[I].start_Arr = I;
		args[I].ptrA  = ptrA;
		args[I].ptrB  = ptrB;
		args[I].ptrP  = ptrP;
		int thread_id = athreadCreateThread (&global_atm, 0, (void*) Mat_mul, 
									(void*) &(args[I]));
		if(thread_id > 0)
		{
			args[I].thread_id = thread_id; 
			threads[I] = thread_id;
		}
		else
			threads[I] = 0;

		ptrA = (ptrA + args[I].start_Arr);
		ptrP = (ptrP + args[I].start_Arr);
	}

	while(1)
	{
		int selected_thread = athreadSelectAndRunThread (&global_atm, 0, 0);

	//	cortos_printf("Mat_mul_main finished thread %d.\n", selected_thread); 

		if(all_threads_completed(threads, NJOBS))
			break;	
	}


}
