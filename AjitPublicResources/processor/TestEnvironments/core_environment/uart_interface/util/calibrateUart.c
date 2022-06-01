#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "uart_interface.h"

void print_usage(char* app_name)
{
	fprintf(stderr,"USAGE: %s  serial-device-name\n", app_name);
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		print_usage(argv[0]);
		return(1);
	}

	
	int uart_ok = setupDebugUartLink(argv[1]);	
	if(uart_ok < 0)
	{
		fprintf(stderr,"Error: could not open uart %s\n", argv[1]);
		return(1);
	}
	fprintf(stderr,"Info: opened UART (%s)\n", argv[1]);
	sendByte (0x80);
	fprintf(stderr,"Info: sent 0x80 to calibrate UART (%s)\n", argv[1]);

	return(0);
}

