#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pipeHandler.h>
#include <Pipes.h>
#include <uarch_debug_utils.h>
#include <uarch_bist.h>

uint32_t dbg_run_iu_reg_march_test(uint32_t number_of_windows)
{
	uint32_t err = 0;
	uint32_t I,J;

	// for each window, write to all regs and read back from
	// all regs..
	//
	for(I = 0; I < number_of_windows; I++)
	{
		dbg_write_psr(I); // set CWP in PSR to I.
		if(I > 0)
		{
			// a bit of a check of the sliding windows.
			// still not a complete test!
			uint32_t K;
			for(K = 0; K < 8; K++)
			{
				// check that input registers of window I-1
				// are the output registers of this window.
				dbg_write_psr(I-1); // set CWP in PSR to I-1.
				uint32_t rv_in =dbg_read_iunit_register(K+24);
				dbg_write_psr(I); // set CWP in PSR to I-1.
				uint32_t rv_out =dbg_read_iunit_register(K+8);
				if(rv_in != rv_out)
				{
					fprintf(stderr,"Error: in-reg %d of window %d is not outreg %d of window %d.\n",
							K+24, I-1, K+9, I);
					err = 1;
				}

				if(rv_in != (0xffffffff ^ ((I-1)*(K+24))))
				{
					fprintf(stderr,"Error: in-reg %d in window %d is incorrect.\n", 
								K+24, I-1);
				}
			}

		}
		for(J=0; J < 32; J++)
		{
			err = dbg_write_iunit_register(J, 0xffffffff ^ (I*J));
			if(err) return(err);
		}

		for(J=0; J < 32; J++)
		{
			uint32_t rv = dbg_read_iunit_register(J);
			if((J==0) && (rv != 0)) return(1);
			else if((J !=0) && (rv != (0xffffffff ^ (I*J)))) return(1);
		}
	}

	// write status regs
	err = dbg_write_psr(0xffffffff);
	if(err) return(err);
	err = dbg_write_wim(0xffffffff ^ 1);
	if(err) return(err);
	err = dbg_write_tbr(0xffffffff ^ 2);
	if(err) return(err);
	err = dbg_write_y(0xffffffff ^ 3);
	if(err) return(err);

	// write ancillary regs.
	for(I = 0; I < 32; I++)
	{
		err = dbg_write_asr(I, 0xffffffff ^ (I+4));
		if(err) return(err);
	}

	// read back status regs.
	uint32_t rv = dbg_read_psr();
	if(rv != 0xffffffff) return(1);
	rv = dbg_read_wim();
	if(rv != (0xffffffff ^ 1)) return(1);
	rv = dbg_read_tbr();
	if(rv != (0xffffffff ^ 2)) return(1);
	rv = dbg_read_y();
	if(rv != (0xffffffff ^ 3)) return(1);

	// read ancillary regs.
	for(I = 0; I < 32; I++)
	{
		rv = dbg_read_asr(I);
		if(rv !=(0xffffffff ^ (I+4))) return(1);
	}

	return(0);
}

uint32_t dbg_run_fp_reg_march_test()
{
	uint32_t err = 0;
	err = dbg_write_fsr(0xffffffff);
	if(err) return(err);

	uint32_t J;
	for(J=0; J < 32; J++)
	{
		err = dbg_write_fpunit_register(J, 0xffffffff ^ (J+1));
		if(err) return(err);
	}

	uint32_t rv = dbg_read_fsr();
	if(rv != 0xffffffff) return(1);

	for(J=0; J < 32; J++)
	{
		rv = dbg_read_fpunit_register(J);
		if(rv != (0xffffffff ^ (J+1))) return(1);
		if(err) return(err);
	}
	return(0);
}

// checks user space writes/reads to memory.
// currently only asi=10
uint32_t dbg_run_mem_march_test(uint32_t asi, uint32_t mem_size_in_bytes)
{
	uint32_t mem_size_in_words = (mem_size_in_bytes >> 2);
	uint32_t I = 0;
	for(I = 0; I < mem_size_in_words; I++)
	{
		dbg_write_mem(asi,4*I,I);
	}
	for(I = 0; I < mem_size_in_words; I++)
	{
		uint32_t rv = dbg_read_mem(asi,4*I);
		if(rv != I) return(1);
	}
	return(0);
}


uint32_t vanilla_mem_bist(uint32_t nwindows, uint32_t asi, uint32_t mem_size_in_bytes, FILE* fp)
{
	uint32_t ret_val, err;
	err = 0;
	ret_val = dbg_run_iu_reg_march_test(nwindows);
	if(ret_val)
		fprintf(stderr,"Error: iu-reg-march-test failed.\n");
	else
	{
		get_file_print_lock(fp);
		fprintf(fp,"debug>\tpassed iu-reg-march-tests.\n");
		release_file_print_lock(fp);
	}
	err = (err || ret_val);

	ret_val = dbg_run_fp_reg_march_test();
	if(ret_val)
		fprintf(stderr,"Error: fp-reg-march-test failed.\n");
	else
	{
		get_file_print_lock(fp);
		fprintf(fp,"debug>\tpassed fp-reg-march-tests.\n");
		release_file_print_lock(fp);
	}
	err = (err || ret_val);

	ret_val = dbg_run_mem_march_test(asi, mem_size_in_bytes );
	if(ret_val)
		fprintf(stderr,"Error: memory-march-test failed.\n");
	else
	{
		get_file_print_lock(fp);
		fprintf(fp,"debug>\tpassed memory-march-tests.\n");
		release_file_print_lock(fp);
	}

	err = (err || ret_val);

	return(err);
}
