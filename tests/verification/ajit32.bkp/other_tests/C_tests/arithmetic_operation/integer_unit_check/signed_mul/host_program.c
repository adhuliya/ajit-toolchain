#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include <inttypes.h>
#include <limits.h>

uint32_t a=0xfee6a1ff;//seed1
uint32_t b=0x80000001;//seed2

int32_t a1,b1;
int64_t rmul,rsig=0x0;

int i,n=10000000;//Number of random cases to be generated
int main()
{
	for(i=0;i<n;i++)
	{
		//LFSR
		a=((((a>>31)^(a>>6)^(a>>4)^(a>>1)^a)&1)<<31)|(a>>1);
		b=((((b>>31)^(b>>6)^(b>>4)^(b>>1)^b)&1)<<31)|(b>>1);
		
		a1=(int32_t)a;b1=(int32_t)b;
		rmul=(int64_t)a1*b1;
		
		rsig=rsig^rmul;//signature generated
		
	}
	printf(" signature=%"PRIx64"\n",rsig);
	return 0;
}
