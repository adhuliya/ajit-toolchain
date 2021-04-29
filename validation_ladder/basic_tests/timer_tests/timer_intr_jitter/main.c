// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

void set_intr_flag (){

	__asm__ __volatile__("mov 1,%l4 \n\t");
	__asm__ __volatile__("set INTR_FLAG, %%l5; st %%l4 , [%%l5]\n\t" : :  : "memory");
}

void clear_intr_flag (){
	__asm__ __volatile__("mov 0,%l4 \n\t");
	__asm__ __volatile__("set INTR_FLAG, %%l5; st %%l4 , [%%l5]\n\t" : :  : "memory");
}

uint32_t get_intr_flag(){
	int ret_val = 0;
	__asm__ __volatile__("set INTR_FLAG, %%l5; ld [%%l5], %0\n\t" : "=r"(ret_val) :  : "memory");
	return(ret_val);
}

int __enable_serial()
{
	__ajit_write_serial_control_register__ (TX_ENABLE | RX_ENABLE);
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

double ajit_sqrt(double x)
{
	double y;
	uint32_t px = (uint32_t) &x;
	uint32_t py = (uint32_t) &y;

	__ajit_fsqrts__ (px, py);
	
	return(y);
}

int main () 
{

	__enable_serial();
	PRINTF("Starting\n");
	double min_interval, max_interval;
	double    second_moment, mean_interval;
	double    scale_factor = 1.0/(NSAMPLES - 1);

			
	uint64_t last_time_64  = __ajit_get_clock_time();					
	uint32_t lu32 = last_time_64 & 0xffffffff;
	__ajit_fitod__ ((uint32_t) &lu32, (uint32_t) &second_moment);

	// initialize
	min_interval 	  = 10000000.0;
	mean_interval 	  = 0;
	max_interval 	  = 0;
	second_moment     = 0.0;

	clear_intr_flag();
	__ajit_write_timer_control_register__ (TIMERINITVAL);	//Enable timer with 31 bit count value	
	__ajit_write_irc_control_register__(1);			//enable irc


	int E=0;
	int E_flag = 0;


	while (E < NSAMPLES) { 
		// loop

		//
		// code which depends on the interrupt being encountered.
		//	Note: on interrupt, the ISR will set this flag.
		//
		if(get_intr_flag() == 1) 
		{	

			//
			// Code which depends on interrupt being observed.
			// 	(for example: status of Coprocessor action, scheduling of co-processor actions etc.)
			// 

			// clear timer interrupt flag, and reenable timer.
			clear_intr_flag();

			// reenable interrupt.
			__ajit_write_timer_control_register__ (TIMERINITVAL);	//Enable timer with 31 bit count value	
			__ajit_write_irc_control_register__(1);			//enable irc

			// change the state...
			E_flag = 1;
		}

		//
		// code which does not directly depend on interrupt flag being observed
		//  (e.g. PVT calculation)
		// this code depends on the state which may have been altered
		// above.
		//
		if(E_flag == 1) {
			E_flag = 0;
			uint64_t curr_time_64 = __ajit_get_clock_time();

			if(E > 0)
			{
				double interval  =  0;
				uint64_t diff_time_64 = (curr_time_64 - last_time_64);

				uint32_t cu32 = diff_time_64 & 0xffffffff;

				__ajit_fitod__ ((uint32_t) &cu32,    (uint32_t) &interval);

				//uint32_t ct32 = curr_time_64 & 0xffffffff;
				//PRINTF("INTR, current-time=%d, diff-time=%d,interval=%f \n", ct32, cu32, (float) interval);

				if(interval < min_interval)
					min_interval = interval;
				if(interval > max_interval)
					max_interval = interval;

				mean_interval += scale_factor * interval;
				second_moment += (scale_factor * interval) * interval; 
			}
			last_time_64 = curr_time_64;
			E++;
		}

	}

	double sigma = ajit_sqrt(second_moment - (mean_interval*mean_interval));
	PRINTF("INTERVAL : MIN=%f, MAX=%f, MEAN=%f, STD.DEVIATION=%f \n", (float) min_interval, (float) max_interval, (float) mean_interval, (float) sigma);

	return(0);
}
