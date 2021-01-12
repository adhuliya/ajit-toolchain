//A simple memory test.
//
//
//Author: Neha Karanjkar
//Date: 2 Nov 2016

#include<stdint.h>

#define START_ADDRESS 0xFF000000
#define END_ADDRESS   0xFF000010
#define STRIDE 4  //cache block size is 64Bytes.




//correct termination
inline void correct_termination()
{
	__asm__ __volatile__("mov 0xF00, %g5\n\t");
	__asm__ __volatile__("ta 0\n\t");
	__asm__ __volatile__("nop\n\t");
	__asm__ __volatile__("nop\n\t");
	__asm__ __volatile__("nop\n\t");
}

//wrong termination
inline void wrong_termination()
{
	__asm__ __volatile__("mov 0xBAD, %g5\n\t");
	__asm__ __volatile__("ta 0\n\t");
	__asm__ __volatile__("nop\n\t");
	__asm__ __volatile__("nop\n\t");
	__asm__ __volatile__("nop\n\t");
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


//write a 32b value into memory at a given address
#define STORE(val, addr)  {__asm__("st %0, [%1];\n\t" :/*no output*/:"r"(val),"r"(addr) /*input*/ :/*clobbered*/ );}

//read a 32b word from memory into a variable
#define LOAD(addr, variable)  {__asm__("ld [%1], %0;\n\t" :"=r"(variable)/* output*/:"r"(addr)/*input*/ :/*clobbered*/ );}


int  __attribute__((section(".text.main")))  startTest()
{
	
	uint32_t i;
	uint32_t stride =STRIDE;  //cache block size is 64Bytes.
	__asm__ __volatile__("mov 0xBAD, %g5\n\t");
	
	//ascending
	for (i=START_ADDRESS; i<=END_ADDRESS;i+=stride)
	{
	 	//write i itself into mem location i
		STORE(i, i);
	}
	//ascending
	for (i=START_ADDRESS; i<=END_ADDRESS;i+=stride)
	{
	 	//read from mem
	 	uint32_t val=0;
		LOAD(i,val);
		if(val!=i) wrong_termination();
	 	//write i+1 in mem location i
		STORE(i+1, i);
	}
	//descending
	for (i=END_ADDRESS; i>=START_ADDRESS;i-=stride)
	{
	 	//read from mem
	 	uint32_t val=0;
		LOAD(i,val);
		if(val!=i+1) wrong_termination();
	 	//write i-1 in mem location i
		STORE(i-1, i);
	}
	//descending
	for (i=END_ADDRESS; i>=START_ADDRESS;i-=stride)
	{
	 	//read from mem
	 	uint32_t val=0;
		LOAD(i,val);
		if(val!=i-1) wrong_termination();
	}


	correct_termination();
	return 0;
}
	

//============================================
// Trap Table
//In the trap handler, we push the trap_number into %g5
//and return to the instruction following the trapped one.
//The Trap Table must be aligned to a page(4096 Bytes)
//============================================


__asm__ (".align 4096; \n\t\
HW_trap_0x00: mov 0xFF, %g5; restore; ta 0; nop; ! Reset                                   \n\t\
HW_trap_0x01: mov 0x01, %g5; restore; ta 0; nop; ! Text fault, instruction access exception\n\t\
HW_trap_0x02: mov 0x02, %g5; restore; ta 0; nop; ! Illegal instruction                     \n\t\
HW_trap_0x03: mov 0x03, %g5; restore; ta 0; nop; ! Privileged instruction                  \n\t\
HW_trap_0x04: mov 0x04, %g5; restore; ta 0; nop; ! Floating point disabled                 \n\t\
HW_trap_0x05: mov 0x05, %g5; restore; ta 0; nop; ! Window overflow                         \n\t\
HW_trap_0x06: mov 0x06, %g5; restore; ta 0; nop; ! Window underflow                        \n\t\
HW_trap_0x07: mov 0x07, %g5; restore; ta 0; nop; ! Memory address not aligned              \n\t\
HW_trap_0x08: mov 0x08, %g5; restore; ta 0; nop; ! Floating point exception                \n\t\
HW_trap_0x09: mov 0x09, %g5; restore; ta 0; nop; ! Data fault, data access exception       \n\t\
HW_trap_0x0a: mov 0x0a, %g5; restore; ta 0; nop; ! Tag overflow                            \n\t\
HW_trap_0x0b: mov 0x0b, %g5; restore; ta 0; nop; ! Watchpoint detected                     \n\t\
HW_trap_0x0c: mov 0x0c, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x0d: mov 0x0d, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x0e: mov 0x0e, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x0f: mov 0x0f, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x10: mov 0x10, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x11: mov 0x11, %g5; restore; ta 0; nop; ! Interrupt, level 1  - Implementation dependent       \n\t\
HW_trap_0x12: mov 0x12, %g5; restore; ta 0; nop; ! Interrupt, level 2  - Sbus/VME level 1               \n\t\
HW_trap_0x13: mov 0x13, %g5; restore; ta 0; nop; ! Interrupt, level 3  - Sbus/VME level 2               \n\t\
HW_trap_0x14: mov 0x14, %g5; restore; ta 0; nop; ! Interrupt, level 4  - Onboard SCSI                   \n\t\
HW_trap_0x15: mov 0x15, %g5; restore; ta 0; nop; ! Interrupt, level 5  - Sbus/VME level 3               \n\t\
HW_trap_0x16: mov 0x16, %g5; restore; ta 0; nop; ! Interrupt, level 6  - Onboard ethernet               \n\t\
HW_trap_0x17: mov 0x17, %g5; restore; ta 0; nop; ! Interrupt, level 7  - Sbus/VME level 4               \n\t\
HW_trap_0x18: mov 0x18, %g5; restore; ta 0; nop; ! Interrupt, level 8  - Onboard video                  \n\t\
HW_trap_0x19: mov 0x19, %g5; restore; ta 0; nop; ! Interrupt, level 9  - Sbus/VME level 5, module       \n\t\
HW_trap_0x1a: mov 0x1a, %g5; restore; ta 0; nop; ! Interrupt, level 10 - TOD clock                      \n\t\
HW_trap_0x1b: mov 0x1b, %g5; restore; ta 0; nop; ! Interrupt, level 11 - Sbus/VME level 6, floppy       \n\t\
HW_trap_0x1c: mov 0x1c, %g5; restore; ta 0; nop; ! Interrupt, level 12 - Serial I/O                     \n\t\
HW_trap_0x1d: mov 0x1d, %g5; restore; ta 0; nop; ! Interrupt, level 13 - Sbus/VME level 7, audio, X-Call\n\t\
HW_trap_0x1e: mov 0x1e, %g5; restore; ta 0; nop; ! Interrupt, level 14 - Hi-res system timer            \n\t\
HW_trap_0x1f: mov 0x1f, %g5; restore; ta 0; nop; ! Interrupt, level 15 - Asynchronous memory fault      \n\t\
HW_trap_0x20: mov 0x20, %g5; restore; ta 0; nop; ! Register access error (you're hosed!)                \n\t\
HW_trap_0x21: mov 0x21, %g5; restore; ta 0; nop; ! Text fault, instruction access error                 \n\t\
HW_trap_0x22: mov 0x22, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x23: mov 0x23, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x24: mov 0x24, %g5; restore; ta 0; nop; ! Coprocessor disabled        \n\t\
HW_trap_0x25: mov 0x25, %g5; restore; ta 0; nop; ! FLUSH/IFLUSH not implemented\n\t\
HW_trap_0x26: mov 0x26, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x27: mov 0x27, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x28: mov 0x28, %g5; restore; ta 0; nop; ! Coprocessor exception      \n\t\
HW_trap_0x29: mov 0x29, %g5; restore; ta 0; nop; ! Data access error          \n\t\
HW_trap_0x2a: mov 0x2a, %g5; restore; ta 0; nop; ! Division by zero exception \n\t\
HW_trap_0x2b: mov 0x2b, %g5; restore; ta 0; nop; ! Data store error           \n\t\
HW_trap_0x2c: mov 0x2c, %g5; restore; ta 0; nop; ! Data access MMU miss       \n\t\
HW_trap_0x2d: mov 0x2d, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x2e: mov 0x2e, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x2f: mov 0x2f, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x30: mov 0x30, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x31: mov 0x31, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x32: mov 0x32, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x33: mov 0x33, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x34: mov 0x34, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x35: mov 0x35, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x36: mov 0x36, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x37: mov 0x37, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x38: mov 0x38, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x39: mov 0x39, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x3a: mov 0x3a, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x3b: mov 0x3b, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x3c: mov 0x3c, %g5; restore; ta 0; nop; ! Instruction access MMU miss \n\t\
HW_trap_0x3d: mov 0x3d, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x3e: mov 0x3e, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x3f: mov 0x3f, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x40: mov 0x40, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x41: mov 0x41, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x42: mov 0x42, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x43: mov 0x43, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x44: mov 0x44, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x45: mov 0x45, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x46: mov 0x46, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x47: mov 0x47, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x48: mov 0x48, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x49: mov 0x49, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x4a: mov 0x4a, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x4b: mov 0x4b, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x4c: mov 0x4c, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x4d: mov 0x4d, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x4e: mov 0x4e, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x4f: mov 0x4f, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x50: mov 0x50, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x51: mov 0x51, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x52: mov 0x52, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x53: mov 0x53, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x54: mov 0x54, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x55: mov 0x55, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x56: mov 0x56, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x57: mov 0x57, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x58: mov 0x58, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x59: mov 0x59, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x5a: mov 0x5a, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x5b: mov 0x5b, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x5c: mov 0x5c, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x5d: mov 0x5d, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x5e: mov 0x5e, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x5f: mov 0x5f, %g5; restore; ta 0; nop; ! -----Undefined \n\t\
HW_trap_0x60: mov 0x60, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x61: mov 0x61, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x62: mov 0x62, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x63: mov 0x63, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x64: mov 0x64, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x65: mov 0x65, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x66: mov 0x66, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x67: mov 0x67, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x68: mov 0x68, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x69: mov 0x69, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x6a: mov 0x6a, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x6b: mov 0x6b, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x6c: mov 0x6c, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x6d: mov 0x6d, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x6e: mov 0x6e, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x6f: mov 0x6f, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x70: mov 0x70, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x71: mov 0x71, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x72: mov 0x72, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x73: mov 0x73, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x74: mov 0x74, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x75: mov 0x75, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x76: mov 0x76, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x77: mov 0x77, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x78: mov 0x78, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x79: mov 0x79, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x7a: mov 0x7a, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x7b: mov 0x7b, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x7c: mov 0x7c, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x7d: mov 0x7d, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x7e: mov 0x7e, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
HW_trap_0x7f: mov 0x7f, %g5; restore; ta 0; nop; ! -----Implementation-dependant \n\t\
SW_trap_0x80: mov 0x80, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x81: mov 0x81, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x82: mov 0x82, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x83: mov 0x83, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x84: mov 0x84, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x85: mov 0x85, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x86: mov 0x86, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x87: mov 0x87, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x88: mov 0x88, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x89: mov 0x89, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x8a: mov 0x8a, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x8b: mov 0x8b, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x8c: mov 0x8c, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x8d: mov 0x8d, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x8e: mov 0x8e, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x8f: mov 0x8f, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x90: mov 0x90, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x91: mov 0x91, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x92: mov 0x92, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x93: mov 0x93, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x94: mov 0x94, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x95: mov 0x95, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x96: mov 0x96, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x97: mov 0x97, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x98: mov 0x98, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x99: mov 0x99, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x9a: mov 0x9a, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x9b: mov 0x9b, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x9c: mov 0x9c, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x9d: mov 0x9d, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x9e: mov 0x9e, %g5; restore; ta 0; nop; \n\t\
SW_trap_0x9f: mov 0x9f, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xa0: mov 0xa0, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xa1: mov 0xa1, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xa2: mov 0xa2, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xa3: mov 0xa3, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xa4: mov 0xa4, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xa5: mov 0xa5, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xa6: mov 0xa6, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xa7: mov 0xa7, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xa8: mov 0xa8, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xa9: mov 0xa9, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xaa: mov 0xaa, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xab: mov 0xab, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xac: mov 0xac, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xad: mov 0xad, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xae: mov 0xae, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xaf: mov 0xaf, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xb0: mov 0xb0, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xb1: mov 0xb1, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xb2: mov 0xb2, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xb3: mov 0xb3, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xb4: mov 0xb4, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xb5: mov 0xb5, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xb6: mov 0xb6, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xb7: mov 0xb7, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xb8: mov 0xb8, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xb9: mov 0xb9, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xba: mov 0xba, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xbb: mov 0xbb, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xbc: mov 0xbc, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xbd: mov 0xbd, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xbe: mov 0xbe, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xbf: mov 0xbf, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xc0: mov 0xc0, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xc1: mov 0xc1, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xc2: mov 0xc2, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xc3: mov 0xc3, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xc4: mov 0xc4, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xc5: mov 0xc5, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xc6: mov 0xc6, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xc7: mov 0xc7, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xc8: mov 0xc8, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xc9: mov 0xc9, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xca: mov 0xca, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xcb: mov 0xcb, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xcc: mov 0xcc, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xcd: mov 0xcd, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xce: mov 0xce, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xcf: mov 0xcf, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xd0: mov 0xd0, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xd1: mov 0xd1, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xd2: mov 0xd2, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xd3: mov 0xd3, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xd4: mov 0xd4, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xd5: mov 0xd5, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xd6: mov 0xd6, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xd7: mov 0xd7, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xd8: mov 0xd8, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xd9: mov 0xd9, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xda: mov 0xda, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xdb: mov 0xdb, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xdc: mov 0xdc, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xdd: mov 0xdd, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xde: mov 0xde, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xdf: mov 0xdf, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xe0: mov 0xe0, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xe1: mov 0xe1, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xe2: mov 0xe2, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xe3: mov 0xe3, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xe4: mov 0xe4, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xe5: mov 0xe5, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xe6: mov 0xe6, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xe7: mov 0xe7, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xe8: mov 0xe8, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xe9: mov 0xe9, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xea: mov 0xea, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xeb: mov 0xeb, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xec: mov 0xec, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xed: mov 0xed, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xee: mov 0xee, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xef: mov 0xef, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xf0: mov 0xf0, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xf1: mov 0xf1, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xf2: mov 0xf2, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xf3: mov 0xf3, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xf4: mov 0xf4, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xf5: mov 0xf5, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xf6: mov 0xf6, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xf7: mov 0xf7, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xf8: mov 0xf8, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xf9: mov 0xf9, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xfa: mov 0xfa, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xfb: mov 0xfb, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xfc: mov 0xfc, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xfd: mov 0xfd, %g5; restore; ta 0; nop; \n\t\
SW_trap_0xfe: mov 0xfe, %g5; restore; ta 0; nop;");


