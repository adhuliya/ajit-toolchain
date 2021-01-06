// A calculator program which does standard arithmetic operations.

#include "sparc_stdio.h"


//NOTE : with function main() use the
//attribute "((section(".text.main")))"
//to ensure that main() is  put in the
//beginning of the ".text" section in the 
//generated executable.
int  __attribute__((section(".text.main")))  main()
{
	char c;
	int i1, i2;
	float f1, f2;
	double d1, d2;
	putString("\nEnter i for integer , f for float, d for double : ");
	c = getChar();	
	
	if (c == 'i')
	{
		putString("Enter 2 integers:\n");
		i1 = getInt();
		i2 = getInt();		
		putChar('\n');
		putInt(i1); putString(" + "); putInt(i2); putString(" = "); putInt(i1 + i2);
		putChar('\n');
		putInt(i1); putString(" - "); putInt(i2); putString(" = "); putInt(i1 - i2);
		putChar('\n');
		putInt(i1); putString(" * "); putInt(i2); putString(" = "); putInt(i1 * i2);
		putChar('\n');
		putInt(i1); putString(" / "); putInt(i2); putString(" = "); putInt(i1 / i2);
		putChar('\n');
	}

	if (c == 'f')
	{
		putString("Enter 2 floats:\n");
		f1 = getFloat();
		f2 = getFloat();		
		putChar('\n');
		putFloat(f1); putString(" + "); putFloat(f2); putString(" = "); putFloat(f1 + f2);
		putChar('\n');
		putFloat(f1); putString(" - "); putFloat(f2); putString(" = "); putFloat(f1 - f2);
		putChar('\n');
		putFloat(f1); putString(" * "); putFloat(f2); putString(" = "); putFloat(f1 * f2);
		putChar('\n');
		putFloat(f1); putString(" / "); putFloat(f2); putString(" = "); putFloat(f1 / f2);
		putChar('\n');
	}

	if (c == 'd')
	{
		putString("Enter 2 doubles:\n");
		d1 = getDouble();
		d2 = getDouble();		
		putChar('\n');
		putDouble(d1); putString(" + "); putDouble(d2); putString(" = "); putDouble(d1 + d2);
		putChar('\n');
		putDouble(d1); putString(" - "); putDouble(d2); putString(" = "); putDouble(d1 - d2);
		putChar('\n');
		putDouble(d1); putString(" * "); putDouble(d2); putString(" = "); putDouble(d1 * d2);
		putChar('\n');
		putDouble(d1); putString(" / "); putDouble(d2); putString(" = "); putDouble(d1 / d2);
		putChar('\n');
	}
	halt();

	return 0;
}
