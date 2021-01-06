#include <stdint.h>


//
// 32 kB.
//
uint64_t mem_array [NSIZE];

uint64_t mem_march (int n_iters)
{
	int I,J;
	uint64_t rval = 0;
	for(I= 0;  I < n_iters; I++)
	{
		for(J=0; J < NSIZE; J++)
		{
			mem_array[J] = (I + J);
		}

		for(J=0; J < NSIZE; J++)
		{
			rval = ((I+J) ^ mem_array[J]) | rval;
		}
	}
	return(rval);
}
