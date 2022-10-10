#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include <ajit_access_routines.h>

uint32_t global_storage_array[4*ORDER];

//
// Each thread does a series of writes  and reads 
// to and from memory (a crude march test). 
// 
//
volatile int volatile init_done 	= 0;
volatile int volatile write_done[] 	= {0,0,0,0};
volatile int volatile done[] 		= {0,0,0,0};
volatile int volatile _err_[] 		= {0,0,0,0};

volatile int volatile go_flag = 0;

void runMarch(int tid, int BASE, int SIZE, int IC)
{
	uint32_t I;
	for(I = 0; I < SIZE; I++)
	{
		uint32_t J = I + BASE;
		global_storage_array[J] = J + IC;
	}

	write_done[tid] = 1;

	for(I = 0; I < SIZE; I++)
	{
		uint32_t J = I + BASE;
		uint32_t V = global_storage_array[J];
		_err_[tid] = _err_[tid] | (V != (J + IC));
	}
	done[tid] = 1;
}


void setup ()
{
	// enable serial 0 device..  enable_tx, enable_rx, enable_interrupts	
	__ajit_serial_configure__ (1, 1, 1);
	// set baud rate.
	__ajit_serial_set_baudrate__ (115200, CLK_FREQUENCY);
	// bring uart out of reset.
	__ajit_serial_set_uart_reset__ (0);

	cortos_printf ("enabled serial\n");
}

void main_00 () 
{
	uint64_t t0 = cortos_get_clock_time();
	init_done = 1;
	int I;
	for(I = 0; I < NITERATIONS; I++)
		runMarch(0, 0, ORDER, I);


	while(1)
	{
		int all_done = 1;
		for(I = 0; I < 4; I++)
		{
			if(done[I] == 0)
			{
				all_done = 0;
				break;
			}
		}
		if(all_done)
			break;
	}
	uint64_t t1 = cortos_get_clock_time();

	for(I = 0; I < 4; I++)
	{
		if(_err_[I])
			cortos_printf("Error: on job %d.\n", I);
	}

	uint64_t delta_t = (t1 - t0);
	double e_time = ((double) delta_t) * 1000.0 / CLK_FREQUENCY;
	cortos_printf("All done: time taken = %f cycles (%f ms)\n", (double) delta_t, e_time);
}




void main_10 () 
{
	while(!init_done);
	int I;
	for(I = 0; I < NITERATIONS; I++)
		runMarch(1, ORDER, ORDER, I);
}

void main_20 () 
{
	while(!init_done);
	int I;
	for(I = 0; I < NITERATIONS; I++)
		runMarch(2, 2*ORDER, ORDER, I);
}

void main_30 () 
{
	while(!init_done);
	int I;
	for(I = 0; I < NITERATIONS; I++)
		runMarch(3, 3*ORDER, ORDER, I);
}

