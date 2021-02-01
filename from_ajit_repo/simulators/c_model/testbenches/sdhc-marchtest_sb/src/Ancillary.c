//Ancillary.c
//
//
//Ancillary functions used by other modules for bit manipulation etc.
//Author: Sarath Mohan



#include <stdint.h>
#include <stdio.h> 
#include <math.h>
#ifdef SW 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif
#include <pthread.h>
#include "pthreadUtils.h"
#include "Ancillary.h"

MUTEX_DECL(log_mutex__);


void logMessageToStderr(char* msg)
{
	MUTEX_LOCK(log_mutex__);
	fprintf(stderr,"%s\n",msg);
	MUTEX_UNLOCK(log_mutex__);
}

uint8_t getSlice8(uint8_t reg, uint8_t h, uint8_t l)
{
	reg = reg << (7 - h);
	reg = reg >> ((7 - h) + l);
	return reg;
}

uint16_t getSlice16(uint16_t reg, uint8_t h, uint8_t l)
{
	reg = reg << (15 - h);
	reg = reg >> ((15 - h) + l);
	return reg;
}

uint32_t getSlice32(uint32_t reg, uint8_t h, uint8_t l)
{
	reg = reg << (31 - h);
	reg = reg >> ((31 - h) + l);
	return reg;
}

uint64_t getSlice64(uint64_t reg, uint8_t h, uint8_t l)
{
	reg = reg << (63 - h);
	reg = reg >> ((63 - h) + l);
	return reg;
}

uint8_t getBit8(uint8_t reg, uint8_t pos)
{
	return getSlice8(reg, pos, pos);
}

uint8_t getBit16(uint16_t reg, uint8_t pos)
{
	return getSlice16(reg, pos, pos);
}

// from a 32-bit value (reg), extract the
// bit at position pos.
//
//  reg is assumed to be [31:0]
//
uint8_t getBit32(uint32_t reg, uint8_t pos)
{
	return getSlice32(reg, pos, pos);
}

uint8_t getBit64(uint64_t reg, uint8_t pos)
{
	return getSlice64(reg, pos, pos);
}

uint8_t setSlice8(uint8_t reg, uint8_t h, uint8_t l, uint8_t value)
{
	uint8_t mask = -1;
	mask = mask >> (7 - h + l);
	value = value & mask;
	value = value << l;

	mask = mask << l;
	reg = reg & ~mask;
	reg = reg | value;
	return reg;
}

uint16_t setSlice16(uint16_t reg, uint8_t h, uint8_t l, uint16_t value)
{
	uint16_t mask = -1;
	mask = mask >> (15 - h + l);
	value = value & mask;
	value = value << l;

	mask = mask << l;
	reg = reg & ~mask;
	reg = reg | value;
	return reg;
}

uint32_t setSlice32(uint32_t reg, uint8_t h, uint8_t l, uint32_t value)
{
	uint32_t mask = -1;
	mask = mask >> (31 - h + l);
	value = value & mask;
	value = value << l;

	mask = mask << l;
	reg = reg & ~mask;
	reg = reg | value;
	return reg;
}

uint64_t setSlice64(uint64_t reg, uint8_t h, uint8_t l, uint64_t value)
{
	uint64_t mask = -1;
	mask = mask >> (63 - h + l);
	value = value & mask;
	value = value << l;

	mask = mask << l;
	reg = reg & ~mask;
	reg = reg | value;
	return reg;
}

uint8_t setBit8(uint8_t reg, uint8_t pos, uint8_t value)
{
	return setSlice8(reg, pos, pos, value);
}

uint16_t setBit16(uint16_t reg, uint8_t pos, uint8_t value)
{
	return setSlice16(reg, pos, pos, value);
}

uint32_t setBit32(uint32_t reg, uint8_t pos, uint8_t value)
{
	return setSlice32(reg, pos, pos, value);
}

uint64_t setBit64(uint64_t reg, uint8_t pos, uint8_t value)
{
	return setSlice64(reg, pos, pos, value);
}

uint32_t signExtend(uint32_t val, uint8_t highest_bit)
{
	uint32_t result;
	uint32_t sign;
	//find out the sign
	sign = getSlice32(val, highest_bit, highest_bit);
	//copy the sign bit to the most significant bits
	if(sign == 0)
	{
		result = setSlice32(val, 31, highest_bit, 0);
	}
	else
	{
		uint32_t all_f = -1;
		result = setSlice32(val, 31, highest_bit, all_f);
	}

	return result;
}

uint32_t zeroExtend(uint32_t val, uint8_t highest_bit)
{
	uint32_t result;
	//copy 0 to the most significant bits
	if(highest_bit < 31)
		result = setSlice32(val, 31, highest_bit, 0);

	return result;
}

uint32_t signExtendByte(uint32_t byte)
{
	return signExtend(byte, 7);
}

uint32_t zeroExtendByte(uint32_t byte)
{
	return zeroExtend(byte, 8);
}

uint32_t signExtendHalfWord(uint32_t halfword)
{
	return signExtend(halfword, 15);
}

uint32_t zeroExtendHalfWord(uint32_t halfword)
{
	return zeroExtend(halfword, 16);
}

uint64_t divideUnsigned(uint64_t dividend, uint32_t divisor)
{
        uint64_t quotient = 0;
        if (divisor != 0)
        {
                while (dividend >= divisor)
                {
                        uint64_t curr_quotient = 1;
                        uint64_t shifted_divisor = divisor;
                        uint64_t reduced_dividend_by_2 = (dividend >> 1);
                        while (1)
                        {
                                if (shifted_divisor < reduced_dividend_by_2)
                                {
                                        shifted_divisor = (shifted_divisor << 1);
                                        curr_quotient = (curr_quotient << 1);
                                }
                                else
                                {
                                        break;
                                }
                        }
                        quotient += curr_quotient;
                        dividend -= shifted_divisor;
                }
        }
        return (quotient);
}

int64_t divideSigned(int64_t dividend, int32_t divisor)
{
        int8_t sign = 1;
        uint64_t udividend;
        uint32_t udivisor;
        if (dividend < 0)
        {
                sign = -sign;
                udividend = (uint64_t)(-dividend);
        }
        else
                udividend = (uint64_t) dividend;

        if (divisor < 0)
        {
                sign = -sign;
                udivisor = (uint32_t)(-divisor);
        }
        else
                udivisor = (uint32_t) divisor;

        int64_t quotient = 0;
        if (udivisor != 0)
        {
                quotient = divideUnsigned(udividend, udivisor);
                if (sign < 0)
                        quotient = -quotient;
        }
        return (quotient);
}

double doubleSqrt(double a)
{
	double ret_val = 0.0;
	if ( a > 0.0)
		ret_val = pow (a, 0.5);
	return(ret_val);
}

double doubleDiv(double a, double b)
{
	double ret_val = a/b;
	return ret_val;
}


uint8_t rem8(uint8_t Q, uint8_t D)
{
    if(Q < D)
	return(Q);

    int8_t idx;
    for(idx = 7; idx >= 0;  idx--)
    {
	uint8_t M = (1 << idx);
        Q = ((D & M) ? (Q - M) : Q);
	if(Q < D)
	   return(Q);
    }
    return(Q);
}

