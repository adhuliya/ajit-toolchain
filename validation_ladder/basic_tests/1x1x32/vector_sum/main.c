#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "defs.h"
extern volatile int C[ORDER];
void initVectors();
void vectorSum ();

void enable_serial()
{
	// enable the serial device.
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE | RX_INTR_ENABLE );
	ee_printf("enabled serial.\n"); 
}

void main () 
{
	int I;
	initVectors();

	uint32_t start_time = ajit_barebones_clock();
	for(I = 0; I < 1024; I++)
	{
		vectorSum();
	}
	uint32_t end_time   = ajit_barebones_clock();

	for(I = 0; I < ORDER; I++)
	{
		if(C[I] != 2*I)
		{
			ee_printf("Error: C[%d]=%d   expected %d\n", I, C[I], 2*I);
		}
	}

	ee_printf("main: start_time=%d, end_time=%d, elapsed=%d\n", 
				start_time, end_time, end_time-start_time);

}
