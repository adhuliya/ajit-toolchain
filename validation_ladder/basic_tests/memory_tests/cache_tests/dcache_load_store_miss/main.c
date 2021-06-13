#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

void init_src_array();
int run_test(int length,int *iters, double* t);

int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);

	ee_printf("Starting \n");
	init_src_array();
	int err = 0;
	int i,iters;
	double t;

	err = run_test (LENGTH, &iters, &t);
	ee_printf("\rFor %d load-stores with definite cache misses, time elapsed is t=%f seconds",LENGTH,t);
	ee_printf("\rSuccesful load-stores are %d and err=%d\n",iters, err);
	ee_printf("\rDone\n");

	return(1);
}


