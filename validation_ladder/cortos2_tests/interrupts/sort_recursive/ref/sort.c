#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#define VECTOR_SIZE  32

void merge (int* GVAL, int m)
{
	int I;
	int V = GVAL[m];
	for (I = 0; I < m; I++)
	{
		if(V < GVAL[I])
		{
			// shift  entries I to m-1 up by 1.
			int J;
			for (J = m; J > I ; J--)
			{
				GVAL[J] = GVAL[J-1];
			}
			GVAL[I] = V;
			break;
		}
	}
}


// sort items 0 1 ... m
void  sort(int *GVAL, int m)
{
	if(m > 0)
        {
	   sort  (GVAL, m-1);
	   merge (GVAL, m);
        }
}



int main(int argc, char* argv[])
{
	int I;
	int VALUES[VECTOR_SIZE];

	for(I = 0; I < VECTOR_SIZE; I++)
	{
		VALUES[I] = VECTOR_SIZE - I;
	}

	for(I = 0; I <= VECTOR_SIZE; I++)
	{
		sort (VALUES, VECTOR_SIZE-1);
		if(I == VECTOR_SIZE)
			break;
		else
			printf("finished  %d interrupts.\n", I);

	}

	for(I = 0; I < VECTOR_SIZE; I++)
	{
		printf("%d\n", VALUES[I]);
	}
}
