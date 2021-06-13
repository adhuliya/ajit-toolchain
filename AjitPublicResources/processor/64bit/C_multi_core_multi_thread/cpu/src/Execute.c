#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "Ajit_Hardware_Configuration.h"
#include "Opcodes.h"
#include "AjitThread.h"
#include "Core.h"
#include "Flags.h"
#include "Traps.h"
#include "Ancillary.h"
#include "Decode.h"
#include "Execute.h"
#include "ThreadInterface.h"
#include "ImplementationDependent.h"
#include "RegisterFile.h"
#include "fpu.h"
#include "ASI_values.h"
#include "ThreadHWserverInterface.h"
#include "Pipes.h"
#include "FpExceptions.h"
#include "Mmu.h"
#include "CacheInterface.h"


//
//
// Candidate for mapping to pipelined Aa module.
// 
//
uint32_t executeLoad(Opcode op, uint32_t operand1, uint32_t operand2, 
				uint32_t *result_h, uint32_t *result_l,
				StatusRegisters *status_reg, uint32_t trap_vector, 
				uint8_t asi, uint8_t rd, uint8_t *flags, ThreadState *state)
{

#ifdef DEBUG
	fprintf(stderr,"\tInfo : Load op-code=%x operand1=%x operand2=%x asi=%x\n", op, operand1, operand2 , asi);
#endif 

	uint32_t tv = trap_vector;
	uint32_t psr = status_reg->psr;
	uint32_t fsr = status_reg->fsr;
	uint8_t s = getBit32(psr, 7);
	uint8_t ef = getBit32(psr, 12);
	uint8_t ec = getBit32(psr, 13);
	uint8_t addr_space = 0;
	uint32_t data = 0;
	uint8_t f = *flags;

	uint32_t address = operand1 + operand2;

	uint8_t is_not_alternate = ((op >= _LDSB_) && (op <= _LDCSR_));
	uint8_t is_alternate     = ((op >= _LDSBA_) && (op <= _LDDA_));

	uint8_t is_privilege_exception    = (is_alternate && !s);
	
	uint8_t lock_flag = 0;
	if(is_not_alternate)
	{
		setPageBit((CoreState*) state->parent_core_state, address); // flag all pages that were accessed.

		if (!s) addr_space =10;
		else	addr_space =11;
	}else
	{
		if (s) 
		{
			//
			// bit[6] of asi is lock flag
			// in lda
			lock_flag = ((asi & 0x40) != 0);

			//
			// lowest 6 bits of asi are the
			// base asi bits.
			//
			addr_space= (asi & 0x3f);
		}
	}


	if(is_privilege_exception)
	{
		tv = setBit32(tv, _TRAP_, 1);
		tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1);
	}


	uint8_t is_fp_trap = ((op == _LDF_ || op == _LDDF_ || op == _LDFSR_) && ((!ef) || !getBpFPUPresent(state)));

	if(!is_privilege_exception && is_fp_trap)
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _FP_DISABLED_, 1) ;
	}

	uint8_t is_cp_trap = ((op == _LDC_ || op == _LDDC_ || op == _LDCSR_) && ((!ec) || !getBpCPPresent(state)));

	if(!is_privilege_exception && is_cp_trap) 
	{
		tv =setBit32(tv, _TRAP_, 1);
		tv =setBit32(tv, _CP_DISABLED_, 1);
	}

	uint8_t is_mem_address_not_aligned = ((((op == _LDD_) || (op == _LDDA_) || (op == _LDDF_) || (op == _LDDC_)) 
				&& (getSlice32(address, 2, 0)))
			|| (((op == _LD_) || 
					(op == _LDA_) || (op == _LDF_) || (op == _LDFSR_) 
					|| (op == _LDC_) || (op == _LDCSR_)) 
				&& (getSlice32(address, 1, 0))) 
			|| (((op == _LDSH_) || (op == _LDSHA_) || (op == _LDUH_) || (op == _LDUHA_)) 
				&& (getBit32(address, 0))));

	if(!is_privilege_exception && is_mem_address_not_aligned)
	{
		tv = setBit32(tv, _TRAP_, 1);
		tv = setBit32(tv, _MEM_ADDRESS_NOT_ALIGNED_, 1);
	}

	uint8_t is_trap = getBit32(tv, _TRAP_);

	uint8_t invalid_fp_reg = ((op == _LDDF_) && getBit8(rd, 0));
	if(!is_trap && invalid_fp_reg) 
	{
		tv = setBit32(tv, _TRAP_, 1);
		tv = setBit32(tv, _INVALID_FP_REGISTER_, 1);
	}
	if(!is_trap && invalid_fp_reg) status_reg->fsr= setSlice32(fsr, 16, 14, 6);

	// Note - Not implemented fp_sequence_error and cp_sequence_error

	uint8_t is_trap1 = getBit32(tv, _TRAP_);
	uint8_t mae1=0;
	uint64_t data64;
	if(!is_trap1)	
	{
		uint8_t byte_mask = calculateReadByteMask(op, address);
		if(lock_flag)
		{
			lockAndReadData64(state->mmu_state, state->dcache, 
					addr_space, byte_mask,  address, &mae1, &data64);
		}
		else
		{
			readData64(state->mmu_state, state->dcache, 
					addr_space, byte_mask, address, &mae1, &data64);
		}

		if (getBit32(address,2)==1) data= data64; else data = (data64)>>32;

		//inform the HW server about the memory access
		inform_HW_server(state, GDB_MEM_ACCESS, address);
	}
	if(mae1)
	{
		tv = setBit32(tv, _TRAP_, 1);
		tv = setBit32(tv, _DATA_ACCESS_EXCEPTION_, 1);
	}

	uint8_t byte = 0;
	uint32_t word1, word0;
	word1 = word0 = 0;


	uint8_t is_byte_inst = ((op == _LDSB_) || (op == _LDSBA_) || (op == _LDUB_) || (op == _LDUBA_));
	uint8_t address_10 = getSlice32(address, 1, 0);

	if(is_byte_inst)
	{
		if(address_10 == 0) byte = getSlice32(data, 31, 24) ;
		else if(address_10 == 1) byte = getSlice32(data, 23, 16) ;
		else if(address_10 == 2) byte = getSlice32(data, 15, 8)  ;
		else if(address_10 == 3) byte = getSlice32(data, 7, 0)   ;
	}

	if((op == _LDSB_) || (op == _LDSBA_)) word0 = signExtendByte(byte);
	if((op == _LDUB_) || (op == _LDUBA_)) word0 = zeroExtendByte(byte);

	uint16_t half_word = 0;
	uint8_t is_half_word_inst = ((op == _LDSH_) || (op == _LDSHA_) || (op == _LDUH_) || (op == _LDUHA_));

	if(is_half_word_inst)
	{

		if(address_10 == 0) half_word = getSlice32(data, 31, 16) ;
		else if(address_10 == 2) half_word = getSlice32(data, 15, 0) ;
	}

	if((op == _LDSH_) || (op == _LDSHA_)) word0= signExtendHalfWord(half_word) ;
	if((op == _LDUH_) || (op == _LDUHA_)) word0= zeroExtendHalfWord(half_word) ;

	if(!is_byte_inst && !is_half_word_inst) word0= data;

	is_trap = getBit32(tv, _TRAP_);


	if (!is_trap && (op == _LDFSR_)) status_reg->fsr =  word0 ;
	if (!is_trap && (op == _LDCSR_)) status_reg->csr =  word0 ;

	uint8_t is_double_word_inst = (op == _LDD_) || (op == _LDDA_) || (op == _LDDF_) || (op == _LDDC_);

	uint8_t mae2 = 0;
	uint8_t skip_read = (is_trap || !is_double_word_inst);
	if(!skip_read)	
	{
		// readData(addr_space, (address + 4), &mae2, &word1);
		word1 = (data64);
		mae2 = mae1;

		//inform the HW server about the memory access
		inform_HW_server(state, GDB_MEM_ACCESS, address+4);
	}
	if(mae2)
	{	tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _DATA_ACCESS_EXCEPTION_, 1);
	}

	if(is_double_word_inst) 		f = setBit8(f, _DOUBLE_RESULT_, 1);
	if((op == _LDF_) || (op == _LDDF_)) 	f = setBit8(f, _FLOAT_INSTRUCTION_, 1);
	uint8_t no_write_back = ((op == _LDC_) || (op == _LDFSR_) || (op == _LDCSR_) || (op == _LDDC_));
	if(!no_write_back ) f = setBit8(f, _NEED_WRITE_BACK_, 1);

	*result_l = (is_double_word_inst ? word1 : word0);
	*result_h = word0;
	*flags = f;

	return tv;
}


//
// Candidate for pipelined Aa module
//
uint32_t executeStore( Opcode op, uint32_t operand1, uint32_t operand2, uint32_t *result_h, uint32_t *result_l, uint32_t data0,	uint32_t data1, StatusRegisters *status_reg, uint32_t trap_vector, uint8_t asi, uint8_t rd, ThreadState *state)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : Store op-code=%x operand1=%x operand2=%x asi=%x\n", op, operand1, operand2, asi);
#endif 
	uint32_t tv = trap_vector;
	uint32_t psr = status_reg->psr;
	uint32_t fsr = status_reg->fsr;
	uint8_t s = getBit32(psr, 7);
	uint8_t ef = getBit32(psr, 12);
	uint8_t ec = getBit32(psr, 13);
	uint8_t addr_space = 0;

	uint32_t address = operand1 + operand2;

	uint8_t is_alternate = ((op >= _STBA_) && (op <= _STDA_));
	uint8_t is_privileged = ((is_alternate || op == _STDFQ_ || op == _STDCQ_) && (!s));

	//
	//
	// flush the ICACHE if it is an mmu-ctrl-register write.
	//
	//
	if((asi == ASI_MMU_REGISTER) || (asi == ASI_MMU_FLUSH_PROBE))
	{
#ifdef DEBUG
		fprintf(stderr,"\tInfo:executeStore: Flushing ICACHE due to MMU-CTRl-REGISTER-WRITE/FLUSH-PROBE (asi=0x%x) \n", asi);
#endif
		flushCache(state->icache);
	}

	if(is_privileged)
	{
		tv = setBit32(tv, _TRAP_, 1);
		tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1);
	}

	uint8_t is_not_alternate = ((op >= _STB_) && (op <= _STDCQ_));
	if(is_not_alternate)
	{
		setPageBit((CoreState*) state->parent_core_state, address); // flag all pages that were accessed.
		if( !s) addr_space = 10;
		else    addr_space = 11;
	}else
	{
		if(s) addr_space = asi;
	}

	uint8_t is_fp_trap = (((op == _STF_) || (op == _STDF_) || (op == _STFSR_) || (op == _STDFQ_)) && ((!ef) || !getBpFPUPresent(state)));

	if(!is_privileged && is_fp_trap) 
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _FP_DISABLED_, 1);
	}

	uint8_t is_cp_trap = (((op == _STC_) || (op == _STDC_) || (op == _STCSR_) || (op == _STDCQ_)) && ((!ec) || !getBpCPPresent(state)));
	if(!is_privileged && is_cp_trap)
	{
		tv = setBit32(tv, _TRAP_, 1);
		tv = setBit32(tv, _CP_DISABLED_, 1);
	}

	uint8_t misaligned_hw = (((op == _STH_) || (op == _STHA_)) && getBit32(address, 0));
	uint8_t misaligned_fw = (((op == _ST_) || (op == _STA_) || (op == _STF_) || (op == _STFSR_) || (op == _STC_) || (op == _STCSR_))
			&& getSlice32(address, 1, 0));
	uint8_t misaligned_dw = (((op == _STD_) || (op == _STDA_) || (op == _STDF_) || (op == _STDFQ_) || (op == _STDC_) || (op == _STDCQ_))
			&& getSlice32(address, 2, 0));

	uint8_t is_misaligned = (misaligned_hw || misaligned_fw || misaligned_dw);

	uint8_t is_trap = getBit32(tv, _TRAP_);

	if(!is_trap && is_misaligned)
	{
		tv = setBit32(tv, _TRAP_, 1);
		tv = setBit32(tv, _MEM_ADDRESS_NOT_ALIGNED_, 1);
	}

	uint8_t invalid_fp_reg = (!is_trap && !is_misaligned && (op == _STDF_) && getBit8(rd, 0));
	if(invalid_fp_reg)
	{

	tv =  setBit32(tv, _TRAP_, 1) ;
	tv =  setBit32(tv, _INVALID_FP_REGISTER_, 1) ;
	status_reg->fsr = setSlice32(fsr, 16, 14, 6) ;
	}

	// Note - Not implemented invalid_fp_register, no fp queue and no cp queue

	uint8_t byte_mask = 0;

	if((op == _STF_) || (op == _STC_) || (op == _STDF_) || \
			(op == _STDC_) || (op == _STD_) || (op == _STDA_) || (op == _STDFQ_) ||\
			(op == _STDCQ_) || (op == _STFSR_) || (op == _STCSR_) || (op == _ST_) || (op == _STA_))
	{
		byte_mask = 0xF ;
	}

	if (op == _STFSR_) data0 = status_reg->fsr ;
	if (op == _STCSR_) data0 = status_reg->csr ;

	if ((op == _STH_) || (op == _STHA_))
	{
		if (getSlice32(address, 1, 0) == 0) 
		{
			byte_mask = 0xC ;
			data0 = (data0 << 16) ;
		}
		else if (getSlice32(address, 1, 0) == 2) byte_mask = 0x3 ;
	}
	
	if ((op == _STB_) || (op == _STBA_))

	{
		if (getSlice32(address, 1, 0) == 0)  { byte_mask = 0x8 ; data0 = (data0 << 24) ;}
		if (getSlice32(address, 1, 0) == 1)  { byte_mask = 0x4 ; data0 = (data0 << 16) ;}
		if (getSlice32(address, 1, 0) == 2)  { byte_mask = 0x2 ; data0 = (data0 << 8)  ;}
		if (getSlice32(address, 1, 0) == 3)  { byte_mask = 0x1 ; }
	}

	uint8_t is_dw = (op == _STD_) || (op == _STDA_) || (op == _STDF_) || (op == _STDC_) || (op == _STDFQ_) || (op == _STDCQ_);
	uint8_t is_trap1 = getBit32(tv, _TRAP_);
	uint8_t mae1 = 0;
	
	if(!is_trap1)	
	{
			if(!is_dw)
			{
				//perform a memory access if this is not a double-word store
				writeData(state->mmu_state, state->dcache,
						addr_space, address, byte_mask, data0, &mae1);
			}
			else
			{
				uint64_t data64 = data0;
				data64 = data64<<32 | data1;
				
				//This is a double word store
				writeData64(state->mmu_state, state->dcache,
						addr_space, address , 0xFF, data64, &mae1);

			}



			//Log information about the store
			StateUpdateFlags* reg_update_flags = &(state->reg_update_flags);
			reg_update_flags->store_active=1;
			reg_update_flags->store_asi=addr_space;
			reg_update_flags->store_addr=address;
			if(is_dw)
			{
				reg_update_flags->store_double_word=1;
				reg_update_flags->store_byte_mask=0xFF;
				reg_update_flags->store_word_low=data1;
				reg_update_flags->store_word_high=data0;
			}
			else
			{
				reg_update_flags->store_double_word=0;
				// byte-mask shifted if write to upper word of double word.
				reg_update_flags->store_byte_mask=
					(((address & 0x4) != 0) ? byte_mask : (byte_mask << 4));
				reg_update_flags->store_word_low=data0;
			}


			//inform the HW server about the memory access
			inform_HW_server(state, GDB_MEM_ACCESS,  address);
			
			//Check mae
			if(mae1)
			{
				tv = setBit32(tv, _TRAP_, 1) ;
				tv = setBit32(tv, _DATA_ACCESS_EXCEPTION_, 1);
			}

			
	}
	return tv;
}

