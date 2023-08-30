#ifndef __ajit_coroutine__h__
#define __ajit_coroutine__h__

#include <stdint.h>
#include "ajit_context.h"

typedef enum {
	__UNDEFINED,
	__CREATED,
	__RUNNING,
	__SUSPENDED,
	__COMPLETED
} coroutine_state_t;

typedef struct ajit_coroutine_t__ {

   ajit_context_t *caller_context;
   ajit_context_t *run_context;

   void* fn;
   void* arg;
   coroutine_state_t state;
} ajit_coroutine_t;

int ajit_coroutine_create (ajit_context_t* run_context, 
				uint32_t stack_base_address,
				uint32_t stack_size,
				ajit_context_t* scheduler_context,
				void* f, 
				void* arg, 
				ajit_coroutine_t* cr);

int ajit_coroutine_run    ( ajit_coroutine_t* cr);
int ajit_coroutine_yield  ( ajit_coroutine_t* cr);
int ajit_coroutine_resume ( ajit_coroutine_t* cr);
int ajit_coroutine_return ( ajit_coroutine_t* cr);

// IN PROGRESS

#endif
