#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "half_precision_float.h"
#include "fpunit_exec_exec_aa_c_model.h"

int   __initialized_flag__ = 0;

#define __init_if_needed__   {if(!__initialized_flag__)\
			        { __initialized_flag__ = 1; fpunit_exec_exec___init_aa_globals__();}}


// pos/neg infinity maps to pos/neg infinity.
// pos/neg zero maps to pos/neg zero
// denorm maps to denorm by using sticky
// normalized maps to 
//    normalized if exponent in range.
//    pos-inf if exponent too large.
//    denorm  if exponent small, but not too small.
//    neg-inf if exponent too too small. 
half floatToHalf(float f)
{
	__init_if_needed__;

	uint32_t uf = *((uint32_t*) &f);
	half R;

	fpunit_exec_exec_exec_fstoh(uf, &R);
	return(R);
}

float    halfToFloat(half x)
{
	__init_if_needed__;

	float R;
	uint32_t* puR = (uint32_t*) &R;
	fpunit_exec_exec_exec_fhtos(x,puR);
	return(R);	
}

half intToHalf(int x)
{
	__init_if_needed__;

	int16_t u = x;
	uint16_t uu = *((uint16_t*) &u);
	half R;
	fpunit_exec_exec_exec_fi16toh(uu, &R);
	return(R);
}

int  halfToInt(half x)
{
	__init_if_needed__;

	int16_t r16;
	fpunit_exec_exec_exec_fhtoi16(x, &r16);

	return(r16);
}


half  addHalf(half x, half y)
{
	__init_if_needed__;
	half R;
	fpunit_exec_exec_fadd16_wrap(x,y,&R);
	return(R);
}

half subHalf(half x, half y)
{
	__init_if_needed__;
	half R;
	fpunit_exec_exec_fsub16_wrap(x,y,&R);
	return(R);
}

half mulHalf(half x, half y)
{
	__init_if_needed__;
	half R;
	fpunit_exec_exec_fmul16_wrap(x,y,&R);
	return(R);
}

#define HADDOP 0
#define HSUBOP 1
#define HMULOP 2

uint64_t vectorHalfPrecisionOpInU64Form(uint64_t x, uint64_t y, uint8_t op)
{
	__init_if_needed__;
	int I;
	uint64_t result = 0;
	for(I = 0; I < 4; I++)
	{
		half op1 = (x >> (16*I)) & 0xffff;
		half op2 = (y >> (16*I)) & 0xffff;

		half hz;

		if(op == HADDOP)
			hz = addHalf(op1, op2);
		else if(op == HSUBOP)
			hz = subHalf(op1, op2);
		else if(op == HMULOP)
			hz = mulHalf(op1, op2);

		result = (result | (((uint64_t) hz) << (16*I)));
	}
	return(result);
}

uint64_t vectorHalfPrecisionAddInU64Form(uint64_t x, uint64_t y)
{
	__init_if_needed__;
	return(vectorHalfPrecisionOpInU64Form(x,y,HADDOP));
}

uint64_t vectorHalfPrecisionSubInU64Form(uint64_t x, uint64_t y)
{
	__init_if_needed__;
	return(vectorHalfPrecisionOpInU64Form(x,y,HSUBOP));
}
uint64_t vectorHalfPrecisionMulInU64Form(uint64_t x, uint64_t y)
{
	__init_if_needed__;
	return(vectorHalfPrecisionOpInU64Form(x,y,HMULOP));
}

#define TOHALF 3
#define TOI16  4

uint64_t halfPrecisionConvertBase(uint64_t cvt_op, uint8_t cvt_type)
{
	int I;
	uint64_t result = 0;
	for(I = 0; I < 4; I++)
	{
		int16_t op = (int16_t) ((cvt_op >> (16*I)) & 0xffff);
		uint64_t lr = 0;

		half hz;

		if(cvt_type == TOHALF)
		{
			half hz  = intToHalf(op);
			lr = hz & 0xffff;
		}
		else
		{
			lr = halfToInt(op) & 0xffff;
		}

		result = (result |  (lr << (16*I)));
	}
	return(result);
}

uint64_t halfPrecisionToI16VectorConvert(uint64_t cvt_op)
{
	__init_if_needed__;
	return(halfPrecisionConvertBase(cvt_op,  TOI16));
}

uint64_t i16ToHalfPrecisionVectorConvert(uint64_t cvt_op)
{
	__init_if_needed__;
	return(halfPrecisionConvertBase(cvt_op, TOHALF));
}

uint32_t vectorHalfAddReduce(uint64_t cvt_op)
{
	__init_if_needed__;
	int I;

	half hresult = 0;
	for(I = 0; I < 4; I++)
	{
		half hx = (cvt_op >> (16*I)) & 0xffff;
		uint64_t lr = 0;

		hresult = addHalf(hx, hresult);
	}
	return((uint32_t) hresult);
}

uint32_t halfToFloatInU32Form(half operand)
{
	__init_if_needed__;
	float fx = halfToFloat(operand);
	uint32_t ret_val = *((uint32_t*) &fx);
	return(ret_val);
}

half floatToHalfInU32Form(uint32_t operand)
{
	__init_if_needed__;

	float f = *((float*) &operand);
	half x = floatToHalf(f);

	return(x);
}

