#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <assert.h>
#include "do_val.h"

void print_usage(char* pgm)
{
	fprintf(stderr,"%s <ncores> <nthreads> <init-pc> <mmap-file-name> <results-file-name> <output-file-name> <log-file-name> \n", pgm);
	return;
}

int main(int argc, char* argv [])
{
	if(argc < 8)
	{
		print_usage(argv[0]);
		return(1);
	}

	uint32_t ncores = atoi(argv[1]);
	fprintf(stderr,"ncores = 0x%x\n", ncores);

	uint32_t nthreads = atoi(argv[2]);
	fprintf(stderr,"nthreads (per core) = 0x%x\n", nthreads);

	uint32_t init_pc;
	sscanf(argv[3], "0x%x", &init_pc);
	fprintf(stderr,"init_pc = 0x%x (%s)\n", init_pc, argv[3]);

	fprintf(stderr,"mmap-file = %s\n", argv[4]);
	fprintf(stderr,"results-file = %s\n", argv[5]);
	fprintf(stderr,"output-file = %s\n", argv[6]);


	configureDumpAdm (ncores, nthreads, init_pc, argv[4], argv[6]);
	doval (NULL, argv[5], argv[7]);

	return(0);
}
