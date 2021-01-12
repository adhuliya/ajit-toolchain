// Basic test for address translation
// Author: Neha Karanjkar
//
//Scheme:
//1.	Initially mmu is disabled, and VA=PA.
//2.	Setup a context table, and page tables 
//	such that all virtual addresses in the range
//	0xc000 0000 to 0xFFFF FFFF are mapped such that VA=PA.
//
//	In addition, map a single 4KB page as follows :
//
//	For context 0:
//	virtual address			phy address
//	0x10000000 - 0x10001000 	0xA0000000-0xA00001000
//
//
//3. 	Initial context table ptr, context register, and enable MMU.
//4.	In context 0, write a magic string using physical address, read using virtual addr.
//	check that the string is the same.
//=============================================================



#include<stdint.h>


//Mmu asi constants
#define ASI_MMU_REGISTER 		0x04
#define ASI_MMU_FLUSH_PROBE	 	0x03
#define ASI_FLUSH_I_D_CONTEXT		0x13

//#define ASI_MMU_BYPASS		0x2f
//Addresses of MMU registers
#define MMU_REG_CONTROL			0x00000000
#define MMU_REG_CONTEXT_TABLE_PTR	0x00000100
#define MMU_REG_CONTEXT			0x00000200
#define MMU_REG_FSR			0x00000300
#define MMU_REG_FAR			0x00000400



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

inline void halt()
{
	__asm__ __volatile__( "nop; ta 0; nop; nop; \n\t "); 
}


//correct termination
inline void correct_termination(void)
{
	__asm__ __volatile__("mov %0, %%g1\n\t" : :
			     "i"(0xF00) : );
	halt();
}

