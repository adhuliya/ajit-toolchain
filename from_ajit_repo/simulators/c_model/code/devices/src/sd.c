/*	sd.c
AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 8 Jan 2021 

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

void sdCardControl();
DEFINE_THREAD(sdCardControl); 

pthread_mutex_t SDcard_lock = PTHREAD_MUTEX_INITIALIZER;

struct cid_reg *CID;
struct cardStatus *card_stat;
uint16_t RCA=0x1111;
uint16_t DSR=0;
uint32_t OCR=0;

void initializeSdCard()
{
    //some initialization routines
}

void registerSdCardPipes()
{
int depth=1;
//pipe declarations
    register_pipe("sdhc_to_sdcard_cmd_request", depth, 64, 0);
	register_pipe("sdcard_to_sdhc_cmd_response", depth, 64, 0);
    register_pipe("sdcard_to_sdhc_data", depth, 64, 0);
	register_pipe("sdhc_to_sdcard_data", depth, 64, 0);

    set_pipe_is_read_from("sdhc_to_sdcard_cmd_request");
    set_pipe_is_written_into("sdcard_to_sdhc_cmd_response");
    set_pipe_is_read_from("sdcard_to_sdhc_data");
    set_pipe_is_written_into("sdhc_to_sdcard_data");

}

void startSdCardThreads()
{
    registerSdCardPipes();
    initializeSdCard();
   
    PTHREAD_DECL(sdCardControl);
	PTHREAD_CREATE(sdCardControl); 
}

 void extractCommandFromSDHC(const char* req_pipe, uint8_t *start_bit, uint8_t *tx_bit, 
 uint8_t *cmd_index, uint32_t *argument, uint8_t *crc7, uint8_t *end_bit)
{
	uint64_t cmd = read_uint64 (req_pipe);
	*start_bit 	 = (cmd >> 47) & 0x1;
	*tx_bit 	 = (cmd >> 46) & 0x1;
	*cmd_index   = (cmd >> 40) & 0x3f;
	*argument 	 = (cmd >> 32) & 0xffffffff;
    *crc7        = (cmd >> 7) & 0x7f;
	*end_bit 	 = (cmd >> 0) & 0x1;
#ifdef DEBUG
	fprintf(stderr,"Info:decodeCommandFromSDHC: from pipe %s, start_bit=%d, 
    tx_bit=0x%x, cmd_index=0x%x, argument=0x%x, crc7=0x%x,end_bit=0x%x\n", 
    req_pipe, *start_bit, *tx_bit, *cmd_index, *argument, *crc7, *end_bit);
#endif
}

void sendR2Response()//IN PROGRESS
{
    uint64_t cid_upper64=0, cid_lower64=0;
    cid_upper64 |= ((uint64_t)CID->MID >> 56) & 0xff;
    cid_upper64 |= ((uint64_t)CID->OID >> 40) & 0xffff;
    cid_upper64 |= ((uint64_t)CID->PNM[0] >> 32) & 0xff;
    cid_upper64 |= ((uint64_t)CID->PNM[1] >> 24) & 0xff;
    cid_upper64 |= ((uint64_t)CID->PNM[2] >> 16) & 0xff;
    cid_upper64 |= ((uint64_t)CID->PNM[3] >>  8) & 0xff;
    cid_upper64 |= ((uint64_t)CID->PNM[4] >>  0) & 0xff;
    write_uint64("sdcard_to_sdhc_cmd_response",cid_upper64);
    cid_lower64 |= ((uint64_t)CID->PRV >> 56) & 0xff;
    cid_lower64 |= ((uint64_t)CID->PSN >> 24) & 0xffffffff;
    cid_lower64 |= ((uint64_t)CID->MDT_y >> 12) & 0xff;
    cid_lower64 |= ((uint64_t)CID->MDT_m >> 8) & 0xf;
    cid_lower64 |= ((uint64_t)CID->crc >> 1)& 0x7f;
    write_uint64("sdcard_to_sdhc_cmd_response",cid_lower64);
}

void sendR3Response()
{   uint64_t frame_data=0;
    uint8_t res_value1=0x3F;uint8_t res_value2 = 0x7F;
    frame_data|=0UL<<47;//start bit
	frame_data|=0UL<<46;//tx bit
	frame_data|=(uint64_t)res_value1<<40;
    frame_data|=OCR<<8;
	frame_data|=res_value2<<1;
	frame_data|=1UL<<0;
    write_uint64("sdcard_to_sdhc_cmd_response",frame_data);
}

void sendR6Response()
{
	uint64_t frame_data=0;
    uint16_t card_stat_bits=0;//23,22,19,12:9
    card_stat_bits |= card_stat->com_crc_err << 15;
    card_stat_bits |= card_stat->illegal_cmd << 14;
    card_stat_bits |= card_stat->error << 13;
    card_stat_bits |= card_stat->current_state << 9;
    card_stat_bits |= card_stat->ready_for_data << 8;
    card_stat_bits |= card_stat->app_cmd << 5;
    card_stat_bits |= card_stat->ake_seq_err << 3;
    uint8_t crc7 = 0; // temp values, to be updated
	
    //we load the paramters for R6 herafter
    frame_data|=0UL<<47;//start bit
	frame_data|=0UL<<46;//tx bit
	frame_data|=3UL<<40;//cmd_index=3 for CMD3, see page 72 of Phy.Layer.Spec
	frame_data|=RCA<<24;
    frame_data|=card_stat_bits<<8;
	frame_data|=crc7<<1;
	frame_data|=1UL<<0;
    write_uint64("sdcard_to_sdhc_cmd_response",frame_data);
}


void actionForReceivedCommandIndex(uint8_t cmd_index)
{
    switch (cmd_index)
    {
    case 0:
         initializeSdCard();   
    case 2: //send CID i.e R2 response
        sendR2Response();
        break;
    case 3: //
        sendR6Response();
        break;
    case 4:
        break;
    case 41:
        sendR3Response();
    default:
        break;
    }
    
    
}

void sdCardControl()
{
    uint8_t start_bit, tx_bit,cmd_index, crc7, end_bit;
    uint32_t argument;

    extractCommandFromSDHC("sdhc_to_sdcard_cmd_request", &start_bit, 
    &tx_bit, &cmd_index, &argument, &crc7, &end_bit);
    //lock state variables//
    pthread_mutex_lock(&SDcard_lock);

    while(1)
    {
        //check if received data in indeed a frame
        if (start_bit == 0 && tx_bit == 1 && end_bit ==1)
        {
            actionForReceivedCommandIndex(cmd_index);
        }
    }    
}
