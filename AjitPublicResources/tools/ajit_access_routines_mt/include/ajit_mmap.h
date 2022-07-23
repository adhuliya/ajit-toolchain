#ifndef ajit_mmap_h___
#define ajit_mmap_h___

///////////////////////////////////////////////////////////////////////////////////
// utilities for managing page tables.
//   Based on the page table specification in the SPARC V8 SRMMU.
//   Note: not been sufficiently tested!!
///////////////////////////////////////////////////////////////////////////////////

#define ADD_TO_MMAP_OP 		1
#define DELETE_FROM_MMAP_OP 	2

#define ERR_NO_ROOM_IN_ALLOCATOR   1
#define ERR_LOOKUP_FAILED	   2


typedef struct __PageTableAllocator {
	uint64_t base_physical_address;
	uint64_t allocated_size;
	uint64_t free_pointer;

} PageTableAllocator;
void initPageTableAllocator (PageTableAllocator* pta, uint64_t base_addr, uint32_t allocated_size);
//
// returns a 0 on success...
//
uint32_t  allocatePageTableBlock (PageTableAllocator* pts, uint8_t level, uint64_t* block_base_address);


// Given page table level, return the index into the table.
uint32_t ajit_mmap_index_in_table(uint8_t level, uint32_t va);

// return 1 if the entry is a PTE else 0.
uint8_t ajit_mmap_is_pte(uint32_t entry);

// return 1 if the entry is a PTD else 0.
uint8_t ajit_mmap_is_ptd(uint32_t entry);

// From the PTD at the indicated level, with the specified index into the table
// at that level, calculate and return the physical address from which the page table walk 
// should continue.
uint64_t ajit_mmap_get_phy_addr_from_ptd(uint32_t ptd, uint8_t level, uint32_t index);

// From the PTE at the indicated level, with the specified index,
// calculate and return the translated physical address for the virtual address va.
uint64_t ajit_mmap_get_phy_addr_from_pte(uint32_t ptd, uint8_t level, uint32_t va);

// Make and return a PTD using the specified pa as the address to which the PTD should point.
uint32_t ajit_mmap_make_ptd(uint8_t level, uint64_t pa);

// Make and return a PTE using the specified va and translated pa
uint32_t ajit_mmap_make_pte(uint8_t level, uint8_t acc, uint32_t va, uint64_t pa);

//
// Lookup a translation in the page table starting at the
// indicated page_table_base_phy_addr.
//
// Input arguments:
//   context, virtual address (va).
//
// Output arguments:
//   *level  contains the level at which the search ended.
//   *pa     translated physical address if found.
//   *pdte_a address ofpage table descriptor/entry at which search ended.
//   *pdte   page table descriptor/entry at which search ended.
// 
//
// return 
//        1 if no matching pte found
//        0 if matching pte found.
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
	uint32_t* ptde);

// Add/delete a page table entry.  
//
// Input arguments:
//   base address of page table, ADD/DELETE, context, insertion level
//   
// return 
//        0 if operation successful
//        non-zero otherwise.
//
// NOTE:  This function must be called in conjunction
// with ajit_lookup_mmap.  For example, to add a page
// translation at level 3, you would do:
//
// while (1) {
//   int f3 = ajit_lookup_mmap (...., *level, *pdte_a, *pdte)
//   if (!f3) {
//       if(*level == 3) 
//           break;
//       else
//           allocate_table_at_level(*level....)
//   }
// }
//
// ajit_mmap_operation (....);
//
// 
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
	);

#endif
