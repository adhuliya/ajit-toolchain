#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "uart_interface.h"

void print_usage(char* app_name)
{
	fprintf(stderr,"USAGE: %s  inputfile serial-device-name\n", app_name);
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		print_usage(argv[0]);
		return(1);
	}

	
	FILE* fp;
	fp = fopen(argv[1], "rb");
	if(fp == NULL)
	{
		fprintf(stderr,"Error: could not open bin file %s\n", argv[1]);
		return(1);
	}
	
		
	int uart_ok = setupDebugUartLink(argv[2]);	
	if(uart_ok < 0)
	{
		fprintf(stderr,"Error: could not open uart %s\n", argv[2]);
		return(1);
	}
	fprintf(stderr,"Info: opened UART (%s)\n", argv[2]);

	int byte_count = 0;
	while(1)
	{
		uint8_t x;
		int r = fread(&x, sizeof(uint8_t), 1, fp);
		if((r==0) || (r == EOF))
			break;
		sendByte(x);	
		byte_count++;
	
		if((byte_count % 1024) == 0)
		{
			fprintf(stderr,"Info: sent %d bytes.. last-byte=0x%x\n", 
					byte_count, x);
		}
	}
	return(0);
}

