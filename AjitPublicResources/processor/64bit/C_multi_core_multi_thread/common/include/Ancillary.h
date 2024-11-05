//Ancillary.h
//Author: Sarath Mohan


#ifndef __ANCILLARY_H__
#define __ANCILLARY_H__


#define _BITCAST_(Type,val) ((Type) (*((Type*)&val)))

void logMessageToStderr(char* msg);

//returns a continuous set of bits from position h to l from reg.
//the selected bits are right justified into a 8 bit result.
//0<=l<=h<=7
uint8_t getSlice8(uint8_t reg, uint8_t h, uint8_t l);

//returns a continuous set of bits from position h to l from reg.
//the selected bits are right justified into a 16 bit result.
//0<=l<=h<=15
uint16_t getSlice16(uint16_t reg, uint8_t h, uint8_t l);

//returns a continuous set of bits from position h to l from reg.
//the selected bits are right justified into a 32 bit result.
//0<=l<=h<=31
uint32_t getSlice32(uint32_t reg, uint8_t h, uint8_t l);

//returns a continuous set of bits from position h to l from reg.
//the selected bits are right justified into a 64 bit result.
//0<=l<=h<=63
uint64_t getSlice64(uint64_t reg, uint8_t h, uint8_t l);

//Insert the bits from h to l in reg with value.
uint8_t setSlice8(uint8_t reg, uint8_t h, uint8_t l, uint8_t value);

//Insert the bits from h to l in reg with value.
uint16_t setSlice16(uint16_t reg, uint8_t h, uint8_t l, uint16_t value);

//Insert the bits from h to l in reg with value.
uint32_t setSlice32(uint32_t reg, uint8_t h, uint8_t l, uint32_t value);

//Insert the bits from h to l in reg with value.
uint64_t setSlice64(uint64_t reg, uint8_t h, uint8_t l, uint64_t value);

// returns the bit at pos.
uint8_t getBit8(uint8_t reg, uint8_t pos);

// returns the bit at pos.
uint8_t getBit16(uint16_t reg, uint8_t pos);

// returns the bit at pos.
uint8_t getBit32(uint32_t reg, uint8_t pos);

// returns the bit at pos.
uint8_t getBit64(uint64_t reg, uint8_t pos);

//Set the bit at pos with 0 or 1.
uint8_t setBit8(uint8_t reg, uint8_t pos, uint8_t value);

//Set the bit at pos with 0 or 1.
uint16_t setBit16(uint16_t reg, uint8_t pos, uint8_t value);

//Set the bit at pos with 0 or 1.
uint32_t setBit32(uint32_t reg, uint8_t pos, uint8_t value);

//Set the bit at pos with 0 or 1.
uint64_t setBit64(uint64_t reg, uint8_t pos, uint8_t value);

//The highest_bit is used to decide whether the number is positive or negative.
uint32_t signExtend(uint32_t val, uint8_t highest_bit);

//Insert 0s upto and including the highest_bit.
uint32_t zeroExtend(uint32_t val, uint8_t highest_bit);

//Extend the sign of a byte to 32 bits.
uint32_t signExtendByte(uint32_t byte);

//Extend a byte to 32 bits by inserting 0s at the MSBs.
uint32_t zeroExtendByte(uint32_t byte);

//Extend the sign of a half word to 32 bits. 
uint32_t signExtendHalfWord(uint32_t halfword);

//Extend a half word to 32 bits by inserting 0s at the MSBs.
uint32_t zeroExtendHalfWord(uint32_t halfword);

// Unsigned Divide
uint64_t divideUnsigned(uint64_t dividend, uint32_t divisor);

// Signed Divide
int64_t divideSigned(int64_t dividend, int32_t divisor);

// Float divide
double doubleDiv(double a, double b);

// Float square root
double doubleSqrt(double a);

// remainder
uint8_t rem8(uint8_t Q, uint8_t D);

int calculate_log2(int number_of_lines);
uint64_t insert_bytes_into_dword (uint64_t oval, uint8_t bmask, uint64_t wval);

#endif
