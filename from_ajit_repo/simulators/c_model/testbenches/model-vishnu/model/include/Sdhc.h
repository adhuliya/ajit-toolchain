//Authors:
//2. Saurabh Bansode
//3. Vishnu Easwaran E
//Last updated: 21 Dec '20

#ifndef _SDHC_H
#define _SDHC_H

#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"

// SDHC register addresses
#define ADDR_SDHC_ARG_2                         0xFFFF3300      // 4 BYTES WIDE
#define ADDR_SDHC_BLOCK_SIZE                    0xFFFF3304      // 2 BYTES WIDE
#define ADDR_SDHC_BLOCK_COUNT                   0xFFFF3306      // 2 BYTES WIDE
#define ADDR_SDHC_ARG_1                         0xFFFF3308      // 4 BYTES WIDE
#define ADDR_SDHC_TRANSFER_MODE                 0xFFFF330C      // 2 BYTES WIDE
#define ADDR_SDHC_REGISTER_COMMAND              0xFFFF330E      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE0                     0xFFFF3310      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE1                     0xFFFF3312      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE2                     0xFFFF3314      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE3                     0xFFFF3316      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE4                     0xFFFF3318      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE5                     0xFFFF331A      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE6                     0xFFFF331C      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE7                     0xFFFF331E      // 2 BYTES WIDE
#define ADDR_SDHC_BUFFER_DATA_PORT              0xFFFF3320      // 4 BYTES WIDE
#define ADDR_SDHC_PRESENT_STATE                 0xFFFF3324      // 4 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROL_1                0xFFFF3328      // 1 BYTES WIDE
#define ADDR_SDHC_POWER_CONTROL                 0xFFFF3329      // 1 BYTES WIDE
#define ADDR_SDHC_BLOCK_GAP_CONTROL             0xFFFF332A      // 1 BYTES WIDE
#define ADDR_SDHC_WAKEUP_CONTROL                0xFFFF332B      // 1 BYTES WIDE
#define ADDR_SDHC_CLOCK_CONTROL                 0xFFFF332C      // 2 BYTES WIDE
#define ADDR_SDHC_TIMEOUT_CONTROL               0xFFFF332E      // 1 BYTES WIDE
#define ADDR_SDHC_SOFTWARE_RESET                0xFFFF332F      // 1 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_STATUS            0xFFFF3330      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_STATUS             0xFFFF3332      // 2 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_STATUS_EN         0xFFFF3334      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_STATUS_EN          0xFFFF3336      // 2 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_SIGNAL_EN         0xFFFF3338      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_SIGNAL_EN          0xFFFF333A      // 2 BYTES WIDE
#define ADDR_SDHC_AUTO_CMD_ERROR_STATUS         0xFFFF333C      // 2 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROL_2                0xFFFF333E      // 2 BYTES WIDE
#define ADDR_SDHC_CAPS                          0xFFFF3340      // 8 BYTES WIDE
#define ADDR_SDHC_MAX_CURRENT_CAPS              0xFFFF3348      // 4 BYTES WIDE
#define ADDR_SDHC_MAX_CURRENT_CAPS_RES          0xFFFF334C      // 4 BYTES WIDE
#define ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT   0xFFFF3350      // 2 BYTES WIDE
#define ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT 0xFFFF3352      // 2 BYTES WIDE
#define ADDR_SDHC_ADMA_ERR_STAT                 0xFFFF3354      // 1 BYTE WIDE
#define ADDR_SDHC_ADMA_SYSTEM_ADDR              0xFFFF3358      // 8 BYTES WIDE
#define ADDR_SDHC_HOST_PRESET_VALUES            0xFFFF3360      // 16 BYTES WIDE
#define ADDR_SDHC_SHARED_BUS_CTRL               0xFFFF33E0      // 2 BYTES WIDE
#define ADDR_SDHC_SLOT_INTR_STATUS              0xFFFF33FC      // 2 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROLLER_VERSION       0xFFFF33FE      // 2 BYTES WIDE

