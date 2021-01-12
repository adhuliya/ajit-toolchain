#include <stdint.h>
#include "core_portme.h"

int correlate (int *a, int *incoming)
{
	int i =0, j=0;
	for(i=0; i<1023*6; i++){
		j = j + incoming[i] * a[i];
	}
	return j;
}

