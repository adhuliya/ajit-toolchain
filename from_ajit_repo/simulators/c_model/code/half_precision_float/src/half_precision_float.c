#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "half_precision_float.h"

uint16_t exponentMask(half* x)
{
	return((1 << x->exponent_width)-1);
}

uint16_t exponentWidth(half* x)
{
	return(x->exponent_width);
}

uint16_t mantissaWidth(half* x)
{
	return(15 - x->exponent_width);
}

void initHalf(half* x, uint8_t exp, uint16_t val)
{
	x->exponent_width = exp;
	x->value = val;
}

half* makeHalf(uint8_t exp, uint16_t val)
{
	half* ret_val = (half*) malloc(sizeof(half));
	initHalf(ret_val, exp, val);
	return(ret_val);
}

uint16_t  __half_nan__(uint8_t expwidth, uint8_t sign) 
{
	uint16_t mantissa_width = 15 - expwidth;
	uint16_t ret_val = ((sign << 15) | (((1 << expwidth)-1) << mantissa_width) | 0x1);
	return(ret_val);
}
uint16_t  __half_inf__(uint8_t expwidth, uint8_t sign) 
{
	uint16_t mantissa_width = 15 - expwidth;
	uint16_t ret_val = ((sign << 15) | (((1 << expwidth)-1) << mantissa_width));
	return(ret_val);
}

uint32_t __float_nan__(uint8_t sign) 
{
  return((sign << 31) | (0xff << 23) | 0x1);
}

uint32_t  __float_inf__(uint8_t sign)  
{
	return((((uint32_t) sign) << 31) | (0xff << 23));
}
uint64_t  __double_nan__(uint8_t sign) {
	return((((uint64_t) sign) << 63) | (((uint64_t) 0x3ff) << 52) | 0x1);
}

uint64_t  __double_inf__(uint8_t sign)  
{
	return((((uint64_t) sign) << 63) | (((uint64_t) 0x3ff) << 52));
}


uint16_t __half_exponent_bias__(uint16_t exp_width)
{
   return ((1 << (exp_width-1)) - 1);
}

uint16_t  __float_exponent_bias__()
{ 
	return(127);
}

uint16_t  __double_exponent_bias__()
{ 
	return(1023);
}

int16_t __max_unbiased_half_exponent__(uint16_t exp_width)
{
  return ( ((1 << (exp_width)) - 1) - __half_exponent_bias__(exp_width));
}

int16_t  __min_unbiased_half_exponent__ (uint16_t exp_width)
{
	int16_t bias = __half_exponent_bias__(exp_width);
	int16_t min_val = 1 - bias;
	return(min_val);
}

void classifyDouble(double d, uint8_t* sign,
		uint16_t* exponent,
		uint64_t* mantissa,
		int* is_nan, int* is_pos_inf, int* is_neg_inf,
		int* is_denorm, int* is_pos_zero, 
		int* is_neg_zero, int* is_normalized)
{
	uint64_t x = *((uint64_t*) &d);

	*sign = (x >> 63) & 0x1;
	*exponent = (x >> 52) & 0x3ff;
	*mantissa = (x & 0xfffffffffffff);

	*is_pos_zero = (!(*sign)) && (*exponent == 0) && (*mantissa == 0);
	*is_neg_zero = (*sign) && (*exponent == 0) && (*mantissa == 0);
	*is_denorm   = (*exponent == 0) && (*mantissa != 0);
	*is_pos_inf = (!(*sign)) && (*exponent == 0x3ff) && (*mantissa == 0);
	*is_neg_inf = (*sign) && (*exponent == 0x3ff) && (*mantissa == 0);
	*is_nan = (*exponent == 0x3ff) && (*mantissa != 0);

	*is_normalized   =  (*exponent != 0) && (*exponent != 0x3ff);
}

