
/*==================================================

* File Name 	: 	processor_link.c

* Purpose		: 	A driver for a VC709 platform system, based
		  			around the AJIT processor. It provides the 
		 			API for opening and closing fpga devices
		 			along with sending and receiving 64-bit numbers
		 			to and from the processor core.

* Creation Date :	21-09-2018

* Last Modified : 	Friday 21 September 2018 05:09:16 PM IST

* Created By 	: 	Prathu Baronia, 14D070046 

===================================================*/

#include <stdio.h>
#include "processor_link_internal.h"
#include "processor_link.h"
#include "hardware_description.h"

void* initialize_axi_link(char* name, char* resource_file)
{
		fprintf(stderr,"Initializing AXI link ...\n\n");
		return ((void*) open_fpga(name, resource_file));
}

int close_axi_link(void* fpga_device)
{
		fprintf(stderr,"Closing AXI link ...\n\n");
		return close_fpga((FPGA*) fpga_device);
}

// return 0 on success.
int write_to_axi_dram(void* vfpga_device, uint32_t dram_internal_address, uint32_t dram_write_word)
{
	FPGA* fpga_device = (FPGA*) vfpga_device;

	if(fpga_device == NULL)
	{ 	
		fprintf(stderr,"FPGA pointer is passed as NULL to write_to_axi_dram \n\n");
		return -1;
	}

	if(dram_internal_address <= RAM_UPPER_LIMIT && dram_internal_address >= RAM_LOWER_LIMIT)
	{
			return fpga_axi_write(fpga_device, dram_internal_address, dram_write_word);
	}
	else
	{
			fprintf(stderr,"Invalid Address range for DRAM, Should be between %d and %d \n\n",RAM_LOWER_LIMIT,RAM_UPPER_LIMIT);
			return -1;
	}
	
}

// return 0 on success.
int read_from_axi_dram(void* vfpga_device, uint32_t dram_internal_address, uint32_t *dram_read_word)
{
	FPGA* fpga_device = (FPGA*) vfpga_device;

	if(fpga_device == NULL)
	{ 	
		fprintf(stderr,"FPGA pointer is passed as NULL to read_from_axi_dram \n\n");
		return -1;
	}

	if(dram_internal_address <= RAM_UPPER_LIMIT && dram_internal_address >= RAM_LOWER_LIMIT)
	{
			return fpga_axi_read(fpga_device, dram_internal_address, dram_read_word);
	}
	else
	{
			fprintf(stderr,"Invalid Address range for DRAM, Should be between %d and %d \n\n",RAM_LOWER_LIMIT,RAM_UPPER_LIMIT);
			return -1;
	}

}

int recv_u64_from_processor(void* vfpga_device, uint64_t* r_word)
{
		FPGA* fpga_device = (FPGA*) vfpga_device;
		uint32_t read_result_lower,read_result_higher;

		if(fpga_device == NULL)
			return -1;

		if((fpga_device->fd)!=0) 
			fpga_device = open_fpga(fpga_device->name, fpga_device->resource_file);

		if((fpga_device->fd)!=0) return -1;

		/* 
		 *  One read for data_valid signal and the two reads for two 32 bit values
		 *  then merge those to form read_result 
		 */

		uint32_t success_status = 0 ;

		/* Wait until the data valid signal is '1' */

		while( success_status != 1)
		{
				fpga_axi_read(fpga_device, FIFO_TO_AXI_SUCCESS_REGISTER,  &success_status);
				sleep(0.001);
		}

		fpga_axi_read(fpga_device,FIFO_TO_AXI_DATA_REGISTER_1,&read_result_lower);

		fpga_axi_read(fpga_device,FIFO_TO_AXI_DATA_REGISTER_2,&read_result_higher);

		*r_word = (uint64_t) read_result_higher << 32 | read_result_lower ;	
		return 0;
}

int send_u64_to_processor(void* vfpga_device ,uint64_t* s_word)
{
		FPGA* fpga_device = (FPGA*) vfpga_device;
		uint32_t write_val_lower, write_val_higher;

		if(fpga_device == NULL)
			return -1;

		if((fpga_device->fd)!=0) fpga_device = open_fpga(fpga_device->name, fpga_device->resource_file);

		if((fpga_device->fd)!=0) return -1;

		write_val_lower  = *(s_word) && 0x0000FFFF; /* split the 64 bit word for lower nibble  */
		write_val_higher = *(s_word) && 0xFFFF0000; /* split the 64 bit word for higher nibble */

		/* Two writes for data_lower and data_higher and 1 write for start bit, and then
		 *  wait for write_status to come.
		 */

		/* Write data_lower */

		fpga_axi_write(fpga_device, AXI_TO_FIFO_DATA_REGISTER_1, write_val_lower);

		/* Write data_higher */

		fpga_axi_write(fpga_device, AXI_TO_FIFO_DATA_REGISTER_2, write_val_higher);

		/* Write start bit */

		fpga_axi_write(fpga_device, AXI_TO_FIFO_START_REGISTER, 1);

		/* Wait until write success is 1 */

		uint32_t write_status = 0;
		while(write_status == 1)
		{
				fpga_axi_read(fpga_device, AXI_TO_FIFO_SUCCESS_REGISTER,  &write_status);
				sleep(0.001);
		}

		return 0;
}
