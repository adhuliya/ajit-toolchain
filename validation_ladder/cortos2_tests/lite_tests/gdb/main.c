#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include <cortos.h>


void main_00 () 
{
	__ajit_serial_configure__(1,0,0);
	__ajit_serial_set_baudrate__ (115200, 80000000);
	__ajit_serial_set_uart_reset__ (0);
	
	//float f  = fp (0.1, 1.1);

	cortos_printf("Hello: 1\n");
	cortos_printf("Hello: 2\n");
	cortos_printf("Hello: 3\n");
	
	char buffer[256];

	sprintf(buffer,"Hello: 1\n");
	__ajit_serial_puts__(buffer,255);	

	sprintf(buffer,"Hello: 2\n");
	__ajit_serial_puts__(buffer,255);	

	sprintf(buffer,"Hello: 3\n");
	__ajit_serial_puts__(buffer,255);	

}

