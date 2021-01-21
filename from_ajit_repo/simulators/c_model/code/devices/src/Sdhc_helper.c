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
#include "sdhc.c"
#include "sd.h"

void generateCommandForSDCard(struct sdhc_reg_internal_view *internal_reg_view)
{
//extracting command index value to be inserted in bits 40:45
	uint8_t cmd_index = getSlice16(internal_reg_view->command_reg,13,8);
	uint8_t crc7=7;//dummy value for now, will be updated with crc7 function's
							//return value later
	uint64_t frame_data=0;
	frame_data|=0UL<<47;//start bit
	frame_data|=1UL<<46;//tx bit
	frame_data|=(uint64_t)cmd_index<<40;
	frame_data|=internal_reg_view->argument1<<8;
	frame_data|=crc7<<1;
	frame_data|=0UL<<0;
	write_uint64("sdhc_to_sdcard_request",frame_data);
}

uint8_t checkResponseType(struct sdhc_reg_internal_view *internal_reg_view, struct sdhc_reg_cpu_view *cpu_reg_view)
{
	uint8_t n = getSlice16(internal_reg_view->command_reg,13,8);
	uint8_t cmd;
	if( (n == 0)|| (n==4) ||(n==15))//No response
  	cmd = (0<<6)|(0<<5)|(0<<4)|(0<<3)|0;
  else if((n==2)||(n==9)||(n==10))//Response generated is R2.
    cmd = (0<<6)|(0<<5)|(0<<4)|(1<<3)|(0<<2)|1;
  else if ((n == 411) || (n == 412)) //Response generated is R3.
  {
    n=41;
    cmd = (0<<6)|(0<<5)|(0<<4)|(0<<3)|(0<<2)|2;
  }
  else if((n == 55)||(n == 3)||(n==8)||(n==17)||(n==19)||(n==24)||(n==25))
  //Response generated is of the type R1/R7.
  {
    if((n==17)||(n==24)||(n==25))
    cmd = (0<<6)|(1<<5)|(1<<4)|(1<<3)|(0<<2)|2;
    else
    cmd = (0<<6)|(0<<5)|(1<<4)|(1<<3)|(0<<2)|2;
  }
  else//Response Type R1b, R5b
  {
  cmd = (0<<6)|(0<<5)|(1<<4)|(1<<3)|(0<<2)|3;
  }
  return (cmd & 0xff);
}

//if any bits in normal_intr_signal_en reg are set, they are 
//to be compared with the bits of normal_intr_stat reg and,
//if both are 1, interrupt has to be generated for that bit
void checkNormalInterrupts(struct sdhc_reg_internal_view *internal_reg_view, struct sdhc_reg_cpu_view *cpu_reg_view)
{	
	uint32_t normalStatusEnableBits = internal_map.normal_intr_status_enable & 0x1FFF;//12:0
	// To find which bit of the normal_interrrupt_status_enable register
	// has been set and reflect those in normal_interrupt_status register
	internal_map.normal_intr_status |= normalStatusEnableBits << 12;

	//copy these values to cpu side regs for normal-intr-stat reg
	uint8_t size=2;
	void *dest = &(cpu_reg_view->normal_intr_status);//cpu side regs are destination here
	void *source = &(internal_reg_view->normal_intr_status);
	memcpy(dest,source,size);	

	uint16_t intr_flag=0;
	if ( (internal_map.present_state>>16) & 0x1 )//card insertion check
	{	
		event_card_inserted=1;
		uint8_t norm_intr_stat_val = getBit16(internal_map.normal_intr_status,6);
		uint8_t norm_intr_sig_en_val = getBit16(internal_map.normal_intr_signal_enable,6);
		intr_flag = (norm_intr_sig_en_val & norm_intr_stat_val);
	}

	else if ( ((internal_map.present_state>>16) & 0x1) == 0)//card removal check
	{
		event_card_inserted=0;
		uint8_t norm_intr_stat_val = getBit16(internal_map.normal_intr_status,7);
		uint8_t norm_intr_sig_en_val = getBit16(internal_map.normal_intr_signal_enable,7);
		intr_flag = (norm_intr_sig_en_val & norm_intr_stat_val);
	}
	//	TODO: more checks for other interrupts sources to be added
	else if ( (internal_map.normal_intr_status>>15) & 0x1)//checks for error interrupts here itself first
	{
		intr_flag=1; 
	}
	
	else if ( internal_map.command_reg & 0x1 ) //command complete check interrupt
	{
		uint8_t norm_intr_stat_val = getBit16(internal_map.normal_intr_status,0);
		uint8_t norm_intr_sig_en_val = getBit16(internal_map.normal_intr_signal_enable,0);
		intr_flag = (norm_intr_sig_en_val & norm_intr_stat_val);		
	}
	
	switch (intr_flag)
	{
	case 1:
		SDHC_INT_OUT=SDHC_IRL;
		write_uint8("SDHC_to_IRC_INT",SDHC_INT_OUT);
		break;
	case 0:
		//de-asserts the interrupt that may have been generated earlier
		SDHC_INT_OUT = 0;
		write_uint8("SDHC_to_IRC_INT",SDHC_INT_OUT);
		break;
	default:	
		SDHC_INT_OUT = 0;
		write_uint8("SDHC_to_IRC_INT",SDHC_INT_OUT);
		break;
	}
}