//register pipes/signals used by the SDHC
void registerSdhcPipes();
void sdhcInitialState();

//this function will imitate the action of a SD card being
//physically inserted in the Slot and will change the necessary
//bits of internal registers.
void cardInsert();

void startSdhcThreads();

// Threads for SDHC control
//1. monitors data going to and coming from CPU via bridge 
//2. values are stored in sdhc_reg_cpu_view struct 
//3. Copies the values of sdhc_reg_cpu_view inside
//	sdhc_reg_internal_view struct using updateRegister function
void sdhcControl();

typedef struct sdhc_reg_internal_view
{
        uint32_t argument2; 			//0x0
        uint16_t blk_size; 			//0x4 	
        uint16_t blk_count; 			//0x6 		
        uint32_t argument1;			//0x8		
        uint16_t tx_mode; 			//0xC 		
        uint16_t command_reg; 			//0xE		
        uint16_t response0; 			//0x10		
        uint16_t response1; 			//0x12		
        uint16_t response2; 			//0x14 		
        uint16_t response3; 			//0x16 		
        uint16_t response4; 			//0x18 		
        uint16_t response5; 			//0x1A		
        uint16_t response6; 			//0x1C 		
        uint16_t response7; 			//0x1E	
        uint32_t buffer_data_port; 		//0x20 
        uint32_t present_state; 		//0x24 		
        uint8_t  host_ctrl1;			//0x28
        uint8_t  pwr_ctrl; 			//0x29 		
        uint8_t  blk_gap_ctrl; 			//0x2A 		
        uint8_t  wakeup_ctrl; 			//0x2B
        uint16_t clk_ctrl; 			//0x2C 		 	
        uint8_t  timeout_ctrl; 			//0x2E
        uint8_t  sw_reset; 			//0x2F
        uint16_t normal_intr_status; 		//0x30 
        uint16_t error_intr_status; 		//0x32 	
        uint16_t normal_intr_status_enable; 	//0x34 
        uint16_t error_intr_status_enable; 	//0x36 
        uint16_t normal_intr_signal_enable; 	//0x38
        uint16_t error_intr_signal_enable; 	//0x3A 	
        uint16_t autoCMD_error_status; 		//0x3C 		
        uint16_t host_ctrl2; 			//0x3E 			
        uint64_t capabilities; 			//0x40 TODO needs to be split to two 32b regs
        uint32_t max_current_cap; 		//0x48
        uint32_t res_max_current_cap; 		//0x4C
        uint16_t force_event_autoCMD_err_stat;	//0x50
        uint16_t force_event_autoCMD_err_interrupt_stat;	//0x52
        uint8_t  ADMA_err_status;		//0x54
        uint64_t ADMA_system_address; 		//0x58 TODO needs to be split to two 32b regs
        __uint128_t preset_value ; 		//0x60 TODO needs to be split to four 32b regs
        uint16_t shared_bus_control;		//0xE0
        uint16_t slot_interrupt_status;		//0xFC
        uint16_t host_controller_version; 	//0xFE 
}sdhc_reg_internal_view;

