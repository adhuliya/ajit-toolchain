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

void generateCommandForSDCard(struct SDHCInternalMap *int_str)
{
//extracting command index value to be inserted in bits 40:45
	uint8_t cmd_index = getSlice16(int_str->command_reg,13,8);
	uint8_t crc7=7;//dummy value for now, will be updated with crc7 function's
							//return value later
	uint64_t frame_data=0;
	frame_data|=0UL<<47;//start bit
	frame_data|=1UL<<46;//tx bit
	frame_data|=cmd_index<<40;
	frame_data|=int_str->argument1<<8;
	frame_data|=crc7<<1;
	frame_data|=0UL<<0;
	write_uint64("sdhc_to_sdcard_request",frame_data);
}

void readSDHCRegister(uint32_t addr,
 struct CPUViewOfSDHCRegs *str, struct SDHCInternalMap *int_str)
{
	uint32_t data_out = 0;

	if (addr == (0xffffff & ADDR_SDHC_ARG_2))
	{
		uint8_t size=4;
		void *dest = &(str->argument2);//cpu side regs are destination here
		void *source = &(int_str->argument2);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->argument2;
	}
	else if (addr == (0xffffff & ADDR_SDHC_BLOCK_SIZE))
	{
		uint8_t size=2;
		void *dest = &(str->blk_size);//cpu side regs are destination here
		void *source = &(int_str->blk_size);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->blk_size;
	}
	else if (addr == (0xffffff & ADDR_SDHC_BLOCK_COUNT))
	{
		uint8_t size=2;
		void *dest = &(str->blk_count);//cpu side regs are destination here
		void *source = &(int_str->blk_count);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->blk_count;
	}
	else if (addr == (0xffffff & ADDR_SDHC_ARG_1))
	{
		uint8_t size=4;
		void *dest = &(str->argument1);//cpu side regs are destination here
		void *source = &(int_str->argument1);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->argument1;
	}
		else if (addr == (0xffffff & ADDR_SDHC_TRANSFER_MODE))
	{
		uint8_t size=2;
		void *dest = &(str->tx_mode);//cpu side regs are destination here
		void *source = &(int_str->tx_mode);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->tx_mode;
	}
		else if (addr == 0xffffff & ADDR_SDHC_REGISTER_COMMAND)
		{
		uint8_t size=4;
		void *dest = &(str->command_reg);//cpu side regs are destination here
		void *source = &(int_str->command_reg);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->command_reg;
	}
					/*	else if	((addr>=ADDR_SDHC_RESPONSE0)&&(addr<=ADDR_SDHC_RESPONSE7))
						{
					In progress
						}*/	
		else if (addr == (0xffffff && ADDR_SDHC_BUFFER_DATA_PORT))
	{
		uint8_t size=4;
		void *dest = &(str->buffer_data_port);//cpu side regs are destination here
		void *source = &(int_str->buffer_data_port);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->buffer_data_port;
	}
		else if (addr == (0xffffff & ADDR_SDHC_PRESENT_STATE))
		{
		uint8_t size=4;
		void *dest = &(str->present_state);//cpu side regs are destination here
		void *source = &(int_str->present_state);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->present_state;			
		}
		else if (addr == (0xffffff) & ADDR_SDHC_HOST_CONTROL_1)
		{
		uint8_t size=1;
		void *dest = &(str->host_ctrl1);//cpu side regs are destination here
		void *source = &(int_str->host_ctrl1);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->host_ctrl1;			
		}
		else if(addr == (0xffffff) & ADDR_SDHC_POWER_CONTROL)
		{
		uint8_t size=1;
		void *dest = &(str->pwr_ctrl);//cpu side regs are destination here
		void *source = &(int_str->pwr_ctrl);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->pwr_ctrl;						
		}
		else if (addr == (0xffffff) & ADDR_SDHC_BLOCK_GAP_CONTROL)
		{
		uint8_t size=1;
		void *dest = &(str->blk_gap_ctrl);//cpu side regs are destination here
		void *source = &(int_str->blk_gap_ctrl);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->blk_gap_ctrl;
		}
		else if (addr == (0xffffff) & ADDR_SDHC_WAKEUP_CONTROL)
		{
		uint8_t size=1;
		void *dest = &(str->wakeup_ctrl);//cpu side regs are destination here
		void *source = &(int_str->wakeup_ctrl);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->wakeup_ctrl;
		}
		else if (addr == (0xffffff) & ADDR_SDHC_CLOCK_CONTROL)
		{
		uint8_t size=2;
		void *dest = &(str->clk_ctrl);//cpu side regs are destination here
		void *source = &(int_str->clk_ctrl);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->clk_ctrl;
		}
		else if (addr == (0xffffff) & ADDR_SDHC_TIMEOUT_CONTROL)
		{
		uint8_t size=1;
		void *dest = &(str->timeout_ctrl);//cpu side regs are destination here
		void *source = &(int_str->timeout_ctrl);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->timeout_ctrl;
		}
		else if (addr == (0xffffff) & ADDR_SDHC_SOFTWARE_RESET)
		{
		uint8_t size=1;
		void *dest = &(str->sw_reset);//cpu side regs are destination here
		void *source = &(int_str->sw_reset);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->sw_reset;
		}		
		else if (addr == (0xffffff) & ADDR_SDHC_NORMAL_INTR_STATUS)
		{
		uint8_t size=2;
		void *dest = &(str->timeout_ctrl);//cpu side regs are destination here
		void *source = &(int_str->timeout_ctrl);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->timeout_ctrl;
		}
		else if (addr == (0xffffff) & ADDR_SDHC_ERROR_INTR_STATUS)
		{
		uint8_t size=2;
		void *dest = &(str->error_intr_status);//cpu side regs are destination here
		void *source = &(int_str->error_intr_status);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->error_intr_status;
		}	
		else if (addr == (0xffffff) & ADDR_SDHC_NORMAL_INTR_STATUS_EN)
		{
		uint8_t size=2;
		void *dest = &(str->normal_intr_status_enable);//cpu side regs are destination here
		void *source = &(int_str->normal_intr_status_enable);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->normal_intr_status_enable;
		}	
		else if (addr == (0xffffff) & ADDR_SDHC_ERROR_INTR_STATUS_EN)
		{
		uint8_t size=2;
		void *dest = &(str->error_intr_status_enable);//cpu side regs are destination here
		void *source = &(int_str->error_intr_status_enable);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->error_intr_status_enable;
		}
		else if (addr == (0xffffff) & ADDR_SDHC_NORMAL_INTR_SIGNAL_EN)
		{
		uint8_t size=2;
		void *dest = &(str->normal_intr_signal_enable);//cpu side regs are destination here
		void *source = &(int_str->normal_intr_signal_enable);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->normal_intr_signal_enable;
		}
		else if (addr == (0xffffff) & ADDR_SDHC_ERROR_INTR_SIGNAL_EN)
		{
		uint8_t size=2;
		void *dest = &(str->error_intr_signal_enable);//cpu side regs are destination here
		void *source = &(int_str->error_intr_signal_enable);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->error_intr_signal_enable;
		}		
		else if (addr == (0xffffff) & ADDR_SDHC_AUTO_CMD_ERROR_STATUS)
		{
		uint8_t size=2;
		void *dest = &(str->autoCMD_error_status);//cpu side regs are destination here
		void *source = &(int_str->autoCMD_error_status);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->autoCMD_error_status;
		}		
		else if (addr == (0xffffff) & ADDR_SDHC_HOST_CONTROL_2)
		{
		uint8_t size=2;
		void *dest = &(str->host_ctrl2);//cpu side regs are destination here
		void *source = &(int_str->host_ctrl2);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->host_ctrl2;
		}		
		else if (addr == (0xffffff) & ADDR_SDHC_CAPS)
		{
		uint8_t size=8;
		void *dest = &(str->capabilities);//cpu side regs are destination here
		void *source = &(int_str->capabilities);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->capabilities;
		}	
		else if (addr == (0xffffff) & ADDR_SDHC_MAX_CURRENT_CAPS)
		{
		uint8_t size=8;
		void *dest = &(str->max_current_cap);//cpu side regs are destination here
		void *source = &(int_str->max_current_cap);
		memcpy(dest,source,size);
		data_out = (uint32_t)str->max_current_cap;
		}	
	sendPeripheralResponse("sdhc_to_peripheral_bridge_response", data_out);
}

