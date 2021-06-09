/*==================================================

* File Name 	: 	processor_link_internal.c

* Purpose		: 	The low level functions for controlling 
					the FPGAs.

* Creation Date : 	21-09-2018

* Last Modified : 	Friday 21 September 2018 05:09:16 PM IST

* Created By 	: 	Prathu Baronia, 14D070046 

===================================================*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <inttypes.h>
#include "processor_link_internal.h"

FPGA* new_fpga(char* fpga_name, char* resource_file)
{
	FPGA* pointer_to_new_fpga = (FPGA*) malloc(sizeof(FPGA));
	pointer_to_new_fpga->name = fpga_name;
	pointer_to_new_fpga->map_base = NULL;
	pointer_to_new_fpga->fd = -1;
	pointer_to_new_fpga->resource_file = strdup(resource_file); 
	return pointer_to_new_fpga;
}

FPGA* open_fpga (char* name, char* resource_file)
{
	// resource_filename should be SYS_FILE kind addresses;

	FPGA* fpga = new_fpga(name, resource_file);	

	if((fpga->fd = open(resource_file, O_RDWR | O_SYNC)) == -1)
	{
		fprintf(stderr,"Failed to open FPGA device \n");
		return NULL;
	}
	
	fpga->map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fpga->fd, 0);
	if((fpga->map_base) == (void*) -1) 
	{
		fprintf(stderr,"Failed to get a map base for FPGA device \n");
		return NULL;
	}

	return fpga;
}

int close_fpga( FPGA* fpga_device)
{
	if(munmap(fpga_device->map_base, MAP_SIZE) == -1)
	{
		fprintf(stderr,"Failed to close FPGA device \n");
		return -1;
	}

	close(fpga_device->fd);
	free(fpga_device);
	return 0;
}

// return 0 on success
int fpga_axi_write(FPGA* fpga_device, uint32_t addr, uint32_t data)
{
	void* write_addr;
	
	off_t target = (unsigned long) addr;

	uint64_t write_val = (unsigned long long) data;

	// Assuming fpga_device pointer was created but it was unable to open the device
	assert (fpga_device->fd >= 0);


	/* Write data */
	write_addr = fpga_device->map_base + (target & MAP_MASK);

	*((uint32_t *) write_addr) = write_val;

	return 0;

}

// return 0 on success
int fpga_axi_read(FPGA* fpga_device, uint32_t addr,  uint32_t *data)
{
	void *read_addr;

	off_t target = (unsigned long) addr;

	// Assuming fpga_device pointer was created but it was unable to open the device
	assert (fpga_device->fd >= 0);

	/* Read data */
	read_addr = fpga_device->map_base + (target & MAP_MASK);
	
	*data = *((uint32_t *) read_addr);

	return 0;
}
