#include <stdint.h>
#include <stdio.h>
#include <core_portme.h>
#include <ajit_access_routines.h>
#include <rng_marsaglia.h>

int main_00 ()
{

	uint32_t seed = 191;
	cortos_printf("seed=0x%x\n", seed);

	int I;
	for(I = 0; I < 100; I++)
	{
		double v = ajit_marsaglia_rng (&seed);
		cortos_printf ("0x%x %f\n", seed, v);
	}	

	return(0);
}

