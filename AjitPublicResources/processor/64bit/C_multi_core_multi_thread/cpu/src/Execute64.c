#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <assert.h>

#include "Ajit_Hardware_Configuration.h"
#include "Opcodes.h"
#include "AjitThread.h"
#include "Flags.h"
#include "Traps.h"
#include "Ancillary.h"
#include "Execute.h"
#include "ThreadInterface.h"
#include "ImplementationDependent.h"
#include "RegisterFile.h"
#include "fpu.h"
#include "ASI_values.h"
#include "ThreadHWserverInterface.h"
#include "Pipes.h"
#include "FpExceptions.h"
#include "half_precision_float.h"

uint64_t splice_words (uint32_t w0, uint32_t w1)
{
	uint64_t w0_64 = w0;
	uint64_t w1_64 = w1;
	uint64_t ret_val = (w0_64 << 32) | w1_64;
	return(ret_val);
}

void split_words (uint64_t w64, uint32_t* w0, uint32_t* w1)
{
	*w1 = (w64 & 0xffffffff);
	w64 = (w64 >> 32);
	*w0 = (w64 & 0xffffffff);
}



void execute64BitLogical( Opcode op, uint32_t operand1_0, uint32_t operand1_1, 
				uint32_t operand2_0, uint32_t operand2_1,
				uint32_t *result_h, uint32_t* result_l,  
				StatusRegisters *status_reg, StateUpdateFlags*  reg_update_flags,
				uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : 64-bit LOGICAL  op-code=0x%x operand1=0x%x,0x%x operand2=0x%x,0x%x\n", op, 
			operand1_0, 
			operand1_1, 
			operand2_0, 
			operand2_1);
#endif 
	uint64_t res = 0;
	uint64_t operand1 = splice_words (operand1_0, operand1_1);
	uint64_t operand2 = splice_words (operand2_0, operand2_1);

	uint8_t f = *flags;

	 if ((op == _ANDD_) || (op == _ANDDcc_)) 		res = (operand1 & operand2) 	;
	 else if ((op == _ANDDN_) || (op == _ANDDNcc_)) 	res = (operand1 & ~operand2)	;
	 else if ((op == _ORD_) || (op == _ORDcc_)) 	res = (operand1 | operand2) 	;
	 else if ((op == _ORDN_) || (op == _ORDNcc_)) 	res = (operand1 | ~operand2)	;
	 else if ((op == _XORD_) || (op == _XORDcc_)) 	res = (operand1 ^ operand2) 	;
	 else if ((op == _XNORD_) || (op == _XNORDcc_)) 	res = (operand1 ^ ~operand2)	;
	 else assert(0);

	uint8_t modify_icc =  ((op == _ANDDcc_) || (op == _ANDDNcc_) 
					|| (op == _ORDcc_) || (op == _ORDNcc_) || (op == _XORDcc_) 
					|| (op == _XNORDcc_));

	 
	 if(modify_icc)
	 {
		 status_reg->psr = 
			setBit32(status_reg->psr, 23, getBit64(res, 63)) ; //N flag
		 status_reg->psr = 
			setBit32(status_reg->psr, 21, 0) ; //V flag
		 status_reg->psr = 
			setBit32(status_reg->psr, 20, 0) ; //C flag

		 uint8_t z_flag = (res == 0);
		 status_reg->psr = 
				setBit32(status_reg->psr, 22, z_flag) ; //Z flag
		 reg_update_flags->psr_updated=1;
	 }
	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	f = setBit8(f, _DOUBLE_RESULT_, 1);
	*flags = f;

	split_words(res,result_h, result_l);
}

