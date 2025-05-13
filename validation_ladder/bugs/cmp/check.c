#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <cortos.h>

int fp_cmp(double, double);

int main ()
{
	// V9 = 0xfff0000000000000
        // Y=-8.98846567431059984e+307
	// 0xffe0000000000000
	
	double NegInf;
	*((uint64_t*) &NegInf) = 0xfff0000000000000;
	double Y;
	*((uint64_t*) &Y) = 0xffe0000000000000;
	int cmp = fp_cmp(NegInf, Y);
	cortos_printf("(%.17e < %.17ee)=%d\n", NegInf, Y, cmp);

	double CInvrse=1.37153101719842217e+303;
	double HInvrse=2.00000000000000000e+00;
	Y = - CInvrse;
	double V9 = HInvrse * Y;
	double V;

	do {
		V = Y;
		Y = V9;
		V9 = HInvrse * Y;
		cortos_printf("INFO:OVFLOW:  V9=%.17e (0x%llx)\n", V9, *((uint64_t*) &V9));
		cortos_printf("INFO:OVFLOW:  Y=%.17e (0x%llx)\n",  Y, *((uint64_t*) &Y));
		int  condition = (V9 < Y);
		if(!condition)
		{
			condition = fp_cmp(V9, Y);
			cortos_printf("INFO:OVFLOW:  (V9 < Y)=%d\n", condition);
		}

		} while(V9 < Y);


	return(0);
}

