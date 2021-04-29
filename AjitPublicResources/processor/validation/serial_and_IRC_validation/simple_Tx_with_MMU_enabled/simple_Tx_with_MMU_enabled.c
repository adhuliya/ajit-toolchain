// simple_Tx_with_MMU_enabled
// Check if output through serial device works when the MMU is enabled
//
// Author: Neha Karanjkar




#include<stdint.h>
#include"Ajit_Hardware_Configuration.h"
#include"CommonSerialRoutines.h"


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



//correct termination
inline void correct_termination(void)
{
	__asm__ __volatile__("mov %0, %%g1\n\t" : :
			     "i"(0xF00) : );
	__asm__ __volatile__( "nop; ta 0; nop; nop; \n\t "); 
}

//wrong termination
inline void wrong_termination(void)
{
	__asm__ __volatile__("mov %0, %%g1\n\t" : :
			     "i"(0xBAD) : );
	__asm__ __volatile__( "nop; ta 0; nop; nop; \n\t "); 
}


int startTest();
//NOTE : with function main() use the
//attribute "((section(".text.main")))"
//to ensure that main() is  put in the
//beginning of the ".text" section in the 
//generated executable.
int  __attribute__((section(".text.main")))  main()
{
	//Initialize PSR, enable traps.
	//set PSR with ET=1 PS=1 S=1, all other fields=0
	__asm__ __volatile__("mov 0xE0, %l0	;");
	__asm__ __volatile__("wr %l0, %psr 	;");
	__asm__ __volatile__("nop	   	;");
	__asm__ __volatile__("nop	   	;");
	__asm__ __volatile__("nop	   	;");
	
	//store base of trap table in TBR register
	__asm__ __volatile__("set	trap_table_base, %l0	;");
	__asm__ __volatile__("wr	%l0, 0x0, %tbr      	;");
	__asm__ __volatile__("nop	                    	;");
	__asm__ __volatile__("nop	                    	;");
	__asm__ __volatile__("nop                           	;");


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

	//Initialize stack pointer
	//Top of stack is 0x20000000.
	__asm__ __volatile__( "set 0x20000000, %g1 \n\t ");
	__asm__ __volatile__( "mov %g1, %sp \n\t ");
	__asm__ __volatile__( "mov %g0, %g1 \n\t ");
	
	startTest();
	return 0;

}

//Page tables
uint32_t ContextTable[256]  		__attribute__((aligned(0x1000)));
uint32_t process1_L1PageTable[256] 	__attribute__((aligned(0x1000)));
uint32_t process1_L2PageTable[64]  	__attribute__((aligned(0x1000)));
uint32_t process1_L3PageTable[64]  	__attribute__((aligned(0x1000)));

	
inline void setupPageTables()
{
	//Map all instruction-area such that VA=PA, with full permissions
	
	//context table pointer register
	uint32_t context_table_ptr_value = convertPhyAddrToPTD((uint32_t)ContextTable);
	store_word_mmureg(context_table_ptr_value, (uint32_t*)MMU_REG_CONTEXT_TABLE_PTR);
	
	//Context table:
	ContextTable[0] = convertPhyAddrToPTD(((uint32_t)process1_L1PageTable));

	//Create L1 page table entries
	//such that physical address = virtual address.
	//for all addresses except 0xA0000000-0xA1000000.
	uint32_t i;
	i=0x00; process1_L1PageTable[i] = (i<<20) | (0x8E);//text segment
	i=0x1F; process1_L1PageTable[i] = (i<<20) | (0x8E);//stack area
	i=0xFF; process1_L1PageTable[i] = (i<<20) | (0x8E);//stack area
};


