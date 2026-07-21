#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <cortos.h>
#include "ajit_access_routines.h"


volatile uint32_t volatile global_counter = 0;
volatile uint32_t volatile counter_00 = 0;
volatile uint32_t volatile counter_10 = 0;

volatile uint8_t* volatile lock_ptr = NULL;

volatile int volatile done_0  = 0;
volatile int volatile done_1  = 0;

void setup_uart()
{
	__ajit_serial_set_uart_reset__(1);
	__ajit_serial_set_baudrate__(115200, CLK_FREQUENCY);
	__ajit_serial_set_uart_reset__(0);
	__ajit_write_serial_control_register__ ( TX_ENABLE );

	// Reserve a lock..
	lock_ptr = cortos_reserveLock(0);
	cortos_printf("Core 00 reserved lock\n");
}


// increments private variable counter_00 and
// shared variable global_counter in the critical
// region.
int main_00()
{
	int I;

	uint64_t t0 = __ajit_get_clock_time();
	for(I = 0; I < 1024*1024; I++)
	{
		cortos_lock_acquire_buzy (lock_ptr);

		//---------  critical region starts -----------//
		counter_00++;
		global_counter++;
		//---------  critical region ends -----------//

		cortos_lock_release(lock_ptr);
		
	}
	uint64_t t1 = __ajit_get_clock_time();
	

	// signal done to other core (note: TSO)
	done_0 = 1;

	// Wait until both are done (note: cache coherence has snoop invalidate delay)
	while (!done_0 || !done_1);

	cortos_printf("Core-00 Done[Ticks=%lld], counter_00 = %d, global_counter=%d\n", 
				t1 - t0, counter_00, global_counter);

	return(0);
}

int main_10()
{

	uint64_t I;

	uint64_t t0 = __ajit_get_clock_time();
	for(I = 0; I < 1024*1024; I++)
	{
		cortos_lock_acquire_buzy (lock_ptr);

		//---------  critical region starts -----------//
		counter_10++;
		global_counter++;
		//---------  critical region ends  -----------//

		cortos_lock_release(lock_ptr);
		
	}
	uint64_t t1 = __ajit_get_clock_time();

	// signal done to other core (note: TSO)
	done_1 = 1;

	// Wait until both are done (note: cache coherence has snoop invalidate delay)
	while (!done_0 || !done_1);

	cortos_printf("Core-10 Done[Ticks=%lld], counter_10 = %d, global_counter=%d\n", 
				t1 - t0, counter_10, global_counter);

	return(0);
}

