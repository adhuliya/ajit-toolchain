// A simple integer sort program

#include "sparc_stdio.h"

//declare the array to be sorted
#define SIZE 4
int bubble_sort();

//populate the array with 100 random integers
int Array[100] = {-204,
498,
352,
275,
-187,
-497,
255,
-112,
-309,
-435,
-11,
-154,
-336,
-355,
324,
410,
38,
-24,
-51,
356,
404,
255,
223,
386,
-418,
408,
179,
-405,
-40,
336,
329,
444,
454,
382,
-398,
496,
57,
161,
446,
-376,
207,
-49,
386,
-151,
-156,
171,
-368,
-351,
467,
402,
-453,
267,
450,
-273,
251,
-271,
-129,
-297,
330,
356,
-116,
58,
289,
456,
211,
-352,
168,
-221,
-225,
229,
440,
-226,
81,
-194,
92,
-188,
48,
125,
-72,
-210,
-61,
-478,
433,
328,
440,
78,
25,
-48,
-298,
-16,
177,
-364,
43,
-384,
-10,
-324,
273,
215,
461,
-492};

//NOTE : with function main() use the
//attribute "((section(".text.main")))"
//to ensure that main() is  put in the
//beginning of the ".text" section in the 
//generated executable.

int  __attribute__((section(".text.main")))  main()
{
//Initialize all registers
	__asm__ __volatile__( "mov %g0, %g1 \n\t "); __asm__ __volatile__( "mov %g0, %g2 \n\t ");
	__asm__ __volatile__( "mov %g0, %g3 \n\t "); __asm__ __volatile__( "mov %g0, %g4 \n\t ");
	__asm__ __volatile__( "mov %g0, %g5 \n\t "); __asm__ __volatile__( "mov %g0, %g6 \n\t ");
	__asm__ __volatile__( "mov %g0, %g7 \n\t ");

	__asm__ __volatile__( "mov %g0, %i0 \n\t "); __asm__ __volatile__( "mov %g0, %i1 \n\t ");
	__asm__ __volatile__( "mov %g0, %i2 \n\t "); __asm__ __volatile__( "mov %g0, %i3 \n\t ");
	__asm__ __volatile__( "mov %g0, %i4 \n\t "); __asm__ __volatile__( "mov %g0, %i5 \n\t ");
	__asm__ __volatile__( "mov %g0, %i6 \n\t "); __asm__ __volatile__( "mov %g0, %i7 \n\t ");

	__asm__ __volatile__( "mov %g0, %l0 \n\t "); __asm__ __volatile__( "mov %g0, %l1 \n\t ");
	__asm__ __volatile__( "mov %g0, %l2 \n\t "); __asm__ __volatile__( "mov %g0, %l3 \n\t ");
	__asm__ __volatile__( "mov %g0, %l4 \n\t "); __asm__ __volatile__( "mov %g0, %l5 \n\t ");
	__asm__ __volatile__( "mov %g0, %l6 \n\t "); __asm__ __volatile__( "mov %g0, %l7 \n\t ");

	__asm__ __volatile__( "mov %g0, %o0 \n\t "); __asm__ __volatile__( "mov %g0, %o1 \n\t ");
	__asm__ __volatile__( "mov %g0, %o2 \n\t "); __asm__ __volatile__( "mov %g0, %o3 \n\t ");
	__asm__ __volatile__( "mov %g0, %o4 \n\t "); __asm__ __volatile__( "mov %g0, %o5 \n\t ");
	__asm__ __volatile__( "mov %g0, %o6 \n\t "); __asm__ __volatile__( "mov %g0, %o7 \n\t ");

	//initialize registers in other windows
	int window=0;
	for(window=0;window<7;window++)
	{
		__asm__ __volatile__( "save\n\t "); 

		__asm__ __volatile__( "mov %g0, %l0 \n\t "); __asm__ __volatile__( "mov %g0, %l1 \n\t ");
		__asm__ __volatile__( "mov %g0, %l2 \n\t "); __asm__ __volatile__( "mov %g0, %l3 \n\t ");
		__asm__ __volatile__( "mov %g0, %l4 \n\t "); __asm__ __volatile__( "mov %g0, %l5 \n\t ");
		__asm__ __volatile__( "mov %g0, %l6 \n\t "); __asm__ __volatile__( "mov %g0, %l7 \n\t ");

		__asm__ __volatile__( "mov %g0, %o0 \n\t "); __asm__ __volatile__( "mov %g0, %o1 \n\t ");
		__asm__ __volatile__( "mov %g0, %o2 \n\t "); __asm__ __volatile__( "mov %g0, %o3 \n\t ");
		__asm__ __volatile__( "mov %g0, %o4 \n\t "); __asm__ __volatile__( "mov %g0, %o5 \n\t ");
		__asm__ __volatile__( "mov %g0, %o6 \n\t "); __asm__ __volatile__( "mov %g0, %o7 \n\t ");

	}

	for(window=0;window<7;window++)
	{
		__asm__ __volatile__( "restore\n\t "); 
	}

	
	int ret_val = bubble_sort();
	return(ret_val);
}

int bubble_sort()
{
	//bubblesort

	int i=0;
	int j=0;
	int t=0;
	for(i=0;i<SIZE;i++)// passes
	{
		for(j=0;j<(SIZE-1);j++)//a single pass
		{
			if(Array[j]>Array[j+1])
			{
				//swap
				t=Array[j+1];
				Array[j+1]=Array[j];
				Array[j]=t;
			}
		}
	}
	/*
	for(i = 0; i < SIZE; i++)
	{
		putChar('\n');
		putInt(Array[i]);
	}
	*/
	halt();
	return 0;
}



