// Program for finding jitter using timer interrupts
#include <stdarg.h>
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

void bypass_printf(const char* fmt, ...)
{
  char print_buffer[256];
  va_list args;
  int n=0;
  va_start(args, fmt);
  ee_vsprintf(print_buffer, fmt, args);
  va_end(args);

  __ajit_serial_puts__(print_buffer,255);	

}


void my_serial_interrupt_handler()
{
	uint8_t c = __ajit_read_serial_rx_register__();

	buffer[serial_interrupt_counter] = c;
	buffer[serial_interrupt_counter+1]= 0;

	serial_interrupt_counter++;


	if((c == 'q') || (serial_interrupt_counter == 1022))
		exit_flag = 1;
}

void setup ()
{
	// enable serial 0 device..  enable_tx, enable_rx, enable_interrupts	
	__ajit_serial_configure__ (1, 1, 1);
	// set baud rate.
	__ajit_serial_set_baudrate__ (115200, CLK_FREQUENCY);
	// bring uart out of reset.
	__ajit_serial_set_uart_reset__ (0);

	bypass_printf ("enabled serial\n");

	// enable interrupt controller for the current thread.
	enableInterruptControllerAndAllInterrupts(0,0);
}

int main () 
{
	bypass_printf("Starting\n");

	// infinite loop
	while(!exit_flag)
	{
	}

	bypass_printf("echo %s\nDone.\n", buffer);
	__ajit_serial_puts__ (buffer, 1023);
	return(0);
}

