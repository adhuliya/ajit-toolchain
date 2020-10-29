/*	SDHC.c

AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 13 Oct 2020 

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

#include "Sdhc.H"
#include "sd.H"
//#include "pthreadUtils.h"

struct SdhcState__ sdhc_init;
struct SdcardState sd_init; 
#define CARD_INSERT_INTR_FLAG 1 //Flag for card insertion interrupt 
#define CARD_REMOVE_INTR_FLAG 0 //Flag for card removal interrupt

// **** Thread declarations ******//
void SDHC_Control();
DEFINE_THREAD(SDHC_Control);

//This thread reads data from SD card and passes
// it to the pipes(to cpu)/external devices(serial).
void SDHC_Read();
DEFINE_THREAD(SDHC_Read);

//This thread receives data from a pipe and stores
// it in SD Card
void SDHC_Write();
DEFINE_THREAD(SDHC_Write);

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
	card_insert_remove(1); //default mode selected as insertion
	sdhc_init.present_state =  1<<16; //card inserted flag set in PSR
	printf("PSR=%d\r\n",sdhc_init.present_state);
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

// 3.2.3 Clock Frequency Change sequence
int16_t sdhc_sd_clk_freq_change(uint64_t freq)
{
	sdhc_clk_stop(); // can be skipped if clock still off
	sdhc_sd_clk_supply(freq);

	return 0;
}

/*		Subsequence 3.3 SD Bus Power Control Page 107	*/
/*
(1) By reading the Capabilities register, get the support voltage of the Host Controller.
(2) Set SD Bus Voltage Select in the Power Control register with maximum voltage that the Host
Controller supports.
(3) Set SD Bus Power in the Power Control register to 1.
(4) Get the OCR value of all function internal of SD card.
(5) Judge whether SD Bus voltage needs to be changed or not. In case where SD Bus voltage needs
to be changed, go to step (6). In case where SD Bus voltage does not need to be changed, go to
'End'.
(6) Set SD Bus Power in the Power Control register to 0 for clearing this bit. The card requires
voltage rising from 0 volt to detect it correctly. The Host Driver shall clear SD Bus Power before
changing voltage by setting SD Bus Voltage Select.
(7) Set SD Bus Voltage Select in the Power Control register.
(8) Set SD Bus Power in the Power Control register to 1.
*/
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
	else((sdhc_init.capabilities&SDHCI_CAN_VDD_180))
	{ 
		sdhc_init.pwr_ctrl |=(SDHCI_BUS_POWER_180);	//1.8V supported
	}
	sdhc_init.pwr_ctrl |= (SDHCI_BUS_POWER_ON); //set SD BUS Power to 1
	ocr = 1<<31; //indicator that card power-up sequence is completed
	ocr = 1<<30; //indicator that card is SDHC/SDXC
}

/* 3.4 changing bus width pg no. 108 */

// The sequence for changing bit mode on SD Bus
// 	(1)	Set Card Interrupt Status Enable in the Normal Interrupt Status Enable register to 0 for masking
// 		incorrect interrupts that may occur while changing the bus width.
// 	(2)	In case of SD memory only card, go to step (4). In case of other card, go to step (3).
// 	(3)	Set "IENM" of the CCCR in a SDIO or SD combo card to 0 by CMD52. Please refer to Section
// 		3.7.1 for how to generate CMD52.
// 	(4)	Change the bus width mode for a SD card. SD Memory Card bus width is changed by ACMD6 and
// 		SDIO card bus width is changed by setting Bus Width of Bus Interface Control register in CCCR.
// 	(5)	In case of changing to 4-bit mode, set Data Transfer Width to 1 in the Host Control 1 register. In
// 		another case (1-bit mode), set this bit to 0.
// 	(6)	In case of SD memory only card, go to the 'End'. In case of other card, go to step (7).
// 	(7)	Set "IENM" of the CCCR in a SDIO or SD combo card to 1 by CMD52.
// 	(8)	Set Card Interrupt Status Enable in the Normal Interrupt Status Enable register to 1.
// Note that if the card is locked, bus width cannot be changed. Unlock the card is required before changing
// bus width.

int sdhc_change_bus_width()
{
	sdhc_init.normal_intr_status_enable &= ~(SDHCI_INT_CARD_INT);
	SWITCH_FUNC(1); //this function will issue a ACMD6 command to SD card
}