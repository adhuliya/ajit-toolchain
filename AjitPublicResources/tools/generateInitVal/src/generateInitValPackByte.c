#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


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
		sram_size = (1 << atoi(argv[1]));

	fprintf(stderr,"Size of sram = %d bytes.\n", sram_size);
	
	fprintf(stdout,"library ieee; use ieee.std_logic_1164.all; use ieee.numeric_std.all;\n");
	fprintf(stdout, "package init_val_package is \n");
	fprintf(stdout,"  type RamMemArray is array (natural range <>) of std_logic_vector(7 downto 0);\n");
	fprintf(stdout,"  constant ram_init_val: RamMemArray (%d downto 0) := (\n", sram_size-1);
	
	uint32_t addr;
	uint32_t  data;
	int file_read=0;

	int first_one = 1;
	int number_of_bytes_read = 0;

	while (1)
	{
		int eof_reached = 0;
		data = 0;
		
		file_read=fscanf(stdin, "%x", &addr);
		if (feof(stdin)) 
		{
			eof_reached = 1;
		}
		else
		{
			file_read=fscanf(stdin, "%x", &data);
		}

		if(eof_reached)
			break;

		
		if(data != 0)
		{
			if(!first_one)
				fprintf(stdout,",\n");
			else
				first_one = 0;

			byte_to_binary_string(data);
			fprintf(stdout, "     %d => \"%s\"",  addr, byte_buffer);
		}
		number_of_bytes_read++;


		first_one = 0;

	}
	fprintf(stdout, ",\n  others => (others => '0'));\n"); // end constant 
	fprintf(stdout, "end package init_val_package;\n");
	return 1;
}

