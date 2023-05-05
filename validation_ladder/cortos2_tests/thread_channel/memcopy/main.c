#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include <thread_channel.h>
#include <ajit_access_routines.h>

volatile ThreadChannel volatile tc;

uint64_t source_array [ORDER];
uint64_t destination_array[ORDER];

typedef struct __Args {
	uint64_t* src;
	uint64_t* dest;
	uint32_t  n_dwords;
	uint32_t  stride_in_dwords;
} Args;

void init()
{
	// initialize
	uint32_t I = 0;
	for(I = 0; I < ORDER; I++)
		source_array[I] = I;
}
void setup()
{
	__ajit_serial_configure__(1,0,0);
	__ajit_serial_set_baudrate__ (115200, CLK_FREQUENCY);
	__ajit_serial_set_uart_reset__ (0);

	// initialize scoreboard.
	initChannel(&tc, 1);
	CORTOS_DEBUG("initChannel %d: status=%d.\n", tc.id, tc.status);


	init();
	cortos_printf("setup completed.\n");
}

void my_memcopy (uint64_t* src, uint64_t* dest, uint32_t n_dwords, uint32_t stride_in_dwords)
{
	CORTOS_DEBUG("entered memcopy (n_dwords=%d, stride=%d).\n", n_dwords, stride_in_dwords);

	uint32_t I;
	for(I = 0; I < n_dwords; I+= stride_in_dwords)
	{
		dest[I] = src[I];
	}

	CORTOS_DEBUG("leaving memcopy (n_dwords=%d, stride=%d).\n", n_dwords, stride_in_dwords);
}

void my_memcopy_wrap (void* varg)
{
	Args* args = (Args*) varg;
	my_memcopy (args->src, args->dest, args->n_dwords, args->stride_in_dwords);
}

volatile uint32_t volatile exit_flag = 0;

void main_00 () 
{
	cortos_printf("Entered main_00\n");

	uint32_t J;
	Args args;
	
	args.src  = (uint64_t*) &(source_array[1]);
	args.dest = (uint64_t*) &(destination_array[1]);
	args.n_dwords = ORDER;
	args.stride_in_dwords = 2;


	// run with single thread...
	uint64_t s_start_time = __ajit_get_clock_time();
	for(J = 0; J < NITERATIONS; J++)
		my_memcopy (source_array, destination_array, ORDER, 1);
	uint64_t s_end_time = __ajit_get_clock_time();
	cortos_printf("Info: single-thread  time = %f seconds.\n",
				((double) (s_end_time - s_start_time))*1.0/CLK_FREQUENCY);

	s_start_time = __ajit_get_clock_time();
	for(J = 0; J < NITERATIONS; J++)
		my_memcopy (source_array, destination_array, ORDER, 2);
	s_end_time = __ajit_get_clock_time();
	cortos_printf("Info: single-thread half-array time = %f seconds.\n",
				((double) (s_end_time - s_start_time))*1.0/CLK_FREQUENCY);

	init();

	// run with sidekick.
	uint64_t start_time = __ajit_get_clock_time();
	for(J = 0; J < NITERATIONS; J++)
	{
		scheduleChannelJob(&tc, (void*) my_memcopy_wrap, &args);
		CORTOS_DEBUG("main_00 scheduled channel job.\n");

		my_memcopy (source_array, destination_array, ORDER, 2);

		void* vptr = NULL;
		while(getChannelResponse(&tc, &vptr))
		{
		}

		CORTOS_DEBUG("main_00 received channel response.\n");
	}
	uint64_t end_time = __ajit_get_clock_time();

	cortos_printf("Info: total time = %f seconds.\n",
				((double) (end_time - start_time))*1.0/CLK_FREQUENCY);

	scheduleChannelJob(&tc, NULL, NULL);

	// check results.
	uint32_t I;	
	for(I = 0; I < ORDER; I++)
	{
		if (destination_array[I] != I)
		{
			cortos_printf("ERROR: dest[%d] = %d, expected %d.\n", destination_array[I], I);
		}
	}
	cortos_printf("Info: main_00 finished.\n");
}


void main_01 ()
{
	void (*__fn) (void*);
	void *__arg;

	cortos_printf("Entered main_01\n");

	while(1) 
	{
		while(getChannelJob(&tc, (void**) &__fn, (void**) &__arg))
		{
		}

		CORTOS_DEBUG("main_01 got channel job.\n");

		if(__fn != NULL)
		{
			(*__fn)(__arg);
			setChannelResponse(&tc, __arg);
		}
		else
			break;
	}

	cortos_printf("Info: main_01 finished.\n");

}



