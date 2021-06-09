#include <stdint.h>
#include <stdlib.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "math.h" 

int run_test(int length, unsigned int* arr1, unsigned int* arr2, double* t);

unsigned int *array_1 = (unsigned int *) 0x400A0000; //index: 0x00 
unsigned int *array_2 = (unsigned int *) 0x40089000; //index: 0x040

int run_test(int length, unsigned int* arr1, unsigned int* arr2, double* t)
{
	int loads = 0;
	int status = 0;
	int i;int k=0;

	// initialize the memory arrays using some standard values
	// e.g. array_1[I] = 2*I
	//      array_2[I] = (2*I)+1
	//
	for(i = 0; i < length; i++)
	{
		__ajit_store_word_mmu_bypass__((uint32_t) (2*i),(uint32_t) (arr1 + i));
		__ajit_store_word_mmu_bypass__((uint32_t) ((2*i)+1),(uint32_t) (arr2 + i));
	}

	uint64_t start_time  = __ajit_get_clock_time();					

	for(i = 0; i < length; i++)
	{
		//only to perform load operations, these values wont match
		uint32_t val1 = __ajit_load_word_mmu_bypass__((uint32_t) (arr1 + i));
		uint32_t val2 = __ajit_load_word_mmu_bypass__((uint32_t) (arr2 + i));

		// val1 must be even and val2 must be odd.
		status = !(((~val1) & 0x1) && (val2 & 0x1)) || status;
		if(!status)
		{
		}
	}
	uint64_t end_time  = __ajit_get_clock_time();					
	*t = ((double) (end_time - start_time)) * 1.0e-8;

	return(status);
}


int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);


	ee_printf("Starting \n");
	int err = 0;
	int i;
	double t;

	// this should return a 0 on success.
	int status = run_test (256, array_1, array_2, &t);
	if(!status)
		ee_printf("Success! for 256 bypass loads, time elapsed is t=%f seconds\n", t);
	else
		ee_printf("Error: Failure! for 256 bypass loads, time elapsed is t=%f seconds\n", t);

	return(status);
}


