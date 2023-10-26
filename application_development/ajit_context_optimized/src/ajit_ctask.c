#include <stdio.h>
#include <stdint.h>
#include <ajit_access_routines.h>
#include <ajit_context.h>
#include <cortos.h>
#include "ajit_coroutine.h"
#include "ajit_ctask.h"

void ajit_init_ctask (ajit_ctask_t* ctask)
{
	ctask->index_in_pool = -1;
	ctask->pool = NULL;
	ctask->next = NULL;
	ctask->prev = NULL;
}

void ajit_init_ctask_list (ajit_ctask_list_t* tl)
{
	tl->head = NULL;
	tl->tail = NULL;
}


void   ajit_push_back_ctask (ajit_ctask_t* t, ajit_ctask_list_t* tl)
{
	if(tl->tail == NULL)
	{
		tl->head = t;
		tl->tail = t;	
		
		t->next = NULL;
		t->prev = NULL;
	}
	else
	{
		t->prev = tl->tail;
		t->next = NULL;

		tl->tail->next = t;
		tl->tail = t;
	}
	CORTOS_DEBUG("pushed back task 0x%x\n", (uint32_t) t);
}

ajit_ctask_t* ajit_pop_back_ctask (ajit_ctask_list_t* tl)
{
	ajit_ctask_t* rv = NULL;
	if(tl->tail != NULL)
	{
		// go with the tail.
		rv = tl->tail;
		if(rv->prev != NULL)
		{
			rv->prev->next = NULL;
			tl->tail = rv->prev;
		}
		else
		{
			tl->head = NULL;
			tl->tail = NULL;
		}
	}
	return(rv);
}



void   ajit_push_front_ctask (ajit_ctask_t* t, ajit_ctask_list_t* tl)
{
	if(tl->head == NULL)
	{
		t->prev = NULL;
		t->next = NULL;

		tl->head  = t;
		tl->tail  = t;

	}
	else
	{
		t->next = tl->head;
		tl->head->prev = t;

		t->prev = NULL;
		tl->head = t;
	}
}
	

ajit_ctask_t* ajit_pop_front_ctask (ajit_ctask_list_t* tl)
{
	ajit_ctask_t* rv = NULL;
	if(tl->head != NULL)
	{
		rv = tl->head;
		tl->head = rv->next;

		if(tl->head != NULL)
		{
			tl->head->prev = NULL;
		}
		else
		{
			tl->tail = NULL;
		}
	}	
	return(rv);
}

// init..
void ajit_init_ctask_pool (ajit_ctask_pool_t* cpool)
{
	int i;
	for(i = 0; i < MAX_NUMBER_OF_CTASKS; i++)
		cpool->valid[i] = 0;	
}

// return NULL if there is no room.
ajit_ctask_t*  ajit_reserve_ctask_from_pool (ajit_ctask_pool_t* cpool)
{
	int i = 0;
	ajit_ctask_t* rv = NULL;
	for(i = 0; i < MAX_NUMBER_OF_CTASKS; i++)
	{
		if (!cpool->valid[i])
		{
			rv = &(cpool->tasks[i]);
			rv->index_in_pool = i;
			cpool->valid[i] = 1;
			break;
		}
	}

	if(rv != NULL)
	{
		CORTOS_DEBUG("reserved ctask 0x%x (index=%d)\n", rv, rv->index_in_pool);
	}
	return(rv);
}

// return to pool
void ajit_release_ctask_to_pool (ajit_ctask_t* t, ajit_ctask_pool_t* cpool)
{
	cpool->valid[t->index_in_pool] = 0;
}

// return 0 on success.
int ajit_init_ctask_scheduler(ajit_ctask_scheduler_t* sched)
{
	ajit_init_ctask_pool(&(sched->pool));
	ajit_init_ctask_list (&(sched->active_list));
	sched->lock = cortos_reserveLock(1);

	if (sched->lock == NULL)
		return(-1);
	else return(0);
}

int ajit_run_ctask_scheduler (ajit_ctask_scheduler_t* sched)
{
	uint32_t seq_number = 0;

	while(1) 
	{
		cortos_lock_acquire_buzy (sched->lock);

		ajit_ctask_t* t = ajit_pop_front_ctask(&(sched->active_list));
		seq_number++;

		cortos_lock_release (sched->lock);

		CORTOS_DEBUG("popped ctask 0x%x\n", (uint32_t) t);

		if(t != NULL)
		{

			if(t->coroutine.state == __CREATED)
			{
				CORTOS_DEBUG("starting coroutine of ctask 0x%x\n", (uint32_t) t);
				t->sequence_id = seq_number;
				ajit_coroutine_run ((&(t->coroutine)));

				CORTOS_DEBUG("returned from coroutine of ctask 0x%x\n", (uint32_t) t);

				// hang around until done.
				if(t->coroutine.state == __SUSPENDED)
				{
				
					CORTOS_DEBUG("suspended coroutine of ctask 0x%x\n", (uint32_t) t);

					// push it back into the queue..
					cortos_lock_acquire_buzy (sched->lock);
					ajit_push_back_ctask (t, &(sched->active_list));
					cortos_lock_release (sched->lock);
				}
			}
			else if(t->coroutine.state == __SUSPENDED)
			{
				CORTOS_DEBUG("resuming coroutine of ctask 0x%x\n", (uint32_t) t);

				ajit_coroutine_resume ((&(t->coroutine)));
				if(t->coroutine.state == __SUSPENDED)
				{
					// push it back into the queue..
					cortos_lock_acquire_buzy (sched->lock);
					ajit_push_back_ctask (t, &(sched->active_list));
					cortos_lock_release (sched->lock);
				}
			}
			else
			{
			}
		}
		else
		{
			// sleep for 64 clock cycles.
			__ajit_sleep__ (64);
		} 
	}
}


int  ajit_schedule_ctask (ajit_ctask_t* ct,
				void *fn, void* arg, uint32_t stack_size_in_bytes,
								ajit_ctask_scheduler_t* cts)
{
	CORTOS_DEBUG("entered ajit_schedule_ctask (ct=0x%x), index=%d\n", (uint32_t) ct, ct->index_in_pool);

	if(ct == NULL)
		return(-1);

	int v = ajit_coroutine_create (stack_size_in_bytes, fn, arg, &(ct->coroutine));
	if(v != 0)
		return (-1);


	ajit_push_back_ctask (ct, &(cts->active_list));
	return(ct);
}
	


int ajit_resume_ctask (ajit_ctask_t* ct, ajit_ctask_scheduler_t* cts)
{
	ajit_coroutine_resume((&(ct->coroutine)));
}

int ajit_join_ctask (ajit_ctask_t* ct,  ajit_ctask_scheduler_t* cts)
{
	while(1) {
		if(ct->coroutine.state == __COMPLETED)
			break;

		__ajit_sleep__ (256);
	}
	return(0);	
}

