/*	SDHC.c

AUTHORS: Saurabh Bansode, Vishnu Easwaran

last modified: 12 Oct 2020 by Saurabh

Model that emulates a version 3.00 SD Host Controller
and an SD card for verification purposes.

Device Registers:
	SDHC registers, SD registers & flash memory
	 are defined in Sdhc.h
*/

#include "Ajit_Hardware_Configuration.h"
#include "Sdhc.h"
#include <stdlib.h>
#include <stdint.h>
#ifdef SW
#include <stdio.h>
#include <unistd.h>
#endif
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "RequestTypeValues.h"
#include "Ancillary.h"

// Thread declarations
void SDHC_Control();
DEFINE_THREAD(SDHC_Control);

//This thread reads data from SD card and passes
// it to the pipes(to cpu)/external devices(serial).
void SDHC_Read();
DEFINE_THREAD(SDHC_Read);

//This thread recieves data from a pipe and stores
// it in SD Card
void SDHC_Write();
DEFINE_THREAD(SDHC_Write);



void SDHC_initialize(); //Page 92 of the specfication doc
{
	struct SdhcState__ sdhcinit;
	int tempvar=3;
	sdhc_init.normal_intr_status_enable = tempvar<<7; 
	sdhc_init.normal_intr_signal_enable = tempvar<<7;
	
}

