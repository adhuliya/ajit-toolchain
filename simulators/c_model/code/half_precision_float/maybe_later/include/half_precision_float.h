#ifndef _ieee_half_precision___
#define _ieee_half_precision___
#include <stdint.h>



//
// Variable precision 16-bit format.  The exponent
// has a variable number of bits.  The default IEEE
// half precision exponent has 5 bits, which is too
// small.  We permit larger (and smaller) exponents.
//
// the base representation is coded as a uint16_t
//
typedef struct half__ 
{
	uint8_t  exponent_width;
	uint16_t value;
} half;


uint16_t exponentWidth(half* x);
uint16_t mantissaWidth(half* x);
void initHalf(half* x, uint8_t exp, uint16_t val);
half* makeHalf(uint8_t exp, uint16_t val);

void classifyDouble(double d, uint8_t* sign,
		uint16_t* exponent,
		uint64_t* mantissa,
		int* is_nan, int* is_pos_inf, int* is_neg_inf,
		int* is_denorm, int* is_pos_zero, 
		int* is_neg_zero, int* is_normalized);
void classifyFloat(float f, uint8_t* sign,
				uint16_t* exponent,
				uint32_t* mantissa,
				int* is_nan, 
				int* is_pos_inf, int* is_neg_inf,
				int* is_denorm, int* is_pos_zero, 
				int* is_neg_zero, int* is_normalized);
void classifyHalf(half *x, 
			uint8_t* sign, 
			uint16_t* exponent,
			uint32_t* mantissa,
			int* is_nan, int* is_pos_inf, int* is_neg_inf,
			int* is_denorm, int* is_pos_zero, 
			int* is_neg_zero, int* is_normalized);

void floatToHalf(float f, half *h);
float    halfToFloat(half *x);

void intToHalf(int x, half* h);
int  halfToInt(half* h);

void doubleToHalf(double f, half* x);
double    halfToDouble(half* x);

void addHalf(half *x, half *y, half* sum);
void subHalf(half *x, half *y, half* diffr);
void mulHalf(half *x, half *y, half* prod);

uint64_t vectorHalfPrecisionOpInU64Form(uint64_t x, uint64_t y, uint8_t exp_width, uint8_t op);
uint64_t vectorHalfPrecisionAddInU64Form(uint64_t x, uint64_t y, uint8_t exp_width);
uint64_t vectorHalfPrecisionSubInU64Form(uint64_t x, uint64_t y, uint8_t exp_width);
uint64_t vectorHalfPrecisionMulInU64Form(uint64_t x, uint64_t y, uint8_t exp_width);

	
uint64_t halfPrecisionToI16VectorConvert(uint64_t cvt_op, uint8_t exp_width);
uint64_t i16ToHalfPrecisionVectorConvert(uint64_t cvt_op, uint8_t exp_width);

uint32_t vectorHalfAddReduce(uint64_t cvt_op,uint8_t half_precision_exponent_width);
uint32_t halfToFloatInU32Form(uint32_t operand, uint8_t half_precision_exponent_width);
uint32_t floatToHalfInU32Form(uint32_t operand, uint8_t half_precision_exponent_width);
#endif
