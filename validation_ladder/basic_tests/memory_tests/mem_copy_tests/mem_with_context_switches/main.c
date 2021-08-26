#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

void print_array ();

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

int mem_march(int n);

int main () 
{

	//ajit_serial_init();
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	ee_printf ("Starting...\n");
	int n_iters = NITERS;
	uint32_t t0 = ajit_barebones_clock(); 
	uint64_t err = mem_march(n_iters);
	int contexts = 1;
 
	if(!err)
	{
		context_switch(1);
		err = mem_march(n_iters);
		contexts++;
	}

	if (!err)
	{
		context_switch(2);
		err = mem_march(n_iters);
		contexts++;
	}

	if (!err)
	{
		context_switch(3);
		err = mem_march(n_iters);
		contexts++;
	}

	uint32_t t1 = ajit_barebones_clock();
	ee_printf ("March-time (ticks,contexts)=%u,%d\n",  (t1 - t0), contexts);
	if(err)
		ee_printf ("ERROR\n");
	else
		ee_printf ("OK\n");


	//print_array();

	return(0);
}
