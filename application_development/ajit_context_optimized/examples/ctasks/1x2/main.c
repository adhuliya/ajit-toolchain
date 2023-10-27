// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <cortos.h>
#include <ajit_ctask.h>


volatile int __counter = 0;
void func (void* vcr)
{
	uint8_t core_id, thread_id;
	ajit_get_core_and_thread_id (&core_id, &thread_id);

	ajit_ctask_args_t* marg = (ajit_ctask_args_t*) vcr;
	
	uint32_t counter = marg->args[0];
	cortos_printf("1.(%d,%d): func* %d.\n", core_id, thread_id, counter);

	ajit_ctask_yield(marg->ct);
	cortos_printf("2.(%d,%d): func** %d.\n", core_id, thread_id, counter);

	ajit_ctask_yield(marg->ct);
	cortos_printf("3.(%d,%d): func*** %d.\n", core_id, thread_id, counter);

	ajit_ctask_yield(marg->ct);
	cortos_printf("4.(%d,%d): func**** %d.\n", core_id, thread_id, counter);

	ajit_ctask_return(marg->ct);
}

void setup ()
{
	// enable serial 0 device..  enable_tx, enable_rx, enable_interrupts	
	__ajit_serial_configure__ (1, 0, 0);
	// set baud rate.
	__ajit_serial_set_baudrate__ (115200, CLK_FREQUENCY);
	// bring uart out of reset.
	__ajit_serial_set_uart_reset__ (0);

	CORTOS_DEBUG ("enabled serial\n");

}

#define COUNT 4

volatile int sched_init_flag = 0;
volatile ajit_ctask_scheduler_t ctask_scheduler  __attribute__ ((aligned(8)));
volatile ajit_ctask_args_t g_marg[COUNT];


int main_00 () 
{
	CORTOS_DEBUG("start scheduler\n");
	ajit_init_ctask_scheduler (&ctask_scheduler);

	int i;
	for(i = 0; i < COUNT; i++)
	{
		ajit_ctask_t* ct = ajit_reserve_ctask_from_pool(&(ctask_scheduler.pool));
		CORTOS_DEBUG("main_00: reserved task 0x%x. \n", (uint32_t) ct);

		if(ct == NULL)
			return(-1);

		// put the argument...
		g_marg[i].args[0] = i;

		ajit_schedule_ctask (ct, (void*) func, (void*) &(g_marg[i]), 
					AJIT_COROUTINE_STACK_SIZE_IN_BYTES,
						&ctask_scheduler);	
		CORTOS_DEBUG("main_00: scheduled task \n");
	}	
	sched_init_flag = 1;

	ajit_run_ctask_scheduler (&ctask_scheduler);


	CORTOS_DEBUG("completed\n");
}


int main_01 ()
{
	while (!sched_init_flag);

	CORTOS_DEBUG("start scheduler\n");
	ajit_run_ctask_scheduler (&ctask_scheduler);
}
