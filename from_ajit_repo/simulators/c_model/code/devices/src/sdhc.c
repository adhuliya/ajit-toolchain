/*	SDHC.c

AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 22 Dec 2020 

Model that emulates a version 3.00 SD Host Controller
and an SD card for verification purposes.

Device Registers:
	SDHC registers
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#ifdef SW
#include <stdio.h>
#include <unistd.h>
#endif
#include <pthread.h>
#include "Ancillary.h"
#include "Ajit_Hardware_Configuration.h"
#include "Sdhc.h"
#include "sd.h"
#include "RequestTypeValues.h"
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "Device_utils.h"

uint32_t sdhc_tx_buffer;
uint32_t sdhc_rx_buffer;
uint8_t SDHC_INT_OUT;

// **** Thread declarations ******//
void SDHC_CPU_Control();
DEFINE_THREAD(SDHC_CPU_Control);
void SDHC_Internal();
DEFINE_THREAD(SDHC_Internal);

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

	register_pipe("peripheral_bridge_to_SDHC_request",depth,64,0);
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

	PTHREAD_DECL(SDHC_Internal);
	PTHREAD_CREATE(SDHC_Internal);
}

void updateRegister(uint32_t data_in, uint32_t addr, uint8_t byte_mask)
{
	CPUViewOfSDHCRegArray cpu_reg_view;

	uint32_t data_in_masked = insertUsingByteMask(0, data_in, byte_mask);
	if (addr== (0xffffff & 0xff3300))
	{
	
	}

	else if(addr == (0xffffff & 0xff330C))
	{
	uint8_t temp1 = getSlice32(data_in_masked,7,0);
	cpu_reg_view.tx_mode[0] = temp1;
	uint8_t temp2 = getSlice32(data_in_masked,15,8);
	cpu_reg_view.tx_mode[1] = temp2;
	}
//to be used soon:	sdhc_tx_buffer = 1;//load the updated value in a pipe
}

void SDHC_CPU_Control()
{
	while (1)
	{
	uint8_t rwbar, byte_mask;
	uint32_t addr, data_in;
	
	getPeripheralAccessCommand("peripheral_bridge_to_serial_request",
	&rwbar, &byte_mask, &addr, &data_in);
	uint32_t data_out=0;
	
		if(!rwbar)
		{
		//***lock the state variables***
		pthread_mutex_lock(&Sdhc_lock);	
		if((addr<=0xff3300)&&(addr>=0xff33ff))
			{
				updateRegister(data_in,addr,byte_mask);
			}
		}
	}
}

void SDHC_Internal()
{
	
}
