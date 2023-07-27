#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main (int argc, char* argv[])
{
	fprintf(stderr,"Usage: %s  < coeff-file  > header-file\n", argv[0]);

	// read filter coefficients.
	int I=0;
		
	fprintf(stdout,"#ifndef __bpf_coefficients__\n");
	fprintf(stdout,"#define __bpf_coefficients__\n");
	fprintf(stdout,"int16_t bpf_coefficients [128] = {\n");
	while (!feof(stdin))
	{
		char line_buffer[256];
		char* fs = fgets(line_buffer,255, stdin);
		if(fs == NULL)
			break;

		if(line_buffer[0] == '!')
		{
			continue;
		}

		int32_t x;
		int n = sscanf(line_buffer,"%d", &x);

		if((n == 0) || (n == EOF))
			break;


		fprintf(stdout,"%d,\n", x);
		I++;
	}

	while(I < 127)
	{	
		fprintf(stdout,"0,\n");
		I++;
	}
	fprintf(stdout,"0};\n");
	fprintf(stdout, "#endif\n");

	return(0);
}

