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
#include "Ajit_Hardware_Configuration.h"
#include "sd.h"
struct SdhcState__ *sdhc_regs;

    /*  CMD0    */
/*int GO_IDLE_STATE()
{

}*/

    /*  ACMD6   */
int SET_BUS_WIDTH(int enable)  //corresponds to ACMD6
                              // ie. changes bus width mode
{
    return enable;
}    


