//display hello world on the console

#include "sparc_stdio.h"



//NOTE : with function main() use the
//attribute "((section(".text.main")))"
//to ensure that main() is  put in the
//beginning of the ".text" section in the 
//generated executable.

int  __attribute__((section(".text.main")))  main()
{
	putString("Hello World");
	putChar('\n');
	halt();
	return 0;
}
