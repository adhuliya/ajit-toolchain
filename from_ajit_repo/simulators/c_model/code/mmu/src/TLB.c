//TLB.c
//
//Implementation of the Translation Lookaside Buffer (TLB)
//(also known as the Page descriptor cache (PDC))
//For the sparc V8 Reference MMU.
//Refer Appendix H in Sparc v8 Reference manual.
////AUTHOR: Neha Karanjkar

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "Mmu.h"
#include "Ancillary.h"


//initialize TLB state
void initializeTLB(MmuState* ms)
{
	int i;
	for(i=0;i<TLB_SIZE;i++)
	{
		ms->TLB_entries[i].va_tag=0;
		ms->TLB_entries[i].ctx_tag=0;
		ms->TLB_entries[i].pte=0;
		ms->TLB_entries[i].pte_level=0;
	}

}

//write a new entry into the TLB
void writeTLBentry(MmuState* ms,
			 uint32_t index, uint32_t va_tag, uint32_t ctx_tag, 
			uint32_t pte, uint8_t pte_level)
{
	uint32_t tag = va_tag;	 	  
	if	(pte_level==3) tag = va_tag;		    	//use for level 2 pte
	else if	(pte_level==2) tag = setSlice32(va_tag, 5,0,0); //use for level 2 pte
	else if (pte_level==1) tag = setSlice32(va_tag,11,0,0); //use for level 1 pte
	else if (pte_level==0) tag = 0;			    	//use for level 0 pte
	
	ms->TLB_entries[index].va_tag=tag;
	ms->TLB_entries[index].ctx_tag=ctx_tag;
	ms->TLB_entries[index].pte=pte;
	ms->TLB_entries[index].pte_level=pte_level;

#ifdef MMU_DEBUG
	fprintf(stderr,"Info: added TLB entry VA_TAG=0x%x, PPN=0x%x, C=0x%x, ACC=0x%x, PTE_LEVEL=%d\n", va_tag, (getSlice32(pte,31,8) << 12),
												getSlice32(pte,7,7),
												getSlice32(pte,4,2),
												pte_level);
#endif
}

//update an existing entry in the TLB
void updateTLBentry(MmuState* ms, uint32_t index, uint32_t pte)
{
		ms->TLB_entries[index].pte=pte;
}


//returns true if a TLB entry is valid
//For a valid entry, the lat two bits in 
//pte should be equal to 2
uint8_t isValidTLBEntry(MmuState* ms, uint8_t entry_number)
{
	uint32_t pte = ms->TLB_entries[entry_number].pte;
	if(getSlice32(pte,1,0)==0x2) return 1;
	else return 0;
}




//Check if a given virtual address and context hits in the TLB.
//If hit, return 1, and return  an index to the 
//corresponding page table entry in TLB
//else return 0.
uint8_t isTLBHit(MmuState* ms, uint32_t va_tag, uint32_t current_context, uint32_t* TLB_index)
{

	//from virtual address tag (va_tag),
	//obtain values which we shall use for 
	//comparison with TLB tags depending on the level of PTE 
	uint32_t va_tag_L3 = va_tag;			  //use for level 3 pte
	uint32_t va_tag_L2 = setSlice32(va_tag_L3, 5,0,0);//use for level 2 pte
	uint32_t va_tag_L1 = setSlice32(va_tag_L3,11,0,0);//use for level 1 pte
	//uint32_t va_tag_L0 = 0;			 //use for level 0 pte


	//go though each TLB entry to find a match
	uint32_t i;
	for(i=0;i<TLB_SIZE;i++)
	{
		if(isValidTLBEntry(ms, i)) //check if TLB entry is valid
		{
			//Check if context matches
			if(current_context== ms->TLB_entries[i].ctx_tag)
			{
				//Check if tag matches
				if( ( (ms->TLB_entries[i].pte_level==3) && 
					(va_tag_L3== ms->TLB_entries[i].va_tag))
				||  ( (ms->TLB_entries[i].pte_level==2) && 
					(va_tag_L2==setSlice32(ms->TLB_entries[i].va_tag, 5,0,0)))
				||  ( (ms->TLB_entries[i].pte_level==1) && 
					(va_tag_L1==setSlice32(ms->TLB_entries[i].va_tag, 11,0,0)))
				||  ( (ms->TLB_entries[i].pte_level==0) )
				)
				{ 
					//match found
					*TLB_index = i;
					return 1; 
				}
			}

		}
	}
	//match was not found
	return 0;
}

		