void checkErrorInterrupts(struct sdhc_reg_internal_view *internal_reg_view, struct sdhc_reg_cpu_view *cpu_reg_view)
{
	uint16_t errorStatusEnableBits = internal_map.error_intr_status_enable & 0x1FFF;
	// To find which bit of the error_interrrupt_status_enable register
	// has been set and reflect those(12:0) in error_interrupt_status register
	internal_map.error_intr_status |= errorStatusEnableBits << 12;

	//copy these values to cpu side regs for error-intr-stat reg
	uint8_t size=2;		
	void *dest = &(cpu_reg_view->error_intr_status);//cpu side regs are destination here
	void *source = &(internal_reg_view->error_intr_status);
	memcpy(dest,source,size);	

	//check the "Normal" Interrupt status reg's 'MSB', 
	//if it is 1, means an error interrupt is present
	
	uint16_t err_sign_en_bits = getSlice16(internal_map.error_intr_signal_enable,12,0);
	uint16_t err_status_bits = getSlice16(internal_map.error_intr_status,12,0);
	if( ( (err_sign_en_bits & err_status_bits) !=0) )
	{
		//if the above ANDed value is non-zero, indicates that there is an error interrupt,
		//needs to be notified in the normal intr status's MSB
		//the error interrupt will be notified through the normal intr status reg.
		internal_map.normal_intr_status |= 1<<15;
		uint8_t size=2;		
		void *dest = &(cpu_reg_view->normal_intr_status);
		void *source = &(cpu_reg_view->normal_intr_status);
		memcpy(dest,source,size);
	}

	else // no error interrupt, send 0 to IRC
	{
		//de-asserts the interrupt that may have been generated earlier
		SDHC_INT_OUT = 0;
		write_uint8("SDHC_to_IRC_INT",SDHC_INT_OUT);		
	}
	//	TODO: write individual cases for all possible
	//	error interrupt sources
}

