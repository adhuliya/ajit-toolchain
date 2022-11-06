#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>

void coroutine_yield(int active_context);

void coroutine_0 (void* ptr)
{
	static int I=0;
	cortos_printf("C0: %d.\n", I);
	I++;
	coroutine_yield(0);
}

void coroutine_1 (void* ptr)
{
	static int I=0;
	cortos_printf("C1: %d.\n", I);
	I++;
	coroutine_yield(1);
}