void execute64BitShift(Opcode op, uint32_t operand1_0, uint32_t operand1_1, 
				uint32_t operand2,
				uint32_t *result_h, uint32_t* result_l, 
				StatusRegisters *status_reg, StateUpdateFlags*  reg_update_flags,
				uint8_t *flags)
{
#ifdef DEBUG
	// TBD: shift rs2 need not be 64-bit.
	fprintf(stderr,"\tInfo : 64-bit SHIFT  op-code=0x%x operand1=0x%x,0x%x operand2=0x%x\n",  
			op, operand1_0, operand1_1, operand2);
#endif 
	 uint64_t res = 0;
	 uint64_t shift_amount  = operand2;
	 uint64_t operand1 = splice_words (operand1_0, operand1_1);

	 if (op == _SLLD_) 	
		 res = (operand1 << shift_amount) ;
	 else if (op == _SRLD_) 
		 res = (operand1 >> shift_amount) ;
	 else if (op == _SRAD_) 
		 res = (((int64_t)operand1) >> shift_amount) ;

	 uint8_t f = *flags;
	 f = setBit8(f, _NEED_WRITE_BACK_, 1);
	 f = setBit8(f, _DOUBLE_RESULT_, 1);
	 *flags = f;

	 split_words (res, result_h, result_l);
}

void execute64BitAdd  (Opcode op, uint32_t operand1_0, uint32_t operand1_1, 
				uint32_t operand2_0, uint32_t operand2_1,
				uint32_t *result_h, uint32_t* result_l, 
				StatusRegisters *status_reg,
				StateUpdateFlags *reg_update_flags,
				uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : ADDD  op-code=0x%x operand1=0x%x,0x%x operand2=0x%x,0x%x\n", 
				op, operand1_0, operand1_1, operand2_0, operand2_1);
#endif 
	uint64_t res = 0;
	uint8_t f = *flags;

	uint64_t operand1 = splice_words (operand1_0,operand1_1);
	uint64_t operand2 = splice_words (operand2_0,operand2_1);

	if ((op == _ADDD_) || (op == _ADDDcc_))   
		res=  (operand1 + operand2) ;

	uint8_t modify_icc =  
		(op == _ADDDcc_);

	uint8_t operand1_sign = getBit64(operand1, 63);
	uint8_t operand2_sign = getBit64(operand2, 63);
	uint8_t n = getBit64(res, 63);
	uint8_t z = (res == 0);
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
	f = setBit8(f, _DOUBLE_RESULT_, 1);
	*flags = f;

	split_words (res, result_h, result_l);
}

void execute64BitSub  (Opcode op, uint32_t operand1_0, uint32_t operand1_1, 
				uint32_t operand2_0, uint32_t operand2_1,
				uint32_t *result_h, uint32_t* result_l, 
				StatusRegisters *status_reg,
				StateUpdateFlags *reg_update_flags,
				uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : SUBD  op-code=0x%x operand1=0x%x,0x%x operand2=0x%x,0x%x\n", 
				op, operand1_0, operand1_1, operand2_0, operand2_1);
#endif 
	uint64_t res = 0;
	uint8_t f = *flags;

	uint64_t operand1 = splice_words (operand1_0,operand1_1);
	uint64_t operand2 = splice_words (operand2_0,operand2_1);

	if ((op == _SUBD_) || (op == _SUBDcc_))   
		res=  (operand1 - operand2) ;

	uint8_t modify_icc =  
		(op == _SUBDcc_);

	uint8_t operand1_sign = getBit64(operand1, 63);
	uint8_t operand2_sign = getBit64(operand2, 63);
	uint8_t n = getBit64(res, 63);
	uint8_t z = (res == 0);
	uint8_t v = ((operand1_sign && (!operand2_sign) & (!n)) || ((!operand1_sign) && operand2_sign && n));
	uint8_t c = ((!operand1_sign) && operand2_sign) || (n && ((!operand1_sign) || operand2_sign));

	if(modify_icc)
	{
	status_reg->psr =  setBit32(status_reg->psr, 23, n) ; //N flag
	status_reg->psr =  setBit32(status_reg->psr, 22, z) ; //Z flag
	status_reg->psr =  setBit32(status_reg->psr, 21, v) ; //V flag
	status_reg->psr =  setBit32(status_reg->psr, 20, c) ; //C flag
	
	reg_update_flags->psr_updated=1;
	}
	
	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	f = setBit8(f, _DOUBLE_RESULT_, 1);
	*flags = f;

	split_words (res, result_h, result_l);
}

