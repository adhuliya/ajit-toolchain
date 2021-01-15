#include <stdint.h>
#include <stdlib.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

#define SIZE 256
int  a0[SIZE];
int  a1[SIZE];
int  a2[SIZE];
int  a3[SIZE];

extern int f0, f1, f2, f3;
extern int ok_flag[4];

int __enable_serial()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	return(0);
}

int march_test(int CPUID)
{
	
	int* ptr  = NULL;
	if(CPUID == 0) ptr = (int*) a0;
	if(CPUID == 1) ptr = (int*) a1;
	if(CPUID == 2) ptr = (int*) a2;
	if(CPUID == 3) ptr = (int*) a3;
	int I;
	int err = 0;
	for (I=0; I < SIZE; I ++)
	{
		*(ptr+I)=I;
	}
	for (I=0; I < SIZE; I ++)
	{
		if(*(ptr+I) != I)
			err = 1;
	}

	return(err);
}

void print_vals ()
{

	__enable_serial();

				
	while(1)
	{
		if(f0 && f1 && f2 && f3)
		//if(f0)
		{

			ee_printf("\nok-flags: %d %d %d %d\n", ok_flag[0], ok_flag[1], ok_flag[2], ok_flag[3]);
#ifdef PRINTVERBOSE
			int I;
			for(I=0; I< SIZE; I++)
			{
				ee_printf("\na0[%u] = %u\n", I, a0[I]);
				ee_printf("\na1[%u] = %u\n", I, a1[I]);
				ee_printf("\na2[%u] = %u\n", I, a2[I]);
				ee_printf("\na3[%u] = %u\n", I, a3[I]);
			}
#endif
			break;
		}
	}
}
