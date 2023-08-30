#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <ajit_context.h>
#include <data_struct.h>
extern volatile int n_calls;
extern volatile int done_flag;
void foo_1 (CoroutineControl* cc_ctrl)
{
	cortos_printf("entered foo_1 (sp=0x%x)\n", cc_ctrl->pcc->mctxt.outs[6]);
	__ajit_swapcontext__ (cc_ctrl->pcc, cc_ctrl->pscheduler);
	cortos_printf("continuing from foo_1 (sp=0x%x)\n", cc_ctrl->pcc->mctxt.outs[6]);
}

void foo_2 (CoroutineControl* cc_ctrl)
{
	cortos_printf("entered foo_2 (sp=0x%x)\n", cc_ctrl->pcc->mctxt.outs[6]);
	foo_1(cc_ctrl);
}


void coroutine (CoroutineControl* cc_ctrl)
{
	cortos_printf ("coroutine [a: %d]: (sp=0x%x).\n", n_calls, cc_ctrl->pcc->stack_pointer);
	n_calls++;

	cortos_printf ("coroutine [a: %d]: (sp=0x%x).\n", n_calls, cc_ctrl->pcc->stack_pointer);
	__ajit_swapcontext__ (cc_ctrl->pcc, cc_ctrl->pscheduler);

	n_calls++;
	cortos_printf ("coroutine [b: %d]: (sp=0x%x).\n", n_calls, cc_ctrl->pcc->stack_pointer);

	foo_1(cc_ctrl);

	n_calls++;
	cortos_printf ("coroutine [c: %d]: (sp=0x%x).\n", n_calls, cc_ctrl->pcc->stack_pointer);

	foo_2(cc_ctrl);

	cortos_printf("setting done=1 (sp=0x%x)\n", cc_ctrl->pcc->mctxt.outs[6]);
	done_flag = 1;
}
