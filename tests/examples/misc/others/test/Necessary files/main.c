#include <stdint.h>
#include "core_portme.h"

void mem_march (int num);

int main () 
{

	ajit_serial_init();
  //int re;
	//uint32_t t0 = ajit_barebones_clock(); 
	mem_march(7);
//	uint32_t t1 = ajit_barebones_clock();

//	ee_printf ("March-time (ticks)=%u\n",  (t1 - t0));
	//if(err)
	//	ee_printf ("ERROR\n");
//	else
//		ee_printf ("OK\n");


	return(0);
}
