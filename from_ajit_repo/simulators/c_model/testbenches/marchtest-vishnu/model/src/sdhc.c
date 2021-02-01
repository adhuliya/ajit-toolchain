/*	SDHC.c

AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 14 Jan 2021

Model that emulates a version 3.00 SD Host Controller
and an SD card for verification purposes.

Reference:
	- SD Host Controller Simplified Specification Version 3.00, Feb. 25 2011
		link: https://www.sdcard.org/downloads/pls/archive/index.html
*/

/* FUNCTIONAL DETAIL

 THREADS:
	SDHC controller consists of 2 threads

	1. Thread 'SDHC_Control'
		keeps monitoring requests from CPU and performs
		read/writes to device registers

  DEVICE REGISTERS:
	- The register set is 256 bytes in size
	- Their sizes vary between 8, 16, 32, 64 and 128 bits.
	- List of registers, its size, offset from base address and address defenitions:
		01. Argument 2	 			   (32b)  000h  ADDR_SDHC_ARG_2
		02. Block size	 			   (16b)  004h  ADDR_SDHC_BLOCK_SIZE
		03. Block count	 			   (16b)  006h  ADDR_SDHC_BLOCK_COUNT
		04. Argument 1	 			   (32b)  00Ah  ADDR_SDHC_ARG_1
		05. Transfer Mode 			   (16b)  00Ch  ADDR_SDHC_TRANSFER_MODE
		06. Command	 			   (16b)  00Eh  ADDR_SDHC_REGISTER_COMMAND
		07. Response	 			   (128b) 010h  ADDR_SDHC_RESPONSE0 --> ADDR_SDHC_RESPONSE7
		08. Buffer Data Port			   (32b)  020h  ADDR_SDHC_BUFFER_DATA_PORT
		09. Present State 			   (32b)  024h  ADDR_SDHC_PRESENT_STATE
		10. Host Control 1			   (08b)  028h  ADDR_SDHC_HOST_CONTROL_1
		11. Power Control			   (08b)  029h  ADDR_SDHC_POWER_CONTROL
		12. Block Gap Control			   (08b)  02Ah  ADDR_SDHC_BLOCK_GAP_CONTROL
		13. Wakeup Control			   (08b)  02Bh  ADDR_SDHC_WAKEUP_CONTROL
		14. Clock Control			   (16b)  02Ch  ADDR_SDHC_CLOCK_CONTROL
		15. Timeout Control			   (08b)  02Eh  ADDR_SDHC_TIMEOUT_CONTROL
		16. Softwrae Reset			   (08b)  02Fh  ADDR_SDHC_SOFTWARE_RESET
		17. Normal Interrupt Status		   (16b)  030h  ADDR_SDHC_NORMAL_INTR_STATUS
		18. Error Interrupt Status		   (16b)  032h  ADDR_SDHC_ERROR_INTR_STATUS
		19. Normal Interrupt Status Enable	   (16b)  034h  ADDR_SDHC_NORMAL_INTR_STATUS_EN
		20. Error Interrupt Status Enable	   (16b)  036h  ADDR_SDHC_ERROR_INTR_STATUS_EN
		21. Normal Interrupt Signal Enable	   (16b)  038h  ADDR_SDHC_NORMAL_INTR_SIGNAL_EN
		22. Error Interrupt Signal Enable	   (16b)  03Ah  ADDR_SDHC_ERROR_INTR_SIGNAL_EN
		23. Auto CMD Error Status		   (16b)  03Ch  ADDR_SDHC_AUTO_CMD_ERROR_STATUS
		24. Host Control 2			   (16b)  03Eh  ADDR_SDHC_HOST_CONTROL_2
		25. Capabilities			   (64b)  040h  ADDR_SDHC_CAPS
		26. Maximum Current Cpabilities		   (64b)  048h  ADDR_SDHC_MAX_CURRENT_CAPS --> ADDR_SDHC_MAX_CURRENT_CAPS_RES
		27. Force Event For Auto CMD Error Status  (16b)  050h  ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT
		28. Force Event For Error Interrupt Status (16b)  052h  ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT
		29. ADMA Error Status			   (08b)  054h  ADDR_SDHC_ADMA_ERR_STAT
		30. ADMA System Address			   (64b)  058h  ADDR_SDHC_ADMA_SYSTEM_ADDR
		31. Preset Value			   (128b) 060h  ADDR_SDHC_HOST_PRESET_VALUES
		32. Shared bus Control			   (32b)  0E0h  ADDR_SDHC_SHARED_BUS_CTRL
		33. Slot Interrupt Status		   (16b)  0FCh  ADDR_SDHC_SLOT_INTR_STATUS
		34. Host Controller Version		   (16b)  0FEh  ADDR_SDHC_HOST_CONTROLLER_VERSION
	- Register attributes :
		RO	: read-only register; register bits are read only and cannot be altered
				by software or any reset operation. Writes to these bits are ignored.
		ROC	: read-only status; these bits are initialised to zero at reset. Write to these
				bits are ignored.
		RW	: read-write register; register bits are read-write and may be either set or
				cleared by software to the desired state.
		RW1C	: read-only status, write-1-to-clear status; register bits indicate status when read,
				a set bit indicating a status event maybe  cleared by writing a 1. Writing a 0
				to RW1C bit has no effect.
		RWAC	: read-write, automatic clear register; the host driver requests a host controller
				operation by setting the bit. The host controller shal clear the bit automatically
				when the operation complete. Writing a 0 to RWAC bit has no effect.
		HwInit	: hardware intialised; register bits are intialised by firmware. Bits are read-only after
				initialisation, and write to these bits are ignored.
		Rsvd	: reserved; these bits are initialised to zero and writes to them are ignored
		WO	: write-only register; It is not physically implimented register. Rather, it is a ddress
				at which registers can be written.
	- Details of each register is described in the corresponding switch..case instance in SDHC_Control

SDHC_Control:
	Polls CPU commands and do corresponding register updates.

2. SDHC_Internal_ops:
	This thread will take special actions after read and write operations are performed to 
	the register bank. Interrupts are handled in this thread.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "Ancillary.h"
#include "Ajit_Hardware_Configuration.h"
#include "RequestTypeValues.h"
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "Device_utils.h"

#include "Sdhc.h"

// #define DEBUG

#define READ	1
#define	WRITE	0

sdhc_reg_cpu_view cpu_reg_view = {0};
sdhc_reg_internal_view internal_map = {0};

uint32_t read_or_write_sdhc_reg(uint32_t addr, uint8_t bytemask, sdhc_reg_cpu_view *cpu_view, 
					sdhc_reg_internal_view *internal_view, uint32_t data_in, uint8_t rwbar)
{
	uint32_t data_in_masked = 0, ret_val = 0;
	void *dest, *source;

	if(!rwbar) data_in_masked = insertUsingByteMask(0, data_in, bytemask);

#ifdef DEBUG
		printf("Data in masked for %x = %x\n", addr, data_in_masked);
#endif
	uint8_t offset = (uint8_t)(addr - (0xFFFFFF & ADDR_SDHC_ARG_2));
	
	if ( addr == (0xFFFFFF & ADDR_SDHC_HOST_CONTROL_1)
				|| (addr == (0xFFFFFF & ADDR_SDHC_POWER_CONTROL))
				|| (addr == (0xFFFFFF & ADDR_SDHC_BLOCK_GAP_CONTROL))
				|| (addr == (0xFFFFFF & ADDR_SDHC_WAKEUP_CONTROL))
				|| (addr == (0xFFFFFF & ADDR_SDHC_TIMEOUT_CONTROL))
				|| (addr == (0xFFFFFF & ADDR_SDHC_SOFTWARE_RESET))
				|| (addr == (0xFFFFFF & ADDR_SDHC_ADMA_ERR_STAT)))
	{
		uint8_t temp = 0;
		if (!rwbar) 
		{
			temp = (uint8_t)getSlice32(data_in_masked, 7, 0);
			dest = &cpu_view->argument2[0] + offset;
			source = &temp;
		}
		else if (rwbar)
		{
			dest = &temp;
			source = &cpu_view->argument2[0] + offset;
		}
		memcpy(dest, source, sizeof(uint8_t));
		ret_val = (uint32_t)temp;
	}
	else if ( (addr == (0xFFFFFF & ADDR_SDHC_BLOCK_SIZE))
			|| (addr == (0xFFFFFF & ADDR_SDHC_BLOCK_COUNT))
			|| (addr == (0xFFFFFF & ADDR_SDHC_TRANSFER_MODE))
			|| (addr == (0xFFFFFF & ADDR_SDHC_REGISTER_COMMAND))
			|| (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE0))
			|| (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE1))
			|| (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE2))
			|| (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE3))
			|| (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE4))
			|| (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE5))
			|| (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE6))
			|| (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE7))
			|| (addr == (0xFFFFFF & ADDR_SDHC_CLOCK_CONTROL))
			|| (addr == (0xFFFFFF & ADDR_SDHC_NORMAL_INTR_STATUS))
			|| (addr == (0xFFFFFF & ADDR_SDHC_ERROR_INTR_STATUS))
			|| (addr == (0xFFFFFF & ADDR_SDHC_NORMAL_INTR_STATUS_EN))
			|| (addr == (0xFFFFFF & ADDR_SDHC_ERROR_INTR_STATUS_EN))
			|| (addr == (0xFFFFFF & ADDR_SDHC_NORMAL_INTR_SIGNAL_EN))
			|| (addr == (0xFFFFFF & ADDR_SDHC_ERROR_INTR_SIGNAL_EN))
			|| (addr == (0xFFFFFF & ADDR_SDHC_AUTO_CMD_ERROR_STATUS))
			|| (addr == (0xFFFFFF & ADDR_SDHC_HOST_CONTROL_2))
			|| (addr == (0xFFFFFF & ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT))
			|| (addr == (0xFFFFFF & ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT))
			|| (addr == (0xFFFFFF & ADDR_SDHC_SHARED_BUS_CTRL))
			|| (addr == (0xFFFFFF & ADDR_SDHC_SLOT_INTR_STATUS))
			|| (addr == (0xFFFFFF & ADDR_SDHC_HOST_CONTROLLER_VERSION)))
	{
		uint16_t temp = 0;
		if (!rwbar)
		{
			temp = (uint16_t)getSlice32(data_in_masked, 15, 0);
			dest = &cpu_view->argument2[0] + offset;
			source = &temp;
		}
		else if(rwbar)
		{
			dest = &temp;
			source = &cpu_view->argument2[0] + offset;
		}
		memcpy(dest, source, sizeof(uint16_t));
		ret_val = (uint32_t)temp;
	}
	else
	{
		uint32_t temp = 0;
		if(!rwbar)
		{
			uint32_t temp = data_in_masked;
			dest = &cpu_view->argument2[0] + offset;
			source = &temp;
		}
		if(rwbar)
		{
			dest = &temp;
			source = &cpu_view->argument2[0] + offset;
		}
		memcpy(dest, source, sizeof(uint32_t));
		ret_val = temp;
	}
	return ret_val;
}


void writeToSdhcReg(uint32_t addr, uint8_t bytemask, sdhc_reg_cpu_view *cpu_view, 
			sdhc_reg_internal_view *internal_view, uint32_t data_in)
{
	read_or_write_sdhc_reg(addr, bytemask, cpu_view, internal_view, data_in, WRITE);
}

uint32_t readFromsdhcReg(uint32_t addr, sdhc_reg_cpu_view *cpu_view, 
			sdhc_reg_internal_view *internal_view)
{
	return read_or_write_sdhc_reg(addr, 0, cpu_view, internal_view, 0, READ);
}

/**** Thread declarations ****/

