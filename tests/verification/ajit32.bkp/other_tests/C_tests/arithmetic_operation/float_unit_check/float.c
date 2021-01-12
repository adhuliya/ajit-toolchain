//Author:Asha Devi
//This program tests the floating point operations and generates a
//signature.
//Modified by Aswin Jith S (13 April 2017)


#include <stdint.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "sparc_stdio.h"
#include"Ajit_Hardware_Configuration.h"

#define STACK_POINTER 0x00003000

uint32_t  __attribute__((section(".text.main")))  main()
{
	//Initialize all registers
	__asm__ __volatile__( "set 0x10E0 ,%l0 \n\t");
	__asm__ __volatile__( "wr %l0,%psr \n\t");
	__asm__ __volatile__( "nop          \n\t");
	__asm__ __volatile__( "nop          \n\t");
	__asm__ __volatile__( "nop          \n\t");

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
	
	int window=0;
	for(window=0;window<7;window++)
	{
		__asm__ __volatile__( "save\n\t "); 

	__asm__ __volatile__( "clr %g0 \n\t "); __asm__ __volatile__( "clr %g1 \n\t ");
	__asm__ __volatile__( "clr %g2 \n\t "); __asm__ __volatile__( "clr %g3 \n\t ");
	__asm__ __volatile__( "clr %g4 \n\t "); __asm__ __volatile__( "clr %g5 \n\t ");
	__asm__ __volatile__( "clr %g6 \n\t ");__asm__ __volatile__( "clr %g7 \n\t ");

	__asm__ __volatile__( "clr %l0 \n\t "); __asm__ __volatile__( "clr %l1 \n\t ");
	__asm__ __volatile__( "clr %l2 \n\t "); __asm__ __volatile__( "clr %l3 \n\t ");
	__asm__ __volatile__( "clr %l4 \n\t "); __asm__ __volatile__( "clr %l5 \n\t ");
	__asm__ __volatile__( "clr %l6 \n\t "); __asm__ __volatile__( "clr %l7 \n\t ");

	__asm__ __volatile__( "clr %i0 \n\t "); __asm__ __volatile__( "clr %i1 \n\t ");
	__asm__ __volatile__( "clr %i2 \n\t "); __asm__ __volatile__( "clr %i3 \n\t ");
	__asm__ __volatile__( "clr %i4 \n\t "); __asm__ __volatile__( "clr %i5 \n\t ");
	__asm__ __volatile__( "clr %i6 \n\t "); __asm__ __volatile__( "clr %i7 \n\t ");

	__asm__ __volatile__( "clr %o0 \n\t "); __asm__ __volatile__( "clr %o1 \n\t ");
	__asm__ __volatile__( "clr %o2 \n\t "); __asm__ __volatile__( "clr %o3 \n\t ");
	__asm__ __volatile__( "clr %o4 \n\t "); __asm__ __volatile__( "clr %o5 \n\t ");
	__asm__ __volatile__( "clr %o6 \n\t ");__asm__ __volatile__( "clr %o7 \n\t ");
		

	}

	for(window=0;window<7;window++)
	{
		__asm__ __volatile__( "restore\n\t "); 
	}
	__asm__ __volatile__( "set ZERO,%l0  \n\t");
	__asm__ __volatile__( "ldd [%l0],%f0 \n\t");
	__asm__ __volatile__ ("\
		.align 8;\
		ZERO : .double \
	");
//////////////////////////////////////////clear all FPU registers//////////////////////////////////

	__asm__ __volatile__( "fmovs %f0,%f1 \n\t "); __asm__ __volatile__( "fmovs %f0,%f2 \n\t ");
	__asm__ __volatile__( "fmovs %f0,%f3 \n\t "); __asm__ __volatile__( " fmovs %f0,%f4 \n\t ");
	__asm__ __volatile__( "fmovs %f0,%f5  \n\t "); __asm__ __volatile__( "fmovs %f0,%f6 \n\t ");
	__asm__ __volatile__( "fmovs %f0,%f7  \n\t ");
	
	__asm__ __volatile__( "fmovs %f0,%f8 \n\t "); __asm__ __volatile__( "fmovs %f0,%f9 \n\t ");
	__asm__ __volatile__( "fmovs %f0,%f10 \n\t "); __asm__ __volatile__( "fmovs %f0,%f11 \n\t ");
	__asm__ __volatile__( "fmovs %f0,%f12 \n\t "); __asm__ __volatile__( "fmovs %f0,%f13 \n\t ");
	__asm__ __volatile__( "fmovs %f0,%f14\n\t "); __asm__ __volatile__( "fmovs %f0,%f15 \n\t ");
	
	__asm__ __volatile__( "fmovs %f0,%f16 \n\t "); __asm__ __volatile__( "fmovs %f0,%f17 \n\t ");
	__asm__ __volatile__( "fmovs %f0,%f18 \n\t "); __asm__ __volatile__( "fmovs %f0,%f19 \n\t ");
	__asm__ __volatile__( "fmovs %f0,%f20 \n\t "); __asm__ __volatile__( "fmovs %f0,%f21 \n\t ");
	__asm__ __volatile__( "fmovs %f0,%f22 \n\t "); __asm__ __volatile__( " fmovs %f0,%f23 \n\t ");
	
	__asm__ __volatile__( "fmovs %f0,%f24 \n\t "); __asm__ __volatile__( "fmovs %f0,%f25 \n\t ");
	__asm__ __volatile__( "fmovs %f0,%f26 \n\t "); __asm__ __volatile__( "fmovs %f0,%f27 \n\t ");
	__asm__ __volatile__( "fmovs %f0,%f28 \n\t "); __asm__ __volatile__( "fmovs %f0,%f29\n\t ");
	__asm__ __volatile__( "fmovs %f0,%f30 \n\t "); __asm__ __volatile__( "fmovs %f0,%f31\n\t ");
	//store base of trap table in TBR register
	__asm__ __volatile__("set trap_table_base, %l0 \n\t");
	__asm__ __volatile__("wr	%l0, 0x0, %tbr \n\t");
	__asm__ __volatile__("nop	\n\t"); //insert nops here because
	__asm__ __volatile__("nop	\n\t");// writes to tbr may be delayed
	__asm__ __volatile__("nop	\n\t");
	__asm__ __volatile__("mov 0xBAD, %g5 \n\t");



	//Setting up Stack Pointer and Frame Pointer
	__asm__ __volatile__("mov %0, %%sp\n\t" : : "r"(STACK_POINTER));
        __asm__ __volatile__("mov %0, %%fp\n\t" : : "r"(STACK_POINTER));
	

//////////////////////////double precision////////////////////////////////
	uint64_t a1 =0xabcd12347890cdfe;
	uint64_t b1 =0x567898872abcd123;
	
	uint64_t ea1,fa1,eb1,fb1;
	uint64_t c1,d1;
	uint64_t j;
	int n = 10;
	for (j=0;j<n;j++)
	{
		a1=((((a1>>63)^(a1>>62)^(a1>>61)^(a1>>60)^a1)&1)<<63)|(a1>>1);
		b1=((((b1>>63)^(b1>>62)^(b1>>61)^(b1>>60)^b1)&1)<<63)|(b1>>1);
	
		ea1=(a1 & 0x7FF0000000000000)>>52;
		fa1=(a1 & 0x000FFFFFFFFFFFFF);
		//sa1=(a1 & 0x8000000000000000)>>63;
		eb1=(b1 & 0x7FF0000000000000)>>52;
		fb1=(b1 & 0x000FFFFFFFFFFFFF);
		
	//keeping legal combination
	if(ea1==0)ea1=1;if(eb1==0)eb1=1;//if e=0 2^(1-1023) instead of 2^(-1023)
	if(ea1<2047 && eb1<2047 && fa1!=0 && fb1 !=0 && (ea1+eb1-2046)<1023 && (ea1-eb1)<1023 )
	{

    	__asm__ __volatile__("set C, %o2 \n\t ");
	__asm__ __volatile__("set D, %o4 \n\t ");
	__asm__ __volatile__("std %1,[%%o2];" : "=r"(c1) : "r"(a1));
	__asm__ __volatile__("ldd [%o2],%f0\n\t");
	__asm__ __volatile__("std %1,[%%o4];" : "=r"(d1) : "r"(b1) );
	__asm__ __volatile__("ldd [%o4],%f2\n\t");
	/*if(sa1==0)
	 {
		 __asm__ __volatile__("fsqrtd %f0,%f30 \n\t");//square-root
	}*/
	__asm__ __volatile__("faddd %f0,%f2,%f14\n\t");//add
	__asm__ __volatile__("fmuld %f14,%f2,%f16\n\t");//mul
	__asm__ __volatile__("fsubd %f16,%f14,%f18\n\t");//sub
	//__asm__ __volatile__("fdivd %f16,%f18,%f20\n\t");//div
	
	__asm__ __volatile__("std %f18,[%i2]   \n\t");
	__asm__ __volatile__("ldd [%i2],%l4 \n\t ");
	__asm__ __volatile__("xor %l5,%g4,%g4 \n\t");//signature
	__asm__ __volatile__("xor %l4,%g7,%g7 \n\t");//signature
	

	}
	}
	///////////////////////////////single precision////////////////////////////////
	uint32_t a=0xf95cdb48;
	uint32_t b=0xbe6f2115;
	uint32_t c,d;
	uint32_t ea,fa,eb,fb,sa;
	int n1=10;
	int i;
	
	for(i=0;i<n1;i++)
	{
	//lfsr
	a=((((a>>31)^(a>>6)^(a>>4)^(a>>1)^a)&1)<<31)|(a>>1);
	b=((((b>>31)^(b>>6)^(b>>4)^(b>>1)^b)&1)<<31)|(b>>1);
	
	ea=(a & 0x7F800000)>>23;fa=(a & 0x007FFFFF);sa=(a & 0x80000000)>>31;
	eb=(b & 0x7F800000)>>23;fb=(b & 0x007FFFFF);

	//keeping legal combinations
	if(ea==0)ea=1;if(eb==0)eb=1;//if e=0 2^(1-127) instead of 2^(-127)
	if(ea<255 && eb<255 && fa!=0 && fb !=0 && (ea+eb-254)<127 && (ea-eb)<127)
	{
    	__asm__ __volatile__("set A, %l1 \n\t ");
	__asm__ __volatile__("set B, %l2 \n\t ");


	__asm__ __volatile__("st %1,[%%l1];" : "=r"(c) : "r"(a) );
	__asm__ __volatile__("ld [%l1],%f4\n\t");
	
	__asm__ __volatile__("st %1,[%%l2];" : "=r"(d) : "r"(b) );
	__asm__ __volatile__("ld [%l2],%f5\n\t");
	if(sa==0)
	{
	__asm__ __volatile__("fsqrts %f4,%f28 \n\t");//square-root
	
   	 }
   	 __asm__ __volatile__("fadds %f28,%f5,%f6  \n\t");//addition
    	__asm__ __volatile__("fmuls %f6,%f5,%f7  \n\t");//multiplication
	__asm__ __volatile__("fsubs %f7,%f6,%f8  \n\t");//subtraction
	__asm__ __volatile__("fdivs %f7,%f8,%f9  \n\t");//division
	__asm__ __volatile__("st %f9,[%i4]   \n\t");
	__asm__ __volatile__("ld [%i4],%g6 \n\t ");
	__asm__ __volatile__("xor %g6,%i7,%i7 \n\t");//signature
	
	}
}

	__asm__ __volatile__ ("\
		.align 4;\
        A : .single;\
	B : .single;\
	");	

	__asm__ __volatile__ ("\
		.align 8;\
	C : .double ;\
	D : .double ;\
	");
		
	halt();
	return 0;


}

//============================================
// Trap Table
//In the trap handler, we push the trap_number into %g5
//and return to the instruction following the trapped one.
//The Trap Table must be aligned to a page(4096 Bytes)
//============================================


__asm__ (".align 4096; \n\t\
trap_table_base:\n\t\
HW_trap_0x00: mov 0x00, %g5; restore; ta 0; nop; ! Reset                                   \n\t\
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
