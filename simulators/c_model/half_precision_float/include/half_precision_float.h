#ifndef _ieee_half_precision___
#define _ieee_half_precision___
#include <stdint.h>
//
typedef uint16_t half;

half addHalf (half x, half y);
half subHalf (half x, half y);
half mulHalf (half x, half y);
half floatToHalf(float x);
float halfToFloat(half x);
int   halfToInt(half x);
half  intToHalf(int x);


uint64_t vectorHalfPrecisionOpInU64Form(uint64_t x, uint64_t y,  uint8_t op);
uint64_t vectorHalfPrecisionAddInU64Form(uint64_t x, uint64_t y);
uint64_t vectorHalfPrecisionSubInU64Form(uint64_t x, uint64_t y);
uint64_t vectorHalfPrecisionMulInU64Form(uint64_t x, uint64_t y);

	
uint64_t halfPrecisionToI16VectorConvert(uint64_t cvt_op);
uint64_t i16ToHalfPrecisionVectorConvert(uint64_t cvt_op);

uint32_t vectorHalfAddReduce(uint64_t cvt_op);
uint32_t halfToFloatInU32Form(half operand);
half     floatToHalfInU32Form(uint32_t operand);

#endif
