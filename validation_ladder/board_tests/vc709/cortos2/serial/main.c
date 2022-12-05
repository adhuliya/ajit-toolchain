#include<stdio.h>
#include <stdint.h>
#include "printf.h"
#include "ajit_access_routines.h"
#include "core_portme.h"
#include <math.h>


void setup_uart()
{
#ifdef SERIAL_ADAPTER_CAN_CONFIGURE__UART
	__ajit_serial_set_uart_reset__(1);
	__ajit_serial_set_baudrate__(115200, CLK_FREQUENCY);
	__ajit_serial_set_uart_reset__(0);
#endif
	__ajit_write_serial_control_register__ ( TX_ENABLE );

}


int main()
{
	int32_t I;
	for(I = -32; I < 32; I++)
	{
		ee_printf("ee_printf: %d.\n", I);
		printf_("mp_printf: %d.\n", I);
	}	

	int64_t J;
	for(J = -32; J < 32; J++)
	{
		ee_printf("ee_printf: %d.\n", J);
		printf_("mp_printf: %d.\n", J);
	}

	double X=1.0;
	for(I = 0; I < 32; I++)
	{
		ee_printf("ee_printf: %f.\n", X);
		printf_("mp_printf: %F.\n", X);

		X = X * 2.0;
	}

	X=1.0;
	for(I = 0; I < 32; I++)
	{
		ee_printf("ee_printf: %f.\n", X);
		printf_("mp_printf: %F.\n", X);

		X = X * 0.1;
	}
}