int  __attribute__((section(".text.main"))) startTest()
{
	
	
	//Setup page tables and enabled the MMU
	//the page tables are set up such that all VA=PA.
	setupPageTables();
	


	//Now enable the MMU by writing into MMU control register
	uint32_t MMU_control_word = 0x1; //set the Enable bit
	store_word_mmureg(0x0 , (uint32_t*) MMU_REG_CONTEXT);
	store_word_mmureg(MMU_control_word, (uint32_t*) MMU_REG_CONTROL);

	

	//Enable Tx and Rx in the serial device
	enableTx();
	
	sendAChar('A');
	sendAChar('B');
	sendAChar('C');
	sendAChar('\n');
		
	correct_termination();
	return 0;
}


//====================================
// TRAP TABLE
//
//NOTE : serial trap handler is located at 
//	HW_trap_0x1c 
//
//====================================
__asm__("\
.align 4096;\
trap_table_base:\
HW_trap_0x00: mov 0x00, %g1; restore; ta 0; nop;\
HW_trap_0x01: mov 0x01, %g1; restore; ta 0; nop;\
HW_trap_0x02: mov 0x02, %g1; restore; ta 0; nop;\
HW_trap_0x03: mov 0x03, %g1; restore; ta 0; nop;\
HW_trap_0x04: mov 0x04, %g1; restore; ta 0; nop;\
HW_trap_0x05: mov 0x05, %g1; restore; ta 0; nop;\
HW_trap_0x06: mov 0x06, %g1; restore; ta 0; nop;\
HW_trap_0x07: mov 0x07, %g1; restore; ta 0; nop;\
HW_trap_0x08: mov 0x08, %g1; restore; ta 0; nop;\
HW_trap_0x09: mov 0x09, %g1; restore; ta 0; nop;\
HW_trap_0x0a: mov 0x0a, %g1; restore; ta 0; nop;\
HW_trap_0x0b: mov 0x0b, %g1; restore; ta 0; nop;\
HW_trap_0x0c: mov 0x0c, %g1; restore; ta 0; nop;\
HW_trap_0x0d: mov 0x0d, %g1; restore; ta 0; nop;\
HW_trap_0x0e: mov 0x0e, %g1; restore; ta 0; nop;\
HW_trap_0x0f: mov 0x0f, %g1; restore; ta 0; nop;\
HW_trap_0x10: mov 0x10, %g1; restore; ta 0; nop;\
HW_trap_0x11: mov 0x11, %g1; restore; ta 0; nop;\
HW_trap_0x12: mov 0x12, %g1; restore; ta 0; nop;\
HW_trap_0x13: mov 0x13, %g1; restore; ta 0; nop;\
HW_trap_0x14: mov 0x14, %g1; restore; ta 0; nop;\
HW_trap_0x15: mov 0x15, %g1; restore; ta 0; nop;\
HW_trap_0x16: mov 0x16, %g1; restore; ta 0; nop;\
HW_trap_0x17: mov 0x17, %g1; restore; ta 0; nop;\
HW_trap_0x18: mov 0x18, %g1; restore; ta 0; nop;\
HW_trap_0x19: mov 0x19, %g1; restore; ta 0; nop;\
HW_trap_0x1a: mov 0x20, %g1; restore; ta 0; nop;\
HW_trap_0x1b: mov 0x1b, %g1; restore; ta 0; nop;\
HW_trap_0x1c: mov 0x1c, %g1; restore; ta 0; nop;\
HW_trap_0x1d: mov 0x1d, %g1; restore; ta 0; nop;\
HW_trap_0x1e: mov 0x1e, %g1; restore; ta 0; nop;\
HW_trap_0x1f: mov 0x1f, %g1; restore; ta 0; nop;\
HW_trap_0x20: mov 0x20, %g1; restore; ta 0; nop;\
HW_trap_0x21: mov 0x21, %g1; restore; ta 0; nop;\
HW_trap_0x22: mov 0x22, %g1; restore; ta 0; nop;\
HW_trap_0x23: mov 0x23, %g1; restore; ta 0; nop;\
HW_trap_0x24: mov 0x24, %g1; restore; ta 0; nop;\
HW_trap_0x25: mov 0x25, %g1; restore; ta 0; nop;\
HW_trap_0x26: mov 0x26, %g1; restore; ta 0; nop;\
HW_trap_0x27: mov 0x27, %g1; restore; ta 0; nop;\
HW_trap_0x28: mov 0x28, %g1; restore; ta 0; nop;\
HW_trap_0x29: mov 0x29, %g1; restore; ta 0; nop;\
HW_trap_0x2a: mov 0x2a, %g1; restore; ta 0; nop;\
HW_trap_0x2b: mov 0x2b, %g1; restore; ta 0; nop;\
HW_trap_0x2c: mov 0x2c, %g1; restore; ta 0; nop;\
HW_trap_0x2d: mov 0x2d, %g1; restore; ta 0; nop;\
HW_trap_0x2e: mov 0x2e, %g1; restore; ta 0; nop;\
HW_trap_0x2f: mov 0x2f, %g1; restore; ta 0; nop;\
HW_trap_0x30: mov 0x30, %g1; restore; ta 0; nop;\
HW_trap_0x31: mov 0x31, %g1; restore; ta 0; nop;\
HW_trap_0x32: mov 0x32, %g1; restore; ta 0; nop;\
HW_trap_0x33: mov 0x33, %g1; restore; ta 0; nop;\
HW_trap_0x34: mov 0x34, %g1; restore; ta 0; nop;\
HW_trap_0x35: mov 0x35, %g1; restore; ta 0; nop;\
HW_trap_0x36: mov 0x36, %g1; restore; ta 0; nop;\
HW_trap_0x37: mov 0x37, %g1; restore; ta 0; nop;\
HW_trap_0x38: mov 0x38, %g1; restore; ta 0; nop;\
HW_trap_0x39: mov 0x39, %g1; restore; ta 0; nop;\
HW_trap_0x3a: mov 0x3a, %g1; restore; ta 0; nop;\
HW_trap_0x3b: mov 0x3b, %g1; restore; ta 0; nop;\
HW_trap_0x3c: mov 0x3c, %g1; restore; ta 0; nop;\
HW_trap_0x3d: mov 0x3d, %g1; restore; ta 0; nop;\
HW_trap_0x3e: mov 0x3e, %g1; restore; ta 0; nop;\
HW_trap_0x3f: mov 0x3f, %g1; restore; ta 0; nop;\
HW_trap_0x40: mov 0x40, %g1; restore; ta 0; nop;\
HW_trap_0x41: mov 0x41, %g1; restore; ta 0; nop;\
HW_trap_0x42: mov 0x42, %g1; restore; ta 0; nop;\
HW_trap_0x43: mov 0x43, %g1; restore; ta 0; nop;\
HW_trap_0x44: mov 0x44, %g1; restore; ta 0; nop;\
HW_trap_0x45: mov 0x45, %g1; restore; ta 0; nop;\
HW_trap_0x46: mov 0x46, %g1; restore; ta 0; nop;\
HW_trap_0x47: mov 0x47, %g1; restore; ta 0; nop;\
HW_trap_0x48: mov 0x48, %g1; restore; ta 0; nop;\
HW_trap_0x49: mov 0x49, %g1; restore; ta 0; nop;\
HW_trap_0x4a: mov 0x4a, %g1; restore; ta 0; nop;\
HW_trap_0x4b: mov 0x4b, %g1; restore; ta 0; nop;\
HW_trap_0x4c: mov 0x4c, %g1; restore; ta 0; nop;\
HW_trap_0x4d: mov 0x4d, %g1; restore; ta 0; nop;\
HW_trap_0x4e: mov 0x4e, %g1; restore; ta 0; nop;\
HW_trap_0x4f: mov 0x4f, %g1; restore; ta 0; nop;\
HW_trap_0x50: mov 0x50, %g1; restore; ta 0; nop;\
HW_trap_0x51: mov 0x51, %g1; restore; ta 0; nop;\
HW_trap_0x52: mov 0x52, %g1; restore; ta 0; nop;\
HW_trap_0x53: mov 0x53, %g1; restore; ta 0; nop;\
HW_trap_0x54: mov 0x54, %g1; restore; ta 0; nop;\
HW_trap_0x55: mov 0x55, %g1; restore; ta 0; nop;\
HW_trap_0x56: mov 0x56, %g1; restore; ta 0; nop;\
HW_trap_0x57: mov 0x57, %g1; restore; ta 0; nop;\
HW_trap_0x58: mov 0x58, %g1; restore; ta 0; nop;\
HW_trap_0x59: mov 0x59, %g1; restore; ta 0; nop;\
HW_trap_0x5a: mov 0x5a, %g1; restore; ta 0; nop;\
HW_trap_0x5b: mov 0x5b, %g1; restore; ta 0; nop;\
HW_trap_0x5c: mov 0x5c, %g1; restore; ta 0; nop;\
HW_trap_0x5d: mov 0x5d, %g1; restore; ta 0; nop;\
HW_trap_0x5e: mov 0x5e, %g1; restore; ta 0; nop;\
HW_trap_0x5f: mov 0x5f, %g1; restore; ta 0; nop;\
HW_trap_0x60: mov 0x60, %g1; restore; ta 0; nop;\
HW_trap_0x61: mov 0x61, %g1; restore; ta 0; nop;\
HW_trap_0x62: mov 0x62, %g1; restore; ta 0; nop;\
HW_trap_0x63: mov 0x63, %g1; restore; ta 0; nop;\
HW_trap_0x64: mov 0x64, %g1; restore; ta 0; nop;\
HW_trap_0x65: mov 0x65, %g1; restore; ta 0; nop;\
HW_trap_0x66: mov 0x66, %g1; restore; ta 0; nop;\
HW_trap_0x67: mov 0x67, %g1; restore; ta 0; nop;\
HW_trap_0x68: mov 0x68, %g1; restore; ta 0; nop;\
HW_trap_0x69: mov 0x69, %g1; restore; ta 0; nop;\
HW_trap_0x6a: mov 0x6a, %g1; restore; ta 0; nop;\
HW_trap_0x6b: mov 0x6b, %g1; restore; ta 0; nop;\
HW_trap_0x6c: mov 0x6c, %g1; restore; ta 0; nop;\
HW_trap_0x6d: mov 0x6d, %g1; restore; ta 0; nop;\
HW_trap_0x6e: mov 0x6e, %g1; restore; ta 0; nop;\
HW_trap_0x6f: mov 0x6f, %g1; restore; ta 0; nop;\
HW_trap_0x70: mov 0x70, %g1; restore; ta 0; nop;\
HW_trap_0x71: mov 0x71, %g1; restore; ta 0; nop;\
HW_trap_0x72: mov 0x72, %g1; restore; ta 0; nop;\
HW_trap_0x73: mov 0x73, %g1; restore; ta 0; nop;\
HW_trap_0x74: mov 0x74, %g1; restore; ta 0; nop;\
HW_trap_0x75: mov 0x75, %g1; restore; ta 0; nop;\
HW_trap_0x76: mov 0x76, %g1; restore; ta 0; nop;\
HW_trap_0x77: mov 0x77, %g1; restore; ta 0; nop;\
HW_trap_0x78: mov 0x78, %g1; restore; ta 0; nop;\
HW_trap_0x79: mov 0x79, %g1; restore; ta 0; nop;\
HW_trap_0x7a: mov 0x7a, %g1; restore; ta 0; nop;\
HW_trap_0x7b: mov 0x7b, %g1; restore; ta 0; nop;\
HW_trap_0x7c: mov 0x7c, %g1; restore; ta 0; nop;\
HW_trap_0x7d: mov 0x7d, %g1; restore; ta 0; nop;\
HW_trap_0x7e: mov 0x7e, %g1; restore; ta 0; nop;\
HW_trap_0x7f: mov 0x7f, %g1; restore; ta 0; nop;\
SW_trap_0x80: mov 0x80, %g1; restore; ta 0; nop;\
SW_trap_0x81: mov 0x81, %g1; restore; ta 0; nop;\
SW_trap_0x82: mov 0x81, %g1; restore; ta 0; nop;\
SW_trap_0x83: mov 0x83, %g1; restore; ta 0; nop;\
SW_trap_0x84: mov 0x84, %g1; restore; ta 0; nop;\
SW_trap_0x85: mov 0x85, %g1; restore; ta 0; nop;\
SW_trap_0x86: mov 0x86, %g1; restore; ta 0; nop;\
SW_trap_0x87: mov 0x87, %g1; restore; ta 0; nop;\
SW_trap_0x88: mov 0x88, %g1; restore; ta 0; nop;\
SW_trap_0x89: mov 0x89, %g1; restore; ta 0; nop;\
SW_trap_0x8a: mov 0x8a, %g1; restore; ta 0; nop;\
SW_trap_0x8b: mov 0x8b, %g1; restore; ta 0; nop;\
SW_trap_0x8c: mov 0x8c, %g1; restore; ta 0; nop;\
SW_trap_0x8d: mov 0x8d, %g1; restore; ta 0; nop;\
SW_trap_0x8e: mov 0x8e, %g1; restore; ta 0; nop;\
SW_trap_0x8f: mov 0x8f, %g1; restore; ta 0; nop;\
SW_trap_0x90: mov 0x90, %g1; restore; ta 0; nop;\
SW_trap_0x91: mov 0x91, %g1; restore; ta 0; nop;\
SW_trap_0x92: mov 0x92, %g1; restore; ta 0; nop;\
SW_trap_0x93: mov 0x93, %g1; restore; ta 0; nop;\
SW_trap_0x94: mov 0x94, %g1; restore; ta 0; nop;\
SW_trap_0x95: mov 0x95, %g1; restore; ta 0; nop;\
SW_trap_0x96: mov 0x96, %g1; restore; ta 0; nop;\
SW_trap_0x97: mov 0x97, %g1; restore; ta 0; nop;\
SW_trap_0x98: mov 0x98, %g1; restore; ta 0; nop;\
SW_trap_0x99: mov 0x99, %g1; restore; ta 0; nop;\
SW_trap_0x9a: mov 0x9a, %g1; restore; ta 0; nop;\
SW_trap_0x9b: mov 0x9b, %g1; restore; ta 0; nop;\
SW_trap_0x9c: mov 0x9c, %g1; restore; ta 0; nop;\
SW_trap_0x9d: mov 0x9d, %g1; restore; ta 0; nop;\
SW_trap_0x9e: mov 0x9e, %g1; restore; ta 0; nop;\
SW_trap_0x9f: mov 0x9f, %g1; restore; ta 0; nop;\
SW_trap_0xa0: mov 0xa0, %g1; restore; ta 0; nop;\
SW_trap_0xa1: mov 0xa1, %g1; restore; ta 0; nop;\
SW_trap_0xa2: mov 0xa2, %g1; restore; ta 0; nop;\
SW_trap_0xa3: mov 0xa3, %g1; restore; ta 0; nop;\
SW_trap_0xa4: mov 0xa4, %g1; restore; ta 0; nop;\
SW_trap_0xa5: mov 0xa5, %g1; restore; ta 0; nop;\
SW_trap_0xa6: mov 0xa6, %g1; restore; ta 0; nop;\
SW_trap_0xa7: mov 0xa7, %g1; restore; ta 0; nop;\
SW_trap_0xa8: mov 0xa8, %g1; restore; ta 0; nop;\
SW_trap_0xa9: mov 0xa9, %g1; restore; ta 0; nop;\
SW_trap_0xaa: mov 0xaa, %g1; restore; ta 0; nop;\
SW_trap_0xab: mov 0xab, %g1; restore; ta 0; nop;\
SW_trap_0xac: mov 0xac, %g1; restore; ta 0; nop;\
SW_trap_0xad: mov 0xad, %g1; restore; ta 0; nop;\
SW_trap_0xae: mov 0xae, %g1; restore; ta 0; nop;\
SW_trap_0xaf: mov 0xaf, %g1; restore; ta 0; nop;\
SW_trap_0xb0: mov 0xb0, %g1; restore; ta 0; nop;\
SW_trap_0xb1: mov 0xb1, %g1; restore; ta 0; nop;\
SW_trap_0xb2: mov 0xb2, %g1; restore; ta 0; nop;\
SW_trap_0xb3: mov 0xb3, %g1; restore; ta 0; nop;\
SW_trap_0xb4: mov 0xb4, %g1; restore; ta 0; nop;\
SW_trap_0xb5: mov 0xb5, %g1; restore; ta 0; nop;\
SW_trap_0xb6: mov 0xb6, %g1; restore; ta 0; nop;\
SW_trap_0xb7: mov 0xb7, %g1; restore; ta 0; nop;\
SW_trap_0xb8: mov 0xb8, %g1; restore; ta 0; nop;\
SW_trap_0xb9: mov 0xb9, %g1; restore; ta 0; nop;\
SW_trap_0xba: mov 0xba, %g1; restore; ta 0; nop;\
SW_trap_0xbb: mov 0xbb, %g1; restore; ta 0; nop;\
SW_trap_0xbc: mov 0xbc, %g1; restore; ta 0; nop;\
SW_trap_0xbd: mov 0xbd, %g1; restore; ta 0; nop;\
SW_trap_0xbe: mov 0xbe, %g1; restore; ta 0; nop;\
SW_trap_0xbf: mov 0xbf, %g1; restore; ta 0; nop;\
SW_trap_0xc0: mov 0xc0, %g1; restore; ta 0; nop;\
SW_trap_0xc1: mov 0xc1, %g1; restore; ta 0; nop;\
SW_trap_0xc2: mov 0xc2, %g1; restore; ta 0; nop;\
SW_trap_0xc3: mov 0xc3, %g1; restore; ta 0; nop;\
SW_trap_0xc4: mov 0xc4, %g1; restore; ta 0; nop;\
SW_trap_0xc5: mov 0xc5, %g1; restore; ta 0; nop;\
SW_trap_0xc6: mov 0xc6, %g1; restore; ta 0; nop;\
SW_trap_0xc7: mov 0xc7, %g1; restore; ta 0; nop;\
SW_trap_0xc8: mov 0xc8, %g1; restore; ta 0; nop;\
SW_trap_0xc9: mov 0xc9, %g1; restore; ta 0; nop;\
SW_trap_0xca: mov 0xca, %g1; restore; ta 0; nop;\
SW_trap_0xcb: mov 0xcb, %g1; restore; ta 0; nop;\
SW_trap_0xcc: mov 0xcc, %g1; restore; ta 0; nop;\
SW_trap_0xcd: mov 0xcd, %g1; restore; ta 0; nop;\
SW_trap_0xce: mov 0xce, %g1; restore; ta 0; nop;\
SW_trap_0xcf: mov 0xcf, %g1; restore; ta 0; nop;\
SW_trap_0xd0: mov 0xd0, %g1; restore; ta 0; nop;\
SW_trap_0xd1: mov 0xd1, %g1; restore; ta 0; nop;\
SW_trap_0xd2: mov 0xd2, %g1; restore; ta 0; nop;\
SW_trap_0xd3: mov 0xd3, %g1; restore; ta 0; nop;\
SW_trap_0xd4: mov 0xd4, %g1; restore; ta 0; nop;\
SW_trap_0xd5: mov 0xd5, %g1; restore; ta 0; nop;\
SW_trap_0xd6: mov 0xd6, %g1; restore; ta 0; nop;\
SW_trap_0xd7: mov 0xd7, %g1; restore; ta 0; nop;\
SW_trap_0xd8: mov 0xd8, %g1; restore; ta 0; nop;\
SW_trap_0xd9: mov 0xd9, %g1; restore; ta 0; nop;\
SW_trap_0xda: mov 0xda, %g1; restore; ta 0; nop;\
SW_trap_0xdb: mov 0xdb, %g1; restore; ta 0; nop;\
SW_trap_0xdc: mov 0xdc, %g1; restore; ta 0; nop;\
SW_trap_0xdd: mov 0xdd, %g1; restore; ta 0; nop;\
SW_trap_0xde: mov 0xde, %g1; restore; ta 0; nop;\
SW_trap_0xdf: mov 0xdf, %g1; restore; ta 0; nop;\
SW_trap_0xe0: mov 0xe0, %g1; restore; ta 0; nop;\
SW_trap_0xe1: mov 0xe1, %g1; restore; ta 0; nop;\
SW_trap_0xe2: mov 0xe2, %g1; restore; ta 0; nop;\
SW_trap_0xe3: mov 0xe3, %g1; restore; ta 0; nop;\
SW_trap_0xe4: mov 0xe4, %g1; restore; ta 0; nop;\
SW_trap_0xe5: mov 0xe5, %g1; restore; ta 0; nop;\
SW_trap_0xe6: mov 0xe6, %g1; restore; ta 0; nop;\
SW_trap_0xe7: mov 0xe7, %g1; restore; ta 0; nop;\
SW_trap_0xe8: mov 0xe8, %g1; restore; ta 0; nop;\
SW_trap_0xe9: mov 0xe9, %g1; restore; ta 0; nop;\
SW_trap_0xea: mov 0xea, %g1; restore; ta 0; nop;\
SW_trap_0xeb: mov 0xeb, %g1; restore; ta 0; nop;\
SW_trap_0xec: mov 0xec, %g1; restore; ta 0; nop;\
SW_trap_0xed: mov 0xed, %g1; restore; ta 0; nop;\
SW_trap_0xee: mov 0xee, %g1; restore; ta 0; nop;\
SW_trap_0xef: mov 0xef, %g1; restore; ta 0; nop;\
SW_trap_0xf0: mov 0xf0, %g1; restore; ta 0; nop;\
SW_trap_0xf1: mov 0xf1, %g1; restore; ta 0; nop;\
SW_trap_0xf2: mov 0xf2, %g1; restore; ta 0; nop;\
SW_trap_0xf3: mov 0xf3, %g1; restore; ta 0; nop;\
SW_trap_0xf4: mov 0xf4, %g1; restore; ta 0; nop;\
SW_trap_0xf5: mov 0xf5, %g1; restore; ta 0; nop;\
SW_trap_0xf6: mov 0xf6, %g1; restore; ta 0; nop;\
SW_trap_0xf7: mov 0xf7, %g1; restore; ta 0; nop;\
SW_trap_0xf8: mov 0xf8, %g1; restore; ta 0; nop;\
SW_trap_0xf9: mov 0xf9, %g1; restore; ta 0; nop;\
SW_trap_0xfa: mov 0xfa, %g1; restore; ta 0; nop;\
SW_trap_0xfb: mov 0xfb, %g1; restore; ta 0; nop;\
SW_trap_0xfc: mov 0xfc, %g1; restore; ta 0; nop;\
SW_trap_0xfd: mov 0xfd, %g1; restore; ta 0; nop;\
SW_trap_0xfe: mov 0xfe, %g1; restore; ta 0; nop;\
");
