#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ajit_access_routines.h>
volatile int* volatile mutex_address = 0x40070000;

void enable_serial()
{
	*mutex_address = 1;

        // enable the serial device.
        __ajit_write_serial_control_register__ ( TX_ENABLE );
}

