#include <stdint.h>
#include "core_portme.h"

uint64_t mem_march (int niters);

int main () 
{

	ajit_serial_init();
	int n_iters = NITERS;

	uint32_t t0 = ajit_barebones_clock(); 
	uint64_t err = mem_march(n_iters);
	uint32_t t1 = ajit_barebones_clock();

	ee_printf ("March-time (ticks)=%u\n",  (t1 - t0));
	if(err)
		ee_printf ("ERROR\n");
	else
		ee_printf ("OK\n");


	return(0);
}
