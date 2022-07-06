#include <stdio.h>
#include <stdint.h>
#include <ajit_access_routines.h>
#include <ajit_context.h>

int __ajit_swapcontext__ (ajit_context_t *__restrict __oucp, const ajit_context_t *__restrict __ucp)
{
	__ajit_getcontext__(__oucp);
	__ajit_setcontext__(__ucp);
}


void __ajit_print_context__ (ajit_context_t* t)
{

#ifdef EE_PRINTF_AVAILABLE
	ee_printf("psr = 0x%x.\n", t->psr);
	ee_printf("wim = 0x%x.\n", t->wim);
	ee_printf("tbr = 0x%x.\n", t->tbr);
	ee_printf("y   = 0x%x.\n", t->y);
	ee_printf("fsr = 0x%x.\n", t->fsr);

	int I;
	for(I = 0; I < 8; I++)
		ee_printf("g%d = 0x%x.\n", I, t->g[I]);

	for(I = 0; I < 16*8; I++)
		ee_printf("r[%d] = 0x%x.\n", I, t->r[I]);

	for(I = 0; I < 32; I++)
		ee_printf("f%d = 0x%x.\n", I, t->f[I]);
#endif

}