uint32_t readSdhcReg(uint32_t addr,
 			sdhc_reg_cpu_view *cpu_reg_view, sdhc_reg_internal_view *internal_reg_view)
{
	uint32_t data_out = 0;

	if (addr == (0xFFFFFF & ADDR_SDHC_ARG_2))
	{
		//cpu side regs are destination in readSdhcReg function
		void *dest = &cpu_reg_view->argument2[0];
		void *source = &internal_reg_view->argument2;
		memcpy(dest, source, sizeof(internal_reg_view->argument2));
		data_out = (uint32_t)(internal_reg_view->argument2);
	}
	else if (addr == (0xffffff & ADDR_SDHC_BLOCK_SIZE))
	{
		void *dest = &cpu_reg_view->blk_size[0];
		void *source = &internal_reg_view->blk_size;
		memcpy(dest,source,sizeof(internal_reg_view->blk_size));
		data_out = (uint32_t)(internal_reg_view->blk_size);
	}
	else if (addr == (0xffffff & ADDR_SDHC_BLOCK_COUNT))
	{
		void *dest = &cpu_reg_view->blk_count[0];
		void *source = &internal_reg_view->blk_count;
		memcpy(dest,source,sizeof(internal_reg_view->blk_count));
		data_out = (uint32_t)internal_reg_view->blk_count;
	}
	else if (addr == (0xffffff & ADDR_SDHC_ARG_1))
	{
		void *dest = &cpu_reg_view->argument1[0];
		void *source = &internal_reg_view->argument1;
		memcpy(dest,source,sizeof(internal_reg_view->argument1));
		data_out = (uint32_t)(internal_reg_view->argument1);
	}
	else if (addr == (0xffffff & ADDR_SDHC_TRANSFER_MODE))
	{
		void *dest = &cpu_reg_view->tx_mode[0];
		void *source = &internal_reg_view->tx_mode;
		memcpy(dest,source,sizeof(internal_reg_view->tx_mode));
		data_out = (uint32_t)internal_reg_view->tx_mode;
	}
	else if (addr == (0xffffff & ADDR_SDHC_REGISTER_COMMAND))
	{
		void *dest = &cpu_reg_view->command_reg[0];
		void *source = &internal_reg_view->command_reg;
		memcpy(dest,source,sizeof(internal_reg_view->command_reg));
		data_out = (uint32_t)internal_reg_view->command_reg;
	}
					/*	else if	((addr>=ADDR_SDHC_RESPONSE0)&&(addr<=ADDR_SDHC_RESPONSE7))
						{
					In progress
						}*/	
	else if (addr == (0xffffff & ADDR_SDHC_BUFFER_DATA_PORT))
	{
		void *dest = &cpu_reg_view->buffer_data_port[0];
		void *source = &internal_reg_view->buffer_data_port;
		memcpy(dest,source,sizeof(internal_reg_view->buffer_data_port));
		data_out = (uint32_t)internal_reg_view->buffer_data_port;
	}
	else if (addr == (0xffffff & ADDR_SDHC_PRESENT_STATE))
	{
		void *dest = &cpu_reg_view->present_state[0];
		void *source = &internal_reg_view->present_state;
		memcpy(dest,source,sizeof(internal_reg_view->present_state));
		data_out = (uint32_t)internal_reg_view->present_state;			
	}
	else if (addr == (0xffffff & ADDR_SDHC_HOST_CONTROL_1))
	{
		void *dest = &cpu_reg_view->host_ctrl1;
		void *source = &internal_reg_view->host_ctrl1;
		memcpy(dest,source,sizeof(internal_reg_view->host_ctrl1));
		data_out = (uint32_t)internal_reg_view->host_ctrl1;			
	}
	else if(addr == (0xffffff & ADDR_SDHC_POWER_CONTROL))
	{
		void *dest = &cpu_reg_view->pwr_ctrl;
		void *source = &internal_reg_view->pwr_ctrl;
		memcpy(dest,source,sizeof(internal_reg_view->pwr_ctrl));
		data_out = (uint32_t)internal_reg_view->pwr_ctrl;						
	}
	else if (addr == (0xffffff & ADDR_SDHC_BLOCK_GAP_CONTROL))
	{
		void *dest = &cpu_reg_view->blk_gap_ctrl;
		void *source = &internal_reg_view->blk_gap_ctrl;
		memcpy(dest,source,sizeof(internal_reg_view->blk_gap_ctrl));
		data_out = (uint32_t)internal_reg_view->blk_gap_ctrl;
	}
	else if (addr == (0xffffff & ADDR_SDHC_WAKEUP_CONTROL))
	{
		void *dest = &cpu_reg_view->wakeup_ctrl;
		void *source = &internal_reg_view->wakeup_ctrl;
		memcpy(dest,source,sizeof(internal_reg_view->wakeup_ctrl));
		data_out = (uint32_t)internal_reg_view->wakeup_ctrl;
	}
	else if (addr == (0xffffff & ADDR_SDHC_CLOCK_CONTROL))
	{
		void *dest = &cpu_reg_view->clk_ctrl[0];
		void *source = &internal_reg_view->clk_ctrl;
		memcpy(dest,source,sizeof(internal_reg_view->clk_ctrl));
		data_out = (uint32_t)internal_reg_view->clk_ctrl;
	}
	else if (addr == (0xffffff & ADDR_SDHC_TIMEOUT_CONTROL))
	{
		void *dest = &cpu_reg_view->timeout_ctrl;
		void *source = &internal_reg_view->timeout_ctrl;
		memcpy(dest,source,sizeof(internal_reg_view->timeout_ctrl));
		data_out = (uint32_t)internal_reg_view->timeout_ctrl;
	}
	else if (addr == (0xffffff & ADDR_SDHC_SOFTWARE_RESET))
	{
		void *dest = &cpu_reg_view->sw_reset;
		void *source = &internal_reg_view->sw_reset;
		memcpy(dest,source,sizeof(internal_reg_view->sw_reset));
		data_out = (uint32_t)internal_reg_view->sw_reset;
	}		
	else if (addr == (0xffffff & ADDR_SDHC_NORMAL_INTR_STATUS))
	{
		void *dest = &cpu_reg_view->normal_intr_status[0];
		void *source = &internal_reg_view->normal_intr_status;
		memcpy(dest,source,sizeof(internal_reg_view->normal_intr_status));
		data_out = (uint32_t)internal_reg_view->normal_intr_status;
	}
	else if (addr == (0xffffff & ADDR_SDHC_ERROR_INTR_STATUS))
	{
		void *dest = &cpu_reg_view->error_intr_status[0];
		void *source = &internal_reg_view->error_intr_status;
		memcpy(dest,source,sizeof(internal_reg_view->error_intr_status));
		data_out = (uint32_t)internal_reg_view->error_intr_status;
	}	
	else if (addr == (0xffffff & ADDR_SDHC_NORMAL_INTR_STATUS_EN))
	{
		void *dest = &cpu_reg_view->normal_intr_status_enable[0];
		void *source = &internal_reg_view->normal_intr_status_enable;
		memcpy(dest,source,sizeof(internal_reg_view->normal_intr_status_enable));
		data_out = (uint32_t)internal_reg_view->normal_intr_status_enable;
	}	
	else if (addr == (0xffffff & ADDR_SDHC_ERROR_INTR_STATUS_EN))
	{
		void *dest = &cpu_reg_view->error_intr_status_enable[0];
		void *source = &internal_reg_view->error_intr_status_enable;
		memcpy(dest,source,sizeof(internal_reg_view->error_intr_status_enable));
		data_out = (uint32_t)internal_reg_view->error_intr_status_enable;
	}
	else if (addr == (0xffffff & ADDR_SDHC_NORMAL_INTR_SIGNAL_EN))
	{
		void *dest = &cpu_reg_view->normal_intr_signal_enable[0];
		void *source = &internal_reg_view->normal_intr_signal_enable;
		memcpy(dest,source,sizeof(internal_reg_view->normal_intr_signal_enable));
		data_out = (uint32_t)internal_reg_view->normal_intr_signal_enable;
	}
	else if (addr == (0xffffff & ADDR_SDHC_ERROR_INTR_SIGNAL_EN))
	{
		void *dest = &cpu_reg_view->error_intr_signal_enable[0];
		void *source = &internal_reg_view->error_intr_signal_enable;
		memcpy(dest,source,sizeof(internal_reg_view->error_intr_signal_enable));
		data_out = (uint32_t)internal_reg_view->error_intr_signal_enable;
	}		
	else if (addr == (0xffffff & ADDR_SDHC_AUTO_CMD_ERROR_STATUS))
	{
		void *dest = &cpu_reg_view->autoCMD_error_status[0];
		void *source = &internal_reg_view->autoCMD_error_status;
		memcpy(dest,source,sizeof(internal_reg_view->autoCMD_error_status));
		data_out = (uint32_t)internal_reg_view->autoCMD_error_status;
	}		
	else if (addr == (0xffffff & ADDR_SDHC_HOST_CONTROL_2))
	{
		void *dest = &cpu_reg_view->host_ctrl2[0];
		void *source = &internal_reg_view->host_ctrl2;
		memcpy(dest,source,sizeof(internal_reg_view->host_ctrl2));
		data_out = (uint32_t)internal_reg_view->host_ctrl2;
	}		
	else if (addr == (0xffffff & ADDR_SDHC_CAPS))
	{
		void *dest = &cpu_reg_view->capabilities[0];
		void *source = &internal_reg_view->capabilities;
		memcpy(dest,source,sizeof(internal_reg_view->capabilities));
		data_out = (uint32_t)internal_reg_view->capabilities;
	}	
	else if (addr == (0xffffff & ADDR_SDHC_MAX_CURRENT_CAPS))
	{
		void *dest = &cpu_reg_view->max_current_cap[0];
		void *source = &internal_reg_view->max_current_cap;
		memcpy(dest,source,sizeof(internal_reg_view->max_current_cap));
		data_out = (uint32_t)internal_reg_view->max_current_cap;
	}	
	// sendPeripheralResponse("sdhc_to_peripheral_bridge_response", data_out);

	return data_out;
}

