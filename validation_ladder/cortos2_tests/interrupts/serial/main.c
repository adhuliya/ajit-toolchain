// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>

#define TIMERCOUNT 10000000
#define COUNT TIMERCOUNT
#define TIMERINITVAL ((COUNT << 1) | 1)

volatile int volatile serial_interrupt_counter = 0;
volatile int volatile exit_flag  = 0;

char buffer[1024];

void my_serial_interrupt_handler()
{
	uint8_t c = __ajit_read_serial_rx_register_via_vmap__();

	buffer[serial_interrupt_counter] = c;
	buffer[serial_interrupt_counter+1]= 0;

	serial_interrupt_counter++;

	//__ajit_serial_puts_via_vmap__ (buffer, 1023);

	if((c == 'q') || (serial_interrupt_counter == 1022))
		exit_flag = 1;
}

int main () 
{
	cortos_printf("Starting\n");

	// enable interrupt controller for the current thread.
	enableInterruptControllerAndAllInterrupts(0,0);

	// reenable the timer, right away..
	// __ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	


	// infinite loop
	while(!exit_flag)
	{
	}

	cortos_printf("echo %s", buffer);
	return(0);
}

