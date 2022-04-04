//#define CORTOS  0
#include <stdlib.h>
#include <stdint.h>
#ifdef CORTOS
#include <cortos.h>
#else
#include "ajit_access_routines.h"
#include "core_portme.h"
#endif
#include "athread.h"

// This one does not have acquire a mutex...
uint32_t athreadManagerInit(athreadManager* atm)
{
#ifdef CORTOS
	atm->atm_mutex_var = cortos_reserveLock(0);
#else
	atm->atm_mutex_var = 0;
#endif
	atm->thread_counter = 0;

	int I;
	for(I = 0; I < MAX_ACTIVE_THREADS; I++)
	{
		atm->threads[I].thread_status = THREAD_UNALLOCATED;
		atm->threads[I].thread_id     = (I + 1);
		atm->threads[I].priority      = 0;
		atm->threads[I].sequence_id = 0;
		atm->threads[I].fn = NULL;
		atm->threads[I].arg = NULL;
	}
	return(0);
}

// returns a non-zero thread id between 1 and MAX_ACTIVE_THREADS
uint32_t athreadCreateThread(athreadManager* atm, uint32_t priority, int* fn, void* arg)
{
	AMUTEX_ACQUIRE (atm->atm_mutex_var);	

	uint32_t ret_val = 0;
	int I;
	for(I = 0; I < MAX_ACTIVE_THREADS; I++)
	{
		if(atm->threads[I].thread_status == THREAD_UNALLOCATED)
		{
			ret_val = atm->threads[I].thread_id;
			atm->threads[I].priority = priority;
			atm->threads[I].sequence_id = atm->thread_counter;
			atm->thread_counter++;
			
	
			atm->threads[I].fn  = fn;
			atm->threads[I].arg = arg;
		
			atm->threads[I].thread_status = THREAD_ALLOCATED;

			break;
		}
	}
	AMUTEX_RELEASE (atm->atm_mutex_var);
	return(ret_val);
}

// returns 0 on success.
uint32_t athreadRestartThread(athreadManager* atm, uint32_t thread_id)
{
	int ret_val = 1;
	AMUTEX_ACQUIRE (atm->atm_mutex_var);	
	if ((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS))
	{
		if(atm->threads[thread_id-1].thread_status == THREAD_COMPLETED)
		{
			atm->threads[thread_id-1].thread_status = THREAD_ALLOCATED;
			atm->threads[thread_id-1].sequence_id = __ajit_get_clock_time();
			ret_val = 0;
		}
	}
	AMUTEX_RELEASE (atm->atm_mutex_var);
	return(ret_val);
}

// returns 0 on success.
uint32_t athreadDestroyThread(athreadManager* atm, uint32_t thread_id)
{
	int ret_val = 0;
	AMUTEX_ACQUIRE (atm->atm_mutex_var);	
	if((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS) && 
			(atm->threads[thread_id-1].thread_status == THREAD_COMPLETED))
	{
		atm->threads[thread_id-1].thread_status = THREAD_UNALLOCATED;
	}
	else
	{
		ret_val = 1;
	}
	AMUTEX_RELEASE (atm->atm_mutex_var);

	return(ret_val);
}



uint32_t athreadThreadStatus (athreadManager* atm, uint32_t thread_id)
{
	int ret_val = -1;
	if((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS))
	{
		ret_val = atm->threads[thread_id-1].thread_status;
	}
	return(ret_val);
}

uint32_t athreadThreadGetArgs (athreadManager* atm, uint32_t thread_id, int** fn, void** arg)
{
	int ret_val = -1;
	*fn = NULL;
	*arg = NULL;
	if((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS))
	{
		ret_val = 0;
		*fn =  atm->threads[thread_id-1].fn;
		*arg =  atm->threads[thread_id-1].arg;
	}
	return(ret_val);
}

uint32_t athreadThreadGetReturnValue (athreadManager* atm, uint32_t thread_id, int* ret_value)
{
	int ret_val = 1;
	if((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS))
	{
		ret_val = 0;
		*ret_value = atm->threads[thread_id-1].return_value;
	}
}

//
// spin until thread has returned..
// returns 0 on success..
//
uint32_t athreadJoinThread (athreadManager* atm, uint32_t thread_id)
{
	int ret_val = 1;
	if((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS))
	{
		while(1)
		{
			int ts = athreadThreadStatus(atm, thread_id);
			if ((ts == THREAD_UNALLOCATED) || (ts == THREAD_COMPLETED))
				break;

		}
		ret_val = 0;
	}
	return(ret_val);
}

// returns 0 on success..
uint32_t athreadReturn (athreadManager* atm, uint32_t thread_id)
{
	int ret_val = 1;
	if((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS))
	{

		int ts = athreadThreadStatus(atm, thread_id);
		if(ts == THREAD_RUNNING)
		{
			AMUTEX_ACQUIRE (atm->atm_mutex_var);	
			atm->threads[thread_id-1].thread_status = THREAD_COMPLETED;
			AMUTEX_RELEASE (atm->atm_mutex_var);
			ret_val = 0;
		}
	}
	return(ret_val);
}


//
// return thread id > 0 on success.
// 
// Will look for the highest-priority thread in the specified priority range.
// If there is more than one such thread, it will use the earliest creation time as a tie-breaker.
//
uint32_t athreadSelectAndRunThread(athreadManager* atm, 
				uint32_t min_priority,
				uint32_t max_priority)
{
	int ret_val = 0;
	
	int I;
	uint32_t P = 0;
	uint64_t ET = 0xffffffffffffffff;

	AMUTEX_ACQUIRE (atm->atm_mutex_var);	
	for(I = 0; I < MAX_ACTIVE_THREADS; I++)
	{
		if(atm->threads[I].thread_status == THREAD_ALLOCATED)
		{
			if((atm->threads[I].priority >= min_priority) &&
				(atm->threads[I].priority <= max_priority))
			{
				if(atm->threads[I].priority >= P) 
				{
					P = atm->threads[I].priority;
					if(atm->threads[I].sequence_id < ET)
					{
						ret_val = I + 1;
						ET = atm->threads[I].sequence_id;
					}
				}
			}
		}
	}

	if(ret_val > 0)
	{
		// which core/thread is it running on?
		atm->threads[ret_val-1].thread_status = THREAD_RUNNING;
	}
	AMUTEX_RELEASE (atm->atm_mutex_var);

	if(ret_val > 0)
	{
		int (*__fn)(void*) = atm->threads[ret_val-1].fn;
		void *arg = atm->threads[ret_val-1].arg;

		atm->threads[ret_val-1].return_value = (*__fn)(arg);
		athreadReturn(atm, ret_val);
	}

	return(ret_val);
}