void execute64BitMul  (Opcode op, uint32_t operand1_0, 
				uint32_t operand1_1, uint32_t operand2_0, uint32_t operand2_1,
				uint32_t *result_h, uint32_t* result_l, 
				StatusRegisters *status_reg,
				StateUpdateFlags *reg_update_flags,
				uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : *MULD*  op-code=0x%x operand1=0x%x,0x%x operand2=0x%x,0x%x\n", 
				op, operand1_0, operand1_1, operand2_0, operand2_1);
#endif 
	uint64_t res = 0;
	uint8_t f = *flags;

	uint64_t operand1 = splice_words (operand1_0,operand1_1);
	uint64_t operand2 = splice_words (operand2_0,operand2_1);

	if ((op == _UMULD_) || (op == _UMULDcc_))   
		res=  (operand1 * operand2) ;
	else if ((op == _SMULD_) || (op == _SMULDcc_))   
		res =  (uint64_t) (((int64_t) operand1) * ((int64_t) operand2));

	uint8_t modify_icc =  (op == _UMULDcc_) ||  (op == _SMULDcc_);

	uint8_t n = getBit64(res, 63);
	uint8_t z = (res == 0);
	uint8_t v = 0;
	uint8_t c = 0;

	if(modify_icc)
	{
	status_reg->psr =  setBit32(status_reg->psr, 23, n) ; //N flag
	status_reg->psr =  setBit32(status_reg->psr, 22, z) ; //Z flag
	status_reg->psr =  setBit32(status_reg->psr, 21, v) ; //V flag
	status_reg->psr =  setBit32(status_reg->psr, 20, c) ; //C flag
	
	reg_update_flags->psr_updated=1;
	}
	
	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	f = setBit8(f, _DOUBLE_RESULT_, 1);
	*flags = f;

	split_words (res, result_h, result_l);
}

uint32_t execute64BitDiv   (Opcode op, uint32_t operand1_0, uint32_t operand1_1, 
		uint32_t operand2_0, uint32_t operand2_1, uint32_t *result_h,  uint32_t *result_l,
		StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags,
		uint32_t trap_vector, uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : *DIVD*  op-code=0x%x operand1=0x%x,0x%x operand2=0x%x,0x%x\n", 
				op, operand1_0, operand1_1, operand2_0, operand2_1);
#endif 
	uint64_t res = 0;
	uint8_t exception = 0;
	uint8_t f = *flags;

	uint64_t operand1 = splice_words (operand1_0,operand1_1);
	uint64_t operand2 = splice_words (operand2_0,operand2_1);

	uint32_t tv = trap_vector;
	if(operand2 == 0)
	{
		tv = setBit32(tv, _TRAP_, 1);
		tv = setBit32(tv, _DIVISION_BY_ZERO_, 1) ;
		exception = 1;
	}

	uint8_t udiv = (op == _UDIVD_) || (op == _UDIVDcc_);
	uint8_t sdiv = (op == _SDIVD_) || (op == _SDIVDcc_);
	if(udiv && !exception)
	{
		res = operand1/operand2;
	}
	else if(sdiv && !exception)
	{
		res = (uint64_t) (((int64_t) operand1)/((int64_t)operand2));
	}

	uint8_t n = getBit64(res, 63);
	uint8_t z = (res == 0);

	uint8_t modify_icc =  !exception && ((op == _UDIVDcc_) || (op == _SDIVDcc_));
	if(modify_icc)
	{
		status_reg->psr = setBit32(status_reg->psr, 23, n) ; //N flag
		status_reg->psr = setBit32(status_reg->psr, 22, z) ; //Z flag
		status_reg->psr = setBit32(status_reg->psr, 21, 0) ; //V flag
		status_reg->psr = setBit32(status_reg->psr, 20, 0) ; //C flag
		reg_update_flags->psr_updated=1;
	}


	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	f = setBit8(f, _DOUBLE_RESULT_, 1);
	*flags = f;

	split_words (res, result_h, result_l);
	return tv;
}

