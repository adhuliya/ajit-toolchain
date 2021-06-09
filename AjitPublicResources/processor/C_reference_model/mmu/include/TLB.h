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


//each entry in the TLB has the following fields:
struct TLB_entry_type
{
	uint32_t va_tag;	//virtual address tag
	uint32_t ctx_tag;	//context tag
	uint32_t pte;		//page table entry
	uint8_t	 pte_level;	//level at which this pte was found
				//in the page table hierarchy.
				//the level can be:
				//0 => PTE was found in context table
				//1 => PTE was found in Level-1 Table
				//2 => PTE was found in Level-2 Table
				//3 => PTE was found in Level-3 Table
};


//TLB_SIZE is declared in Ajit_Hardware_Configuration.h

//Here's the TLB data structure
extern struct TLB_entry_type TLB_entries[TLB_SIZE];



//initialize TLB state
void initializeTLB();

//write a new entry into the TLB
void writeTLBentry(uint32_t index, uint32_t va_tag, uint32_t ctx_tag, uint32_t pte, uint8_t pte_level);
//update an existing entry in the TLB
void updateTLBentry(uint32_t index, uint32_t pte);


//returns true if a TLB entry is valid
//For a valid entry, the lat two bits in 
//pte should be equal to 2
uint8_t isValidTLBEntry(uint8_t entry_number);



//Check if a given virtual address and context hits in the TLB.
//If hit, return 1, and return index of the corresponding page table entry in TLB
//else return 0.
uint8_t isTLBHit(uint32_t virt_addr, uint32_t current_context, uint32_t* TLB_index);

#endif
