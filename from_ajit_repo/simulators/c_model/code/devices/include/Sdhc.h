//Authors:
//1. Prof. Madhav Desai
//2. Saurabh Bansode
//Last updated: 12 Oct '20 by SB
#ifndef _SDHC_H
#define _SDHC_H
#include<stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"

//register pipes/signals used by the SDHC
void register_sdhc_pipes();

//start SDHC thread
void start_sdhc_threads();
//SDHC control thread overlooks the overall ops
//SDHC Read will perform read ops 
//SDHC Write will perform write ops
void SDHC_Control();
void SDHC_Read();
void SDHC_Write();

// data structures
typedef struct SdhcState__ {
	// registers of SDHC
uint32_t argument2; //addr-offset 0x00
uint16_t blk_size; // 0x4
uint16_t blk_count; //0x6
uint32_t argument; //0x8
uint16_t tx_mode; //0xC
uint16_t command_reg; //0xE
uint32_t response0; //0x10
uint32_t response2; //0x14
uint32_t response4; //0x18
uint32_t response6; //0x1c
uint32_t buffer_data_port; //0x20
uint32_t present_state; //0x24
uint8_t host_ctrl; //ox28
uint8_t pwr_ctrl;//0x29
uint8_t blk_gap_ctrl; //0x2A 
uint8_t wakeup_ctrl; //0x2B
uint16_t clk_ctrl; //0x2C
uint8_t timeout_ctrl; //0x2E
uint8_t sw_reset; //0x2F
uint16_t normal_intr_status; //0x30
uint16_t error_intr_status; //0x32
uint16_t normal_intr_status_enable; //0x34
uint16_t error_intr_status_enable; //0x36
uint16_t normal_intr_signal_enable; //0x38
uint16_t error_intr_signal_enable; //0x3A
uint16_t autoCMD_error_status; //0x3C
uint16_t host_ctrl2; //0x3E
uint32_t capabilities; //0x40
uint16_t host_controller_version; //0xFE
	SdcardState sd_card_state;
} SdhcState;

typedef struct SdcardState {
	// registers

	// storage array.
} SdcardState;

void initSdcardState();
{
// return 0 if read ok, else 1 - communication check
int readBlock(SdcardState* s, int block_size_in_bytes, int block_start_byte_index, uint8_t* barray);
int writeBlock(SdcardState* s, int block_size_in_bytes, int block_start_byte_index, uint8_t* barray);
// etc...
}

#endif
