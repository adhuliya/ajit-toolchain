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