//wrong termination
inline void wrong_termination(void)
{
	__asm__ __volatile__("mov %0, %%g1\n\t" : :
			     "i"(0xBAD) : );
	halt();
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



//Context table
uint32_t ContextTable[256]  __attribute__((aligned(0x1000)));
//Page tables for process 1:
uint32_t process0_L1PageTable[256] __attribute__((aligned(0x1000)));
uint32_t process0_L2PageTable[64]  __attribute__((aligned(0x1000)));
uint32_t process0_L3PageTable[64]  __attribute__((aligned(0x1000)));
//Page tables for process 2:
uint32_t process1_L1PageTable[256] __attribute__((aligned(0x1000)));
uint32_t process1_L2PageTable[64]  __attribute__((aligned(0x1000)));
uint32_t process1_L3PageTable[64]  __attribute__((aligned(0x1000)));


void strcpy(char dest[],char const src[]) 
{int i;
 for (i = 0; src[i] != 0; i++)  dest[i] = src[i];
}


//returns 1 if src and dest are the same.
//Else returns 0.
int str_equal(char const src[],char const dest[]) 
{
	int i;
	if(dest[0] != src[0]) return 0;
	for (i = 0; (src[i] != 0 && dest[i]!=0); i++)
	{
		if(dest[i] != src[i]) return 0;
	}
	return 1;
}



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


uint32_t convertPhyAddrToPTD(uint64_t phy_addr)
{
	//Get bits 35:6 from phy addr and place them into bits 31:2 of PTD
	uint32_t PTD = 0;
	PTD= setSlice32(PTD, 31,2, getSlice64(phy_addr,35,6));

	//Mark bits1:0 = 0x1 to denote that its a PTD
	PTD= setSlice32(PTD, 1,0, 0x1);
	return PTD;
}



//NOTE : with function main() use the
//attribute "((section(".text.main")))"
//to ensure that main() is  put in the
//beginning of the ".text" section in the 
//generated executable.
int  startTest();
int  __attribute__((section(".text.main")))  main()
{
	//Initialize all registers
	__asm__ __volatile__( "mov %g0, %g1 \n\t "); __asm__ __volatile__( "mov %g0, %g2 \n\t ");
	__asm__ __volatile__( "mov %g0, %g3 \n\t "); __asm__ __volatile__( "mov %g0, %g4 \n\t ");
	__asm__ __volatile__( "mov %g0, %g5 \n\t "); __asm__ __volatile__( "mov %g0, %g6 \n\t ");
	__asm__ __volatile__( "mov %g0, %g7 \n\t ");
	
	__asm__ __volatile__( "mov %g0, %i0 \n\t "); __asm__ __volatile__( "mov %g0, %i1 \n\t ");
	__asm__ __volatile__( "mov %g0, %i2 \n\t "); __asm__ __volatile__( "mov %g0, %i3 \n\t ");
	__asm__ __volatile__( "mov %g0, %i4 \n\t "); __asm__ __volatile__( "mov %g0, %i5 \n\t ");
	__asm__ __volatile__( "mov %g0, %i6 \n\t "); __asm__ __volatile__( "mov %g0, %i7 \n\t ");
	
	__asm__ __volatile__( "mov %g0, %l0 \n\t "); __asm__ __volatile__( "mov %g0, %l1 \n\t ");
	__asm__ __volatile__( "mov %g0, %l2 \n\t "); __asm__ __volatile__( "mov %g0, %l3 \n\t ");
	__asm__ __volatile__( "mov %g0, %l4 \n\t "); __asm__ __volatile__( "mov %g0, %l5 \n\t ");
	__asm__ __volatile__( "mov %g0, %l6 \n\t "); __asm__ __volatile__( "mov %g0, %l7 \n\t ");
	
	__asm__ __volatile__( "mov %g0, %o0 \n\t "); __asm__ __volatile__( "mov %g0, %o1 \n\t ");
	__asm__ __volatile__( "mov %g0, %o2 \n\t "); __asm__ __volatile__( "mov %g0, %o3 \n\t ");
	__asm__ __volatile__( "mov %g0, %o4 \n\t "); __asm__ __volatile__( "mov %g0, %o5 \n\t ");
	__asm__ __volatile__( "mov %g0, %o6 \n\t "); __asm__ __volatile__( "mov %g0, %o7 \n\t ");

	startTest();
	return 0;

}


int  __attribute__((section(".text.main"))) startTest()
{
	
	uint32_t i;
	
	
	//Currently MMU is disabled and translation hasn't kicked in

	//==========================
	//Set up page tables
	//==========================
	
	//set context table pointer
	uint32_t context_table_ptr_value = convertPhyAddrToPTD((uint32_t)ContextTable);
	store_word_mmureg(context_table_ptr_value, (uint32_t*)MMU_REG_CONTEXT_TABLE_PTR);

	//Populate entries in the context table
	//set first two entries to a PTD
	ContextTable[0] = convertPhyAddrToPTD(((uint32_t)process0_L1PageTable));
	ContextTable[1] = convertPhyAddrToPTD(((uint32_t)process1_L1PageTable));

	//Populate L1 page tables
	//map all addresses in range 0xC0000000-0xFFFFFFFF
	//such that VA=PA
	for(i=0x00; i<=0xFF; i++) //change by harshal 7/09/2016 0xC0 to 0x00
	{
		//PTE feilds :
		// C M R ACC ET
		// 1 0 0 011 10 = 0x8E
		uint32_t PPN = (i<<12);
		uint32_t PTE_level1 = (PPN<<8) | (0x8E);
		process0_L1PageTable[i] = PTE_level1;
		process1_L1PageTable[i] = PTE_level1;
	}
	
	//Place page table descriptors for 
	//address range 0x1000 0000 to 0x1100 0000
	process0_L1PageTable[0x10] = convertPhyAddrToPTD((uint32_t)process0_L2PageTable);
	process1_L1PageTable[0x10] = convertPhyAddrToPTD((uint32_t)process1_L2PageTable);

	
	//Populate L2 page tables
	//Place page table descriptors for 
	//address range 0x1000 0000 to 0x1100 0000
	process0_L2PageTable[0x00] = convertPhyAddrToPTD((uint32_t)process0_L3PageTable);
	process1_L2PageTable[0x00] = convertPhyAddrToPTD((uint32_t)process1_L3PageTable);
	
	//Populate L3 page tables
	//Place page table entries for 
	//address range 0x1000 0000 to 0x1100 0000
	uint32_t process0_PTE = ((0xA0<<12)<<8) | 0x8E ;
	uint32_t process1_PTE = ((0xB0<<12)<<8) | 0x8E ;
	process0_L3PageTable[0x00] = process0_PTE;
	process1_L3PageTable[0x00] = process1_PTE;


	//===================================================
	//write two test strings in memory using physical addr
	char* write_string = (char*)0xA0000000;
	strcpy(write_string, "AA\n\0");
	
	write_string = (char*)0xB0000000;
	strcpy(write_string, "BB\n\0");
	
	//Also write a string to phy add 10000000.
	//If this string is read, that means VA to PA translation
	//isn't happening at all.
	write_string = (char*)0x10000000;
	strcpy(write_string, "XX\n\0");


	
	//There. all translation info has been given to the MMU.
	//Now enable the MMU by writing into MMU control register
	uint32_t MMU_control_word = 0x1; //set the Enable bit
	store_word_mmureg(0x0 , (uint32_t*) MMU_REG_CONTEXT);
	store_word_mmureg(MMU_control_word, (uint32_t*) MMU_REG_CONTROL);

	
	
	// Check that basic address translation works 
	//read the string using virtual address.
	//If the string prints fine, the translation is working

	char* read_string = (char*)0x10000000;
	if (! str_equal("AA\n\0",read_string) ) wrong_termination();

	//now switch context 
	context_switch(1);
	//read the string using virtual address.
	//If the string prints fine, the translation is working
	read_string = (char*)0x10000000;
	if (! str_equal("BB\n\0",read_string) ) wrong_termination();

	//now switch context back
	context_switch(0);
	//read the string using virtual address.
	//If the string prints fine, the translation is working
	read_string = (char*)0x10000000;
	if (! str_equal("AA\n\0",read_string) ) wrong_termination();

	correct_termination();

	halt();
	return 0;
}


