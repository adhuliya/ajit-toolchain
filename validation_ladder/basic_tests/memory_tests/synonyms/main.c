#include "stdint.h"
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "math.h" 

#define ORDER 4
#define REPETITIONS 2

// 
unsigned int *A = (unsigned int *) 0x40002000; 
unsigned int *B = (unsigned int *) 0x40003000; 

void clearA()
{
	int I;
	for(I = 0; I < ORDER; I++)
		A[I] = 0;
}
void writeB()
{
	int I;
	for(I = 0; I < ORDER; I++)
		B[I] = I;
}
void checkA()
{
	int I;
	for(I = 0; I < ORDER; I++)
	{
		if(A[I] != I)
			ee_printf("Error: checkA A[%d]=%d\n", I, A[I]);
	}
}


int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);

	// ee_printf("Start:\n");

	int I;
	for(I = 0; I < REPETITIONS; I++)
	{
		clearA();
		writeB();
		checkA();
	}
	// ee_printf("done %d\n", I);
	return (0);
}



