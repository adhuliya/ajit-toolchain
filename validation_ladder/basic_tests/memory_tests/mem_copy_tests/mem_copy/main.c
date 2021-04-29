#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

#define CHUNK 1024

int init_src_array();
int run_test(int length, int NREPS,  double* t);

int main()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);

	ee_printf("Starting\n");

	init_src_array();
	ee_printf("Done initialising array\n");
	int err = 0;
	int i;
	double t;

	err = run_test (CHUNK, NITERS, &t);
	ee_printf("1K: err=%d t=%f seconds\n", err, t);

	err = run_test (4*CHUNK, NITERS, &t);
	ee_printf("4K: err=%d t=%f seconds\n", err, t);

	err = run_test (16*CHUNK, NITERS, &t);
	ee_printf("16K: err=%d t=%f seconds\n", err, t);

	err = run_test (64*CHUNK, NITERS, &t);
	ee_printf("64K: err=%d t=%f seconds\n", err, t);

	ee_printf("Done\n");

	return(1);
}


