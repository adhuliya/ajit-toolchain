/*  
This file holds the declarations of the SD card registers 
and the function prototypes for emulation the SD card 

Information regarding the variables declared in this file has
been taken from the Physical layer specifications V 3.01 document

*/

#ifndef _SD_H
#define _SD_H

#include<stdint.h>
#include<stdbool.h>
#include"Sdhc.h"
/* Register decalarations	*/

typedef struct cid_reg
{
uint8_t MID;      //127:120
uint16_t OID;     //119:104
char PNM[5];      //103:64
uint8_t PRV;      //63:56
uint32_t PSN;     //55:24
//23:20 bits are reserved
uint8_t MDT_y;    //19:12
uint8_t MDT_m;    //11:8 use only lower 4 bits
uint8_t crc;      //7:1 use only lower 7bits
//0th bit is unused
}cid_reg;

//CSD Version 2.0 (high capacity and extended cards)
typedef struct csd{ 
	uint8_t  csd_structure;
	uint8_t  taac;
	uint8_t  nsac;
	uint8_t  tran_speed;
	uint16_t ccc;
	uint8_t  read_bl_len;
	uint8_t  read_bl_partial;
	uint8_t  write_blk_misalign;
	uint8_t  read_blk_misalign;
	uint8_t  dsr_imp;
	uint32_t c_size;
	uint8_t  erase_blk_en;
	uint8_t  sector_size;
	uint8_t  wp_grp_size;
	uint8_t  wp_grp_enable;
	uint8_t  r2w_factor;
	uint8_t  write_bl_len;
	uint8_t  write_bl_partial;
	uint8_t  file_format_grp;
	uint8_t  copy;
	uint8_t  perm_write_protect;
	uint8_t  tmp_write_protect;
	uint8_t  file_format;
	uint8_t  crc;
}csd;

typedef struct scr{
uint8_t SCR_structure;//use only lower 4 bits 63:60
uint8_t SD_spec;			//use only lower 4 bits 59:56
uint8_t DATA_STAT_AFTER_ERASE; //55:55
uint8_t SD_security;	//use only lower 3 bits 54:52
uint8_t SD_buswidth;	//use only lower 4 bits 51:48
uint8_t SD_spec3; //47:47
uint8_t ex_security;	//use only lower 4 bits 46:43
uint8_t cmd_support;	//use only lower 2 bits 33:32
}scr;

//page 74 of Physical Layer spec v3.01
//32-bit card status value is used in R1 and R6 responses
typedef struct cardStatus 
{
	uint8_t out_of_range; 		//31
	uint8_t addr_error;		//30
	uint8_t blk_len_err; 		//29
	uint8_t	erase_seq_err;		//28
	uint8_t erase_param;		//27
	uint8_t wp_violation;		//26
	uint8_t card_is_locked;		//25
	uint8_t lock_unlock_failed; 	//24
	uint8_t com_crc_err;		//23
	uint8_t illegal_cmd;		//22
	uint8_t card_ecc_failed;	//21
	uint8_t cc_error;		//20
	uint8_t error;			//19
	uint8_t csd_overwrite;		//16
	uint8_t wp_erase_skip;		//15
	uint8_t card_ecc_disable;	//14
	uint8_t erase_reset;		//13
	uint8_t current_state;		//12:9
	uint8_t ready_for_data;		//8
	uint8_t app_cmd;		//5
	uint8_t ake_seq_err;		//3
}cardStatus;

//three registers: OCR, RCA, DSR, are directly initialized in "sd.c" 

uint8_t flash_array[1024];//1 block or 1kByte

/*functions declarations and misc initialization*/
void sdCardControl();
void initializeSdCard();
void registerSdCardPipes();
void startSdCardThreads();

//takes data from the incoming cmd pipe and
//extracts the 48 bit frame contents
void extractCommandFromSDHC(const char* req_pipe, uint8_t *start_bit,
uint8_t *tx_bit, uint8_t *cmd_index, uint32_t *argument, uint8_t *crc7, uint8_t *end_bit);


//initiates actions to be performed based on received frame's command index
void actionForReceivedCommandIndex(uint8_t cmd_index);

//sends CID/CSD as response R2
// Gather values to be put together for R2 response and load them in a pipe
//TODO: should the response pipe(s) for R2 response be declared as
//3 pipes of 64, 64 & 8 bits OR should the sdhc take care of this 
//when CMD3 is sent to SD card and is expecting a 136 bit response
void sendR2Response();//IN PROGRESS

void sendR3Response();

//Gather values to be put together for R6 response and load them in a pipe
void sendR6Response();


//functions that read commands from the SDHC
//and send responses
void readFromSDHC();
void writeToSDHC();

//functions that perform read and writes to the 
//flash memory
void readFromFlashMemory(uint8_t flash_array);
void writeToFlashMemory(uint8_t flash_array);
#endif
