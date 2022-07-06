#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include <ajit_context.h>

void func_0(void);
void func_1(void);

void foo(void*);

int  x = 0;
int  y = 0;
volatile int volatile flag = 0;

ajit_context_t context_0 __attribute__ ((aligned(8))) ;
ajit_context_t context_1 __attribute__ ((aligned(8))) ;

ajit_context_t *cp_0 = &context_0;
ajit_context_t *cp_1 = &context_1;

int main(void) {

    //__cortos_enable_serial();

    cortos_printf("starting\n");
    __ajit_getcontext__(cp_0);

  if (!x) {
    cortos_printf("getcontext cp_0 has been called: cp_0 follows\n");
    cortos_printf("---------------------------------------------------------\n");
    __ajit_print_context__(cp_0);
    cortos_printf("---------------------------------------------------------\n");
    func_0();
  }
  else if (!y) {
    func_1();
    cortos_printf("setcontext cp_0 has been called: cp_0 follows\n");
    cortos_printf("---------------------------------------------------------\n");
    __ajit_print_context__(cp_0);
    cortos_printf("---------------------------------------------------------\n");
  }
  else {
    func_1();
    cortos_printf("swapcontext cp_1 -> cp_0 has been called: cp_0 follows\n");
    cortos_printf("---------------------------------------------------------\n");
    __ajit_print_context__(cp_0);
    cortos_printf("---------------------------------------------------------\n");
    return(0);
  }

  __ajit_makecontext__(cp_1, &foo, (void*) &flag);
  cortos_printf("back in main after makecontext cp_1: flag (*0x%x)=%d. cp_1 follows\n", ((uint32_t) &flag), flag);
    cortos_printf("---------------------------------------------------------\n");
    __ajit_print_context__(cp_1);
    cortos_printf("---------------------------------------------------------\n");

  // switch context from cp_1 to cp_0..
  __ajit_swapcontext__(cp_1, cp_0);

}

void func_0(void) {

  x++;
  __ajit_setcontext__(cp_0);

}

void func_1(void) {
  y++;
}

void foo(void* flag)
{
  	cortos_printf("foo %d.\n", x);
	x++;
	*((int*) flag) = 1;
	__ajit_setcontext__(cp_1);
}
