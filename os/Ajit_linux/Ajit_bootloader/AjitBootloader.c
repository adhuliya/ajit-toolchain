//A simple bootloader for booting the Linux kernel on the Ajit processor.
//
//The bootloader does its job in 4 steps:
//
//	STEP 1 : Initialize all processor registers
//	STEP 2 : Set up the inital MMU page tables.
//	STEP 3 : Pass hardware information to the kernel through a romvec structure
//	STEP 4 : Enable the MMU and jump to start of kernel.
//
//Author: Neha Karanjkar

	
	
#include "Ajit_putchar.h"
#include "Ajit_romvec.h"
#include "Ajit_memory_map.h"


//Physical address of initial page tables
#ifndef MAPTOHIGH
#define CONTEXT_TABLE_BASE_ADDR 0x00001000
#define L1_TABLE_BASE_ADDR      0x00002000
#else
#define CONTEXT_TABLE_BASE_ADDR 0xf0001000
#define L1_TABLE_BASE_ADDR      0xf0002000
#endif

//Addresses of MMU registers
#define AJIT_MMU_REG_CONTROL			0x00000000
#define AJIT_MMU_REG_CONTEXT_TABLE_PTR		0x00000100
#define AJIT_MMU_REG_CONTEXT			0x00000200
#define AJIT_MMU_REG_FSR			0x00000300
#define AJIT_MMU_REG_FAR			0x00000400

//Mmu asi constants
#define AJIT_ASI_MMU_REGISTER 		0x04
#define AJIT_ASI_MMU_FLUSH_PROBE	0x03
#define AJIT_ASI_FLUSH_I_D_CONTEXT	0x13

//get a PTD, given a physical address
#define getPTD(paddr) ( (paddr>>4) | (0x00000001) )
//get a PTE, given a physical address
#define getPTE(paddr) ( (paddr>>4) | (0x0000009E) )

#define clear_register_window() {\
__asm__ __volatile__( "save\n\t "); \
__asm__ __volatile__( "mov %g0, %l0 \n\t "); __asm__ __volatile__( "mov %g0, %l1 \n\t ");\
__asm__ __volatile__( "mov %g0, %l2 \n\t "); __asm__ __volatile__( "mov %g0, %l3 \n\t ");\
__asm__ __volatile__( "mov %g0, %l4 \n\t "); __asm__ __volatile__( "mov %g0, %l5 \n\t ");\
__asm__ __volatile__( "mov %g0, %l6 \n\t "); __asm__ __volatile__( "mov %g0, %l7 \n\t ");\
__asm__ __volatile__( "mov %g0, %o0 \n\t "); __asm__ __volatile__( "mov %g0, %o1 \n\t ");\
__asm__ __volatile__( "mov %g0, %o2 \n\t "); __asm__ __volatile__( "mov %g0, %o3 \n\t ");\
__asm__ __volatile__( "mov %g0, %o4 \n\t "); __asm__ __volatile__( "mov %g0, %o5 \n\t ");\
__asm__ __volatile__( "mov %g0, %o6 \n\t "); __asm__ __volatile__( "mov %g0, %o7 \n\t ");}

#define restore_window() {\
__asm__ __volatile__( "restore\n\t "); }

//NOTE : with function main() use the
//attribute "((section(".text.main")))"
//to ensure that main() is  put in the
//beginning of the ".text" section in the 
//generated executable.
int bootloader();
void  __attribute__((section(".text.main")))  main()
{
	//===================================
	//STEP 1 : Initialize all registers
	//===================================
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
	clear_register_window();
	clear_register_window();
	clear_register_window();
	clear_register_window();
	clear_register_window();
	clear_register_window();
	clear_register_window();
	clear_register_window();

	restore_window();
	restore_window();
	restore_window();
	restore_window();
	restore_window();
	restore_window();
	restore_window();
	restore_window();

	//Initialize the stack pointer and frame pointer
	__asm__ __volatile__("mov %0, %%sp\n\t" : : "r"(BOOTLOADER_INITIAL_STACK_POINTER));
	bootloader();

}

int  __attribute__((section(".text.main")))  bootloader()
{
	
	ajit_putstring("\n Ajit Bootloader\n");
	
	//===================================
	//STEP 2 : Set up the inital page tables.
	//===================================
	//set up the context table
	uint32_t* context_table = (uint32_t*) CONTEXT_TABLE_BASE_ADDR;
	context_table[0] = getPTD(L1_TABLE_BASE_ADDR);

	//set up the L1 page table entries
	uint32_t* L1_table = (uint32_t*) L1_TABLE_BASE_ADDR;
	

#ifndef MAPTOHIGH
	//map the bootloader segment
	//VA 0x0000 0000 - 0x0100 0000  to  PA 0x0000 0000 - 0x0100 0000
	L1_table[0] = getPTE(0x00000000);
	
	//map the kernel
	//VA 0xf000 0000 - 0xf100 0000  to  PA 0x0000 0000 - 0x0100 0000
	L1_table[0xf0] = getPTE(0x00000000);
#else
	//map the bootloader+kernel segment
	//VA 0xf000 0000 - 0xf100 0000  to  PA 0xf000 0000 - 0xf100 0000
	L1_table[0xf0] = getPTE(0xf0000000);
#endif

	//set up mmu context table pointer register
	uint32_t context_table_pointer_value = ((uint32_t)CONTEXT_TABLE_BASE_ADDR) >> 4;
	
	//Set up MMU registers :
	//Context register :
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(0x0), "r"(AJIT_MMU_REG_CONTEXT),"i"(AJIT_ASI_MMU_REGISTER) : "memory");
	//Context table pointer register
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(context_table_pointer_value), "r"(AJIT_MMU_REG_CONTEXT_TABLE_PTR),"i"(AJIT_ASI_MMU_REGISTER) : "memory");

	

	//=================================================
	//STEP 3 : Pass hardware information to the kernel
	//through a structure called "romvec".
	//=================================================
	uint32_t romvec_pointer = (uint32_t)(get_Ajit_romvec())+(uint32_t)(KERNEL_OFFSET);
	__asm__ __volatile__("mov %0, %%o0 \n\t" : : "r"(romvec_pointer));
	

	
	//=================================================
	//STEP 4 : Enable the MMU and jump to start of kernel.
	//=================================================
	//Control register (set the mmu enable bit)
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(0x00000001), "r"(AJIT_MMU_REG_CONTROL),"i"(AJIT_ASI_MMU_REGISTER) : "memory");
	//jump to kernel start
	__asm__ __volatile__("set 0xf0004000, %g2 \n\t \
			      jmpl %g2, %g0\n\t" );
	__asm__ __volatile__("nop \n\t \
			      nop \n\t \
			      nop \n\t" );


	//halt
	//this should never be executed
	__asm__ __volatile__("ta 0 \n\t \
			      nop \n\t \
			      nop \n\t" );


	return 0;
}
