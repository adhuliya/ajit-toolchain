#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <mmapToAssy.h>

uint8_t*  data_block        = NULL;
uint32_t  block_size_aligned_to_u64 = 0;
uint32_t  start_dest_address_aligned_to_u64 = 0;

uint32_t align_up_to_u64(uint32_t x)
{
	if((x&7) == 0)
	{
		return(x);
	}
	else
	{
		return( ((x >> 3)  + 1) << 3);
	}
}

uint32_t align_down_to_u64(uint32_t x)
{
	if((x%7) == 0)
	{
		return(x);
	}
	else
	{
		return((x >> 3) << 3);
	}
}



void printAssembly (FILE* out_file)
{
	
	fprintf(out_file,".section .text.copy_program_image_u64\n");
	fprintf(out_file,".global copy_program_image_u64\n");
	fprintf(out_file,"copy_program_image_u64:\n");
	fprintf(out_file,  "    save;\n");

			
	fprintf(out_file,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	fprintf(out_file,"    set DATA_SEGMENT_TO_COPY, %s\n", "%g3");
	fprintf(out_file,"!   length of data segment\n");
	fprintf(out_file,"    set %d, %s\n", block_size_aligned_to_u64, "%g4");
	fprintf(out_file,"!   starting destination address of data segment\n");
	fprintf(out_file,"    set 0x%x, %s\n", start_dest_address_aligned_to_u64, "%g5");
	fprintf(out_file,"!   call function defined in bootstrap.s \n");
	fprintf(out_file,"    call _copy_segment_u64\n");
	fprintf(out_file,"    nop\n");
	fprintf(out_file,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

	fprintf(out_file,  "    restore\n");
	fprintf (out_file, "    retl\n");
	fprintf (out_file, "    nop\n");

	fprintf(out_file,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	fprintf(out_file,"! Data segment, length=%d, starting_dest_addr=0x%x\n",
				 block_size_aligned_to_u64, start_dest_address_aligned_to_u64);
	fprintf(out_file,".align 8\n");
	fprintf(out_file,".global DATA_SEGMENT_TO_COPY\n");
	fprintf(out_file,"DATA_SEGMENT_TO_COPY:\n");

	int I;
	for(I = 0; I < block_size_aligned_to_u64; I++)
	{
		fprintf(out_file,".byte 0x%x\n", data_block[I]);
	}
	fprintf(out_file,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}

//
// generate assembly code to copy u64 to base-address + offset.
//
int main(int argc, char* argv[])
{


	FILE *in_file, *out_file;
	if(argc < 5) 
	{
		fprintf(stderr,"Usage: %s <in-file> <out-file> <base-address-value (0x...) > <block-size-in-bytes>\n", argv[0]);
		return(1);
	}

	in_file = fopen(argv[1],"r");
	if(in_file == NULL)
	{
		fprintf(stderr,"Error: could not open infile %s\n", argv[1]);
	}

	out_file = fopen(argv[2],"w");
	if(out_file == NULL)
	{
		fprintf(stderr,"Error: could not open outfile %s\n", argv[2]);
	}


	uint32_t saddr;
	sscanf (argv[3], "%x", &saddr);

	start_dest_address_aligned_to_u64 = align_down_to_u64 (saddr);
	fprintf(stderr,"Info: destination base address = 0x%x\n", start_dest_address_aligned_to_u64);

	uint32_t bsize;
	sscanf (argv[4], "%x", &bsize);
	block_size_aligned_to_u64 = align_up_to_u64 (bsize);
	fprintf(stderr,"Info: block size in bytes = 0x%x\n", block_size_aligned_to_u64);


	// allocate the data block.. zero it out.
	data_block = (uint8_t*)  calloc(1, (block_size_aligned_to_u64*sizeof(uint8_t)));


	char data_line[1024];
	uint32_t offset = 0;
	int line_id = 0;
	while(fgets(data_line,1023,in_file) != NULL)
	{
		line_id++;

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

		if(address >= start_dest_address_aligned_to_u64)
		{
			offset = address - start_dest_address_aligned_to_u64;
			if(offset < block_size_aligned_to_u64)
			{
				data_block[offset] = byte_val;
			}
			else
			{
				fprintf(stderr,"Error: line %d.. offset overflows data block.\n", line_id);
			}
		}
		else
		{
			fprintf(stderr,"Error: line %d.. address < start-address.\n", line_id);
		}
	}

	printAssembly(out_file);

	fclose(in_file);
	fclose(out_file);

	return(0);
}


