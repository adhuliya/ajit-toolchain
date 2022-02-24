#ifndef _AJIT_GENERIC_SYS_CALLS_H___
#define _AJIT_GENERIC_SYS_CALLS_H___

//
// Can be called in user mode.   Will cause a trap and
// then the trap handler does the lifting.  Note that
// going to the trap handler will cost you at least a dozen
// clock cycles.
//
uint32_t ajit_sys_read_asr (uint32_t asr_id);
void     ajit_sys_get_core_and_thread_id(uint8_t* core_id, uint8_t* thread_id);
uint64_t ajit_sys_get_clock_time();
void     ajit_sys_sleep(uint32_t clock_cycles);


#endif
