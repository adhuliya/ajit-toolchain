// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <cortos.h>
#include <ajit_coroutine.h>

#define STACK_SIZE_IN_BYTES 4096

volatile int __counter = 0;

void func (void* vcr)
{
	ajit_coroutine_t* cr = vcr;


	while(__counter < 8)
	{
		__counter++;

		cortos_printf("func* %d.\n", __counter);
		ajit_coroutine_yield(cr);

		__counter++;
		cortos_printf("func** %d.\n", __counter);
		ajit_coroutine_yield(cr);

		__counter++;
		cortos_printf("func*** %d.\n", __counter);
		ajit_coroutine_yield(cr);
	}

	__counter++;
	cortos_printf("func**** %d. (returns) \n", __counter);
	ajit_coroutine_return(cr);
}

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


volatile ajit_coroutine_t cr  __attribute__ ((aligned(8))) ;

int main () 
{
	ajit_coroutine_create (STACK_SIZE_IN_BYTES, (void*) func, (void*) &cr,  &cr);
	CORTOS_DEBUG("coroutine created 0x%x, 0x%x\n", func, &cr);

	ajit_coroutine_run ((&cr));
	CORTOS_DEBUG("ajit_coroutine_run returns\n");

	while(cr.state != __COMPLETED)
	{
		CORTOS_DEBUG("calling ajit_coroutine_resume\n");
		ajit_coroutine_resume ((&cr));
		CORTOS_DEBUG("ajit_coroutine_resume returns\n");

	}

	cortos_printf("Done.\n");
	return(0);
}

