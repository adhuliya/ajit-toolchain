#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ajit_access_routines.h>

void (*core_mark_0)(uint32_t) = (void (*) (uint32_t)) 0x40020000;
int ajit_main(uint32_t cpu_id)
{
	core_mark_0(cpu_id);
	return(1);
}


