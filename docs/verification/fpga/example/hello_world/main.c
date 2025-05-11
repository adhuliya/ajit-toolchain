#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include <ajit_access_routines.h>

volatile int volatile start_1 = 0;
volatile int volatile done_0  = 0;

#define MAX_COUNT 1024

void setup()
{
	__ajit_serial_configure__(1,0,0);
	__ajit_serial_set_baudrate__ (115200, CLK_FREQUENCY);
	__ajit_serial_set_uart_reset__ (0);
}

void main_00 () 
{

	int counter = 0;

	uint64_t t0 = __ajit_get_clock_time ();
	while(1)
	{
		counter++;

		start_1 = 1;		
		while (start_1);

		if(counter == MAX_COUNT)
			break;
	}
	uint64_t t1 = __ajit_get_clock_time ();

	start_1 = 1;		
	cortos_printf("Done 0: counter=%d, t1 - t0 = %d\n", counter, (uint32_t) (t1 - t0));

}

void main_10 () 
{
	int counter = 0;

	uint64_t t0 = __ajit_get_clock_time ();
	while(1)
	{

		counter++;

		while(!start_1);

		start_1 = 0;
	
		if(counter == MAX_COUNT)
			break;	

	}
	uint64_t t1 = __ajit_get_clock_time ();

	cortos_printf("Done 1: counter=%d, t1 - t0 = %d\n", counter, (uint32_t) (t1 - t0));
}

