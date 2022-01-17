#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t next = 0;

uint32_t myrand(void) {
	next = next * 1103515245 + 12345;
	return(next);
}

void mysrand(uint32_t seed) {
	next = seed;
}

void primeMemory (uint32_t START_ADDRESS, uint32_t END_ADDRESS)
{
	uint32_t ptr = START_ADDRESS;
	while(ptr < END_ADDRESS)
	{
		*((uint32_t*)ptr) = 0xffffffff;
		ptr += 4;
	}
}

int runSweep (int I, uint32_t BLOCK_SIZE, uint32_t START_ADDRESS, uint32_t END_ADDRESS)
{
	ee_printf("Info: entering runSweep(0x%x, 0x%x, 0x%x, 0x%x)\n", 
				I, BLOCK_SIZE, START_ADDRESS, END_ADDRESS);

	// fill known values into each location.
	primeMemory (START_ADDRESS, END_ADDRESS);

	int ret_val =0;
	int J;
	int NSTEPS = (BLOCK_SIZE >> 2);

	// write into lots of random addresses. 
	for(J = 0; J < NSTEPS; J += 1)
	{
		uint32_t OFFSET = ((myrand()  << 2) & (BLOCK_SIZE-1));
		uint32_t ADDR = START_ADDRESS + OFFSET;

		uint32_t B;

		//ee_printf("Info: writing into 0x%x.\n", ADDR);

		*((uint32_t*) ADDR) = ADDR + I;
		B = *((uint32_t*) ADDR);

		// read back immediately to check..
		if(B != (ADDR + I))
			ret_val = 1;
	}

	// read back..
	for(J = 0; J < NSTEPS; J += 1)
	{
		uint32_t OFFSET = ((myrand()  << 2) & (BLOCK_SIZE-1));
		uint32_t ADDR = START_ADDRESS + OFFSET;

		uint32_t B = *((uint32_t*) ADDR);
		if((B != (ADDR + I)) && (B != 0xffffffff))
		{
			ee_printf("Error: in runSweep 0x%x = *(0x%x), expected 0x%x.\n",
					B, ADDR, ADDR+I);
			ret_val = 1;
		}
	}

	return(ret_val);
}
