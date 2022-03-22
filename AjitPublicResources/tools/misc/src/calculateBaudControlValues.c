#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint32_t gcd(uint32_t a, uint32_t b)
{
	uint32_t ret_val = a;

	if(a == 0)
		ret_val = b;
	else if(b==0)
		ret_val = a;
	else if (a > b) 
	{
		a = a%b;
		ret_val = gcd(a,b);
	}
	else if (a < b)
	{
		b = b%a;
		ret_val = gcd(a,b);
	}
	else
		ret_val = a;

	return(ret_val);
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		fprintf(stderr,"Usage:\n %s <baud-rate> <clock-frequency-in-hertz>\n", argv[0]);
		return(1);
	}

	uint32_t baud_rate = atoi(argv[1]);
	uint32_t clk_freq  = atoi(argv[2]);

	uint32_t gcd_val = gcd(16*baud_rate, clk_freq);
	fprintf(stderr,"Info: gcdval=%d\n", gcd_val);

	uint32_t baud_freq = (16*baud_rate)/gcd_val;
	uint32_t baud_limit = (clk_freq/gcd_val)-baud_freq;
	if((clk_freq/gcd_val) < baud_freq)
		fprintf(stderr,"Error: reduce the baud rate\n");	
	else
	{
		if((baud_limit & (~ 0xffff)) != 0)
			fprintf(stderr,"Error: baud-limit exceeds precision\n");	
		else if((baud_freq & (~ 0xfff)) != 0)
			fprintf(stderr,"Error: baud_freq exceeds precision\n");	
		else
		{

			uint32_t baud_control_word =  
					((baud_limit & 0xffff) << 16) | (baud_freq & 0xfff);
			fprintf(stdout,"Info: Baudrate %d ClkFreq %d:  Baud-freq = %d, Baud-limit= %d Baud-control=0x%08x\n" , 
					baud_rate, clk_freq, 
					baud_freq, baud_limit, baud_control_word);
		}
	}
}

