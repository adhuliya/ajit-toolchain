// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <cortos.h>
#include <ajit_context.h>
#include <ajit_coroutine.h>


volatile ajit_coroutine_t cr  __attribute__ ((aligned(8))) ;
volatile ajit_coroutine_t* pcr = (&cr);

void coroutine_0 (ajit_coroutine_t* cr_ptr);

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
	ajit_coroutine_create (STACK_SIZE_IN_BYTES, coroutine_0, (void*) pcr, pcr);
	CORTOS_DEBUG("coroutine_0 created 0x%x, 0x%x\n", coroutine_0, pcr);

	ajit_coroutine_run (pcr);
	CORTOS_DEBUG("ajit_coroutine_run (coroutine_0) returns\n");
	
	while(pcr->state != __COMPLETED)
	{
		CORTOS_DEBUG("calling ajit_coroutine_resume (coroutine_0)\n");
		ajit_coroutine_resume (pcr);
		CORTOS_DEBUG("ajit_coroutine_resume returns (coroutine_0)\n");
	}

	cortos_printf("done %d.\n", done_flag);
	return(0);
}

