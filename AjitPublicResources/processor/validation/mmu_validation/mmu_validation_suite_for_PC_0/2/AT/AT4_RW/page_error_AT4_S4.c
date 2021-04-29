/*----------------------------------------------------------------------------
Filename:			page_error_AT4_S4.c
Version:			1.00
Goal: 				Fault Type=2 for Acess Type=4 and PTE.ACC=4
Author:				Harshal Kalyane
Description:	
1.	Initially mmu is disabled, and VA=PA.
2.	Setup a context table, and page tables 
	such that all virtual addresses in the range
	0xD000 0000 to 0xFFFF FFFF are mapped such that VA=PA.

	In addition, map a single 4KB page as follows :

	For context 0:
	virtual address			phy address
	0x10000000 - 0x10001000 	0xA0000000-0xA00001000 with PTE.ACC=4

3.	Write a 0x12 using physical address(0xA0000000)
3. 	Initial context table ptr, context register, and enable MMU.
4.	MOV 0x3 to %g6
5.	In context 0 write data(%g6) using virtual addr(0x10000000) from user mode.
6.	Check memory content of 0XA0000000 (.vprj)
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
	uint32_t process1_PTE = ((0xA0<<12)<<8) | 0x92 ;//PTE.ACC=4
	uint32_t process2_PTE = ((0xA0<<12)<<8) | 0x8E ;//0x9E or 0x9A 0r 0x 92
	process1_L3PageTable[0x00] = process1_PTE;
	process2_L3PageTable[0x00] = process2_PTE;

//------------------------------------------------------------------------------------------------------------------
	 uint32_t *j=(uint32_t*) 0xA0000000; //store it at A000 0000 address.
	*j=12;
	 


	//======================================Test for AT=4,S=4==========================================================
	// //--------------------------------------MMU Enabled------------------------------------------------------------
	uint32_t MMU_control_word = 0x1; //set the Enable bit
	store_word_mmureg(0x0 , (uint32_t*) MMU_REG_CONTEXT);
	__asm__ __volatile__( "mov 0x1, %g6 \n\t ");//check point
	store_word_mmureg(MMU_control_word, (uint32_t*) MMU_REG_CONTROL);
	__asm__ __volatile__( "mov 0x2, %g6 \n\t ");
	//--------------------------------------------------------------------------------------------------------------

	//----------------------------------Go to user mode-------------------------------------------------------------
	__asm__ __volatile__( "mov %psr, %l0 \n\t "); //clear P=0 bit of PSR
	__asm__ __volatile__("set 0xFFFFFF7F, %l3 \n\t");//store 32 bit mask in %l3
	__asm__ __volatile__("and %l0, %l3, %l0");//clear P(7th bit) using Mask
	__asm__ __volatile__("mov %l0, %psr");//load it in PSR
	//-----------------------------*******In Context[0] or process_1*******-----------------------------------------

	__asm__ (".align 4096");
	__asm__ __volatile__("set 0x10000000, %l4 ");
	__asm__ __volatile__( "mov 0x3, %g6  ");
	__asm__ __volatile__("st %g6 , [%l4] " );
	__asm__ __volatile__("ld [%l4] ,%g7 " );
	__asm__ __volatile__( "mov 0x4, %g6  ");

//-----------------------------------------------END----------------------------------------------------------------
	//halt();
	__asm__ __volatile__("ta 5; nop; nop;");
	return 0;

}


