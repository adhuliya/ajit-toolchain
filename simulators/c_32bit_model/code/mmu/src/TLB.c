//TLB.c
//
//Implementation of the Translation Lookaside Buffer (TLB)
//(also known as the Page descriptor cache (PDC))
//For the sparc V8 Reference MMU.
//Refer Appendix H in Sparc v8 Reference manual.
////AUTHOR: Neha Karanjkar

#include <stdlib.h>
#include <stdint.h>
#include "TLB.h"
#include "Ancillary.h"


//In TLB.h :
//each entry in the TLB has the following fields:
//struct TLB_entry_type
//{
//	uint32_t va_tag;	//virtual address tag
//	uint32_t ctx_tag;	//context tag
//	uint32_t pte;		//page table entry
//	uint8_t	 pte_level;	//level at which this pte was found
//				//in the page table hierarchy.
//				//the level can be:
//				//0 => PTE was found in context table
//				//1 => PTE was found in Level-1 Table
//				//2 => PTE was found in Level-2 Table
//				//3 => PTE was found in Level-3 Table
//};
//number of entries in the TLB
//#define TLB_SIZE	64 


//Here's the TLB.
//Its just an array of TLB entries.
struct TLB_entry_type TLB_entries[TLB_SIZE];


//initialize TLB state
void initializeTLB()
{
	int i;
	for(i=0;i<TLB_SIZE;i++)
	{
		TLB_entries[i].va_tag=0;
		TLB_entries[i].ctx_tag=0;
		TLB_entries[i].pte=0;
		TLB_entries[i].pte_level=0;
	}

}

//write a new entry into the TLB
void writeTLBentry(uint32_t index, uint32_t va_tag, uint32_t ctx_tag, uint32_t pte, uint8_t pte_level)
{
	uint32_t tag = va_tag;	 	  
	if	(pte_level==3) tag = va_tag;		    	//use for level 2 pte
	else if	(pte_level==2) tag = setSlice32(va_tag, 5,0,0); //use for level 2 pte
	else if (pte_level==1) tag = setSlice32(va_tag,11,0,0); //use for level 1 pte
	else if (pte_level==0) tag = 0;			    	//use for level 0 pte
	
	TLB_entries[index].va_tag=tag;
	TLB_entries[index].ctx_tag=ctx_tag;
	TLB_entries[index].pte=pte;
	TLB_entries[index].pte_level=pte_level;
}

//update an existing entry in the TLB
void updateTLBentry(uint32_t index, uint32_t pte)
{
		TLB_entries[index].pte=pte;
}


//returns true if a TLB entry is valid
//For a valid entry, the lat two bits in 
//pte should be equal to 2
uint8_t isValidTLBEntry(uint8_t entry_number)
{
	uint32_t pte =TLB_entries[entry_number].pte;
	if(getSlice32(pte,1,0)==0x2) return 1;
	else return 0;
}




//Check if a given virtual address and context hits in the TLB.
//If hit, return 1, and return  an index to the 
//corresponding page table entry in TLB
//else return 0.
uint8_t isTLBHit(uint32_t va_tag, uint32_t current_context, uint32_t* TLB_index)
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
		if(isValidTLBEntry(i)) //check if TLB entry is valid
		{
			//Check if context matches
			if(current_context==TLB_entries[i].ctx_tag)
			{
				//Check if tag matches
				if( ( (TLB_entries[i].pte_level==3) && (va_tag_L3==TLB_entries[i].va_tag))
				||  ( (TLB_entries[i].pte_level==2) && (va_tag_L2==setSlice32(TLB_entries[i].va_tag, 5,0,0)))
				||  ( (TLB_entries[i].pte_level==1) && (va_tag_L1==setSlice32(TLB_entries[i].va_tag, 11,0,0)))
				||  ( (TLB_entries[i].pte_level==0) )
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

		



