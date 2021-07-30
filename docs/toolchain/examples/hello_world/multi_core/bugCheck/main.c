#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "core_portme.h"

int lock_address = 0x44000;
void acqiure_mutex_using_swap(lock_address);
void release_mutex_using_swap(lock_address);


void enable_serial()
{
	// enable the serial device.
	__ajit_write_serial_control_register__ ( TX_ENABLE );
}


void main_00 () 
{
	//acquire_mutex_using_swap(lock_address);
	acquire_lock();
	ee_printf("Hello world from 00\n");
	//release_mutex_using_swap(lock_address);
	release_lock();
}

void main_01 () 
{
	//acquire_mutex_using_swap(lock_address);
	acquire_lock();
	ee_printf("Hello world from 01\n");
	release_lock();
	//release_mutex_using_swap(lock_address);
}

void main_10 () 
{
	//acquire_mutex_using_swap(lock_address);
	acquire_lock();
	ee_printf("Hello world from 10\n");
	release_lock();
	//release_mutex_using_swap(lock_address);
}

void main_11 () 
{
	//acquire_mutex_using_swap(lock_address);
	acquire_lock();
	ee_printf("Hello world from 11\n");
	release_lock();
	//release_mutex_using_swap(lock_address);
}