// 
// Potential candidate for Aa implementation.. This should be
// a Daemon which listens on a pipe and sends back response on
// a pipe.  So that its caller can be pipelined.
//
void testAndSetBlockLdstFlags(ThreadState* state, uint8_t byte_flag, uint8_t word_flag)
{
	while((getPbBlockLdstByte(state) == 1) || (getPbBlockLdstWord(state) == 1))
	{
	}
	setPbBlockLdstByte(state, byte_flag);
	setPbBlockLdstWord(state, word_flag);
}

uint32_t executeLdstub(Opcode op, 
				uint32_t operand1, uint32_t operand2, uint32_t *result, 
				StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags,
				uint32_t trap_vector, uint8_t asi, uint8_t *flags,
				ThreadState* state)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : LDSTUB  op-code=%x operand1=%x operand2=%x asi=%x\n", op, operand1, operand2,asi);
#endif 
	uint32_t tv = trap_vector;
	uint32_t psr = status_reg->psr;
	uint8_t s = getBit32(psr, 7);
	uint8_t f = *flags;

	uint8_t addr_space = 0;
	uint32_t data = 0;

	uint32_t address = operand1 + operand2;

	uint8_t is_not_alternate = (op == _LDSTUB_);
	if(is_not_alternate)
	{
		if(!s) addr_space =10;
		else   addr_space =11;
	}

	uint8_t is_alternate = (op == _LDSTUBA_);
	uint8_t is_privileged = (is_alternate && !s);
	
	if(is_privileged)
	{
		tv = setBit32(tv, _TRAP_, 1);
		tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1);
	}

	
	if(is_alternate && s) {addr_space= asi;}

	//
	// wait until both BlockLdstByte and BlockLdstWord are 0
	//
	if(!is_privileged)
		testAndSetBlockLdstFlags(state, 1, 0);
	uint8_t mae1=0;

	uint8_t byte_mask = 0;

	uint8_t address_10 = getSlice32(address, 1, 0);
	if(address_10 == 0) byte_mask = 0x8 ;
	if(address_10 == 1) byte_mask = 0x4 ;
	if(address_10 == 2) byte_mask = 0x2 ;
	if(address_10 == 3) byte_mask = 0x1 ;

	if(!is_privileged)
		lockAndReadData(state->mmu_state, state->dcache, addr_space, byte_mask, address, &mae1,&data);

	if(mae1)
	{
		tv = setBit32(tv, _TRAP_, 1);
		tv = setBit32(tv, _DATA_ACCESS_EXCEPTION_, 1);
	}

	uint8_t is_trap = getBit32(tv, _TRAP_);


	uint8_t mae2 = 0;
	if(!is_trap)
	{
		writeData(state->mmu_state, state->dcache,  addr_space, address, byte_mask, 0xFFFFFFFF, &mae2);
		
		//Log information about the store
		reg_update_flags->store_active=1;
		reg_update_flags->store_asi=addr_space;
		reg_update_flags->store_addr=address;
		reg_update_flags->store_double_word=0;
		reg_update_flags->store_byte_mask=
				(((address & 0x4) != 0)  ? byte_mask : (byte_mask << 4));
		reg_update_flags->store_word_low=0xFFFFFFFF;

	}

	// clear the LdstByte flag.
	if(!is_trap)
		setPbBlockLdstByte(state, 0);
	if(mae2)
	{
	tv = setBit32(tv, _TRAP_, 1);
	tv = setBit32(tv, _DATA_ACCESS_EXCEPTION_, 1);
	}

	uint8_t is_trap1 = getBit32(tv, _TRAP_);
	uint32_t word = 0;

	if(!is_trap1)
	{

		if (address_10 == 0) word = zeroExtendByte(getSlice32(data, 31, 24)) ;
		if (address_10 == 1) word = zeroExtendByte(getSlice32(data, 23, 16)) ;
		if (address_10 == 2) word = zeroExtendByte(getSlice32(data, 15, 8)) ;
		if (address_10 == 3) word = zeroExtendByte(getSlice32(data, 7, 0))  ;
	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);

	*result = word;
	*flags = f;

	return tv;
}

uint32_t executeSwap( Opcode op, 
			uint32_t operand1, uint32_t operand2, uint32_t *result, 
			StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags, 
			uint32_t trap_vector, uint8_t asi, uint8_t imm_flag,
			uint32_t temp, uint8_t *flags,
			ThreadState* state)
{
	//We assume a uniprocessor system.
	//Hence a swap is simply a load followed by a store.
	
#ifdef DEBUG
	fprintf(stderr,"\tInfo : DEBUGAP op-code=%x operand1=%x operand2=%x asi=%x\n", op, operand1, operand2,asi);
#endif 
	uint32_t tv = trap_vector;
	uint32_t psr = status_reg->psr;
	uint8_t s = getBit32(psr, 7);
	uint8_t f = *flags;
	uint8_t addr_space = 0;
	uint32_t address = 0;
	
	uint8_t is_privileged_trap = 0;
	uint8_t is_illegal_instr_trap = 0;
	uint8_t is_alignment_trap = 0;

	if(op==_SWAP_)
	{
		address = operand1+operand2;
		if(s==0) addr_space = 10;
		else addr_space = 11;
	}
	else if(op == _SWAPA_)
	{
		if(s==0)
		{
			tv = setBit32(tv, _TRAP_, 1);
			tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1);
			is_privileged_trap = 1;
		}
		else if(imm_flag)
		{
			tv = setBit32(tv, _TRAP_, 1);
			tv = setBit32(tv, _ILLEGAL_INSTRUCTION_, 1);
			is_illegal_instr_trap = 1;
		}
		else
		{
			address = operand1 + operand2;
			addr_space=asi;
		}
	}


	uint8_t b2bits = getSlice32(address, 1, 0);
	if(!is_privileged_trap && !is_illegal_instr_trap && (b2bits != 0))
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _MEM_ADDRESS_NOT_ALIGNED_, 1);
		is_alignment_trap = 1;
	}


	uint32_t word = 0;
	uint8_t mae1 = 0;
	if(!is_privileged_trap && !is_illegal_instr_trap && !is_alignment_trap) 
	{
		// wait until BlockLdstByte and BlockLdstWord are both 0
		testAndSetBlockLdstFlags(state, 0, 1);
		uint8_t load_byte_mask = 0xf;
		lockAndReadData(state->mmu_state,  state->dcache, addr_space, load_byte_mask, address, &mae1, &word);
		if(mae1)
		{
			tv = setBit32(tv, _TRAP_, 1) ;
			tv = setBit32(tv, _DATA_ACCESS_EXCEPTION_, 1);
		}
	}

	uint8_t is_trap = getBit32(tv, _TRAP_);
	uint8_t skip_write =  is_trap;
	uint8_t mae2 = 0;
	if(!skip_write)
	{
		writeData(state->mmu_state, state->dcache,  addr_space, address, 0xF, temp,&mae2);
		
		//Log information about the store
		reg_update_flags->store_active=1;
		reg_update_flags->store_asi=addr_space;
		reg_update_flags->store_addr=address;
		reg_update_flags->store_double_word=0;
		reg_update_flags->store_byte_mask=
				(((address & 0x4) != 0) ? 0xF : 0xF0);
		reg_update_flags->store_word_low=temp;

	}
	if(!is_trap)
		setPbBlockLdstWord(state, 0);
	if(mae2)
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _DATA_ACCESS_EXCEPTION_, 1) ;
	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags =  f;

	*result =  word;
	return tv;
}

// 32 bit compare and swap.
uint32_t executeCswap( Opcode op, 
				uint32_t operand1, 
				uint32_t operand2,
				uint32_t *result, 
				uint32_t operand3,
				uint32_t trap_vector, uint8_t asi, uint8_t imm_flag,
				ThreadState* state,
				StatusRegisters *status_reg, 
				StateUpdateFlags*  reg_update_flags,
				uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : CSWAP  op-code=0x%x operand1=0x%x operand2=0x%x operand3=0x%x\n", op, 
			operand1, 
			operand2, 
			operand3);
#endif 

	uint32_t tv = trap_vector;
	uint32_t psr = status_reg->psr;
	uint8_t s = getBit32(psr, 7);
	uint8_t f = *flags;
	uint8_t addr_space = 0;
	uint32_t address = 0;
	uint8_t is_privileged_trap = 0;
	uint8_t is_illegal_instr_trap = 0;
	if(op==_CSWAP_)
	{
		address = operand1;
		addr_space = (s ? 11 : 10);
	}
	else if(op == _CSWAPA_)
	{
		if(s==0)
		{
			tv = setBit32(tv, _TRAP_, 1);
			tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1);
			is_privileged_trap = 1;
		}
		else if(imm_flag)
		{
			tv = setBit32(tv, _TRAP_, 1);
			tv = setBit32(tv, _ILLEGAL_INSTRUCTION_, 1);
			is_illegal_instr_trap = 1;
		}
		else
		{
			address =  operand1;
			addr_space=asi;
		}
	}


	// address must be single word aligned.
	uint8_t is_alignment_trap = 0;
	uint8_t b2bits = getSlice32(address, 1, 0);
	if(!is_privileged_trap && !is_illegal_instr_trap && (b2bits != 0))
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _MEM_ADDRESS_NOT_ALIGNED_, 1);
		is_alignment_trap = 1;
	}


	uint8_t  mae 	   = 0;

	// byte mask for 32-bit read  (this is expanded to 64-bit read in lockAndReadData).
	uint8_t byte_mask = 0xf;

	if(!is_privileged_trap && !is_illegal_instr_trap && !is_alignment_trap) 
	{
		uint32_t read_data;
		lockAndReadData(state->mmu_state,  
					state->dcache, 
					addr_space, 
					byte_mask,
					address,
					&mae, 	
					&read_data);

		if(mae)
		{
			tv = setBit32(tv, _TRAP_, 1) ;
			tv = setBit32(tv, _DATA_ACCESS_EXCEPTION_, 1);
		}
		else
		{
			if(read_data == operand2)
			{
				// swap register with memory.
				writeData(state->mmu_state, 
						state->dcache,  
						addr_space, address, 
						byte_mask, 
						operand3,
						&mae);
				*result = read_data;
			}
			else
			{
				//
				// write back the word just read in order
				// to unlock the system bus.  This may
				// be wasteful but so what?
				//
				writeData(state->mmu_state, 
						state->dcache,  
						addr_space, 
						address, 
						byte_mask, 
						read_data,
						&mae);

				//
				// destination register maintains its old value.
				//
				*result  = operand3;
			}
		}
		if(mae)
		{
			tv = setBit32(tv, _TRAP_, 1) ;
			tv = setBit32(tv, _DATA_ACCESS_EXCEPTION_, 1) ;
		}
	}


	// result to be written back.
	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f;
	

	//return traps.
	return (tv);
}


//
// Implement in VHDL and make it a functionLibrary Aa element.
//
void executeLogical( Opcode op, uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg, StateUpdateFlags*  reg_update_flags,
			uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : LOGICAL  op-code=%x operand1=%x operand2=%x\n", op, operand1, operand2);
#endif 
	uint32_t res = 0;
	uint8_t f = *flags;

	 if ((op == _AND_) || (op == _ANDcc_)) 		res = (operand1 & operand2) 	;
	 else if ((op == _ANDN_) || (op == _ANDNcc_)) 	res = (operand1 & ~operand2)	;
	 else if ((op == _OR_) || (op == _ORcc_)) 	res = (operand1 | operand2) 	;
	 else if ((op == _ORN_) || (op == _ORNcc_)) 	res = (operand1 | ~operand2)	;
	 else if ((op == _XOR_) || (op == _XORcc_)) 	res = (operand1 ^ operand2) 	;
	 else if ((op == _XNOR_) || (op == _XNORcc_)) 	res = (operand1 ^ ~operand2)	;

	uint8_t modify_icc =  ((op == _ANDcc_) || (op == _ANDNcc_) || (op == _ORcc_) || (op == _ORNcc_) || (op == _XORcc_) 
					|| (op == _XNORcc_));

	 
	 if(modify_icc)
	 {
		 status_reg->psr = setBit32(status_reg->psr, 23, getBit32(res, 31)) ; //N flag
		 status_reg->psr = setBit32(status_reg->psr, 21, 0) ; //V flag
		 status_reg->psr = setBit32(status_reg->psr, 20, 0) ; //C flag
		 if(res == 0) 	 status_reg->psr = setBit32(status_reg->psr, 22, 1) ; //Z flag
		 if(!(res == 0))  status_reg->psr = setBit32(status_reg->psr, 22, 0) ; //Z flag

		 reg_update_flags->psr_updated=1;
	 }
	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f;

	*result = res;
}

// 
// Nothing.. is still something..
// map to an Aa statement
//
void executeNop()
{

#ifdef DEBUG
	fprintf(stderr,"\tInfo : NOP \n");
#endif 
}

// 
// Direct VHDL implementation.
//
void executeSethi( uint32_t operand1, uint32_t *result, uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : SETHI  operand1=%x\n", operand1);
#endif 
	uint32_t res = 0; // Do not change
	res = setSlice32(res, 31, 10, operand1);
	uint8_t f = *flags;

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags =f;    

	*result = res;
}

//
// Direct VHDL implementation
//
void executeShift(Opcode op, uint32_t operand1, uint32_t operand2, uint32_t *result, uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : SHIFT  op-code=%x operand1=%x operand2=%x\n",  op, operand1, operand2);
#endif 
	uint32_t res = 0;
	 if (op == _SLL_) 	res = (operand1 << operand2) ;
	 else if (op == _SRL_) res = (operand1 >> operand2) ;
	 else if (op == _SRA_) 
	 {
		 res = (operand1 >> operand2) ;
		 if(getBit32(operand1,31)==1 && operand2>0)
		 {
			 //need to fill the shifted bits with a 1
			 uint8_t bit_position; 
			 if(operand2==31) bit_position =0;
			 else bit_position = 31-operand2+1;
			 res = setSlice32(res,31, bit_position, 0xFFFFFFFF) ;
		 }
	 }

	uint8_t f = *flags;
	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f;

	*result = res;

}

