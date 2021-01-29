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

#define BASIC
//#define SWITCH

#define READ	1
#define	WRITE	0

uint32_t sdhc_tx_buffer;
uint32_t sdhc_rx_buffer;
uint8_t SDHC_INT_OUT;

sdhc_reg_cpu_view cpu_reg_view = {0};
sdhc_reg_internal_view internal_map = {0};


#ifdef BASIC
// ***** easwaran ***** //

uint32_t ve_read(uint32_t addr, sdhc_reg_cpu_view *cpu_view, sdhc_reg_internal_view *internal_view)
{
	uint32_t out = 0;
	
	switch (addr)
	{
	case (0xFFFFFF & ADDR_SDHC_ARG_2):
	{
		void *dest = &cpu_view->argument2[0];
		void *source = &internal_view->argument2;
		memcpy(dest, source, sizeof(internal_view->argument2));
		out = (uint32_t)internal_view->argument2;
		break;
	}
	case (0xFFFFFF & ADDR_SDHC_ARG_1):
	{
		void *dest = &cpu_view->argument1[0];
		void *source = &internal_view->argument1;
		memcpy(dest, source, sizeof(internal_view->argument1));
		out = (uint32_t)internal_view->argument1;
		break;
	}
	case (0xFFFFFF & ADDR_SDHC_BLOCK_SIZE):
	{
		void *dest = &cpu_view->blk_size[0];
		void *source = &internal_view->blk_size;
		memcpy(dest, source, sizeof(internal_view->blk_size));
		out = (uint32_t)internal_view->blk_size;
		break;
	}
	case (0xFFFFFF & ADDR_SDHC_HOST_CONTROL_1):
	{
		void *dest = &cpu_view->host_ctrl1;
		void *source = &internal_view->host_ctrl1;
		memcpy(dest, source, sizeof(internal_view->host_ctrl1));
		out = (uint32_t)internal_view->host_ctrl1;
		break;
	}
	default:
		out = 0;
		break;
	}
	return out;
	out = 0;
}

void ve_write(uint32_t data_in, uint32_t addr, uint8_t byte_mask,
 			struct sdhc_reg_cpu_view *cpu_view, struct sdhc_reg_internal_view *internal_view)
{
	data_in = insertUsingByteMask(0, data_in, byte_mask);
	switch (addr)
	{
	case (0xFFFFFF & ADDR_SDHC_ARG_2):
	{
		internal_view->argument2 = data_in;
		void *dest = &cpu_view->argument2[0];
		void *source = &internal_view->argument2;
		memcpy(dest, source, sizeof(internal_view->argument2));
		break;
	}
	case (0xFFFFFF & ADDR_SDHC_ARG_1):
	{
		internal_view->argument1 = data_in;
		void *dest = &cpu_view->argument1[0];
		void *source = &internal_view->argument1;
		memcpy(dest, source, sizeof(internal_view->argument1));
		break;
	}
	case (0xFFFFFF & ADDR_SDHC_BLOCK_SIZE):
	{
		internal_view->blk_size = data_in;
		void *dest = &cpu_view->blk_size[0];
		void *source = &internal_view->blk_size;
		memcpy(dest, source, sizeof(internal_view->blk_size));
		break;
	}
	case (0xFFFFFF & ADDR_SDHC_HOST_CONTROL_1):
	{
		internal_view->host_ctrl1 = data_in;
		void *dest = &cpu_view->host_ctrl1;
		void *source = &internal_view->host_ctrl1;
		memcpy(dest, source, sizeof(internal_view->host_ctrl1));
		break;
	}
	default:
		break;
	}

	data_in = 0;
}
#endif

// **** events **** //

bool event_card_inserted; // TRUE for inserted; FALSE for removed
//flags
uint8_t command_register_updated; //TRUE after a write is performed on this register
uint8_t cmd_response_receieved; //associated with command completed interrupt

/**** Thread declarations ****/

// thread that monitors data written and read from the SDHC registers
void sdhcControl();
DEFINE_THREAD(sdhcControl);
void sdhcInterruptAndOtherActions();
DEFINE_THREAD(sdhcInterruptAndOtherActions);

