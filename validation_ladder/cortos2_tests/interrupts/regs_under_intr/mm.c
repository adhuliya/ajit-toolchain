#include <stdlib.h>
#include "cortos.h"
#define ORDER 4

double a[ORDER][ORDER];
double b[ORDER][ORDER];
double c[ORDER][ORDER];

void mm_print()
{
	int I;
	for(I = 0; I < ORDER; I++)
	{
		cortos_printf("c[%d][%d]=%f\n", I, I, c[I][I]);
	}
}

void mm_init()
{
	int I, J;
	for(I = 0; I < ORDER; I++)
	{
		for(J = 0; J < ORDER; J++)
		{
			a[I][J]  = 1;
			b[I][J]  = 1;
		}
	}
}

void mm ()
{
	int I, J, K;
	for(I = 0; I < ORDER; I++)
	{
		for(J = 0; J < ORDER; J++)
		{
			double S = 0;
			for(K = 0; K < ORDER; K++)
			{
				S += a[I][K] * b[K][J];
			}
			c[I][J] = S;
			cortos_printf("c[%d][%d]=%f\n", I, J, c[I][J]);
		}
	}
	mm_print();
}

