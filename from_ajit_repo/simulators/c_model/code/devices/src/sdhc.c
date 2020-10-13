/*	SDHC.c

AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 12 Oct 2020 by Saurabh

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

#include "Sdhc.h"
//#include "pthreadUtils.h"


// Thread declarations
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

//mimics the action of SD card
void card_insertion();
{
 return x;
}

void SDHC_detection(); //Page 92 of the specification doc | Sequence 3.1
{
	struct SdhcState__ sdhcinit;
	int tempvar=3;
	sdhc_init.normal_intr_status_enable = tempvar<<7; 
	sdhc_init.normal_intr_signal_enable = tempvar<<7;
	if(x==0)
	{ 
	sdhc.init.present_state = 
	sdhc_init.normal_intr_status_enable
	sdhc_init.normal_intr_signal_enable
	}
}

/* SDHC SD Clock control. pg no. 105 */

// The sequence for supplying SD Clock to a SD card is described in Figure 3-3. The clock shall be supplied
// to the card before either of the following actions is taken.
// a) 	Issuing a SD command
// b) 	Detect an interrupt from a SD card in 4-bit mode.
// 
// (1) 	Calculate a divisor to determine SD Clock frequency by reading Base Clock Frequency For SD
// 	Clock in the Capabilities register. If Base Clock Frequency For SD Clock is 00 0000b, the Host
// 	System shall provide this information to the Host Driver by another method.
// (2) 	Set Internal Clock Enable and SDCLK Frequency Select in the Clock Control register in
// 	accordance with the calculated result of step (1).
// (3) 	Check Internal Clock Stable in the Clock Control register. Repeat this step until Clock Stable is 1.
// (4) 	Set SD Clock Enable in the Clock Control register to 1. Then, the Host Controller starts to supply
// the SD Clock

void sdhc_sd_clk_supply(uint64_t freq)
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

}

// The Host Driver shall not stop the SD Clock when a SD transaction is occurring on the SD Bus -- namely, 
// when either Command Inhibit (DAT) or Command Inhibit (CMD) in the Present State register is set to 1.
// (1) Set SD Clock Enable in the Clock Control register to 0. Then, the Host Controller stops supplying
// the SD Clock

void sdhc_clk_stop()
{
	struct SdhcState__ sdhcinit;

	while((sdhcinit.present_state & SDHCI_CMD_INHIBIT) || (sdhcinit.present_state & SDHCI_DATA_INHIBIT)) {}

	// set sd clk enable to 0
	sdhcinit.clk_ctrl &= ~(SDHCI_CLOCK_CARD_EN);
}

void sdhc_sd_clk_freq_change(uint64_t freq)
{
	sdhc_clk_stop(); // can be skipped if clock still off
	sdhc_sd_clk_supply(freq);
}
