/*	for marching test */

/* Threads
SDHC_Control:
	Polls CPU commands and do corresponding register updates.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include "Device_utils.h"
#include "Ancillary.h"
#include "Ajit_Hardware_Configuration.h"
#include "Sdhc.h"
#include "RequestTypeValues.h"
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"

struct cpu_view cpu_reg_view;
struct internal_view internal_map;

#define READ 1
#define WRITE 0
// thread that monitors data written and read from the SDHC registers
void sdhcControl();
DEFINE_THREAD(sdhcControl);

// Mutex for locking state variables (only control register in this case)
pthread_mutex_t Sdhc_lock = PTHREAD_MUTEX_INITIALIZER;

void registerSdhcPipes()
{
	//pipes between system bus and SDHC device
	int depth=1;

	register_pipe("peripheral_bridge_to_sdhc_request", depth, 64, 0);
	register_pipe("sdhc_to_peripheral_bridge_response", depth, 32, 0);
	
	set_pipe_is_read_from("peripheral_bridge_to_sdhc_request");
	set_pipe_is_written_into("sdhc_to_peripheral_bridge_response");
}

void startSdhcThreads()
{
	registerSdhcPipes();
	PTHREAD_DECL(sdhcControl);
	PTHREAD_CREATE(sdhcControl);
}

void sdhcControl()
{
	while(1)
	{
		uint8_t rwbar, byte_mask;
		uint32_t addr, data_in;
		/*This returns the following information
		  rwbar 	read-write-bar; 0 for write, 1 for read.
		  byte_mask 	4-bit byte-mask, most significant byte select at left end.
		  addr      	24 bit address (NOTE: when you compare internally, use only
		            	 the bottom 24-bits for comparison.)
		  data_in    	incoming word to be written (using byte_mask).*/
		getPeripheralAccessCommand("peripheral_bridge_to_sdhc_request",
			&rwbar, &byte_mask, &addr, &data_in);
	//fprintf(stderr,"Inside sdhcControl thread\r\nExtracted data from pipe is\r\n rwbar=%d, byte-mask=0x%x, addr=0x%x, wdata=0x%x\n",
	 //rwbar, byte_mask, addr, data_in);

		uint32_t data_out = 0;

		pthread_mutex_lock(&Sdhc_lock);

		switch (addr)
		{
		case (0xFFFFFF & ADDR_SDHC_ARG_2):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				data_out = readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}		
			break;

		case (0xFFFFFF & ADDR_SDHC_BLOCK_SIZE):
			switch (rwbar)
			{
			case WRITE:
			{
					writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			}
			break;
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
			break;
			}
			break;

		case (0xffffff & ADDR_SDHC_BLOCK_COUNT):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			break;
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
			break;
			}
			break;

		case (0xFFFFFF & ADDR_SDHC_ARG_1):
			//fprintf(stderr,"reached sdhc arg1,rwbar is:%d\n",rwbar);
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}

			break;
		case (0xFFFFFF & ADDR_SDHC_TRANSFER_MODE):
			switch (rwbar)
			{
			case WRITE:
					writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_REGISTER_COMMAND):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_RESPONSE0):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_RESPONSE1):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_RESPONSE2):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_RESPONSE3):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_RESPONSE4):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_RESPONSE5):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;
			
		case (0xffffff & ADDR_SDHC_RESPONSE6):
			switch (rwbar)
			{
			case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ: readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;
			
		case (0xffffff & ADDR_SDHC_RESPONSE7):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;		
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
		}
		
			break;
		case (0xffffff & ADDR_SDHC_BUFFER_DATA_PORT):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_PRESENT_STATE):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_HOST_CONTROL_1):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;
		
				case (0xffffff & ADDR_SDHC_POWER_CONTROL):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;
		case (0xffffff & ADDR_SDHC_CLOCK_CONTROL):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_BLOCK_GAP_CONTROL):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

			case (0xffffff & ADDR_SDHC_WAKEUP_CONTROL):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_TIMEOUT_CONTROL):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_SOFTWARE_RESET):
			switch (rwbar)
			{
			case WRITE:
				writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
				break;			
			case READ:
				readSdhcReg(addr, &cpu_reg_view, &internal_map);
				break;
			}
			break;

		case (0xffffff & ADDR_SDHC_NORMAL_INTR_STATUS):
			switch (rwbar)
			{
			case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			break;
			case READ: readSdhcReg(addr, &cpu_reg_view, &internal_map);
			break;
			}
			break;
			
		case (0xffffff & ADDR_SDHC_ERROR_INTR_STATUS):
		switch (rwbar)
		{
			case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			break;
			case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
			break;
		}
		break;
		
		case (0xffffff & ADDR_SDHC_NORMAL_INTR_STATUS_EN):
		switch (rwbar)
		{
			case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			break;
			case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
			default: break;
		}break;

		case (0xffffff & ADDR_SDHC_ERROR_INTR_STATUS_EN):
		switch(rwbar)
		{
			case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
			break;
			case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
			break;
		}
		break;

		case (0xffffff & ADDR_SDHC_NORMAL_INTR_SIGNAL_EN):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;

		case (0xffffff & ADDR_SDHC_ERROR_INTR_SIGNAL_EN):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;

		case (0xffffff & ADDR_SDHC_AUTO_CMD_ERROR_STATUS):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;

		case (0xffffff & ADDR_SDHC_HOST_CONTROL_2):
				switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;
		
		case (0xffffff & ADDR_SDHC_CAPS):
		switch (rwbar)
		{
			fprintf(stderr,"in sdhcControl thread: 0x%x\r\n",data_in);
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;
		
		case (0xffffff & ADDR_SDHC_MAX_CURRENT_CAPS):
				switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;
		
		case (0xffffff & ADDR_SDHC_MAX_CURRENT_CAPS_RES):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;		
		
		case (0xffffff & ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;

		case (0xffffff & ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;
		
		case (0xffffff & ADDR_SDHC_ADMA_ERR_STAT):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;

		case (0xffffff & ADDR_SDHC_ADMA_SYSTEM_ADDR):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;
		
		case (0xffffff & ADDR_SDHC_HOST_PRESET_VALUES):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;
		
		case (0xffffff & ADDR_SDHC_SHARED_BUS_CTRL):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;

		case (0xffffff & ADDR_SDHC_SLOT_INTR_STATUS):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;

		case (0xffffff & ADDR_SDHC_HOST_CONTROLLER_VERSION):
		switch (rwbar)
		{
		case WRITE: writeSdhcReg(data_in, addr, byte_mask, &cpu_reg_view, &internal_map);
		break;
		case READ: readSdhcReg(addr,&cpu_reg_view,&internal_map);
		break;
		}
		break;			
		}
		pthread_mutex_unlock(&Sdhc_lock);
	}
}


