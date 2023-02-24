#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"

double elapsed_time = 0.0;
inline void halt()
{
	__asm__ __volatile__("ta 0; nop; nop;");
}


inline void daxpy8 (uint32_t a, uint32_t b, uint32_t c)
{
	__asm__ __volatile__(
				 "ld [%2], %%f31; "

				 "ldd [%0], %%f0; "
				 "ldd [%1], %%f8; "
				 "ldd [%0 + 0x8], %%f2; "
				 "ldd [%1 + 0x8], %%f10;" 
				 "ldd [%0 + 0x10], %%f4; "
				 "ldd [%1 + 0x10], %%f12; "
				 "ldd [%0 + 0x18], %%f6; "
				 "ldd [%1 + 0x18], %%f14;" 

				 "fmuls %%f31, %%f0, %%f0;"
				 "fmuls %%f31, %%f1, %%f1;"

				 "fmuls %%f31, %%f2, %%f2;"
				 "fmuls %%f31, %%f3, %%f3;"

				 "fmuls %%f31, %%f4, %%f4;"
				 "fmuls %%f31, %%f5, %%f5;"

				 "fmuls %%f31, %%f6, %%f6;"
				 "fmuls %%f31, %%f7, %%f7;"

				 "fadds %%f0, %%f8, %%f0;"
				 "fadds %%f1, %%f9, %%f1;"

				 "fadds %%f2, %%f10, %%f2;"
				 "fadds %%f3, %%f11, %%f3;"

				 "fadds %%f4, %%f12, %%f4;"
				 "fadds %%f5, %%f13, %%f5;"

				 "fadds %%f6, %%f14, %%f6;"
				 "fadds %%f7, %%f15, %%f7;"

				 "std %%f0, [%0]; "
				 "std %%f2, [%0+8]; "
				 "std %%f4, [%0+16]; "
				 "std %%f6, [%0+24]; "

 				:
				: "r" (a), "r" (b), "r" (c)
				: );
			
}


// defined at compile time.. #define VECTORSIZE 

float a[VECTORSIZE] __attribute__ ((aligned(8)));
float b[VECTORSIZE] __attribute__ ((aligned(8)));

void vectorGen();

#ifndef AJIT
#include <stdio.h>
#endif

void run_test (float c, float* S)
{

    vectorGen();
    int i,j; 

    uint32_t pS = (uint32_t) S;

    ee_printf("run_test (0x%x).\n", pS);
// NITERATIONS defined at compile time...
    uint32_t ival = 0;

    uint64_t t0 = __ajit_get_clock_time();

    uint32_t pc = (uint32_t) &c;
    for(j = 0; j < NITERATIONS; j++)
    {
	for (i = 0; i < VECTORSIZE; i += 8) 
	{
		uint32_t pa = (uint32_t) &(a[i]);
		uint32_t pb = (uint32_t) &(b[i]);
		daxpy8 (pa, pb, pc);
	}
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
	float scale_factor = 0.5;

	run_test(scale_factor, &S);

	int i;
	for(i = 0; i < VECTORSIZE; i++)
	{
		ee_printf("%f.\n", a[i]);
	}


	ee_printf("Elapsed time=%14f, MFLOPS=%f\n", 
				elapsed_time,
				((double) (3 * NITERATIONS * VECTORSIZE))/(elapsed_time * 1000000));

	return 0;
}