//
// Direct VHDL implementation.. pipelined module!
//
void executeAdd( Opcode op, uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags, uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : ADD  op-code=%x operand1=%x operand2=%x\n", op, operand1, operand2);
#endif 
	uint32_t res = 0;
	uint8_t f = *flags;

	if 	((op == _ADD_) || (op == _ADDcc_))   res=  (operand1 + operand2) ;
	else if ((op == _ADDX_) || (op == _ADDXcc_)) res=  (operand1 + operand2 + getBit32(status_reg->psr, 20)) ;

	uint8_t modify_icc =  ((op == _ADDcc_) || (op == _ADDXcc_));

	uint8_t operand1_sign = getBit32(operand1, 31);
	uint8_t operand2_sign = getBit32(operand2, 31);
	uint8_t n = getBit32(res, 31);
	uint8_t z = ((res == 0) ? 1 : 0);
	uint8_t v = ((operand1_sign & operand2_sign & !n) | (!operand1_sign & !operand2_sign & n));
	uint8_t c = (operand1_sign & operand2_sign) | ((!n) & (operand1_sign | operand2_sign));

	if(modify_icc)
	{
	status_reg->psr =  setBit32(status_reg->psr, 23, n) ; //N flag
	status_reg->psr =  setBit32(status_reg->psr, 22, z) ; //Z flag
	status_reg->psr =  setBit32(status_reg->psr, 21, v) ; //V flag
	status_reg->psr =  setBit32(status_reg->psr, 20, c) ; //C flag
	
	reg_update_flags->psr_updated=1;
	}
	
	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f;

	*result = res;
}


