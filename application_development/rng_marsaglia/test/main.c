#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <rng_marsaglia.h>

// generate 100 random numbers using seed provided as argv[1].
int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s <seed>\n", argv[0]);
		return(1);
	}

	uint32_t seed = atoi(argv[1]);
	fprintf(stdout, "seed = 0x%x\n", seed);
	int I;
	for (I = 0; I < 100; I++)
	{
		double v = ajit_marsaglia_rng (&seed);
		fprintf(stdout, "0x%x %f\n", seed, v);
	}
	
}

