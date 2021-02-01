//Authors: Saurabh Bansode
//Last updated: 29 Jan '21
#include<stdio.h>
#include<stdint.h>

typedef struct internal_view
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
	uint64_t capabilities; 			//0x40
	uint32_t max_current_cap; 		//0x48
	uint32_t res_max_current_cap; 		//0x4C
	uint16_t force_event_autoCMD_err_stat;	//0x50
	uint16_t force_event_autoCMD_err_interrupt_stat;	//0x52
	uint8_t  ADMA_err_status;		//0x54
	uint64_t ADMA_system_address; 		//0x58
	__uint128_t preset_value ; 		//0x60
	uint16_t shared_bus_control;		//0xE0
	uint16_t slot_interrupt_status;		//0xFC
 	uint16_t host_controller_version; 	//0xFE 
}internal_view;

typedef struct cpu_view
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
	uint8_t ADMA_err_status;		//0x54
	uint8_t ADMA_system_address[8]; 	//0x58
	uint8_t preset_value[16] ; 		//0x60
	uint8_t shared_bus_control[2];		//0xE0
	uint8_t slot_interrupt_status[2];	//0xFC
 	uint8_t host_controller_version[2]; 	//0xFE 
}cpu_view;

//register pipes/signals used by the SDHC
void registerSdhcPipes();

//this function will read the SDCARD_to_SDHC port and
//change the necessary bits of internal registers.
void startSdhcThreads();

// Threads for SDHC control
//1.monitors data going to and coming from CPU via bridge 
//2. values are stored in sdhc_reg_cpu_view struct 
//3. Copies the values of sdhc_reg_cpu_view inside
//	sdhc_reg_internal_view struct using updateRegister function
void sdhcControl();

//Functions for register value manipulations
uint32_t writeSdhcReg(uint32_t data_in, uint32_t addr, uint8_t byte_mask, 
			cpu_view *cpu_reg_view, 
			internal_view *internal_reg_view);

uint32_t readSdhcReg(uint32_t addr,  
			cpu_view *cpu_reg_view, 
			internal_view *internal_reg_view);
