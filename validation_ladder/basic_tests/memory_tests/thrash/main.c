#include<stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "core_portme.h"
#include "ajit_access_routines.h"
#include <math.h>

void mysrand(uint32_t seed);
uint32_t myrand(void);

void primeMemory (uint32_t START_ADDRESS, uint32_t END_ADDRESS);
int runSweep (int I, uint32_t BLOCK_SIZE, uint32_t START_PTR, uint32_t END_PTR);
int runTest(uint32_t START_ADDRESS, uint32_t END_ADDRESS);

int runTest(uint32_t START_ADDRESS, uint32_t END_ADDRESS)
{
		

	int err = 0;
	int I;

	uint32_t BLOCK_SIZE = (END_ADDRESS - START_ADDRESS);
	//uint32_t BLOCK_SIZE = 256;

	ee_printf("Info: starting runTest(0x%x, 0x%x), block size 0x%x\n", 
				START_ADDRESS, END_ADDRESS, BLOCK_SIZE);
	for(I = 1; I < NSWEEPS; I += 2)
	{
		// write a 0xffffffff into every location.
		//primeMemory (START_ADDRESS, END_ADDRESS);

		ee_printf("Info: starting sweep %d\n", I);
		err = runSweep (I, BLOCK_SIZE,  START_ADDRESS, END_ADDRESS) || err;
		if(err)
		{
			ee_printf("Sweep %d failed.\n", I);
		}
		else
		{
			ee_printf("Info: finished sweep %d\n", I);
		}
	}

	ee_printf("Info: finished runTest(0x%x, 0x%x)\n", START_ADDRESS, END_ADDRESS);
	return(err);
}

int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);

	mysrand (291);

	int err = runTest (0x42000000, 0x43000000);
	err     = runTest (0xf0000000, 0xf1000000);

	
	ee_printf("done\n");
	return(err);
}