void classifyFloat(float f, uint8_t* sign,
				uint16_t* exponent,
				uint32_t* mantissa,
				int* is_nan, 
				int* is_pos_inf, int* is_neg_inf,
				int* is_denorm, int* is_pos_zero, 
				int* is_neg_zero, int* is_normalized)
{
	uint32_t x = *((uint32_t*) &f);

	*sign = (x >> 31) & 0x1;
	*exponent = (x >> 23) & 0xff;
	*mantissa = (x & 0x7fffff);

	*is_pos_zero = (! (*sign)) && (*exponent == 0) && (*mantissa == 0);
	*is_neg_zero = (*sign) && (*exponent == 0) && (*mantissa == 0);
	*is_denorm   = (*exponent == 0) && (*mantissa != 0);
	*is_pos_inf = (!(*sign)) && (*exponent == 0xff) && (*mantissa == 0);
	*is_neg_inf = (*sign) && (*exponent == 0xff) && (*mantissa == 0);
	*is_nan = (*exponent == 0xff) && (*mantissa != 0);
	*is_normalized   =  (*exponent != 0) && (*exponent != 0xff);
}

void classifyHalf(half *x, uint8_t* sign, 
				uint16_t* exponent,
				uint32_t* mantissa,
				int* is_nan, int* is_pos_inf, int* is_neg_inf,
				int* is_denorm, int* is_pos_zero, 
				int* is_neg_zero, int* is_normalized)
{
	*sign = (x->value >> 15) & 0x1;
	*exponent = (x->value >> mantissaWidth(x)) & exponentMask(x);
	*mantissa = (x->value & ((1 << mantissaWidth(x))-1));

	*is_pos_zero = (!(*sign)) && (*exponent == 0) && (*mantissa == 0);
	*is_neg_zero = (*sign) && (*exponent == 0) && (*mantissa == 0);
	*is_denorm   = (exponent == 0) && (*mantissa != 0);
	*is_pos_inf = (!(*sign)) && (*exponent == exponentMask(x)) && (*mantissa == 0);
	*is_neg_inf = (*sign) && (*exponent == exponentMask(x)) && (*mantissa == 0);
	*is_nan     = (*exponent == exponentMask(x)) && (*mantissa != 0);

	*is_normalized   =  (*exponent != 0) && (*exponent != exponentMask(x));
}



// pos/neg infinity maps to pos/neg infinity.
// pos/neg zero maps to pos/neg zero
// denorm maps to denorm by using sticky
// normalized maps to 
//    normalized if exponent in range.
//    pos-inf if exponent too large.
//    denorm  if exponent small, but not too small.
//    neg-inf if exponent too too small. 
void floatToHalf(float f, half* x)
{
	uint8_t sign;
	uint16_t exponent;
	uint32_t mantissa;
	int is_nan, is_pos_inf, is_neg_inf, is_pos_zero, is_neg_zero, denorm, norm;
	classifyFloat(f, &sign, &exponent, &mantissa,
			&is_nan, &is_pos_inf, &is_neg_inf, &denorm,
			&is_pos_zero, &is_neg_zero, &norm);
	

	if(is_nan)
	{
		x->value = __half_nan__(exponentWidth(x), sign);
	}
	else if(is_pos_zero || is_neg_zero)
	{
		x->value = (sign << 15);
	}
	else if(is_pos_inf || is_neg_inf)
	{
		x->value = __half_inf__(exponentWidth(x), sign);
	}
	else if(denorm)
	{
		//
		// exponent stays zero.  mantissa gets truncated.
		//
		x->value = (((uint16_t)sign) << 15) | (mantissa >> (23 - mantissaWidth(x)));
	}
	else if(norm)
	{
		// if exponent value is too large, inf.
		int16_t unbiased_float_exponent = 
				((int16_t) exponent) - __float_exponent_bias__(exponentWidth(x));

		if(unbiased_float_exponent > __max_unbiased_half_exponent__(exponentWidth(x)))
		{
			x->value = __half_inf__(exponentWidth(x), sign);
		}	
		else if(unbiased_float_exponent < __min_unbiased_half_exponent__(exponentWidth(x)))
		{
			// get to minimum exponent by shifting the mantissa.
			int shift_amount = 
				(__min_unbiased_half_exponent__(exponentWidth(x)) - 
				 				unbiased_float_exponent);
			
			// add the leading 1 and shift right.
			uint16_t ret_mantissa = 
				(((1 << mantissaWidth(x)) | mantissa) >> 
							(shift_amount + 23 - mantissaWidth(x)));

			// return exponent is 0 (denorm)
			x->value = (((uint16_t) sign) <<  15) | ret_mantissa;
		}
		else
		{
			// mantissa is 10 bits instead of 23.
			uint16_t ret_mantissa = (mantissa >> (23 - mantissaWidth(x)));
			uint16_t ret_exponent = (unbiased_float_exponent + 
							__half_exponent_bias__(exponentWidth(x)));
			x->value = (((uint16_t) sign) <<  15) | 
					(ret_exponent << mantissaWidth(x)) |
									 ret_mantissa;
		}
	}
	else
	{
		assert(0);
	}
}