void execute64BitReduce8  (Opcode op, uint32_t operand1_0, uint32_t operand1_1, 
					uint32_t operand2, 
					uint32_t* result_l, 
					StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags,
					uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : *ByteReduce*  op-code=0x%x operand1=0x%x,0x%x operand2=0x%x\n", 
				op, operand1_0, operand1_1, operand2);
#endif 
	uint64_t operand1 = splice_words (operand1_0,operand1_1);
	uint8_t  mask     = operand2 & 0xff;
	uint8_t f = *flags;
	
	*result_l = ((op == _ANDDREDUCE8_) ? 0xff : 0x0);
	int I;
	for (I = 0; I < 8; I++)
	{
		if (mask & (1 << I)) 
		{
			uint8_t cbyte = (operand1  >> (I*8)) & 0xff;
			switch (op)
			{
				case _ADDDREDUCE8_:
					*result_l += cbyte;
					break;
				case _ORDREDUCE8_:
					*result_l |= cbyte;
					break;
				case _ANDDREDUCE8_:
					*result_l &= cbyte;
					break;
				case _XORDREDUCE8_:
					*result_l ^= cbyte;
					break;
				default:
					break;
			} 
		}
	}
	
	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	f = setBit8(f, _SINGLE_RESULT_, 1);
	*flags = f;
}

void execute64BitReduce16  (Opcode op, uint32_t operand1_0, uint32_t operand1_1, 
					uint32_t operand2, 
					uint32_t* result_l, 
					StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags,
					uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : *ByteReduce*  op-code=0x%x operand1=0x%x,0x%x operand2=0x%x\n", 
				op, operand1_0, operand1_1, operand2);
#endif 
	uint64_t operand1 = splice_words (operand1_0,operand1_1);
	uint8_t  mask     = operand2 & 0xf;
	uint8_t f = *flags;
	
	*result_l = ((op == _ANDDREDUCE16_) ? 0xffff : 0x0);
	int I;
	for (I = 0; I < 4; I++)
	{
		if (mask & (1 << I)) 
		{
			uint16_t ch = (operand1  >> (I*16)) & 0xffff;
			switch (op)
			{
				case _ADDDREDUCE16_:
					*result_l += ch;
					break;
				case _ORDREDUCE16_:
					*result_l |= ch;
					break;
				case _ANDDREDUCE16_:
					*result_l &= ch;
					break;
				case _XORDREDUCE16_:
					*result_l ^= ch;
					break;
				default:
					break;
			} 
		}
	}
	
	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	f = setBit8(f, _SINGLE_RESULT_, 1);
	*flags = f;
}

void execute64BitZBytePos  (Opcode op, uint32_t operand1_0, uint32_t operand1_1, 
					uint32_t operand2, 
					uint32_t *result_l,
					StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags,
					uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : ZBytePos  op-code=0x%x operand1=0x%x,0x%x operand2=0x%x\n", 
				op, operand1_0, operand1_1, operand2);
#endif 
	uint64_t operand1 = splice_words (operand1_0,operand1_1);
	uint8_t  mask     = operand2 & 0xff;
	uint8_t f = *flags;
	
	*result_l = 0;
	uint32_t I;
	for (I = 0; I < 8; I++)
	{
		if (mask & (1 << I)) 
		{
			uint8_t cbyte = (operand1  >> (I*8)) & 0xff;
			if(cbyte == 0)
				*result_l |= (1 << I);
		}
	}
	
	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	f = setBit8(f, _SINGLE_RESULT_, 1);
	*flags = f;
}

