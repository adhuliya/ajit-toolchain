//Program for RPN calculator  using serial interrupts
#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int __enable_serial()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	return(0);
}

int __enable_serial_interrupt()
{
	__ajit_write_serial_control_register__ (TX_ENABLE | RX_ENABLE |RX_INTR_ENABLE);
	return(0);
}


// array and result.
uint32_t pA      = 0x50000;
uint32_t pB      = 0x51000;
uint32_t pRESULT = 0x52000;



int main () {

	__enable_serial();

	float* fpA = (float*) pA;
	float* fpB = (float*) pB;

	int I;
	for(I = 0; I < 16; I++)
	{
		fpA[I] = I;
		fpB[I] = I;
	}

	for(I = 0; I < 16; I++)
	{	
		dotP();
		ee_printf("dotP[%d]=%f.\n", I, *((float*) pRESULT));
	}

	return(0);
	
}