float    halfToFloat(half *x)
{
	uint8_t sign;
	uint16_t exponent;
	uint32_t mantissa;
	int is_nan, is_pos_inf, is_neg_inf, is_pos_zero, is_neg_zero, denorm, norm;
	classifyHalf(x, &sign, &exponent, &mantissa,
			&is_nan, &is_pos_inf, &is_neg_inf, &denorm,
			&is_pos_zero, &is_neg_zero, &norm);

	uint32_t uret_val;
	float ret_val;
	if(is_nan)
	{
		uret_val = __float_nan__(sign);
	}
	else if(is_pos_zero || is_neg_zero)
	{
		uret_val = (sign << 31);
	}
	else if(is_pos_inf || is_neg_inf)
	{
		uret_val = __float_inf__(sign);
	}
	else if(denorm)
	{
		// mantissa is 23 bits instead of 10
		uret_val = (((uint32_t)sign) << 31) | (mantissa << (23 - mantissaWidth(x)));
	}
	else if(norm)
	{
		int16_t unbiased_float_exponent = 
			((int16_t) exponent) - __half_exponent_bias__(exponentWidth(x));
		// mantissa pad with zeros
		uint32_t ret_mantissa = (mantissa << (23 - mantissaWidth(x)));
		uint32_t ret_exponent = (uint32_t) 
				(unbiased_float_exponent +
						 __float_exponent_bias__(exponentWidth(x)));
		uret_val = (((uint32_t) sign) <<  31) | (ret_exponent << 23) | ret_mantissa;
	}
	else
	{
		assert(0);
	}

	ret_val = *((float*) &uret_val);
	return(ret_val);
}

void intToHalf(int x, half* h)
{
	floatToHalf(((float) x), h);
}

int  halfToInt(half* x)
{
	return((int) halfToFloat(x));
}


void doubleToHalf(double f, half* x)
{
	floatToHalf(((float) f), x);
}

double    halfToDouble(half* x)
{
	return ((double) halfToFloat(x));
}


void addHalf(half* x, half* y, half* sum)
{
	float fx = halfToFloat(x);
	float fy = halfToFloat(y);
	
	float fsum = fx + fy;

	floatToHalf(fsum, sum);
}

void subHalf(half* x, half* y, half* diffr)
{
	float fx = halfToFloat(x);
	float fy = halfToFloat(y);
	
	float fdiff = fx - fy;

	floatToHalf(fdiff, diffr);
}

void mulHalf(half* x, half* y, half* prod)
{
	float fx = halfToFloat(x);
	float fy = halfToFloat(y);
	
	float fprod = fx * fy;

	floatToHalf(fprod, prod);
}

#define HADDOP 0
#define HSUBOP 1
#define HMULOP 2

