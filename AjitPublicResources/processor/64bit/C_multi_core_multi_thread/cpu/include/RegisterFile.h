#ifndef __REGISTER_FILE_H__
#define __REGISTER_FILE_H__

#include "ImplementationDependent.h"

typedef struct __Registerfile {
	uint32_t g[8]; // Global Registers
	uint32_t r[16 * NWINDOWS]; // Windowed Registers
	uint32_t f[32]; // General Purpose floating point registers;

} RegisterFile;

void resetRegisterFile(RegisterFile* rf);
RegisterFile*  makeRegisterFile();

void writeRegister(uint32_t pc, RegisterFile *rf, uint8_t addr, uint8_t cwp, uint32_t value);
void writeFRegister(RegisterFile *rf, uint8_t addr, uint32_t value);

uint32_t readRegister(RegisterFile* rf, uint8_t addr, uint8_t cwp);
uint32_t readFRegister(RegisterFile* rf, uint8_t addr);

void dumpRegisters (RegisterFile* rf, uint8_t cwp);


#endif
