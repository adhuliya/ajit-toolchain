#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"

double elapsed_time = 0.0;
inline void halt()
{
	__asm__ __volatile__("ta 0; nop; nop;");
}


// initialize f16-f19 with contents of address a.
inline void initSumRegs (uint32_t a) 
{
	__asm__ __volatile__ ( "ld [%0], %%f16;"
				"fmovs %%f16, %%f17;"
				"fmovs %%f16, %%f18;"
				"fmovs %%f16, %%f19;"
				:
				: "r"(a) : );
}

// final sum of f16-f19 into location pointed to by a.
inline void finalSum (uint32_t a) 
{
	__asm__ __volatile__ ( 
				"fadds %%f16, %%f17, %%f0;"
				"fadds %%f18, %%f19, %%f1;"
				"fadds %%f0, %%f1, %%f0;"
				"st %%f0, [%0];"
				: 
				: "r"(a)
				:);
}


// registers 16,17,18,19 for running sums.
inline void dot8 (uint32_t a, uint32_t b)
{
	__asm__ __volatile__(
				 "ldd [%0], %%f0; "
				 "ldd [%1], %%f2; "
				 "ldd [%0 + 0x8], %%f4; "
				 "ldd [%1 + 0x8], %%f6;" 
				 "ldd [%0 + 0x10], %%f8; "
				 "ldd [%1 + 0x10], %%f10; "
				 "ldd [%0 + 0x18], %%f12; "
				 "ldd [%1 + 0x18], %%f14;" 
				 "fmuls %%f0, %%f2, %%f0;"
				 "fmuls %%f1, %%f3, %%f1;"
				 "fmuls %%f4, %%f6, %%f2;"
				 "fmuls %%f5, %%f7, %%f3;"
				 "fmuls %%f8, %%f10, %%f4;"
				 "fmuls %%f9, %%f11, %%f5; "
				 "fmuls %%f12, %%f14, %%f6;"
				 "fmuls %%f13, %%f15, %%f7;"
				 "fadds %%f16, %%f0, %%f16;"
				 "fadds %%f17, %%f2, %%f17;"
				 "fadds %%f18, %%f4, %%f18;"
				 "fadds %%f19, %%f6, %%f19;"
				 "fadds %%f16, %%f1, %%f16;"
				 "fadds %%f17, %%f3, %%f17;"
				 "fadds %%f18, %%f5, %%f18;"
				 "fadds %%f19, %%f7, %%f19;"
 				:
				: "r" (a), "r" (b)
				:);
			
}


// defined at compile time.. #define VECTORSIZE 

float a[VECTORSIZE] __attribute__ ((aligned(8)));
float b[VECTORSIZE] __attribute__ ((aligned(8)));

void vectorGen();

#ifndef AJIT
#include <stdio.h>
#endif

void run_test (float* S)
{

    vectorGen();
    int i,j; 

    uint32_t pS = (uint32_t) S;

    ee_printf("run_test (0x%x).\n", pS);
// NITERATIONS defined at compile time...
    uint32_t ival = 0;

    uint64_t t0 = __ajit_get_clock_time();

    initSumRegs((uint32_t) &ival);
    for(j = 0; j < NITERATIONS; j++)
    {
	for (i = 0; i < VECTORSIZE; i += 8) 
	{
		uint32_t pa = (uint32_t) &(a[i]);
		uint32_t pb = (uint32_t) &(b[i]);
		dot8 (pa, pb);
	}
	finalSum (pS);
    }

    uint64_t t1 = __ajit_get_clock_time();
    elapsed_time = ((double) (t1 - t0))/CLK_FREQUENCY;

}


#define ASI_MMU_REGISTER                0x04
inline void store_word_mmureg(uint32_t value, uint32_t* addr)
{
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
			"i"(ASI_MMU_REGISTER) : "memory");
}


int ajit_main(void)
{	
	store_word_mmureg(0x100,(uint32_t*) 0x0);
	__ajit_write_serial_control_register__ (TX_ENABLE);

	ee_printf("Hello.\n");

	float S = 0.0;

	run_test(&S);
	ee_printf("Final sum = %14f.\n", S);


	ee_printf("Elapsed time=%14f, MFLOPS=%f\n", 
				elapsed_time,
				((double) (2 * NITERATIONS * VECTORSIZE))/(elapsed_time * 1000000));

	return 0;
}
