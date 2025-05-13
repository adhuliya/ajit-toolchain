#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int main ()
{
	// V9 = 0xfff0000000000000
        // Y=-8.98846567431059984e+307
	// 0xffe0000000000000
	
	double NegInf;
	*((uint64_t*) &NegInf) = 0xfff0000000000000;

	double Y;
	*((uint64_t*) &Y) = 0xffe0000000000000;


	int cmp = (NegInf < Y);
	printf("(%.17e < %.17ee)=%d\n", NegInf, Y, cmp);

	return(0);
}

