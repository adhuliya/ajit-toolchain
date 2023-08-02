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

void __ajit_context_set_stack__(ajit_context_t* ctxt, uint32_t stack_base_addr, uint32_t stack_size)
{
	uint32_t stack_pointer = ((stack_base_addr + stack_size) & 0xfffffff0) - 96;
	ctxt->stack_pointer = stack_pointer;
	ctxt->stack_size_in_bytes = stack_size;
}

void __ajit_context_set_link__ (ajit_context_t* ctxt, ajit_context_t* link)
{
	ctxt->uc_link = link;
}

void __ajit_makecontext__ (ajit_context_t *__ucp, void (*__func) (void*), void* arg)
{
	__ucp->func = (uint32_t) __func;
	__ucp->func_arg = (uint32_t) arg;
}


void __ajit_print_mcontext__ (ajit_context_t* t)
{
	cortos_printf("y-register = 0x%x.\n", t->mctxt.y);
	cortos_printf("fsr = 0x%x.\n", t->mctxt.fsr);

	int I;
	for(I = 0; I < 8; I++)
		cortos_printf("g%d = 0x%x.\n", I, t->mctxt.g[I]);

	for(I = 0; I < 8; I++)
		cortos_printf("l%d = 0x%x.\n", I, t->mctxt.locals[I]);

	for(I = 0; I < 8; I++)
		cortos_printf("i%d = 0x%x.\n", I, t->mctxt.ins[I]);

	for(I = 0; I < 32; I++)
		cortos_printf("f%d = 0x%x.\n", I, t->mctxt.f[I]);
}

void __ajit_print_context__ (ajit_context_t* t)
{
	cortos_printf("func = 0x%x, arg = 0x%x, link = 0x%x, stack = 0x%x\n",
				t->func, t->func_arg, (uint32_t) t->uc_link, t->stack_pointer);
	__ajit_print_mcontext__ (t); 
}

void __ajit_context_init__(ajit_context_t* ctxt)
{
	ctxt->func    = 0;	
	ctxt->uc_link = NULL;	
	ctxt->stack_pointer = 0;
	ctxt->stack_size_in_bytes = 0;
}

