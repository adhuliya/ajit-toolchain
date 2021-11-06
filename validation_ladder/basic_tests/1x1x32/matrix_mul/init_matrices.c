#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "defs.h"

volatile int A[ORDER][ORDER];
volatile int B[ORDER][ORDER];
volatile int P[ORDER][ORDER];

volatile int mutex_var = 0;

void initMatrices(int S, int F)
{
	int I, J;
	for(I = S; I <= F; I++)
	{
		for(J = 0; J < ORDER; J++)
		{
			A[I][J] = 1;
			B[I][J] = 1;
			P[I][J] = 0;
		}
	}
}



void mulBlock (int S, int F) 
{

	int I, J, K;
	for(I = S; I <= F; I++)
	{
		for (J = 0; J < ORDER; J++)
		{
			int r = 0;
			for (K = 0; K < ORDER; K++)
			{ 
				r += A[I][K] * B [K][J];
			}
			P[I][J] = r;
		}
	}
}