void updateRegister(uint32_t data_in, uint32_t addr, uint8_t byte_mask,
 struct CPUViewOfSDHCRegs *str, struct SDHCInternalMap *int_str)
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
		void *dest = &(int_str->argument2);//internal regs are destionation here
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
		void *dest = &(int_str->blk_size);
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
		void *dest = &(int_str->blk_count);
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
		void *dest = &(int_str->argument1);
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
		void *dest = &(int_str->tx_mode);
		void *source = &(str->tx_mode);
		memcpy(dest,source,size);
	}
	else if(addr == (0xffffff & ADDR_SDHC_REGISTER_COMMAND))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->command_reg[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		str->command_reg[1] = temp2;
		uint8_t temp3 = getSlice32(data_in_masked,23,16);
		str->command_reg[2] = temp3;
		uint8_t temp4 = getSlice32(data_in_masked,31,24);
		str->command_reg[3] = temp4;
		uint8_t size=4;		
		void *dest = &(int_str->command_reg);
		void *source = &(str->command_reg);
		memcpy(dest,source,size);
		generateCommandForSDCard(int_str);//as soon as the upper-byte of the command
		//register is written to, the SDHC is suppossed to send the command to card
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
		void *dest = &(int_str->buffer_data_port);
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
		void *dest = &(int_str->present_state);
		void *source = &(str->present_state);
		memcpy(dest,source,size);			
	}
	else if (addr == (0xffffff & ADDR_SDHC_HOST_CONTROL_1))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->host_ctrl1 = temp1;
		uint8_t size=1;		
		void *dest = &(int_str->host_ctrl1);
		void *source = &(str->host_ctrl1);
		memcpy(dest,source,size);			
	}
	else if (addr == (0xffffff & ADDR_SDHC_POWER_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->pwr_ctrl = temp1;
		uint8_t size=1;		
		void *dest = &(int_str->pwr_ctrl);
		void *source = &(str->pwr_ctrl);
		memcpy(dest,source,size);			
	}	
	else if (addr == (0xffffff & ADDR_SDHC_BLOCK_GAP_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->blk_gap_ctrl = temp1;
		uint8_t size=1;		
		void *dest = &(int_str->blk_gap_ctrl);
		void *source = &(str->blk_gap_ctrl);
		memcpy(dest,source,size);			
	}
	else if (addr == (0xffffff & ADDR_SDHC_WAKEUP_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->wakeup_ctrl = temp1;
		uint8_t size=1;		
		void *dest = &(int_str->wakeup_ctrl);
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
		void *dest = &(int_str->wakeup_ctrl);
		void *source = &(str->wakeup_ctrl);
		memcpy(dest,source,size);			
	}	
	else if (addr == (0xffffff & ADDR_SDHC_TIMEOUT_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->timeout_ctrl = temp1;
		uint8_t size=1;		
		void *dest = &(int_str->timeout_ctrl);
		void *source = &(str->timeout_ctrl);
		memcpy(dest,source,size);			
	}	
	else if (addr == (0xffffff & ADDR_SDHC_SOFTWARE_RESET))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->sw_reset = temp1;
		uint8_t size=1;		
		void *dest = &(int_str->sw_reset);
		void *source = &(str->sw_reset);
		memcpy(dest,source,size);			
	}	
	else if (addr == (0xffffff & ADDR_SDHC_NORMAL_INTR_STATUS))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		str->normal_intr_status[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,7,0);
		str->normal_intr_status[1] = temp2;
		uint8_t size=2;		
		void *dest = &(int_str->normal_intr_status);
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
		void *dest = &(int_str->error_intr_status);
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
		void *dest = &(int_str->normal_intr_status_enable);
		void *source = &(str->normal_intr_status_enable);
		memcpy(dest,source,size);			
	}	
	//acknowledgement MUST be sent to CPU 
	//read requests will carry the data the read request was supposed to read
	//write requests will return the value 0 as acknowledgement
	sendPeripheralResponse("sdhc_to_peripheral_bridge_response", data_out);
}