void writeSdhcReg(uint32_t data_in, uint32_t addr, uint8_t byte_mask,
 			struct sdhc_reg_cpu_view *str, struct sdhc_reg_internal_view *internal_reg_view)
{
	uint32_t data_in_masked = insertUsingByteMask(0, data_in, byte_mask);
	uint32_t data_out=0;
	if (addr== (0xffffff & ADDR_SDHC_ARG_2))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->argument2[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		str->argument2[1] = temp2;
		uint8_t temp3 = getSlice32(data_in_masked,23,16);
		str->argument2[2] = temp3;
		uint8_t temp4 = getSlice32(data_in_masked,31,24);
		str->argument2[3] = temp4;
		uint8_t size=4;
		void *dest = &(internal_reg_view->argument2);//internal regs are destionation here
		void *source = &(str->argument2);
		memcpy(dest,source,size);
	}

	else if (addr== (0xffffff & ADDR_SDHC_BLOCK_SIZE))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->blk_size[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		str->blk_size[1] = temp2;
		uint8_t size=2;
		void *dest = &(internal_reg_view->blk_size);
		void *source = &(str->blk_size);
		memcpy(dest,source,size);
	}

	else if (addr== (0xffffff & ADDR_SDHC_BLOCK_COUNT))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->blk_count[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		str->blk_count[1] = temp2;
		uint8_t size=2;
		void *dest = &(internal_reg_view->blk_count);
		void *source = &(str->blk_count);
		memcpy(dest,source,size);
	}

