/*----------------------------------------------------------------------------
Filename:			page_error_AT4_Valid_1.c
Version:			1.00
Goal: 				Fault Type=1 for Acess Type=4 and PTE.V=0
Author:				Harshal Kalyane
Description:	
1.	Initially mmu is disabled, and VA=PA.
2.	Setup a context table, and page tables 
	such that all virtual addresses in the range
	0xD000 0000 to 0xFFFF FFFF are mapped such that VA=PA.

	In addition, map a single 4KB page as follows :

	For context 0:
	virtual address			phy address
	0x10000000 - 0x10001000 	0xA0000000-0xA00001000 with PTE.ACC=3

3.	Write a 0x12 using physical address(0xA0000000)
3. 	Initial context table ptr, context register, and enable MMU.
4.	MOV 0x3 to %g6
5.	In context 0 write data(%g6) using virtual addr(0x20000000) from user mode.
-----------------------------------------------------------------------------*/



#include<stdint.h>


//Mmu asi constants
#define ASI_MMU_REGISTER 		0x04
#define ASI_MMU_FLUSH_PROBE	 	0x03
#define ASI_FLUSH_I_D_CONTEXT	0x13
#define ASI_SUP_INST			0x09

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


//context switch.
//make a switch to a particular context
inline void context_switch(uint32_t context_number)
{
	//flush dcache
	//putString("\nflush dcache");
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_FLUSH_I_D_CONTEXT) : "memory");
	//flush icache
	//putString("\nflush icache");
	__asm__ __volatile__(" flush ");
	//flush TLB
	//putString("\nflush TLB");
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t"  : : "i"(ASI_MMU_FLUSH_PROBE) : "memory");

	//write new context number into mmu context register
	//putString("\nnew context number");
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(context_number), "r"(MMU_REG_CONTEXT),
			     "i"(ASI_MMU_REGISTER) : "memory");

	//putString("\nflush dcache");
	//flush dcache
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_FLUSH_I_D_CONTEXT) : "memory");
	//flush icache
	//putString("\nflush icache");
	__asm__ __volatile__(" flush ");
	//flush TLB
	//putString("\nflush TLB");
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t"  : : "i"(ASI_MMU_FLUSH_PROBE) : "memory");


}



//Context table
uint32_t ContextTable[256]  __attribute__((aligned(0x1000)));
//Page tables for process 1:
uint32_t process1_L1PageTable[256] __attribute__((aligned(0x1000)));
uint32_t process1_L2PageTable[64]  __attribute__((aligned(0x1000)));
uint32_t process1_L3PageTable[64]  __attribute__((aligned(0x1000)));
//Page tables for process 2:
uint32_t process2_L1PageTable[256] __attribute__((aligned(0x1000)));
uint32_t process2_L2PageTable[64]  __attribute__((aligned(0x1000)));
uint32_t process2_L3PageTable[64]  __attribute__((aligned(0x1000)));



inline void strcpy(char dest[],char const src[]) 
{int i;
 for (i = 0; src[i] != 0; i++)  dest[i] = src[i];
}


inline uint64_t getSlice64(uint64_t reg, uint8_t h, uint8_t l)
{
	reg = reg << (63 - h);
	reg = reg >> ((63 - h) + l);
	return reg;
}

	
inline uint32_t setSlice32(uint32_t reg, uint8_t h, uint8_t l, uint32_t value)
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


inline uint32_t convertPhyAddrToPTD(uint64_t phy_addr)
{
	//Get bits 35:6 from phy addr and place them into bits 31:2 of PTD
	uint32_t PTD = 0;
	PTD= setSlice32(PTD, 31,2, getSlice64(phy_addr,35,6));

	//Mark bits1:0 = 0x1 to denote that its a PTD
	PTD= setSlice32(PTD, 1,0, 0x1);
	return PTD;
}

void sotore_mmu_FR(void)
{
		uint32_t *FSR = (uint32_t*)0XF0000000;
		*FSR = load_word_mmureg((uint32_t*)MMU_REG_FSR);
		uint32_t *FAR = (uint32_t*)0XF0000010;
		*FAR = load_word_mmureg((uint32_t*)MMU_REG_FAR);
	__asm__ __volatile__("ta 7; nop; nop;");
}
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


