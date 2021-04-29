#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include "uarch_debug_utils.h"
#include "processor_link.h"
#include "pthreadUtils.h"
#include <stdio.h>


extern int global_verbose_flag;

// to be used to initialize memory through the debug
// interface..  This will be needed to test the FPGA
// prototype.
int axi_init_ram_base(int use_debug_flag, void* fpga, char* memoryMapFile)
{
	FILE * file;
	file= fopen(memoryMapFile, "r");
	if(!file)
	{
		#ifdef SW
		fprintf(stderr,"\n ERROR: file %s could not be opened for reading!\n",memoryMapFile);
		#endif
		return 0;
	}
	
	#ifdef DEBUG
	printf("\n opened memory map file %s\n",memoryMapFile);
	#endif
	uint32_t addr;
	uint32_t  data;
	int file_read=0;

	int number_of_bytes_read = 0;
	int current_word_address = -1;
	int current_read_word    = 0;

	while (1)
	{
		int eof_reached = 0;
		data = 0;
		
		file_read=fscanf(file, "%x", &addr);
		if (feof(file)) 
		{
			eof_reached = 1;
		}
		else
		{
			file_read=fscanf(file, "%x", &data);
		}

		if(number_of_bytes_read == 0)
		{
			current_word_address = (addr & 0xfffffffc);
			if(!eof_reached)
				current_read_word = (data <<  8*(3 - (addr & 0x3)));
		}

		if ((current_word_address != (addr & 0xffffffffc)) || (eof_reached))
		{
			uint32_t read_back;
			if(use_debug_flag)
			{
				dbg_write_mem(0x20, current_word_address, current_read_word);
				read_back = dbg_read_mem(0x20, current_word_address);
			}
			else
			{
				write_to_axi_dram(fpga, current_word_address, current_read_word);
				read_from_axi_dram(fpga, current_word_address,&current_read_word);
			}


			if(read_back != current_read_word)
				fprintf(stderr,"Error: read-back mem[0x%x] = 0x%x, expected 0x%x.\n",  
										current_word_address, 
										read_back,
										current_read_word);

			if(global_verbose_flag)
				fprintf(stderr,"Info: initialized mem[0x%x] = 0x%x.\n",  current_word_address,
										current_read_word);

			current_word_address = (addr & 0xfffffffc);
			current_read_word = (data <<  8*(3 - (addr & 0x3)));
		}
		else if (current_word_address == (addr & 0xffffffffc))
		{
			current_read_word = current_read_word | (data <<  8*(3 - (addr & 0x3)));
		}

		number_of_bytes_read++;

		if(eof_reached)
			break;

	}
	fprintf(stderr, "\n Finished initializing memory from file %s.\
			\nLast address written = %x.\n",memoryMapFile, addr);

	fclose(file);
	return 1;
	
}

int axi_init_ram(void* fpga, char* memoryMapFile)
{
	axi_init_ram_base(0, fpga, memoryMapFile);
}

int axi_init_ram_through_debug_interface(void* fpga, char* memoryMapFile)
{
	axi_init_ram_base(1, fpga, memoryMapFile);
}




