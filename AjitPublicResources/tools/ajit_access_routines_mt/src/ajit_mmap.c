#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"
#include "ajit_mmap.h"

uint32_t ajit_mmap_index_into_table(uint8_t level, uint32_t va)
{
	uint32_t ret_val = 0;
	switch(level)
	{
		case 0:
			ret_val = va & 0xff; // context.
			break;
		case 1: 
			ret_val = (va >> 24) & 0x3f;	
			break;
		case 2:
			ret_val = (va >> 18) & 0x3f;	
			break;
		case 3: 
			ret_val = (va >> 12) & 0x3f;	
			break;
		default:
			break;
	}
	return(ret_val);
}

uint8_t ajit_mmap_is_pte(uint32_t entry)
{
	uint8_t rv = ((entry & 0x3) == 0x2);
	return(rv);
}

uint8_t ajit_mmap_is_ptd(uint32_t entry)
{
	uint8_t rv = ((entry & 0x3) == 0x1);
	return(rv);
}

uint64_t ajit_mmap_get_phy_addr_from_ptd(uint32_t ptd, uint8_t level, uint32_t index)
{
        uint64_t phy_addr= (ptd >> 2) << 2; 

        phy_addr = phy_addr << 4;
        phy_addr = phy_addr | (index << 2);

        return phy_addr;

}

uint64_t ajit_mmap_get_phy_addr_from_pte(uint32_t pte, uint8_t level, uint32_t va)
{
	uint64_t page_offset = 0;
	if(level == 3)
		page_offset = (va & 0xfff);	
	else if(level == 2)
		page_offset = (va & 0x3fff);	
	else if(level == 1)
		page_offset = (va & 0xffffff);	
	else 
		page_offset = va;

	uint32_t ppn = (pte >> 8);
	uint64_t pa = 0;
	pa = ppn;
	pa = pa << 12;
	pa = pa | page_offset;

	return(pa);
}
					
uint32_t ajit_mmap_make_ptd(uint8_t level, uint64_t pa)
{
	uint64_t pa_shifted = pa;
	pa_shifted = (pa_shifted >> 6) << 2;
	uint32_t ptd = ((uint32_t) pa_shifted ) | 0x1;
	return(ptd);
}

uint32_t ajit_mmap_make_pte(uint8_t level, uint8_t acc, uint32_t va, uint64_t pa)
{
	uint64_t ppn_64 = (pa >> 12);
	uint32_t pte = ((uint32_t) ppn_64) | (((uint32_t) acc) << 2) | 0x2;
	return(pte);
}
				
//
// return 
//        0 if matching pte found
//        1 if matching pte not found.
// 
// *level, *ptde_a, *ptde specify
// the point at which the trail ended or went cold.
//
int ajit_lookup_mmap (
	// page table base address
	uint64_t page_table_base_phy_addr, 
	// context for lookup.
	uint8_t context, 
	// va for lookup
	uint32_t va, 
	// level at which search ended.
	uint8_t* level, 
	// translated pa if pte found.
	uint64_t* pa,
	// ptde address where search ended.
	uint64_t* ptde_a, 
	// ptde value at the point where
	// search ended.
	uint32_t* ptde)
{
	int ret_val = 0;
	*level  = 0;
	*pa     = 0;
	*ptde_a = 0;
	*ptde   = 0;

	uint64_t context_table_base_address  = page_table_base_phy_addr;
	uint64_t current_entry_address  = context_table_base_address + (4*context);
	uint8_t  current_level = 0;

	while(1)	
	{

		uint32_t current_entry = 
			__ajit_phy_mem_read_word__(current_entry_address);

		uint32_t index_into_table =
			((current_level == 0) ? context : 
					indexIntoTable(current_level, va));

		*level = current_level;
		*ptde_a    = current_entry_address;
		*ptde      = current_entry;

		// is it a PTD?
		if(ajit_mmap_is_ptd (current_entry))
		{
			// Yes, it is a PTD.  Calculate the physical
			// address of the next entry.
			current_entry_address = 
				ajit_mmap_get_phy_addr_from_ptd(current_entry, current_level, index_into_table);

		}
		else if(ajit_mmap_is_pte(current_entry))
		{
			// A PTE.  record the hit info and return.
			*pa    = ajit_mmap_get_phy_addr_from_pte(current_entry, current_level, va);
			ret_val = 1;
			break;
		}

		if(current_level == 3)
		{
			break;
		}
			
		current_level++;
	}

	return(ret_val);
}


// call this function only if you have allocated
// a table where the PTE will go.  That is, the
// lookup must be called before the mmap!
int ajit_mmap_operation 
	(	// base address of page table
		uint64_t page_table_base_phy_address,
		// operation? ADD/DELETE.
		uint8_t operation,
		// Context..
		uint8_t context, 
		// level
		uint8_t level, 
		// permissions
		uint8_t acc, 
		// virtual address of page
		uint32_t va, 
		// physical address of page
		uint32_t pa
	)
{
	int ret_val = 0;

	uint8_t  pdte_level;
	uint32_t pdte;
	uint64_t pdte_a;
	uint64_t ign_pa;
	uint8_t status = ajit_lookup_mmap(page_table_base_phy_address,
							context, va,
							&pdte_level,
							&ign_pa,
							&pdte_a,
							&pdte);
	if(pdte_level == level)
	{
		if(operation == ADD_TO_MMAP_OP)
		{
			// update context entry...
			pdte = ajit_mmap_make_pte(level, acc, va, pa);
		}
		else if(operation == DELETE_FROM_MMAP_OP)
		{
			pdte = 0x0;
		}

		__ajit_phy_mem_write_word__(pdte_a, pdte);
	}
	else
	{
		ret_val = 1;
	}

	return(ret_val);
}

