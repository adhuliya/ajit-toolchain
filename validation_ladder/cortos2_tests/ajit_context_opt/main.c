#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include <ajit_access_routines.h>
#include <ajit_context.h>

#define STACK_SIZE_IN_BYTES (8*1024)
volatile uint32_t stack_0[STACK_SIZE_IN_BYTES/4];
volatile uint32_t stack_1[STACK_SIZE_IN_BYTES/4];

volatile ajit_context_t context_0 __attribute__ ((aligned(8))) ;
volatile ajit_context_t *cp_0 = &context_0;

volatile ajit_context_t context_1 __attribute__ ((aligned(8))) ;
volatile ajit_context_t *cp_1 = &context_1;

volatile ajit_context_t context_2 __attribute__ ((aligned(8))) ;
volatile ajit_context_t *cp_2 = &context_1;

volatile int volatile x = 0;
volatile int volatile done_flag = 0;

void foo (int id)
{
	cortos_printf("foo [%d]: 0x%x, 0x%x\n", id, cp_0, cp_1);
}

void coroutine(void* px) {

        uint32_t sp, psr;
	 __AJIT_GET_IU_REGISTER(14,sp);
	 __AJIT_GET_PSR(psr);
	x++;
	cortos_printf("coroutine* (psr=0x%x, sp=0x%x): x=%d %d (ptr=0x%x)\n", psr, sp, x, *((int*) px),
							(uint32_t) px);
   
	if(!done_flag)
	{
		cortos_printf("setcontext to cp_0 (0x%x)\n", cp_0);
   		__ajit_print_context__ (cp_0);
		__ajit_setcontext__ (cp_0);
	}
}

void coroutine_0(void* px) {
	static int c = 0;

        uint32_t sp, psr;

	 __AJIT_GET_IU_REGISTER(14,sp);
	 __AJIT_GET_PSR(psr);
	x++;
	cortos_printf("coroutine_0* (psr=0x%x, sp=0x%x): x=%d %d (ptr=0x%x)\n", psr, sp, x, *((int*) px),
							(uint32_t) px);

   	__ajit_context_set_func_and_arg__ (cp_0, NULL, NULL);

	cortos_printf("swapcontext [0] from cp_0 (0x%x) to cp_1 (0x%x)\n", cp_0, cp_1);
	__ajit_swapcontext__ (cp_0, 0x0, cp_1);

	 __AJIT_GET_IU_REGISTER(14,sp);
	 __AJIT_GET_PSR(psr);
	x++;
	cortos_printf("coroutine_0** (psr=0x%x, sp=0x%x): x=%d %d (ptr=0x%x)\n", psr, sp, x, *((int*) px),
							(uint32_t) px);
	cortos_printf("swapcontext [1] from cp_0 (0x%x) to cp_1 (0x%x)\n", cp_0, cp_1);

	done_flag= 1;
	__ajit_swapcontext__ (cp_0, 0x0, cp_1);
}

int main(void) {

   volatile int volatile counter = 0; 
   uint32_t stack_pointer_0 = ((uint32_t) &stack_0) + STACK_SIZE_IN_BYTES - 96;
   uint32_t stack_pointer_1 = ((uint32_t) &stack_1) + STACK_SIZE_IN_BYTES - 96;

   __cortos_enable_serial();

   uint32_t sp;
   __AJIT_GET_IU_REGISTER(14,sp);
   cortos_printf ("cp_0 = 0x%x, cp_1 = 0x%x, sp=0x%x,  sp_0=0x%x, sp_1=0x%x\n", 
					cp_0, cp_1, sp, stack_pointer_0, stack_pointer_1);

   if(x == 0)
   {
	  cortos_printf("x==0, init cp_0\n");
   	__ajit_context_init__(cp_0);
   	__ajit_context_set_func_and_arg__ (cp_0, (uint32_t) coroutine_0, (uint32_t) &x);
   	__ajit_getcontext__ (cp_0, stack_pointer_0);
   }

   cortos_printf ("after getcontext (cp_0), cp_0 is\n");
   __ajit_print_context__ (cp_0);


   foo(0);

   __AJIT_GET_IU_REGISTER(14,sp);
   cortos_printf("return from cp_0 (current stack=0x%x)\n", sp);

   if( x == 0)
   {
	  cortos_printf("x==0, init cp_1\n");
     __ajit_context_init__(cp_1);
     __ajit_context_set_func_and_arg__ (cp_1, (uint32_t) coroutine, (uint32_t) &x);
     __ajit_getcontext__ (cp_1, stack_pointer_1);
   }

   cortos_printf ("after getcontext (cp_1), cp_1 is\n");
   __ajit_print_context__ (cp_1);

   if(x == 8)
   { 
	cortos_printf("done\n");
	return;
   }
	
   foo(1);

   if(!done_flag)
   {
   	cortos_printf("setcontext to cp_1 (0x%x)\n", cp_1);
   	__ajit_setcontext__ (cp_1);
   }

   cortos_printf("done!\n");

   return(0);
}


