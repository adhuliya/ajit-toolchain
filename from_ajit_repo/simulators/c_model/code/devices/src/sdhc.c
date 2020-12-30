/*	SDHC.c

AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 28 Dec 2020 

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
struct CPUViewOfSDHCRegs cpu_reg_view;
struct SDHCInternalMap internal_map;

// **** Thread declarations ******//
void SDHC_Control();
DEFINE_THREAD(SDHC_Control);

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

	register_pipe("peripheral_bridge_to_sdhc_request", depth, 64, 0);
	register_pipe("sdhc_to_peripheral_bridge_response", depth, 32, 0);	
	
	set_pipe_is_read_from("peripheral_bridge_to_sdhc_request");
	set_pipe_is_written_into("sdhc_to_peripheral_bridge_response");
}

void start_sdhc_threads()
{
	register_sdhc_pipes();
	sdhc_initialize();

	PTHREAD_DECL(SDHC_Control);
	PTHREAD_CREATE(SDHC_Control);
}

void readSDHCRegister(uint32_t data_out, uint32_t addr,
 struct CPUViewOfSDHCRegs *str, struct SDHCInternalMap *int_str)
{
	if (addr == (0xffffff & ADDR_SDHC_ARG_2))
	{
		uint8_t size=4;
		void *dest = &(str->argument2);//cpu side regs are destination here
		void *source = &(int_str->argument2);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->argument2;
	}
	else if (addr == (0xffffff & ADDR_SDHC_BLOCK_SIZE))
	{
		uint8_t size=2;
		void *dest = &(str->blk_size);//cpu side regs are destination here
		void *source = &(int_str->blk_size);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->blk_size;
	}
	else if (addr == (0xffffff & ADDR_SDHC_BLOCK_COUNT))
	{
		uint8_t size=2;
		void *dest = &(str->blk_count);//cpu side regs are destination here
		void *source = &(int_str->blk_count);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->blk_count;
	}
	else if (addr == (0xffffff & ADDR_SDHC_ARG_1))
	{
		uint8_t size=4;
		void *dest = &(str->argument1);//cpu side regs are destination here
		void *source = &(int_str->argument1);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->argument1;	
	}
		else if (addr == (0xffffff & ADDR_SDHC_TRANSFER_MODE))
	{
		uint8_t size=2;
		void *dest = &(str->tx_mode);//cpu side regs are destination here
		void *source = &(int_str->tx_mode);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->tx_mode;
	}
	sendPeripheralResponse("sdhc_to_peripheral_bridge_response", data_out);
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
		void *dest = &(int_str->argument2);//internal regs are destionation here
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

	else if (addr== (0xffffff & ADDR_SDHC_ARG_1))
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
	/* We can replace the if-else ladder with the following switch-case format.
	 NOTE: I modified the address defines in ajit_device_addresses for easy processing.
	 uint32_t addr_in = addr;
	 switch (addr_in)
	 {
	 case (0xffffff & ADDR_SDHC_ARG_2):
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
	 	break;
	 default:
	 	break;
	 }	*/

//to be used soon:	sdhc_tx_buffer = 1;//load the updated value in a pipe
}

