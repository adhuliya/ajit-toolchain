#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"


//
// 64 kB.
//
uint64_t mem_array [NSIZE];

uint64_t mem_march (int n_iters)
{
	int I,J;
	uint64_t rval = 0;
	for(I= 0;  I < n_iters; I++)
	{
		for(J=0; J < NSIZE; J += 4)
		{
			int K = I + J;
			mem_array[J] = (I + J);
			K++;
			mem_array[J+1] = K;
			K++;
			mem_array[J+2] = K;
			K++;
			mem_array[J+3] = K;
		}

		for(J=0; J < NSIZE; J += 4)
		{
			int K = I + J;
			rval = (K ^ mem_array[J]) | rval;
			K++;
			rval = (K ^ mem_array[J+1]) | rval;
			K++;
			rval = (K ^ mem_array[J+2]) | rval;
			K++;
			rval = (K ^ mem_array[J+3]) | rval;
		}
	}
	return(rval);
}


void print_array()
{
	int J;
	for(J=0; J < NSIZE; J ++)
	{
		uint32_t K = mem_array[J];
		ee_printf("mem_array[%u] = %u\n", J, K);
	}
}
