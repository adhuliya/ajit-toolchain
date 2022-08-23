#include <stdlib.h>
#include <stdint.h>
#include <cortos.h>
#include <ajit_access_routines.h>
#include <ajit_mmap.h>

#define NPAGES 8
PageTableAllocator pta;
uint32_t page_table_array [16 * 1024];

void startup_init()
{
}

int main(void) {


	// first find the context table pointer...
	uint32_t c_ptr   = __ajit_load_word_mmu_reg__ ( MMU_REG_CONTEXT_TABLE_PTR );
	uint32_t context = __ajit_load_word_mmu_reg__ ( MMU_REG_CONTEXT );
	cortos_printf ("context = 0x%x, context_table_pointer = 0x%x.\n", context, c_ptr);

	uint64_t c_ptr_pa = (((uint64_t) c_ptr) >> 2) << 6;
	cortos_printf ("context_table_pointer_pa = 0x%x.\n", (uint32_t) c_ptr_pa);

	uint32_t va;
	uint32_t P;
	uint8_t  level;
	uint64_t pa, ptde_a;
	uint32_t ptde;
	for(P = 0; P < NPAGES; P++)
	{	
		va = 0x40000000 + (P*4096);
		int status = ajit_lookup_mmap (c_ptr_pa, context, va, 
				&level, &pa, &ptde_a, &ptde);

		if (!status)
			cortos_printf("Translated VA 0x%x -> PA 0x%x level=%d\n", va, (uint32_t) pa, level);
		else
			cortos_printf("Error: translation of VA 0x%x failed.\n", va);
	}

	// Lets map some pages..
	uint64_t npa = ((uint64_t) &(page_table_array[0]));
	initPageTableAllocator(&pta, npa, 16*1024);

	// Now mmap level 3 pages..
	for(P = 0; P < NPAGES; P++)
	{
		va = 0x80000000 + (P*4096);
		pa = 0x90000000 + (P*4096);
		int status = ajit_mmap_operation(&pta, 
				npa,  
				ADD_TO_MMAP_OP, 
				1,
				3, 	
				3,
				va,
				pa);
		if(!status)
			cortos_printf("In npa, mapped 0x%x -> 0x%x level %d entry.\n", va, (uint32_t) pa, 3);
		else
			cortos_printf("Error: In npa, failed to mmap 0x%x -> 0x%x level %d entry.\n", va, pa, 3);
	}



	// Now mmap level 2 pages 256KB.
	for(P = 0; P < NPAGES; P++)
	{
		va = 0xa0000000 + (P*64*4096);
		pa = 0xb0000000 + (P*64*4096);
		int status = ajit_mmap_operation(&pta, 
				npa,  
				ADD_TO_MMAP_OP, 
				1,
				2, 	
				3,
				va,
				pa);
		if(!status)
			cortos_printf("In npa, mapped 0x%x -> 0x%x level %d entry.\n", va, (uint32_t) pa, 2);
		else
			cortos_printf("Error: In npa, failed to mmap 0x%x -> 0x%x level %d entry.\n", va, pa, 2);
	}

	// Now mmap level 1 pages 16MB.
	for(P = 0; P < NPAGES; P++)
	{
		va = 0xc0000000 + (P*4096*4096);
		pa = 0xd0000000 + (P*4096*4096);
		int status = ajit_mmap_operation(&pta, 
				npa,  
				ADD_TO_MMAP_OP, 
				1,
				1, 	
				3,
				va,
				pa);
		if(!status)
			cortos_printf("In npa, mapped 0x%x -> 0x%x level %d entry.\n", va, (uint32_t) pa, 1);
		else
			cortos_printf("Error: In npa, failed to mmap 0x%x -> 0x%x level %d entry.\n", va, pa, 1);
	}


	// lookup what you have mapped level 3
	for(P = 0; P < NPAGES; P++)
	{
		va = 0x80000000 + (P*4096);
		int status = ajit_lookup_mmap (npa, 1, va, 
				&level, &pa, &ptde_a, &ptde);

		if (!status)
			cortos_printf("In npa,  translated VA 0x%x -> PA 0x%x level=%d\n", 
					va, (uint32_t) pa, level);
		else
			cortos_printf("Error: In npa, translation  of VA 0x%x failed.\n", va);
	}

	// lookup what you have mapped level 2
	for(P = 0; P < NPAGES; P++)
	{
		va = 0xa0000000 + (P*64*4096);
		int status = ajit_lookup_mmap (npa, 1, va, 
				&level, &pa, &ptde_a, &ptde);

		if (!status)
			cortos_printf("In npa,  translated VA 0x%x -> PA 0x%x level=%d\n", 
					va, (uint32_t) pa, level);
		else
			cortos_printf("Error: In npa, translation  of VA 0x%x failed.\n", va);
	}


	// lookup what you have mapped level 1
	for(P = 0; P < NPAGES; P++)
	{
		va = 0xc0000000 + (P*4096*4096);
		int status = ajit_lookup_mmap (npa, 1, va, 
				&level, &pa, &ptde_a, &ptde);

		if (!status)
			cortos_printf("In npa,  translated VA 0x%x -> PA 0x%x level=%d\n", 
					va, (uint32_t) pa, level);
		else
			cortos_printf("Error: In npa, translation  of VA 0x%x failed.\n", va);
	}

	// try the failed cases of translation.
	va = 0x80000000 + (NPAGES*4096);
	int status = ajit_lookup_mmap (npa, 1, va, &level, &pa, &ptde_a, &ptde);
	if(status)
		cortos_printf("In npa, translation  of VA 0x%x failed.\n", va);
	else
		cortos_printf("Error: In npa,  translated VA 0x%x -> PA 0x%x level=%d\n", 
				va, (uint32_t) pa, level);

	{
		va = 0xa0000000 + (NPAGES*64*4096);
		int status = ajit_lookup_mmap (npa, 1, va, &level, &pa, &ptde_a, &ptde);
		if(status)
			cortos_printf("In npa, translation  of VA 0x%x failed.\n", va);
		else
			cortos_printf("Error: In npa,  translated VA 0x%x -> PA 0x%x level=%d\n", 
					va, (uint32_t) pa, level);
	}

	{
		va = 0xc0000000 + (P*4096*4096);
		int status = ajit_lookup_mmap (npa, 1, va, &level, &pa, &ptde_a, &ptde);
		if(status)
			cortos_printf("In npa, translation  of VA 0x%x failed.\n", va);
		else
			cortos_printf("Error: In npa,  translated VA 0x%x -> PA 0x%x level=%d\n", 
					va, (uint32_t) pa, level);
	}

}

