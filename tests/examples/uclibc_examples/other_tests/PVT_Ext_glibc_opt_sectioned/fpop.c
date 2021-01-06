#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

#ifdef AJIT
#define PRINTF ee_printf
#else
#define PRINTF printf
#endif

inline void sqrt_ajit_asm_double (uint32_t a, uint32_t b)
{
        __asm__ __volatile__ ( "ldd [%0], %%f0 " : : "r" (a): );
	__asm__ __volatile__ ( "fsqrtd %f0, %f2 " );
	__asm__ __volatile__ ( "std %%f2, [%0]" : : "r" (b) : );


}

inline void sqrt_ajit_asm_single (uint32_t a, uint32_t b)
{
        __asm__ __volatile__ ( "ld [%0], %%f0 " : : "r" (a): );
	__asm__ __volatile__ ( "fsqrts %f0, %f2 " );
	__asm__ __volatile__ ( "st %%f2, [%0]" : : "r" (b) : );

}
