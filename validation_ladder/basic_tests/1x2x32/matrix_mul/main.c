#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "defs.h"

extern volatile int A[ORDER][ORDER];
extern volatile int B[ORDER][ORDER];
extern volatile int P[ORDER][ORDER];
extern volatile int mutex_var;

volatile int done_01 = 0;

volatile int init_done_00 = 0;
volatile int init_done_01 = 0;

void mulBlock (int S, int F);
void mulSelBlock (int select_odds);

void enable_serial()
{
	// enable the serial device.
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE | RX_INTR_ENABLE );
	ee_printf("enabled serial.\n"); 
}





void main_00 () 
{

	// initialize the mutex...  
	mutex_var = 0;

	initMatrices(0, (ORDER/2)-1);
	init_done_00 = 1;

	while(!init_done_01)
	{
	}

	uint32_t start_time = ajit_barebones_clock();
	// mulBlock(0, (ORDER/2)-1);
	mulSelBlock(0);
	uint32_t end_time   = ajit_barebones_clock();

	while(1)
	{
		if(done_01)
			break;
	}

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

	volatile int mutex_ptr = (int) &mutex_var;
	acquire_mutex_using_swap(mutex_ptr);
	ee_printf("main_00: start_time=%d, end_time=%d, elapsed=%d\n", 
				start_time, end_time, end_time-start_time);
	release_mutex_using_swap(mutex_ptr);

}



void main_01 () 
{
	initMatrices((ORDER/2), ORDER-1);
	init_done_01 = 1;

	while(!init_done_00)
	{
	}

	uint32_t start_time = ajit_barebones_clock();
	//mulBlock(ORDER/2, ORDER-1);
	mulSelBlock(1);
	uint32_t end_time   = ajit_barebones_clock();

	done_01 = 1;

	volatile int mutex_ptr = (int) &mutex_var;
	acquire_mutex_using_swap(mutex_ptr);
	ee_printf("main_01: start_time=%d, end_time=%d, elapsed=%d\n", 
				start_time, end_time, end_time-start_time);
	release_mutex_using_swap(mutex_ptr);
}

