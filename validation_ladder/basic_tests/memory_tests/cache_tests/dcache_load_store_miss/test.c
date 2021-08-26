#include <stdint.h>
#include <stdlib.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "math.h" 

//cache lines kept same to create conflicts resulting in mandatory misses
uint32_t* array_1 = 0x40044000; //index: 0x100 
uint32_t* array_2 = 0x40084000; //index: 0x100
 
void init_src_array()
{
	int i;
	for(i = 0; i < LENGTH; i++)
	{
		*(array_1 + i) = i;
		*(array_2 + i) = LENGTH-i;
	}
}

int run_test(int length, int* k, double* t)
{
	int err = 0;
	uint64_t start_time  = __ajit_get_clock_time();					
	int i;
	int iterations=1;
	int value1, value2;
	for(i = 0; i < length; i++)
	{
		value1=array_1[i];
		value2=array_2[length-i];
		if(value1 != value2) 
		{
		err=i;
		}	
		else 
		{
			iterations++;
		}
	}

	*k = iterations;
	uint64_t end_time  = __ajit_get_clock_time();					
	*t = ((double) (end_time - start_time)) * 1.0e-8;

	return (err);
}