void execute64BitVectorOp  (Opcode op, 
				uint8_t  data_type,
				uint32_t operand1_0, uint32_t operand1_1, 
				uint32_t operand2_0, uint32_t operand2_1,
				uint32_t *result_h, uint32_t* result_l, 
				StatusRegisters *status_reg, StateUpdateFlags* reg_update_flags,
				uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : IntVectorOp  op-code=0x%x data_type=0x%x operand1=0x%x,0x%x operand2=0x%x,0x%x\n", 
				op, operand1_0, operand1_1, operand2_0, operand2_1);
#endif 
	uint64_t res = 0;

	uint8_t f = *flags;
	uint64_t operand1 = splice_words (operand1_0,operand1_1);
	uint64_t operand2 = splice_words (operand2_0,operand2_1);

	int I;
	switch (data_type) 
	{
		case 1:
			for (I = 0; I < 8; I++)
			{
				uint8_t x = (operand1 >> (7-I)*8);
				uint8_t y = (operand2 >> (7-I)*8);
				uint64_t res8 = 0;
				switch (op)
				{
					case _VADDD8_:
						res8 = x + y;
						break;
					case _VSUBD8_:
						res8 = x - y;
						break;
					case _VUMULD8_:
						res8 = x * y;
						break;
					case _VSMULD8_:
						res8 = (uint8_t) ((int8_t) x) * ((int8_t) y);
						break;
					default:
						break;
				}
				res = res | ((res8 & 0xff) << (7-I)*8);
			}		
			break;
		case 2:
			for (I = 0; I < 4; I++)
			{
				uint16_t x = (operand1 >> (3-I)*16);
				uint16_t y = (operand2 >> (3-I)*16);
				uint64_t res16 = 0;
				switch (op)
				{
					case _VADDD16_:
						res16 = x + y;
						break;
					case _VSUBD16_:
						res16 = x - y;
						break;
					case _VUMULD16_:
						res16 = x * y;
						break;
					case _VSMULD16_:
						res16 = (uint16_t) ((int16_t) x) * ((int16_t) y);
						break;
					default:
						break;
				}
				res = res | ((res16 & 0xffff) << (3-I)*16);
			}		
			break;
		case 4:
			for (I = 0; I < 2; I++)
			{
				uint32_t x = (operand1 >> (1-I)*32);
				uint32_t y = (operand2 >> (1-I)*32);
				uint64_t res32 = 0;
				switch (op)
				{
					case _VADDD32_:
						res32 = x + y;
						break;
					case _VSUBD32_:
						res32 = x - y;
						break;
					case _VUMULD32_:
						res32 = x * y;
						break;
					case _VSMULD32_:
						res32 = (uint32_t) ((int32_t) x) * ((int32_t) y);
						break;
					default:
						break;
				}
				res = res | ((res32 & 0xffffffff) << (1-I)*32);
			}		
			break;
		default :
			break;
	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	f = setBit8(f, _DOUBLE_RESULT_, 1);
	*flags = f;

	split_words (res, result_h, result_l);
}


