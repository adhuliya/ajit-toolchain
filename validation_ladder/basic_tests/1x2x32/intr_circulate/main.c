#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int done_00 = 0;
int done_01 = 0;
int rsum (int N);

void enable_serial()
{
	// enable the serial device.
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE | RX_INTR_ENABLE );
	ee_printf("enabled serial.\n"); 
}


void enable_interrupts()
{
	uint8_t core_id, thread_id;
	ajit_get_core_and_thread_id(&core_id, &thread_id);

	ee_printf("enabled interrupts for (%d, %d)\n", core_id, thread_id);
	enableInterruptControllerAndAllInterrupts(core_id, thread_id);

}

void disable_interrupts()
{
	uint8_t core_id, thread_id;
	ajit_get_core_and_thread_id(&core_id, &thread_id);
	disableInterruptController(core_id,thread_id);	
	ee_printf("disabled interrupts for (%d, %d)\n", core_id, thread_id);
}

void rotate_interrupts()
{
	uint8_t core_id, thread_id;
	ajit_get_core_and_thread_id(&core_id, &thread_id);
	ee_printf("rotated interrupts for (%d, %d)\n", core_id, thread_id);
	enableInterruptControllerAndAllInterrupts(core_id, (1-thread_id));
}


void generic_interrupt_handler()
{
	disable_interrupts();

	uint8_t rx = __ajit_read_serial_rx_register__();
	ee_printf("entered interrupt handler (serial=%d).\n",  rx);


	uint8_t core_id, thread_id;
	ajit_get_core_and_thread_id(&core_id, &thread_id);
	ee_printf("Hello world from %d%d\n", core_id, thread_id);

	if(rx == 'q') 
	{
		if(thread_id == 0)
		{
			done_00 = 1;
			ee_printf("done_00 = 1");
		}
		else
		{
			ee_printf("done_01 = 1");
			done_01 = 1;
		}
	}

	rotate_interrupts();
}


void main_00 () 
{
	int C = 0;
	while(1)
	{
		C++;
		int R = C;

		int I;

		for(I = 0; I < 16; I++)
		{
			R = R + rsum(I);
		}
		ee_printf("main_00: R = %d\n", R);
		
		if(done_00 && done_01)
			break;
	}
}

void main_01 () 
{
	ee_printf("Entered 01\n");
	int C = 0;
	while(1)
	{
		C++;
		int R = C;

		int I;
		for(I = 0; I < 16; I++)
		{
			R = R + rsum(I);
		}
		
		ee_printf("main_01: R = %d\n", R);
		if(done_00 && done_01)
			break;
	}
}

