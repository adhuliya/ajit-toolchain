#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ajit_access_routines.h>

void enable_serial()
{
        // enable the serial device.
        __ajit_write_serial_control_register__ ( TX_ENABLE );
}

