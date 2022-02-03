#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "dispatch.h"

// initialize..
int initDispatchQueue(dispatchQueue* dq)
{
	int I;
	for(I=0; I < DISPATCH_QUEUE_SIZE; I++)
	{
		dq->jobs[I].thread_id = 0;
		dq->jobs[I].fn    = NULL;
		dq->jobs[I].arg  = NULL;
	}

	dq->write_pointer = 0;
	dq->read_pointer  = 0;

}
	

// returns 0 if push succeeded..
int pushIntoDispatchQueue(dispatchQueue* dq, int thread_id, void* fn, void* arg)
{
	int ret_val = 0;

	int wp = dq->write_pointer;
	int nwp = (wp + 1) & DISPATCH_QUEUE_MASK;
	if(nwp != dq->read_pointer)
	{
		dq->jobs[wp].thread_id = thread_id;
		dq->jobs[wp].fn  = fn;
		dq->jobs[wp].arg = arg;
		dq->write_pointer = nwp;
	}
	else
		ret_val = 1;
	return(ret_val);
}

// returns thread_id > 0 on success.  *fn and *arg are updated/
int popFromDispatchQueue(dispatchQueue* dq, void** fn, void** arg)
{
	int ret_val = 0;

	int rp = dq->read_pointer;
	int wp = dq->write_pointer;
	
	if(rp != wp)
	{
		*fn = dq->jobs[rp].fn;
		*arg =	dq->jobs[rp].arg;
		ret_val = dq->jobs[rp].thread_id;
		dq->read_pointer = (rp + 1) & DISPATCH_QUEUE_MASK;
	}
	else
	{
		*fn = NULL;
		*arg = NULL;
	}

	return(ret_val);
}

