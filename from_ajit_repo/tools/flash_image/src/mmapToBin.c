#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <mmapToAssy.h>


//
// convert memory map file to binary.
//
int main(int argc, char* argv[])
{
	uint8_t* mem_array = NULL;
	FILE *in_file, *out_file;
	if(argc < 4) 
	{
		fprintf(stderr,"Usage: %s <log-of-mem-size> <in-file> <out-file>\n", argv[0]);
		fprintf(stderr,"  Example: %s 20 prog.mmap prog.bin\n", argv[0]);
		
		return(1);
	}

	int log_mem_size = atoi(argv[1]);
	if((log_mem_size < 0) || (log_mem_size > 24))
	{
		fprintf(stderr,"Error: argv[1] (log_mem_size) must be between 0 and 24, but is specified as %d\n", log_mem_size);
		return(1);
	}

	int mem_size = (1 << log_mem_size);
	mem_array = (uint8_t*) malloc (mem_size*sizeof(uint8_t));
	memset((void*)mem_array, 0, mem_size);	

	in_file = fopen(argv[2],"r");
	if(in_file == NULL)
	{
		fprintf(stderr,"Error: could not open infile %s\n", argv[2]);
	}

	// this is a bin file.
	out_file = fopen(argv[3],"wb");
	if(out_file == NULL)
	{
		fprintf(stderr,"Error: could not open outfile %s\n", argv[3]);
	}

	char data_line[1024];
	int line_number = 1;
  	while(fgets(data_line,1023,in_file) != NULL)
	{
		// comments start with !
		if(data_line[0] == '!') continue;

		char* addr_buf = strtok(data_line, " \t");
		if (addr_buf == NULL) break;

		uint32_t address = 0;
		sscanf (addr_buf, "%x", &address);

		char* data_buf = strtok(NULL, " \t");
		if (data_buf == NULL) break;
	
		uint32_t byte_val;	
		sscanf (data_buf, "%x", &byte_val);

		if(address < mem_size)
		{
			mem_array[address] = byte_val & 0xff;
		}
		else
		{
			fprintf(stderr,"Error: address 0x%x exceeds mem_size %d (line %d)\n", address, mem_size, line_number);
		}
		line_number++;
	}

	fwrite(mem_array,mem_size,1,out_file);

	fclose(in_file);
	fclose(out_file);

	return(0);
}


