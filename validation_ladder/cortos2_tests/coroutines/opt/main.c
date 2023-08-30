// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <cortos.h>
#include <ajit_context.h>
#include <coroutine.h>
#include <data_struct.h>

#define STACK_SIZE_IN_BYTES 4096


volatile ajit_context_t volatile scheduler __attribute__ ((aligned(8))) ;
volatile ajit_context_t volatile cc  __attribute__ ((aligned(8))) ;

volatile ajit_context_t volatile *pscheduler = &scheduler;
volatile ajit_context_t volatile *pcc        = &cc;


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

   	uint32_t* stack_0 = (uint32_t*) cortos_bget (STACK_SIZE_IN_BYTES);
   	uint32_t* stack_1 = (uint32_t*) cortos_bget (STACK_SIZE_IN_BYTES);

	cc_ctrl.pcc = pcc;
	cc_ctrl.pscheduler = pscheduler;

   	__ajit_context_init__(pcc);
	__ajit_getcontext__ (pcc);
	if(pcc->scratch[0] == 0)
	{
		__ajit_context_set_stack__(pcc, ((uint32_t) stack_1), STACK_SIZE_IN_BYTES);
		__ajit_context_set_link__ (pcc, pscheduler);
		__ajit_makecontext__ (pcc, coroutine, (void*) &cc_ctrl);
	}
	cortos_printf("returned from getcontext(pcc) [%d], pcc=0x%x pscheduler=0x%x\n",
				n_calls, pcc, pscheduler);
				


   	__ajit_context_init__(pscheduler);
	__ajit_getcontext__ (pscheduler);
	if(pscheduler->scratch[0] == 0)
	{
		//__ajit_context_set_stack__(pscheduler, ((uint32_t) stack_0), STACK_SIZE_IN_BYTES);
		pscheduler->scratch[0] = 1;
	}
	cortos_printf("scheduler: got context [%d] pscheduler = 0x%x 0x%x\n", 
									n_calls, 
									(uint32_t) pscheduler,
									(uint32_t) cc_ctrl.pscheduler);

	if(n_calls < LOOPS)
	{
		__ajit_setcontext__ (pcc);
	}
		
	cortos_printf("Done.\n");
	return(0);
}

