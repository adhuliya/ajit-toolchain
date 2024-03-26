// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <device_addresses.h>
#include <ajit_mt_irc.h>
#include <ajit_ipi.h>
#include <mp_printf.h>
#include <cortos.h>

#define MAX_COUNT   4

uint32_t ipi_base_address = ADDR_INTERRUPT_CONTROLLER_IPI_BASE;
volatile uint32_t volatile  ipi_interrupt_counter = 0;


void my_ipi_interrupt_handler()
{
	uint8_t core_id, thread_id;
	ajit_get_core_and_thread_id (&core_id, &thread_id);	
	
	if((core_id != 0) || (thread_id != 1))
	{
		mp_printf ("--------isr error! wrong thread (%d,%d)------------\n", core_id, thread_id);
	}

	// get the interrupt message.	
	IpiMessage* mesg = __ajit_get_ipi_message_pointer__ (ipi_base_address,0,1);

	uint32_t v = *((uint32_t*) mesg->pointer);
	*((uint32_t*) mesg->pointer) = (v + 1);

	ipi_interrupt_counter++;
	__ajit_clear_ipi_interrupt__(ipi_base_address, 0,1);
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

	// enable interrupt controller for the thread (0,1).
	enableInterruptControllerAndAllInterrupts(0,1);
	cortos_printf ("enabled interrupt controller for thread (0,1) (all interrupts)\n");

	cortos_printf ("ipi base address = 0x%x\n", ipi_base_address);
	cortos_printf ("ipi swap mutex address = 0x%x\n", __AJIT_IPI_LOCK_ADDRESS(ipi_base_address));
	__ajit_ipi_init__(ipi_base_address);

	cortos_printf ("initialized ipi\n");

	// enable ipi interrupt for thread (0,1);
	__ajit_enable_ipi_interrupt__(ipi_base_address, 0, 1);
	cortos_printf ("enabled ipi to 0,1 (mask=0x%x, val=0x%x)\n",
				*((uint32_t*) ipi_base_address),
				*((uint32_t*) (ipi_base_address + 4))
			);

}

volatile uint32_t volatile counter = 0;

int main_00 () 
{
	cortos_printf("main_00 started.\n");


	IpiMessage* mesg = __ajit_get_ipi_message_pointer__ (ipi_base_address,0,1);
	mesg->source_core_id   = 0;
	mesg->source_thread_id = 0;
	mesg->dest_core_id     = 0;
	mesg->dest_thread_id   = 1;
	mesg->pointer          = (void*) &counter;

	cortos_printf("main_00:  mesg pointer = 0x%x\n", (uint32_t) mesg);
			
	// invoke interrupt from (0,0) to (0,1).
	while(counter < MAX_COUNT)
	{
		while(1) {	
			int status = __ajit_set_ipi_interrupt__ (ipi_base_address, 0,0,0,1, (void*) &counter); 
			if(status == 0)
			{
				cortos_printf ("main_00: set ipi interrupt to 0,1 (mask=0x%x, val=0x%x)\n",
						*((uint32_t*) ipi_base_address),
						*((uint32_t*) (ipi_base_address + 4))
				);
				break;
			}
			__ajit_sleep__ (64);
		}
	}

	cortos_printf("main_00 done, *mesg->pointer=%d.\n", *((uint32_t*) mesg->pointer));
	return(0);
}


int main_01 ()
{
	cortos_printf("main_01 started.\n");
	// Just spin waiting to get interrupted.
	while(1) {
		if(ipi_interrupt_counter >= MAX_COUNT)
			break;

		__ajit_sleep__ (64);
	}
	cortos_printf("main_01 done.\n");
	return(0);
}




