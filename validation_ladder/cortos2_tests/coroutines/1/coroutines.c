#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <ajit_context.h>
#include <data_struct.h>

void coroutine_yield(int active_context);
extern volatile int volatile exit_flag;

extern ajit_context_t *cp_0;
extern ajit_context_t *cp_1;

// coroutine 0 does setcontext(cp_1)
void coroutine_0 (void* ptr)
{
	static int I=0;
	uint32_t sp;
	 __AJIT_GET_IU_REGISTER(14,sp);
	cortos_printf("C0 (sp=0x%x): %d.\n", sp, I);
	I++;

	__ajit_setcontext__ (cp_1);
}

// coroutine 1 does setcontext(cp_0) as long 
// as exit flag is 0.  If exit flag is 1,
// coroutine modifies cp_0 so that setcontext(cp_0)
// returns and the chain is broken.
void coroutine_1 (void* ptr)
{
	static int I=0;

	uint32_t sp; __AJIT_GET_IU_REGISTER(14,sp);
	cortos_printf("C1 (sp=0x%x): %d.\n", sp, I);
	I++;

	if(exit_flag)
	// break the links, setcontext(cp_0)
	// will return to post getcontext(cp_0) point.
	{
		cp_0->func = NULL;
		cp_0->uc_link = NULL;
	}

	__ajit_setcontext__ (cp_0);
}
