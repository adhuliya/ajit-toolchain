#include <stdio.h>
#include <stdint.h>
#include <ajit_access_routines.h>
#include <ajit_context.h>
#include <cortos.h>
#include "ajit_coroutine.h"

//
//  fill the ajit_coroutine_t* structure.
//
int ajit_coroutine_create (uint32_t stack_size_in_bytes,
 				void* f, 
 				// the argument for the function.
 				void* arg, 
 				// the coroutine structure.
 				ajit_coroutine_t* cr)
{

	__ajit_context_init__ (&(cr->caller_context));

	__ajit_context_init__ (&(cr->run_context));
	__ajit_context_set_func_and_arg__ (&(cr->run_context), (uint32_t) f, (uint32_t) arg);

	//__ajit_context_set_link_context__ (&(cr->run_context), &(cr->caller_context));

	// allocate stack.
	cr->stack  = cortos_bget(stack_size_in_bytes);
	cr->stack_size_in_bytes = stack_size_in_bytes;


	if(cr->stack == NULL)
	{
		cortos_printf("Error: could not allocate stack.\n");
		return(-1);
	}


	cr->fn = f;
	cr->arg = arg;

	cr->state = __CREATED;

	return(0);
}


int ajit_coroutine_destroy(ajit_coroutine_t* cr)
{
	if ((cr != NULL) && (cr->stack != NULL))
		cortos_brel(cr->stack);
}