typedef struct sdhc_reg_cpu_view
{
        uint8_t argument2[4];   		//0x0  	
        uint8_t blk_size[2];    		//0x4 		
        uint8_t blk_count[2];   		//0x6 		
        uint8_t argument1[4];   		//0x8 		
        uint8_t tx_mode[2]; 			//0xC 
        uint8_t command_reg[2]; 		//0xE	
        uint8_t response0[2]; 			//0x10	
        uint8_t response1[2]; 			//0x12	
        uint8_t response2[2]; 			//0x14 	
        uint8_t response3[2]; 			//0x16 	
        uint8_t response4[2]; 			//0x18 	
        uint8_t response5[2]; 			//0x1A
        uint8_t response6[2]; 			//0x1C 
        uint8_t response7[2]; 			//0x1E
        uint8_t buffer_data_port[4]; 		//0x20
        uint8_t present_state[4];    		//0x24
        uint8_t host_ctrl1;   			//0x28 		
        uint8_t pwr_ctrl;     			//0x29
        uint8_t blk_gap_ctrl; 			//0x2A
        uint8_t wakeup_ctrl;  			//0x2B 		
        uint8_t clk_ctrl[2];  			//0x2C 		 	
        uint8_t timeout_ctrl; 			//0x2E
        uint8_t sw_reset;     			//0x2F	
        uint8_t normal_intr_status[2]; 		//0x30 
        uint8_t error_intr_status[2]; 		//0x32 
        uint8_t normal_intr_status_enable[2]; 	//0x34 	
        uint8_t error_intr_status_enable[2]; 	//0x36 	
        uint8_t normal_intr_signal_enable[2]; 	//0x38 	
        uint8_t error_intr_signal_enable[2]; 	//0x3A 	
        uint8_t autoCMD_error_status[2]; 	//0x3C 		
        uint8_t host_ctrl2[2]; 			//0x3E 			
        uint8_t capabilities[8]; 		//0x40
        uint8_t max_current_cap[4]; 		//0x48
        uint8_t res_max_current_cap[4]; 	//0x4C
        uint8_t force_event_autoCMD_err_stat[2];//0x50
        uint8_t force_event_autoCMD_err_interrupt_stat[2];	//0x52
        uint8_t ADMA_err_status;		//0x54 3 byte gap after this
        uint8_t gap_0[3];
        uint8_t ADMA_system_address[8]; 	//0x58
        uint8_t preset_value[16] ; 		//0x60 112 byte gap after this
        uint8_t gap_1[112];
        uint8_t shared_bus_control[2];		//0xE0 26 byte gap after this
        uint8_t gap_2[26];
        uint8_t slot_interrupt_status[2];	//0xFC
        uint8_t host_controller_version[2]; 	//0xFE 
}sdhc_reg_cpu_view;

/********************************************************************
 **
 ** uint32_t changeAddress(uint32_t addr, uint8_t byte_mask);
 **
 ** Args:       addr      - pointer to destination buffer
 **             byte_mask - pointer to source buffer
 **
 ** Return:     32 bit changed address
 **
 ** Purpose:    change and return the address accessed to the 
 **              absolute value using positioning of bits in 
 **              the byte_mask 
 **
 *******************************************************************/
uint32_t changeAddress(uint32_t addr, uint8_t byte_mask);

/********************************************************************
 **
 ** void syncBothStructs(sdhc_reg_cpu_view *cpu_view, 
 **                             sdhc_reg_internal_view *internal_view, 
 **                             uint8_t direction);
 **
 ** Args:       cpu_view        - pointer to byte-aligned register 
 **                                structure
 **             internal_view   - pointer to non-aligned register 
 **                                struct
 **             direction       - specify the direction of copying
 **             
 ** Return:     nothing returned
 **
 ** Purpose:    copies data between cpu_view and internal-view of 
 **             registers 
 **
 *******************************************************************/
void syncBothStructs(sdhc_reg_cpu_view *cpu_view, 
                                sdhc_reg_internal_view *internal_view, 
                                uint8_t direction);

/********************************************************************
 **
 ** uint32_t readOrWriteSdhcReg(uint32_t addr, uint8_t bytemask, 
 **                              sdhc_reg_cpu_view *cpu_view,
 **                              sdhc_reg_internal_view *internal_view, 
 **                              uint32_t data_in, 
 **                              uint8_t rwbar);
 **
 ** Args:       addr            - sdhc byte address.
 **             cpu_view        - pointer to byte-aligned register 
 **                                structure.
 **             internal_view   - pointer to non-aligned register 
 **                                structure.
 **             data_in         - incoming data that needs to be
 **                                written into specified register.
 **             rwbar           - specifies weather to read or write
 **             
 ** Return:     returns the value read, or 0 in case of write.
 **
 ** Purpose:    function that read or write to specified address
 **              and send corresponding responses.
 **
 *******************************************************************/
