//TLB.c
//
//Implementation of the Translation Lookaside Buffer (TLB)
//(also known as the Page descriptor cache (PDC))
//For the sparc V8 Reference MMU.
//Refer Appendix H in Sparc v8 Reference manual.
////AUTHOR: Neha Karanjkar

#ifdef USE_NEW_TLB

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "Mmu.h"
#include "Ancillary.h"
#include "tlbs.h"

//initialize TLB state
void initializeTlbNew(MmuState* ms)
{
	clearSetAssociativeMemory(ms->tlb_0);
	clearSetAssociativeMemory(ms->tlb_1);
	clearSetAssociativeMemory(ms->tlb_2);
	clearSetAssociativeMemory(ms->tlb_3);
}

//write a new entry into the TLB (note: context is taken from ms)
void writeTlbNewEntry(MmuState* ms, 
			int thread_id, 
			uint32_t virtual_addr,
			uint32_t va_tag, uint32_t pte, uint8_t pte_level)
{
	uint32_t context = ms->MmuContextRegister[thread_id];
	uint32_t tag = va_tag;	 	  
	if	(pte_level==3) 
	{
	  	tag = va_tag | (context << 20);
		writeIntoSetAssociativeMemory(ms->tlb_3,
							tag >> ms->tlb_3->log_number_of_sets,
							pte, ms->tlb_3->set_index_mask & tag);
#ifdef MMU_DEBUG
		fprintf(stderr,"Info: TlbNew: added entry (context=0x%x), tag=0x%x pte=0x%x to tlb_3\n", 
					context, tag,pte);
#endif
	}
	else if	(pte_level==2) 
	{
		tag = (va_tag >> 6) | (context << 14);
		writeIntoSetAssociativeMemory(ms->tlb_2,
						tag >> ms->tlb_2->log_number_of_sets,
						pte, 
						ms->tlb_2->set_index_mask & tag);
#ifdef MMU_DEBUG
		fprintf(stderr,"Info: TlbNew: added entry (context=0x%x), tag=0x%x pte=0x%x to tlb_2\n", 
						context, tag,pte);
#endif
	} 
	else if (pte_level==1) {
		tag = (va_tag >> 12) | (context << 8);
		writeIntoSetAssociativeMemory(ms->tlb_1,
						(tag >> ms->tlb_1->log_number_of_sets),
						pte, ms->tlb_1->set_index_mask & tag);
#ifdef MMU_DEBUG
		fprintf(stderr,"Info: TlbNew: added entry (context = 0x%x), tag=0x%x pte=0x%x to tlb_1\n", 
						context, tag,pte);
#endif
	}
	else if (pte_level==0) 
	{
		tag = context;			    	//use for level 0 pte
		writeIntoSetAssociativeMemory(ms->tlb_0,
						tag >> ms->tlb_0->log_number_of_sets,
						pte, 
						ms->tlb_0->set_index_mask & tag);
#ifdef MMU_DEBUG
		fprintf(stderr,"Info: TlbNew: added entry (context = 0x%x) tag=0x%x pte=0x%x to tlb_0\n", 
						context, tag,pte);
#endif
	}
	
#ifdef MMU_DEBUG
	fprintf(stderr,"Info: added TLB entry VA=0x%x, VA_TAG=0x%x, PPN=0x%x, C=0x%x, ACC=0x%x, PTE_LEVEL=%d\n", 
				virtual_addr, 
				va_tag, (getSlice32(pte,31,8) << 12),
				getSlice32(pte,7,7),
				getSlice32(pte,4,2),
				pte_level);
#endif
}


//Check if a given virtual address and context hits in the TLB.
// (note: context is taken from *ms)
//If hit, return 1, and return  an index to the 
//corresponding page table entry in TLB
//else return 0.
uint8_t isTlbNewHit(MmuState* ms, 
			int thread_id,
			uint32_t virtual_addr,
			uint32_t va_tag, uint32_t* pte, uint8_t*  pte_level)
{
	*pte = 0;
	*pte_level = 0;

	uint32_t context = ms->MmuContextRegister[thread_id];

	uint8_t ret_val = 0;
	uint32_t va_tag_L3 = va_tag | (context << 20);			  //use for level 3 pte
	uint32_t va_tag_L2 = (va_tag >> 6) | (context << 14);		  //use for level 2 pte
	uint32_t va_tag_L1 = (va_tag >> 12) | (context << 8);		  //use for level 1 pte
	uint32_t va_tag_L0 = context;				 	  //use for level 0 pte

	uint64_t ld;
	ret_val = lookupSetAssociativeMemory(ms->tlb_0, 
			(va_tag_L0 >> ms->tlb_0->log_number_of_sets), 
			ms->tlb_0->set_index_mask & va_tag_L0, &ld);
	if(ret_val)
	{
		*pte = ld;
		*pte_level = 0;
	}

	if(!ret_val)
	{
		ret_val = lookupSetAssociativeMemory(ms->tlb_1, 
				(va_tag_L1 >> ms->tlb_1->log_number_of_sets), 
				ms->tlb_1->set_index_mask & va_tag_L1, &ld);
		if(ret_val)
		{
			*pte = ld;
			*pte_level = 1;
		}
	}

	if(!ret_val)
	{
		ret_val = lookupSetAssociativeMemory(ms->tlb_2, 
				(va_tag_L2 >> ms->tlb_2->log_number_of_sets), 
				ms->tlb_2->set_index_mask & va_tag_L2, &ld);
		if(ret_val)
		{
			*pte = ld;
			*pte_level = 2;
		}
	}

	if(!ret_val)
	{
		ret_val = lookupSetAssociativeMemory(ms->tlb_3, 
				(va_tag_L3 >> ms->tlb_3->log_number_of_sets), 
				ms->tlb_3->set_index_mask & va_tag_L3, &ld);
		if(ret_val)
		{
			*pte = ld;
			*pte_level = 3;
		}
	}


	return ret_val;
}





#endif