// Mutex for locking state variables (only control register in this case)
pthread_mutex_t Sdhc_lock = PTHREAD_MUTEX_INITIALIZER;

void sdhcInitialState()
{

	//interrupt output signal
	SDHC_INT_OUT = 0;
	write_uint8("SDHC_to_IRC_INT", SDHC_INT_OUT);

	/* TODO 
		- have the internal and external struct set to 0 
			internal_map = { 0 };
			cpu_reg_view = { 0 }; these doesn't work!
		- write appropriate vales in HwInit register fields
	*/
	memset(&internal_map, 0, sizeof(internal_map));
	memset(&cpu_reg_view, 0, sizeof(cpu_reg_view));

	/* 
	HwInit bits

		- most of capabilities reg
		- Max curent caps reg; 
		  - [23-16]
		  - [15-08]
		  - [07-00]
		- preset value regs; IGNORED
		  - [15-14]
		  - [10]
		  - [09-00]
		- shared bus cntrl reg; IGNORED
		  - [14-08]
		  - [05-04]
		  - [02-00]
		- host controller version register
		  - [15-08]
		  - [07-00] 
	 */

	setSlice64(internal_map.capabilities, 63, 0, 0x1000A8A); // hard code the reg
	memcpy(&cpu_reg_view.capabilities, &internal_map.capabilities, 
			sizeof(internal_map.capabilities));

	setSlice64(internal_map.max_current_cap, 23, 16, 0);
	setSlice64(internal_map.max_current_cap, 15, 8, 0);
	setSlice64(internal_map.max_current_cap, 7, 0, 0);
	memcpy(&cpu_reg_view.max_current_cap, &internal_map.max_current_cap, 
			sizeof(internal_map.max_current_cap));

	setSlice16(internal_map.host_controller_version, 15, 8, 1);
	setSlice16(internal_map.host_controller_version, 7, 0, 0x02);  // set controller version to SD Host specification 3.0
	memcpy(&cpu_reg_view.host_controller_version, &internal_map.host_controller_version, 
			sizeof(internal_map.host_controller_version));

}

void asyncListenerForSdCard()
{
	while (1)
	{
		uint8_t signalFromSdCard = read_uint8("SDCARD_TO_SDHC");
		if(signalFromSdCard) cardInsert();
	}
	
}

void cardInsert()
{
	//setting bits 16,17,18 of PSR indicated that card is inserted 
	//and detected 
	cpu_reg_view.present_state[2]=0x7;
	internal_map.present_state=0x0700;
}

void registerSdhcPipes()
{
	//signal going from SDHC to IRC
	register_port("SDHC_to_IRC_INT",8,1);
	set_pipe_is_written_into("SDHC_to_IRC_INT");

	//pipes between system bus and SDHC device
	int depth=1;

	register_pipe("peripheral_bridge_to_sdhc_request", depth, 64, 0);
	register_pipe("sdhc_to_peripheral_bridge_response", depth, 32, 0);
	register_pipe("sdhc_to_sdcard_request", depth, 64, 0);
	register_pipe("sdcard_to_sdhc_response", depth, 64, 0);
	
	set_pipe_is_read_from("peripheral_bridge_to_sdhc_request");
	set_pipe_is_written_into("sdhc_to_peripheral_bridge_response");
	set_pipe_is_written_into("sdhc_to_sdcard_request");
	set_pipe_is_read_from("sdcard_to_sdhc_response");
}

void startSdhcThreads()
{
	registerSdhcPipes();
	sdhcInitialState();
	cardInsert();
	PTHREAD_DECL(sdhcControl);
	PTHREAD_CREATE(sdhcControl);
	PTHREAD_DECL(sdhcInterruptAndOtherActions);
	PTHREAD_CREATE(sdhcInterruptAndOtherActions);
}

