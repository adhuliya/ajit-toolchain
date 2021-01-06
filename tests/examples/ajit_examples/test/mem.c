#include <stdint.h>
#include "core_portme.h"

//
// 32 kB.
//

void mem_march (int num)
{
	int I,J =1;
	for(I= 1;  I < num+1; I++)
	{
		J = J * I;
			
		}
ee_printf ("Fact: %u\n",  J);
}
