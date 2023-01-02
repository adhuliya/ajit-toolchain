#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include <ajit_access_routines.h>
#include <ajit_context.h>

#define STACK_SIZE_IN_BYTES (8*1024)
uint8_t stack_0[STACK_SIZE_IN_BYTES];
uint8_t stack_1[STACK_SIZE_IN_BYTES];

void func_0(void*);

volatile int volatile  x = 0;
ajit_context_t context_0 __attribute__ ((aligned(8))) ;
ajit_context_t *cp_0 = &context_0;

ajit_context_t context_1 __attribute__ ((aligned(8))) ;
ajit_context_t *cp_1 = &context_1;

int main(void) {

   volatile int volatile counter = 0;

   __ajit_context_init__(cp_0);

   __cortos_enable_serial();

   cortos_printf("starting\n");

   counter++;
   cortos_printf("%d. x=%d *\n", counter, x);

   __ajit_getcontext__ (cp_0);
   if(x == 0)
   {
     __ajit_getcontext__ (cp_1);
     counter++;
     cortos_printf("%d. x=%d **\n", counter, x);
   }

   if(x > 2)
   {
	   counter++;
	   cortos_printf("%d. x=%d ***\n", counter, x);
   }
   else
   {
	  counter++;
	  cortos_printf("%d. x=%d ****\n", counter, x);

	  if(x == 0)
	  {
	  	__ajit_context_set_stack__(cp_0, &stack_0, STACK_SIZE_IN_BYTES);
	  	__ajit_context_set_link__(cp_0, cp_1);
	  	__ajit_makecontext__ (cp_0, &func_0, &x);
	  }

	  __ajit_setcontext__(cp_0);
   }

   cortos_printf("%d. x=%d **** *\n", counter, x);
   return(0);
}


void func_0(void* px) {
	uint32_t sp;
	 __AJIT_GET_IU_REGISTER(14,sp);
	cortos_printf("func_0 sp=0x%x.\n", sp);

	*((int*) px) += 1;
	cortos_printf("in func_0, set x = %d.\n", *((int*) px) );
}