	else if (addr== (0xffffff & ADDR_SDHC_ARG_1))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->argument1[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		str->argument1[1] = temp2;
		uint8_t temp3 = getSlice32(data_in_masked,23,16);
		str->argument1[2] = temp3;
		uint8_t temp4 = getSlice32(data_in_masked,31,24);
		str->argument1[3] = temp4;
		uint8_t size=4;
		void *dest = &(internal_reg_view->argument1);
		void *source = &(str->argument1);
		memcpy(dest,source,size);
	}

	else if(addr == (0xffffff & ADDR_SDHC_TRANSFER_MODE))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->tx_mode[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		str->tx_mode[1] = temp2;
		uint8_t size=2;
		void *dest = &(internal_reg_view->tx_mode);
		void *source = &(str->tx_mode);
		memcpy(dest,source,size);
	}
	else if(addr == (0xffffff & ADDR_SDHC_REGISTER_COMMAND))
	{
		//stores cmd_index value before anything is updated
		uint8_t cmd_index_init=getSlice16(internal_reg_view->command_reg,13,8);
		uint8_t temp1 = getSlice16(data_in_masked,7,0);
		str->command_reg[0] = temp1;
		uint8_t temp2 = getSlice16(data_in_masked,15,8);
		str->command_reg[1] = temp2;
		uint8_t size=2;		
		void *dest = &(internal_reg_view->command_reg);
		void *source = &(str->command_reg);
		memcpy(dest,source,size);
		//stores cmd_index value after register is updated
		uint8_t cmd_index_post=getSlice16(internal_reg_view->command_reg,13,8);
		//compares old cmd_index value i.e cmd_init with the updated one
		//if there is a change in the upper byte of this register, 
		//command is to be send to SD card, which happens by generateCommandForSDCard
		if(cmd_index_init!=cmd_index_post)
		{
			generateCommandForSDCard(internal_reg_view);
		}
	}
	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE0))
	{
		/* to be done during sd card modelling as write to 
		these regs are initiated from there */
	}
	
	else if (addr == (0xffffff & ADDR_SDHC_BUFFER_DATA_PORT))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->buffer_data_port[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		str->buffer_data_port[1] = temp2;
		uint8_t temp3 = getSlice32(data_in_masked,23,16);
		str->buffer_data_port[2] = temp3;
		uint8_t temp4 = getSlice32(data_in_masked,31,24);
		str->buffer_data_port[3] = temp4;
		uint8_t size=4;		
		void *dest = &(internal_reg_view->buffer_data_port);
		void *source = &(str->buffer_data_port);
		memcpy(dest,source,size);		
	}
	else if (addr == (0xffffff & ADDR_SDHC_PRESENT_STATE))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->present_state[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		str->present_state[1] = temp2;
		uint8_t temp3 = getSlice32(data_in_masked,23,16);
		str->present_state[2] = temp3;
		uint8_t temp4 = getSlice32(data_in_masked,31,24);
		str->present_state[3] = temp4;
		uint8_t size=4;		
		void *dest = &(internal_reg_view->present_state);
		void *source = &(str->present_state);
		memcpy(dest,source,size);			
	}
	else if (addr == (0xffffff & ADDR_SDHC_HOST_CONTROL_1))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->host_ctrl1 = temp1;
		uint8_t size=1;		
		void *dest = &(internal_reg_view->host_ctrl1);
		void *source = &(str->host_ctrl1);
		memcpy(dest,source,size);			
	}
	else if (addr == (0xffffff & ADDR_SDHC_POWER_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->pwr_ctrl = temp1;
		uint8_t size=1;		
		void *dest = &(internal_reg_view->pwr_ctrl);
		void *source = &(str->pwr_ctrl);
		memcpy(dest,source,size);			
	}	
	else if (addr == (0xffffff & ADDR_SDHC_BLOCK_GAP_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->blk_gap_ctrl = temp1;
		uint8_t size=1;		
		void *dest = &(internal_reg_view->blk_gap_ctrl);
		void *source = &(str->blk_gap_ctrl);
		memcpy(dest,source,size);			
	}
	else if (addr == (0xffffff & ADDR_SDHC_WAKEUP_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->wakeup_ctrl = temp1;
		uint8_t size=1;		
		void *dest = &(internal_reg_view->wakeup_ctrl);
		void *source = &(str->wakeup_ctrl);
		memcpy(dest,source,size);			
	}
	else if (addr == (0xffffff & ADDR_SDHC_CLOCK_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->clk_ctrl[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,7,0);
		str->clk_ctrl[1] = temp2;		
		uint8_t size=2;		
		void *dest = &(internal_reg_view->wakeup_ctrl);
		void *source = &(str->wakeup_ctrl);
		memcpy(dest,source,size);			
	}	
	else if (addr == (0xffffff & ADDR_SDHC_TIMEOUT_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->timeout_ctrl = temp1;
		uint8_t size=1;		
		void *dest = &(internal_reg_view->timeout_ctrl);
		void *source = &(str->timeout_ctrl);
		memcpy(dest,source,size);			
	}	
	else if (addr == (0xffffff & ADDR_SDHC_SOFTWARE_RESET))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->sw_reset = temp1;
		uint8_t size=1;		
		void *dest = &(internal_reg_view->sw_reset);
		void *source = &(str->sw_reset);
		memcpy(dest,source,size);			
	}	
	else if (addr == (0xffffff & ADDR_SDHC_NORMAL_INTR_STATUS))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->normal_intr_status[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		str->normal_intr_status[1] = temp2;
		uint8_t size=2;		
		void *dest = &(internal_reg_view->normal_intr_status);
		void *source = &(str->normal_intr_status);
		memcpy(dest,source,size);			
	}			
	else if (addr == (0xffffff & ADDR_SDHC_ERROR_INTR_STATUS))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->error_intr_status[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,7,0);
		str->error_intr_status[1] = temp2;
		uint8_t size=2;		
		void *dest = &(internal_reg_view->error_intr_status);
		void *source = &(str->error_intr_status);
		memcpy(dest,source,size);			
	}			
	else if (addr == (0xffffff & ADDR_SDHC_NORMAL_INTR_STATUS_EN))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->normal_intr_status_enable[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,7,0);
		str->normal_intr_status_enable[1] = temp2;
		uint8_t size=2;		
		void *dest = &(internal_reg_view->normal_intr_status_enable);
		void *source = &(str->normal_intr_status_enable);
		memcpy(dest,source,size);			
	}	
	//acknowledgement MUST be sent to CPU 
	//read requests will carry the data the read request was supposed to read
	//write requests will return the value 0 as acknowledgement
	sendPeripheralResponse("sdhc_to_peripheral_bridge_response", data_out);
}