void SDHC_Control()
{
	register_sdhc_pipes();
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
			
			if((addr>=ADDR_SDHC_ARG_2)&&(addr<=ADDR_SDHC_HOST_CONTROLLER_VERSION))
			{
			/*	switch (addr)
				{
					case (0xFFFFFF & ADDR_SDHC_ARG_2):
						// RW
						// used with Auto CMD23 to set a 32-bit blk count value

					break;

					case (0xFFFFFF & ADDR_SDHC_BLOCK_SIZE):
						// Rsvd & RW
						// one portion or sdma
						// blk size of data ttrnafers for cmd17, cmd18, cmd24, cmd25 and cmd53

					break;

					case (0xffffff & ADDR_SDHC_BLOCK_COUNT):
						// RW
						// enabled when 'block count enable' in 'transfer mode' is set to 1
						// valid for the case, values/states wont change
						// writes a only multiple block transfers
						// host driver set this value and host controller decrements the value
						// according to the tranfered blocks; stops when reaches zero
						// can be accessed onlywhen no transactions is executing; during data transfer
						// ignore write and read will be incorrect

					break;

					case (0xFFFFFF & ADDR_SDHC_ARG_1):
						// RW

					break;
					
					case (0xFFFFFF & ADDR_SDHC_TRANSFER_MODE):
						// Rsvd & RW
						// used to control the operation of data transfer
						// to prevent data loss host controller shall implement write protection during
						// data transfers; writes to this reg sahll be ignroes when 'comand inhibit (DAT)'
						// in 'present state reg' is 1

					break;

					case (0xffffff & ADDR_SDHC_REGISTER_COMMAND):
						// Rsvd & RW
						// host driver shall check the 'command inhibit (DAT)' and 'vommand inhibit (CMD)'
						// bits in 'present state' reg beforewriting to thid reg
						// writing to the upper byte triggersSD command generation
						// host controller doesn't protect for writing when 'command inhibit(CMD)' is set
					break;

					case (0xffffff & ADDR_SDHC_RESPONSE0):
					case (0xffffff & ADDR_SDHC_RESPONSE1):
					case (0xffffff & ADDR_SDHC_RESPONSE2):
					case (0xffffff & ADDR_SDHC_RESPONSE3):
					case (0xffffff & ADDR_SDHC_RESPONSE4):
					case (0xffffff & ADDR_SDHC_RESPONSE5):
					case (0xffffff & ADDR_SDHC_RESPONSE6):
					case (0xffffff & ADDR_SDHC_RESPONSE7):
						// ROC
						// host driver shall check the 'command inhibit (DAT)' and 'command inhibit (CMD)'
						// bits in 'present state' reg before writing to this reg
						// writing to the upper byte triggers SD command generation
						// host controller doesn't protect for writing when 'command inhibit(CMD)' is set
					
					break;
					
					case (0xffffff & ADDR_SDHC_BUFFER_DATA_PORT):
						// RW
						// for accessing host controller buffer
					break;

					case (0xffffff & ADDR_SDHC_PRESENT_STATE):
						// Rsvd, RO & ROC
						// host driver can get the status of the host controller
						// from this 32-bit read-only reg
					break;

					case (0xffffff & ADDR_SDHC_HOST_CONTROL_1):
						// RW
					case (0xffffff & ADDR_SDHC_POWER_CONTROL):
						// Rsvd & RW
					case (0xffffff & ADDR_SDHC_BLOCK_GAP_CONTROL):
						// Rsvd, RW & RWAC
					case (0xffffff & ADDR_SDHC_WAKEUP_CONTROL):
						// Rsvd & RW
					case (0xffffff & ADDR_SDHC_CLOCK_CONTROL):
						// RW & ROC
					case (0xffffff & ADDR_SDHC_TIMEOUT_CONTROL):
						// Rsvd & RW

					break;

					case (0xffffff & ADDR_SDHC_SOFTWARE_RESET):
						// Rsvd & RWAC
						// write 1 to all the unrsvd bits for resetting
						// after completing reset clear all bits
						// 
						// affects the following regs
						// 	buffer data port reg
						// 	Present state reg
						// 	blk gap ctrl reg
						// 	normal intr status reg
					break;

					case (0xffff & ADDR_SDHC_NORMAL_INTR_STATUS):
						// Rsvd, ROC & RW1C 
					case (0xffff & ADDR_SDHC_ERROR_INTR_STATUS):
						// Rsvd & RW1C
					case (0xffff & ADDR_SDHC_NORMAL_INTR_STATUS_EN):
						// Rsvd, RW & RO
					case (0xffff & ADDR_SDHC_ERROR_INTR_STATUS_EN):
						// Rsvd & RW
					case (0xffff & ADDR_SDHC_NORMAL_INTR_SIGNAL_EN):
						// Rsvd, RW & RO
					case (0xffff & ADDR_SDHC_ERROR_INTR_SIGNAL_EN):
						// Rsvd & RW
					case (0xffff & ADDR_SDHC_AUTO_CMD_ERROR_STATUS):
						// Rsvd & ROC
					case (0xffff & ADDR_SDHC_HOST_CONTROL_2):
						// Rsvd, RW & RWAC

					break;

					case (0xffffff & ADDR_SDHC_CAPS):
						// Rsvd & HwInit
						// whatever the case, values/states wont change
						// writes are ignored
					break;

					case (0xffffff & ADDR_SDHC_MAX_CURRENT_CAPS):
					case (0xffffff & ADDR_SDHC_MAX_CURRENT_CAPS_RES):
						// Rsvd & HwInit
						// whatever the case, values/states wont change
						// writes are ignored
					break;
					
					case (0xffffff & ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT):
						// Rsvd & WO
					case (0xffffff & ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT_R):
						// Rsvd & WO
					
					break;

					case (0xffffff & ADDR_SDHC_ADMA_ERR_STAT):
						// Rsvd & ROC
						// DMA not present
					case (0xffffff & ADDR_SDHC_ADMA_SYSTEM_ADDR):
						// RW
						// DMA not present
					break;
					
					case (0xffffff & ADDR_SDHC_HOST_PRESET_VALUES):
						// Rsvd & HwInit

					break;

					case (0xffffff & ADDR_SDHC_SHARED_BUS_CTRL):
						// Rsvd, RW & HwInit
						// optional
						// relavent when shared bus is used
					break;

					case (0xffffff & ADDR_SDHC_SLOT_INTR_STATUS):
						// Rsvd & ROC
						// writes are ignored
						// relavent only when there are slots
					break;

					case (0xffffff & ADDR_SDHC_HOST_CONTROLLER_VERSION):
						// HwInit
						// whatever the case, values/states wont change
						// writes are ignored
					break;								
				default:
					break;
				}*/
				updateRegister(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			}
			pthread_mutex_unlock(&Sdhc_lock);	
			data_out=0;
		}
		else
		{
			pthread_mutex_lock(&Sdhc_lock);
			if((addr<=ADDR_SDHC_ARG_2)&&(addr>=ADDR_SDHC_HOST_CONTROLLER_VERSION))
			{
				readSDHCRegister(data_out, addr, &cpu_reg_view, &internal_map);
			}
			pthread_mutex_unlock(&Sdhc_lock);	
		}
		
	}
}

void reg_set(uint32_t addr)
{
	// logic to set 1 as value for the mentioned reg
}

void reg_clear(uint32_t addr)
{
	// logic to set 0 as the value in the reg passed on
}
