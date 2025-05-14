#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <setjmp.h>
#include <cortos.h>

int check ()
{
	double X = 1.0;

	int I;
	for (I = 0; I < 10; I++)
	{
		double Y = X/1;
		if(X != (X/1))
		{
			fprintf(stderr,".17e !=  .17e\n", X, Y);
		}
		X = 2.0*X;
	}
		
	cortos_printf("done check.\n");
	return(0);
}

