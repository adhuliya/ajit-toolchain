#include <stdlib.h>
#include <riffa.h>

fpga_t* fpga_open(int v) 
{
	return(NULL);
}

void fpga_reset(void* v)
{
}

void fpga_close(void* v)
{
}

int fpga_send(fpga_t* fpga, int l, void* buf, int nwords, int offset, int last, int timeout)
{
	return(0);
}

int fpga_recv(fpga_t* fpga, int offset, void* r_word, int len, int timeout)
{
	return(0);
}
