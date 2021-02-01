
#ifndef __FP_EXCEPTIONS__H__
#define __FP_EXCEPTIONS__H__

uint8_t isNaN32(float op);
uint8_t isNaN64(double op);
uint8_t isSNaN32(float op);
uint8_t isSNaN64(double op);
uint8_t isQNaN32(float op);
uint8_t isQNaN64(double op);
uint8_t isPosZero32(float op);
uint8_t isPosZero64(double op);
uint8_t isNegZero32(float op);
uint8_t isNegZero64(double op);
uint8_t isPosInf32(float op);
uint8_t isPosInf64(double op);
uint8_t isNegInf32(float op);
uint8_t isNegInf64(double op);
uint8_t isPosDenormal32(float op);
uint8_t isPosDenormal64(double op);
uint8_t isNegDenormal32(float op);
uint8_t isNegDenormal64(double op);
uint8_t check_sNaN32(float op);
uint8_t check_sNaN64(double op);

uint8_t isFpInvalidOp(Opcode op, float f1_s, float f2_s, double f1_d, double f2_d);
uint8_t isNvmSet(uint32_t fsr);

uint8_t isNeg32(float op);
uint8_t isNeg64(double op);

#endif
