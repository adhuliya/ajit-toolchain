//Routine to test keyboard/console 
//functionality
#include "sparc_stdio.h"



//NOTE : with function main() use the
//attribute "((section(".text.main")))"
//to ensure that main() is  put in the
//beginning of the ".text" section in the 
//generated executable.

int  __attribute__((section(".text.main")))  main()
{
	putString("\nTesting output.....");
	putChar('\n');
	putChar('A');
	putChar('B');
	putChar('C');
	putChar('\n');
	putString("\nHello World! \n");
	putInt(1234);
	putChar('\n');
	putInt(-564);
	putChar('\n');
	putFloat(3.1415000);
	putChar('\n');
	putDouble(1.234567891234567);
	putChar('\n');

	putString("\n Size of char     = "); putInt(sizeof(char));
	putString("\n Size of int      = "); putInt(sizeof(int));
	putString("\n Size of float    = "); putInt(sizeof(float));
	putString("\n Size of double   = "); putInt(sizeof(double));
	putString("\n Size of long int = "); putInt(sizeof(long int));
	putChar('\n');


	putString("\nTesting Input .... ");
	
	putString("\nEnter a char : "); char c = getChar(); 
	putString("\nYou entered : ");putChar(c);
	putString("\nEnter an int : "); int i = getInt(); 
	putString("\nYou entered : ");putInt(i);
	putString("\nEnter a float : "); float f = getFloat(); 
	putString("\nYou entered : ");putFloat(f);
	putString("\nEnter a double : "); double d = getDouble(); 
	putString("\nYou entered : ");putDouble(d);

	putString("\nEnter any char to end program : ");getChar();


	halt();
	return 0;
}