// thread that monitors data written and read from the SDHC registers
void sdhcControl();
DEFINE_THREAD(sdhcControl);

// Mutex for locking state variables (only control register in this case)
pthread_mutex_t Sdhc_lock = PTHREAD_MUTEX_INITIALIZER;

// void sdhcInitialState()
// {

// 	//interrupt output signal
// 	SDHC_INT_OUT = 0;
// 	write_uint8("SDHC_to_IRC_INT", SDHC_INT_OUT);

// 	/* TODO 
// 		- have the internal and external struct set to 0 
// 			internal_map = { 0 };
// 			cpu_reg_view = { 0 }; these doesn't work!
// 		- write appropriate vales in HwInit register fields
// 	*/
// 	memset(&internal_map, 0, sizeof(internal_map));
// 	memset(&cpu_reg_view, 0, sizeof(cpu_reg_view));

// 	/* 
// 	HwInit bits

// 		- most of capabilities reg
// 		- Max curent caps reg; 
// 		  - [23-16]
// 		  - [15-08]
// 		  - [07-00]
// 		- preset value regs; IGNORED
// 		  - [15-14]
// 		  - [10]
// 		  - [09-00]
// 		- shared bus cntrl reg; IGNORED
// 		  - [14-08]
// 		  - [05-04]
// 		  - [02-00]
// 		- host controller version register
// 		  - [15-08]
// 		  - [07-00] 
// 	 */

