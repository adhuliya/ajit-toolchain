#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <cortos.h>
#include "ajit_access_routines.h"


void setup_uart()
{
	__ajit_serial_set_uart_reset__(1);
	__ajit_serial_set_baudrate__(115200, CLK_FREQUENCY);
	__ajit_serial_set_uart_reset__(0);
	__ajit_write_serial_control_register__ ( TX_ENABLE );

	*((int*) 0xffff3204) = 0x68686868;
}


int pcore(int core_id, int thread_id)
{
	int32_t I;
	for(I = -32; I < 32; I++)
	{
		cortos_printf("(%d,%d):int32: %d.\n", core_id, thread_id, I);
	}	

	int64_t J;
	for(J = -32; J < 32; J++)
	{
		cortos_printf("(%d,%d):int64: %lld.\n", core_id, thread_id, J);
	}

	double X=1.0;
	for(I = 0; I < 32; I++)
	{
		cortos_printf("(%d,%d):double: %f.\n", core_id, thread_id, X);

		X = X * 2.0;
	}

	X=1.0;
	for(I = 0; I < 32; I++)
	{
		cortos_printf("(%d,%d):double: %lE\n", core_id, thread_id, X);
		X = X * 0.1;
	}
}

void macros_test()
{
#define A 1
#define B 1

#if (A == B)
	cortos_printf("A==B\n");
#else
	cortos_printf("ERROR!\n");
#endif

#if (1)
	cortos_printf("Always\n");
#else
	cortos_printf("ERROR!\n");
#endif

#ifndef C 
#define C 2
#endif

#ifndef D 
#define D 3
#endif

#if (C!=D)
	cortos_printf("C!=D\n");
#endif

#if (C!=E)
	cortos_printf("C!=E\n");
#endif

#if (C==E)
	cortos_printf("C==E\n");
#endif

#if (F==E)
	cortos_printf("F==E\n");
#endif
	
#if (F!=E)
	cortos_printf("F!=E\n");
#endif
}

int main()
{
	macros_test();
	pcore(0,0);

	cortos_printf("Done.\n");
}

