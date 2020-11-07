#include <stdint.h>
#include "ImplementationDependent.h"

uint8_t privilegedASR(uint8_t addr)
{
	return 1;// Currently all of the ASR registers are privileged
}

uint8_t illegalInstructionASR(uint8_t addr)
{
	return 0;// Currently it is legal to read/write to all asr's. ( 0 to 31)
}

