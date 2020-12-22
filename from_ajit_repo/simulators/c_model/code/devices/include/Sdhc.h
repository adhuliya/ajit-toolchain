//Authors:
//1. Prof. Madhav Desai
//2. Saurabh Bansode
//3. Vishnu Easwaran E
//Last updated: 21 Dec '20

#ifndef _SDHC_H
#define _SDHC_H

#include<stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
// bit masks for standard registers

// present state register
#define  SDHCI_CMD_INHIBIT	0x00000001
#define  SDHCI_DATA_INHIBIT	0x00000002
#define  SDHCI_DOING_WRITE	0x00000100
#define  SDHCI_DOING_READ	0x00000200
#define  SDHCI_SPACE_AVAILABLE	0x00000400
#define  SDHCI_DATA_AVAILABLE	0x00000800
#define  SDHCI_CARD_PRESENT	0x00010000
#define  SDHCI_WRITE_PROTECT	0x00080000
#define  SDHCI_DATA_LVL_MASK	0x00F00000
#define   SDHCI_DATA_LVL_SHIFT	20

// clk control
#define  SDHCI_DIVIDER_SHIFT	8
#define  SDHCI_DIVIDER_HI_SHIFT	6
#define  SDHCI_DIV_MASK		0xFF
#define  SDHCI_DIV_MASK_LEN	8
#define  SDHCI_DIV_HI_MASK	0x300
#define  SDHCI_PROG_CLOCK_MODE	0x0020
#define  SDHCI_CLOCK_CARD_EN	0x0004
#define  SDHCI_CLOCK_INT_STABLE	0x0002
#define  SDHCI_CLOCK_INT_EN	0x0001

//capabilities
#define  SDHCI_TIMEOUT_CLK_MASK	0x0000003F
#define  SDHCI_TIMEOUT_CLK_SHIFT 0
#define  SDHCI_TIMEOUT_CLK_UNIT	0x00000080
#define  SDHCI_CLOCK_BASE_MASK	0x00003F00
#define  SDHCI_CLOCK_V3_BASE_MASK	0x0000FF00
#define  SDHCI_CLOCK_BASE_SHIFT	8
#define  SDHCI_MAX_BLOCK_MASK	0x00030000
#define  SDHCI_MAX_BLOCK_SHIFT  16
#define  SDHCI_CAN_DO_8BIT	0x00040000
#define  SDHCI_CAN_DO_ADMA2	0x00080000
#define  SDHCI_CAN_DO_ADMA1	0x00100000
#define  SDHCI_CAN_DO_HISPD	0x00200000
#define  SDHCI_CAN_DO_SDMA	0x00400000
#define  SDHCI_CAN_VDD_330	0x01000000
#define  SDHCI_CAN_VDD_300	0x02000000
#define  SDHCI_CAN_VDD_180	0x04000000
#define  SDHCI_CAN_64BIT	0x10000000
#define  SDHCI_SUPPORT_SDR50	0x00000001
#define  SDHCI_SUPPORT_SDR104	0x00000002
#define  SDHCI_SUPPORT_DDR50	0x00000004
#define  SDHCI_DRIVER_TYPE_A	0x00000010
#define  SDHCI_DRIVER_TYPE_C	0x00000020
#define  SDHCI_DRIVER_TYPE_D	0x00000040
#define  SDHCI_RETUNING_TIMER_COUNT_MASK	0x00000F00
#define  SDHCI_RETUNING_TIMER_COUNT_SHIFT	8
#define  SDHCI_USE_SDR50_TUNING			0x00002000
#define  SDHCI_RETUNING_MODE_MASK		0x0000C000
#define  SDHCI_RETUNING_MODE_SHIFT		14
#define  SDHCI_CLOCK_MUL_MASK	0x00FF0000
#define  SDHCI_CLOCK_MUL_SHIFT	16

//power control register
#define  SDHCI_BUS_POWER_ON		0x01
#define  SDHCI_BUS_POWER_180	0x0A
#define  SDHCI_BUS_POWER_300	0x0C
#define  SDHCI_BUS_POWER_330	0x0E