int  startTest()
{
	// __asm__ __volatile__( "mov 0xE0, %l0 \n\t "); //80 only supervisor and no traps. //E0 only supervisor and traps.
	// __asm__ __volatile__("wr %l0, %psr \n\t nop\n\t");
	// // 	! insert nops here because\n\t 
	// __asm__ __volatile__( "	nop\n\t nop \n\t ");
	// // //!store base of trap table in TBR register
	// __asm__ __volatile__("set	HW_trap_0x00, %l0");
	// __asm__ __volatile__("wr %l0, 0x0, %tbr");
	// __asm__ __volatile__("nop; nop; nop;");	//! insert nops here because. ! writes to tbr may be delayed

//========================================MMU Verifiaction=============================================
//--------------------------------setting page table---------------------------------------------------
	uint32_t i;		
	//Currently MMU is disabled and translation hasn't kicked in
	//putString("\n---- Mmu disabled -----");

	//set context table pointer
	uint32_t context_table_ptr_value = convertPhyAddrToPTD((uint32_t)ContextTable);//It will point to the context tablein physical memory.
	store_word_mmureg(context_table_ptr_value, (uint32_t*)MMU_REG_CONTEXT_TABLE_PTR);
	

	//Populate entries in the context table
	//Mark all entries in the context table invalid.
	for(i=0;i<256;i++)ContextTable[i]=0;
	//set first two entries to a PTD
	ContextTable[0] = convertPhyAddrToPTD(((uint32_t)process1_L1PageTable));
	ContextTable[1] = convertPhyAddrToPTD(((uint32_t)process2_L1PageTable));

	
	//=========================
	//Populate L1 page tables
	//=========================
	//First, mark all entries as invalid
	for(i=0;i<256;i++) 
	{
		process1_L1PageTable[i] =0x00;
		process2_L1PageTable[i] =0x00;

	}
	//next map all addresses in range 0xC0000000-0xFFFFFFFF
	//such that VA=PA
	for(i=0x00; i<=0x10; i++)
	{
	//PTE feilds : USER ASI:(Instruction=0x8,Data=0xA) SUPER ASI:(Instruction=0x9,Data=0xB)
	// C M R ACC ET
	// 1 0 0 000 10 = 0x82 user:Read_only Super:Read_only.
	// 1 0 0 001 10 = 0x86 user:Read_only/Write Super:Read_only/Write.
	// 1 0 0 010 10 = 0x8A user:Read_only/Execute Super:Read_only/Execute.
	// 1 0 0 011 10 = 0x8E user:Read_only/Write/Execute Super:Read_only/Write/Execute.
	// 1 0 0 100 10 = 0x92 user:Execute_only Super:Execute_only.
	// 1 0 0 101 10 = 0x96 user:Read_only Super:Read/Write.
	// 1 0 0 110 10 = 0x9A user:No Acess. Super:Read/Execute.
	// 1 0 0 111 10 = 0x9E user:No Acess. Super:Read/Write/Execute.
		uint32_t PPN = (i<<12);
		uint32_t PTE_level1 = (PPN<<8) | (0x8E);//In this any one can read/write/ execute
		uint32_t PTE_level2 = (PPN<<8) | (0x8E);//In this contex only supervisor can execute

		process1_L1PageTable[i] = PTE_level1;
		process2_L1PageTable[i] = PTE_level2;

	}
	//Place page table descriptors for 
	//address range 0x1000 0000 to 0x1100 0000
	process1_L1PageTable[0x10] = convertPhyAddrToPTD((uint32_t)process1_L2PageTable);
	process2_L1PageTable[0x10] = convertPhyAddrToPTD((uint32_t)process2_L2PageTable);

	
	//=========================
	//Populate L2 page tables
	//=========================
	//First, mark all entries as invalid
	for(i=0;i<64;i++) 
	{
		process1_L2PageTable[i] =0x00;
		process2_L2PageTable[i] =0x00;

	}
	
	//Place page table descriptors for 
	//address range 0x1000 0000 to 0x1000 1000
	process1_L2PageTable[0x00] = convertPhyAddrToPTD((uint32_t)process1_L3PageTable);
	process2_L2PageTable[0x00] = convertPhyAddrToPTD((uint32_t)process2_L3PageTable);

	//=========================
	//Populate L3 page tables
	//=========================
	//First, mark all entries as invalid
	for(i=0;i<64;i++) 
	{
		process1_L3PageTable[i] =0x00;
		process2_L3PageTable[i] =0x00;
	
	}
	//Place page table entries for 
	//address range 0x1000 0000 to 0x1000 1000
	//PTE feilds : USER ASI:(Instruction=0x8,Data=0xA) SUPER ASI:(Instruction=0x9,Data=0xB)
	// C M R ACC ET
	// 1 0 0 000 10 = 0x82 user:Read_only Super:Read_only.
	// 1 0 0 001 10 = 0x86 user:Read_only/Write Super:Read_only/Write.
	// 1 0 0 010 10 = 0x8A user:Read_only/Execute Super:Read_only/Execute.
	// 1 0 0 011 10 = 0x8E user:Read_only/Write/Execute Super:Read_only/Write/Execute.
	// 1 0 0 100 10 = 0x92 user:Execute_only Super:Execute_only.
	// 1 0 0 101 10 = 0x96 user:Read_only Super:Read/Write.
	// 1 0 0 110 10 = 0x9A user:No Acess. Super:Read/Execute.
	// 1 0 0 111 10 = 0x9E user:No Acess. Super:Read/Write/Execute.
	uint32_t process1_PTE = ((0xA0<<12)<<8) | 0x82 ;//0x8E
	uint32_t process2_PTE = ((0xA0<<12)<<8) | 0x8E ;//0x9E or 0x9A 0r 0x 92
	process1_L3PageTable[0x00] = process1_PTE;
	process2_L3PageTable[0x00] = process2_PTE;

//------------------------------------------------------------------------------------------------------------------
	 uint32_t *j=(uint32_t*) 0xA0000000; //store it at A000 0000 address.
	*j=12;
	 


	//======================================Test for AT=4,S=0==========================================================
	// //--------------------------------------MMU Enabled------------------------------------------------------------
	uint32_t MMU_control_word = 0x1; //set the Enable bit
	store_word_mmureg(0x0 , (uint32_t*) MMU_REG_CONTEXT);
	__asm__ __volatile__( "mov 0x1, %g6 \n\t ");//check point
	store_word_mmureg(MMU_control_word, (uint32_t*) MMU_REG_CONTROL);
	__asm__ __volatile__( "mov 0x2, %g6 \n\t ");
	//--------------------------------------------------------------------------------------------------------------
	// uint32_t control_word = load_word_mmureg((uint32_t*)MMU_REG_CONTROL);
	// //the control word with 0x02 to set no-fault bit;
	// control_word = control_word | 0x02;
	// //write the updated control word to mmu.
	// store_word_mmureg(control_word, ((uint32_t*)MMU_REG_CONTROL));

	//----------------------------------Go to user mode-------------------------------------------------------------
	__asm__ __volatile__( "mov %psr, %l0 \n\t "); //clear P=0 bit of PSR
	__asm__ __volatile__("set 0xFFFFFF7F, %l3 \n\t");//store 32 bit mask in %l3
	__asm__ __volatile__("and %l0, %l3, %l0");//clear P(7th bit) using Mask
	__asm__ __volatile__("mov %l0, %psr");//load it in PSR
	//-----------------------------*******In Context[0] or process_1*******-----------------------------------------

	__asm__ (".align 4096");
	__asm__ __volatile__("set 0x20000000, %l4 ");
	__asm__ __volatile__( "mov 0x3, %g6  ");
	__asm__ __volatile__("st %g6 , [%l4] " );
	__asm__ __volatile__( "mov 0x4, %g6  ");

//-----------------------------------------------END----------------------------------------------------------------
	//halt();
	__asm__ __volatile__("ta 5; nop; nop;");
	return 0;

}


