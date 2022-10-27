#include "aclock.h"

void initAclock(Aclock* clk, uint32_t number_of_threads)
{
	clk->number_of_threads = number_of_threads;
	clk->free_thread_id    = 1;
	
	int I;
	for(I = 0; I < MAX_CLOCK_THREADS; I++)
	{
		clk->time_stamps[I] = 0;
		clk->used_arg_flags[I] = 0;
		clk->arg_array[I] = NULL;
		
	}
}

uint32_t getNumberOfThreads(Aclock* clk)
{
	return(clk->number_of_threads);
}


// return non-zero thread id on success
uint32_t registerThreadWithAclock(Aclock* clk)
{
	uint32_t ret_val = 0;
	if(clk->free_thread_id <= clk->number_of_threads)
	{
		ret_val = clk->free_thread_id;
		clk->free_thread_id++;
	}
	return(ret_val);
}

// get arg.
//  0 on success..
uint32_t getSynchedArg (Aclock* clk, uint64_t time_stamp, uint32_t from_thread_id, void** arg)
{
	if(clk->time_stamps[from_thread_id-1] == time_stamp)
	{
		*arg = clk->arg_array[from_thread_id - 1];
		return(0);
	}
	else
	{
		*arg = NULL;
		return(1);
	}
}

uint32_t markArgsAsUsed (Aclock* clk, uint64_t time_stamp, uint32_t thread_id)
{
	if(clk->time_stamps[thread_id-1] == time_stamp)
	{
		clk->used_arg_flags[thread_id - 1] = 1;
		return(0);
	}
	else
	{
		return(1);
	}
}

// return 0 on success.
uint32_t synchStart (Aclock* clk, uint64_t time_stamp, uint32_t thread_id, void* arg)
{

	clk->used_arg_flags[thread_id - 1] = 0;
	clk->arg_array[thread_id - 1] = arg;
	clk->time_stamps[thread_id - 1] = time_stamp;

	return(0);
}




//
// return 0 on success.
// error codes
//   #define NOT_ALL_SYNCHED  1
//   #define NOT_ALL_USED_ARG 2
//   
uint32_t synchComplete (Aclock* clk, uint64_t time_stamp, uint32_t thread_id)
{
	markArgsAsUsed (clk, time_stamp, thread_id);

	uint32_t all_have_synched  = 1;
	uint32_t all_have_used_arg = 1;
	int I;
	for(I = 0; I < clk->number_of_threads; I++)
	{
		// bail out if all have not synched.
		if(time_stamp != clk->time_stamps[I])
			all_have_synched = 0;

		
		// bail out if all have not used the args..
		if(!clk->used_arg_flags[I])
			all_have_used_arg = 0;
	}	

	if(!all_have_synched)
		ret_val = NOT_ALL_SYNCHED;
	else if(!all_have_used_arg)
		ret_val = NOT_ALL_USED_ARG;
	else
		ret_val = 0;

	return(ret_val);
}

