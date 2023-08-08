#ifndef __ajit_coroutine__h__
#define __ajit_coroutine__h__

#include <stdint.h>
#include "ajit_context.h"

typedef enum {
	CREATED,
	RUNNING,
	SUSPENDED,
	COMPLETED
} coroutine_state_t;

typedef struct ajit_coroutine_t__ {

   ajit_context_t *caller_context;
   ajit_context_t *run_context;

   void* fn();
   void* arg;
   coroutine_state_t state;
} ajit_coroutine_t;

void ajit_coroutine_create (ajit_context_t* run_context, 
				void* f(), 
				void* arg, 
				ajit_coroutine_t* cr);

void ajit_coroutine_run (ajit_context_t* scheduler_context, ajit_coroutine_t* cr);
void ajit_coroutine_resume (ajit_context_t* scheduler_context, ajit_coroutine_t* cr);

// IN PROGRESS

#endif