/* OCR bit definitions */
#define SD_OCR_S18R		(1 << 24)    /* 1.8V switching request */
#define SD_ROCR_S18A	SD_OCR_S18R  /* 1.8V switching accepted by card */
#define SD_OCR_XPC		(1 << 28)    /* SDXC power control */
#define SD_OCR_CCS		(1 << 30)    /* Card Capacity Status */

/*	RESET Related	*/
#define SDHCI_SOFTWARE_RESET	0x2F
#define  SDHCI_RESET_ALL	0x01
#define  SDHCI_RESET_CMD	0x02
#define  SDHCI_RESET_DATA	0x04

/*	Interrupt register related*/
#define SDHCI_INT_STATUS	0x30
#define SDHCI_INT_ENABLE	0x34
#define SDHCI_SIGNAL_ENABLE	0x38
#define  SDHCI_INT_RESPONSE	0x00000001
#define  SDHCI_INT_DATA_END	0x00000002
#define  SDHCI_INT_BLK_GAP	0x00000004
#define  SDHCI_INT_DMA_END	0x00000008
#define  SDHCI_INT_SPACE_AVAIL	0x00000010
#define  SDHCI_INT_DATA_AVAIL	0x00000020
#define  SDHCI_INT_CARD_INSERT	0x00000040
#define  SDHCI_INT_CARD_REMOVE	0x00000080
#define  SDHCI_INT_CARD_INT	0x00000100
#define  SDHCI_INT_ERROR	0x00008000
#define  SDHCI_INT_TIMEOUT	0x00010000
#define  SDHCI_INT_CRC		0x00020000
#define  SDHCI_INT_END_BIT	0x00040000
#define  SDHCI_INT_INDEX	0x00080000
#define  SDHCI_INT_DATA_TIMEOUT	0x00100000
#define  SDHCI_INT_DATA_CRC	0x00200000
#define  SDHCI_INT_DATA_END_BIT	0x00400000
#define  SDHCI_INT_BUS_POWER	0x00800000
#define  SDHCI_INT_ACMD12ERR	0x01000000
#define  SDHCI_INT_ADMA_ERROR	0x02000000

#define  SDHCI_INT_NORMAL_MASK	0x00007FFF
#define  SDHCI_INT_ERROR_MASK	0xFFFF8000

/*	Host Control Register*/

#define SDHCI_HOST_CONTROL	0x28
#define  SDHCI_CTRL_LED		0x01
#define  SDHCI_CTRL_4BITBUS	0x02
#define  SDHCI_CTRL_HISPD	0x04
#define  SDHCI_CTRL_DMA_MASK	0x18
#define   SDHCI_CTRL_SDMA	0x00
#define   SDHCI_CTRL_ADMA1	0x08
#define   SDHCI_CTRL_ADMA32	0x10
#define   SDHCI_CTRL_ADMA64	0x18
#define   SDHCI_CTRL_8BITBUS	0x20


//register pipes/signals used by the SDHC
void register_sdhc_pipes();
void sdhc_initialize();
void start_sdhc_threads();

//Functions for register value manipulations
void updateRegister(uint32_t data_in, uint32_t addr, uint8_t byte_mask);


// Threads for SDHC control
void SDHC_CPU_Control(); //monitors data going to and
	//coming from CPU via bridge, 
	//values stored in CPUViewOfSDHCRegArray
void SDHC_Internal(); //copies data from CPUViewOfSDHCRegArray into
	//internal registers, takes actions accordingly,
	//values stored in SDHCInternalMap
	//syncs the two structs

