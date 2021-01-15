#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

char byte_buffer [256];
char nibble_buffer [5];
			
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

//
// read an mmap file and convert to integer, bit-vector form.
//
int main(int argc, char* argv [])
{
	
	if(argc > 1)
	{
		fprintf(stderr,"Usage: %s  < infile > outfile.\n", argv[0]);
		return(-1);
	}


	while (1)
	{
		int eof_reached = 0;
		uint32_t addr = 0;
		uint32_t byte_data = 0;
		
		uint32_t file_read=fscanf(stdin, "%x", &addr);
		if (feof(stdin)) 
		{
			eof_reached = 1;
		}
		else
		{
			file_read = fscanf(stdin, "%x", &byte_data);
			byte_to_binary_string((uint8_t) byte_data);
			fprintf(stdout,"%d %s\n", addr, byte_buffer);
		}

		if(eof_reached)
			break;
	}
	return 1;
}

