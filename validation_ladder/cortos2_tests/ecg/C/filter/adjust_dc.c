#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main (int argc, char* argv[])
{
	if(argc < 2)
	{
		fprintf(stderr,"Usage: %s coeff-file \n", argv[0]);
		return(1);
	}

	int32_t coeff_sum = 0;

	int32_t filter_coeffs[1024];
	FILE* fc = fopen(argv[1],"r");
	if(fc == NULL)
	{
		fprintf(stderr,"Error: filter coefficient file %s could not be opened\n", argv[1]);
		return(1);
	}

	// read filter coefficients.
	int I=0;
	while (!feof(fc))
	{
		char line_buffer[256];
		char* fs = fgets(line_buffer,255, fc);
		if(fs == NULL)
			break;

		if(line_buffer[0] == '!')
		{
			fprintf(stdout,"%s", line_buffer);
			continue;
		}

		int32_t x;
		int n = sscanf(line_buffer,"%d", &x);

		if((n == 0) || (n == EOF))
			break;

		filter_coeffs[I] = x;

		coeff_sum += x;
		I++;
	}
	fclose(fc);

	int32_t adj = coeff_sum/I;
	fprintf(stderr,"Filter coeff sum is %d, adjustment = %d\n", coeff_sum, adj);

	int J;
	for(J = 0; J < I; J++)
	{
		fprintf(stdout,"%d\n", filter_coeffs[J] - adj);
	}

	return(0);
}

