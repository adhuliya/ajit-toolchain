#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int  ok_flag[4] = {0,0,0,0};

int f0=0;
int f1=0;
int f2=0;
int f3=0;

void acquire_lock ();
void release_lock ();

void main_0 () 
{
	acquire_lock ();
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	ee_printf ("HI FROM CPU-0\n");
	__ajit_write_serial_control_register__ ( 0 );
	release_lock ();
}

void main_1 () 
{
	acquire_lock ();
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	ee_printf ("HI FROM CPU-1\n");
	__ajit_write_serial_control_register__ ( 0 );
	release_lock ();
}

void main_2 () 
{
	acquire_lock ();
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	ee_printf ("HI FROM CPU-2\n");
	__ajit_write_serial_control_register__ ( 0 );
	release_lock ();
}

void main_3 () 
{
	acquire_lock ();
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	ee_printf ("HI FROM CPU-3\n");
	__ajit_write_serial_control_register__ ( 0 );
	release_lock ();
}

