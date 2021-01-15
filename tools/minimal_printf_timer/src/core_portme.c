#include <stdint.h>
#include "ajit_access_routines.h"
#define EE_TICKS_PER_SECOND  (100000000/256)

void ajit_serial_init () 
{
	__ajit_serial_configure__ (1,0,0);
}

uint32_t ajit_barebones_clock() {
	uint32_t tick_h = __ajit_read_cycle_count_register_high__();
	uint32_t tick_l = __ajit_read_cycle_count_register_low__();

	//  divide by 256
	uint32_t rval  = (tick_h << 24) | (tick_l >> 8);

	return(rval);
}
