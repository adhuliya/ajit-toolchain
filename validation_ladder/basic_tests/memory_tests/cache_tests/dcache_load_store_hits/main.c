#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int init_src_array();
int run_test(int length, double* t, int* result);

int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);

	ee_printf("Starting by filling up arrays\n");

	init_src_array();
	ee_printf("\rDone initialising array\n");
	int err = 0;
	int i;
	double t;
	int res;
	err = run_test (LENGTH, &t, &res);
	ee_printf("\rFor %d load-stores, time elapsed is t=%f seconds,\r\n successful load-srores completed: %d, \n and errors occured=%d\n",LENGTH, t, res+1, err);
	ee_printf("\rDone\n");
 
	return(1);
}