//
// Direct VHDL implementation. .. pipelined module!
//
uint32_t executeTAdd( Opcode op, uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags,
		uint32_t trap_vector, uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : TADD op-code=%x operand1=%x operand2=%x\n", op, operand1, operand2);
#endif 
	uint32_t tv = trap_vector;
	uint8_t f = *flags;

	uint32_t res = operand1 + operand2;

	uint8_t operand1_sign = getBit32(operand1, 31);
	uint8_t operand2_sign = getBit32(operand2, 31);
	uint8_t n = getBit32(res, 31);

	uint8_t temp_v = ((operand1_sign && operand2_sign && !n) || (!operand1_sign && !operand2_sign && n)) || 
				((getSlice32(operand1, 1, 0) != 0) || (getSlice32(operand2, 1, 0) != 0));

	uint8_t is_trap = ((op == _TADDccTV_) && temp_v);
	if(is_trap)
	{
	tv = setBit32(tv, _TRAP_, 1);
	tv = setBit32(tv, _TAG_OVERFLOW_, 1);
	}

	uint8_t z = ((res == 0) ? 1 : 0);
	uint8_t v = temp_v;
	uint8_t c = (operand1_sign & operand2_sign) | ((!n) & (operand1_sign | operand2_sign));

	uint8_t modify_icc = !is_trap;

	if(modify_icc)
	{

	status_reg->psr = setBit32(status_reg->psr, 23, n) ; //N flag
	status_reg->psr = setBit32(status_reg->psr, 22, z) ; //Z flag
	status_reg->psr = setBit32(status_reg->psr, 21, v) ; //V flag
	status_reg->psr = setBit32(status_reg->psr, 20, c) ; //C flag
	reg_update_flags->psr_updated=1;

	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f; 

	*result = res; 
	return tv;
}

//
// Direct VHDL implementation. .. pipelined module!
//
void executeSub( Opcode op, uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags, 
			uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : SUB  op-code=%x operand1=%x operand2=%x\n", op, operand1, operand2);
#endif 
	uint32_t res = 0;
	uint8_t f = *flags;
	if((op == _SUB_) || (op == _SUBcc_))   res= (operand1 - operand2) ;
	else if((op == _SUBX_) || (op == _SUBXcc_)) res= (operand1 - operand2 - getBit32(status_reg->psr, 20));

	uint8_t modify_icc =  ((op == _SUBcc_) || (op == _SUBXcc_));

	uint8_t operand1_sign = getBit32(operand1, 31);
	uint8_t operand2_sign = getBit32(operand2, 31);

	uint8_t n = getBit32(res, 31);
	uint8_t z = ((res == 0) ? 1 : 0);
	uint8_t v = ((operand1_sign && (!operand2_sign) & (!n)) || ((!operand1_sign) && operand2_sign && n));
	uint8_t c = ((!operand1_sign) && operand2_sign) || (n && ((!operand1_sign) || operand2_sign));

	if(modify_icc)
	{

	status_reg->psr = setBit32(status_reg->psr, 23, n) ; //N flag
	status_reg->psr = setBit32(status_reg->psr, 22, z) ; //Z flag
	status_reg->psr = setBit32(status_reg->psr, 21, v) ; //V flag
	status_reg->psr = setBit32(status_reg->psr, 20, c) ; //C flag
	reg_update_flags->psr_updated=1;

	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f; 

	*result = res; 
}

//
// Direct VHDL implementation. .. pipelined module!
//
uint32_t executeTSub( Opcode op, uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags,
		uint32_t trap_vector, uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : TSUB  op-code=%x operand1=%x operand2=%x\n", op, operand1, operand2);
#endif 
	uint32_t tv = trap_vector;
	uint8_t f = *flags;

	uint32_t res = operand1 - operand2;

	uint8_t operand1_sign = getBit32(operand1, 31);
	uint8_t operand2_sign = getBit32(operand2, 31);
	uint8_t n = getBit32(res, 31);
	
	uint8_t temp_v = (  
			   ( operand1_sign	&& (!operand2_sign) && (!n)) 
			|| ( (!operand1_sign)   && operand2_sign    && n   ) 
			|| ((getSlice32(operand1, 1, 0) != 0) || (getSlice32(operand2, 1, 0) != 0))
			);
	
	
	uint8_t is_trap = ((op == _TSUBccTV_) && temp_v);
	if(is_trap)
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _TAG_OVERFLOW_, 1) ;
	}

	uint8_t z = ((res == 0) ? 1 : 0);
	uint8_t v = temp_v;
	uint8_t c = (	   ( (!operand1_sign) && operand2_sign)
			|| ( n && ((!operand1_sign) || operand2_sign) )
		    );
	
	uint8_t modify_icc =  !is_trap;
	if(modify_icc)
	{

	status_reg->psr =  setBit32(status_reg->psr, 23, n) ; //N flag
	status_reg->psr =  setBit32(status_reg->psr, 22, z) ; //Z flag
	status_reg->psr =  setBit32(status_reg->psr, 21, v) ; //V flag
	status_reg->psr =  setBit32(status_reg->psr, 20, c) ; //C flag
	reg_update_flags->psr_updated=1;

	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f; 

	*result = res; 

	return tv;
}

//
// Direct VHDL implementation. .. pipelined module!
//   Note: include pipelined multiplier.
//
void executeMul( Opcode op, uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags, 
			uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : MUL  op-code=%x operand1=%x operand2=%x\n", op, operand1, operand2);
#endif 
	uint64_t res_64 = 0;

	if( (op == _UMUL_) || (op == _UMULcc_))
	{
		//do unsigned multiplication
		uint64_t oprnd1 = operand1;
		uint64_t oprnd2 = operand2;
		res_64 = oprnd1 * oprnd2;
	}
	else if( (op == _SMUL_) || (op == _SMULcc_))
	{
		
		//do signed multiplication
		uint64_t oprnd1;
		uint64_t oprnd2;

		if(getBit32(operand1, 31)==1) oprnd1 = (uint64_t) ((int64_t)(-((int32_t) operand1))); else	oprnd1=operand1;
		if(getBit32(operand2, 31)==1) oprnd2 = (uint64_t) ((int64_t)(-((int32_t) operand2))); else	oprnd2=operand2;

		uint64_t s_res_64 = oprnd1 * oprnd2;

		//check signs of operands.
		if( (getBit32(operand1, 31)==1) ^ (getBit32(operand2, 31)==1))
		{
			//result would be negative
			s_res_64 = -s_res_64;
		}
		res_64=s_res_64;
	}

	uint8_t f = *flags;
	uint32_t res = getSlice64(res_64, 31, 0);

	//update Y
	{
		status_reg->y = getSlice64(res_64, 63, 32);
		reg_update_flags->y_updated=1;
	}
	uint8_t n = getBit32(res, 31);
	uint8_t z = ((res == 0) ? 1 : 0);
	uint8_t modify_icc =  ((op == _UMULcc_) || (op == _SMULcc_));

	if(modify_icc)
	{
	status_reg->psr = setBit32(status_reg->psr, 23, n) ; //N flag
	status_reg->psr = setBit32(status_reg->psr, 22, z) ; //Z flag
	status_reg->psr = setBit32(status_reg->psr, 21, 0) ; //V flag
	status_reg->psr = setBit32(status_reg->psr, 20, 0) ; //C flag
	reg_update_flags->psr_updated=1;

	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f ;

	*result = res; 
}


//
// What is this?
//
void executeMulStep( uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags, uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : MULSTEP  operand1=%x operand2=%x\n", operand1, operand2);
#endif 
	uint8_t f = *flags;

	uint32_t oprnd1 = (operand1 >> 1);
	uint32_t n1 = getBit32(status_reg->psr, 23);
	uint32_t v1 = getBit32(status_reg->psr, 21);

	oprnd1 = setBit32(oprnd1, 31, n1 ^ v1);
	uint32_t oprnd2 = ((getBit32(status_reg->y, 0) == 0) ? 0 : operand2);

	uint32_t res = oprnd1 + oprnd2;
	uint32_t y = ((status_reg->y) >> 1);
	y = setBit32(y, 31, getBit32(operand1, 0));

	//update Y
	{
		status_reg->y =  y;
		reg_update_flags->y_updated=1;
	}

	uint8_t oprnd1_sign = getBit32(oprnd1, 31);
	uint8_t oprnd2_sign = getBit32(oprnd2, 31);

	uint8_t n = getBit32(res, 31);
	uint8_t z = ((res == 0) ? 1 : 0);
	uint8_t v = ((oprnd1_sign & oprnd2_sign & !n) | (!oprnd1_sign & !oprnd2_sign & n));
	uint8_t c = (oprnd1_sign & oprnd2_sign) | ((!n) & (oprnd1_sign | oprnd2_sign));

	uint8_t modify_icc = 1;

	if(modify_icc)
	{
	status_reg->psr = setBit32(status_reg->psr, 23, n) ; //N flag
	status_reg->psr = setBit32(status_reg->psr, 22, z) ; //Z flag
	status_reg->psr = setBit32(status_reg->psr, 21, v) ; //V flag
	status_reg->psr = setBit32(status_reg->psr, 20, c) ; //C flag
	reg_update_flags->psr_updated=1;

	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f ;

	*result = res; 
}

uint32_t executeDiv( Opcode op, uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags,
		uint32_t trap_vector, uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : DIV  op-code=%x operand1=%x operand2=%x\n",  op, operand1, operand2);
#endif 
	uint32_t tv = trap_vector;
	uint8_t f = *flags;

	uint8_t div_by_zero_trap = 0;

	if(operand2 == 0)
	{
		tv = setBit32(tv, _TRAP_, 1);
		tv = setBit32(tv, _DIVISION_BY_ZERO_, 1) ;
		div_by_zero_trap = 1;
	}

	uint64_t oprnd1 = operand1;
	oprnd1 = setSlice64(oprnd1, 63, 32, status_reg->y);
	uint32_t oprnd2 = operand2;

	int64_t s_oprnd1 = oprnd1;
	int32_t s_oprnd2 = oprnd2;

	uint64_t res_64 = 0;
	uint32_t res = 0;

	uint8_t udiv = (op == _UDIV_) || (op == _UDIVcc_);
	uint8_t sdiv = (op == _SDIV_) || (op == _SDIVcc_);

	uint8_t temp_v = 0;
	 if(udiv )
	 {
		 res_64= divideUnsigned(oprnd1, oprnd2) ;
		 res = getSlice64(res_64, 31, 0);
		 if(getSlice64(res_64, 63, 32) == 0) temp_v =0;
		 else temp_v =1;
	 }
	 else if(sdiv)
	 {
		 res_64= divideSigned(s_oprnd1, s_oprnd2) ;
		 res = getSlice64(res_64, 31, 0);
		 if ( (getSlice64(res_64, 63, 31) == 0) 
				 || (getSlice64(res_64, 63, 31) == (uint64_t)0x1FFFFFFFF))
			 temp_v =0;
		 else
			 temp_v =1;
	 }
	
	if(temp_v)
	{
		if(udiv ) res=  0xFFFFFFFF ;
		else if(sdiv )
		{
			if(getBit64(res_64, 63)==0)
				res=  0x7FFFFFFF ;
			else
				res=  0x80000000 ;
		}
	}

	uint8_t modify_icc =  !div_by_zero_trap && ((op == _UDIVcc_) || (op == _SDIVcc_));

	uint8_t n = getBit32(res, 31);
	uint8_t z = ((res == 0) ? 1 : 0);
	uint8_t v = temp_v;
	uint8_t c = 0;
	if(modify_icc)
	{
	status_reg->psr = setBit32(status_reg->psr, 23, n) ; //N flag
	status_reg->psr = setBit32(status_reg->psr, 22, z) ; //Z flag
	status_reg->psr = setBit32(status_reg->psr, 21, v) ; //V flag
	status_reg->psr = setBit32(status_reg->psr, 20, c) ; //C flag
	reg_update_flags->psr_updated=1;

	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags =  f;

	*result =  res;

	return tv;
}

uint32_t executeSave( uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg,StateUpdateFlags* reg_update_flags, 
			uint32_t trap_vector, uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : SAVE  operand1=%x operand2=%x\n", operand1, operand2);
#endif 
	uint32_t tv = trap_vector;
	uint8_t cwp = getSlice32(status_reg->psr, 4, 0);
	uint8_t new_cwp = (uint8_t)(cwp - 1) % NWINDOWS;
	uint8_t f = *flags;

	uint8_t is_trap = ((status_reg->wim & (1 << new_cwp)) != 0);

	if(is_trap)
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _WINDOW_OVERFLOW_, 1);
#ifdef DEBUG
		fprintf(stderr,"\tInfo : A window overflow trap occured during a SAVE instruction at PC = 0x%x with CWP = 0x%x NEW_CWP=0x%x and WIM=0x%x\n",status_reg->pc, cwp, new_cwp, status_reg->wim);
#endif
	}

	uint32_t res = operand1 + operand2;

	if( !is_trap) 
	{
		status_reg->psr =  setSlice32(status_reg->psr, 4, 0, new_cwp);
		reg_update_flags->psr_updated=1;
	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f; 

	*result = res;

	return tv;
}

uint32_t executeRestore( uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags, 
			uint32_t trap_vector, uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : RESTORE  operand1=%x operand2=%x\n", operand1, operand2);
#endif 
	uint32_t tv = trap_vector;
	uint8_t cwp = getSlice32(status_reg->psr, 4, 0);
	uint8_t new_cwp = (uint8_t)(cwp + 1) % NWINDOWS;
	uint8_t f = *flags;

	uint8_t is_trap = ((status_reg->wim & (1 << new_cwp)) != 0);

	if(is_trap)
	{	
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _WINDOW_UNDERFLOW_, 1) ;
	}

	uint32_t res = operand1 + operand2;

	if(!is_trap)
	{
		status_reg->psr = setSlice32(status_reg->psr, 4, 0, new_cwp);
		reg_update_flags->psr_updated=1;
	}


	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f; 

	*result = res; 

	return tv;
}

uint32_t executeBicc( Opcode op, uint32_t operand1, StatusRegisters *status_reg, uint32_t trap_vector, uint8_t flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : BICC  op-code=%x operand1=%x\n", op, operand1);
#endif 
	uint32_t tv = trap_vector;
	uint8_t eval_icc = 0;
	uint32_t psr = status_reg->psr;

	uint8_t n = getBit32(psr, 23);
	uint8_t z = getBit32(psr, 22);
	uint8_t v = getBit32(psr, 21);
	uint8_t c = getBit32(psr, 20);
	switch(op)
	{
	case ( _BNE_) 	:{ eval_icc =  !z 			; break ; }
	case ( _BE_) 	:{ eval_icc =  z 			; break ; }
	case ( _BG_) 	:{ eval_icc =  !(z | (n ^ v)) 		; break ; }
	case ( _BLE_) 	:{ eval_icc =  (z | (n ^ v)) 		; break ; }
	case ( _BGE_) 	:{ eval_icc =  !(n ^ v) 		; break ; }
	case ( _BL_) 	:{ eval_icc =  (n ^ v) 			; break ; }
	case ( _BGU_) 	:{ eval_icc =  (!c & !z) 		; break ; }
	case ( _BLEU_)	:{ eval_icc =  (c | z) 			; break ; }
	case ( _BCC_) 	:{ eval_icc =  !c 			; break ; }
	case ( _BCS_) 	:{ eval_icc =  c 			; break ; }
	case ( _BPOS_)	:{ eval_icc =  !n 			; break ; }
	case ( _BNEG_)	:{ eval_icc =  n 			; break ; }
	case ( _BVC_) 	:{ eval_icc =  !v 			; break ; }
	case ( _BVS_) 	:{ eval_icc =  v 			; break ; }
	case ( _BA_) 	:{ eval_icc =  1 			; break ; }
	case ( _BN_) 	:{ eval_icc =  0 			; break ; }
	default : break;
	}


	uint32_t jmp_address = status_reg->pc + signExtend((operand1 << 2), 23);
	status_reg->pc = status_reg->npc; //Delay slot

	if(eval_icc)
	{
		status_reg->npc = jmp_address;
		if(op==_BA_ && (getBit8(flags, _ANNUL_FLAG_) == 1))
		{
			tv = setBit32(tv, _ANNUL_, 1);
		}
	}
	else
	{
		status_reg->npc = status_reg->npc + 4;
		if(getBit8(flags, _ANNUL_FLAG_) == 1)
		{
			tv = setBit32(tv, _ANNUL_, 1);
		}
	}
	return tv;
}

uint32_t executeBfpcc(ThreadState* s,
			Opcode op, uint32_t operand1, StatusRegisters *status_reg, uint32_t trap_vector, uint8_t flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : BFPCC op-code=%x operand1=%x\n", 	op, operand1);
#endif 
	uint32_t tv = trap_vector;
	uint8_t eval_fcc = 0;
	uint8_t fcc = getSlice32(status_reg->fsr, 11, 10);
	uint8_t e = (fcc == 0);
	uint8_t l = (fcc == 1);
	uint8_t g = (fcc == 2);
	uint8_t u = (fcc == 3);

	 switch(op)
	 {
	 case( _FBU_) 	: {eval_fcc = u 	;	break;}
	 case( _FBG_) 	: {eval_fcc = g 	;	break ; }
	 case( _FBUG_) 	: {eval_fcc = (g || u) ;        break ; }
	 case( _FBL_) 	: {eval_fcc = l 	;       break ; }
	 case( _FBUL_) 	: {eval_fcc = (l || u) ;        break ; }
	 case( _FBLG_) 	: {eval_fcc = (l || g) ;        break ; }
	 case( _FBNE_) 	: {eval_fcc = (l || g || u);    break ; }
	 case( _FBE_) 	: {eval_fcc = e 	;       break ; }
	 case( _FBUE_) 	: {eval_fcc = (e || u) ;        break ; }
	 case( _FBGE_) 	: {eval_fcc = (e || g) ;        break ; }
	 case( _FBUGE_) : {eval_fcc = (e || g || u);    break ; }
	 case( _FBLE_) 	: {eval_fcc = (e || l) 	;       break ; }
	 case( _FBULE_) : {eval_fcc = (e || l || u);    break ; }
	 case( _FBO_) 	: {eval_fcc = (e || l || g);    break ; }
	 case( _FBA_) 	: {eval_fcc = 1 	;       break ; }
	 case( _FBN_) 	: {eval_fcc = 0 	;       break ; }
	 default :break;
	  }                                             

	uint8_t fp_disabled = !getBpFPUPresent(s) || (getBit32(status_reg->psr, 12) == 0);
	uint8_t fp_exception = getBpFPUException(s);

	uint8_t is_trap = fp_disabled || fp_exception;

	if (is_trap      ) tv = setBit32(tv, _TRAP_, 1);
	if (fp_disabled  ) tv = setBit32(tv, _FP_DISABLED_, 1);
	if (fp_exception ) tv = setBit32(tv, _FP_EXCEPTION_, 1);

	uint32_t jmp_address = status_reg->pc + signExtend((operand1 << 2), 23);

	if(!is_trap)	status_reg->pc = status_reg->npc;// Delay slot
	if ( !is_trap && eval_fcc) status_reg->npc = jmp_address;
	if ( !is_trap && eval_fcc && (op == _FBA_) && (getBit8(flags, _ANNUL_FLAG_) == 1)) tv = setBit32(tv, _ANNUL_, 1);


	if( !is_trap && !eval_fcc) status_reg->npc = (status_reg->npc + 4);
	if ( !is_trap && !eval_fcc && (getBit8(flags, _ANNUL_FLAG_) == 1)) tv = setBit32(tv, _ANNUL_, 1) ;

	return tv;
}

uint32_t executeBcpcc( ThreadState* s, Opcode op, uint32_t operand1, StatusRegisters *status_reg, uint32_t trap_vector, uint8_t flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : BCPCC  op-code=%x operand1=%x\n", op, operand1);
#endif 
	uint32_t tv = trap_vector;
	uint8_t eval_bp_cp_cc = 0;
	uint8_t bp_cp_cc = getBpCPCc(s);

	uint8_t cpcc = getSlice32(bp_cp_cc, 1, 0);
	uint8_t c0 = (cpcc == 0);
	uint8_t c1 = (cpcc == 1);
	uint8_t c2 = (cpcc == 2);
	uint8_t c3 = (cpcc == 3);

	switch(op)
	{
	case ( _CB3_  ): { eval_bp_cp_cc = c3 ;				break;}
	case ( _CB2_  ): { eval_bp_cp_cc = c2 ;                         break ; }
	case ( _CB23_ ): { eval_bp_cp_cc = (c2 || c3) ;                 break ; }
	case ( _CB1_  ): { eval_bp_cp_cc = c1 ;                         break ; }
	case ( _CB13_ ): { eval_bp_cp_cc = (c1 || c3) ;                 break ; }
	case ( _CB12_ ): { eval_bp_cp_cc = (c1 || c2) ;                 break ; }
	case ( _CB123_): { eval_bp_cp_cc = (c1 || c2 || c3) ;           break ; }
	case ( _CB0_  ): { eval_bp_cp_cc = c0 ;                         break ; }
	case ( _CB03_ ): { eval_bp_cp_cc = (c0 || c3) ;                 break ; }
	case ( _CB02_ ): { eval_bp_cp_cc = (c0 || c2) ;                 break ; }
	case ( _CB023_): { eval_bp_cp_cc = (c0 || c2 || c3) ;           break ; }
	case ( _CB01_ ): { eval_bp_cp_cc = (c0 || c1) ;                 break ; }
	case ( _CB013_): { eval_bp_cp_cc = (c0 || c1 || c3) ;           break ; }
	case ( _CB012_): { eval_bp_cp_cc = (c0 || c1 || c2) ;           break ; }
	case ( _CBA_  ): { eval_bp_cp_cc = 1 ;                          break ; }
	case ( _CBN_  ): { eval_bp_cp_cc = 0 ;	break ; }
	default: break;


	}

	uint8_t cp_disabled = !getBpCPPresent(s) || (getBit32(status_reg->psr, 13) == 0);
	uint8_t cp_exception = getBpCPException(s);

	uint8_t is_trap = cp_disabled || cp_exception;
	if (is_trap      ) tv = setBit32(tv, _TRAP_, 1);
	if (cp_disabled  ) tv = setBit32(tv, _CP_DISABLED_, 1);
	if (cp_exception ) tv = setBit32(tv, _CP_EXCEPTION_, 1);


	uint32_t jmp_address = status_reg->pc + signExtend((operand1 << 2), 23);

	
	if(!is_trap) status_reg->pc =  status_reg->npc;
	if( !is_trap && eval_bp_cp_cc) status_reg->npc = jmp_address;
	if( !is_trap && eval_bp_cp_cc && (op == _CBA_) && (getBit8(flags, _ANNUL_FLAG_) == 1)) tv = setBit32(tv, _ANNUL_, 1);

	if( !is_trap && !eval_bp_cp_cc) status_reg->npc =  (status_reg->npc + 4);
	if( !is_trap && !eval_bp_cp_cc && (getBit8(flags, _ANNUL_FLAG_) == 1)) tv= setBit32(tv, _ANNUL_, 1);

	return tv;
}

uint32_t executeCoprocessor(uint32_t trap_vector)
{
	//Coprocessor instructons should generate a trap
#ifdef DEBUG
	fprintf(stderr,"\tInfo : _CPop1_ or _CPop2_ instruction Encountered");
#endif 
	uint32_t tv = trap_vector;
	//cause a CP_DISABLED trap
	tv = setBit32(tv, _TRAP_, 1);
	tv = setBit32(tv, _CP_DISABLED_, 1);
	return tv;
}

void executeCall(RegisterFile* rf,  uint32_t operand1, StatusRegisters *status_reg, StateUpdateFlags* suf)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : CALL  operand1=%x\n", operand1);
#endif 
	StatusRegisters sr = *status_reg;
	uint8_t cwp = getSlice32(sr.psr, 4, 0);
	writeRegister(rf, 15, cwp, sr.pc);

	// GPR is updated.
	suf->gpr_updated = 1;
        suf->reg_id = 15;
        suf->reg_val_low = sr.pc;

	uint32_t call_address = status_reg->pc + operand1;
	status_reg->pc =  status_reg->npc;
	status_reg->npc =  call_address;
}

uint32_t executeJumpAndLink( Opcode op, uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg, uint32_t trap_vector, uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : JumpAndLink  op-code=%x operand1=%x operand2=%x\n", 
				op, operand1, operand2);
#endif 

	uint32_t tv = trap_vector;
	uint8_t f = *flags;

	uint32_t jump_address = operand1 + operand2;

	uint8_t is_trap = getSlice32(jump_address, 1, 0);
	if(is_trap)
	{
	tv = setBit32(tv, _TRAP_, 1) ;
	tv = setBit32(tv, _MEM_ADDRESS_NOT_ALIGNED_, 1);
	}

	uint32_t res = (*status_reg).pc;
	if(!is_trap)
	{
		status_reg->pc  =  status_reg->npc ;
		status_reg->npc =  jump_address    ;
	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags =  f;

	*result = res;

	return tv;
}

uint32_t executeRett( Opcode op, uint32_t operand1, uint32_t operand2, uint32_t *result, StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags,
			uint32_t trap_vector, ThreadMode* p_mode)
{
	#ifdef DEBUG
	fprintf(stderr,"\tInfo : RETT  op-code=%x operand1=%x operand2=%x\n", op, operand1, operand2);
	#endif 
	
	uint32_t tv = trap_vector;
	ThreadMode mode = *p_mode;
	StatusRegisters sr = *status_reg;
	uint32_t psr = sr.psr;
	uint32_t tbr = sr.tbr;
	uint8_t cwp = getSlice32(psr, 4, 0);
	uint8_t new_cwp = (uint8_t)(cwp + 1) % NWINDOWS;
	uint32_t address = operand1 + operand2;
	uint8_t et = getBit32(psr, 5);
	uint8_t s = getBit32(psr, 7);
	uint8_t ps = getBit32(psr, 6);
	uint8_t tt = getSlice32(tbr, 11, 4);

	
	if(et)	    tv = setBit32(tv, _TRAP_, 1) ;
	if(et & !s) tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1) ;
	if(et & s)  tv = setBit32(tv, _ILLEGAL_INSTRUCTION_, 1) ;
	if(!et & !s)tv = setBit32(tv, _TRAP_, 1) ;
	if(!et & !s)tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1) ;
	if(!et & !s)tt = 3 ;
	
	if(!et & !s) mode = _ERROR_MODE_;

	uint8_t is_window_underflow = ((sr.wim & (1 << new_cwp)) != 0);
	if((!et) & s & is_window_underflow) tv = setBit32(tv, _TRAP_, 1) ;
	if((!et) & s & is_window_underflow) tv = setBit32(tv, _WINDOW_UNDERFLOW_, 1) ;
	if((!et) & s & is_window_underflow) tt = 6 ;
	if((!et) & s & is_window_underflow) mode = _ERROR_MODE_ ;

	uint8_t mem_address_not_aligned = (getSlice32(address, 1, 0) != 0);
	if((!et) & s & (!is_window_underflow) & mem_address_not_aligned)
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _MEM_ADDRESS_NOT_ALIGNED_, 1) ;
		tt = 7 ;
		mode = _ERROR_MODE_ ;
	}
	else if ((!et) & s & (!is_window_underflow) & (!mem_address_not_aligned))
	{
		psr = setBit32(psr, 5, 1) ;
		psr = setSlice32(psr, 4, 0, new_cwp) ;
		psr = setBit32(psr, 7, ps) ;

		//before updating pc,
		//remember the current value of pc 
		//for logging.
		reg_update_flags->pc=status_reg->pc;
				
		status_reg->pc = status_reg->npc ;
		status_reg->npc = address ;


	}
#ifdef DEBUG
	if(mode == _ERROR_MODE_)
	{
		fprintf(stderr,"\tInfo : Entering ERROR mode \n");
		fprintf(stderr,"\tInfo : in RETT instruction at PC = 0x%x\n",status_reg->pc);
		fprintf(stderr,"\tInfo : PSR = 0x%x\n",psr);
		fprintf(stderr,"\tInfo : ET  = %d\n",et);
		fprintf(stderr,"\tInfo : S   = %d\n",s);
		if(is_window_underflow)
		fprintf(stderr,"\tInfo : Window underflow = TRUE\n");
		if(mem_address_not_aligned)
		fprintf(stderr,"\tInfo : Mem Address Not Aligne = TRUE\n");
	}
#endif
	
	//update psr
	status_reg->psr =  psr;
	reg_update_flags->psr_updated=1;

	//update tbr
	status_reg->tbr =  setSlice32(sr.tbr, 11, 4, tt);
	//reg_update_flags->tbr_updated=1;

	*p_mode =  mode;

	return tv;
}

