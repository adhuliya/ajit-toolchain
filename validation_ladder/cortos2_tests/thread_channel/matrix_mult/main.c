#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include "ajit_access_routines.h"
#include "thread_channel.h"

typedef struct argstruct__ {
	int start_index;
	int stride;
} argstruct;

void initMatrices();
void mmul(int s_index, int stride);


ThreadChannel tc;
uint64_t t0, t1, t2, t3;

int sb_init = 0;

void setup()
{
	__ajit_serial_configure__(1,0,0);
	__ajit_serial_set_baudrate__ (115200, 80000000);
	__ajit_serial_set_uart_reset__ (0);

	CORTOS_DEBUG("Init channel.\n");
	// initialize scoreboard.
	initChannel(&tc, 1);

}


int mmul_s (void* varg)
{
	argstruct* arg = (argstruct*) varg;
	CORTOS_DEBUG("start mmul_s (%d, %d).\n", arg->start_index, arg->stride);
	mmul (arg->start_index, arg->stride);
	CORTOS_DEBUG("finished mmul_s (%d, %d).\n", arg->start_index, arg->stride);
}

void main_00 () 
{
	CORTOS_DEBUG("Initialize matrices\n");

	// initialize..
	initMatrices();

	CORTOS_DEBUG("Run all on 00\n");

	// Run one cold 
	mmul(0,1);

	// run entirely on thread 00 
	// but with cache primed..
	t0 = __ajit_get_clock_time();
	mmul(0,1);
	t1 = __ajit_get_clock_time();

	CORTOS_DEBUG("Shared run.\n");
	// second run...
	t2 = __ajit_get_clock_time();


	// arguments
	argstruct sarg;
	sarg.start_index = 0;
	sarg.stride = 2;

	argstruct* rarg;

	scheduleChannelJob(&tc, (void*) &mmul_s, (void*) &sarg);

	mmul(1,2);
	while(getChannelResponse(&tc, (void**) &rarg))
	{
	}

	// finished runs on both threads..
	t3 =__ajit_get_clock_time();

	// print_result_matrix();
	cortos_printf("Single-thread time=%f ticks, Two-thread time=%f ticks.\n",
			((double) (t1 - t0)), ((double) (t3-t2)));
}




void main_01 () 
{
	void (*__fn) (void*);

	void *__arg;
	while(getChannelJob(&tc, (void**) &__fn, (void**) &__arg))
	{
	}

	(*__fn)(__arg);
	tc.status = CH_COMPLETED;
}

