#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int done_00 = 0;
int done_01 = 0;

int R00 = 0;
int R01 = 1;

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

	enableInterruptControllerAndAllInterrupts(core_id, thread_id);
	ee_printf("enabled interrupts for (%d, %d)\n", core_id, thread_id);

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
	ee_printf("enabled interrupts for (%d, %d)\n", core_id, 1-thread_id);
}


void generic_interrupt_handler()
{
	disable_interrupts();

	uint8_t rx = __ajit_read_serial_rx_register__();
	ee_printf("entered interrupt handler (serial=%d).\n",  rx);


	uint8_t core_id, thread_id;
	ajit_get_core_and_thread_id(&core_id, &thread_id);
	if(thread_id == 0)
		ee_printf("Hello world from %d%d R00=%d.\n", core_id, thread_id, R00);
	else
		ee_printf("Hello world from %d%d R01=%d.\n", core_id, thread_id, R01);

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
	while(1)
	{

		int I;
		for(I = 0; I < 16; I++)
		{
			R00 = R00 + rsum(I);
		}
		
		if(done_00 && done_01)
			break;
	}
}

void main_01 () 
{

	while(1)
	{
		int I;
		for(I = 0; I < 16; I++)
		{
			R01 = R01 + rsum(I);
		}
		
		if(done_00 && done_01)
			break;
	}
}

