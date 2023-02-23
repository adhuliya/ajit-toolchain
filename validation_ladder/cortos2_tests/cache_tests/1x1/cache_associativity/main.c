#include <stdint.h>
#include <stdio.h>
#include <core_portme.h>
#include <ajit_access_routines.h>
#include <cortos.h>

// fits into the cache..
#define NWORDS  (8*1024)
#define CACHE_SIZE_IN_BYTES  (32*1024)

// 32 KB  + 32 KB
//   base address should have bits 14:6 0.
uint32_t  test_array[16*1024]  __attribute__ ((aligned(64*1024)));

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

	uint32_t set_way_size_in_bytes = 64 * 512/A;

	while(nreps > 0)
	{
		nreps--;

		// write in low way and then in high way..
		for(I = 0; I < set_way_size_in_bytes; I += 4)
		{
			test_array[(I >> 2)] = I;
			test_array[(I + CACHE_SIZE_IN_BYTES) >> 2] = I + CACHE_SIZE_IN_BYTES;
		}

		// read back from low way and then in high way..
		for(I = 0; I < set_way_size_in_bytes; I += 4)
		// across all sets.
		{
			int J = test_array[(I >> 2)];
			int K = test_array[(I + CACHE_SIZE_IN_BYTES) >> 2];

			if((J != I) || (K != (I + CACHE_SIZE_IN_BYTES)))
				err = 1;
		}

		nreps--;
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

		cortos_printf ("%d  %f\n", A, t/NREPS);
	}
	cortos_printf("Cacheable marches... done.\n");
	return(0);
}

