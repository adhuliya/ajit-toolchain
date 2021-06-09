//-------------------------------------------------------------------------
// Interface signals (Appendix C Page 153)
//-------------------------------------------------------------------------

#ifndef __INTERFACES_H__
#define __INTERFACES_H__

#include"RequestTypeValues.h"

//read an Instruction by accessing the instruction fetch interface
void readInstruction(uint8_t asi, uint32_t addr, uint8_t* mae, uint32_t *inst, uint32_t* mmu_fsr);

//Request ICACHE to flush line containing a given doubleword.
//returns mae=0 after flush is complete
void flushIcacheLine(uint8_t asi, uint32_t addr, uint8_t* mae);


//read a word from DCACHE.
//This routine fetches an aligned  doubleword, 
//and returns one word from the double-word
//to the cpu.
void readData( uint8_t asi, uint32_t addr, uint8_t* mae, uint32_t *data);
void readData64(uint8_t asi, uint32_t addr, uint8_t* mae, uint64_t *data);
// same as above, but to Debug.  Ignores trap information in caches.
void readDataToDebug( uint8_t asi, uint32_t addr, uint8_t* mae, uint32_t *data);


// write MMU FSR, FAR through DCACHE.
void updateMmuFsrFar(uint32_t mmu_fsr, uint32_t mmu_far);


//write a word (with a byte mask) to DCACHE.
void writeData( uint8_t asi, uint32_t addr, uint8_t byte_mask, uint32_t data, uint8_t* mae);


//write a double word (with a byte mask) to DCACHE.
void writeData64( uint8_t asi, uint32_t addr, uint8_t byte_mask, uint64_t data, uint8_t* mae);

// same as above but from Debug.  Ignores trap information in caches.
void writeDataFromDebug( uint8_t asi, uint32_t addr, uint8_t byte_mask, uint32_t data, uint8_t* mae);

//send an STBAR request to the Dcache
void sendSTBAR();


//functions to read interface pipes and set internal flags:
void readBpIRL(); 
void readBpReset() ;
uint8_t getBpIRL();

//functions used by cpu to read flags
uint8_t getBpReset();
uint8_t getBpFPUPresent()  ;
uint8_t getBpFPUException() ;
uint8_t getBpFPUCc();
uint8_t getBpCPPresent() ;
uint8_t getBpCPException() ;
uint8_t getBpCPCc();
uint8_t getPbError();
uint8_t getPbBlockLdstWord();
uint8_t getPbBlockLdstByte();

//functions used by cpu to write to flags
void setPbError( uint8_t val);
void setPbBlockLdstWord( uint8_t val);
void setPbBlockLdstByte( uint8_t val);

//send a signature to logger pipe
void writeToLoggerPipe( uint32_t word);



// Register write trace logging
#include <stdio.h>
FILE* reg_write_ref;    // File pointer of logger-trace
#endif
