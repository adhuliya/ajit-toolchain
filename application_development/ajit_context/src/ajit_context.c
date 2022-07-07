#include <stdio.h>
#include <stdint.h>
#include <ajit_access_routines.h>
#include <ajit_context.h>

/*
int __ajit_swapcontext__ (ajit_context_t *__restrict __oucp, const ajit_context_t *__restrict __ucp)
{
	__ajit_getcontext__(__oucp);
	__ajit_setcontext__(__ucp);
}
*/

void __ajit_context_set_stack__(ajit_context_t* ctxt, uint32_t stack_base_addr, uint32_t stack_size)
{
	uint32_t window_id = (ctxt->mctxt.psr & 0x7);

	// stack pointer is o6 in current window.
	uint32_t sp_index = (window_id * 16) + 14;
	ctxt->mctxt.r[sp_index] = (stack_base_addr + stack_size - 256);

	// frame pointer is i6 in current window.. ie o6 in
	// current_window + 1.
	uint32_t fp_index = (((window_id + 1) & 7) * 16) + 14;
	ctxt->mctxt.r[fp_index] = 0;
}

void __ajit_context_set_link__ (ajit_context_t* ctxt, ajit_context_t* link)
{
	ctxt->uc_link = link;
}

void __ajit_print_mcontext__ (ajit_context_t* t)
{

#ifdef EE_PRINTF_AVAILABLE
	ee_printf("psr = 0x%x.\n", t->mctxt.psr);
	ee_printf("wim = 0x%x.\n", t->mctxt.wim);
	ee_printf("tbr = 0x%x.\n", t->mctxt.tbr);
	ee_printf("y   = 0x%x.\n", t->mctxt.y);
	ee_printf("fsr = 0x%x.\n", t->mctxt.fsr);

	int I;
	for(I = 0; I < 8; I++)
		ee_printf("g%d = 0x%x.\n", I, t->mctxt.g[I]);

	for(I = 0; I < 16*8; I++)
		ee_printf("r[%d] = 0x%x.\n", I, t->mctxt.r[I]);

	for(I = 0; I < 32; I++)
		ee_printf("f%d = 0x%x.\n", I, t->mctxt.f[I]);
#endif

}

void __ajit_context_init__(ajit_context_t* ctxt)
{
	ctxt->func    = 0;	
	ctxt->uc_link = NULL;	
	ctxt->stack_base_addr = 0;
	ctxt->stack_size_in_bytes = 0;
}