typedef struct SDHCInternalMap
{
	uint32_t argument2; //0x0
	uint16_t blk_size; // 0x4 		
	uint16_t blk_count; //0x6 		
	uint32_t argument1;//0x8		
	uint16_t tx_mode; //0xC 		
	uint16_t command_reg; //0xE		
	uint16_t response0; //0x10		
	uint16_t response1; //0x10		
	uint16_t response2; //0x14 		
	uint16_t response3; //0x18 		
	uint16_t response4; //0x1c 		
	uint16_t response5; //0x10		
	uint16_t response6; //0x14 		
	uint16_t response7; //0x18 		
	uint32_t buffer_data_port; //0x20 
	uint32_t present_state; //0x24 		
	uint8_t pwr_ctrl;//0x28
	uint8_t host_ctrl1; //0x29 		
	uint8_t wakeup_ctrl; //0x2A 		
	uint8_t blk_gap_ctrl; //0x2B
	uint16_t clk_ctrl; //0x2C 		 	
	uint8_t sw_reset; //0x2E
	uint8_t timeout_ctrl; //0x2F
	uint16_t normal_intr_status; //0x30 
	uint16_t error_intr_status; //0x32 	
	uint16_t normal_intr_status_enable; //0x34 
	uint16_t error_intr_status_enable; //0x36 
	uint16_t normal_intr_signal_enable; //0x38
	uint16_t error_intr_signal_enable; //0x3A 	
	uint16_t autoCMD_error_status; //0x3C 		
	uint16_t host_ctrl2; //0x3E 			
	uint64_t capabilities; //0x40
	uint32_t max_current_cap; //0x48
	uint32_t res_max_current_cap; //0x4C
	uint16_t force_event_autoCMD_err_stat;//0x50
	uint16_t force_event_autoCMD_err_interrupt_stat;//0x52
	uint8_t ADMA_err_status;//0x55
	uint64_t ADMA_system_address; //0x58
	__uint128_t preset_value ; //0x60
	uint16_t shared_bus_control;//0xE0
	uint16_t slot_interrupt_status;//0xFC
 	uint16_t host_controller_version; //0xFE 
}SDHCInternalMap;

typedef struct CPUViewOfSDHCRegArray
{
	uint8_t argument2[4];   //0x0  	
	uint8_t blk_size[2];    // 0x4 		
	uint8_t blk_count[2];   //0x6 		
	uint8_t argument1[4];   //0x8 		
	uint8_t tx_mode[2]; 	  //0xC 
	uint8_t command_reg[2]; //0xE	
	uint8_t response0[2]; //0x10	
	uint8_t response1[2]; //0x10	
	uint8_t response2[2]; //0x14 	
	uint8_t response3[2]; //0x18 	
	uint8_t response4[2]; //0x1c 	
	uint8_t response5[2]; //0x10
	uint8_t response6[2]; //0x14 
	uint8_t response7[2]; //0x18
	uint8_t buffer_data_port[4]; //0x20
	uint8_t present_state[4];    //0x24
	uint8_t pwr_ctrl;     //0x28
	uint8_t host_ctrl1;   //0x29 		
	uint8_t wakeup_ctrl;  //0x2A 		
	uint8_t blk_gap_ctrl; //0x2B
	uint8_t clk_ctrl[2];  //0x2C 		 	
	uint8_t sw_reset;     //0x2E
	uint8_t timeout_ctrl; //0x2F
	uint8_t normal_intr_status[2]; //0x30 
	uint8_t error_intr_status[2]; //0x32 
	uint8_t normal_intr_status_enable[2]; //0x34 	
	uint8_t error_intr_status_enable[2]; //0x36 	
	uint8_t normal_intr_signal_enable[2]; //0x38 	
	uint8_t error_intr_signal_enable[2]; //0x3A 	
	uint8_t autoCMD_error_status[2]; //0x3C 		
	uint8_t host_ctrl2[2]; //0x3E 			
	uint8_t capabilities[8]; //0x40
	uint8_t max_current_cap[4]; //0x48
	uint8_t res_max_current_cap[4]; //0x4C
	uint8_t force_event_autoCMD_err_stat[2];//0x50
	uint8_t force_event_autoCMD_err_interrupt_stat[2];//0x52
	uint8_t ADMA_err_status;//0x55
	uint8_t ADMA_system_address[8]; //0x58
	uint8_t preset_value[16] ; //0x60
	uint8_t shared_bus_control[2];//0xE0
	uint8_t slot_interrupt_status[2];//0xFC
 	uint8_t host_controller_version[2]; //0xFE 
}CPUViewOfSDHCRegArray;

char readDataFromSDCard();
void writeDataToSDCard(uint64_t inputToSDCard);

#endif
