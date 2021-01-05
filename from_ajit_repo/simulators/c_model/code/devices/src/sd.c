/*	sd.c
AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 4 Jan 2021 

Model that emulates an SD card and raw memory 
for compliance checks with SDHC version 3.0.

Device Registers:
	 SD card registers & flash memory
	 are defined in sd.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#ifdef SW
#include <stdio.h>
#include <unistd.h>
#endif
#include <pthread.h>
#include "Ancillary.h"
#include "Ajit_Hardware_Configuration.h"
#include "RequestTypeValues.h"
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "Device_utils.h"
#include "Sdhc.h"
#include "sd.h"

void SDCard_Control();
DEFINE_THREAD(SDCard_Control); 

pthread_mutex_t SDcard_lock = PTHREAD_MUTEX_INITIALIZER;

void initialize_sdcard()
{
    
}

void register_sdcard_pipes()
{
int depth=1;
//pipe declarations
}

void start_sdcard_threads()
{
    register_sdcard_pipes();
    initialize_sdcard();
   
    PTHREAD_DECL(SDCard_Control);
	PTHREAD_CREATE(SDCard_Control); 
}
