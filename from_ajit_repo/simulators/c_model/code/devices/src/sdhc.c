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
struct CPUViewOfSDHCRegs cpu_reg_view;
struct SDHCInternalMap internal_map;

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

void readRegister(uint32_t data_out, uint32_t addr,
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
	
	sendPeripheralResponse("SDHC_to_peripheral_bridge_response", data_out);
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
	/* We can replace the switch ladder with the following switch-case format.
	 NOTE: I modified the address defines in ajit_device_addresses for easy processing.
	 uint32_t addr_in = addr;
	 switch (addr_in)
	 {
	 case ADDR_SDHC_ARG_2:
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

void SDHC_CPU_Control()
{
	
	while(1)
	{
		uint8_t rwbar, byte_mask;
		uint32_t addr, data_in;

		getPeripheralAccessCommand("peripheral_bridge_to_SDHC_request",
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
				readRegister(data_out, addr, &cpu_reg_view, &internal_map);
			}
			pthread_mutex_unlock(&Sdhc_lock);	
		}
		
	}
}

int action_reg_arg2()
{
	// RW
	// used with Auto CMD23 to set a 32-bit blk count value
}
int action_reg_blksize()
{
	// Rsvd and RW
	// one portion or sdma
	// blk size of data ttrnafers for cmd17, cmd18, cmd24, cmd25 and cmd53
}
int action_reg_blkcount()
{
	// RW
	// enabled when 'block count enable' in 'transfer mode' is set to 1
	// valid for only multiple block transfers
	// host driver set this value and host controller decrements the value
	// according to the tranfered blocks; stops when reaches zero
	// can be accessed onlywhen no transactions is executing; during data transfer
	// ignore write and read will be incorrect
}
int action_reg_arg1()
{
	// RW
}
int action_reg_txmode()
{
	// Rsvd and RW
	// used to control the operation of data transfer
	// to prevent data loss host controller shall implement write protection during
	// data transfers; writes to this reg sahll be ignroes when 'comand inhibit (DAT)'
	// in 'present state reg' is 1
}
int action_reg_cmd()
{
	// host driver shall check the 'command inhibit (DAT)' and 'vommand inhibit (CMD)'
	// bits in 'present state' reg beforewriting to thid reg
	// writing to the upper byte triggersSD command generation
	// host controller doesn't protect for writing when 'command inhibit(CMD)' is set
}
int action_reg_rsp0();
int action_reg_rsp1();
int action_reg_rsp2();
int action_reg_rsp3();
int action_reg_rsp4();
int action_reg_rsp5();
int action_reg_rsp6();
int action_reg_rsp7();
int action_reg_buffr_data_port()
{
	// RW
	// foraccessing host controller buffer
}
int action_reg_psr()
{
	// Rsvvd, RO and ROC
	// host driver can get the status of the host controller
	// from this 32-bit read-only reg
}
int action_reg_pwr_ctrl();
int action_reg_host_ctrl();
int action_reg_wakeup_ctrl();
int action_reg_blk_gap_ctrl();
int action_reg_clk_ctrl();
int action_reg_sw_rst()
{
	// write 1 to all the unrsvd bits for resetting
	// after completing reset clear all bits
	// 
	// affects the following regs
	// 	buffer data port reg
	// 	Present state reg
	// 	blk gap ctrl reg
	// 	normal intr status reg
	// 	
}
int action_reg_timeout_ctrl();
int action_reg_nrml_itr_status();
int action_reg_err_itr_status();
int action_reg_nrml_itr_status_en();
int action_reg_err_itr_status_en();
int action_reg_nrml_itr_signal_en();
int action_reg_err_itr_signal_en();
int action_reg_acmd_err_status();
int action_reg_host_ctrl2();
int action_reg_cap()
{
	// whatever the case, values/states wont change
	// writes are ignored
	return -1;
}
int action_reg_max_current_cap()
{
	// whatever the case, values/states wont change
	// writes are ignored
	return -1;
}
int action_reg_force_event_autoCMD_err_stat();
int action_reg_force_event_autoCMD_err_interrupt_stat();
int action_reg_adma_err_status()
{
	// DMA not present
	return -1;
}
int action_reg_adma_sys_addr()
{
	// DMA not present
	return -1;
}
int action_reg_preset_value();
int action_reg_shared_bus_ctrl()
{
	// optional
	// relavent when shared bus is used
	return -1;
}
int action_reg_slot_itr()
{
	// ROC
	// writes are ignored
	// relavent nly when there are slots
	return 0;
}
int action_reg_host_controller_version()
{
	// whatever the case, values/states wont change
	// writes are ignored
	return -1;	
}

void reg_set(uint32_t addr)
{
	// logic to set 1 as value for the mentioned reg
}

void reg_clear(uint32_t addr)
{
	// logic to set 0 as the value in the reg passed on
}
