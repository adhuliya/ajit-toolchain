#include<stdio.h>
#include <stdint.h>
#include "printf.h"
#include "ajit_access_routines.h"
#include "core_portme.h"
#include <math.h>


int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE );

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
		printf_("mp_printf: %f.\n", X);

		X = X * 2.0;
	}

	X=1.0;
	for(I = 0; I < 32; I++)
	{
		ee_printf("ee_printf: %f.\n", X);
		printf_("mp_printf: %f.\n", X);

		X = X * 0.1;
	}
}

