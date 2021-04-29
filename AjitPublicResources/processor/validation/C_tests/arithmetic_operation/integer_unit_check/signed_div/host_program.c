#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include <inttypes.h>
#include <limits.h>
uint64_t a=0x0,atemp=0x0;
uint32_t b=0x77FFFF5B,a2=0x77abcd,a3=0xF12AB67;
int64_t a1;
int32_t b1;
int64_t rdiv=0x0,rdiv2;
int32_t rdiv1=0x0,isig=0x0;
uint32_t sa,sb;
int i,n=1000000;//Number of testcases
int main()
{
	for(i=0;i<n;i++)
	{
		//lfsr
		b=((((b>>31)^(b>>6)^(b>>4)^(b>>1)^b)&1)<<31)|(b>>1);
		a2=((((a2>>31)^(a2>>6)^(a2>>4)^(a2>>1)^a2)&1)<<31)|(a2>>1);
		a3=((((a3>>31)^(a3>>6)^(a3>>4)^(a3>>1)^a3)&1)<<31)|(a3>>1);
		//get sign bit from 32 bit number
		sa=(a2 & 0x80000000)>>31;sb=(b & 0x80000000)>>31;
		
		a=(int64_t)a3;//lower 32 bit
		atemp=(int64_t)a2;//store upper 32 bit
		atemp=atemp<<32;
		a=a|atemp;
		a1=(int64_t)a;b1=(int32_t)b;
		rdiv=(int64_t)a1/b1;
		rdiv1=a1/b1;
		if(rdiv!=rdiv1) 
		{
			if(sa==sb)rdiv1=0x7FFFFFFF;
			if(sa!=sb)rdiv1=0x80000000;
		}
		isig=isig^rdiv1;//signature generated
		
		
	}
	printf("isig=%"PRIx32"\n",isig);
	printf("Program completed succefully!!! \n");
	return 0;
}
