//TLB.h
//
#ifndef _TLB_H
#define _TLB_H
//Implementation of the Translation Lookaside Buffer (TLB)
//(also known as the Page descriptor cache (PDC))
//For the sparc V8 Reference MMU.
//Refer Appendix H in Sparc v8 Reference manual.
////AUTHOR: Neha Karanjkar
#include <stdint.h>
#include <Ajit_Hardware_Configuration.h>
#include "Mmu.h"

#ifndef USE_NEW_TLB



//initialize TLB state
void initializeTLB(MmuState* ms);

//write a new entry into the TLB
void writeTLBentry(MmuState* ms,
			uint32_t index, uint32_t va_tag, uint32_t ctx_tag,
			uint32_t pte, uint8_t pte_level);
//update an existing entry in the TLB
void updateTLBentry(MmuState* ms,
			uint32_t index, uint32_t pte);


//returns true if a TLB entry is valid
//For a valid entry, the lat two bits in 
//pte should be equal to 2
uint8_t isValidTLBEntry(MmuState* ms,
				uint8_t entry_number);



//Check if a given virtual address and context hits in the TLB.
//If hit, return 1, and return index of the corresponding page table entry in TLB
//else return 0.
uint8_t isTLBHit(MmuState* ms,
			uint32_t virt_addr, uint32_t current_context, uint32_t* TLB_index);

#endif
#endif