uint32_t readOrWriteSdhcReg(uint32_t addr, uint8_t bytemask, 
                                        sdhc_reg_cpu_view *cpu_view,
                                        sdhc_reg_internal_view *internal_view, 
                                        uint32_t data_in, 
                                        uint8_t rwbar);

/********************************************************************
 **
 ** uint32_t readFromsdhcReg(uint32_t addr, 
 **                             sdhc_reg_cpu_view *cpu_view, 
 **                             sdhc_reg_internal_view *internal_view);
 **
 ** Args:       addr            - sdhc byte address.
 **             cpu_view        - pointer to byte-aligned register 
 **                                structure.
 **             internal_view   - pointer to non-aligned register 
 **             
 ** Return:     returns data read
 **
 ** Purpose:    an internal function for reading a register, 
 **              without checking any conditions/flags.  
 **
 *******************************************************************/
uint32_t readFromsdhcReg(uint32_t addr, 
                                sdhc_reg_cpu_view *cpu_view, 
                                sdhc_reg_internal_view *internal_view);

/********************************************************************
 **
 ** uint32_t checkAndReadSdhcReg(uint32_t addr, 
 **                               sdhc_reg_cpu_view *cpu_view, 
 **                               sdhc_reg_internal_view *internal_view);
 **
 ** Args:       addr            - sdhc byte address.
 **             cpu_view        - pointer to byte-aligned register 
 **                                structure.
 **             internal_view   - pointer to non-aligned register 
 **                                structure.
 **             
 ** Return:     returns data read
 **
 ** Purpose:    a function for reading a register, 
 **              after checking for proper conditions/flags.
 **
 *******************************************************************/
uint32_t checkAndReadSdhcReg(uint32_t addr, 
                                sdhc_reg_cpu_view *cpu_view, 
                                sdhc_reg_internal_view *internal_view);

/********************************************************************
 **
 ** void writeToSdhcReg(uint32_t addr, 
 **                     uint8_t bytemask, 
 **                     sdhc_reg_cpu_view *cpu_view, 
 **                     sdhc_reg_internal_view *internal_view, 
 **                     uint32_t data_in);
 **
 ** Args:       addr            - sdhc byte address.
 **             byte_mask       - byte_mask corresponding to data 
 **                                position
 **             cpu_view        - pointer to byte-aligned register 
 **                                structure.
 **             internal_view   - pointer to non-aligned register 
 **                                structure.
 **             data_in         - incoming data that needs to be
 **                                written into specified register.
 **             
 ** Return:     returns nothing.
 **
 ** Purpose:    an internal function for writing to a register,
 **              without checking any conditions/flags
 **
 *******************************************************************/
void writeToSdhcReg(uint32_t addr, 
                        uint8_t bytemask, 
                        sdhc_reg_cpu_view *cpu_view, 
                        sdhc_reg_internal_view *internal_view, 
                        uint32_t data_in);

/********************************************************************
 **
 ** void checkAndWriteSdhcReg(uint32_t addr, 
 **                             uint8_t byte_mask, 
 **                             sdhc_reg_cpu_view *cpu_view,
 **                             sdhc_reg_internal_view *internal_view, 
 **                             uint32_t data_in);
 **
 ** Args:       addr            - sdhc byte address.
 **             byte_mask       - byte_mask corresponding to data 
 **                                position
 **             cpu_view        - pointer to byte-aligned register 
 **                                structure.
 **             internal_view   - pointer to non-aligned register 
 **                                structure.
 **             data_in         - incoming data that needs to be
 **                                written into specified register.
 **             
 ** Return:     returns nothing.
 **
 ** Purpose:    a function for writing to a register,
 **              after checking for proper conditions/flags.
 **
 *******************************************************************/
void checkAndWriteSdhcReg(uint32_t addr, 
                                uint8_t byte_mask, 
                                sdhc_reg_cpu_view *cpu_view,
                                sdhc_reg_internal_view *internal_view, 
                                uint32_t data_in);

#endif
