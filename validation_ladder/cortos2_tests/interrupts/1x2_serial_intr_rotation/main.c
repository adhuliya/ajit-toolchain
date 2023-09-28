// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <cortos.h>

volatile int volatile serial_interrupt_counter = 0;
volatile int volatile exit_flag  = 0;
volatile int volatile i_count[2];

volatile char volatile buffer[1024];

void my_serial_interrupt_handler()
{
	uint8_t core_id, thread_id;
	ajit_get_core_and_thread_id(&core_id, &thread_id);

	i_count[thread_id] += 1;
	
	uint8_t c = __ajit_read_serial_rx_register_via_vmap__();

	if(serial_interrupt_counter < 1022)
	{
		buffer[serial_interrupt_counter] = c;
		buffer[serial_interrupt_counter+1]= 0;
	}

	serial_interrupt_counter++;

	if((c == 'q') || (serial_interrupt_counter == 1022))
		exit_flag = 1;

	// rotate the interrupt handler to the other thread.
	disableInterrupt(core_id, thread_id, 12);
	enableInterrupt (core_id, (1 - thread_id), 12);	

}

void setup ()
{
	// enable serial 0 device..  enable_tx, enable_rx, enable_interrupts	
	__ajit_serial_configure_via_vmap__ (1, 1, 1);

	// set baud rate.
	//__ajit_serial_set_baudrate_via_vmap__ (115200, CLK_FREQUENCY);
	// bring uart out of reset.
	//__ajit_serial_set_uart_reset_via_vmap__ (0);

	cortos_printf ("enabled serial\n");

	i_count[0] = 0;
	i_count[1] = 0;

	// enable interrupt controller for thread 00
	enableInterruptControllerAndAllInterrupts(0,0);
	enableInterruptController(0,1);

	cortos_printf ("interrupt will be handled by (0,0)\n");
}

int main_00 () 
{
	cortos_printf("Starting thread 00\n");

	// infinite loop
	while(!exit_flag)
	{
	}

	cortos_printf("echo %s", buffer);
	cortos_printf("\ni_counts=%d, %d.\n", i_count[0], i_count[1]);
	return(0);
}

int main_01  ()
{
	cortos_printf("Starting thread 01\n");
	while(!exit_flag)
	{
	}

	return(0);

}

