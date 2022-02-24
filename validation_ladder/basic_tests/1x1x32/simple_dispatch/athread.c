#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "defs.h"
#include "dispatch.h"
#include "athread.h"

// This one does not have acquire a mutex...
int athreadInit(athreadManager* atm)
{
	atm->atm_mutex_var = 0;

	int I;
	for(I = 0; I < MAX_ACTIVE_THREADS; I++)
		atm->thread_status[I] = THREAD_UNALLOCATED;

	initDispatchQueue(&(atm->dq));
}

// returns a non-zero thread id between 1 and MAX_ACTIVE_THREADS
int athreadAllocateThread(athreadManager* atm)
{
	AMUTEX_ACQUIRE (atm->atm_mutex_var);	

	int ret_val = 0;
	int I;
	for(I = 0; I < MAX_ACTIVE_THREADS; I++)
	{
		if(atm->thread_status[I] == THREAD_UNALLOCATED)
		{
			ret_val = (I+1);
			atm->thread_status[I] = THREAD_ALLOCATED;
			break;
		}
	}
	AMUTEX_RELEASE (atm->atm_mutex_var);
	return(ret_val);
}

int athreadDeallocateThread(athreadManager* atm, int thread_id)
{
	int ret_val = 0;
	if((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS))
	{
		AMUTEX_ACQUIRE (atm->atm_mutex_var);	
		atm->thread_status[thread_id-1] = THREAD_UNALLOCATED;
		AMUTEX_RELEASE (atm->atm_mutex_var);
	}
	else
		ret_val = 1;

	return(ret_val);
}


int athreadDispatchThread (athreadManager* atm, int thread_id, void* fn, void* arg)
{
	int ret_val = 1;

	if((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS))
	{
		AMUTEX_ACQUIRE (atm->atm_mutex_var);	
		ret_val = pushIntoDispatchQueue(&(atm->dq), thread_id, fn, arg);
		atm->thread_status[thread_id-1] = THREAD_ON_DISPATCH_Q;
		AMUTEX_RELEASE (atm->atm_mutex_var);
	}

	return(ret_val);
}

int athreadThreadStatus (athreadManager* atm, int thread_id)
{
	int ret_val = -1;
	if((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS))
	{
		AMUTEX_ACQUIRE (atm->atm_mutex_var);	
		ret_val = atm->thread_status[thread_id-1];
		AMUTEX_RELEASE (atm->atm_mutex_var);
	}
	return(ret_val);
}

// spin until thread has returned..
int athreadJoinThread (athreadManager* atm, int thread_id)
{
	int ret_val = 0;
	if((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS))
	{
		while(1)
		{
			int ts = athreadThreadStatus(atm, thread_id);
			if ((ts == THREAD_UNALLOCATED) || (ts == THREAD_COMPLETED))
				break;

		}
	}
	return(ret_val);
}

// returns 0 on success..
int athreadReturn (athreadManager* atm, int thread_id)
{
	int ret_val = 1;
	if((thread_id > 0) && (thread_id <= MAX_ACTIVE_THREADS))
	{

		int ts = athreadThreadStatus(atm, thread_id);
		if(ts == THREAD_RUNNING)
		{
			AMUTEX_ACQUIRE (atm->atm_mutex_var);	
			atm->thread_status[thread_id-1] = THREAD_COMPLETED;
			AMUTEX_RELEASE (atm->atm_mutex_var);
			ret_val = 0;
		}
	}
	return(ret_val);
}


// return thread id > 0 on success.  *fn, *arg updated.
int athreadGetThreadToRun(athreadManager* atm, void** fn, void** arg)
{
	int ret_val = 0;
	AMUTEX_ACQUIRE (atm->atm_mutex_var);	
	ret_val = popFromDispatchQueue(&(atm->dq), fn, arg);
	AMUTEX_RELEASE (atm->atm_mutex_var);

	return(ret_val);
}


