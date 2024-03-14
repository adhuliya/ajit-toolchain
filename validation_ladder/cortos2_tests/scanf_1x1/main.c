#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "bscanf.h"
#include "cortos.h"
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
	cortos_printf("?\n");

	int N = __ajit_serial_getline__ (buf, 1023);
	buf[N] = 0;

	cortos_printf("read %d characters %s\n", N, buf);

	bscanf(buf,"%d", &val);
	cortos_printf("read %d\n", val);

	sprintf(buf, "%f %d %s\n", 1.0, 1, "check_string");

	float fval;
        char str[16];
	bscanf(buf,"%f %d %15s", &fval, &val, str);
	cortos_printf("from buf: %s read %f %d %s\n", buf, fval, val, str);

	sprintf(buf, "%e %x %s\n", 1.0, 1, "check_string");
	bscanf(buf,"%f %x %15s", &fval, &val, str);
	cortos_printf("from buf: %s read %f %x %s\n", buf, fval, val, str);
	
	return(0);
}

