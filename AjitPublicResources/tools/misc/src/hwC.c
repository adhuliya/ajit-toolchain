#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint32_t my_gcd(uint32_t a, uint32_t b)
{
	int loop_counter = 0;
	uint32_t ret_val = a;
	while(1)
	{
		loop_counter++;
		if((a == 1) || (b==1))
		{
			ret_val = 1;
			break;
		}
		else if(a == b)
		{
			ret_val = a;
			break;
		}
		else 
		{
			if( a < b)
				b = b-a;
			else
				a = a-b;
		}
	}
	fprintf(stderr,"gcd: loop_counter= %d.\n", loop_counter);
	return(ret_val);
}

uint32_t my_div(uint32_t a, uint32_t b)
{
	uint32_t ret_val = 0;
	uint32_t loop_counter = 0;

	while(1)
	{
		loop_counter++;
		if((a==0) || (a < b))
			break;
		else
		{
			a = a-b;
			ret_val++;
		}
	}
	fprintf(stderr,"div: loop_counter= %d.\n", loop_counter);
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

	uint32_t gcd_val = my_gcd(16*baud_rate, clk_freq);
	fprintf(stderr,"Info: gcdval=%d\n", gcd_val);

	uint32_t baud_freq = my_div((16*baud_rate),gcd_val);
	uint32_t baud_limit = my_div(clk_freq,gcd_val)-baud_freq;

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

