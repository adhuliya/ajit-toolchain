#include <stdint.h>
#include <stdlib.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "math.h" 

uint32_t* array_1 = 0x40044000; //index: 0x100
uint32_t* array_2 = 0x40089000; //index: 0x040

int init_src_array()
{
	int i;
	for(i = 0; i < LENGTH; i++)
	{
		*(array_1 + i) = i;
		*(array_2 + i) = LENGTH-i;
	}
}
 
int run_test(int length, double* t, int* result)
{
	int err = 0;
	uint64_t start_time  = __ajit_get_clock_time();					
	int i;int k=0;
	int value1, value2;

	for(i = 0; i < length; i++)
	{
			value1 = array_1[i];
			value2 = array_2[(length)-i];
		if(value1 != value2)
		{
		err=i;
		}
		else
		{
			k++;
			*result = k;
		}
	}	

	uint64_t end_time  = __ajit_get_clock_time();					
	*t = ((double) (end_time - start_time)) * 1.0e-8;

	return (err);
}