void sdhcControl()
{
	while(1)
	{
		uint8_t rwbar, byte_mask;
		uint32_t addr, data_in;

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

		uint32_t data_out = 0;
		//added for verifying the read functions
		// internal_map.argument2 = 0x123;
		// internal_map.argument1 = 0x234;
		internal_map.buffer_data_port = 0x345;
		internal_map.max_current_cap = 0x456;

#ifdef SWITCH
		pthread_mutex_lock(&Sdhc_lock);

		switch (addr)
		{
		case (0xFFFFFF & ADDR_SDHC_ARG_2):
			// *bits*
			// 31-0		RW	Used with Auto CMD23 to set a 32-bit blk count value
			// 			 32b if used with ADMA, otherwise limited by 'blk count' reg
			// 			 
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				data_out = readSdhcReg(addr, &cpu_reg_view, &internal_map);
				// data_out = ve_read(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}		
			break;

		case (0xFFFFFF & ADDR_SDHC_BLOCK_SIZE):
			// *bits*
			//   15		Rsvd	reserved
			//  14-12	RW	used for SDMA
			//  11-0	RW	blk size of data transfers for cmd17, cmd18, cmd24,
			// 			 cmd25 and cmd53; can only be accessed when there is no transaction;
			// 			  read operations during transfer may return invalid
			//			  write operations shall be ignored.
			switch (rwbar)
			{
			case WRITE:
			{
				// checking for ongoing transactions
				if ( !( getBit32(internal_map.present_state, 9) || (getBit32(internal_map.present_state, 8))) )
				{
					writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				}
			}
				break;
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				setSlice32(internal_map.blk_size, 14, 12, 0);
				memcpy(&cpu_reg_view.blk_size, &internal_map.blk_size, 4);
				break;
			}
			
			break;
		case (0xffffff & ADDR_SDHC_BLOCK_COUNT):
			// *bits*
			// 15-0		RW
			// enabled when 'block count enable' in 'transfer mode' is set to 1
			// valid for only multiple block transfers
			// host driver set this value and host controller decrements the value
			// according to the tranfered blocks; stops when reaches zero
			// can be accessed only when no transactions is executing; during data transfer
			// ignore write, and read will be incorrect
			if( getBit16(internal_map.tx_mode, 1) &&  
				(!( getBit32(internal_map.present_state, 9) || 
					(getBit32(internal_map.present_state, 8)))) )
			{
				switch (rwbar)
				{
				case WRITE:
					writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
					break;
				case READ:
					readSdhcReg(addr, &cpu_reg_view, &internal_map);
					break;
				default:
					break;
				}
			}
			else
			
			break;
		case (0xFFFFFF & ADDR_SDHC_ARG_1):
			// *bits*
			// 31-00	RW 	SD command arg is specified as bit 39-8 of Command-Format
			// 			 in the physical layer spec
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;
		case (0xFFFFFF & ADDR_SDHC_TRANSFER_MODE):
			// *bits*
			// 15-06	Rsvd
			// 05		RW	multi/single blk select
			// 			 bit is set when issuing multiple-block tx commands
			// 			 using DAT line. For any other command this bit will be 0.
			// 			 If 0, it is not necessary to set 'blk count' register.
			// 04		RW	data transfer direction set
			// 			 bit defines direction of data line transfers.
			// 			 set to 1 by host driver to tx data from SD to SDHC, 0 for
			// 			 all other commands.
			// 			 	1 read(card to host)
			//  			 	0 write(host to card)
			// 03-02	Rsvd	auto command enable
			// 01		RW	blk count enable
			// 			 only relevant for multiple blk tx.
			// 			 'blk count' disable if this bit is 0
			// 				1 enable
			// 				0 disable
			// 00		RW	DMA enable
			// 			 bit enables DMA if indicated in 'caps' reg.
			// 			 if no DMA, bit is meaningless and aways zero.
			// 		  	 if this bit is 1, DMA operation starts when host driver write
			// 			 to upper byte of 'command reg'
			// 				1 DMA data tx
			// 				0 no data tx or non-DMA data tx
			// Used to control the operation of data transfer; host driver shall set this reg before issuing 
			// cmd which transfers data, or before issuing a Resume command
			// To prevent data loss host controller shall implement write protection during
			// data transfers; writes to this reg sahll be ignroed when 'comand inhibit (DAT)'[1]
			// in 'present state reg'[31:0] is 1
			switch (rwbar)
			{
			case WRITE:
				if (!(getBit32(internal_map.present_state, 1)))
					writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;
		case (0xffffff & ADDR_SDHC_REGISTER_COMMAND):
			// *bits*
			// 15-14	Rsvd
			// 13-08	RW	command index
			// 			 bits shall be set to comd number (CMD0-63, ACMD0-63) that
			// 			 is specified in bits 45-40 of the command format in 
			// 			 the physical layer spec
			// 07-06	RW	command type
			// 			 there are 3 special commands
			// 				11b abort
			// 				10b resume
			// 				01b suspend
			// 				00b normal
			// 05		RW	data present select
			// 			 set to 1 to indicate that data is present and shall be transfered
			// 			 using DAT line. It is set to 0 for the following
			// 			   1 - cmds using only CMD line(ex. CMD52)
			// 			   2 - cmds with no data tx but using busy signal on DAT[0]
			//			        line(R1b or R5b ex. CMD38)
			// 				1 : data present
			// 				0 : data not present
			// 04		RW	command index check enable
			// 03		RW	command CRC check enable
			// 02		RW	Rsvd
			// 01-00	RW	response type
			// Host driver shall check the 'command inhibit (DAT)' and 'command inhibit (CMD)'
			// bits in 'present state' reg before writing to this reg.
			// Writing to the upper byte triggers SD command generation.
			// Host controller doesn't protect for writing when 'command inhibit(CMD)' is set
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				command_register_updated=1;
				break;
			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_RESPONSE0):
		case (0xffffff & ADDR_SDHC_RESPONSE1):
		case (0xffffff & ADDR_SDHC_RESPONSE2):
		case (0xffffff & ADDR_SDHC_RESPONSE3):
		case (0xffffff & ADDR_SDHC_RESPONSE4):
		case (0xffffff & ADDR_SDHC_RESPONSE5):
		case (0xffffff & ADDR_SDHC_RESPONSE6):
		case (0xffffff & ADDR_SDHC_RESPONSE7):
			// *bits*
			// 127-00	ROC command response
			// Host driver shall check the 'command inhibit (DAT)' and 'command inhibit (CMD)'
			// bits in 'present state' reg before writing to this reg.
			// Writing to the upper byte triggers SD command generation.
			// Host controller doesn't protect for writing when 'command inhibit(CMD)' is set.
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
		
			break;
		case (0xffffff & ADDR_SDHC_BUFFER_DATA_PORT):
			// *bits*
			// 31-00	RW	buffer data 
			// 			 SDHC buffer can be accessed 
			// 			 through this 32b 'Data Port' reg.
			// for accessing host controller buffer
			// TODO impliment Buffer control: Page 5
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				// TODO copy to sdhc_tx_buffer
				break;
			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				// TODO copy from sdhc_rx_buffer
				break;
			default:
				break;
			}
			break;
		case (0xffffff & ADDR_SDHC_PRESENT_STATE):
			// *bits*
			// 31-25	Rsvd
			// 24		RO	CMD line signal level
			// 23-20	RO	DAT[3:0] line signal level
			// 19		RO	write protect switch pin level
			// 18		RO 	card detedt pin level
			// 17		RO	card state stable
			// 16		RO	card inserted
			// 15-12	Rsvd
			// 11		ROC	buffer read enable
			// 10		ROC	buffer write enable
			// 09		ROC	read transfer active
			// 08		ROC	write transfer active
			// 07-04	Rsvd
			// 03		ROC	re-tuning request
			// 02		ROC	DAT line active
			// 01		ROC	command inhibit(DAT)
			// 00		ROC	command inhibit(CMD)
			// Host driver can get the status of the host controller
			// from this 32-bit read-only reg
			// Members are updated as per the states of SDHC.
			

			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;
		case (0xffffff & ADDR_SDHC_HOST_CONTROL_1):
			// *bits*
			// 07		RW	card detect signal selection
			// 06		RW	card detect test dsignal
			// 05		RW	extended date transfer width
			// 04-03	RW	DMA select
			// 02		RW	high speed enable
			// 01		RW	data transfer width
			// 00		RW	LED control
			break;
		case (0xffffff & ADDR_SDHC_POWER_CONTROL):
			// *bits*
			// 07-04	Rsvd
			// 03-01	RW	SD bus voltage select
			// 			 The HD selects the voltage level for the sd card by setting these.
			// 			 Before setting this reg, HD shall check 'Voltage Support'
			// 			 bits in 'Caps reg'. If an unsupported voltage is selected
			// 			 the Host System shall not supply SD Bus voltage.
			// 			 	111b	 3.3v
			// 				110b	 3.0v
			// 				101b	 1.8v
			// 				100-000b Rsvd	
			// 00		RW	SD bus power
			// 			 Before setting this bit, HD shall set 'SD Bus Voltage Select'
			// 			 If the HC detect no-card state, this bit shall be cleared.
			// 			 If this bit is cleared, HC immediately stor driving CMD and DAT[3:0]
			// 			 and drive SDCLK to low level
			// 				1	Power on
			// 				0	Power off
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;
		
		case (0xffffff & ADDR_SDHC_BLOCK_GAP_CONTROL):
			// *bits*
			// 07-04	Rsvd
			// 03		RW	interrupt at block gap
			// 02		RW	read wait control
			// 01		RWAC	continue request
			// 00		RW	stop at block gap request
			break;
		case (0xffffff & ADDR_SDHC_WAKEUP_CONTROL):
			// *bits*
			// 07-03	Rsvd
			// 02		RW	wakeup event enable on SD card removal
			// 01		RW	wakeup event enable on card intsertion
			// 00		RW	wakeup event enable on card interrupt
			break;
		case (0xffffff & ADDR_SDHC_CLOCK_CONTROL):
			// *bits*
			// 15-08	RW	SDCLK freq select
			// 07-06	ROC/RW	upper bits of SDCLK freq select
			// 05		RW/ROC	clock generator select
			// 04-03	Rsvd
			// 02		RW	SD clock enable
			// 01		ROC	internal clock stable
			// 00		RW	internal clock enable
			break;
		case (0xffffff & ADDR_SDHC_TIMEOUT_CONTROL):
			// *bits*
			// 07-04	Rsvd
			// 03-00	data timeout counter value
			break;
		case (0xffffff & ADDR_SDHC_SOFTWARE_RESET):
			// *bits*
			// 07-03	Rsvd
			// 02		RWAC	software reset for DAT line
			// 01		RWAC 	software reset for CMD line
			// 00		RWAC	software reset for all
			// write 1 to all the unrsvd bits for resetting
			// after completing reset clear all bits
			//
			// affects the following regs
			// 	buffer data port reg
			// 	Present state reg
			// 	blk gap ctrl reg
			// 	normal intr status reg
			switch (rwbar)
			{
			case WRITE:
				
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				
				if (getBit8(internal_map.sw_reset, 2))
				{
					setSlice32(internal_map.buffer_data_port, 31, 0, 0);
					setSlice32(internal_map.present_state, 31, 0, 0);
					setSlice8(internal_map.blk_gap_ctrl, 7, 0, 0);
					setSlice16(internal_map.normal_intr_status, 7, 0, 0);
				}
				else if(getBit8(internal_map.sw_reset, 1))
				{
					setSlice32(internal_map.present_state, 31, 0, 0);
					setSlice16(internal_map.normal_intr_status, 15, 0, 0);
				}
				else if(getBit8(internal_map.sw_reset, 0))
				{
					sdhcInitialState();
				}
				break;
			case READ:
				break;
			}
			setSlice8(internal_map.sw_reset, 7, 0, 0); // all bits set to 0 after reset
			break;

		case (0xffff & ADDR_SDHC_NORMAL_INTR_STATUS):
			// Rsvd, ROC & RW1C
			switch (rwbar)
			{
			case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			break;
			case READ: readSdhcReg(addr, &cpu_reg_view, &internal_map);
			break;
			default:break;
			}
			
		case (0xffff & ADDR_SDHC_ERROR_INTR_STATUS):
		switch (rwbar)
		{
			case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			break;
			case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		default:break;
		}
			// Rsvd & RW1C
		case (0xffff & ADDR_SDHC_NORMAL_INTR_STATUS_EN):
		switch (rwbar)
		{
			case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			break;
			case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
			default: break;
		}
		case (0xffff & ADDR_SDHC_ERROR_INTR_STATUS_EN):
			// Rsvd & RW
		case (0xffff & ADDR_SDHC_NORMAL_INTR_SIGNAL_EN):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		default: break;
		}
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
			switch (rwbar)
			{
			case WRITE:
				// write protected
				break;
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;
		case (0xffffff & ADDR_SDHC_MAX_CURRENT_CAPS):
		case (0xffffff & ADDR_SDHC_MAX_CURRENT_CAPS_RES):
			// Rsvd & HwIn
			// whatever the case, values/states wont change
			// writes are ignored
			break;
		case (0xffffff & ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT):
			// Rsvd & WO
		case (0xffffff & ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT):
			// Rsvd & WO
			break;
		case (0xffffff & ADDR_SDHC_ADMA_ERR_STAT):
			// Rsvd & ROC
			// DMA not present
		case (0xffffff & ADDR_SDHC_ADMA_SYSTEM_ADDR):
			// RW
			// DMA not present
			break;/* constant-expression */
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
		}

		pthread_mutex_unlock(&Sdhc_lock);
#endif


#ifdef BASIC
		pthread_mutex_lock(&Sdhc_lock);
		
		switch (addr)
		{
		// arg2, arg1, blk_size and host_ctrl1 are the candidates for testing
		//  32b, 16b and 8b registers. ****DO NOT CHANGE THE ORDER****
		case(0xFFFFFF & ADDR_SDHC_ARG_2):
			switch (rwbar)
			{
			case WRITE:
				//ve_write(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				data_out = readSdhcReg(addr, &cpu_reg_view, &internal_map);
				// data_out = ve_read(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;
		
		case(0xFFFFFF & ADDR_SDHC_ARG_1):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				//ve_write(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				data_out = readSdhcReg(addr, &cpu_reg_view, &internal_map);
				// data_out = ve_read(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;

		case(0xFFFFFF & ADDR_SDHC_BLOCK_SIZE):
		 	switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			//	ve_write(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				data_out = readSdhcReg(addr, &cpu_reg_view, &internal_map);
				// data_out = ve_read(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;

		case(0xFFFFFF & ADDR_SDHC_HOST_CONTROL_1):
		 	switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				//ve_write(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				data_out = readSdhcReg(addr, &cpu_reg_view, &internal_map);
				// data_out = ve_read(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;

		case(0xFFFFFF & ADDR_SDHC_BUFFER_DATA_PORT):
		 	switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				data_out = readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;
		
		case(0xFFFFFF & ADDR_SDHC_MAX_CURRENT_CAPS):
		 	switch (rwbar)
			{
			case WRITE:
				data_out = 0;
				break;
			case READ:
				data_out = readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;

		case(0xFFFFFF & ADDR_SDHC_PRESENT_STATE):
		 	switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				data_out = readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			default:
				break;
			}
			break;

		default:
			data_out = 0x1deadbee;
			break;
		}
		
		pthread_mutex_unlock(&Sdhc_lock);
#endif

		sendPeripheralResponse("sdhc_to_peripheral_bridge_response", data_out);
		data_out = 0;
	}
}

void sdhcInterruptAndOtherActions()
{
while (1)
	{
		pthread_mutex_lock(&Sdhc_lock);
		
		if(command_register_updated)
		{
			internal_map.present_state |= 1<<0; //set the CMD inhibit(CMD) bit to 1
			uint8_t resp_type = checkResponseType(&internal_map, &cpu_reg_view);
			//the value resp_type holds the lower byte of the command(0xE) register
			setSlice16(internal_map.command_reg,7,0,resp_type);
			memcpy(&cpu_reg_view.present_state, &internal_map.present_state,4);
			memcpy(&cpu_reg_view.command_reg, &internal_map.command_reg,2);
		}
		checkNormalInterrupts(&internal_map, &cpu_reg_view);
		checkErrorInterrupts(&internal_map, &cpu_reg_view);
		pthread_mutex_unlock(&Sdhc_lock);
	}
}

