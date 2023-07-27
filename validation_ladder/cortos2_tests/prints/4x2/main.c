#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <cortos.h>
#include "ajit_access_routines.h"

#define N 8

void setup_uart()
{
#ifdef SERIAL_ADAPTER_CAN_CONFIGURE__UART
	__ajit_serial_set_uart_reset__(1);
	__ajit_serial_set_baudrate__(115200, CLK_FREQUENCY);
	__ajit_serial_set_uart_reset__(0);
#endif
	__ajit_write_serial_control_register__ ( TX_ENABLE );

}


int pcore(int core_id, int thread_id)
{
	int32_t I;
	for(I = -N; I < N; I++)
	{
		cortos_printf("(%d,%d):int32: %d.\n", core_id, thread_id, I);
	}	

	int64_t J;
	for(J = -N; J < N; J++)
	{
		cortos_printf("(%d,%d):int64: %lld.\n", core_id, thread_id, J);
	}

	double X=1.0;
	for(I = 0; I < N; I++)
	{
		cortos_printf("(%d,%d):double: %f.\n", core_id, thread_id, X);

		X = X * 2.0;
	}

	X=1.0;
	for(I = 0; I < N; I++)
	{
		cortos_printf("(%d,%d):double: %lE\n", core_id, thread_id, X);
		X = X * 0.1;
	}
}

int main_00()
{
	pcore(0,0);
}

int main_01()
{
	pcore(0,1);
}

int main_10()
{
	pcore(1,0);
}

int main_11()
{
	pcore(1,1);
}

int main_20()
{
	pcore(2,0);
}

int main_21()
{
	pcore(2,1);
}

int main_30()
{
	pcore(3,0);
}

int main_31()
{
	pcore(3,1);
}
