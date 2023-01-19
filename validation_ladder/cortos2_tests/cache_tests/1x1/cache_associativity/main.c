#include <stdint.h>
#include <stdio.h>
#include <core_portme.h>
#include <ajit_access_routines.h>
#include <cortos.h>

#define NWORDS  (8*1024)

// 32 KB
//   base address should have bits 14:6 0.
uint32_t  test_array[8*1024]  __attribute__ ((aligned(16*1024)));

/*
	32KB cache: with associativity A of 1/2/4/8/16.

	There are 512 lines.  Each set has room for 
	A lines.

	The number of sets  is S = 512/A.   The lines
	in set I are those with indices 
	I, I + S, I + 2S, ..., I + (A-1)S.

	So we iterate over S sets.. 
	 	For each set, write to A lines
		

*/
int runMarch (uint32_t start_addr, int A, int nreps, double* t)
{
	int err = 0;

	// number of sets.
	int S = 512/A;

	int I,J,K;
	uint64_t tstart = cortos_get_clock_time();

	while(nreps > 0)
	{
		nreps--;

		for(I = 0; I < S; I++)
		// across all sets.
		{
			for(J = 0; J < A; J++)
			// A lines in the set..
			{
				uint32_t line_index =  I + (J*S);
				uint32_t line_addr = (line_index  << 6);

				// write to line.
				for(K = 0; K < 16; K++)
				// each line has 16 words.
				{
					uint32_t t_index = (line_addr + (K << 2)) >> 2;
					test_array[t_index] = t_index;
					// CORTOS_DEBUG("Wrote to index %d.\n", t_index);
				}
			}
		}

		for(I = 0; I < S; I++)
		// across all sets.
		{
			for(J = 0; J < A; J++)
			{
				uint32_t line_index =  I + (J*S);
				uint32_t line_addr = (line_index  << 6);

				// write to line.
				for(K = 0; K < 16; K++)
				{
					uint32_t t_index = (line_addr + (K << 2)) >> 2;
					if(test_array[t_index] != t_index)
						err = 1;
				}
			}
		}


	}
	uint64_t tend = cortos_get_clock_time();
	*t = ((double) (tend - tstart))/((double) CLK_FREQUENCY);
	return(err);
}

int main_00 ()
{

	uint32_t size;
	cortos_printf("Cacheable marches... on test_array starting at 0x%x\n", (uint32_t) test_array);
	int A;
	for(A = 1; A <= 16; A = 2*A)
	{
		double t;
		int err =  runMarch ((uint32_t) test_array, A, NREPS, &t);
		if(err)
			cortos_printf("Error: runMarch A=%d.\n", A);

		cortos_printf ("%d  %f\n", size, t/NREPS);
	}
	cortos_printf("Cacheable marches... done.\n");
	return(0);
}

