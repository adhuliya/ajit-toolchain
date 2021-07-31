#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int main () 
{
	// enable the serial device.
	//   from ajit_access_routines...
	__ajit_write_serial_control_register__ ( TX_ENABLE );

	//
	// in core_portme...
	//
	ee_printf("Hello World!\n");

	return(0);
}

