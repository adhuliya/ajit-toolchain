#include<stdio.h>
#include <stdint.h>
#include "core_portme.h"
#include "ajit_access_routines.h"

int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	ee_printf("hello world\n");
	return(0);
}

