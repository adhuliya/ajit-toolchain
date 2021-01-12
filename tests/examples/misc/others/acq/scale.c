#include <stdint.h>
#include <math.h>
#include "core_portme.h"

int mycos(float x){
	x = x/(2*M_PI) ;
 x = x - (int)x;
 if(x>0 && x<0.25)
 return 1;
 else if(x>0.25 && x<0.75)
 return -1;
 else if(x>0.75 && x<1)
 return 1;
 else return 1;
}

void scale (int  fi, int fd_lo, float *t, int *in_data)
{
	int i = 0;
	for(i = 0; i< 1023*6 ; i++){
	in_data[i] = mycos(2.0*M_PI*(fi+fd_lo)*(t[i]))*in_data[i];
	}
}
