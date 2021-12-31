// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"
#include "ajit_mt_irc.h"
#include "core_portme.h"


int __enable_serial()
{
	__ajit_write_serial_control_register_via_vmap__ (TX_ENABLE | RX_ENABLE);
	return(0);
}

#define PRINTF ee_printf

// timer will be set to 1ms..  Clock cycle is 10ns.
// Thus, the counter should be set to 100000.
#define COUNT TIMERCOUNT
#define TIMERINITVAL ((COUNT << 1) | 1)

//
// number of samples for jitter measurement.
//
#define NSAMPLES TIMERSAMPLES
#define TIME_SCALE_FACTOR (0.001/NSAMPLES)

double ajit_sqrt(double x)
{
	double y;
	uint32_t px = (uint32_t) &x;
	uint32_t py = (uint32_t) &y;

	__ajit_fsqrts__ (px, py);
	
	return(y);
}

double    volatile min_interval, max_interval;
double    volatile sum_of_squares, sum_of_intervals;

double    volatile mean_scale_factor = 1.0/NSAMPLES;
double    volatile scale_factor = 1.0/(NSAMPLES - 1);
double    time_scale_factor;
int 	  volatile E;

uint64_t last_time_64;

//
// get all the work done in the interrupt handler!
//
void timer_interrupt_handler()
{
	// clear timer control register.
	__ajit_write_timer_control_register_via_vmap__ (0x0);

	// reenable the timer, right away..
	__ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	

#ifdef DEBUG_MODE
	PRINTF("Info: entered timer_interrupt_handler (E=%d).\n", E);
#endif

	//
	// Code which depends on interrupt being observed.
	// 	(for example: status of Coprocessor action, scheduling of co-processor actions etc.)
	//
	// code which does not directly depend on interrupt flag being observed
	//  (e.g. PVT calculation)
	// this code depends on the state which may have been altered
	// above.
	//
	if(E <= NSAMPLES) {

		uint64_t curr_time_64 = __ajit_get_clock_time();

		if(E > 0)
		{
			double interval  =  0;
			uint64_t diff_time_64 = (curr_time_64 - last_time_64);

			uint32_t cu32 = diff_time_64 & 0xffffffff;

			__ajit_fitod__ ((uint32_t) &cu32,    (uint32_t) &interval);


			if(interval < min_interval)
				min_interval = interval;
			if(interval > max_interval)
				max_interval = interval;

			interval = interval * TIME_SCALE_FACTOR;

			sum_of_intervals += interval;
			sum_of_squares   += (interval * interval); 
		}
		last_time_64 = curr_time_64;
		E++;
	}
}

int main () 
{
	__enable_serial();
	PRINTF("Starting\n");


	// initialize
	min_interval 	  = 10000000.0;
	sum_of_intervals 	  = 0;
	max_interval 	  = 0;
	sum_of_squares     = 0.0;
	scale_factor = 1.0/(NSAMPLES - 1);
	mean_scale_factor = 1.0/NSAMPLES;
	E = 0;

	// set up interrupt handler function pointer.
	ajit_initialize_interrupt_handlers_to_null();
	ajit_set_interrupt_handler(10, &(timer_interrupt_handler));	

	// enable interrupt controller for the current thread.
	enableInterruptControllerAndAllInterrupts(0,0);

	// reenable the timer, right away..
	__ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	

	while(1)
	{
		if(E > NSAMPLES)
		{

			double scaled_square_mean= (mean_scale_factor * (sum_of_intervals*sum_of_intervals));
			double variance = scale_factor * (sum_of_squares - scaled_square_mean);

			double sigma = ajit_sqrt(variance);
			PRINTF("INTERVAL : MIN=%f, MAX=%f, MEAN=%f, STD.DEVIATION=%20.8f \n", 
					(float) min_interval, 
					(float) max_interval, 
					(float) mean_scale_factor*sum_of_intervals* (1.0/TIME_SCALE_FACTOR), 
					(float) (sigma * (1.0/TIME_SCALE_FACTOR)));

			break;
		}
	}

	return(0);
}

