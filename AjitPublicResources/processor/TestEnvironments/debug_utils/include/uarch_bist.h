#ifndef __uarch_bist_h___
#define __uarch_bist_h___

//
// author: Madhav Desai
//

// elementary march-tests.
// write known magic values into all, in sequence,
// and read them back..
uint32_t dbg_run_iu_reg_march_test(uint32_t number_of_windows);
uint32_t dbg_run_fp_reg_march_test();
uint32_t dbg_run_mem_march_test(uint32_t asi, uint32_t mem_size_in_bytes);
uint32_t vanilla_mem_bist(uint32_t nwindows, uint32_t asi, uint32_t mem_size_in_bytes, FILE* fp);

#endif
