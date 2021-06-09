#include <stdint.h>
#include <stdlib.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "math.h" 

void run_test(int length, unsigned int* arr1, unsigned int* arr2, double* t);

unsigned int *array_1 = (unsigned int *) 0x400A0000; //index: 0x00 
unsigned int *array_2 = (unsigned int *) 0x40089000; //index: 0x040

void run_test(int length, unsigned int* arr1, unsigned int* arr2, double* t)
{
	uint64_t start_time  = __ajit_get_clock_time();					
	int i;int err=0;

	for(i = 0; i < length; i++)
	{
		__ajit_store_word_mmu_bypass__((uint32_t) i,(uint32_t) (arr1 + i));
		__ajit_store_word_mmu_bypass__((uint32_t) i,(uint32_t) (arr2 + i));
	}
	uint64_t end_time  = __ajit_get_clock_time();					
	*t = ((double) (end_time - start_time)) * 1.0e-8;
}

int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);

	ee_printf("Starting \n");
	int i;
	double t;

	run_test (256, array_1, array_2, &t);
	ee_printf("For 256 bypass stores, time elapsed is t=%f seconds\n", t);

	return(1);
}


