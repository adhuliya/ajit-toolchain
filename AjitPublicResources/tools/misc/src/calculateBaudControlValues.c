#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int baud_limit_width = 16;
int baud_freq_width  = 12;

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

	if(argc >= 4)
		baud_limit_width = atoi(argv[3]);
	if(argc >= 5)
		baud_freq_width = atoi(argv[4]);

	fprintf(stderr,"baud-limit-width = %d, baud-freq-width = %d\n", baud_limit_width, baud_freq_width);

	uint32_t baud_rate = atoi(argv[1]);
	uint32_t clk_freq  = atoi(argv[2]);

	uint32_t  bl_mask = (1 << baud_limit_width)-1;
	uint32_t  bf_mask = (1 << baud_freq_width) -1 ;	

	uint32_t gcd_val = gcd(16*baud_rate, clk_freq);
	fprintf(stderr,"Info: gcdval=%d\n", gcd_val);

	uint32_t baud_freq = (16*baud_rate)/gcd_val;
	uint32_t baud_limit = (clk_freq/gcd_val)-baud_freq;
	fprintf(stderr,"Info: baud_limit=0x%x, baud_freq=0x%x\n", baud_limit, baud_freq);
	if((clk_freq/gcd_val) < baud_freq)
		fprintf(stderr,"Error: reduce the baud rate\n");	
	else
	{
		if((baud_limit & (~ bl_mask)) != 0)
			fprintf(stderr,"Error: baud-limit 0x%x exceeds precision\n", baud_limit);	
		else if((baud_freq & (~ bf_mask)) != 0)
			fprintf(stderr,"Error: baud_freq 0x%x exceeds precision\n", baud_freq);	
		else
		{

			uint32_t baud_control_word =  
					((baud_limit & 0xffff) << 16) | (baud_freq & 0xfff);
			fprintf(stdout,"Info: Baudrate %d ClkFreq %d:  Baud-control=0x%08x\n" , 
					baud_rate, clk_freq, baud_control_word);

			uint32_t baud_control_alt_word = 
				((baud_limit & bl_mask) << baud_limit_width) |
					((baud_freq & bf_mask) << baud_freq_width);
			fprintf(stdout,"Info: Baud-control-v2=0x%08x\n" ,  baud_control_alt_word);
		}
	}
}