uint32_t executeTicc( Opcode op, uint32_t operand1, uint32_t operand2, StatusRegisters *status_reg,StateUpdateFlags* reg_update_flags, uint32_t trap_vector,
		uint8_t *ticc_trap_type)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : TICC  op-code=%x operand1=%x operand2=%x\n", op, operand1, operand2);
#endif 
	uint32_t tv = trap_vector;
	uint8_t trap_eval_icc = 0;
	uint32_t psr = status_reg->psr;
	uint8_t trap_type = *ticc_trap_type;

	uint8_t n = getBit32(psr, 23);
	uint8_t z = getBit32(psr, 22);
	uint8_t v = getBit32(psr, 21);
	uint8_t c = getBit32(psr, 20);

	switch(op)
	{
	 case(_TNE_) : {trap_eval_icc = !z ;			break;}
	 case(_TE_)  : {trap_eval_icc = z ;                     break;}
	 case(_TG_)  : {trap_eval_icc = !(z | (n ^ v)) ;        break;}
	 case(_TLE_) : {trap_eval_icc = (z | (n ^ v)) ;         break;}
	 case(_TGE_) : {trap_eval_icc = !(n ^ v) ;              break;}
	 case(_TL_)  : {trap_eval_icc = (n ^ v) ;               break;}
	 case(_TGU_) : {trap_eval_icc = (!c & !z) ;             break;}
	 case(_TLEU_): {trap_eval_icc = (c | z) ;               break;}
	 case(_TCC_) : {trap_eval_icc = !c ;                    break;}
	 case(_TCS_) : {trap_eval_icc = c ;                     break;}
	 case(_TPOS_): {trap_eval_icc = !n ;                    break;}
	 case(_TNEG_): {trap_eval_icc = n ;                     break;}
	 case(_TVC_) : {trap_eval_icc = !v ;                    break;}
	 case(_TVS_) : {trap_eval_icc = v ;                     break;}
	 case(_TA_)  : {trap_eval_icc = 1;                      break;}
	 case(_TN_)  : {trap_eval_icc = 0;                      break;}
	 default : break;
	}

	uint32_t trap_number = operand1 + operand2;
	if(trap_eval_icc)
	{

	  tv = setBit32(tv, _TRAP_, 1) ;
	  tv = setBit32(tv, _TRAP_INSTRUCTION_, 1) ;
	  trap_type = getSlice32(trap_number, 6, 0) ;
	} else
	{
		//before updating pc,
		//remember the current value of pc 
		//for logging.
		reg_update_flags->pc=status_reg->pc;
	//update pc	
	 status_reg->pc = status_reg->npc ;
	 status_reg->npc = (status_reg->npc + 4) ;
	}

	*ticc_trap_type =  trap_type;
#ifdef DEBUG
	{
		fprintf(stderr,"\tInfo : A Software Trap occured of type = %d at PC = 0x%x\n", trap_type, status_reg->pc);
	}
#endif

	return tv;
}

uint32_t executeReadStateReg( Opcode op, uint8_t rs1, uint32_t *result, 
					ThreadState* thread_state,
					uint32_t trap_vector,
					uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : ReadStateReg  op-code=%x rs1=%x\n", 
				op, rs1);
#endif 
	StatusRegisters* sr = &(thread_state->status_reg);
	uint32_t res = 0;
	uint32_t tv = trap_vector;
	uint32_t psr = sr->psr;
	uint8_t s = getBit32(psr, 7);
	uint8_t f = *flags;

	uint8_t is_privileged_instruction = ((!s) && ((op == _RDPSR_) || (op == _RDWIM_) || (op == _RDTBR_) || ((op == _RDASR_)
			&& (privilegedASR(rs1)))));

	uint8_t is_illegal_instruction_asr = illegalInstructionASR(rs1);

	 if (is_privileged_instruction || is_illegal_instruction_asr) tv = setBit32(tv, _TRAP_, 1) ;
	 if (is_privileged_instruction) tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1) ;
	 if (!is_privileged_instruction && is_illegal_instruction_asr) tv = setBit32(tv, _ILLEGAL_INSTRUCTION_, 1) ;

	switch(op)
	{
	case(_RDY_)   :{ res = sr->y ;		break;}
	case(_RDASR_) :
		       {
			       if((rs1 == 31) || (rs1 == 30))
			       {
				       uint64_t cycle_count = getCycleEstimate (thread_state);			
				       if(rs1 == 30)
				       {
					       cycle_count = cycle_count >> 32;
				       }
				       res = cycle_count & 0xffffffff;
			       }
			       else
				       res = sr->asr[rs1] ;    
		       }
		       break;
	case(_RDPSR_) :{ res = sr->psr ;         break;}

	case(_RDWIM_) :{ res = sr->wim;          break;}

	case(_RDTBR_) :{ res = sr->tbr ;         break;}
	default: break;
	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	*flags = f ;

	*result =  res;

	return tv;
}

uint32_t executeWriteStateReg( Opcode op, uint32_t operand1, uint32_t operand2, uint8_t rd, StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags, uint32_t trap_vector)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : WriteStateReg  op-code=%x operand1=%x operand2=%x\n", op, operand1, operand2);
#endif 
	uint32_t tv = trap_vector;
	StatusRegisters sr = *status_reg;
	uint32_t psr = sr.psr;
	uint8_t s = getBit32(psr, 7);

	uint32_t result = operand1 ^ operand2;

	//WRY
	if(op == _WRY_) 
	{
		status_reg->y = result;
	}

	uint8_t is_asr = (op == _WRASR_);

	uint8_t is_privileged_instruction_asr = (!s && (privilegedASR(rd)));
	if(is_asr && is_privileged_instruction_asr)
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1) ;
	}

	uint8_t is_illegal_instruction_asr = illegalInstructionASR(rd);
	if(is_asr && !is_privileged_instruction_asr && is_illegal_instruction_asr)
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _ILLEGAL_INSTRUCTION_, 1) ;
	}

	//WRASR
	if( is_asr && !is_privileged_instruction_asr && !is_illegal_instruction_asr)
	{
		if(rd < 29)
		{
			//
			// asr 29,30,31 are reserved read-only registers	
			// 
			status_reg->asr[rd] = result;
		}
	}

	uint8_t is_psr = (op == _WRPSR_);

	uint8_t is_privileged_instruction_psr = (!s);
	if(is_psr && is_privileged_instruction_psr)
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1) ;
	}

	uint8_t is_illegal_instruction_psr = (getSlice32(result, 4, 0) >= NWINDOWS);
	if(is_psr && is_illegal_instruction_psr)
	{
		tv = setBit32(tv, _TRAP_, 1) ;
		tv = setBit32(tv, _ILLEGAL_INSTRUCTION_, 1) ;
	}

	//WRPSR
	if( is_psr && !is_privileged_instruction_psr && !is_illegal_instruction_psr)
	{
		status_reg->psr = result ;
	}

	//WRWIM
	uint8_t is_wim = (op == _WRWIM_);

	uint8_t is_privileged_instruction_wim = (!s);
	 if(is_wim && is_privileged_instruction_wim)
	 {
	 tv = setBit32(tv, _TRAP_, 1) ;
	 tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1) ;
	 } 
	 else if( is_wim && !is_privileged_instruction_wim)
	 {
		 //Note: as per v8 bits in wim
		 //that correspond to unimplemented windows
		 //must read as zeros, and writes to them 
		 //should be ignored
		 int32_t mask = (1<<NWINDOWS) - 1;
		 status_reg->wim = result & mask;
	 }
	//WRTBR
	uint8_t is_tbr = (op == _WRTBR_);

	uint8_t is_privileged_instruction_tbr = (!s);
	 if(is_tbr && is_privileged_instruction_tbr)
	 {
	 tv = setBit32(tv, _TRAP_, 1) ;
	 tv = setBit32(tv, _PRIVILEGED_INSTRUCTION_, 1) ;
	 }else if( is_tbr && !is_privileged_instruction_tbr) 
	 {
		 status_reg->tbr = setSlice32(sr.tbr, 31, 12, getSlice32(result, 31, 12));
	 }

	 //Information to be logged:
	 if(tv==0)
	 {
		 if	(op == _WRY_)  {reg_update_flags->y_updated  =1; reg_update_flags->reg_val_low=result;}
		 else if(op == _WRPSR_){reg_update_flags->psr_updated=1; reg_update_flags->reg_val_low=result;}
		 else if(op == _WRWIM_){reg_update_flags->wim_updated=1; reg_update_flags->reg_val_low=result;}
		 else if(op == _WRTBR_){reg_update_flags->tbr_updated=1; reg_update_flags->reg_val_low=result;}
	 }
	return tv;
}

void executeStbar( uint8_t *store_barrier_pending, StateUpdateFlags* reg_update_flags, ThreadState* s)
{
	sendSTBAR(s->mmu_state, s->dcache);
#ifdef DEBUG
	fprintf(stderr,"\tInfo : STBAR \n");
#endif 
	*store_barrier_pending = 1 ;

	reg_update_flags->store_active=1;
	reg_update_flags->store_asi=0x0;
	reg_update_flags->store_addr=0x0;
	reg_update_flags->store_double_word=0;
	reg_update_flags->store_byte_mask=0x0;
	reg_update_flags->store_word_low=0;
	reg_update_flags->store_word_high=0;
}

uint32_t executeUnImplemented( uint32_t trap_vector)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : UNIMPLEMENTED \n");
#endif 
	uint32_t tv = trap_vector;
	tv = setBit32(tv, _TRAP_, 1);
	tv = setBit32(tv, _ILLEGAL_INSTRUCTION_, 1);

	return tv;
}

uint32_t executeFlush(uint32_t flush_addr, uint32_t trap_vector, StateUpdateFlags* reg_update_flags,
				ThreadState* state)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : FLUSH\n" );
#endif 
	//Flush D-cache
	//D-cache can be flushed by performing a
	//store-alternate with asi=ASI_FLUSH_I_D_CONTEXT
	uint8_t mae=0;
	writeData(state->mmu_state, state->dcache, ASI_FLUSH_I_D_CONTEXT, flush_addr, 0x00, 0x00, &mae);


	if(mae)
	{
		//An error occured while executing FLUSH!
		#ifdef SW
		fprintf(stderr,"\tInfo : An error occured while flushing Dcache in a FLUSH instruction\n" );
		#endif

	}

	
	//Flush I-cache
	uint8_t flush_asi = ASI_FLUSH_I_CONTEXT;
	uint8_t flush_mae=0;
	//address is ignored, the entire cache is flushed
	//as per current implementation if Icache
	flushIcacheLine(state->mmu_state,  state->icache, flush_asi, flush_addr, &flush_mae);

	if(flush_mae)
	{
		//An error occured while executing FLUSH!
		#ifdef SW
		fprintf(stderr,"\tInfo : An error occured while executing FLUSH instruction\n" );
		#endif

	}

	//if flush is unimplemented :
	//uint32_t tv = trap_vector;
	//tv = setBit32(tv, _TRAP_, 1);
	//tv = setBit32(tv, _UNIMPLEMENTED_FLUSH_, 1);
	
	//Log information about the store
	reg_update_flags->store_active=1;
	reg_update_flags->store_asi=ASI_FLUSH_I_D_CONTEXT;
	reg_update_flags->store_addr=flush_addr;
	reg_update_flags->store_double_word=0;
	reg_update_flags->store_byte_mask=0x0;
	reg_update_flags->store_word_low=0;
	reg_update_flags->store_word_high=0;


	return trap_vector;
}

