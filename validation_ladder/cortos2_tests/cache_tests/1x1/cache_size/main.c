#include <stdint.h>
#include <stdio.h>
#include <core_portme.h>
#include <ajit_access_routines.h>
#include <cortos.h>


// up to 64 KB
uint32_t  test_array[16*1024];

int runMarch (uint32_t start_addr, uint32_t nwords, int nreps, double* t)
{
	int err = 0;
	uint64_t tstart = cortos_get_clock_time();
	while (nreps > 0)
	{
		uint32_t I;
		for(I = 0; I < nwords; I++)
		{
			uint32_t* addr = (uint32_t*) (start_addr + (nwords << 2));
			*addr = I;
		}
		for(I = 0; I < nwords; I++)
		{
			uint32_t* addr = (uint32_t*) (start_addr + (nwords << 2));
			if(*addr != I)
				err = 1;
		}
	}
	uint64_t tend = cortos_get_clock_time();

	*t = ((double) (tend - tstart))/((double) CLK_FREQUENCY);
	return(err);
}

int main_00 ()
{

	uint32_t size;
	cortos_printf("Cacheable marches...\n");
	for(size = 256; size <= (16*1024); size = size*2)
	{
		double t;
		int err =  runMarch ((uint32_t) test_array, size, NREPS, &t);
		if(err)
			cortos_printf("Error: runMarch (C) size=%d.\n", size);

		cortos_printf ("C  %d  %f\n", size, t/NREPS);
	}
	cortos_printf("Cacheable marches... done.\n");

	cortos_printf("Non-cacheable marches...\n");
	for(size = 256; size <= (16*1024); size = size*2)
	{
		double t;
		int err =  runMarch ((uint32_t) NCRAM_BASE, size, NREPS, &t);
		if(err)
			cortos_printf("Error: runMarch (N) size=%d.\n", size);

		cortos_printf ("N  %d  %f\n", size, t/NREPS);
	}
	cortos_printf("Non-cacheable marches... done.\n");

	return(0);
}