__asm__ (".align 4096; HW_trap_0x00: mov 0xf0, %g5; restore; ta 0; nop;\
HW_trap_0x01: mov 0x01, %g5; restore; ta 0; nop;\
HW_trap_0x02: mov 0x02, %g5; restore; ta 0; nop;\
HW_trap_0x03: mov 0x03, %g5; restore; ta 0; nop;\
HW_trap_0x04: mov 0x04, %g5; restore; ta 0; nop;\
HW_trap_0x05: mov 0x05, %g5; restore; ta 0; nop;\
HW_trap_0x06: mov 0x06, %g5; restore; ta 0; nop;\
HW_trap_0x07: mov 0x07, %g5; restore; ta 0; nop;\
HW_trap_0x08: mov 0x08, %g5; restore; ta 0; nop;\
HW_trap_0x09: mov 0x09, %g5; call sotore_mmu_FR; nop; nop;\
HW_trap_0x0a: mov 0x0a, %g5; restore; ta 0; nop;\
HW_trap_0x0b: mov 0x0b, %g5; restore; ta 0; nop;\
HW_trap_0x0c: mov 0x0c, %g5; restore; ta 0; nop;\
HW_trap_0x0d: mov 0x0d, %g5; restore; ta 0; nop;\
HW_trap_0x0e: mov 0x0e, %g5; restore; ta 0; nop;\
HW_trap_0x0f: mov 0x0f, %g5; restore; ta 0; nop;\
HW_trap_0x10: mov 0x10, %g5; restore; ta 0; nop;\
HW_trap_0x11: mov 0x11, %g5; restore; ta 0; nop;\
HW_trap_0x12: mov 0x12, %g5; restore; ta 0; nop;\
HW_trap_0x13: mov 0x13, %g5; restore; ta 0; nop;\
HW_trap_0x14: mov 0x14, %g5; restore; ta 0; nop;\
HW_trap_0x15: mov 0x15, %g5; restore; ta 0; nop;\
HW_trap_0x16: mov 0x16, %g5; restore; ta 0; nop;\
HW_trap_0x17: mov 0x17, %g5; restore; ta 0; nop;\
HW_trap_0x18: mov 0x18, %g5; restore; ta 0; nop;\
HW_trap_0x19: mov 0x19, %g5; restore; ta 0; nop;\
HW_trap_0x1a: mov 0x1a, %g5; restore; ta 0; nop;\
HW_trap_0x1b: mov 0x1b, %g5; restore; ta 0; nop;\
HW_trap_0x1c: mov 0x1c, %g5; restore; ta 0; nop;\
HW_trap_0x1d: mov 0x1d, %g5; restore; ta 0; nop;\
HW_trap_0x1e: mov 0x1e, %g5; restore; ta 0; nop;\
HW_trap_0x1f: mov 0x1f, %g5; restore; ta 0; nop;\
HW_trap_0x20: mov 0x20, %g5; restore; ta 0; nop;\
HW_trap_0x21: mov 0x21, %g5; restore; ta 0; nop;\
HW_trap_0x22: mov 0x22, %g5; restore; ta 0; nop;\
HW_trap_0x23: mov 0x23, %g5; restore; ta 0; nop;\
HW_trap_0x24: mov 0x24, %g5; restore; ta 0; nop;\
HW_trap_0x25: mov 0x25, %g5; restore; ta 0; nop;\
HW_trap_0x26: mov 0x26, %g5; restore; ta 0; nop;\
HW_trap_0x27: mov 0x27, %g5; restore; ta 0; nop;\
HW_trap_0x28: mov 0x28, %g5; restore; ta 0; nop;\
HW_trap_0x29: mov 0x29, %g5; restore; ta 0; nop;\
HW_trap_0x2a: mov 0x2a, %g5; restore; ta 0; nop;\
HW_trap_0x2b: mov 0x2b, %g5; restore; ta 0; nop;\
HW_trap_0x2c: mov 0x2c, %g5; restore; ta 0; nop;\
HW_trap_0x2d: mov 0x2d, %g5; restore; ta 0; nop;\
HW_trap_0x2e: mov 0x2e, %g5; restore; ta 0; nop;\
HW_trap_0x2f: mov 0x2f, %g5; restore; ta 0; nop;\
HW_trap_0x30: mov 0x30, %g5; restore; ta 0; nop;\
HW_trap_0x31: mov 0x31, %g5; restore; ta 0; nop;\
HW_trap_0x32: mov 0x32, %g5; restore; ta 0; nop;\
HW_trap_0x33: mov 0x33, %g5; restore; ta 0; nop;\
HW_trap_0x34: mov 0x34, %g5; restore; ta 0; nop;\
HW_trap_0x35: mov 0x35, %g5; restore; ta 0; nop;\
HW_trap_0x36: mov 0x36, %g5; restore; ta 0; nop;\
HW_trap_0x37: mov 0x37, %g5; restore; ta 0; nop;\
HW_trap_0x38: mov 0x38, %g5; restore; ta 0; nop;\
HW_trap_0x39: mov 0x39, %g5; restore; ta 0; nop;\
HW_trap_0x3a: mov 0x3a, %g5; restore; ta 0; nop;\
HW_trap_0x3b: mov 0x3b, %g5; restore; ta 0; nop;\
HW_trap_0x3c: mov 0x3c, %g5; restore; ta 0; nop;\
HW_trap_0x3d: mov 0x3d, %g5; restore; ta 0; nop;\
HW_trap_0x3e: mov 0x3e, %g5; restore; ta 0; nop;\
HW_trap_0x3f: mov 0x3f, %g5; restore; ta 0; nop;\
HW_trap_0x40: mov 0x40, %g5; restore; ta 0; nop;\
HW_trap_0x41: mov 0x41, %g5; restore; ta 0; nop;\
HW_trap_0x42: mov 0x42, %g5; restore; ta 0; nop;\
HW_trap_0x43: mov 0x43, %g5; restore; ta 0; nop;\
HW_trap_0x44: mov 0x44, %g5; restore; ta 0; nop;\
HW_trap_0x45: mov 0x45, %g5; restore; ta 0; nop;\
HW_trap_0x46: mov 0x46, %g5; restore; ta 0; nop;\
HW_trap_0x47: mov 0x47, %g5; restore; ta 0; nop;\
HW_trap_0x48: mov 0x48, %g5; restore; ta 0; nop;\
HW_trap_0x49: mov 0x49, %g5; restore; ta 0; nop;\
HW_trap_0x4a: mov 0x4a, %g5; restore; ta 0; nop;\
HW_trap_0x4b: mov 0x4b, %g5; restore; ta 0; nop;\
HW_trap_0x4c: mov 0x4c, %g5; restore; ta 0; nop;\
HW_trap_0x4d: mov 0x4d, %g5; restore; ta 0; nop;\
HW_trap_0x4e: mov 0x4e, %g5; restore; ta 0; nop;\
HW_trap_0x4f: mov 0x4f, %g5; restore; ta 0; nop;\
HW_trap_0x50: mov 0x50, %g5; restore; ta 0; nop;\
HW_trap_0x51: mov 0x51, %g5; restore; ta 0; nop;\
HW_trap_0x52: mov 0x52, %g5; restore; ta 0; nop;\
HW_trap_0x53: mov 0x53, %g5; restore; ta 0; nop;\
HW_trap_0x54: mov 0x54, %g5; restore; ta 0; nop;\
HW_trap_0x55: mov 0x55, %g5; restore; ta 0; nop;\
HW_trap_0x56: mov 0x56, %g5; restore; ta 0; nop;\
HW_trap_0x57: mov 0x57, %g5; restore; ta 0; nop;\
HW_trap_0x58: mov 0x58, %g5; restore; ta 0; nop;\
HW_trap_0x59: mov 0x59, %g5; restore; ta 0; nop;\
HW_trap_0x5a: mov 0x5a, %g5; restore; ta 0; nop;\
HW_trap_0x5b: mov 0x5b, %g5; restore; ta 0; nop;\
HW_trap_0x5c: mov 0x5c, %g5; restore; ta 0; nop;\
HW_trap_0x5d: mov 0x5d, %g5; restore; ta 0; nop;\
HW_trap_0x5e: mov 0x5e, %g5; restore; ta 0; nop;\
HW_trap_0x5f: mov 0x5f, %g5; restore; ta 0; nop;\
HW_trap_0x60: mov 0x60, %g5; restore; ta 0; nop;\
HW_trap_0x61: mov 0x61, %g5; restore; ta 0; nop;\
HW_trap_0x62: mov 0x62, %g5; restore; ta 0; nop;\
HW_trap_0x63: mov 0x63, %g5; restore; ta 0; nop;\
HW_trap_0x64: mov 0x64, %g5; restore; ta 0; nop;\
HW_trap_0x65: mov 0x65, %g5; restore; ta 0; nop;\
HW_trap_0x66: mov 0x66, %g5; restore; ta 0; nop;\
HW_trap_0x67: mov 0x67, %g5; restore; ta 0; nop;\
HW_trap_0x68: mov 0x68, %g5; restore; ta 0; nop;\
HW_trap_0x69: mov 0x69, %g5; restore; ta 0; nop;\
HW_trap_0x6a: mov 0x6a, %g5; restore; ta 0; nop;\
HW_trap_0x6b: mov 0x6b, %g5; restore; ta 0; nop;\
HW_trap_0x6c: mov 0x6c, %g5; restore; ta 0; nop;\
HW_trap_0x6d: mov 0x6d, %g5; restore; ta 0; nop;\
HW_trap_0x6e: mov 0x6e, %g5; restore; ta 0; nop;\
HW_trap_0x6f: mov 0x6f, %g5; restore; ta 0; nop;\
HW_trap_0x70: mov 0x70, %g5; restore; ta 0; nop;\
HW_trap_0x71: mov 0x71, %g5; restore; ta 0; nop;\
HW_trap_0x72: mov 0x72, %g5; restore; ta 0; nop;\
HW_trap_0x73: mov 0x73, %g5; restore; ta 0; nop;\
HW_trap_0x74: mov 0x74, %g5; restore; ta 0; nop;\
HW_trap_0x75: mov 0x75, %g5; restore; ta 0; nop;\
HW_trap_0x76: mov 0x76, %g5; restore; ta 0; nop;\
HW_trap_0x77: mov 0x77, %g5; restore; ta 0; nop;\
HW_trap_0x78: mov 0x78, %g5; restore; ta 0; nop;\
HW_trap_0x79: mov 0x79, %g5; restore; ta 0; nop;\
HW_trap_0x7a: mov 0x7a, %g5; restore; ta 0; nop;\
HW_trap_0x7b: mov 0x7b, %g5; restore; ta 0; nop;\
HW_trap_0x7c: mov 0x7c, %g5; restore; ta 0; nop;\
HW_trap_0x7d: mov 0x7d, %g5; restore; ta 0; nop;\
HW_trap_0x7e: mov 0x7e, %g5; restore; ta 0; nop;\
HW_trap_0x7f: mov 0x7f, %g5; restore; ta 0; nop;\
\
SW_trap_0x80: mov 0x80, %g5; restore; ta 0; nop;\
SW_trap_0x81: mov 0x81, %g5; restore; ta 0; nop;\
SW_trap_0x82: mov 0x82, %g5; restore; ta 0; nop;\
SW_trap_0x83: mov 0x83, %g5; restore; ta 0; nop;\
SW_trap_0x84: mov 0x84, %g5; restore; ta 0; nop;\
SW_trap_0x85: mov 0x85, %g5; nop; ta 0; nop;\
SW_trap_0x86: mov 0x86, %g5; restore; ta 0; nop;\
SW_trap_0x87: mov 0x87, %g5; restore; ta 0; nop;\
SW_trap_0x88: mov 0x88, %g5; restore; ta 0; nop;\
SW_trap_0x89: mov 0x89, %g5; restore; ta 0; nop;\
SW_trap_0x8a: mov 0x8a, %g5; restore; ta 0; nop;\
SW_trap_0x8b: mov 0x8b, %g5; restore; ta 0; nop;\
SW_trap_0x8c: mov 0x8c, %g5; restore; ta 0; nop;\
SW_trap_0x8d: mov 0x8d, %g5; restore; ta 0; nop;\
SW_trap_0x8e: mov 0x8e, %g5; restore; ta 0; nop;\
SW_trap_0x8f: mov 0x8f, %g5; restore; ta 0; nop;\
SW_trap_0x90: mov 0x90, %g5; restore; ta 0; nop;\
SW_trap_0x91: mov 0x91, %g5; restore; ta 0; nop;\
SW_trap_0x92: mov 0x92, %g5; restore; ta 0; nop;\
SW_trap_0x93: mov 0x93, %g5; restore; ta 0; nop;\
SW_trap_0x94: mov 0x94, %g5; restore; ta 0; nop;\
SW_trap_0x95: mov 0x95, %g5; restore; ta 0; nop;\
SW_trap_0x96: mov 0x96, %g5; restore; ta 0; nop;\
SW_trap_0x97: mov 0x97, %g5; restore; ta 0; nop;\
SW_trap_0x98: mov 0x98, %g5; restore; ta 0; nop;\
SW_trap_0x99: mov 0x99, %g5; restore; ta 0; nop;\
SW_trap_0x9a: mov 0x9a, %g5; restore; ta 0; nop;\
SW_trap_0x9b: mov 0x9b, %g5; restore; ta 0; nop;\
SW_trap_0x9c: mov 0x9c, %g5; restore; ta 0; nop;\
SW_trap_0x9d: mov 0x9d, %g5; restore; ta 0; nop;\
SW_trap_0x9e: mov 0x9e, %g5; restore; ta 0; nop;\
SW_trap_0x9f: mov 0x9f, %g5; restore; ta 0; nop;\
SW_trap_0xa0: mov 0xa0, %g5; restore; ta 0; nop;\
SW_trap_0xa1: mov 0xa1, %g5; restore; ta 0; nop;\
SW_trap_0xa2: mov 0xa2, %g5; restore; ta 0; nop;\
SW_trap_0xa3: mov 0xa3, %g5; restore; ta 0; nop;\
SW_trap_0xa4: mov 0xa4, %g5; restore; ta 0; nop;\
SW_trap_0xa5: mov 0xa5, %g5; restore; ta 0; nop;\
SW_trap_0xa6: mov 0xa6, %g5; restore; ta 0; nop;\
SW_trap_0xa7: mov 0xa7, %g5; restore; ta 0; nop;\
SW_trap_0xa8: mov 0xa8, %g5; restore; ta 0; nop;\
SW_trap_0xa9: mov 0xa9, %g5; restore; ta 0; nop;\
SW_trap_0xaa: mov 0xaa, %g5; restore; ta 0; nop;\
SW_trap_0xab: mov 0xab, %g5; restore; ta 0; nop;\
SW_trap_0xac: mov 0xac, %g5; restore; ta 0; nop;\
SW_trap_0xad: mov 0xad, %g5; restore; ta 0; nop;\
SW_trap_0xae: mov 0xae, %g5; restore; ta 0; nop;\
SW_trap_0xaf: mov 0xaf, %g5; restore; ta 0; nop;\
SW_trap_0xb0: mov 0xb0, %g5; restore; ta 0; nop;\
SW_trap_0xb1: mov 0xb1, %g5; restore; ta 0; nop;\
SW_trap_0xb2: mov 0xb2, %g5; restore; ta 0; nop;\
SW_trap_0xb3: mov 0xb3, %g5; restore; ta 0; nop;\
SW_trap_0xb4: mov 0xb4, %g5; restore; ta 0; nop;\
SW_trap_0xb5: mov 0xb5, %g5; restore; ta 0; nop;\
SW_trap_0xb6: mov 0xb6, %g5; restore; ta 0; nop;\
SW_trap_0xb7: mov 0xb7, %g5; restore; ta 0; nop;\
SW_trap_0xb8: mov 0xb8, %g5; restore; ta 0; nop;\
SW_trap_0xb9: mov 0xb9, %g5; restore; ta 0; nop;\
SW_trap_0xba: mov 0xba, %g5; restore; ta 0; nop;\
SW_trap_0xbb: mov 0xbb, %g5; restore; ta 0; nop;\
SW_trap_0xbc: mov 0xbc, %g5; restore; ta 0; nop;\
SW_trap_0xbd: mov 0xbd, %g5; restore; ta 0; nop;\
SW_trap_0xbe: mov 0xbe, %g5; restore; ta 0; nop;\
SW_trap_0xbf: mov 0xbf, %g5; restore; ta 0; nop;\
SW_trap_0xc0: mov 0xc0, %g5; restore; ta 0; nop;\
SW_trap_0xc1: mov 0xc1, %g5; restore; ta 0; nop;\
SW_trap_0xc2: mov 0xc2, %g5; restore; ta 0; nop;\
SW_trap_0xc3: mov 0xc3, %g5; restore; ta 0; nop;\
SW_trap_0xc4: mov 0xc4, %g5; restore; ta 0; nop;\
SW_trap_0xc5: mov 0xc5, %g5; restore; ta 0; nop;\
SW_trap_0xc6: mov 0xc6, %g5; restore; ta 0; nop;\
SW_trap_0xc7: mov 0xc7, %g5; restore; ta 0; nop;\
SW_trap_0xc8: mov 0xc8, %g5; restore; ta 0; nop;\
SW_trap_0xc9: mov 0xc9, %g5; restore; ta 0; nop;\
SW_trap_0xca: mov 0xca, %g5; restore; ta 0; nop;\
SW_trap_0xcb: mov 0xcb, %g5; restore; ta 0; nop;\
SW_trap_0xcc: mov 0xcc, %g5; restore; ta 0; nop;\
SW_trap_0xcd: mov 0xcd, %g5; restore; ta 0; nop;\
SW_trap_0xce: mov 0xce, %g5; restore; ta 0; nop;\
SW_trap_0xcf: mov 0xcf, %g5; restore; ta 0; nop;\
SW_trap_0xd0: mov 0xd0, %g5; restore; ta 0; nop;\
SW_trap_0xd1: mov 0xd1, %g5; restore; ta 0; nop;\
SW_trap_0xd2: mov 0xd2, %g5; restore; ta 0; nop;\
SW_trap_0xd3: mov 0xd3, %g5; restore; ta 0; nop;\
SW_trap_0xd4: mov 0xd4, %g5; restore; ta 0; nop;\
SW_trap_0xd5: mov 0xd5, %g5; restore; ta 0; nop;\
SW_trap_0xd6: mov 0xd6, %g5; restore; ta 0; nop;\
SW_trap_0xd7: mov 0xd7, %g5; restore; ta 0; nop;\
SW_trap_0xd8: mov 0xd8, %g5; restore; ta 0; nop;\
SW_trap_0xd9: mov 0xd9, %g5; restore; ta 0; nop;\
SW_trap_0xda: mov 0xda, %g5; restore; ta 0; nop;\
SW_trap_0xdb: mov 0xdb, %g5; restore; ta 0; nop;\
SW_trap_0xdc: mov 0xdc, %g5; restore; ta 0; nop;\
SW_trap_0xdd: mov 0xdd, %g5; restore; ta 0; nop;\
SW_trap_0xde: mov 0xde, %g5; restore; ta 0; nop;\
SW_trap_0xdf: mov 0xdf, %g5; restore; ta 0; nop;\
SW_trap_0xe0: mov 0xe0, %g5; restore; ta 0; nop;\
SW_trap_0xe1: mov 0xe1, %g5; restore; ta 0; nop;\
SW_trap_0xe2: mov 0xe2, %g5; restore; ta 0; nop;\
SW_trap_0xe3: mov 0xe3, %g5; restore; ta 0; nop;\
SW_trap_0xe4: mov 0xe4, %g5; restore; ta 0; nop;\
SW_trap_0xe5: mov 0xe5, %g5; restore; ta 0; nop;\
SW_trap_0xe6: mov 0xe6, %g5; restore; ta 0; nop;\
SW_trap_0xe7: mov 0xe7, %g5; restore; ta 0; nop;\
SW_trap_0xe8: mov 0xe8, %g5; restore; ta 0; nop;\
SW_trap_0xe9: mov 0xe9, %g5; restore; ta 0; nop;\
SW_trap_0xea: mov 0xea, %g5; restore; ta 0; nop;\
SW_trap_0xeb: mov 0xeb, %g5; restore; ta 0; nop;\
SW_trap_0xec: mov 0xec, %g5; restore; ta 0; nop;\
SW_trap_0xed: mov 0xed, %g5; restore; ta 0; nop;\
SW_trap_0xee: mov 0xee, %g5; restore; ta 0; nop;\
SW_trap_0xef: mov 0xef, %g5; restore; ta 0; nop;\
SW_trap_0xf0: mov 0xf0, %g5; restore; ta 0; nop;\
SW_trap_0xf1: mov 0xf1, %g5; restore; ta 0; nop;\
SW_trap_0xf2: mov 0xf2, %g5; restore; ta 0; nop;\
SW_trap_0xf3: mov 0xf3, %g5; restore; ta 0; nop;\
SW_trap_0xf4: mov 0xf4, %g5; restore; ta 0; nop;\
SW_trap_0xf5: mov 0xf5, %g5; restore; ta 0; nop;\
SW_trap_0xf6: mov 0xf6, %g5; restore; ta 0; nop;\
SW_trap_0xf7: mov 0xf7, %g5; restore; ta 0; nop;\
SW_trap_0xf8: mov 0xf8, %g5; restore; ta 0; nop;\
SW_trap_0xf9: mov 0xf9, %g5; restore; ta 0; nop;\
SW_trap_0xfa: mov 0xfa, %g5; restore; ta 0; nop;\
SW_trap_0xfb: mov 0xfb, %g5; restore; ta 0; nop;\
SW_trap_0xfc: mov 0xfc, %g5; restore; ta 0; nop;\
SW_trap_0xfd: mov 0xfd, %g5; restore; ta 0; nop;\
SW_trap_0xfe: mov 0xfe, %g5; restore; ta 0; nop;");
