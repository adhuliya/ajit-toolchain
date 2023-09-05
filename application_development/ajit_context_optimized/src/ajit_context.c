#include <stdio.h>
#include <stdint.h>
#include <ajit_access_routines.h>
#include <ajit_context.h>
#include <cortos.h>
	
void __update_current_window_on_stack__ (uint32_t stack_pointer);

/*
int __ajit_swapcontext__ (ajit_context_t *__restrict __oucp, const ajit_context_t *__restrict __ucp)
{
	__ajit_getcontext__(__oucp);
	__ajit_setcontext__(__ucp);
}
*/

void __ajit_context_set_func_and_arg__ (ajit_context_t* ctxt, uint32_t fn_pointer, uint32_t arg_pointer)
{
	ctxt->func       = (uint32_t) fn_pointer;
	ctxt->func_arg   = (uint32_t) arg_pointer;
	CORTOS_DEBUG("func, arg = 0x%x, 0x%x\n", fn_pointer, arg_pointer);
}

void __ajit_context_set_link_context__ (ajit_context_t* ctxt, ajit_context_t* link_context)
{
	ctxt->link_context = (uint32_t) link_context;
}



void __ajit_print_context__ (ajit_context_t* t)
{
	cortos_printf("pc = 0x%x.\n", t->pc);
	cortos_printf("stack-pointer = 0x%x\n", t->stack_pointer);
	cortos_printf("fp = 0x%x\n", t->fp);
	cortos_printf("link-context = 0x%x.\n", t->link_context);
	cortos_printf("func = 0x%x.\n", t->func);
	cortos_printf("arg  = 0x%x.\n", t->func_arg);

	/*
	cortos_printf("y-register = 0x%x.\n", t->y);
	cortos_printf("fsr = 0x%x.\n", t->fsr);

	int I;
	for(I = 0; I < 8; I++)
		cortos_printf("g%d = 0x%x.\n", I, t->g[I]);
	*/
	/*
	for(I = 0; I < 32; I++)
		cortos_printf("f%d = 0x%x.\n", I, t->f[I]);
	*/
}

void __ajit_context_init__(ajit_context_t* ctxt)
{
	ctxt->func    	    = 0;	
	ctxt->func_arg      = 0;	
	ctxt->stack_pointer = 0;
	ctxt->link_context  = 0;

	ctxt->pc  = 0;
	ctxt->y   = 0;
	ctxt->fsr = 0;

	int I;
	for(I = 0; I < 8; I++)
	{
		ctxt->g[I] = 0;
	}

	for(I = 0; I < 32; I++)
	{
		ctxt->f[I] = 0;
	}

}

