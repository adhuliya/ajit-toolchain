#include <stdint.h>
#include "core_portme.h"
#include "ajit_access_routines.h"
int main(void)
{
	// initialize serial	
	__ajit_serial_configure__ (1,0,0);
	__ajit_serial_set_baudrate__(115200, CLK_FREQUENCY);
	__ajit_serial_set_uart_reset__(0);


	// Print
	ee_printf("Hello world!\n");
}


