#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pipeHandler.h>
#include <Pipes.h>
#include <uarch_debug_utils_ultra_lite.h>
#include <uart_interface.h>


extern uint32_t global_verbose_flag;

int dbg_load_mmap_ultra_lite(char* memoryMapFile)
{
	FILE * file;
	file= fopen(memoryMapFile, "r");
	if(!file)
	{
		#ifdef SW
		fprintf(stderr,"\n ERROR: file %s could not be opened for reading!\n",memoryMapFile);
		#endif
		return 1;
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
	int written_word_count = 0;

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

		uint32_t masked_addr = addr & 0xfffffffc;
		if ((current_word_address != masked_addr) || (eof_reached))
		{
			dbg_write_mem_ultra_lite(current_word_address, current_read_word);
			if(global_verbose_flag)
			{
				uint32_t read_back = dbg_read_mem_ultra_lite(current_word_address);
				fprintf(stderr,"Info: initialized mem[0x%x] = 0x%x.\n",  current_word_address,
										current_read_word);
				if(read_back != current_read_word)
					fprintf(stderr,"Error: read-back mem[0x%x] = 0x%x, expected 0x%x.\n",  
										current_word_address, 
										read_back,
										current_read_word);
			}


			current_word_address = masked_addr;
			current_read_word = (data <<  8*(3 - (addr & 0x3)));

			written_word_count++;

			if((written_word_count % 1024) == 0)
			{
				fprintf(stderr,"Info: initialized %d words..\n", written_word_count);
			}
		}
		else if (current_word_address == masked_addr)
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
	return 0;
}

uint32_t dbg_write_reset_ultra_lite(uint32_t rval)
{
	uint32_t cmd_val = (UL_RESET_OP << 24) | (rval & 0xf);
	dbg_send_debug_command_ultra_lite( cmd_val);
	uint32_t resp = dbg_get_debug_response_ultra_lite();

	return(resp);
}

uint32_t dbg_go_ultra_lite()
{
	uint32_t cmd_val = (UL_RUN_OP << 24);
	dbg_send_debug_command_ultra_lite( cmd_val);
	uint32_t resp = dbg_get_debug_response_ultra_lite();

	return(resp);

}

uint32_t dbg_read_mem_ultra_lite(uint32_t addr)
{
	uint32_t cmd_val = (UL_READ_OP << 24);
	cmd_val =  (cmd_val | (addr & 0x3fff)); // 18-bit address

	dbg_send_debug_command_ultra_lite( cmd_val);
	uint32_t ret_val = dbg_get_debug_response_ultra_lite();
	return(ret_val);
}

uint32_t dbg_write_mem_ultra_lite(uint32_t addr, uint32_t data)
{
	uint32_t cmd_val = (UL_WRITE_OP << 24);
	cmd_val = (cmd_val | (addr & 0x3fff));
	dbg_send_debug_command_ultra_lite( cmd_val);
	dbg_send_debug_command_ultra_lite( data );
	uint32_t ret_val = dbg_get_debug_response_ultra_lite();
	return(ret_val);
}
void dbg_send_debug_command_ultra_lite(uint32_t cmd_val)
{
	// UART ..
	int n = sendBytesOverUart ((uint8_t*) &cmd_val, 4);
	if(n != 4)
	{
		fprintf(stderr,"Error: dbg_send_debug_command_ultra_lite returns %d, expected 4\n", n);
	}
}

uint32_t dbg_get_debug_response_ultra_lite()
{

	// UART ..
	uint32_t ret_val = 0;
	int n = recvBytesOverUart((uint8_t*) &ret_val, 4, 0);

	if(n != 4)
	{
		fprintf(stderr,"Error: dbg_get_debug_response_ultra_lite returns %d, expected 4\n", n);
	}

	return(ret_val);
}
