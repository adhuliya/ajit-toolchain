#include <stdint.h>
#include "core_portme.h"

//declaration of functions
void circshift (int *incoming, int amt);
void scale (int  fi, int fd_lo, float *t, int *n_data);
int correlate (int *a, int *incoming);
void acquisition();

int main () 
{

	ajit_serial_init();
 
	acquisition();

	return(0);
}
