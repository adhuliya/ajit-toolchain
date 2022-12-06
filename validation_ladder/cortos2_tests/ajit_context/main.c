#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include <ajit_access_routines.h>
#include <ajit_context.h>

void func_0(void*);
void func_1(void*);

void foo();

int  x = 0;
int  y = 0;
volatile int volatile flag = 0;

ajit_context_t context_0 __attribute__ ((aligned(8))) ;
ajit_context_t context_1 __attribute__ ((aligned(8))) ;

ajit_context_t *cp_0 = &context_0;
ajit_context_t *cp_1 = &context_1;

int main(void) {
   __ajit_context_init__(cp_0);
   __ajit_context_init__(cp_1);

   __cortos_enable_serial();

   cortos_printf("starting\n");
   __ajit_makecontext__ (cp_0, &func_0, &x);
   cortos_printf("made context cp_0\n");
   if(x > 0)
   {
	   cortos_printf("x=%d!\n", x);
   }
   else
   {
	   __ajit_makecontext__ (cp_1, &func_1, &y);
	   if(y > 0) 
	   {
		   cortos_printf("y=%d!\n", y);
	   }
	   else
	   {
		   cortos_printf("made context cp_1\n");
		   __ajit_context_set_stack__(cp_0, 0x40010000, 16*1024);
		   __ajit_context_set_stack__(cp_1, 0x40020000, 16*1024);

		  __ajit_context_set_link__(cp_0, cp_1);
		  if(x == 0)
		  {
		   	__ajit_context_set_link__(cp_1, cp_0);
		  }

		   // continue from cp_0...  will call func_0, then
		   // switch to cp_1 which will call func_1.. which will
		   // switch to cp_0 which will call func_...  etc.
		   cortos_printf("setcontext(cp_0)\n");
		   __ajit_setcontext__(cp_0);
	   }
   }
		  
   // clear and start afresh..
   __ajit_context_init__(cp_0);
   __ajit_context_init__(cp_1);


   __ajit_makecontext__ (cp_0, &func_0, &x);
   cortos_printf("x=%d.\n", x);
   if(x == 2)
   {
	__ajit_setcontext__(cp_0);
   }
   
   __ajit_makecontext__ (cp_1, &func_1, &y);
   cortos_printf("y=%d.\n", y);
    if(y == 2)
    {
	cortos_printf("swapcontext(cp_0, cp_1)\n");
	__ajit_swapcontext__(cp_0, cp_1);
    }
   

   __ajit_context_init__(cp_0);
   __ajit_getcontext__ (cp_0);
   cortos_printf("return-point of getcontext(cp_0): x=%d\n", x);
   if(x == 3)
   {
	foo();
   }

   return(1);

}

void foo()
{
	x++;
	__ajit_setcontext__(cp_0);
} 


void func_0(void* px) {
	uint32_t sp;
	 __AJIT_GET_IU_REGISTER(14,sp);
	cortos_printf("func_0 sp=0x%x.\n", sp);

	*((int*) px) += 1;
	cortos_printf("in func_0, set x = %d.\n", *((int*) px) );
	int v = *((int*) px);
	if (v > 1)
	{
		cortos_printf("in func_0, detach link from cp_1 -> cp_0\n");
		__ajit_context_set_link__(cp_1, NULL);
	}
}

void func_1(void* py) {
	*((int*)py) += 1;
	int v = *((int*) py);
	cortos_printf("in func_1, set y = %d.\n", v);
}

