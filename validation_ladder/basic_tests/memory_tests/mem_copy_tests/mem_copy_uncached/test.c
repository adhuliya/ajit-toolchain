#include <stdint.h>
#include <stdlib.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "math.h" 


// 2X the cache size.
uint32_t src_array [ 64 * 1024 ];
uint32_t dest_array[ 64 * 1024 ];

int init_src_array()
{
	int i;
	for(i = 0; i < 64*1024; i++)
	{
		src_array[i] = i;
	}
}


int run_test(int length, int NREPS, double* t)
{
	int err = 0;
	uint64_t start_time  = __ajit_get_clock_time();					
	int i;

	for(i = 0; i < NREPS; i++)
	{
		memcpy((void*) dest_array, (void*) src_array, length*4);
	}

	uint64_t end_time  = __ajit_get_clock_time();					
	*t = ((double) (end_time - start_time)) * 1.0e-8;

	for(i = 0; i < length; i++)
	{
		if(dest_array[i] != i)
			err = 1;
	}

	return (err);
}

