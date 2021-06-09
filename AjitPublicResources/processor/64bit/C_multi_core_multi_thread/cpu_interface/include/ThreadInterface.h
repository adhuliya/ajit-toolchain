//-------------------------------------------------------------------------
// Interface signals (Appendix C Page 153)
//-------------------------------------------------------------------------

#ifndef __INTERFACES_H__
#define __INTERFACES_H__

#include "RequestTypeValues.h"
#include "Mmu.h"
#include "CacheInterface.h"
#include "AjitThread.h"

//read an Instruction by accessing the instruction fetch interface
void readInstruction(MmuState* ms,  WriteThroughAllocateCache* icache, 
			uint8_t asi, uint32_t addr, uint8_t* mae, uint32_t *inst, uint32_t* mmu_fsr);

//Request ICACHE to flush line containing a given doubleword.
//returns mae=0 after flush is complete
void flushIcacheLine(MmuState* ms,  WriteThroughAllocateCache* icache, 
			uint8_t asi, uint32_t addr, uint8_t* mae);


//read a word from DCACHE.
//  This routine fetches an aligned  doubleword, 
//  and returns one word from the double-word
//  to the cpu.
void readData(MmuState* ms, WriteThroughAllocateCache* dcache,
			 uint8_t asi, uint8_t byte_mask, uint32_t addr, uint8_t* mae, uint32_t *data);

// starts the read and locks the bus.
void lockAndReadData(MmuState* ms, WriteThroughAllocateCache* dcache,
			 uint8_t asi, uint8_t byte_mask, uint32_t addr, uint8_t* mae, uint32_t *data);

void readData64(MmuState* ms, WriteThroughAllocateCache* dcache,
			uint8_t asi, uint8_t byte_mask, uint32_t addr, uint8_t* mae, uint64_t *data);
void lockAndReadData64(MmuState* ms, WriteThroughAllocateCache* dcache,
			uint8_t asi,  uint8_t byte_mask,  uint32_t addr, uint8_t* mae, uint64_t *data);
// same as above, but to Debug.  Ignores trap information in caches.
void readDataToDebug(MmuState* ms, WriteThroughAllocateCache* dcache,
			 uint8_t asi, uint8_t byte_mask, uint32_t addr, uint8_t* mae, uint32_t *data);


// write MMU FSR, FAR through DCACHE.
void updateMmuFsrFar(MmuState* ms, WriteThroughAllocateCache* dcache,
			uint32_t mmu_fsr, uint32_t mmu_far);


//write a word (with a byte mask) to DCACHE.
void writeData(MmuState* ms, WriteThroughAllocateCache* dcache,
			 uint8_t asi, uint32_t addr, uint8_t byte_mask, uint32_t data, uint8_t* mae);

//write a double word (with a byte mask) to DCACHE.
void writeData64(MmuState* ms, WriteThroughAllocateCache* dcache,
			 uint8_t asi, uint32_t addr, uint8_t byte_mask, uint64_t data, uint8_t* mae);

// same as above but from Debug.  Ignores trap information in caches.
void writeDataFromDebug(MmuState* ms, WriteThroughAllocateCache* dcache,
			 uint8_t asi, uint32_t addr, uint8_t byte_mask, uint32_t data, uint8_t* mae);

//send an STBAR request to the Dcache
void sendSTBAR(MmuState* ms, WriteThroughAllocateCache* dcache);


//functions to read interface pipes and set internal flags:
void readBpIRL(ThreadState* s); 
void readBpReset(ThreadState* s) ;
uint8_t getBpIRL(ThreadState* s);

//functions used by cpu to read flags
uint8_t getBpReset(ThreadState* s);
uint8_t getBpFPUPresent(ThreadState* s)  ;
uint8_t getBpFPUException(ThreadState* s) ;
uint8_t getBpFPUCc(ThreadState* s);
uint8_t getBpCPPresent(ThreadState* s) ;
uint8_t getBpCPException(ThreadState* s) ;
uint8_t getBpCPCc(ThreadState* s);
uint8_t getPbError(ThreadState* s);
uint8_t getPbBlockLdstWord(ThreadState* s);
uint8_t getPbBlockLdstByte(ThreadState* s);

//functions used by cpu to write to flags
void setPbError(ThreadState* s, uint8_t val);
void setPbBlockLdstWord(ThreadState* s, uint8_t val);
void setPbBlockLdstByte(ThreadState* s, uint8_t val);

//send a signature to logger pipe
void writeToLoggerPipe(ThreadState* s, uint32_t word);



// Register write trace logging
#include <stdio.h>
FILE* reg_write_ref;    // File pointer of logger-trace
#endif
