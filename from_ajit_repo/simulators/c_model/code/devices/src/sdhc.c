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

#define READ	1
#define	WRITE	0

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

/* helper functions */

void reg_clear(uint32_t );
void reg_set(uint32_t );
bool reg_check(uint32_t );

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

/*
Register attributes :
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
	HwInit	: hardware intialised; register bits are ntialised by firmware. Bits are read-only after
			initialisatio, and write to these bits are ignored.
	Rsvd	: reserved; these bits are initialised to zero and writes to them are ignored
	WO	: write-only register; It is not physically implimented register. Rather, it is a ddress
			at which registers can be written.
*/

void SDHC_Control()
{
	register_sdhc_pipes();
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
		uint32_t data_out=0;

		//***lock the state variables***
		pthread_mutex_lock(&Sdhc_lock);

		if((addr>=ADDR_SDHC_ARG_2)&&(addr<=ADDR_SDHC_HOST_CONTROLLER_VERSION))
		{

			switch (addr)
			{
				case (0xFFFFFF & ADDR_SDHC_ARG_2):
					// RW
					// *bits*
					// 31-0		RW
					// used with Auto CMD23 to set a 32-bit blk count value
					switch (rwbar)
					{
						case WRITE:
						{
							#ifdef SDHC_DEBUG
							fprintf(stderr, "\nInside case arg2 and rwbar = %d\n", rwbar);
							#endif
							updateRegister(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
						}
						break;

						case READ:
						{
							readRegister(data_out, addr, &cpu_reg_view, &internal_map);
						}
						break;

						default:
						break;
					}
				break;

				case (0xFFFFFF & ADDR_SDHC_BLOCK_SIZE):
					// Rsvd & RW
					// *bits*
					//   15		Rsvd	reserved
					//  14-12	RW	used for SDMA
					//  11-0	RW	blk size of data transfers for cmd17, cmd18, cmd24,
					// 			 cmd25 and cmd53
					switch (rwbar)
					{
						case 0:
						{
							#ifdef SDHC_DEBUG
							fprintf(stderr, "\nInside case blk_size and rwbar = %d\n", rwbar);
							#endif
							updateRegister(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
						}
						break;

						case 1:
						{
							readRegister(data_out, addr, &cpu_reg_view, &internal_map);
						}
						break;

						default:
						break;
					}
				break;

				case (0xffffff & ADDR_SDHC_BLOCK_COUNT):
					// RW
					// bits
					// 15-0		RW
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
					// *bits*
					//  31-00	RW 	bit39-8 of Command-Format
					switch (rwbar)
					{
						case WRITE:
						{
							#ifdef SDHC_DEBUG
							fprintf(stderr, "\nInside case arg1 and rwbar = %d\n", rwbar);
							#endif
							updateRegister(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
						}
						break;

						case READ:
						{
							readRegister(data_out, addr, &cpu_reg_view, &internal_map);
						}
						break;

						default:
						break;
					}
				break;

				case (0xFFFFFF & ADDR_SDHC_TRANSFER_MODE):
					// Rsvd & RW
					// bits
					// 15-06	Rsvd
					// 05		RW	multi/single blk select
					// 04		RW	data transfer direction set
					// 03-02	Rsvd	auto command enable
					// 01		RW	blk count enable
					// 00		RW	DMA enable
					// used to control the operation of data transfer
					// to prevent data loss host controller shall implement write protection during
					// data transfers; writes to this reg sahll be ignroes when 'comand inhibit (DAT)'
					// in 'present state reg' is 1
				break;

				case (0xffffff & ADDR_SDHC_REGISTER_COMMAND):
					// Rsvd & RW
					// *bits*
					// 15-14	Rsvd
					// 13-08	RW	command index
					// 07-06	RW	command type
					// 05		RW	data present select
					// 04		RW	command index check enable
					// 03		RW	command CRC check enable
					// 02		RW	Rsvd
					// 01-00	RW	response type
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
					// *bits*
					// 127-00	command response
					// host driver shall check the 'command inhibit (DAT)' and 'command inhibit (CMD)'
					// bits in 'present state' reg before writing to this reg
					// writing to the upper byte triggers SD command generation
					// host controller doesn't protect for writing when 'command inhibit(CMD)' is set
				break;

				case (0xffffff & ADDR_SDHC_BUFFER_DATA_PORT):
					// RW
					// *bits*
					// 31-00	buffer data
					// for accessing host controller buffer
				break;

				case (0xffffff & ADDR_SDHC_PRESENT_STATE):
					// Rsvd, RO & ROC
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
					// host driver can get the status of the host controller
					// from this 32-bit read-only reg
				break;

				case (0xffffff & ADDR_SDHC_HOST_CONTROL_1):
					// RW
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
					// Rsvd & RW
					// *bits*
					// 07-04	Rsvd
					// 03-01	RW	SD bus voltage select
					// 00		RW	SD bus power

				break;
				
				case (0xffffff & ADDR_SDHC_BLOCK_GAP_CONTROL):
					// Rsvd, RW & RWAC
					// *bits*
					// 07-04	Rsvd
					// 03		RW	interrupt at block gap
					// 02		RW	read wait control
					// 01		RWAC	continue request
					// 00		RW	stop at block gap request

				break;

				case (0xffffff & ADDR_SDHC_WAKEUP_CONTROL):
					// Rsvd & RW
					// *bits*
					// 07-03	Rsvd
					// 02		RW	wakeup event enable on SD card removal
					// 01		RW	wakeup event enable on card intsertion
					// 00		RW	wakeup event enable on card interrupt

				break;

				case (0xffffff & ADDR_SDHC_CLOCK_CONTROL):
					// RW & ROC
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
					// Rsvd & RW
					// *bits*
					// 07-04	Rsvd
					// 03-00	data timeout counter value

				break;

				case (0xffffff & ADDR_SDHC_SOFTWARE_RESET):
					// Rsvd & RWAC
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
					if (!rwbar)
					{
						updateRegister(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
						if (reg_check(SDHCI_RESET_DATA))
						{
							reg_clear(ADDR_SDHC_BUFFER_DATA_PORT);
							reg_clear(ADDR_SDHC_PRESENT_STATE);
							reg_clear(ADDR_SDHC_BLOCK_GAP_CONTROL);
							reg_clear(ADDR_SDHC_NORMAL_INTR_STATUS);
						}
						else if(reg_check(SDHCI_RESET_CMD))
						{
							reg_clear(ADDR_SDHC_PRESENT_STATE);
							reg_clear(ADDR_SDHC_NORMAL_INTR_STATUS);
						}
						else // reset everything
						{
							sdhc_initialize();
						}

					}
					else
					{
						/* code */
					}

					reg_clear(ADDR_SDHC_SOFTWARE_RESET); // all bits set to 0 after reset
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

					switch (rwbar)
					{
					case WRITE:
						// write protected
						break;
					case READ:
						readRegister(data_out, addr, &cpu_reg_view, &internal_map);
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

			}

			if (!rwbar)	// write
			{
				updateRegister(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);

			}
			else if(rwbar)	// read
			{
				readRegister(data_out, addr, &cpu_reg_view, &internal_map);
			}

		}
		pthread_mutex_unlock(&Sdhc_lock);
	}
}

/* to set all bits to 0 in a register */
void reg_clear(uint32_t addr)
{
	uint32_t data_in = 0;
	uint8_t byte_mask = 0b1111;
	updateRegister(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
	// return 0;
}
/* to set all bits to 1 in a register */
void reg_set(uint32_t addr)
{
	uint32_t data_in = 0xffff;
	uint8_t byte_mask = 0b1111;
	updateRegister(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
}

bool reg_check(uint32_t bit)
{
	return true;
}