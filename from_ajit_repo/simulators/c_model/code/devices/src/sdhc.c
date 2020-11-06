/*	SDHC.c

AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 4 Nov 2020 

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
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"

struct SdhcState__ sdhc_init;

//struct SdcardState sd_init; 
#define CARD_INSERT_INTR_FLAG 1 //Flag for card insertion interrupt 
#define CARD_REMOVE_INTR_FLAG 0 //Flag for card removal interrupt

// **** Thread declarations ******//
void SDHC_Control();
DEFINE_THREAD(SDHC_Control);

void SDHC_Read_Write();
DEFINE_THREAD(SDHC_Read_Write);

void start_sdhc_threads()
{
	register_sdhc_pipes();

	PTHREAD_DECL(SDHC_Control);
	PTHREAD_DECL(SDHC_Read_Write);

	PTHREAD_CREATE(SDHC_Control);
	PTHREAD_CREATE(SDHC_Read_Write);
}

void register_sdhc_pipes()
{
	int depth = 1;
  	//signal going from SDHC to IRC
	register_port("SDHC_to_IRC_INT",8,1);
	set_pipe_is_written_into("SDHC_to_IRC_INT");

	//TO DO: pipes between memoryAccess thread and SDHC device
	depth=1;
	//pipes between memoryAccess thread and the Serial device
	register_pipe("BUS_to_SDHC_request_type", depth, 8, 0);
  	register_pipe("BUS_to_SDHC_addr", depth, 32, 0);  
	register_pipe("BUS_to_SDHC_cmd_index", depth, 8, 0);
	register_pipe("BUS_to_SDHC_arg", depth, 32, 0);
  	register_pipe("BUS_to_SDHC_crc7", depth, 8, 0); 

//the memory access thread reads from these pipes
	set_pipe_is_read_from("BUS_to_SDHC_request_type");
	set_pipe_is_read_from("BUS_to_SDHC_addr");
	set_pipe_is_read_from("BUS_to_SDHC_cmd_index");
  	set_pipe_is_read_from("BUS_to_SDHC_arg");
	set_pipe_is_read_from("BUS_to_SDHC_crc7");
	
	//the memory access thread writes to these pipes
	set_pipe_is_written_into("BUS_to_SDHC_request_type");
	set_pipe_is_written_into("BUS_to_SDHC_request_type");
	set_pipe_is_written_into("BUS_to_SDHC_cmd_index");
  	set_pipe_is_written_into("BUS_to_SDHC_arg");
	set_pipe_is_written_into("BUS_to_SDHC_crc7"); 	
}

/*Three functions below are required for sending
 a command to SDHC from CPU via the bridge. 
 The start, tx and end bits are constants.

		***********		Command Frame		*********** 
bits: 47     	 46   	 45:40 		39:8	7:1		0
	   |		  |		  |			  |	 	|		|
	  start_bit  tx bit  cmd_index   arg	crc7	end_bit 

	  bits 47:40 will be sent using the sendCommandIndexToSDHC
	  bits 39:8 using the sendCommandArgToSDHC and
	  bits 7:0 using the sendCrc7ToSDHC */

void sendCommandIndexToSDHC(uint8_t request_type, uint32_t addr,uint8_t data8)
{
	#define start_bit 0
	#define tx_bit 	  1 
	data8 |= start_bit<<7;
	data8 |= tx_bit<<6;
	write_uint8 ("BUS_to_SDHC_request_type", request_type);
  	write_uint32("BUS_to_SDHC_addr",addr);
	write_uint8 ("BUS_to_SDHC_cmd_index",data8); 
}

void sendCommandArgToSDHC(uint8_t request_type, uint32_t addr,uint32_t data32)
{ 
	write_uint8 ("BUS_to_SDHC_request_type", request_type);
  	write_uint32("BUS_to_SDHC_addr",addr);
  	write_uint32("BUS_to_SDHC_arg",data32);
}

void sendCrc7ToSDHC(uint8_t request_type, uint32_t addr,uint8_t data8)
{
	#define end_bit   1
	data8 |= end_bit<<0;
	write_uint8 ("BUS_to_SDHC_request_type", request_type);
  	write_uint32("BUS_to_SDHC_addr",addr);
 	write_uint8("BUS_to_SDHC_crc7",data8);
}

/*	Subsequence 3.1: SD Card Detection, Page 103	*/
//Routine that mimics the actions of SD card and
//their effect on the registers
int card_insert_remove(int irflag)
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

/* 3.2 SDHC SD Clock control. pg no. 105 */

// 3.2.1
// The sequence for supplying SD Clock to a SD card is described in Figure 3-3. The clock shall be supplied
// to the card before either of the following actions is taken.
// a) 	Issuing a SD command
// b) 	Detect an interrupt from a SD card in 4-bit mode.
// 
// 	(1) 	Calculate a divisor to determine SD Clock frequency by reading Base Clock Frequency For SD
// 		Clock in the Capabilities register. If Base Clock Frequency For SD Clock is 00 0000b, the Host
// 		System shall provide this information to the Host Driver by another method.
// 	(2) 	Set Internal Clock Enable and SDCLK Frequency Select in the Clock Control register in
// 		accordance with the calculated result of step (1).
// 	(3) 	Check Internal Clock Stable in the Clock Control register. Repeat this step until Clock Stable is 1.
// 	(4) 	Set SD Clock Enable in the Clock Control register to 1. Then, the Host Controller starts to supply
// 		the SD Clock

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

int sdhc_clk_stop()
{
	struct SdhcState__ sdhcinit;

	while((sdhcinit.present_state & SDHCI_CMD_INHIBIT) || (sdhcinit.present_state & SDHCI_DATA_INHIBIT)) {}

	// set sd clk enable to 0
	sdhcinit.clk_ctrl &= ~(SDHCI_CLOCK_CARD_EN);

	return 0;
}

/*		3.2.3 Clock Frequency Change sequence	*/
int16_t sdhc_sd_clk_freq_change(uint64_t freq)
{
	sdhc_clk_stop(); // can be skipped if clock still off
	sdhc_sd_clk_supply(freq);

	return 0;
}

/*		Subsequence 3.3 SD Bus Power Control Page 107	*/

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
}

/* 3.4 changing bus width pg no. 108 */
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

