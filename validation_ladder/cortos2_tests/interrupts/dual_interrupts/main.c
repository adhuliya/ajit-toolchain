// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <cortos.h>

#define TIMERCOUNT 100
#define COUNT TIMERCOUNT
#define TIMERINITVAL ((COUNT << 1) | 1)

volatile int volatile serial_interrupt_counter = 0;
volatile int volatile timer_interrupt_counter = 0;

void my_serial_interrupt_handler()
{
	uint8_t c = __ajit_read_serial_rx_register_via_vmap__();
	serial_interrupt_counter++;
	cortos_printf ("serial_interrupt_handler: read %c, timer_interrupt_counter=%d.\n", 
					c, 
					timer_interrupt_counter);
}

void my_timer_interrupt_handler()
{
	// clear timer control register.
	__ajit_write_timer_control_register_via_vmap__ (0x0);

	timer_interrupt_counter++;
	//cortos_printf ("timer_interrupt_handler: serial_interrupt_counter=%d.\n", serial_interrupt_counter);

	// reenable the timer..
	__ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	
}

void setup ()
{
	// enable serial 0 device..  enable_tx, enable_rx, enable_interrupts	
	__ajit_serial_configure_via_vmap__ (1, 1, 1);
	// set baud rate.
	__ajit_serial_set_baudrate_via_vmap__ (115200, CLK_FREQUENCY);
	// bring uart out of reset.
	__ajit_serial_set_uart_reset_via_vmap__ (0);

	cortos_printf ("enabled serial\n");

	// enable interrupt controller for the current thread.
	enableInterruptControllerAndAllInterrupts(0,0);

	// enable the timer, right away..
	__ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	

}

int main () 
{
	setup();
	cortos_printf("Starting\n");

	// infinite loop
	while(1)
	{
	}

	return(0);
}

