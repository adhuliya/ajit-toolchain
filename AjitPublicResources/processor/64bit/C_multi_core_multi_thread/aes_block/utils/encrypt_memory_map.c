#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "aes_block.h"
#include "aes_utils.h"

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		fprintf(stderr,"Usage: %s raw-mmap-file encrypted-mmap-file\n", argv[0]);
		return(1);
	}

	// read the input raw mmap file, organize chunks of 16-byte double words, encrypt double
	// word and dump into output encrypted mmap file.
	
}


