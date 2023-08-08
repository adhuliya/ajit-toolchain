// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <cortos.h>
#include <ajit_context.h>
#include <data_struct.h>


volatile ajit_context_t volatile scheduler __attribute__ ((aligned(8))) ;
volatile ajit_context_t volatile cc  __attribute__ ((aligned(8))) ;

volatile ajit_context_t volatile *pscheduler = &scheduler;
volatile ajit_context_t volatile *pcc        = &cc;

extern uint32_t stack_0[1024];
extern uint32_t stack_1[1024];

CoroutineControl cc_ctrl;
void coroutine (CoroutineControl* pcc_ctrl);

#define LOOPS 4
volatile int n_calls = 0;
volatile int done_flag = 0;

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

	cortos_printf("Starting (pscheduler=0x%x, pcc=0x%x)\n", 
					(uint32_t) pscheduler,
					(uint32_t) pcc);
	cortos_printf ("pscheduler pointer address = 0x%x\n", (uint32_t) &pscheduler);

   	__ajit_context_init__(pscheduler);

   	__ajit_context_init__(pcc);
	__ajit_getcontext__ (pcc);
	__ajit_context_set_stack__(pcc, ((uint32_t) &stack_1), 4*1024);


	cc_ctrl.pcc = pcc;
	cc_ctrl.pscheduler = pscheduler;

	__ajit_getcontext__ (pscheduler);
	__ajit_context_set_stack__(pscheduler, ((uint32_t) &stack_0), 4*1024);
		
	cortos_printf("scheduler: got context [%d] pscheduler = 0x%x 0x%x\n", n_calls, 
									(uint32_t) pscheduler,
									(uint32_t) cc_ctrl.pscheduler);
	if(n_calls == 0)
	{
		//
		// The first time around, call the coroutine
		//
		cortos_printf ("call coroutine \n");
		coroutine (&cc_ctrl);
	}
	else if (!done_flag)
	{
		// 
		// second time onward, just setcontext to the
		// coroutine context to continue.
		//
		cortos_printf("scheduler: set cc-context [%d] = 0x%x (stack=0x%x)\n", 
						n_calls,  pcc, pcc->mctxt.outs[6]);
		__ajit_setcontext__ (pcc);
	}

	cortos_printf("Done.\n");
	return(0);
}

