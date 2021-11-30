#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "defs.h"

volatile int A[ORDER];
volatile int B[ORDER];
volatile int C[ORDER];

volatile int mutex_var = 0;

void initVectors()
{
	int J;
	for(J = 0; J < ORDER; J++)
	{
		A[J] = J;
		B[J] = J;
	}
}



void vectorSum ()
{
	int J;
	for(J = 0; J < ORDER; J++)
	{
		C[J] = A[J] + B[J];
	}
}
