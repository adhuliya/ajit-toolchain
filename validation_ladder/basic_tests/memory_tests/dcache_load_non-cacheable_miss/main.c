#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int init_src_array();
int run_test(int length, double* t);

int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);

	ee_printf("Starting \n");
	int err = 0;
	int i;
	double t;

	err = run_test (256, &t);
	ee_printf("For 256 Bytes, time elapsed is t=%f seconds,\n and err=%d\n", t, err);
	ee_printf("Done\n");

	return(1);
}


