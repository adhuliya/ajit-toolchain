#include <stdint.h>
#include <cortos.h>
#include "ajit_access_routines.h"

#define TIMERCOUNT 100000
#define COUNT TIMERCOUNT
#define TIMERINITVAL ((COUNT << 1) | 1)
#define TIME_SCALE_FACTOR (1.0/CLK_FREQUENCY)

extern volatile int volatile timer_interrupt_counter;
void report_interrupt_status();	

void ajit_init () 
{
	__ajit_serial_configure__ (1,0,0);
	__ajit_serial_puts__ ("\nHiFromAjit\n\n", 13);

	enableInterruptControllerAndAllInterrupts(0,0);
	__ajit_write_timer_control_register__ (TIMERINITVAL);	
}

uint32_t barebones_clock() {
	uint32_t tick_h = __ajit_read_cycle_count_register_high__();
	uint32_t tick_l = __ajit_read_cycle_count_register_low__();

	//  divide by 256
	uint32_t rval  = (tick_h << 24) | (tick_l >> 8);

	return(rval);
}

volatile int volatile timer_interrupt_counter = 0;
volatile int volatile exit_flag  = 0;
volatile uint64_t volatile last_time_64;
volatile double volatile min_interval  = 1000000000.0;
volatile double volatile max_interval  = 0.0;
volatile double volatile sum_of_intervals  = 0.0;

void report_interrupt_status ()
{
	cortos_printf("Timer: %d interrupts min-interval=%f, max-interval=%f.\n",
				timer_interrupt_counter, min_interval, max_interval);
}

void my_timer_interrupt_handler()
{
	double fp_regs[33];

	// clear timer control register.
	__ajit_write_timer_control_register_via_vmap__ (0x0);

	// reenable the timer, right away..
	__ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	

	__AJIT_SAVE_FP_REGS__ ((uint32_t) &fp_regs);

	//
	// Code which depends on interrupt being observed.
	// 	(for example: status of Coprocessor action, scheduling of co-processor actions etc.)
	//
	// code which does not directly depend on interrupt flag being observed
	//  (e.g. PVT calculation)
	// this code depends on the state which may have been altered
	// above.
	//
	uint64_t curr_time_64 = __ajit_get_clock_time();

	if(timer_interrupt_counter > 0)
	{
		double interval  =  0;
		interval =  (((double) curr_time_64) - ((double) last_time_64))*TIME_SCALE_FACTOR;


		if(interval < min_interval)
			min_interval = interval;
		if(interval > max_interval)
			max_interval = interval;

	}
	else
	{
		ee_printf("ISR: 0\n");
	}
	timer_interrupt_counter++;

	__AJIT_RESTORE_FP_REGS__ ((uint32_t) &fp_regs);
	last_time_64 = curr_time_64;
}
