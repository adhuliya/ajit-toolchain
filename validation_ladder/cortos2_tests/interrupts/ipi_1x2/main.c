// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <cortos.h>
#include <ajit_ipi.h>
#include <mp_printf.h>

volatile int volatile serial_interrupt_counter = 0;
volatile int volatile exit_flag  = 0;
volatile int volatile i_count[2];

volatile char volatile buffer[1024];
volatile uint8_t core_id   = 0;
volatile uint8_t thread_id = 0;

volatile int done_flag = 0;

void my_ipi_interrupt_handler()
{
	ajit_get_core_and_thread_id(&core_id, &thread_id);

	uint32_t mask, val;

	IpiMessage* ipimesg = (IpiMessage*) __ajit_get_ipi_message_pointer__ (core_id, thread_id);
	uint32_t mask_reg = __ajit_get_ipi_mask_register__ ();
	uint32_t val_reg  = __ajit_get_ipi_value_register__ ();

	uint32_t count_val = *((uint32_t*) ipimesg->pointer);

	/*
	 * no cortos_printf in ISR...
	 *
	mp_printf("Thread (%d,%d): received ipi [%d] mask_reg=0x%x, val_reg=0x%x.\n", 
				core_id, thread_id, count_val, mask_reg, val_reg);
	*/

	count_val++;
	*((uint32_t*) ipimesg->pointer) = count_val;
	__ajit_clear_ipi_interrupt__ (core_id, thread_id);
}

void setup ()
{
	// enable serial 0 device..  enable_tx, enable_rx, enable_interrupts	
	__ajit_serial_configure_via_vmap__ (1, 0, 0);
	// set baud rate.
	__ajit_serial_set_baudrate_via_vmap__ (115200, CLK_FREQUENCY);
	// bring uart out of reset.
	__ajit_serial_set_uart_reset_via_vmap__ (0);

	cortos_printf ("enabled serial\n");

	__ajit_set_ipi_value_register__ (0x0);
	__ajit_set_ipi_mask_register__ (0xffffffff);

	// enable interrupt controller for thread 01
	enableInterruptControllerAndAllInterrupts (0,1);

	cortos_printf ("ipi interrupt will be handled by (0,1)\n");
}

int main_00 () 
{
	cortos_printf("Starting thread 00\n");
	uint32_t i_counter = 0;

	
	IpiMessage* ipimesg = (IpiMessage*) __ajit_get_ipi_message_pointer__ (0,1);
	cortos_printf("00: ipimesg 0x%x, ->pointer = 0x%x\n", 
				(uint32_t) ipimesg,
				(uint32_t) ipimesg->pointer);

	while(1)
	{
		__ajit_set_ipi_interrupt__ (0,0,0,1, (void*) &i_counter);
		cortos_printf("00: sent ipi interrupt %d.\n", i_counter);	
		while(1)
		{
			IpiMessage* im = NULL;
			uint32_t mask, ival;

			__ajit_read_ipi_info__ (0,1, &mask, &ival, &im);
			cortos_printf("00: wait: ipimesg 0x%x, ->pointer = 0x%x\n", 
							(uint32_t) im,
								(uint32_t) im->pointer);


			// ipi interrupt cleared?
			if(!(mask & ival))
			{
				cortos_printf("00: [%d ? %d] ipi interrupt cleared by thread (0,1)\n", 
							i_counter,
							*((uint32_t*) im->pointer));
				break;
			}
		}

		if(i_counter == 10)
			break;
	}

	done_flag = 1;
	cortos_printf("00: done.\n");
	return(0);
}

int main_01  ()
{
	cortos_printf("Starting thread 01\n");
	while(!exit_flag)
	{
		if(done_flag)
			break;
	}
	cortos_printf("01: done.\n");
	return(0);
}

