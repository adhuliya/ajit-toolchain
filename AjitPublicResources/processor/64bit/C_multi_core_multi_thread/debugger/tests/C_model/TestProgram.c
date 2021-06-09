// A simple integer sort program

#include "sparc_stdio.h"


//NOTE : with function main() use the
//attribute "((section(".text.main")))"
//to ensure that main() is  put in the
//beginning of the ".text" section in the 
//generated executable.

int  __attribute__((section(".text.main")))  main()
{
	//bubblesort

	int i=0;
	int j=0;
	int t=0;
	
	for ( i = 0; i < 10 ; i++)
	{
		t += 2;
	}
	j = 25;
	t = j - t;
	j = t + i;
	halt();
	return 0;
}