void execute64FloatVf (Opcode op, uint32_t operand1_1, uint32_t operand1_0, 
				uint32_t operand2_1, uint32_t operand2_0,
				uint32_t *result_h,  uint32_t *result_l, 
				uint8_t* f_trap,
				uint8_t *flags)
{
#ifdef DEBUG
	fprintf(stderr,"\tInfo : FloatVectorOp  op-code=0x%x data_type=0x%x operand1=0x%x,0x%x operand2=0x%x,0x%x\n", 
				op, operand1_1, operand1_0, operand2_1, operand2_0);
#endif 
	uint8_t f = *flags;


	uint8_t arith_32 = (op == _VFADD32_) || (op == _VFSUB32_) || (op == _VFMUL32_);
	uint8_t arith_16 = (op == _VFADD16_) || (op == _VFSUB16_) || (op == _VFMUL16_);
	uint8_t cvt = (op == _VFHTOI16_) || (op == _VFI16TOH_);

	if(arith_32)
	{
		float X1 = _BITCAST_(float,operand1_1);
		float X0 = _BITCAST_(float,operand1_0);
		float Y1 = _BITCAST_(float,operand2_1);
		float Y0 = _BITCAST_(float,operand2_0);

		float R1 = 0;
		float R0 = 0;
		switch (op)
		{
			case _VFADD32_:
				R1 = X1 + Y1;
				R0 = X0 + Y0;
				break;
			case _VFSUB32_:
				R1 = X1 - Y1;
				R0 = X0 - Y0;
				break;
			case _VFMUL32_:
				R1 = X1 * Y1;
				R0 = X0 * Y0;
				break;
			default:
				break;
		}

		*result_h = _BITCAST_(uint32_t,R1);
		*result_l = _BITCAST_(uint32_t,R0);
	}
	else if(arith_16)
	{
		uint64_t a16_result = 0;
		uint64_t o1 = splice_words ( operand1_1, operand1_0);
		uint64_t o2 = splice_words ( operand2_1, operand2_0);
		switch(op)
		{
			case _VFADD16_:      
				a16_result = vectorHalfPrecisionAddInU64Form(o1,o2); 
				break;
			case _VFSUB16_:
				a16_result = vectorHalfPrecisionSubInU64Form(o1,o2); 
				break;
			case _VFMUL16_:
				a16_result = vectorHalfPrecisionMulInU64Form(o1,o2);
				break;
			default:
				break;
		}
		split_words(a16_result, result_h, result_l);
	}
	else if(cvt)
	{
		uint64_t cvt_op = splice_words ( operand2_1, operand2_0);
		uint64_t cvt_result = 0;
		switch(op) 
		{
			case _VFHTOI16_:
				cvt_result = halfPrecisionToI16VectorConvert(cvt_op);
				break;
			case _VFI16TOH_:
				cvt_result = i16ToHalfPrecisionVectorConvert(cvt_op);
				break;
			default:
				break;
		};
		split_words(cvt_result, result_h, result_l);
	}

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	f = setBit8(f, _DOUBLE_RESULT_, 1);

	*f_trap = setBit8(*f_trap, 0, 1); // set c = 1 to indicate completion.
	*flags = f;
}

// source is a 64-bit operand, result is in 32-bit register.
void execute64FpHalfAddReduce(Opcode op, uint32_t operand2_1, uint32_t operand2_0,
		uint32_t* result_l, uint8_t* ft, uint8_t* flags)
{
	assert(op == _FADDREDUCE16_);

	uint8_t f = *flags;
	uint64_t cvt_op = splice_words ( operand2_1, operand2_0);
	uint32_t cvt_result = vectorHalfAddReduce(cvt_op);

	*result_l = cvt_result;

	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	f = setBit8(f, _SINGLE_RESULT_, 1);
	*ft = setBit8(*ft, 0, 1); // set c = 1 to indicate completion.
	*flags = f;
}

// source and destination are 32-bit registers.
void execute64FpHalfConvert(Opcode op, uint32_t operand2_0,
		uint32_t* result_l, uint8_t* ft, uint8_t* flags)
{
	uint32_t cvt_result;
	uint8_t f = *flags;

	if(op == _FHTOS_)
	{
		cvt_result = halfToFloatInU32Form(operand2_0);
	}
	else
	{
		cvt_result  = floatToHalfInU32Form(operand2_0);
	}

	*result_l = cvt_result;
	f = setBit8(f, _NEED_WRITE_BACK_, 1);
	f = setBit8(f, _SINGLE_RESULT_, 1);
	*ft = setBit8(*ft, 0, 1); // set c = 1 to indicate completion.
	*flags = f;
}


