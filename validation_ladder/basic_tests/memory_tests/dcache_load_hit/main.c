#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int init_src_array();
int run_test(int length, double* t, int* result);

int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);

	ee_printf("Starting by filling up an array of 256 bytes\n");

	init_src_array();
	ee_printf("Done initialising array\n");
	int err = 0;
	int i;
	double t;
	int res;
	err = run_test (256, &t, &res);
	ee_printf("For 256 Bytes, time elapsed is t=%f seconds,\n runs completed: %d, \n and err=%d\n", t, res, err);
	ee_printf("Done\n");

	return(1);
}


