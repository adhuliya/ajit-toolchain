#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include <inttypes.h>
#include <limits.h>
uint64_t a=0x0,atemp=0x0;
uint32_t b=0x77FFFF5B,a_hi=0x77abcd12,a_lo=0xF12AB678;
uint64_t rdiv=0x0,rmul=0x0,sig=0x0;
uint32_t radd,rdiv1=0x0;
int32_t rsub,sigsub=0x0;
int i,n=1000000;
int main()
{
	for(i=0;i<n;i++)
	{
		b=((((b>>31)^(b>>6)^(b>>4)^(b>>1)^b)&1)<<31)|(b>>1);
		a_hi=((((a_hi>>31)^(a_hi>>6)^(a_hi>>4)^(a_hi>>1)^a_hi)&1)<<31)|(a_hi>>1);
		a_lo=((((a_lo>>31)^(a_lo>>6)^(a_lo>>4)^(a_lo>>1)^a_lo)&1)<<31)|(a_lo>>1);
		a=a_lo;//lower 32 bit
		atemp=a_hi;//store upper 32 bit
		atemp=atemp<<32;
		a=a|atemp;
		
		//Division
		rdiv=(uint64_t)a/b;
		rdiv1=a/b;
		if(rdiv!=rdiv1) rdiv1=0xFFFFFFFF;//change the result as per SPARC 
		sig=sig^rdiv1;//signature updated for division
		//other arithmetic operations on lower 32 bit of "a" (ie a_lo) and "b"
		radd=a_lo+b;
		rmul=(uint64_t)a_lo*b;
		rsub=a_lo-b;
		//update signatures
		sig=sig^radd;sig=sig^rmul;sigsub=sigsub^rsub;
		
	}
	printf("sig=%"PRIx64 "\n" "sigsub=%"PRIx32"\n",sig,sigsub);
	printf("Program completed succefully!!!\n");
	return 0;
}
