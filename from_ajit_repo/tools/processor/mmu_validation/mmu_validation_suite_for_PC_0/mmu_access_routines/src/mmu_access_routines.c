// Routines for reading/writing to mmu registers
// Author: Neha Karanjkar


#include"mmu_access_routines.h"

//store word into mmu register
inline void store_word_mmureg(uint32_t value, uint32_t* addr)
{
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
			     "i"(ASI_MMU_REGISTER) : "memory");
}

//load word from mmu register
inline uint32_t load_word_mmureg(uint32_t* addr)
{
        uint32_t retval;
        __asm__ __volatile__("lda [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(addr), "i"(ASI_MMU_REGISTER));
        return retval;
}

//Mmu flush
inline void mmu_flush(uint32_t value, uint32_t* addr)
{
	__asm__ __volatile__("sta %0, [%1] %2\n\t"  : : "r"(value), "r"(addr), "i"(ASI_MMU_FLUSH_PROBE) : "memory");
}

//Mmu probe
inline uint32_t mmu_probe(uint32_t* addr)
{
        uint32_t retval;
        __asm__ __volatile__("lda [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(addr), "i"(ASI_MMU_FLUSH_PROBE));
        return retval;
}

//flush icache
inline void flush_icache(void)
{
	__asm__ __volatile__(" flush ");
}

//flush_dcache
inline void flush_dcache(void)
{
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_FLUSH_I_D_CONTEXT) : "memory");
}


//context switch.
//make a switch to a particular context
inline void context_switch(uint32_t context_number)
{
	
	//Copy context number into register
	__asm__ __volatile__("mov %0, %%l0\n\t" : : "r"(context_number):"memory");

	
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_FLUSH_I_D_CONTEXT) : "memory");
	//flush icache
	__asm__ __volatile__(" flush ");
	//flush TLB
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t"  : : "i"(ASI_MMU_FLUSH_PROBE) : "memory");

	//write new context number into mmu context register
	__asm__ __volatile__("sta %%l0, [%0] %1\n\t" : : "r"(MMU_REG_CONTEXT),
			     "i"(ASI_MMU_REGISTER) : "memory");
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_FLUSH_I_D_CONTEXT) : "memory");
	//flush icache
	__asm__ __volatile__(" flush ");
	//flush TLB
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t"  : : "i"(ASI_MMU_FLUSH_PROBE) : "memory");


}

//Routines required by convertPhyAddrToPTD

uint64_t getSlice64(uint64_t reg, uint8_t h, uint8_t l)
{
	reg = reg << (63 - h);
	reg = reg >> ((63 - h) + l);
	return reg;
}

	
uint32_t setSlice32(uint32_t reg, uint8_t h, uint8_t l, uint32_t value)
{
	uint32_t mask = -1;
	mask = mask >> (31 - h + l);
	value = value & mask;
	value = value << l;

	mask = mask << l;
	reg = reg & ~mask;
	reg = reg | value;
	return reg;
}


//convert a physical address to a page table descriptor
uint32_t convertPhyAddrToPTD(uint64_t phy_addr)
{
	//Get bits 35:6 from phy addr and place them into bits 31:2 of PTD
	uint32_t PTD = 0;
	PTD= setSlice32(PTD, 31,2, getSlice64(phy_addr,35,6));

	//Mark bits1:0 = 0x1 to denote that its a PTD
	PTD= setSlice32(PTD, 1,0, 0x1);
	return PTD;
}


