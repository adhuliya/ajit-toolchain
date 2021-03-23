#include <stdint.h>
#include <stdlib.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "math.h" 

uint32_t* array_1 = 0x40044000; //index: 0x100 
uint32_t* array_2 = 0x40089000; //index: 0x040
uint32_t* comparison = 0x400cdc00; //index: 0x170 

int init_src_array()
{
	int i;
	for(i = 0; i < 256; i++)
	{
		*(array_1 + i) = i;
		*(array_2 + i) = 256-i;
		*(comparison + i) = NULL;
	}
}

int run_test(int length, double* t, int* result)
{
	int err = 0;
	uint64_t start_time  = __ajit_get_clock_time();					
	int i;int k=0;

	for(i = 0; i < length; i++)
	{
		if(array_1[i] != array_2[(length)-i])
		{
		err=i;
		}
		else
		{
			comparison[i]=k;
			k++;
			*result = k;
		}
	}	

	uint64_t end_time  = __ajit_get_clock_time();					
	*t = ((double) (end_time - start_time)) * 1.0e-8;

	return (err);
}

