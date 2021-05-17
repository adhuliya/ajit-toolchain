#ifndef __IMPLEMENTATIONDEPENDENT_H__
#define __IMPLEMENTATIONDEPENDENT_H__

#define NWINDOWS 8

uint8_t privilegedASR(uint8_t addr);
uint8_t illegalInstructionASR(uint8_t addr);

#endif 
