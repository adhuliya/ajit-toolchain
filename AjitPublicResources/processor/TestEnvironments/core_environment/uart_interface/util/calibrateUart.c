#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "uart_interface.h"

void print_usage(char* app_name)
{
	fprintf(stderr,"USAGE: %s  serial-device-name [baudrate]\n", app_name);
	fprintf(stderr,"     baudrate optional, default 115200.\n");
	fprintf(stderr,"\nExample: %s /dev/ttyUSB0 115200\n", app_name); 
}

int main(int argc, char* argv[])
{
	int baud_rate = 115200;
	if(argc < 2)
	{
		print_usage(argv[0]);
		return(1);
	}

	if(argc == 3)
	{
		baud_rate = atoi (argv[2]);
	}
	fprintf (stderr,"Info: tty=%s, baud-rate=%d.\n", argv[1], baud_rate);

	
	int uart_ok = setupDebugUartLinkWithBaudRate(argv[1], baud_rate);	
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

