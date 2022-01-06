#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "defs.h"

extern volatile int A[ORDER][ORDER];
extern volatile int B[ORDER][ORDER];
extern volatile int P[ORDER][ORDER];
extern volatile int mutex_var;

void mulBlock (int S, int F);

void enable_serial()
{
	// enable the serial device.
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE | RX_INTR_ENABLE );
	ee_printf("enabled serial.\n"); 
}

void main () 
{

	// initialize the mutex...  
	mutex_var = 0;

	initMatrices(0, ORDER-1);

	uint32_t start_time = ajit_barebones_clock();
	mulBlock(0, ORDER-1);
	uint32_t end_time   = ajit_barebones_clock();

	// print P;
	int I, J;
	for(I = 0; I < ORDER; I++)
	{
		for(J = 0; J < ORDER; J++)
		{
			if(P[I][J] != ORDER)
				ee_printf("Error: P[%d][%d]=%d   expected %d\n", I, J, P[I][J], ORDER);
		}
	}

	ee_printf("main: start_time=%d, end_time=%d, elapsed=%d\n", 
				start_time, end_time, end_time-start_time);

}