uint32_t executeInstruction( 
				ThreadState *s, 
				Opcode opcode, 
				uint32_t operand2_0, uint32_t operand2_1, 
				uint32_t operand1_0, uint32_t operand1_1,
				uint32_t *result_h, uint32_t *result_l, 
				uint8_t *flags, 
				uint8_t rs1, uint8_t rd, uint8_t asi, 
				uint8_t imm_flag,
				uint32_t data1, uint32_t data0, uint8_t vector_data_type)
{
	uint32_t old_pc = s->status_reg.pc;


	uint32_t trap_vector = s->trap_vector;
	StatusRegisters *status_reg = &(s->status_reg);
	RegisterFile* rf = s->register_file;

	uint8_t is_load = ((opcode >= _LDSB_) && (opcode <= _LDDA_));
	uint8_t is_store = ((opcode >= _STB_) && (opcode <= _STDA_));
	uint8_t is_atomic = ((opcode == _LDSTUB_) || (opcode == _LDSTUBA_));
	uint8_t is_swap = ((opcode == _SWAP_) || (opcode == _SWAPA_));
	uint8_t is_cswap = ((opcode == _CSWAP_) || (opcode == _CSWAPA_));
	uint8_t is_sethi = (opcode == _SETHI_);
	uint8_t is_nop = (opcode == _NOP_);

	uint8_t is_logical    = ((opcode >= _AND_) && (opcode <= _XNORcc_));
	uint8_t is_logical_64 = ((opcode >= _ANDD_) && (opcode <= _XNORDcc_));

	uint8_t is_shift     = ((opcode >= _SLL_) && (opcode <= _SRA_));
	uint8_t is_shift_64  = ((opcode >= _SLLD_) && (opcode <= _SRAD_));

	uint8_t is_add    = ((opcode >= _ADD_) && (opcode <= _ADDXcc_));
	uint8_t is_add_64 = ((opcode >= _ADDD_) && (opcode <= _ADDDcc_));

	uint8_t is_tadd   = ((opcode == _TADDcc_) || (opcode == _TADDccTV_));

	uint8_t is_sub    = ((opcode >= _SUB_) && (opcode <= _SUBXcc_));
	uint8_t is_sub_64 = ((opcode >= _SUBD_) && (opcode <= _SUBDcc_));

	uint8_t is_tsub = ((opcode == _TSUBcc_) || (opcode == _TSUBccTV_));
	uint8_t is_mul_step = (opcode == _MULScc_);

	uint8_t is_multiply    = ((opcode >= _UMUL_) && (opcode <= _SMULcc_));
	uint8_t is_multiply_64 = ((opcode >= _UMULD_) && (opcode <= _SMULDcc_));

	uint8_t is_divide = ((opcode >= _UDIV_) && (opcode <= _SDIVcc_));
	uint8_t is_divide_64 = ((opcode >= _UDIVD_) && (opcode <= _SDIVDcc_));

	uint8_t is_save = (opcode == _SAVE_);
	uint8_t is_restore = (opcode == _RESTORE_);
	uint8_t is_bicc = ((opcode >= _BA_) && (opcode <= _BVS_));
	uint8_t is_bfpcc = ((opcode >= _FBA_) && (opcode <= _FBO_));
	uint8_t is_bcpcc = ((opcode >= _CBA_) && (opcode <= _CB012_));
	uint8_t is_call = ((opcode == _CALL_));
	uint8_t is_jmpl = (opcode == _JMPL_);
	uint8_t is_rett = (opcode == _RETT_);
	uint8_t is_ticc = ((opcode >= _TA_) && (opcode <= _TVS_));
	uint8_t is_read_state_reg = ((opcode >= _RDY_) && (opcode <= _RDTBR_));
	uint8_t is_write_state_reg = ((opcode >= _WRY_) && (opcode <= _WRTBR_));
	uint8_t is_stbar = (opcode == _STBAR_);
	uint8_t is_unimp = (opcode == _UNIMP_);
	uint8_t is_flush = (opcode == _FLUSH_);
	uint8_t is_coprocessor_op = ((opcode >= _CPop1_) && (opcode<=_CPop2_));

	uint8_t is_iu_simd = ((opcode >= _VADDD8_) && (opcode <= _VSMULD32_));
	uint8_t is_byte_reduce = ((opcode == _ADDDREDUCE8_) || 
			(opcode == _ANDDREDUCE8_) ||
			(opcode == _ORDREDUCE8_) ||
			(opcode == _XORDREDUCE8_));
	uint8_t is_halfword_reduce = ((opcode == _ADDDREDUCE16_) || 
			(opcode == _ANDDREDUCE16_) ||
			(opcode == _ORDREDUCE16_) ||
			(opcode == _XORDREDUCE16_));
	uint8_t is_byte_zpos = (opcode == _ZBYTEDPOS_);

	uint32_t tv=0;

	// for 32-bit case
	uint32_t operand1 = operand1_0;
	uint32_t operand2 = operand2_0;

	if(is_load)  		tv = 	executeLoad(opcode, operand1, operand2, result_h, result_l, status_reg, trap_vector, asi, rd, flags, s);
	else if(is_store) 	tv = 	executeStore(opcode, operand1, operand2, result_h, result_l, data0, data1, status_reg,trap_vector, asi, rd, s);
	else if(is_atomic) 	tv = 	executeLdstub(opcode, operand1, operand2, result_l, status_reg,&(s->reg_update_flags), trap_vector, asi, flags, s);
	else if(is_swap) 	tv = 	executeSwap(opcode, operand1, operand2, result_l, status_reg,&(s->reg_update_flags), trap_vector, asi, imm_flag, data0, flags, s);
	else if(is_cswap) 	tv = 	executeCswap(opcode, 
							operand1,  // rs1
						 	operand2,  // rs2
							result_l, // destination.
							data0,
							trap_vector, 
							asi, imm_flag, 
							s,
							status_reg,
							&(s->reg_update_flags),
							flags);
	else if(is_logical) 
		executeLogical(opcode, operand1, operand2, result_l, status_reg, &(s->reg_update_flags), flags);
	else if(is_logical_64)
		execute64BitLogical(opcode, operand1_0, operand1_1, operand2_0, operand2_1, result_h, result_l, status_reg, &(s->reg_update_flags), flags);
	else if(is_nop) 	     	executeNop();
	else if(is_sethi) 	       executeSethi(operand1, result_l, flags);
	else if(is_shift)  
		executeShift(opcode, operand1, operand2, result_l, flags);
	else if(is_shift_64)  
		execute64BitShift(opcode, operand1_0, operand1_1, operand2, result_h, result_l, 
					status_reg, &(s->reg_update_flags), 
					flags);
	else if(is_add) 
		executeAdd(opcode, operand1, operand2, result_l, 
					status_reg, &(s->reg_update_flags), 
					flags);
	else if(is_add_64)
			execute64BitAdd(opcode, operand1_0, operand1_1, 
						operand2_0, operand2_1, 
						result_h, result_l, 
						status_reg, &(s->reg_update_flags), 
						flags);
	else if(is_tadd)	tv = 	executeTAdd(opcode, operand1, operand2, result_l, status_reg, &(s->reg_update_flags), trap_vector, flags);
	else if(is_sub) 
		executeSub(opcode, operand1, operand2, result_l, status_reg, &(s->reg_update_flags),flags);
	else if(is_sub_64) 
		execute64BitSub(opcode, operand1_0, operand1_1, operand2_0, operand2_1, result_h, result_l, status_reg, &(s->reg_update_flags), flags);
	else if(is_tsub)	tv =	executeTSub(opcode, operand1, operand2, result_l, status_reg, &(s->reg_update_flags),trap_vector, flags);
	else if(is_multiply) 
		executeMul(opcode, operand1, operand2, result_l, status_reg, &(s->reg_update_flags),flags);
	else if(is_multiply_64)
		execute64BitMul(opcode, operand1_0, operand1_1, operand2_0, operand2_1, result_h, result_l, status_reg, &(s->reg_update_flags), flags);
	else if(is_mul_step)	       executeMulStep(operand1, operand2, result_l, status_reg, &(s->reg_update_flags),flags);
	else if(is_divide)	
	{
		tv = 	executeDiv(opcode, operand1, operand2, result_l, status_reg, &(s->reg_update_flags),trap_vector, flags);
		s->num_iu_divs_executed++;
	}
	else if(is_divide_64)
		tv = 	execute64BitDiv(opcode, operand1_0, operand1_1, 
						operand2_0, operand2_1, 
						result_h, result_l, 
						status_reg, &(s->reg_update_flags),
						trap_vector, flags);
	else if(is_save)	tv = 	executeSave(operand1, operand2, result_l, status_reg, &(s->reg_update_flags),trap_vector, flags);
	else if(is_restore)	tv = 	executeRestore(operand1, operand2, result_l, status_reg, &(s->reg_update_flags),trap_vector, flags);
	else if(is_bicc)	tv = 	executeBicc(opcode, operand1, status_reg, trap_vector, *flags);
	else if(is_bfpcc)	tv = 	executeBfpcc(s,opcode, operand1, status_reg, trap_vector, *flags);
	else if(is_bcpcc)	tv = 	executeBcpcc(s, opcode, operand1, status_reg, trap_vector, *flags);
	else if(is_call) 	     executeCall(rf, operand1, status_reg, &(s->reg_update_flags));
	else if(is_jmpl)	tv = 	executeJumpAndLink(opcode, operand1, operand2, result_l, status_reg, trap_vector, flags);
	else if(is_rett)	tv = 	executeRett(opcode, operand1, operand2, result_l, status_reg, &(s->reg_update_flags),trap_vector, &(s->mode));
	else if(is_ticc)	tv = 	executeTicc(opcode, operand1, operand2, status_reg,&(s->reg_update_flags), trap_vector, &(s->ticc_trap_type));
	else if(is_read_state_reg) 	tv =	executeReadStateReg(opcode, rs1, result_l, s, trap_vector, flags);
	else if(is_write_state_reg)	tv =	executeWriteStateReg(opcode, operand1, operand2, rd, status_reg, &(s->reg_update_flags), trap_vector);
	else if(is_stbar)		    	executeStbar(&(s->store_barrier_pending), &(s->reg_update_flags), s);
	else if(is_unimp)		tv =	executeUnImplemented(trap_vector);
	else if(is_flush)		tv =	executeFlush((operand1 + operand2), trap_vector,&(s->reg_update_flags), s);
	else if(is_byte_reduce)
		execute64BitReduce8 (opcode, 
						operand1_0, operand1_1, 
						operand2, 
						result_l, 
						status_reg, &(s->reg_update_flags), 
						flags);
	else if(is_halfword_reduce)
		execute64BitReduce16 (opcode, 
						operand1_0, operand1_1, 
						operand2, 
						result_l, 
						status_reg, &(s->reg_update_flags), 
						flags);
	else if(is_byte_zpos)
		execute64BitZBytePos   (opcode, operand1_0, operand1_1, operand2, result_l, status_reg, &(s->reg_update_flags), flags);
	else if (is_iu_simd) 
		execute64BitVectorOp (opcode, 
					vector_data_type,
					operand1_0, operand1_1, 
					operand2_0, operand2_1,
					result_h, result_l, 
					status_reg, &(s->reg_update_flags), 
					flags);
	else if(is_coprocessor_op)	tv = 	executeCoprocessor(trap_vector);

	if(opcode == _UNASSIGNED_) s->mode= _ERROR_MODE_ ;

	uint8_t is_cti = (is_bicc || is_bfpcc || is_bcpcc || is_call || is_jmpl || is_rett);
	if(is_cti)
	{
		uint32_t bp_nnpc;
		uint32_t bp_idx = 0;

		if(branchPrediction(&(s->branch_predictor), old_pc, &bp_idx, &bp_nnpc))
		{
			if(bp_nnpc != s->status_reg.npc) {
				incrementMispredicts (&(s->branch_predictor));
				updateBranchPredictEntry(&(s->branch_predictor), bp_idx, s->status_reg.npc);
			}
		}
		else
		{
			if((s->status_reg.pc+4) != s->status_reg.npc)
			{
				incrementMispredicts (&(s->branch_predictor));
			}
			addBranchPredictEntry(&(s->branch_predictor), old_pc, s->status_reg.npc);
		}
	}

#ifdef SW
	if(s->mode == _ERROR_MODE_)
	{
		fprintf(stderr,"Entering ERROR mode\n" );
		fprintf(stderr,"encountered instruction with UNASSIGNED opcode \n");
		fprintf(stderr,"at PC = 0x%x, npc=0x%x, psr=0x%x, wim=0x%x\n",
				s->status_reg.pc,
				s->status_reg.npc,
				s->status_reg.psr,
				s->status_reg.wim
				);
		fprintf(stderr," instruction word = 0x%x\n",s->instruction);
	}
#endif

	return tv;

}

void trapToString (uint32_t tv, uint8_t intrpt_level, uint8_t ticc_trap_type, char* tt)
{
	uint8_t reset_trap = getBit32(tv, _RESET_TRAP_);
	sprintf(tt,"NO_TRAP");
	if(!reset_trap)
	{
	 if(getBit32(tv, _DATA_STORE_ERROR_) )			sprintf(tt,"DATA_STORE_ERROR");
	 else if(getBit32(tv, _INSTRUCTION_ACCESS_ERROR_) )	sprintf(tt,"INSTR_ACCESS_ERROR");
	 else if(getBit32(tv, _R_REGISTER_ACCESS_ERROR_) )	sprintf(tt,"R_REG_ACCESS_ERROR");
	 else if(getBit32(tv, _INSTRUCTION_ACCESS_EXCEPTION_) )	sprintf(tt,"INSTR_ACCESS_EXCEPTION");
	 else if(getBit32(tv, _PRIVILEGED_INSTRUCTION_) )	sprintf(tt,"PRIVILEGED_INSTR");
	 else if(getBit32(tv, _ILLEGAL_INSTRUCTION_) )		sprintf(tt,"ILLEGAL_INSTR");
	 else if(getBit32(tv, _FP_DISABLED_) )			sprintf(tt,"FP_DISABLED");
	 else if(getBit32(tv, _CP_DISABLED_) )			sprintf(tt,"CP_DISABLED");
	 else if(getBit32(tv, _UNIMPLEMENTED_FLUSH_) )		sprintf(tt,"UNIMPLEMENTED_FLUSH");
	 else if(getBit32(tv, _WINDOW_OVERFLOW_) )		sprintf(tt,"WINDOW_OVERFLOW");
	 else if(getBit32(tv, _WINDOW_UNDERFLOW_) )		sprintf(tt,"WINDOW_UNDERFLOW");
	 else if(getBit32(tv, _MEM_ADDRESS_NOT_ALIGNED_) ) 	sprintf(tt,"MEM_ADDR_NOT_ALIGNED");
	 else if(getBit32(tv, _FP_EXCEPTION_) )			sprintf(tt,"FP_EXCEPTION");
	 else if(getBit32(tv, _CP_EXCEPTION_) )			sprintf(tt,"CP_EXCEPTION");
	 else if(getBit32(tv, _DATA_ACCESS_ERROR_) )		sprintf(tt,"DATA_ACCESS_ERROR");
	 else if(getBit32(tv, _DATA_ACCESS_EXCEPTION_) )	sprintf(tt,"DATA_ACCESS_EXCEPTION");
	 else if(getBit32(tv, _TAG_OVERFLOW_) )			sprintf(tt,"TAG_OVERFLOW");
	 else if(getBit32(tv, _DIVISION_BY_ZERO_) )		sprintf(tt,"DIV_BY_ZERO");
	 else if(getBit32(tv, _TRAP_INSTRUCTION_) )		sprintf(tt,"TRAP_INSTR_TRAP (ta %d)\n", ticc_trap_type);
	 else if((intrpt_level > 0) )				sprintf(tt,"INTERRUPT (level=%d)\n", intrpt_level);
	}
	else sprintf(tt,"RESET_TRAP");

	return;
}

void selectTrap( uint32_t *trap_vector, uint32_t *tbr, uint8_t et, ThreadMode *p_mode, uint8_t *interrupt_level,
		uint8_t ticc_trap_type)
{
	uint32_t tv = *trap_vector;
	uint8_t tt = 0;
	uint8_t intrpt_level = *interrupt_level;
	ThreadMode mode = *p_mode;

	uint8_t reset_trap = getBit32(tv, _RESET_TRAP_);

	if(!reset_trap)
	{
	 if(!et) 					mode	= _ERROR_MODE_ ;
	 if(getBit32(tv, _DATA_STORE_ERROR_) )			tt= 0x2B ;
	 else if(getBit32(tv, _INSTRUCTION_ACCESS_ERROR_) )	tt= 0x21 ;
	 else if(getBit32(tv, _R_REGISTER_ACCESS_ERROR_) )	tt= 0x20 ;
	 else if(getBit32(tv, _INSTRUCTION_ACCESS_EXCEPTION_) )	tt= 0x1 ;
	 else if(getBit32(tv, _PRIVILEGED_INSTRUCTION_) )	tt= 0x3 ;
	 else if(getBit32(tv, _ILLEGAL_INSTRUCTION_) )		tt= 0x2 ;
	 else if(getBit32(tv, _FP_DISABLED_) )			tt= 0x4 ;
	 else if(getBit32(tv, _CP_DISABLED_) )			tt= 0x24 ;
	 else if(getBit32(tv, _UNIMPLEMENTED_FLUSH_) )		tt= 0x25 ;
	 else if(getBit32(tv, _WINDOW_OVERFLOW_) )		tt= 0x5 ;
	 else if(getBit32(tv, _WINDOW_UNDERFLOW_) )		tt= 0X6 ;
	 else if(getBit32(tv, _MEM_ADDRESS_NOT_ALIGNED_) ) 	tt= 0x7 ;
	 else if(getBit32(tv, _FP_EXCEPTION_) )			tt= 0x8 ;
	 else if(getBit32(tv, _CP_EXCEPTION_) )			tt= 0x28 ;
	 else if(getBit32(tv, _DATA_ACCESS_ERROR_) )		tt= 0x29 ;
	 else if(getBit32(tv, _DATA_ACCESS_EXCEPTION_) )	tt= 0x9 ;
	 else if(getBit32(tv, _TAG_OVERFLOW_) )			tt= 0xA ;
	 else if(getBit32(tv, _DIVISION_BY_ZERO_) )		tt= 0x2A ;
	 else if(getBit32(tv, _TRAP_INSTRUCTION_) )		tt= setBit8(ticc_trap_type, 7, 1) ;
	 else if((intrpt_level > 0) )				tt= setBit8(intrpt_level, 4, 1) ;
	}

	tv =  setBit32(tv, _TRAP_, 0) ;
	tv =  setBit32(tv, _INSTRUCTION_ACCESS_EXCEPTION_, 0) ;
	tv =  setBit32(tv, _ILLEGAL_INSTRUCTION_, 0) ;
	tv =  setBit32(tv, _PRIVILEGED_INSTRUCTION_, 0) ;
	tv =  setBit32(tv, _FP_DISABLED_, 0) ;
	tv =  setBit32(tv, _CP_DISABLED_, 0) ;
	tv =  setBit32(tv, _WINDOW_OVERFLOW_, 0) ;
	tv =  setBit32(tv, _WINDOW_UNDERFLOW_, 0) ;
	tv =  setBit32(tv, _MEM_ADDRESS_NOT_ALIGNED_, 0) ;
	tv =  setBit32(tv, _FP_EXCEPTION_, 0) ;
	tv =  setBit32(tv, _CP_EXCEPTION_, 0) ;
	tv =  setBit32(tv, _DATA_ACCESS_EXCEPTION_, 0) ;
	tv =  setBit32(tv, _TAG_OVERFLOW_, 0) ;
	tv =  setBit32(tv, _DIVISION_BY_ZERO_, 0) ;
	tv =  setBit32(tv, _TRAP_INSTRUCTION_, 0) ;

	*interrupt_level = 0;
	*trap_vector = tv;
	*tbr = setSlice32(*tbr, 11, 4, tt);
	*p_mode =  mode ;
	
#ifdef DEBUG
	fprintf(stderr,"A Trap occured. tt=0x%x\n",tt);
	
	if(mode == _ERROR_MODE_)
	{
		fprintf(stderr,"Entering ERROR mode\n" );
		fprintf(stderr,"executeTraps() called with Enable trap bit = 0 \n");
		fprintf(stderr,"tt = 0x%x\n",tt);
	}
#endif

}

