/*	SDHC.c

AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 26 Dec 2020 

Model that emulates a version 3.00 SD Host Controller
and an SD card for verification purposes.

Device Registers:
	SDHC registers
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#ifdef SW
#include <stdio.h>
#include <unistd.h>
#endif
#include <pthread.h>

#include "Ancillary.h"
#include "Ajit_Hardware_Configuration.h"
#include "RequestTypeValues.h"
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "Device_utils.h"

#include "Sdhc.h"
#include "sd.h"

uint32_t sdhc_tx_buffer;
uint32_t sdhc_rx_buffer;
uint8_t SDHC_INT_OUT;

// **** Thread declarations ******//
void SDHC_CPU_Control();
DEFINE_THREAD(SDHC_CPU_Control);

//Mutex for locking state variables (only control register in this case)
pthread_mutex_t Sdhc_lock = PTHREAD_MUTEX_INITIALIZER;



void sdhc_initialize()
{
	sdhc_tx_buffer=0;
	sdhc_rx_buffer=0;
	//interrupt output signal 
	SDHC_INT_OUT = 0;
	write_uint8("SDHC_to_IRC_INT",SDHC_INT_OUT);
}


void register_sdhc_pipes()
{
	//signal going from SDHC to IRC
	register_port("SDHC_to_IRC_INT",8,1);
	set_pipe_is_written_into("SDHC_to_IRC_INT");

	//pipes between system bus and SDHC device
	int depth=1;

	register_pipe("peripheral_bridge_to_SDHC_request", depth, 64, 0);
	register_pipe("SDHC_to_peripheral_bridge_response", depth, 32, 0);	
	
	set_pipe_is_read_from("peripheral_bridge_to_SDHC_request");
	set_pipe_is_written_into("SDHC_to_peripheral_bridge_response");
}

void start_sdhc_threads()
{
	register_sdhc_pipes();
	sdhc_initialize();

	PTHREAD_DECL(SDHC_CPU_Control);
	PTHREAD_CREATE(SDHC_CPU_Control);
}

void updateRegister(uint32_t data_in, uint32_t addr, uint8_t byte_mask,
 struct CPUViewOfSDHCRegs *str, struct SDHCInternalMap *int_str)
{
	uint32_t data_in_masked = insertUsingByteMask(0, data_in, byte_mask);
	if (addr== (0xffffff & ADDR_SDHC_ARG_2))
	{
	uint8_t temp1 = getSlice32(data_in_masked,7,0);
	str->argument2[0] = temp1;
	uint8_t temp2 = getSlice32(data_in_masked,15,8);
	str->argument2[1] = temp2;
	uint8_t temp3 = getSlice32(data_in_masked,23,16);
	str->argument2[2] = temp3;
	uint8_t temp4 = getSlice32(data_in_masked,31,24);
	str->argument2[3] = temp4;
	uint8_t size=4;
	void *dest = &(int_str->argument2);
	void *source = &(str->argument2);
	memcpy(dest,source,size);
	}

	else if (addr== (0xffffff & ADDR_SDHC_BLOCK_SIZE))
	{
	uint8_t temp1 = getSlice32(data_in_masked,7,0);
	str->blk_size[0] = temp1;
	uint8_t temp2 = getSlice32(data_in_masked,15,8);
	str->blk_size[1] = temp2;
	uint8_t size=2;
	void *dest = &(int_str->blk_size);
	void *source = &(str->blk_size);
	memcpy(dest,source,size);
	}

	else if (addr== (0xffffff & ADDR_SDHC_BLOCK_COUNT))
	{
	uint8_t temp1 = getSlice32(data_in_masked,7,0);
	str->blk_count[0] = temp1;
	uint8_t temp2 = getSlice32(data_in_masked,15,8);
	str->blk_count[1] = temp2;
	uint8_t size=2;
	void *dest = &(int_str->blk_count);
	void *source = &(str->blk_count);
	memcpy(dest,source,size);
	}

	else 	if (addr== (0xffffff & ADDR_SDHC_ARG_1))
	{
	uint8_t temp1 = getSlice32(data_in_masked,7,0);
	str->argument1[0] = temp1;
	uint8_t temp2 = getSlice32(data_in_masked,15,8);
	str->argument1[1] = temp2;
	uint8_t temp3 = getSlice32(data_in_masked,23,16);
	str->argument1[2] = temp3;
	uint8_t temp4 = getSlice32(data_in_masked,31,24);
	str->argument1[3] = temp4;
	uint8_t size=4;
	void *dest = &(int_str->argument1);
	void *source = &(str->argument1);
	memcpy(dest,source,size);
	}

	else if(addr == (0xffffff & ADDR_SDHC_TRANSFER_MODE))
	{
	uint8_t temp1 = getSlice32(data_in_masked,7,0);
	str->tx_mode[0] = temp1;
	uint8_t temp2 = getSlice32(data_in_masked,15,8);
	str->tx_mode[1] = temp2;
	uint8_t size=2;
	void *dest = &(int_str->tx_mode);
	void *source = &(str->tx_mode);
	memcpy(dest,source,size);
	}
//to be used soon:	sdhc_tx_buffer = 1;//load the updated value in a pipe
}

void SDHC_CPU_Control()
{
struct CPUViewOfSDHCRegs cpu_reg_view;
struct SDHCInternalMap internal_map;
	while(1)
	{
		uint8_t rwbar, byte_mask;
		uint32_t addr, data_in;

		getPeripheralAccessCommand("peripheral_bridge_to_sdhc_request",
			&rwbar, &byte_mask, &addr, &data_in);
		uint32_t data_out=0;

		if(!rwbar)
		{
			//***lock the state variables***
		pthread_mutex_lock(&Sdhc_lock);	
			
			if((addr<=ADDR_SDHC_ARG_2)&&(addr>=ADDR_SDHC_HOST_CONTROLLER_VERSION))
			{
				updateRegister(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			}
		pthread_mutex_unlock(&Sdhc_lock);	
		}
		else
		{
		pthread_mutex_lock(&Sdhc_lock);
			if((addr<=ADDR_SDHC_ARG_2)&&(addr>=ADDR_SDHC_HOST_CONTROLLER_VERSION))
			{
//function for reading register values
			}
		pthread_mutex_unlock(&Sdhc_lock);	
		}
		
	}
}


