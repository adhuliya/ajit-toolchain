#include <stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
int main()
{
	
	uint32_t a=0xf95cdb48;//seed1
	uint32_t b=0xbe6f2115;//seed2
	uint32_t sa,ea,fa,sb,eb,fb;
	int i,n=10;
	int a1,b1;
	float fta,ftb,fadd,fsub,fmul,fdiv,fsrt;
	float exponent,mantissa;
	int sign,iflag,*ipfinal;
	uint32_t isig=0x0;//integer signature
	for (i=0;i<n;i++)
	{
		// lfsr
		a=((((a>>31)^(a>>6)^(a>>4)^(a>>1)^a)&1)<<31)|(a>>1);
		b=((((b>>31)^(b>>6)^(b>>4)^(b>>1)^b)&1)<<31)|(b>>1);
		a1=(int)a;
		b1=(int)b;

		//separate the sign/exponent/fraction bits 
		sa=(a1 & 0x80000000)>>31;ea=(a1 & 0x7F800000)>>23;fa=(a1 & 0x007fffff);
		sb=(b1 & 0x80000000)>>31;eb=(b1 & 0x7F800000)>>23;fb=(b1 & 0x007fffff);

		//excluding the exceptional cases
		if(ea==0)ea=1;if(eb==0)eb=1;//if e=0 ,set 2^(1-127) instead of 2^(-127)
		if(ea<255 && eb<255 && fa!=0 && fb !=0 && (ea+eb-254)<127 && (ea-eb)<127)
		{
			//A::
			//generate floating point numbers from its components
			sign=pow(-1,sa);exponent=pow(2.0,(ea*1.0-127*1.0));
			iflag=0;if(ea!=0)iflag=1;mantissa=(iflag+fa/(pow(2,23)));
			fta=sign*exponent*mantissa;
			//B::
			sign=pow(-1,sb);exponent=pow(2.0,(eb*1.0-127*1.0));
			iflag=0;if(eb!=0)iflag=1;mantissa=(iflag+fb/(pow(2,23)));
			ftb=sign*exponent*mantissa;
			
			
			if(sa==0)
			{
				fsrt=sqrt(fta);
			}
			fadd=fsrt + ftb; //Add

			fmul = fadd * ftb;//Mul
         
			fsub = fmul - fadd;//Sub

			fdiv = fmul / fsub;//Div
			
			ipfinal=(int*)&fdiv;
			isig = isig ^ *ipfinal;//signature
	
		
		}
	}
		printf("signature_single_precision=%x \n",isig);	
}
