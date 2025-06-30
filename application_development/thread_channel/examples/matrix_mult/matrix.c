#include <stdlib.h>
#include <stdint.h>
#include <math.h>

double A[ORDER][ORDER];
double B[ORDER][ORDER];
double C[ORDER][ORDER];

	
void print_result_matrix()
{
	int I, J;
	for(I =0; I < ORDER; I++)
	{
		for(J=0; J < ORDER; J++)
		{
			cortos_printf("%f ", C[I][J]);
		}
		cortos_printf("\n");
	}
}


void initMatrices()
{
	int I, J;
	for(I = 0; I < ORDER; I++)
	{
		for(J = 0; J < ORDER; J++)
		{
			A[I][J] = I+J;
			B[I][J] = I-J;
		}
	}
}


void mmul(int sindex, int stride)
{
	int I,J,K;
	for(I = sindex; I < ORDER; I = I+stride)
	{
		for(J = 0; J < ORDER; J++)
		{
			double S = 0;
			for(K = 0; K < ORDER; K++)
			{
				S = S + A[I][K]*B[K][J];
			}
			C[I][J] = S;
		}
	}
}



