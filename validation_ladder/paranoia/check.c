#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <setjmp.h>
#include <cortos.h>

int check ()
{
	// V9 = 0xfff0000000000000
        // Y=-8.98846567431059984e+307
	// 0xffe0000000000000
	
	double V9;
	*((uint64_t*) &V9) = 0xfff0000000000000;

	double Z = V9;

	double Y;
	*((uint64_t*) &Y) = 0xffe0000000000000;

	double V;
	*((uint64_t*) &V) = 0xffd0000000000000;

	V9 = -Y;
	double V0 =  V9;


	double U  = V - Y;
	double W  = V + V0;

	cortos_printf( "V=%.17e\n", V);
	cortos_printf( "Y=%.17e\n, 0x%llx\n", Y, *((uint64_t*) &Y));
	cortos_printf( "Z=%.17e, 0x%llx\n", Z, *((uint64_t*) &Z));
	cortos_printf( "V9=%.17e\n", Y);
	cortos_printf( "U=%.17e\n", U);
	cortos_printf( "W=%.17e\n", W);

	if(Z != Y)
		cortos_printf("Bad: Not equal\n");
	else
		cortos_printf("Good: Equal\n");

	return(0);
}

