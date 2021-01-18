#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Sdhc.h"

/* DECLARED in SDHC.H, but written here in comments for reference

//Functions for register value manipulations

void writeSdhcReg(uint32_t data_in, uint32_t addr, uint8_t byte_mask, 
struct CPUViewOfSDHCRegs *str,struct SDHCInternalMap *int_str);

void readSdhcReg(uint32_t data_out, uint32_t addr,  
struct CPUViewOfSDHCRegs *str,struct SDHCInternalMap *int_str);

//Accumulates the parameters to be inserted in the 48 bit frame
// and places them in the required manner
void generateCommandForSDCard(struct SDHCInternalMap *int_str);
void receiveResponseFromSDCard();*/
