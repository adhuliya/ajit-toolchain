// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>

#define TIMERCOUNT 100000
#define COUNT TIMERCOUNT
#define TIMERINITVAL ((COUNT << 1) | 1)
#define TIME_SCALE_FACTOR (1.0/CLK_FREQUENCY)
#define NSAMPLES  64

volatile int volatile timer_interrupt_counter = 0;
volatile int volatile exit_flag  = 0;
volatile uint64_t volatile last_time_64;
volatile double volatile min_interval  = 1000000000.0;
volatile double volatile max_interval  = 0.0;
volatile double volatile sum_of_intervals  = 0.0;


void my_timer_interrupt_handler()
{
	// clear timer control register.
	__ajit_write_timer_control_register_via_vmap__ (0x0);

	// reenable the timer, right away..
	__ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	

	//
	// Code which depends on interrupt being observed.
	// 	(for example: status of Coprocessor action, scheduling of co-processor actions etc.)
	//
	// code which does not directly depend on interrupt flag being observed
	//  (e.g. PVT calculation)
	// this code depends on the state which may have been altered
	// above.
	//
	if(timer_interrupt_counter <= NSAMPLES) {

		uint64_t curr_time_64 = __ajit_get_clock_time();

		if(timer_interrupt_counter > 0)
		{
			double interval  =  0;
			interval =  ((double) (curr_time_64 - last_time_64))*TIME_SCALE_FACTOR;


			if(interval < min_interval)
				min_interval = interval;
			if(interval > max_interval)
				max_interval = interval;

			sum_of_intervals += interval;
		}
		last_time_64 = curr_time_64;
		timer_interrupt_counter++;
	}

	if(timer_interrupt_counter >= NSAMPLES)
		exit_flag = 1;
}

int main () 
{
	cortos_printf("Starting\n");

	// enable interrupt controller for the current thread.
	enableInterruptControllerAndAllInterrupts(0,0);

	// reenable the timer, right away..
	// __ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	


	// infinite loop
	while(!exit_flag)
	{
	}

	cortos_printf("Inter-interrupt interval: Min=%f Max=%f Avge=%f", min_interval, max_interval, sum_of_intervals/(NSAMPLES-1));
	return(0);
}

