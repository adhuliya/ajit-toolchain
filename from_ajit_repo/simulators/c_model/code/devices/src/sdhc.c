/*	SDHC.c

AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 27 Nov 2020 

Model that emulates a version 3.00 SD Host Controller
and an SD card for verification purposes.

Device Registers:
	SDHC registers, SD registers & flash memory
	 are defined in Sdhc.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "Ajit_Hardware_Configuration.h"
#include "Ajit_Device_Addresses.h"
#include "Sdhc.h"
#include "sd.h"
#include "RequestTypeValues.h"
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"

struct SdhcState__ sdhc_init;
uint32_t sdhc_tx_buffer;
uint32_t sdhc_rx_buffer;
//struct SdcardState sd_init; 
#define CARD_INSERT_INTR_FLAG 1 //Flag for card insertion interrupt 
#define CARD_REMOVE_INTR_FLAG 0 //Flag for card removal interrupt

// **** Thread declarations ******//
void SDHC_Control();
DEFINE_THREAD(SDHC_Control);

void SDHC_Read_Write();
DEFINE_THREAD(SDHC_Read_Write);

//Mutex for locking state variables (only control register in this case)
pthread_mutex_t Sdhc_lock = PTHREAD_MUTEX_INITIALIZER;

void sdhc_initialize()
{
	sdhc_tx_buffer=0;
	sdhc_rx_buffer=0;
}


void register_sdhc_pipes()
{
	int depth = 1;
  	//signal going from SDHC to IRC
	register_port("SDHC_to_IRC_INT",8,1);
	set_pipe_is_written_into("SDHC_to_IRC_INT");

	//pipes between system bus and SDHC device
	depth=1;
	register_pipe("BUS_to_SDHC_request_type", depth, 8, 0);
  register_pipe("BUS_to_SDHC_addr", depth, 32, 0);  
	register_pipe("BUS_to_SDHC_data",depth,32,0);	

	set_pipe_is_read_from("BUS_to_SDHC_request_type");
	set_pipe_is_written_into("BUS_to_SDHC_addr");
	set_pipe_is_written_into("BUS_to_SDHC_data");

	register_pipe("SDHC_to_BUS_data", depth, 32, 0);
	set_pipe_is_written_into("SDHC_to_BUS_data");
	set_pipe_is_read_from("SDHC_to_BUS_data");
}

void start_sdhc_threads()
{
	sdhc_initialize();
	register_sdhc_pipes();

	PTHREAD_DECL(SDHC_Control);
	PTHREAD_DECL(SDHC_Read_Write);

	PTHREAD_CREATE(SDHC_Control);
	PTHREAD_CREATE(SDHC_Read_Write);
}


/***********		Command Frame		*********** 
bits::
47 > start bit    	 
46 > tx bit
45:40 > cmd index
39:8 > argument
7:1 > crc7
0 > end bit
***********		 Command Frame		***********/ 

void sendRequestToSDHC(uint8_t request_type, uint32_t addr,uint32_t data32)
{
	write_uint8 ("BUS_to_SDHC_request_type", request_type);
  write_uint32("BUS_to_SDHC_addr",addr);
	write_uint32 ("BUS_to_SDHC_data",data32); 
}

void readResponseFromSDHC(uint32_t* data)
{
	*data = read_uint32("SDHC_to_BUS_data");
}

