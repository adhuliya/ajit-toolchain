#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <cortos.h>
#include <ajit_context.h>
#include <ajit_coroutine.h>

extern volatile int done_flag;
volatile ajit_coroutine_t ccr  __attribute__ ((aligned(8))) ;
volatile ajit_coroutine_t* pccr = (&ccr);

void coroutine_1 (ajit_coroutine_t* pxr);
volatile int ncalls = 0;

void coroutine_0 (ajit_coroutine_t* pxr)
{
	CORTOS_DEBUG("in coroutine_0: trying to create coroutine_1\n");
	ajit_coroutine_create (STACK_SIZE_IN_BYTES, coroutine_1, (void*) pccr, pccr);
	CORTOS_DEBUG("in coroutine_0: created coroutine_1\n");

	ajit_coroutine_yield (pxr);

	CORTOS_DEBUG("in coroutine_0: resumed, call coroutine_1\n");
	ajit_coroutine_run(pccr);
	CORTOS_DEBUG("in coroutine_0: coroutine_1 returned, yield coroutine_0\n");

	while(pccr->state != __COMPLETED)
	{
		CORTOS_DEBUG("in coroutine_0: calling ajit_coroutine_resume (coroutine_1)\n");
		ajit_coroutine_resume (pccr);
		CORTOS_DEBUG("in coroutine_0: ajit_coroutine_resume returns (coroutine_1)\n");

		CORTOS_DEBUG("in coroutine_0: yield\n");
		ajit_coroutine_yield (pxr);
		CORTOS_DEBUG("in coroutine_0: resume\n");
	}

	CORTOS_DEBUG("in coroutine_0: return\n");
	done_flag = 1;

	ajit_coroutine_return(pxr);

}

void coroutine_1 (ajit_coroutine_t* pxr)
{
	cortos_printf("in coroutine_1: ncalls = %d\n", ncalls);
	ncalls++;

	ajit_coroutine_yield(pxr);

	cortos_printf("in coroutine_1: ncalls = %d\n", ncalls);
	ncalls++;

	ajit_coroutine_yield(pxr);
	
	cortos_printf("in coroutine_1: ncalls = %d\n", ncalls);
	ncalls++;

	ajit_coroutine_yield(pxr);

	cortos_printf("in coroutine_1: ncalls = %d\n", ncalls);
	ncalls++;

	cortos_printf("in coroutine_1: return\n");
	ajit_coroutine_return(pxr);
}

