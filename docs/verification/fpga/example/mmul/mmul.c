#include <stdint.h>
#include <stdio.h>

extern double A[32][32]; // 8KB
extern double B[32][32]; // 8KB
extern double C[32][32]; // 8KB

void mmul(int Istart, int Iend)
{
	int I, J, K;
	for(I = Istart; I < Iend; I++)
	{
		for(J = 0; J < 32; J++)
		{
			double sum_0 = 0.0;
			double sum_1 = 0.0;
			double sum_2 = 0.0;
			double sum_3 = 0.0;

			for(K = 0; K < 32; K += 8)
			{
				sum_0 += A[I][K]*B[K][J];
				sum_1 += A[I][K+1]*B[K+1][J];
				sum_2 += A[I][K+2]*B[K+2][J];
				sum_3 += A[I][K+3]*B[K+3][J];
				sum_0 += A[I][K+4]*B[4][J];
				sum_1 += A[I][K+5]*B[K+5][J];
				sum_2 += A[I][K+6]*B[K+6][J];
				sum_3 += A[I][K+7]*B[K+7][J];
			}
			C[I][J] = sum_0 + sum_1 + sum_2 + sum_3;
		}
	}
}