// 	setSlice64(internal_map.capabilities, 63, 0, 0x1000A8A); // hard code the reg
// 	memcpy(&cpu_reg_view.capabilities, &internal_map.capabilities, 
// 			sizeof(internal_map.capabilities));

// 	setSlice64(internal_map.max_current_cap, 23, 16, 0);
// 	setSlice64(internal_map.max_current_cap, 15, 8, 0);
// 	setSlice64(internal_map.max_current_cap, 7, 0, 0);
// 	memcpy(&cpu_reg_view.max_current_cap, &internal_map.max_current_cap, 
// 			sizeof(internal_map.max_current_cap));

// 	setSlice16(internal_map.host_controller_version, 15, 8, 1);
// 	setSlice16(internal_map.host_controller_version, 7, 0, 0x02);  // set controller version to SD Host specification 3.0
// 	memcpy(&cpu_reg_view.host_controller_version, &internal_map.host_controller_version, 
// 			sizeof(internal_map.host_controller_version));

// }

void registerSdhcPipes()
{
	//pipes between system bus and SDHC device
	int depth=1;

	register_pipe("peripheral_bridge_to_sdhc_request", depth, 64, 0);
	register_pipe("sdhc_to_peripheral_bridge_response", depth, 32, 0);
	
	set_pipe_is_written_into("peripheral_bridge_to_sdhc_request");
	set_pipe_is_read_from("peripheral_bridge_to_sdhc_request");
	set_pipe_is_written_into("sdhc_to_peripheral_bridge_response");
	set_pipe_is_read_from("sdhc_to_peripheral_bridge_response");
}

