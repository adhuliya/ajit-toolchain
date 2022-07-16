#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"
#include "ajit_mmap.h"
#ifdef CORTOS2
#include <cortos.h>
#endif

void initPageTableAllocator (PageTableAllocator* pts, uint64_t base_addr, uint32_t allocated_size)
// allocated size and base-addr must be aligned to word boundary..
{
	uint64_t I;

	// initialize to 0.
	for(I = 0; I < allocated_size; I += 4)
	{
		__ajit_store_word_to_physical_address__(0x0, (uint64_t) (base_addr + I));
	}	

	pts->base_physical_address = base_addr;
	pts->allocated_size = allocated_size;
	pts->free_pointer = 0;
}

//
// returns a 0 on success...
uint32_t  allocatePageTableBlock (PageTableAllocator* pts, uint8_t level, uint64_t* block_base_address)
{
	uint32_t ret_val = 1;
	uint64_t request_size = 0;
	if(level <= 1)
		request_size = 256  * 4;	
	else
		request_size = 64 * 4;

	uint64_t next_free_pointer = pts->free_pointer + request_size;
	if(next_free_pointer <= (pts->base_physical_address + request_size))
	{
		*block_base_address = pts->free_pointer; 
		pts->free_pointer = next_free_pointer;
		ret_val = 0;
	}
	return(ret_val);
}

// level is 1/2/3.
uint32_t ajit_mmap_index_into_table(uint8_t level, uint32_t va)
{
	uint32_t ret_val = 0;
	switch(level)
	{
		case 1: 
			ret_val = (va >> 24) & 0xff;	 // [31:24]
			break;
		case 2:
			ret_val = (va >> 18) & 0x3f;	 // [23:18]
			break;
		case 3: 
			ret_val = (va >> 12) & 0x3f;	 // [17:12]
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
	uint32_t pte = (((uint32_t) ppn_64) << 8) | (((uint32_t) acc) << 2) | 0x2;
	return(pte);
}
					
				
//
// return 
//        0 if matching pte found
//        1 if no matching pte found.
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
	int ret_val = 1;
	*level  = 0;
	*pa     = 0;
	*ptde_a = 0;
	*ptde   = 0;
#ifdef CORTOS2
	CORTOS_DEBUG ("ajit_lookup_mmap called with va = 0x%x, context-table-ptr=0x%x.\n",
				va, (uint32_t) page_table_base_phy_addr);
#endif

	uint64_t context_table_base_address  = page_table_base_phy_addr;
	uint8_t  current_level = 0;
	uint32_t index_into_table =
			((current_level == 0) ? context : 
					ajit_mmap_index_into_table(current_level, va));
	uint64_t current_entry_address  = context_table_base_address + (4*index_into_table);

	while(1)	
	{
		uint32_t current_entry = 
			__ajit_load_word_from_physical_address__((uint64_t) current_entry_address);


#ifdef CORTOS2
		CORTOS_DEBUG ("ajit_lookup_mmap at level=%d, read 0x%x from address 0x%x.\n",
					current_level, current_entry, (uint32_t) current_entry_address);
#endif
		*level 	   = current_level;
		*ptde_a    = current_entry_address;
		*ptde      = current_entry;

		// is it a PTD?
		if(ajit_mmap_is_ptd (current_entry))
		{
			// index into table... used to get the location of the next entry..
			index_into_table = ajit_mmap_index_into_table(current_level + 1, va);
#ifdef CORTOS2
		CORTOS_DEBUG ("ajit_lookup_mmap index into table at level=%d is = 0x%x.\n",
					current_level+1, index_into_table);
#endif

			// Yes, it is a PTD.  Calculate the physical
			// address of the next entry.
			current_entry_address = 
				ajit_mmap_get_phy_addr_from_ptd(current_entry, current_level, index_into_table);

		}
		else if(ajit_mmap_is_pte(current_entry))
		{
			// A PTE.  record the hit info and return.
			*pa    = ajit_mmap_get_phy_addr_from_pte(current_entry, current_level, va);
#ifdef CORTOS2
			CORTOS_DEBUG("ajit_lookup_mmap: successfully found pte 0x%x at level %d, pa=0x%x\n", 
							current_entry, 
							current_level,
							(uint32_t) *pa);
#endif
			ret_val = 0;
			break;
		}
		else
			break;

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
//
// return 0 on success, 1 on failure..
//
int ajit_mmap_operation 
	(	
		PageTableAllocator* pts, 
		// base address of page table
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
		uint64_t pa
	)
{

#ifdef CORTOS2
	CORTOS_DEBUG("ajit_mmap_operation: inargs level = %d, va = 0x%x.\n", level, va);
#endif

	int ret_val = 0;

	uint8_t  pdte_level;
	uint32_t pdte;
	uint64_t pdte_a;
	uint64_t ign_pa;
	int status = ajit_lookup_mmap(page_table_base_phy_address,
							context, va,
							&pdte_level,
							&ign_pa,
							&pdte_a,
							&pdte);
	cortos_printf("ajit_mmap_operation: lookup-status = %d, pdte_level = %d\n", status, pdte_level);
	if(status == 0)
	{
		if(operation == ADD_TO_MMAP_OP)
		{
			pdte = ajit_mmap_make_pte(level, acc, va, pa);
		}
		else if(operation == DELETE_FROM_MMAP_OP)
		{
			pdte = 0x0;
		}
			
		__ajit_store_word_to_physical_address__(pdte, pdte_a);

	}	
	else if(operation == ADD_TO_MMAP_OP)
	{
		// OK.  At this point, our search has run cold at pdte_level 
		//      This means that at pdte_level, the address pdte_a 
		//      is pointing to 0x0 and not to a valid pdte/pte.
		//
		//  So: we allocate a block for level = pdte_level + 1,
		//      and create a ptd/pte entry which is written into
		//      *(pdte_a).
		//
		// 
		uint8_t  current_level = pdte_level;
		uint64_t current_pdte_a = pdte_a;
		while (current_level <= level)
		{
#ifdef CORTOS2
			CORTOS_DEBUG("ajit_mmap_operation: current_level=%d, current_pdte_a = 0x%x.\n",
						current_level, (uint32_t) current_pdte_a);
#endif
			uint64_t allocated_block_address;
			uint32_t alloc_status = allocatePageTableBlock(pts, current_level + 1, 
										&allocated_block_address);
			if(alloc_status != 0)
				return(ERR_NO_ROOM_IN_ALLOCATOR);
				
			uint32_t new_ptde;
			if(current_level == level) 
			{
				pdte = ajit_mmap_make_pte(level, acc, va, pa);
			}
			else
			{
			  	pdte = ajit_mmap_make_ptd(current_level, allocated_block_address);
			}
			__ajit_store_word_to_physical_address__(pdte, (uint64_t) current_pdte_a);

#ifdef CORTOS2
			CORTOS_DEBUG("ajit_mmap_operation: at level %d,  wrote pdte=0x%x, to address = 0x%x.\n",
						current_level, pdte, (uint32_t) current_pdte_a);
#endif
			uint32_t index_into_table = ajit_mmap_index_into_table(current_level + 1, va);
			current_pdte_a = allocated_block_address + (4*index_into_table);
			current_level++;
		}
		
	}
	else
	{
		ret_val = 0;
	}

	return(ret_val);
}