void SDHC_Control()
{
	uint8_t  request_type;
	uint32_t addr;
	uint32_t data_in=0;
	uint32_t data_out=0;
	while(1)
	{
		//wait for a request from processor-side
		request_type	= read_uint8("BUS_to_SDHC_request_type");
    addr = read_uint32("BUS_to_SDHC_addr");
		data_in	= read_uint32("BUS_to_SDHC_data");
			
	if(request_type==REQUEST_TYPE_WRITE)
		{
			//***lock the state variables***
			pthread_mutex_lock(&Sdhc_lock);
			switch (addr)
				{
				case ADDR_SDHC_ARG_2:
						sdhc_tx_buffer=getSlice32(data_in,31,31);
					break;
				case ADDR_SDHC_BLOCK_COUNT:
						sdhc_tx_buffer=getSlice32(data_in,31,31);
					break;
				default: ADDR_SDHC_ARG_2;
					return 0;
					break;
				}
			pthread_mutex_unlock(&Sdhc_lock);	
		}	
			else if(request_type==REQUEST_TYPE_READ)
				{
			//***lock the state variables***
			pthread_mutex_lock(&Sdhc_lock);
					switch (addr)
						{
						case ADDR_SDHC_ARG_2:
								sdhc_rx_buffer=getSlice32(data_out,31,31);
							break;
						case ADDR_SDHC_BLOCK_COUNT:
								sdhc_rx_buffer=getSlice32(data_out,31,31);
							break;
						default: ADDR_SDHC_ARG_2;
							return 0;
							break;
						}
				pthread_mutex_unlock(&Sdhc_lock);		
				}
}

void SDHC_Read_Write()
{
	while(1)
	{
			write_uint32("BUS_to_SDHC_data", sdhc_tx_buffer);
	}		
}

/*	Subsequence 3.1: SD Card Detection, Page 103	*/
//Routine that mimics the actions of SD card and
//their effect on the registers
/*int card_insert_remove(int irflag)
{
	if(irflag==CARD_INSERT_INTR_FLAG) //card inserted
	{
		//change sdhc and sd regs
		sdhc_init.normal_intr_status = 1<<8;
	}
	else if(irflag==CARD_REMOVE_INTR_FLAG)
	{		
	//change sdhc and sd regs accordingly
		sdhc_init.normal_intr_status = 1<<7;
	}
 return irflag;
}

void SD_detection() 	
{
	sdhc_init.normal_intr_status_enable = 3<<7; 
	sdhc_init.normal_intr_signal_enable = 3<<7;
	card_insert_remove(CARD_INSERT_INTR_FLAG); //default mode selected as insertion
	sdhc_init.present_state =  1<<16; //card inserted flag set in PSR
	printf("PSR=%d\r\n",sdhc_init.present_state); //for debug purposes
}
				/*	End of subsequence 3.1: SD Card Detection, Page 104	*/


/*
int sdhc_sd_clk_supply(uint64_t freq)
{
	struct SdhcState__ sdhcinit;

	// cal the divisor; freq in MHz
	// Clock Frequency = (Base Clock) / divisor		
	uint32_t base_clock = (sdhcinit.capabilities & SDHCI_CLOCK_BASE_MASK);
	unsigned int divisor = (base_clock/freq);

	// set internal clock enable and SDCLK freq select
	sdhcinit.clk_ctrl |= SDHCI_CLOCK_INT_EN;
	unsigned int mask = (1<<divisor);
	sdhcinit.clk_ctrl |= mask<<15;

	// wait till stable and enable sd clock
	while(!(sdhcinit.clk_ctrl & SDHCI_CLOCK_INT_STABLE)) {}
	sdhcinit.clk_ctrl |= SDHCI_CLOCK_CARD_EN;
	
	return 0;

}

// 3.2.2 SD Clock Stop sequence
// The Host Driver shall not stop the SD Clock when a SD transaction is occurring on the SD Bus -- namely, 
// when either Command Inhibit (DAT) or Command Inhibit (CMD) in the Present State register is set to 1.
// (1) Set SD Clock Enable in the Clock Control register to 0. Then, the Host Controller stops supplying
// the SD Clock
/*
int sdhc_clk_stop()
{
	struct SdhcState__ sdhcinit;

	while((sdhcinit.present_state & SDHCI_CMD_INHIBIT) || (sdhcinit.present_state & SDHCI_DATA_INHIBIT)) {}

	// set sd clk enable to 0
	sdhcinit.clk_ctrl &= ~(SDHCI_CLOCK_CARD_EN);

	return 0;
}

/*		3.2.3 Clock Frequency Change sequence	
int16_t sdhc_sd_clk_freq_change(uint64_t freq)
{
	sdhc_clk_stop(); // can be skipped if clock still off
	sdhc_sd_clk_supply(freq);

	return 0;
}
*/
/*		Subsequence 3.3 SD Bus Power Control Page 107	*/
/*
int buspower()
{
sdhc_init.capabilities = 7<<26; 
// assuming that SDHC supports all Voltage levels
//cases are written regardless of this.
//we are assuming that step 6 won't be executed and 
//card will run in 3.3V range
// In case of using low voltage mode(1.8V), the bus power
// sequence will need to be changed.
	if((sdhc_init.capabilities&SDHCI_CAN_VDD_330)&&(1))
	{
		sdhc_init.pwr_ctrl |=(SDHCI_BUS_POWER_330); //3.3V supported	
	}
	else if((sdhc_init.capabilities&SDHCI_CAN_VDD_300))
	{
		sdhc_init.pwr_ctrl |=(SDHCI_BUS_POWER_300); //3.0V supported
	}
	else if((sdhc_init.capabilities&SDHCI_CAN_VDD_180))
	{ 
		sdhc_init.pwr_ctrl |=(SDHCI_BUS_POWER_180);	//1.8V supported
	}
	sdhc_init.pwr_ctrl |= (SDHCI_BUS_POWER_ON); //set SD BUS Power to 1
	ocr = 1<<31; //indicator that card power-up sequence is completed
	ocr = 1<<30; //indicator that card is SDHC/SDXC
}*/

/* 3.4 changing bus width pg no. 108 
int sdhc_change_bus_width()
{
	int return_resp;
	sdhc_init.normal_intr_status_enable &= ~(SDHCI_INT_CARD_INT);
	return_resp = SET_BUS_WIDTH(1); //this function will issue a ACMD6 command to SD card
	if(return_resp)
	{
		sdhc_init.host_ctrl |= (SDHCI_CTRL_4BITBUS);	
	}
		else
		{
			sdhc_init.host_ctrl |= ~(SDHCI_CTRL_4BITBUS);
		}	
}

int sdhc_timeout()
{
	// TO DO
	//After writing the driver
	//test application
}

*/
