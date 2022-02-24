#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
int marchTest(uint32_t context);

//context switch.
//make a switch to a particular context
inline void context_switch(uint32_t context_number)
{
	
	//Copy context number into register
	__asm__ __volatile__("mov %0, %%l0\n\t" : : "r"(context_number):"memory");

	
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_FLUSH_I_D_CONTEXT) : "memory");
	//flush icache
	__asm__ __volatile__(" flush ");
	//flush TLB
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t"  : : "i"(ASI_MMU_FLUSH_PROBE) : "memory");

	//write new context number into mmu context register
	__asm__ __volatile__("sta %%l0, [%0] %1\n\t" : : "r"(MMU_REG_CONTEXT),
			     "i"(ASI_MMU_REGISTER) : "memory");
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_FLUSH_I_D_CONTEXT) : "memory");
	//flush icache
	__asm__ __volatile__(" flush ");
	//flush TLB
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t"  : : "i"(ASI_MMU_FLUSH_PROBE) : "memory");
}

int main () 
{

	//ajit_serial_init();
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	ee_printf ("Started: clock freq=%d Mhz, NITERS=%d\n", CLK_FREQUENCY, NITERS);


	int i;

	uint64_t t0  = __ajit_get_clock_time();					
	for(i = 0; i < NITERS; i++)
	{
		context_switch(0);
		marchTest(0);

		context_switch(1);
		marchTest(1);

		context_switch(2);
		marchTest(2);

		context_switch(3);
		marchTest(3);

	}
	uint64_t t1  = __ajit_get_clock_time();					

	double   ct  = ((double) (t1 - t0))*(1.0e-6/CLK_FREQUENCY)*(1.0/NITERS)*0.25;
	ee_printf ("Time per sweep with context-switch=%f\n",  ct * 0.25);

	t0  = __ajit_get_clock_time();					
	for(i = 0; i < NITERS; i++)
	{
		marchTest(3);
	}
	t1  = __ajit_get_clock_time();					
	ct  = ((double) (t1 - t0))*(1.0e-6/CLK_FREQUENCY)*(1.0/NITERS)*0.25;
	ee_printf ("Time per sweep without context-switch=%f\n",  ct);

	return(0);
}
