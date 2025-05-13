#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <setjmp.h>
#include <cortos.h>

#include "ajit_access_routines.h"

int fp_cmp(double a, double b) {return(a < b);}

void setup_uart()
{
	__ajit_serial_set_uart_reset__(1);
	__ajit_serial_set_baudrate__(115200, CLK_FREQUENCY);
	__ajit_serial_set_uart_reset__(0);

	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE );
}


