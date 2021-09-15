#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
int sum3(int A, int B, int C)
{
	int r = (A + B);
	r = r + C;
	return(r);
}


int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	ee_printf("Starting.\n");

	int A, B, C;
	
	A = 1;
	B = 2;
	C = 3;

	A = sum3(A,B,C);



	ee_printf("Done.\n");
	return(1);
}


