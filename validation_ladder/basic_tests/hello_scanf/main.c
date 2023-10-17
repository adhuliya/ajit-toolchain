#include <stdio.h>
#include <stdint.h>
#include "bscanf.h"
#include "core_portme.h"
#include "ajit_access_routines.h"

// returns number of characters read into buffer.
int __ajit_serial_getline__ (char* buffer, int max_length)
{
	int i = 0;
	char c = 0;

	while(1)
	{
		c = __ajit_serial_getchar__ ();
		if((c == '\n') || (c == '\r') || (c == 0xff))
			break;

		buffer[i] = c;
		i++;

		if(i == max_length)
			break;
	}

	return(i);
}


int main()
{
	char buf[1024];
	int val;

	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);

	int N = __ajit_serial_getline__ (buf, 1023);
	buf[N] = 0;

	ee_printf("read %d characters %s\n", N, buf);

	bscanf(buf,"%d", &val);
	ee_printf("read %d\n", val);
	
	return(0);
}

