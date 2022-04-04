#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int lock_address = 0x40080000;
void acquire_mutex_using_swap(int lock_address);
void release_mutex_using_swap(int lock_address);


void enable_serial()
{
	// enable the serial device.
	__ajit_write_serial_control_register__ ( TX_ENABLE );
}


void main_00 () 
{
	acquire_mutex_using_swap(lock_address);
	ee_printf("Hello world from 00\n");
	release_mutex_using_swap(lock_address);
}

void main_01 () 
{
	acquire_mutex_using_swap(lock_address);
	ee_printf("Hello world from 01\n");
	release_mutex_using_swap(lock_address);
}

