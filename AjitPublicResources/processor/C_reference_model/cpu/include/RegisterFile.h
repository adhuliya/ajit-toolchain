#ifndef __REGISTER_FILE_H__
#define __REGISTER_FILE_H__

void initRegisterFile();

void writeRegister( uint8_t addr, uint8_t cwp, uint32_t value);
void writeFRegister( uint8_t addr, uint32_t value);

uint32_t readRegister(uint8_t addr, uint8_t cwp);
uint32_t readFRegister(uint8_t addr);


#endif
