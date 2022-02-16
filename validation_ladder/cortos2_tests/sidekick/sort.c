#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "defs.h"
#include "athread.h"

extern uint32_t array_to_be_sorted[ORDER];
extern athreadManager global_atm;

typedef struct __SortArg {

	uint32_t  thread_id;
	uint32_t* ptr;
	uint32_t  length;

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

void sortSingle(void* arg)
{
	SortArg* sarg = (SortArg*) arg;
	int I, J, K;

	// bubble sort..
	for(I = 0; I < sarg->length-1; I++)
	{
		for(J = 0; J < (sarg->length -I)-1; J++)
		{
			if(sarg->ptr[J] > sarg->ptr[J+1])
			{
				uint32_t tmp = sarg->ptr[J];	
				sarg->ptr[J] = sarg->ptr[J+1];
				sarg->ptr[J+1] = tmp;
			}
		}
	}

#ifdef DEBUG_MODE
	for(I = 0; I < sarg->length; I++)
	{
		cortos_printf("s%d: %d.\n", sarg->thread_id, sarg->ptr[I]);
	}
#endif

}

//
// merge..
//  a[0] a[1] .... a[(L/2)-1]
//  a[L/2] a[L/2 + 1] .... a[L-1]
//
void mergeSingle(void* arg)
{
	uint32_t T[ORDER];

	SortArg* sarg = (SortArg*) arg;
	int I, J, K;

	J = 0; K = 0;

	uint32_t H = sarg->length >> 1;
		
#ifdef DEBUG_MODE
	cortos_printf("m%d: entered merge with length=%d, H=%d.\n", sarg->thread_id, sarg->length, H);
#endif
	
	// construct the merged array...
	for(I = 0; I < sarg->length; I++)
	{
		uint32_t A, B;
		A = sarg->ptr[J];
		B = sarg->ptr[H+K];

		if((K == H) ||  (A < B))
		{
			T[I] = A;
			J++;
		}
		else if((J == H) || (B <= A))
		{
			T[I] = B;
			K++;
		}

#ifdef DEBUG_MODE
		cortos_printf("m%d: (%d, %d) -> %d.\n", sarg->thread_id, A, B, T[I]); 
#endif
	}

	// copy the merged array..
	for(I = 0; I < sarg->length; I++)
	{
		sarg->ptr[I] = T[I];
	}
}

void sortParallel()
{
	SortArg args[NJOBS];
	int     threads[NJOBS];
	int I;

	uint32_t* ptr = array_to_be_sorted;
	for(I = 0; I < NJOBS; I++)
	{
		args[I].length = ORDER/NJOBS;
		args[I].ptr    = ptr;
		int thread_id = athreadCreateThread (&global_atm, 0, (void*) sortSingle, 
									(void*) &(args[I]));
		if(thread_id > 0)
		{
			args[I].thread_id = thread_id;
			threads[I] = thread_id;
		}
		else
			threads[I] = 0;

		ptr = (ptr + args[I].length);
	}

	while(1)
	{
		int selected_thread = athreadSelectAndRunThread (&global_atm, 0, 0);

#ifdef DEBUG_MODE
		cortos_printf("sortParallel finished thread %d.\n", selected_thread); 
#endif

		if(all_threads_completed(threads, NJOBS))
			break;	
	}

	int current_length = 2*ORDER/NJOBS;
	while(current_length <= ORDER)
	{
		uint32_t MJOBS = ORDER/current_length;
		ptr = array_to_be_sorted;

		for(I = 0; I < MJOBS; I++)
		{
			args[I].length = current_length;
			args[I].ptr    = ptr;
			int thread_id = athreadCreateThread (&global_atm, 0, (void*) mergeSingle, 
									(void*) &(args[I]));
			if(thread_id > 0)
			{
				args[I].thread_id = thread_id;
				ptr = (ptr + current_length);
				threads[I] = thread_id;
			}
			else 
				threads[I] = 0;
		}
				

		while(1)
		{
			athreadSelectAndRunThread (&global_atm, 0, 0);
			if(all_threads_completed(threads, MJOBS))
				break;	
		}

		current_length = current_length*2;
	}
	
}

