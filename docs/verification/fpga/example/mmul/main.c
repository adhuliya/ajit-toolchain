// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <device_addresses.h>
#include <ajit_mt_irc.h>
#include <cortos.h>
#include <ajit_ipi.h>
#include <mp_printf.h>


AjitPerThreadPerformanceCounters volatile pc_0, pc_0_d;
AjitPerThreadPerformanceCounters volatile pc_1, pc_1_d;

double A[32][32]; // 8KB
double B[32][32]; // 8KB
double C[32][32]; // 8KB

volatile uint8_t core_id   = 0;
volatile uint8_t thread_id = 0;

volatile	int volatile done_0 = 0;
volatile	int volatile done_1 = 0;

void mmul (int, int);

void init_matrices()
{
	int I, J;
	for(I = 0; I < 32; I++)
	{
		for(J = 0; J < 32; J++)
		{
			A[I][J] = (double) J;
			B[I][J] = (double) I;
		}
	}
}

void print_result()
{
	int I, J;
	for(I = 0; I < 32; I++)
	{
		cortos_printf ("result[%d][%d] = %f\n", I, I, C[I][I]);
	}
}

void setup ()
{
	// enable serial 0 device..  enable_tx, enable_rx, enable_interrupts	
	__ajit_serial_configure_via_vmap__ (1, 0, 0);
	// set baud rate.
	__ajit_serial_set_baudrate_via_vmap__ (115200, CLK_FREQUENCY);
	// bring uart out of reset.
	__ajit_serial_set_uart_reset_via_vmap__ (0);
	cortos_printf ("enabled serial\n");

	init_matrices ();
	cortos_printf ("initialized serial\n");
}

void print_performance_counters(int core_id, 
				AjitPerThreadPerformanceCounters* pc,
				AjitPerThreadPerformanceCounters* pc_d)
{
	cortos_printf ("Perf. counters for thread %d,0\n", core_id);
	cortos_printf ("      instructions  =  %lld\n", 
			pc_d->executed_instruction_count - pc->executed_instruction_count);
	cortos_printf ("      skipped instr =  %lld\n", 
			pc_d->skipped_instruction_count -  pc->skipped_instruction_count);
	cortos_printf ("      load  count   =  %lld\n", 
			pc_d->load_count - pc->load_count);
	cortos_printf ("      load misses   =  %lld\n", 
			pc_d->load_miss_count - pc->load_miss_count);
	cortos_printf ("      store count   =  %lld\n", 
			pc_d->store_count - pc->store_count);
	cortos_printf ("      store misses  =  %lld\n", 
			pc->store_miss_count - pc->store_miss_count);
	cortos_printf ("      stream mispr. =  %lld\n", 
			pc_d->stream_mispredict_count - pc->stream_mispredict_count);
	cortos_printf ("      trap count    =  %lld\n", 
			pc_d->trap_count - pc->trap_count);
	cortos_printf ("      icache acceses=  %lld\n", 
			pc_d->icache_access_count - pc->icache_access_count);
	cortos_printf ("      icache misses =  %lld\n", 
			pc_d->icache_miss_count - pc->icache_miss_count);
		
}

int main () 
{
	__ajit_flush_dcache__ ();
	cortos_printf ("dcache flushed\n");

	uint8_t core_id, thread_id;
	ajit_get_core_and_thread_id (&core_id, &thread_id);

	

	cortos_printf("Starting thread (%d,%d)\n", core_id, thread_id);

	int I, J, K, Istart, Iend;
	Istart = ((core_id == 1) ? 16 : 0);
	Iend   = ((core_id == 1) ? 32 : 16);



	__ajit_sample_thread_performance_counters (core_id, thread_id,
							ADDR_PERF_COUNTERS_MIN,
							((core_id == 0) ? &pc_0 : &pc_1) );
	uint64_t t0 =  __ajit_get_clock_time();
	for(K = 0; K < 16; K++)
	{
		mmul(Istart, Iend);
	}
	uint64_t t1 =  __ajit_get_clock_time();
	__ajit_sample_thread_performance_counters (core_id, thread_id,
							ADDR_PERF_COUNTERS_MIN,
							((core_id == 0) ? &pc_0_d : &pc_1_d) );


	if(core_id == 0)
		done_0 = 1;
	else
		done_1 = 1;

	while(1) {
		if(done_0 && done_1)
			break;
	}

	if(core_id == 0)
	{
		print_result();
		print_performance_counters (0, &pc_0, &pc_0_d);
		print_performance_counters (1, &pc_1, &pc_1_d);
	}

	cortos_printf("Done core %d: ticks=%lld\n", core_id, (t1 - t0));
	return(0);
}