void executeTrap(ThreadState* thread_state,
			 uint32_t *trap_vector, uint32_t *psr, uint32_t *tbr, 
			 uint8_t *interrupt_level, ThreadMode *p_mode,
			 uint8_t ticc_trap_type, uint32_t *pc, uint32_t *npc)
{

	
	RegisterFile* rf = thread_state->register_file;

	char trap_buffer[256];
	trapToString(*trap_vector, *interrupt_level, ticc_trap_type, trap_buffer);

	if (thread_state->report_traps)
		fprintf(stderr,"\nTRAP (core=%d,thread=%d): pc=0x%08x npc=0x%08x psr=0x%08x  wim=0x%08x tv=0x%08x\t%s\n", 
				thread_state->core_id,
				thread_state->thread_id,
				*pc, *npc, *psr,
				thread_state->status_reg.wim,
				*trap_vector, trap_buffer);

	uint32_t psr_tmp = *psr;
	uint8_t et = getBit32(psr_tmp, 5);

	selectTrap( trap_vector, tbr, et, p_mode, interrupt_level, ticc_trap_type);

	uint8_t tv = *trap_vector;

	uint8_t is_error_mode = (*p_mode == _ERROR_MODE_);
	uint8_t is_annul = getBit32(tv, _ANNUL_);
	uint8_t s = getBit32(psr_tmp, 7); // Supervisor Bit
	uint8_t cwp = getSlice32(psr_tmp, 4, 0);
	uint8_t new_cwp = (uint8_t)(cwp - 1) % NWINDOWS;

	if(!is_error_mode)
	{
	psr_tmp = setBit32(psr_tmp, 5, 0) ; // Enable Trap - ET 
	psr_tmp = setBit32(psr_tmp, 6, s) ; // Previous Supervisor Bit - PS
	psr_tmp = setSlice32(psr_tmp, 4, 0, new_cwp) ;
	}

	uint32_t pc_tmp = *pc;
	uint32_t npc_tmp = *npc;

	uint8_t skip_write1 = ( is_error_mode || is_annul);
	if(!skip_write1)
	{
		writeRegister(rf, 17, new_cwp, pc_tmp); // %l1
		writeRegister(rf, 18, new_cwp, npc_tmp);// %l2
   	}

	uint8_t skip_write2 = ( is_error_mode || !is_annul);
	if(!skip_write2)
	{
		writeRegister(rf, 17, new_cwp, npc_tmp); // %l1
		writeRegister(rf, 18, new_cwp, (npc_tmp + 4)); // %l2
	}
	if(!skip_write2) tv = setBit32(tv, _ANNUL_, 0);

	 if(!is_error_mode) psr_tmp = setBit32(psr_tmp, 7, 1) ; //supervisor bit

	uint8_t is_reset_trap = getBit32(tv, _RESET_TRAP_);

	uint32_t tbr_tmp = *tbr;

	uint8_t skip_write3 = ( is_error_mode || is_reset_trap);

	if(!skip_write3)
	{
		pc_tmp = tbr_tmp ;
		npc_tmp = (tbr_tmp + 4) ;
	}

	uint8_t skip_write4 = ( is_error_mode || !is_reset_trap);

	//pc_tmp = !skip_write4 ? 0 : pc_tmp;
	//npc_tmp = !skip_write4 ? 4 : npc_tmp;
	if(!skip_write4 )
	{
	 
	  // The starting value of PC and NPC
	  // are model parameters defined in 
	  //C/common/include/Ajit_Hardware_Configuration.h
	  //
	  // But we override with parameter init_pc in  processor state.
	  // 
	  pc_tmp  = thread_state->init_pc;
	  npc_tmp = thread_state->init_pc  + 4;

	  tv      = setBit32(tv, _RESET_TRAP_, 0) ;
	}

	*trap_vector = tv;
	*pc = pc_tmp;
	*npc = npc_tmp;

	*psr =  psr_tmp ;
}

uint32_t executeIntegerToFloat( Opcode op, uint32_t operand2_0, uint32_t *result_h2, uint32_t *result_h1, 
				uint32_t *result_l2, uint32_t *result_l1, uint32_t trap_vector, uint8_t *flags, uint8_t *ft, uint32_t *fsr)
{
	uint32_t tv = 0;
	uint8_t f = *flags;

	int32_t oprnd2_32 = operand2_0;

	switch(op)
	{
	case (_FiTOs_) : {f = setBit8(f, _SINGLE_RESULT_, 1) ; break;}
	case (_FiTOd_) : {f = setBit8(f, _DOUBLE_RESULT_, 1) ; break;}
	case (_FiTOq_) : {f = setBit8(f, _QUAD_RESULT_, 1)   ; break;}
	default: break;
	}

	float res_32_tmp = 0;
	double res_64_tmp = 0;

	if(op == _FiTOs_) res_32_tmp = (float) oprnd2_32 ;
	if(op == _FiTOd_) res_64_tmp = (double) oprnd2_32 ;

	uint32_t res_32 = _BITCAST_(uint32_t,res_32_tmp);
	uint64_t res_64 = _BITCAST_(uint64_t,res_64_tmp);
	
	if (op == _FiTOs_) *result_l1 = res_32 ;
	if (op == _FiTOd_) *result_l1 = getSlice64(res_64, 31, 0) ;
	if (op == _FiTOd_) *result_l2 = getSlice64(res_64, 63, 32) ;


	*flags =  f;
	*ft = 1; // complete bit is set.

	return tv;

}

uint32_t executeFloatToInteger( Opcode op, uint32_t operand2_3, uint32_t operand2_2, uint32_t operand2_1, 
		uint32_t operand2_0, uint32_t *result, uint32_t trap_vector, uint8_t *flags, uint8_t *ft, uint32_t *fsr)
{
	uint32_t tv = trap_vector;
	uint8_t f_trap = *ft;
	uint8_t f = *flags;

	float oprnd2_32 = _BITCAST_(float,operand2_0);
	uint64_t oprnd2_64_tmp = operand2_0;
	oprnd2_64_tmp = setSlice64(oprnd2_64_tmp, 63, 32, operand2_1);
	double oprnd2_64 = _BITCAST_(double,oprnd2_64_tmp);

	f = setBit8(f, _SINGLE_RESULT_, 1);

	uint32_t res = 0;

	// overflow/underflow traps?
	if (op == _FsTOi_) res = (int32_t) oprnd2_32 ;
	if (op == _FdTOi_) res = (int32_t) oprnd2_64 ;

	

	// IEEE-754 Exception
	if (isFpInvalidOp(op, oprnd2_32, 0.0, oprnd2_64, 0.0))
	{
		if(isNvmSet(*fsr))
		{
			tv = setBit32(tv, _TRAP_, 1) ;
			tv = setBit32(tv, _FP_EXCEPTION_, 1) ;
		}

		f_trap = setSlice8(f_trap, 5, 1, 0x10); // NVC bit set.. texc

		*fsr = setSlice32((*fsr), 16, 14, _IEEE_754_EXCEPTION_);
		*fsr = setBit32((*fsr), _NVC_, 1);
	}
	else
		f_trap = setSlice8(f_trap, 5, 1, 0); //texc

	// no deferring.
	f_trap = setBit8(f_trap, 0, 1); //c

	*result =  res;

	*flags = f;
	*ft = f_trap ;

	return tv;
}

uint32_t executeFloatToFloat( Opcode op, uint32_t operand2_3, uint32_t operand2_2, uint32_t operand2_1, uint32_t operand2_0,
			 	uint32_t *result_h2, uint32_t *result_h1,uint32_t *result_l2, uint32_t *result_l1, uint32_t trap_vector, 
				uint8_t *flags, uint8_t *ft, uint32_t *fsr)
{
	uint32_t tv = trap_vector;
	uint8_t f_trap = *ft;
	uint8_t f = *flags;

	float oprnd2_32 = _BITCAST_(float,operand2_0);
	uint64_t oprnd2_64_tmp = operand2_0;
	oprnd2_64_tmp = setSlice64(oprnd2_64_tmp, 63, 32, operand2_1);
	double oprnd2_64 = _BITCAST_(double,oprnd2_64_tmp);

	if ((op == _FdTOs_) || (op == _FqTOs_)) f = setBit8(f, _SINGLE_RESULT_, 1) ;
	if ((op == _FsTOd_) || (op == _FqTOd_)) f = setBit8(f, _DOUBLE_RESULT_, 1) ;
	if ((op == _FsTOq_) || (op == _FdTOq_)) f = setBit8(f, _QUAD_RESULT_, 1) ;

	float res_32_tmp = 0;
	double res_64_tmp = 0;

	if (op == _FsTOd_) res_64_tmp = (double) oprnd2_32 ;
	if (op == _FdTOs_) res_32_tmp = (float) oprnd2_64 ;

	uint32_t res_32 = _BITCAST_(uint32_t,res_32_tmp);
	uint64_t res_64 = _BITCAST_(uint64_t,res_64_tmp);
	

	// IEEE-754 Exception
	if (isFpInvalidOp(op, oprnd2_32, 0.0, oprnd2_64, 0.0))
	{
		if(isNvmSet(*fsr))
		{
			tv = setBit32(tv, _TRAP_, 1) ;
			tv = setBit32(tv, _FP_EXCEPTION_, 1) ;
		}
		f_trap = setSlice8(f_trap, 5, 1, 0x10); // NVC bit set.. texc
		*fsr = setSlice32((*fsr), 16, 14, _IEEE_754_EXCEPTION_);
		*fsr = setBit32((*fsr), _NVC_, 1);
	}
	else 
		f_trap = setSlice8(f_trap, 5, 1, 0); //texc

	// no deferring.
	f_trap = setBit8(f_trap, 0, 1); //c

	if (op == _FdTOs_) *result_l1 = res_32 ;
	if (op == _FsTOd_) *result_l1 = getSlice64(res_64, 31, 0) ;
	if (op == _FsTOd_) *result_l2 = getSlice64(res_64, 63, 32) ;

	*flags = f;
	*ft = f_trap;

	return tv;
}

uint32_t executeFloatMove(Opcode op, uint32_t operand2_0, uint32_t *result, uint32_t trap_vector, uint8_t *flags, uint8_t *ft)
{
	uint32_t tv = trap_vector;
	uint8_t f_trap = *ft;
	uint8_t f = *flags;
	uint32_t res = 0;

	f = setBit8(f, _SINGLE_RESULT_, 1);
	if (op == _FMOVs_) res = operand2_0 ;
	else if (op == _FNEGs_) res = (operand2_0 ^ 0x80000000) ;
	else if (op == _FABSs_) res = (operand2_0 & 0x7FFFFFFF) ;

	f_trap = setSlice8(f_trap, 5, 1, 0); //texc
	f_trap = setBit8(f_trap, 0, 1); //c

	*result =  res;

	*flags =  f ;
	*ft =  f_trap ;

	return tv;

}

uint32_t executeFloatSqrt( Opcode op, uint32_t operand2_3, uint32_t operand2_2, uint32_t operand2_1, uint32_t operand2_0,
		uint32_t operand1_3, uint32_t operand1_2, uint32_t operand1_1, uint32_t operand1_0, uint32_t *result_h2, uint32_t *result_h1,
		uint32_t *result_l2, uint32_t *result_l1, uint32_t trap_vector, uint8_t *flags, uint8_t *ft, uint32_t *fsr)
{
	uint32_t tv = trap_vector;
	uint8_t f_trap = *ft;
	uint8_t f = *flags;

	float oprnd2_32 = _BITCAST_(float,operand2_0);
	uint64_t oprnd2_64_tmp = operand2_0;
	oprnd2_64_tmp = setSlice64(oprnd2_64_tmp, 63, 32, operand2_1);
	double oprnd2_64 = _BITCAST_(double,oprnd2_64_tmp);

	if (op == _FSQRTs_) f = setBit8(f, _SINGLE_RESULT_, 1) ;
	else if (op == _FSQRTd_) f = setBit8(f, _DOUBLE_RESULT_, 1) ;
	else if (op == _FSQRTq_) f = setBit8(f, _QUAD_RESULT_, 1) ;

	float res_32_tmp = 0;
	double res_64_tmp = 0;

	if (op == _FSQRTs_) res_32_tmp = doubleSqrt(oprnd2_32) ;
	else if (op == _FSQRTd_) res_64_tmp = doubleSqrt(oprnd2_64) ;

	uint32_t res_32 = _BITCAST_(uint32_t,res_32_tmp);
	uint64_t res_64 = _BITCAST_(uint64_t,res_64_tmp);




	// IEEE-754 Exception
	if (isFpInvalidOp(op, oprnd2_32, 0.0, oprnd2_64, 0.0))
	{
		if(isNvmSet(*fsr))
		{
			tv = setBit32(tv, _TRAP_, 1) ;
			tv = setBit32(tv, _FP_EXCEPTION_, 1) ;
		}

		f_trap = setSlice8(f_trap, 5, 1, 0x10); // NVC bit set.. texc
		*fsr = setSlice32((*fsr), 16, 14, _IEEE_754_EXCEPTION_);
		*fsr = setBit32((*fsr), _NVC_, 1);
	}
	else
		f_trap = setSlice8(f_trap, 5, 1, 0); //texc

	// No deferring
	f_trap = setBit8(f_trap, 0, 1); //c

	if (op == _FSQRTs_) *result_l1 = res_32 ;
	if (op == _FSQRTd_) *result_l1 = getSlice64(res_64, 31, 0) ;
	if (op == _FSQRTd_) *result_l2 = getSlice64(res_64, 63, 32) ;

	*flags = f; 		
	*ft = f_trap;		

	return tv;
}

