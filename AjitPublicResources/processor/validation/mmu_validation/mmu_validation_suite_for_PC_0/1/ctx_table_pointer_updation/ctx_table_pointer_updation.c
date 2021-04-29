//Test to check if ctx_table_pointer register gets updated correctly.
//The Mmu must flush the TLB automatically whenever it detects a write
//to context table ptr register.
//
//
//SCHEME:
//	In this test, we set up two sets of page tables.
//	In the first set, addr 0x10000000 is mapped to 0xA0000000.
//
//	In the second set of tables, we map
//	VA 0x10000000 to PA 0xB0000000.
//
//	Then, during runtime, while the MMU is enabled,
//	we change the ctx table ptr register to point to the 
//	second set of tables.
//	This should result in the second mapping being used
//	immediately.
//
// Author: Neha Karanjkar


#include<stdint.h>
#include"mmu_access_routines.h"

//Page tables
uint32_t ContextTable[256]  	__attribute__((aligned(0x1000)));
uint32_t L1PageTable[256] 	__attribute__((aligned(0x1000)));
uint32_t L2PageTable[64]  	__attribute__((aligned(0x1000)));
uint32_t L3PageTable[64]  	__attribute__((aligned(0x1000)));

	
void setupPageTables()
{
	//Map all instruction-area and stack such that VA=PA, with full permissions
	//map VA=0x10000000 to PA=0xA0000000.
	
	//context table pointer register
	uint32_t context_table_ptr_value = convertPhyAddrToPTD((uint32_t)ContextTable);
	store_word_mmureg(context_table_ptr_value, (uint32_t*)MMU_REG_CONTEXT_TABLE_PTR);
	
	//Context table:
	ContextTable[0] = convertPhyAddrToPTD(((uint32_t)L1PageTable));

	//Create L1 page table entries
	//such that physical address = virtual address.
	//for all addresses except 0xA0000000-0xA1000000.
	uint32_t i;
	for(i=0x00;i<=0xFF;i++)
	{
		if(i!=0x10)
		{
			L1PageTable[i] = (i<<20) | (0x8E);//all can read/write/execute this page
		}
		if(i==0x10)
		{
			//map 0x10000000 to 0xA0000000
			L1PageTable[i] = (0xA0<<20) | (0x8E);//all can read/write/execute this page
		}
	}

};

//Alternate page tables
uint32_t ContextTable_2[256]  	__attribute__((aligned(0x1000)));
uint32_t L1PageTable_2[256] 	__attribute__((aligned(0x1000)));
uint32_t L2PageTable_2[64]  	__attribute__((aligned(0x1000)));
uint32_t L3PageTable_2[64]  	__attribute__((aligned(0x1000)));

	
void setupPageTables2()
{
	//Map all instruction-area and stack such that VA=PA, with full permissions
	//map VA=0x10000000 to PA=0xB0000000.
	
	//Context table:
	ContextTable_2[0] = convertPhyAddrToPTD(((uint32_t)L1PageTable_2));

	//Create L1 page table entries
	//such that physical address = virtual address.
	//for all addresses except 0xA0000000-0xA1000000.
	uint32_t i;
	for(i=0x00;i<=0xFF;i++)
	{
		if(i!=0x10)
		{
			L1PageTable_2[i] = (i<<20) | (0x8E);//all can read/write/execute this page
		}
		if(i==0x10)
		{
			//map 0x10000000 to 0xB0000000
			L1PageTable_2[i] = (0xB0<<20) | (0x8E);//all can read/write/execute this page
		}
	}

};

//Change the mapping by chaning ctx table ptr
inline void changeCtxTablePointer()
{
	//context table pointer register
	uint32_t context_table_ptr_value = convertPhyAddrToPTD((uint32_t)ContextTable_2);
	store_word_mmureg(context_table_ptr_value, (uint32_t*)MMU_REG_CONTEXT_TABLE_PTR);
};

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

	//initialize registers in other windows
	int window=0;
	for(window=0;window<7;window++)
	{
	__asm__ __volatile__( "save\n\t "); 
	
	__asm__ __volatile__( "mov %g0, %l0 \n\t "); __asm__ __volatile__( "mov %g0, %l1 \n\t ");
	__asm__ __volatile__( "mov %g0, %l2 \n\t "); __asm__ __volatile__( "mov %g0, %l3 \n\t ");
	__asm__ __volatile__( "mov %g0, %l4 \n\t "); __asm__ __volatile__( "mov %g0, %l5 \n\t ");
	__asm__ __volatile__( "mov %g0, %l6 \n\t "); __asm__ __volatile__( "mov %g0, %l7 \n\t ");
	
	__asm__ __volatile__( "mov %g0, %o0 \n\t "); __asm__ __volatile__( "mov %g0, %o1 \n\t ");
	__asm__ __volatile__( "mov %g0, %o2 \n\t "); __asm__ __volatile__( "mov %g0, %o3 \n\t ");
	__asm__ __volatile__( "mov %g0, %o4 \n\t "); __asm__ __volatile__( "mov %g0, %o5 \n\t ");
	__asm__ __volatile__( "mov %g0, %o6 \n\t "); __asm__ __volatile__( "mov %g0, %o7 \n\t ");
	
	}
	
	for(window=0;window<7;window++)
	{
	__asm__ __volatile__( "restore\n\t "); 
	}

	startTest();
	return 0;

}


int  __attribute__((section(".text.main"))) startTest()
{

	// Initialize PSR, enable traps.
	// set PSR with ET=1 PS=1 S=1, all other fields=0 
	__asm__ __volatile__( "mov 0xC7, %l0"); 
	__asm__ __volatile__("wr %l0, %psr");

	//insert nops because wrpsr, wrtbr etc can be delayed 
	__asm__ __volatile__( "nop\n\t	nop\n\t nop \n\t "); 
	//insert nops because wrpsr, wrtbr etc can be delayed 
	__asm__ __volatile__( "nop\n\t	nop\n\t nop \n\t "); 

	
	//set up page tables
	setupPageTables();	
	setupPageTables2();	

	//write a character in memory using physical addresses
	uint32_t* ptr;
	ptr=(uint32_t *)0x10000000; *ptr = 0x101010;
	ptr=(uint32_t *)0xA0000000; *ptr = 0xA0A0A0;
	ptr=(uint32_t *)0xB0000000; *ptr = 0xB0B0B0;
		
	

	//Now enable the MMU, setting NF=0 
	uint32_t MMU_control_word = 0x1; //Enable=1, NF (no fault)=0
	store_word_mmureg(MMU_control_word, (uint32_t*) MMU_REG_CONTROL);

	//checkpoint
	__asm__ __volatile__( "set 0xCC1, %g3");
	

	//[VA= 0x10000000] should be = '0xA0A0A0'
	__asm__ __volatile__( "set 0x10000000, %l6");
	__asm__ __volatile__( "ld [%l6], %g6  ");

	//now change the ctx table ptr
	changeCtxTablePointer();

	//[VA= 0x10000000] should be = '0xB0B0B0'
	__asm__ __volatile__( "set 0x10000000, %l6");
	__asm__ __volatile__( "ld [%l6], %g7  ");


	//Read FSR and FAR registers
	//Checks for these values are present in the vprj file.
	
	__asm__ __volatile__( "set 0xCC2, %g3"); //checkpoint

	//This point should not be reached...
	//halt
	__asm__ __volatile__("ta 0; nop; nop;");
	return 0;

}

