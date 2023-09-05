#ifndef __ajit_coroutine__h__
#define __ajit_coroutine__h__

#include <stdint.h>
#include "ajit_context.h"

#define AJIT_COROUTINE_DEFAULT_FRAME_SIZE  96

typedef enum {
	__UNDEFINED,
	__CREATED,
	__RUNNING,
	__SUSPENDED,
	__COMPLETED
} coroutine_state_t;

typedef struct ajit_coroutine_t__ {

   ajit_context_t caller_context;
   ajit_context_t run_context;

   uint8_t* stack;
   uint32_t stack_size_in_bytes;

   uint8_t* caller_stack;
   uint32_t caller_stack_size_in_bytes;

   void* fn;
   void* arg;

   coroutine_state_t state;
} ajit_coroutine_t;

int ajit_coroutine_create(uint32_t stack_size_in_bytes,
				void* f, 
				// the argument for the function.
				void* arg, 
				// the coroutine structure.
				ajit_coroutine_t* cr);

#define ajit_coroutine_run(pcr) {\
	pcr->state = __RUNNING;\
 	__ajit_getcontext__  (&(pcr->run_context), pcr->stack + STACK_SIZE_IN_BYTES - \
					AJIT_COROUTINE_DEFAULT_FRAME_SIZE);\
         __ajit_swapcontext__ (&(pcr->caller_context), pcr->caller_stack + STACK_SIZE_IN_BYTES-\
					AJIT_COROUTINE_DEFAULT_FRAME_SIZE,\
                                                                         &(pcr->run_context));}
#define ajit_coroutine_yield(pcr) {\
	pcr->state = __SUSPENDED;\
	__ajit_context_set_func_and_arg__ (&(pcr->run_context), 0,0);\
	__ajit_swapcontext__ (&(pcr->run_context), 0, &(pcr->caller_context));}	

#define ajit_coroutine_resume(pcr) {\
	pcr->state = __RUNNING;\
	__ajit_swapcontext__ (&(pcr->caller_context), 0x0, &(pcr->run_context));}

#define ajit_coroutine_return(pcr) {\
		pcr->state = __COMPLETED;\
		__ajit_setcontext__ (&(pcr->caller_context)); }



#endif