uint64_t vectorHalfPrecisionOpInU64Form(uint64_t x, uint64_t y, uint8_t exp_width, uint8_t op)
{
	int I;
	uint64_t result = 0;
	for(I = 0; I < 4; I++)
	{
		uint16_t op1 = (x >> (16*I)) & 0xffff;
		uint16_t op2 = (y >> (16*I)) & 0xffff;

		half hx, hy, hz;
		initHalf(&hx, exp_width, op1);
		initHalf(&hy, exp_width, op2);
		initHalf(&hz, exp_width, 0);

		if(op == HADDOP)
			addHalf(&hx, &hy, &hz);
		else if(op == HSUBOP)
			subHalf(&hx, &hy, &hz);
		else if(op == HMULOP)
			mulHalf(&hx, &hy, &hz);

		result = (result | (hz.value << (16*I)));
	}
	return(result);
}

uint64_t vectorHalfPrecisionAddInU64Form(uint64_t x, uint64_t y, uint8_t exp_width)
{
	return(vectorHalfPrecisionOpInU64Form(x,y,exp_width,HADDOP));
}

uint64_t vectorHalfPrecisionSubInU64Form(uint64_t x, uint64_t y,uint8_t exp_width)
{
	return(vectorHalfPrecisionOpInU64Form(x,y,exp_width,HSUBOP));
}
uint64_t vectorHalfPrecisionMulInU64Form(uint64_t x, uint64_t y,uint8_t exp_width)
{
	return(vectorHalfPrecisionOpInU64Form(x,y,exp_width,HMULOP));
}

#define TOHALF 3
#define TOI16  4

uint64_t halfPrecisionConvertBase(uint64_t cvt_op, uint8_t exp_width, uint8_t cvt_type)
{
	int I;
	uint64_t result = 0;
	for(I = 0; I < 4; I++)
	{
		int16_t op = (int16_t) ((cvt_op >> (16*I)) & 0xffff);
		uint64_t lr = 0;

		half hx, hz;
		initHalf(&hx, exp_width, op);
		initHalf(&hz, exp_width, 0);
		if(cvt_type == TOHALF)
		{
			intToHalf(op, &hz);
			lr = ((uint64_t) hz.value) & 0xffff;
		}
		else
		{
			lr = halfToInt(&hx) & 0xffff;
		}

		result = (result |  (lr << (16*I)));
	}
	return(result);
}

uint64_t halfPrecisionToI16VectorConvert(uint64_t cvt_op, uint8_t exp_width)
{
	return(halfPrecisionConvertBase(cvt_op, exp_width, TOI16));
}

uint64_t i16ToHalfPrecisionVectorConvert(uint64_t cvt_op, uint8_t exp_width)
{
	return(halfPrecisionConvertBase(cvt_op, exp_width, TOHALF));
}

uint32_t vectorHalfAddReduce(uint64_t cvt_op,uint8_t half_precision_exponent_width)
{
	int I;

	half hresult;
	initHalf(&hresult, half_precision_exponent_width,0);

	for(I = 0; I < 4; I++)
	{
		uint16_t op = (cvt_op >> (16*I)) & 0xffff;
		uint64_t lr = 0;

		half hx, hz;
		initHalf(&hx, half_precision_exponent_width, op);
		addHalf(&hx, &hresult, &hresult);
	}
	return(hresult.value);
	
}

uint32_t halfToFloatInU32Form(uint32_t operand, uint8_t half_precision_exponent_width)
{
	half x;	
	initHalf(&x, half_precision_exponent_width, operand & 0xffff);
	float fx = halfToFloat(&x);

	uint32_t ret_val = *((uint32_t*) &fx);
	return(ret_val);
}

uint32_t floatToHalfInU32Form(uint32_t operand, uint8_t half_precision_exponent_width)
{
	half x;	
	initHalf(&x, half_precision_exponent_width,0);
	float f = *((float*) &operand);
	floatToHalf(f, &x);

	uint32_t ret_val = x.value;
	return(ret_val);
}

