// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <cortos.h>
#include <ajit_context.h>
#include <data_struct.h>

ajit_context_t main_context __attribute__ ((aligned(8))) ;

ajit_context_t context_0 __attribute__ ((aligned(8))) ;
ajit_context_t context_1 __attribute__ ((aligned(8))) ;

ajit_context_t *cp_0 = &context_0;
ajit_context_t *cp_1 = &context_1;
ajit_context_t *main_ctxt = &main_context;

CoroutineControl cp_0_ctrl;
CoroutineControl cp_1_ctrl;

extern uint32_t stack_0[1024];
extern uint32_t stack_1[1024];

void coroutine (void* ptr);

#define LOOPS 8

void setup ()
{
	// enable serial 0 device..  enable_tx, enable_rx, enable_interrupts	
	__ajit_serial_configure__ (1, 0, 0);
	// set baud rate.
	__ajit_serial_set_baudrate__ (115200, CLK_FREQUENCY);
	// bring uart out of reset.
	__ajit_serial_set_uart_reset__ (0);

	cortos_printf ("enabled serial\n");

}


int main () 
{

	cortos_printf("Starting\n");

	cp_0_ctrl.id = 0;
	cp_0_ctrl.context = cp_0;
	cp_0_ctrl.counter = 0;

	cp_1_ctrl.id = 1;
	cp_1_ctrl.context = cp_1;
	cp_1_ctrl.counter = 0;

   	__ajit_context_init__(cp_0);
   	__ajit_context_init__(cp_1);
	__ajit_context_init__(main_ctxt);

	cortos_printf("initialized three contexts: cp_0=0x%x, cp_1=0x%x, main=0x%x \n",
				((uint32_t) cp_0), ((uint32_t) cp_1), ((uint32_t) main_ctxt));

	// 
	// make context cp_0 which calls coroutine.. and links back to main_ctxt.
	//
	__ajit_getcontext__(cp_0);
	cortos_printf("make context 0\n");
	__ajit_context_set_stack__(cp_0, ((uint32_t) &stack_0), 4*1024);
	__ajit_context_set_link__(cp_0, main_ctxt);
	__ajit_makecontext__(cp_0, (void*) &coroutine, &cp_0_ctrl);

	// 
	// make context cp_1 which calls coroutine.. and links to cp_0
	//
	__ajit_getcontext__(cp_1);
	cortos_printf("make context 1\n");
	__ajit_context_set_stack__(cp_1, ((uint32_t) &stack_1), 4*1024);
	__ajit_context_set_link__(cp_1, cp_0);
	__ajit_makecontext__(cp_1, (void*) &coroutine, &cp_1_ctrl);
		

	int I;
	//
	// Do this several times...
	//
	// swap from main to cp_1..  This will set context to cp_1, then 
	// to cp_0, and back to main_ctxt.
	//
	for(I = 0; I < LOOPS; I++)
	{
		__ajit_swapcontext__(main_ctxt, cp_1);
	}

	//
	// you will get here after setcontext is applied to main_ctxt
	// enough times..
	//
	cortos_printf("Done.\n");
	return(0);
}

