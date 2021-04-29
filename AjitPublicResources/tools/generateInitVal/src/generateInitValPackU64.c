#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


char uint64_buffer [ 1024 ];
char byte_buffer [ 1024 ];
char nibble_buffer [ 1024 ];
			
void nibble_to_binary_string(uint8_t nibble)
{
	nibble_buffer[0] = 0;
	switch(nibble)
	{
		case 0 : sprintf (nibble_buffer,"0000"); break;
		case 1 : sprintf (nibble_buffer,"0001"); break;
		case 2 : sprintf (nibble_buffer,"0010"); break;
		case 3 : sprintf (nibble_buffer,"0011"); break;
		case 4 : sprintf (nibble_buffer,"0100"); break;
		case 5 : sprintf (nibble_buffer,"0101"); break;
		case 6 : sprintf (nibble_buffer,"0110"); break;
		case 7 : sprintf (nibble_buffer,"0111"); break;
		case 8 : sprintf (nibble_buffer,"1000"); break;
		case 9 : sprintf (nibble_buffer,"1001"); break;
		case 10 : sprintf (nibble_buffer,"1010"); break;
		case 11 : sprintf (nibble_buffer,"1011"); break;
		case 12 : sprintf (nibble_buffer,"1100"); break;
		case 13 : sprintf (nibble_buffer,"1101"); break;
		case 14 : sprintf (nibble_buffer,"1110"); break;
		case 15 : sprintf (nibble_buffer,"1111"); break;
		default: break;
	}
}


void byte_to_binary_string(uint8_t curr_byte)
{
	byte_buffer[0] = 0;
	uint8_t nibble_1 = (curr_byte >> 4) & 0xf;
	nibble_to_binary_string(nibble_1);
	strcat (byte_buffer,nibble_buffer);

	nibble_to_binary_string(nibble_1);
	uint8_t nibble_0 = curr_byte & 0xf;
	nibble_to_binary_string(nibble_0);
	strcat (byte_buffer,nibble_buffer);

}

void uint64_to_binary_string(uint64_t current_read_word)
{
	uint8_t curr_byte;
	uint64_buffer[0] = 0;

	int I;
	for(I= 0; I < 8; I++)
	{
		curr_byte = current_read_word >> (8*(7-I));
		byte_to_binary_string(curr_byte);

		strcat(uint64_buffer,byte_buffer);
	}
}

// to be used to initialize memory through the debug
// interface..  This will be needed to test the FPGA
// prototype.
int main(int argc, char* argv [])
{
	
	int sram_size;
	if(argc < 2)
	{
		fprintf(stderr,"Usage: %s <number-of-address-bits>  < infile > outfile.\n", argv[0]);
		return(-1);
	}

	if(argc > 1)
		sram_size = (1 << atoi(argv[1]))/8;

	uint8_t* byte_array = (uint8_t *) malloc (8*sram_size*sizeof(uint8_t));

	fprintf(stderr,"Size of sram = %d 8-byte words.\n", sram_size);
	
	fprintf(stdout,"library ieee; use ieee.std_logic_1164.all; use ieee.numeric_std.all;\n");
	fprintf(stdout, "package sram_stub_init_val_package is \n");
	fprintf(stdout,"  type sram_type is array (natural range <>) of std_logic_vector(63 downto 0);\n");
	fprintf(stdout,"  constant sram_stub_init_val: sram_type (%d downto 0) := (\n", sram_size-1);

	
	uint32_t addr;
	uint64_t  data;
	int file_read=0;

	int first_one = 1;

	int number_of_bytes_read = 0;
	int current_word_address = -1;
	uint64_t current_read_word    = 0;
	uint32_t rdata;

	while(1)
	{
		file_read=fscanf(stdin, "%x", &addr);
		if (feof(stdin)) 
		{
			break;
		}
		else
		{
			file_read=fscanf(stdin, "%x", &rdata);
			byte_array[addr] = rdata;
			number_of_bytes_read++;
		}

	}

	int number_of_dwords = (number_of_bytes_read/8)  + ((number_of_bytes_read & 0x7) ? 1 : 0);
	uint32_t current_dword_address;
	for (current_dword_address = 0; current_dword_address < number_of_dwords*8; current_dword_address += 8)
	{
		uint64_t current_dword = 0;
		int B;
		for(B = 0; B < 8; B++)
		{
			current_dword = (current_dword << 8) |  byte_array[current_dword_address + B];
		}
		if(!first_one)
		{
			fprintf(stdout,",\n");
		}
		else 
			first_one = 0;
			
		uint64_to_binary_string(current_dword);
		fprintf(stdout, "     %d => \"%s\"",  current_dword_address/8, uint64_buffer);
	}
	fprintf(stdout, ",\n  others => (others => '0'));\n"); // end constant 
	fprintf(stdout, "end package sram_stub_init_val_package;\n");
	return 1;
}

