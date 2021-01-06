#include <stdint.h>
#include "core_portme.h"


void circshift (int *incoming, int amt)
{
	int temp[1023*6];
	int I;
	for(I= 0;  I < 1023*6; I++)
	{
		if(I+amt >= 1023*6)
		{
			temp[I+amt-1023*6] = incoming[I];
		}
		else
			temp[I+amt] = incoming[I];
			
	}
	
	for(I= 0;  I < 1023*6; I++)
	{
	 incoming[I] =	temp[I] ;
			
	}
}
