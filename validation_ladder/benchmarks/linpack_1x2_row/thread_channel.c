#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <cortos.h>
#include "ajit_access_routines.h"
#include "thread_channel.h"


void initChannel(ThreadChannel* tc, uint32_t id)
{
	tc->id = id;
	tc->request_id = 0;	
	tc->fn_ptr = NULL;
	tc->arg_ptr = NULL;
	tc->status = CH_FREE;
}


// return 0 on success.
uint32_t scheduleChannelJob (ThreadChannel* tc, void *fn_ptr, void* arg_ptr)
{
	uint32_t ret_val = 1;
	if(tc->status == CH_FREE)
	{
		tc->request_id += 1;
		tc->fn_ptr = fn_ptr;
		tc->arg_ptr = arg_ptr;
		tc->status = CH_REQUESTED;
		CORTOS_DEBUG("Channel %d: status = %d.\n", tc->status);
		ret_val = 0;
	}
	return(ret_val);
}

// return 0 on success.
uint32_t getChannelResponse (ThreadChannel* tc, void** arg_ptr)
{
	uint32_t ret_val = 1;
	if(tc->status == CH_COMPLETED)
	{
		*arg_ptr = tc->arg_ptr;

		tc->fn_ptr = NULL;
		tc->arg_ptr = NULL;
		tc->status = CH_FREE;

		CORTOS_DEBUG("Channel %d: status = %d.\n", tc->id, tc->status);
		ret_val = 0;
	}
	return(ret_val);
}


uint32_t getChannelJob (ThreadChannel* tc, void** __fn, void** __arg)
{
	uint32_t ret_val = 1;
	if(tc->status == CH_REQUESTED)
	{
		*__fn = tc->fn_ptr;
		*__arg = tc->arg_ptr;
		tc->status = CH_IN_PROGRESS;
		CORTOS_DEBUG("Channel %d: status = %d.\n", tc->id, tc->status);
		ret_val = 0;
	}
	return(ret_val);
}

