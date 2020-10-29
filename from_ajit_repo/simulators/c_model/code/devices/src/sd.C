/*	sd.c

AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 29 Oct 2020 

Model that emulates an SD card and raw memory 
for compliance checks with SDHC version 3.0.

Device Registers:
	 SD registers & flash memory
	 are defined in sd.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "sd.H"
struct SdhcState__ *sdhc_regs;

int SWITCH_FUNC(int enable)  //corresponds to ACMD6
                              // ie. changes bus width mode
{
    if(enable){
        sdhc_regs->host_ctrl |= (SDHCI_CTRL_4BITBUS); 
    }
    else {
        sdhc_regs->host_ctrl |= ~(SDHCI_CTRL_4BITBUS);
    }
}    