uint32_t executeFloatAddSub( Opcode op, uint32_t operand2_3, uint32_t operand2_2, uint32_t operand2_1, uint32_t operand2_0,
		uint32_t operand1_3, uint32_t operand1_2, uint32_t operand1_1, uint32_t operand1_0, uint32_t *result_h2, uint32_t *result_h1,
		uint32_t *result_l2, uint32_t *result_l1, uint32_t trap_vector, uint8_t *flags, uint8_t *ft, uint32_t *fsr)
{
	uint32_t tv = trap_vector;
	uint8_t f_trap = *ft;
	uint8_t f = *flags;

	float oprnd1_32 = _BITCAST_(float,operand1_0);
	uint64_t oprnd1_64_tmp = operand1_0;
	oprnd1_64_tmp = setSlice64(oprnd1_64_tmp, 63, 32, operand1_1);
	double oprnd1_64 = _BITCAST_(double,oprnd1_64_tmp);

	float oprnd2_32 = _BITCAST_(float,operand2_0);
	uint64_t oprnd2_64_tmp = operand2_0;
	oprnd2_64_tmp = setSlice64(oprnd2_64_tmp, 63, 32, operand2_1);
	double oprnd2_64 = _BITCAST_(double,oprnd2_64_tmp);

	if ((op == _FADDs_) || (op == _FSUBs_)) f = setBit8(f, _SINGLE_RESULT_, 1) ;
	else if ((op == _FADDd_) || (op == _FSUBd_)) f = setBit8(f, _DOUBLE_RESULT_, 1) ;
	else if ((op == _FADDq_) || (op == _FSUBq_)) f = setBit8(f, _QUAD_RESULT_, 1) ;

	float res_32_tmp = 0;
	double res_64_tmp = 0;

	if (op == _FADDs_) res_32_tmp = fpadd32(oprnd1_32, oprnd2_32) ;
	else if (op == _FSUBs_) res_32_tmp = fpsub32(oprnd1_32, oprnd2_32) ;
	else if (op == _FADDd_) res_64_tmp = fpadd64(oprnd1_64, oprnd2_64) ;
	else if (op == _FSUBd_) res_64_tmp = fpsub64(oprnd1_64, oprnd2_64) ;

	uint32_t res_32 = _BITCAST_(uint32_t,res_32_tmp);
	uint64_t res_64 = _BITCAST_(uint64_t,res_64_tmp);
	

	// IEEE-754 Exception
	if (isFpInvalidOp(op, oprnd1_32, oprnd2_32,oprnd1_64,oprnd2_64))
	{
		if(isNvmSet(*fsr))
		{
			tv = setBit32(tv, _TRAP_, 1) ;
			tv = setBit32(tv, _FP_EXCEPTION_, 1) ;
		}

		f_trap = setSlice8(f_trap, 5, 1, 0x10); // NVC bit set.. texc
		*fsr = setSlice32((*fsr), 16, 14, _IEEE_754_EXCEPTION_);
		*fsr = setBit32((*fsr), _NVC_, 1);
	}
	else	
		f_trap = setSlice8(f_trap, 5, 1, 0); //texc

	// No deferring.
	f_trap = setBit8(f_trap, 0, 1); //c

	 if((op == _FADDs_) || (op == _FSUBs_)) *result_l1 = res_32 ;
	 if((op == _FADDd_) || (op == _FSUBd_)) *result_l1 = getSlice64(res_64, 31, 0) ;
	 if((op == _FADDd_) || (op == _FSUBd_)) *result_l2 = getSlice64(res_64, 63, 32) ;

	*flags = f ;
	*ft =  f_trap;

	return tv;
}

uint32_t executeFloatMulDiv( Opcode op, uint32_t operand2_3, uint32_t operand2_2, uint32_t operand2_1, uint32_t operand2_0,
		uint32_t operand1_3, uint32_t operand1_2, uint32_t operand1_1, uint32_t operand1_0, uint32_t *result_h2, uint32_t *result_h1,
		uint32_t *result_l2, uint32_t *result_l1, uint32_t trap_vector, uint8_t *flags, uint8_t *ft, uint32_t *fsr)
{
	uint32_t tv = trap_vector;
	uint8_t f_trap = *ft;
	uint8_t f = *flags;

	float oprnd1_32 = _BITCAST_(float,operand1_0);
	uint64_t oprnd1_64_tmp = operand1_0;
	oprnd1_64_tmp = setSlice64(oprnd1_64_tmp, 63, 32, operand1_1);
	double oprnd1_64 = _BITCAST_(double,oprnd1_64_tmp);

	float oprnd2_32 = _BITCAST_(float,operand2_0);
	uint64_t oprnd2_64_tmp = operand2_0;
	oprnd2_64_tmp = setSlice64(oprnd2_64_tmp, 63, 32, operand2_1);
	double oprnd2_64 = _BITCAST_(double,oprnd2_64_tmp);

	if ((op == _FMULs_) || (op == _FDIVs_)) f = setBit8(f, _SINGLE_RESULT_, 1) ;
	else if ((op == _FMULd_) || (op == _FDIVd_ )|| (op == _FsMULd_)) f = setBit8(f, _DOUBLE_RESULT_, 1) ;
	else if ((op == _FMULq_) || (op == _FDIVq_)) f = setBit8(f, _QUAD_RESULT_, 1) ;

	float res_32_tmp = 0;
	double res_64_tmp = 0;

	if 	(op == _FMULs_) res_32_tmp = fpmul32(oprnd1_32, oprnd2_32) ;
	else if (op == _FDIVs_) res_32_tmp = doubleDiv(oprnd1_32, oprnd2_32) ;
	else if (op == _FMULd_)  res_64_tmp = fpmul64(oprnd1_64, oprnd2_64) ;
	else if (op == _FsMULd_) res_64_tmp = fpmul64((double)oprnd1_32, (double)oprnd2_32) ;
	else if (op == _FDIVd_) res_64_tmp = doubleDiv(oprnd1_64, oprnd2_64) ;


	// IEEE-754 Exception
	if (isFpInvalidOp(op, oprnd1_32, oprnd2_32,oprnd1_64,oprnd2_64))
	{
		if(isNvmSet(*fsr))
		{
			tv = setBit32(tv, _TRAP_, 1) ;
			tv = setBit32(tv, _FP_EXCEPTION_, 1) ;
		}

		f_trap = setSlice8(f_trap, 5, 1, 0x10); // NVC bit set.. texc
		*fsr = setSlice32((*fsr), 16, 14, _IEEE_754_EXCEPTION_);
		*fsr = setBit32((*fsr), _NVC_, 1);
	}
	else
		f_trap = setSlice8(f_trap, 5, 1, 0); //texc
	

	// No deferring.
	f_trap = setBit8(f_trap, 0, 1); //c

	uint32_t res_32 = _BITCAST_(uint32_t,res_32_tmp);
	uint64_t res_64 = _BITCAST_(uint64_t,res_64_tmp);

	if ((op == _FMULs_) || (op == _FDIVs_)) *result_l1 = res_32 ;
	if ((op == _FMULd_) || (op == _FDIVd_) || (op == _FsMULd_)) 
	{
		*result_l1 = getSlice64(res_64, 31, 0) ;
		*result_l2 = getSlice64(res_64, 63, 32) ;
	}

	*flags = f ;
	*ft = f_trap;

	return tv;
}

/***************************************************************/

uint32_t executeFloatCompare( Opcode op, uint32_t operand2_3, uint32_t operand2_2, uint32_t operand2_1, uint32_t operand2_0,
	uint32_t operand1_3, uint32_t operand1_2, uint32_t operand1_1, uint32_t operand1_0, uint32_t trap_vector, uint8_t *ft, uint32_t *fsr)
{
	uint32_t tv = trap_vector;
	uint8_t f_trap = *ft;

	float oprnd1_32 = _BITCAST_(float,operand1_0);
	uint64_t oprnd1_64_tmp = operand1_0;
	oprnd1_64_tmp = setSlice64(oprnd1_64_tmp, 63, 32, operand1_1);
	double oprnd1_64 = _BITCAST_(double,oprnd1_64_tmp);

	float oprnd2_32 = _BITCAST_(float,operand2_0);
	uint64_t oprnd2_64_tmp = operand2_0;
	oprnd2_64_tmp = setSlice64(oprnd2_64_tmp, 63, 32, operand2_1);
	double oprnd2_64 = _BITCAST_(double,oprnd2_64_tmp);

	uint8_t fcc = 0;
	
	
	//Not distinguished FCMP and FCMPE. ****TODO 
	//fcc=3 if either of the operands is a signalling NaN or a quiet NaN.
	//Unordered compare - added by Neha Karanjkar (2 Sept 2015) :
	if ((op == _FCMPs_) || (op == _FCMPEs_))
	{
		if(isNaN32(oprnd1_32) 
		|| isNaN32(oprnd2_32))
			fcc = 3;
		else if (oprnd1_32 == oprnd2_32) fcc = 0 ;
		else if (oprnd1_32 <  oprnd2_32) fcc = 1 ;
		else if (oprnd1_32 >  oprnd2_32) fcc = 2 ;
	}
	else if ((op == _FCMPd_) || (op == _FCMPEd_))
	{
		if( isNaN64(oprnd1_64) 
		||  isNaN64(oprnd2_64))
			fcc =3;
		else if (oprnd1_64 == oprnd2_64) fcc = 0 ;
		else if (oprnd1_64 <  oprnd2_64) fcc = 1 ;
		else if (oprnd1_64 >  oprnd2_64) fcc = 2 ;
	}

	// IEEE-754 Exception
	uint8_t is_invalid_op = isFpInvalidOp(op, oprnd1_32, oprnd2_32, oprnd1_64, oprnd2_64);
	uint8_t has_trapped = 0;
	if (is_invalid_op)
	{
		if(isNvmSet(*fsr))
		{
			tv = setBit32(tv, _TRAP_, 1) ;
			tv = setBit32(tv, _FP_EXCEPTION_, 1) ;
			has_trapped = 1;
		}

		f_trap = setSlice8(f_trap, 5, 1, 0x10); // NVC bit set.. texc
		*fsr = setSlice32((*fsr), 16, 14, _IEEE_754_EXCEPTION_);
		*fsr = setBit32((*fsr), _NVC_, 1);
	}
	else
		f_trap = setSlice8(f_trap, 5, 1, 0); //texc




	// no deferring.
	f_trap = setBit8(f_trap, 0, 1); //c

	// fcc not changed if there is a trap!
	if(!has_trapped)
		f_trap = setSlice8(f_trap, 7, 6, fcc); //tfcc

	*ft =  f_trap;

	return tv;
}

uint32_t executeFPInstruction( ThreadState* s, Opcode opcode,
				uint32_t operand2_3, uint32_t operand2_2, 
					uint32_t operand2_1, uint32_t operand2_0,
				uint32_t operand1_3, uint32_t operand1_2, 
					uint32_t operand1_1, uint32_t operand1_0, 
				uint32_t *result_h2, uint32_t *result_h1,
				uint32_t *result_l2, uint32_t *result_l1, 
					uint32_t trap_vector, uint8_t *flags, 
					uint8_t *ft, StatusRegisters *ptr)
{
	uint8_t is_itof = ((opcode >= _FiTOs_) && (opcode <= _FiTOq_));
	uint8_t is_ftoi = ((opcode >= _FsTOi_) && (opcode <= _FqTOi_));
	uint8_t is_ftof = ((opcode >= _FsTOd_) && (opcode <= _FqTOd_));
	uint8_t is_fmov = ((opcode >= _FMOVs_) && (opcode <= _FABSs_));

	uint8_t is_fsqrt = ((opcode >= _FSQRTs_) && (opcode <= _FSQRTq_));
	if(is_fsqrt && (opcode == _FSQRTs_))
		s->num_fp_sp_sqroots_executed++;
	if(is_fsqrt && (opcode == _FSQRTd_))
		s->num_fp_dp_sqroots_executed++;

	uint8_t is_faddsub = ((opcode >= _FADDs_) && (opcode <= _FSUBq_));

	uint8_t is_fmuldiv = ((opcode >= _FMULs_) && (opcode <= _FDIVq_));
	if(opcode == _FDIVs_)
		s->num_fp_sp_divs_executed++;
	if(opcode == _FDIVd_)
		s->num_fp_dp_divs_executed++;
		
	uint8_t is_fcmp = ((opcode >= _FCMPs_) && (opcode <= _FCMPEq_));

	uint8_t is_vf = ((opcode >= _VFADD32_) && (opcode <= _VFHTOI16_));
	uint8_t is_f_half_reduce = (opcode == _FADDREDUCE16_);
	uint8_t is_f_half_convert = ((opcode == _FSTOH_) || (opcode == _FHTOS_));

	uint32_t tv=0;
	if(is_itof) 	 	tv = executeIntegerToFloat( opcode, operand2_0, result_h2, result_h1, result_l2, result_l1, trap_vector, flags, ft, &(ptr->fsr));
	else if(is_ftoi) 	tv = executeFloatToInteger(opcode, operand2_3, operand2_2, operand2_1, operand2_0, result_l1, trap_vector, flags, ft, &(ptr->fsr));
	else if(is_ftof) 	tv = executeFloatToFloat( opcode, operand2_3, operand2_2, operand2_1, operand2_0,	result_h2, result_h1, result_l2, result_l1, trap_vector, flags, ft, &(ptr->fsr));
	else if(is_fmov) 	tv = executeFloatMove( opcode, operand2_0, result_l1, trap_vector, flags, ft);
	else if(is_fsqrt)	tv = executeFloatSqrt( opcode, operand2_3, operand2_2, operand2_1, operand2_0, operand1_3, operand1_2, operand1_1, operand1_0, result_h2, result_h1, result_l2, result_l1, trap_vector, flags, ft, &(ptr->fsr));
	else if(is_faddsub)	tv = executeFloatAddSub( opcode, operand2_3, operand2_2, operand2_1, operand2_0, operand1_3, operand1_2, operand1_1, operand1_0, result_h2, result_h1, result_l2, result_l1, trap_vector, flags, ft, &(ptr->fsr));
	else if(is_fmuldiv)	tv = executeFloatMulDiv( opcode, operand2_3, operand2_2, operand2_1, operand2_0, operand1_3, operand1_2, operand1_1, operand1_0, result_h2, result_h1, result_l2, result_l1, trap_vector, flags, ft, &(ptr->fsr));
	else if(is_fcmp)	tv = executeFloatCompare( opcode, operand2_3, operand2_2, operand2_1, operand2_0, operand1_3, operand1_2,	operand1_1, operand1_0, trap_vector, ft, &(ptr->fsr));
	else if(is_vf)
		execute64FloatVf (opcode, operand1_1, operand1_0, operand2_1, operand2_0,
					result_l2, result_l1, ft, flags);
	else if(is_f_half_reduce)
	{
		execute64FpHalfAddReduce(opcode, operand2_1, operand2_0, result_l1,ft,flags);
	}
	else if(is_f_half_convert)
	{
		execute64FpHalfConvert(opcode, operand2_0, result_l1,ft,flags);
	}
	return tv;
}
