#include <stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
int main()
{
	uint64_t a =0xabcd12347890cdfe;
	uint64_t b =0x567898872abcd123;
	uint64_t sa,ea,fa,sb,eb,fb;
	uint64_t n=10;
	int64_t a1,b1;
	double fta,ftb,fadd,fsub,fmul,fdiv,fsrt;
	int sign,iflag;
	double exponent,mantissa,int_to_dob;
	int dob_to_int,i;
	uint64_t sig2=0x0;
	int64_t *int_fdiv;
	for (i=0;i<n;i++)
	{
		//lfsr
		a=((((a>>63)^(a>>62)^(a>>61)^(a>>60)^a)&1)<<63)|(a>>1);
		b=((((b>>63)^(b>>62)^(b>>61)^(b>>60)^b)&1)<<63)|(b>>1);
		a1=(int64_t)a;
		b1=(int64_t)b;
		
		//separate the sign/exponent/fraction bits 
		ea=(a1 & 0x7FF0000000000000)>>52;
		fa=(a1 & 0x000FFFFFFFFFFFFF);
		sa=(a1 & 0x8000000000000000)>>63;
		eb=(b1 & 0x7FF0000000000000)>>52;
		fb=(b1 & 0x000FFFFFFFFFFFFF);
		sb=(b1 & 0x8000000000000000)>>63;
	
	//excluding the exceptional cases	
	if(ea==0)ea=1;if(eb==0)eb=1;//if e=0 2^(1-1023) instead of 2^(-1023)
	
	if(ea<2047 && eb<2047 && fa!=0 && fb !=0 && (ea+eb-2046)<1023 && (ea-eb)<1023 )

		{	//A:
			//generate floating point numbers from its components
			sign=pow(-1,sa);exponent=pow(2.0,(ea*1.0-1023*1.0));
			iflag=0;if(ea!=0)iflag=1;mantissa=(iflag+fa/(pow(2,52)));
			fta=sign*exponent*mantissa;
			//B:
			sign=pow(-1,sb);exponent=pow(2.0,(eb*1.0-1023*1.0));
			iflag=0;if(eb!=0)iflag=1;mantissa=(iflag+fb/(pow(2,52)));
			ftb=sign*exponent*mantissa;
			
			/*if(sa==0)
			{
				fsrt=sqrt(fta);
			}*/
			
			fadd=fta+ftb;//add
			
			fmul=fadd*ftb;//mul

			fsub=fmul-fadd;	//sub

			//fdiv=fmul/fsub; //div
					
			int_fdiv=(int64_t*)&fsub;

			sig2=sig2^*int_fdiv;//signature
			
			
		}
	}
	printf("signature double precision=%lx\t\n",sig2);
}
