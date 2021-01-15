#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

#define SIZE 1024
int  a[SIZE];

extern int f0, f1, f2, f3;
extern int ok_flag[4];

int __enable_serial()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	return(0);
}

int march_test(int Offset)
{
	int I;
	int err = 0;
	for (I=Offset; I < SIZE; I +=4)
	{
		a[I]=I;
	}
	for (I=Offset; I < SIZE; I +=4)
	{
		if(a[I] != I)
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
				ee_printf("\na[%u] = %u\n", I, a[I]);
			}
#endif
			break;
		}
	}
}
