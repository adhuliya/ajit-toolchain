#include <stdint.h>
#include "ajit_access_routines.h"

#define VECTOR_SIZE  64
#define TIMERCOUNT 10
#define COUNT TIMERCOUNT
#define TIMERINITVAL ((COUNT << 1) | 1)
#define INTERRUPT_LIMIT 32
#define REPORT_INTERVAL 1

volatile int volatile timer_interrupt_counter = 0;
volatile int volatile rec_val = 0;
volatile int volatile isr_busy = 0;

void setup_serial()
{
        __ajit_serial_configure_via_vmap__   (1, 0, 0);
}


void dump_regs (uint32_t* regs)
{
	__AJIT_SAVE_IU_REGS__((uint32_t) regs);	
		
	uint32_t psr; 
	__AJIT_GET_PSR(psr);
	regs[32] = psr;

	uint32_t wim; 
	__AJIT_GET_WIM(wim);
	regs[33] = wim;

	uint32_t y; 
	__AJIT_GET_Y(y);
	regs[34] = y;

}

void print_regs(uint32_t* regs)
{
	cortos_printf(" R: ");
	int I;
	for (I=0; I < 32; I++)
	{
		cortos_printf(" 0x%x ", regs[I]);
	}
	cortos_printf("\n");
	cortos_printf(" R: psr = 0x%x wim =0x%x y=0x%x\n", regs[32], regs[33], regs[34]);
}


		
int compare_regs(uint32_t* regs, uint32_t* last_regs)
{
	int ret_val = 0;
	int I;
	for(I = 0; I < 35; I++)
	{
		if(regs[I]  != last_regs[I])
		{
			ret_val++;
			cortos_printf("!mismatch[%d], 0x%x, 0x%x.\n", I, regs[I], last_regs[I]);
		}
	}
	return(ret_val);
}

void copy_regs(uint32_t* regs, uint32_t* last_regs)
{
	int I;
	for(I = 0; I < 35; I++)
	{
		last_regs[I] = regs[I];
	}
	return;
}

uint32_t recurse (uint32_t* vals, uint32_t n)
{
   if(n == 1)
   {
       vals[0] = 0;
       return(vals[0]);
   }
   else
   {
	vals[n-1] = n-1;
	return(vals[n-1] + recurse(vals, n-1));
   }
}


void my_timer_interrupt_handler()
{
	if(isr_busy)
        {
	   ee_printf("Error: interrupt on interrupt.\n");
	   return;
        }

	isr_busy = 1;

	uint32_t vals[32];
	// clear timer control register.
	__ajit_write_timer_control_register_via_vmap__ (0x0);

	rec_val = recurse(vals, 32);	

	// reenable the timer, right away..
	__ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	

	//ee_printf("Timer Intr!\n");

	// interrupt counter incremented.
	timer_interrupt_counter++;

	isr_busy = 0;
}


void mm_init();
void mm();

int main()
{

	uint64_t regs[20];
	uint64_t last_regs[20];

	int K;
	for(K = 0; K > 20; K++)
	{
		last_regs[K] = 0x0;
	}
	mm_init();	

	setup_serial();

	cortos_printf("Starting: enabling the interrupt controller.\n");

	// enable interrupt controller for the current thread.
	enableInterruptControllerAndAllInterrupts(0,0);

	// enable the timer, right away..
	 __ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	


	int counter = 0;
	int miscompared_count = 0;

	for(K=0; K < 64; K++)
	{
		dump_regs((uint32_t*) regs);

		// first time: 32, next time 0.....
		miscompared_count += compare_regs((uint32_t*) regs, (uint32_t*) last_regs);
		copy_regs((uint32_t*) regs, (uint32_t*) last_regs);
	
		int p_flag = (counter % REPORT_INTERVAL) == 0;
		
		if(p_flag)
		{
			print_regs(regs);
			cortos_printf("%d. interrupt count=%d mismatches=%d rec_val=%d.\n", 
						counter, 
						timer_interrupt_counter, 
						miscompared_count,	
						rec_val);
		}
		counter++;
	}

	__ajit_write_timer_control_register_via_vmap__ (0x0);
}
