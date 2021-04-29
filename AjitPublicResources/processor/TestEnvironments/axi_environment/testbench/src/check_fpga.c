#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <riffa.h>


int main(int argc, char* argv[])
{
	fpga_t* fpga = fpga_open(0);
	if(fpga == NULL)
	{
		fprintf(stderr,"Error: could not open FPGA.\n");
		return(1);
	}
	fprintf(stderr,"Info: opened FPGA.\n");

	fpga_reset(fpga);
	fprintf(stderr,"Info: reset the FPGA.\n");

	fpga_close(fpga);
	fprintf(stderr,"Info: closed the FPGA.\n");

	return(0);
}