void startSdhcThreads()
{
	registerSdhcPipes();
	// sdhcInitialState();
	PTHREAD_DECL(sdhcControl);
	PTHREAD_CREATE(sdhcControl);
}

void sdhcControl()
{
	while(1)
	{
		uint8_t rwbar, byte_mask;
		uint32_t addr, data_in, data_out = 0;

		/*
		  This returns the following information
		  rwbar 	read-write-bar; 0 for write, 1 for read.
		  byte_mask 	4-bit byte-mask, most significant byte select at left end.
		  addr      	24 bit address (NOTE: when you compare internally, use only
		            	 the bottom 24-bits for comparison.)
		  data_in    	incoming word to be written (using byte_mask).
		 */
		getPeripheralAccessCommand("peripheral_bridge_to_sdhc_request",
			&rwbar, &byte_mask, &addr, &data_in);

		pthread_mutex_lock(&Sdhc_lock);

		switch (rwbar)
		{
		case WRITE:
			writeToSdhcReg(addr, byte_mask, &cpu_reg_view, 
					&internal_map, data_in);
			break;
		case READ:
			data_out = readFromsdhcReg(addr, &cpu_reg_view, 
					&internal_map);
			break;
		default:
			data_out = 0xBAD;
			break;
		}

		pthread_mutex_unlock(&Sdhc_lock);

		// data_out = 0xBAD;
		sendPeripheralResponse("sdhc_to_peripheral_bridge_response", data_out);
		data_out = 0;
	}
}