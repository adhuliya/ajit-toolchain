#include <stdint.h>
#include <stdio.h>
#include "ajit_generic_sys_calls.h"

//
// Generic system calls for user-mode programs..
//


void     ajit_sys_get_core_and_thread_id(uint8_t* core_id, uint8_t* thread_id)
{
	// ajit_sys_read_asr is implemented in assembly.
	uint32_t rval = ajit_sys_read_asr(29);

	*core_id = (rval >> 8) & 0xff;
	*thread_id = (rval & 0xff);	
}

uint64_t ajit_sys_get_clock_time()
{
	uint32_t v_l = ajit_sys_read_asr(30);
	uint32_t v_h = ajit_sys_read_asr(31);
	uint64_t ret_val = v_h;
	ret_val = ret_val << 32;
	ret_val = ret_val | v_l;
	return(ret_val);
}

void     ajit_sys_sleep(uint32_t clock_cycles)
{
	uint64_t curr_time = ajit_sys_get_clock_time();
	uint64_t end_time = curr_time + clock_cycles;

	while(curr_time < end_time)
	{
		curr_time =  ajit_sys_get_clock_time();
	}
	return;
}

