#include<stdio.h>
#include <stdint.h>
#include "printf.h"
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "mp_printf.h"
#include <math.h>


int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE );

	int32_t I;
	for(I = -32; I < 32; I++)
	{
		ee_printf("ee_printf:i32: %d.\n", I);
		mp_printf("mp_printf:i32: %d.\n", I);
	}	

	int64_t J;
	for(J = -32; J < 32; J++)
	{
		char buf[1024];
		sprintf(buf, "%lld", J);

		ee_printf("ee_printf:i64: %s.\n", buf);
		mp_printf("mp_printf:i64: %lld.\n", J);
	}

	double X=1.0;
	for(I = 0; I < 32; I++)
	{
		ee_printf("ee_printf:double: %f.\n", X);
		mp_printf("mp_printf:double: %f.\n", X);

		X = X * 2.0;
	}

	X=1.0;
	for(I = 0; I < 32; I++)
	{
		ee_printf("ee_printf:double: %16.12f.\n", X);
		mp_printf("mp_printf:double: %16.12f.\n", X);

		X = X * 0.1;
	}
}

