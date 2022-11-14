#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <ajit_context.h>
#include <data_struct.h>

void coroutine_yield(int active_context);

void coroutine_0 (void* ptr)
{
	static int I=0;
	uint32_t sp;
	 __AJIT_GET_IU_REGISTER(14,sp);
	cortos_printf("C0 (sp=0x%x): %d.\n", sp, I);
	I++;
	coroutine_yield(0);
}

void coroutine_1 (void* ptr)
{
	static int I=0;

	uint32_t sp; __AJIT_GET_IU_REGISTER(14,sp);
	cortos_printf("C1 (sp=0x%x): %d.\n", sp, I);
	I++;
	coroutine_yield(1);
}
