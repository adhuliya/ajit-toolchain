//mmu_probe.c
//
//Check mmu_probe asi.
//AUTHOR: Neha Karanjkar
//17 nov 2016

//The test simply performs an mmu mapping,
//	map VA=0x10000000-0x10ffffff ---> PA=0xA0000000-0xA0ffffff. 
//
//And then does a probe, to check if we get the correct PTE value


#include<stdint.h>
#include"mmu_access_routines.h"
//Page tables
uint32_t ContextTable[256]  		__attribute__((aligned(0x1000)));
uint32_t process1_L1PageTable[256] 	__attribute__((aligned(0x1000)));
uint32_t process1_L2PageTable[64]  	__attribute__((aligned(0x1000)));
uint32_t process1_L3PageTable[64]  	__attribute__((aligned(0x1000)));

	
void setupPageTables()
{
	
	//context table pointer register
	uint32_t context_table_ptr_value = convertPhyAddrToPTD((uint32_t)ContextTable);
	store_word_mmureg(context_table_ptr_value, (uint32_t*)MMU_REG_CONTEXT_TABLE_PTR);
	
	//Context table:
	ContextTable[0] = convertPhyAddrToPTD(((uint32_t)process1_L1PageTable));

	//Create L1 page table entries
	//Map all instruction-area such that VA=PA, with full permissions
	uint32_t i;
	for(i=0x00;i<=0x0F;i++)
	{
		uint32_t PPN = (i<<12);
		uint32_t PTE_level1 = (PPN<<8) | (0x8E);//all can read/write/execute this page
		process1_L1PageTable[i] = PTE_level1;
	}
	//Stack area:
	for(i=0xFE;i<=0xFF;i++)
	{
		uint32_t PPN = (i<<12);
		uint32_t PTE_level1 = (PPN<<8) | (0x8E);//all can read/write/execute this page
		process1_L1PageTable[i] = PTE_level1;
	}

	//Map VA range 0x10000000 to 0x10ffffff to PA 0xA0000000-0xA0ffffff
	{
		uint32_t PTE_level1 = (0xA0<<20) | (0x8E);//all can read/write/execute this page
		process1_L1PageTable[0x10] = PTE_level1;
	}
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

int  __attribute__((section(".text.main")))  startTest()
{


	// Initialize PSR, enable traps.
	// set PSR with ET=1 PS=1 S=1, all other fields=0
	//
	// PSR Bit positions
	// S PS ET CWP
	// 7 6   5  4:0
	__asm__ __volatile__( "mov 0xE0, %l0"); 
	__asm__ __volatile__("wr %l0, %psr");
	//insert nops because wrpsr, wrtbr etc can be delayed 
	__asm__ __volatile__( "nop\n\t	nop\n\t nop \n\t "); 
	//store base of trap table in TBR register
	__asm__ __volatile__("set HW_trap_0x00, %l0");
	__asm__ __volatile__("wr %l0, 0x0, %tbr");
	//insert nops because wrpsr, wrtbr etc can be delayed 
	__asm__ __volatile__( "nop\n\t	nop\n\t nop \n\t "); 

	
	//set up page tables
	setupPageTables();	
	
	//checkpoint
	__asm__ __volatile__( "set 0xCC1, %g3");
	
	
	//write a test data in memory using physical addr
	uint32_t *ptr_A=(uint32_t*) 0xA0000000; 
	uint32_t *ptr_VA=(uint32_t*) 0x10000000; 
	*ptr_A = 0xA0A0A0A0;
	*ptr_VA= 0x10101010;

	//Now enable the MMU
	uint32_t MMU_control_word = 0x1; //Enable=1
	store_word_mmureg(MMU_control_word, (uint32_t*) MMU_REG_CONTROL);

	//read the data using virtual address.
	__asm__ __volatile__("set 0x10000000, %l3 \n\t");
	__asm__ __volatile__("ld  [%l3], %g4");  //g4 should be 0xA0A0A0A0

	
	//now perform a probe and check if we get the expected PTE
	uint32_t probe_value = mmu_probe((uint32_t*)( 0x10000000 | 0x400));
	//write the probe value in  register g6
	__asm__ __volatile__("mov %0, %%g6\n\t" : :"r"(probe_value));


	//halt
	__asm__ __volatile__("ta 0; nop; nop;");
	return 0;

}

//ILLEGAL instr trap is HW trap 0.2
//The Trap Table.
//It Should aligned to page-size(4096 Bytes)
__asm__ (".align 4096; \
HW_trap_0x00: mov 0xFF, %g5; restore; ta 0; nop;\
HW_trap_0x01: mov 0x01, %g5; ta 0; nop; nop; \
HW_trap_0x02: mov 0x02, %g5; ta 0; nop; nop; \
HW_trap_0x03: mov 0x03, %g5; restore; ta 0; nop;\
HW_trap_0x04: mov 0x04, %g5; restore; ta 0; nop;\
HW_trap_0x05: mov 0x05, %g5; restore; ta 0; nop;\
HW_trap_0x06: mov 0x06, %g5; restore; ta 0; nop;\
HW_trap_0x07: mov 0x07, %g5; restore; ta 0; nop;\
HW_trap_0x08: mov 0x08, %g5; restore; ta 0; nop;\
HW_trap_0x09: mov 0x09, %g5; restore; ta 0; nop;\
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
SW_trap_0x80: mov 0x80, %g5; restore; ta 0; nop;\
SW_trap_0x81: mov 0x81, %g5; restore; ta 0; nop;\
SW_trap_0x82: mov 0x82, %g5; restore; ta 0; nop;\
SW_trap_0x83: mov 0x83, %g5; restore; ta 0; nop;\
SW_trap_0x84: mov 0x84, %g5; restore; ta 0; nop;\
SW_trap_0x85: mov 0x85, %g5; restore; ta 0; nop;\
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
