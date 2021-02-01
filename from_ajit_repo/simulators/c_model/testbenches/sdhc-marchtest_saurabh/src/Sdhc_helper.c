#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include "Ancillary.h"
#include "Ajit_Hardware_Configuration.h"
#include "Device_utils.h"
#include "RequestTypeValues.h"
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "Sdhc.h"

uint32_t readSdhcReg(uint32_t addr,
 			cpu_view *cpu_reg_view, internal_view *internal_reg_view)
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
	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE0))
	{
		void *dest = &cpu_reg_view->response0[0];
		void *source = &internal_reg_view->response0;
		memcpy(dest,source,sizeof(internal_reg_view->response0));
		data_out = (uint32_t)internal_reg_view->response0;
	}
	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE1))
	{
		void *dest = &cpu_reg_view->response1[0];
		void *source = &internal_reg_view->response1;
		memcpy(dest,source,sizeof(internal_reg_view->response1));
		data_out = (uint32_t)internal_reg_view->response1;
	}	
	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE2))
	{
		void *dest = &cpu_reg_view->response2[0];
		void *source = &internal_reg_view->response2;
		memcpy(dest,source,sizeof(internal_reg_view->response2));
		data_out = (uint32_t)internal_reg_view->response2;
	}	
	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE3))
	{
		void *dest = &cpu_reg_view->response3[0];
		void *source = &internal_reg_view->response3;
		memcpy(dest,source,sizeof(internal_reg_view->response3));
		data_out = (uint32_t)internal_reg_view->response3;
	}
	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE4))
	{
		void *dest = &cpu_reg_view->response4[0];
		void *source = &internal_reg_view->response4;
		memcpy(dest,source,sizeof(internal_reg_view->response4));
		data_out = (uint32_t)internal_reg_view->response4;
	}
	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE5))
	{
		void *dest = &cpu_reg_view->response5[0];
		void *source = &internal_reg_view->response5;
		memcpy(dest,source,sizeof(internal_reg_view->response5));
		data_out = (uint32_t)internal_reg_view->response5;
	}
		else if (addr == (0xffffff & ADDR_SDHC_RESPONSE6))
	{
		void *dest = &cpu_reg_view->response6[0];
		void *source = &internal_reg_view->response6;
		memcpy(dest,source,sizeof(internal_reg_view->response6));
		data_out = (uint32_t)internal_reg_view->response6;
	}
		else if (addr == (0xffffff & ADDR_SDHC_RESPONSE7))
	{
		void *dest = &cpu_reg_view->response7[0];
		void *source = &internal_reg_view->response7;
		memcpy(dest,source,sizeof(internal_reg_view->response7));
		data_out = (uint32_t)internal_reg_view->response7;
	}
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
	sendPeripheralResponse("sdhc_to_peripheral_bridge_response", data_out);

	return data_out;
}

uint32_t writeSdhcReg(uint32_t data_in, uint32_t addr, uint8_t byte_mask,
 			struct cpu_view *cpu_reg_view, struct internal_view *internal_reg_view)
{	
	uint32_t data_in_masked = data_in;
	uint32_t data_out=0;
	//fprintf(stderr,"inside writeSdhcReg func,data_in_masked is:0x%x\r\n",data_in_masked);
	if (addr== (0xffffff & ADDR_SDHC_ARG_2))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->argument2[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->argument2[1] = temp2;
		uint8_t temp3 = getSlice32(data_in_masked,23,16);
		cpu_reg_view->argument2[2] = temp3;
		uint8_t temp4 = getSlice32(data_in_masked,31,24);
		cpu_reg_view->argument2[3] = temp4;
		void *dest = &(internal_reg_view->argument2);//internal regs are destionation here
		void *source = &cpu_reg_view->argument2[0];
		memcpy(dest,source,sizeof(internal_reg_view->argument2));
	}

	else if (addr== (0xffffff & ADDR_SDHC_BLOCK_SIZE))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->blk_size[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->blk_size[1] = temp2;
		void *dest = &(internal_reg_view->blk_size);
		void *source = &cpu_reg_view->blk_size[0];
		memcpy(dest,source,sizeof(internal_reg_view->blk_size));
	}

	else if (addr== (0xffffff & ADDR_SDHC_BLOCK_COUNT))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->blk_count[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->blk_count[1] = temp2;
		void *dest = &(internal_reg_view->blk_count);
		void *source = &cpu_reg_view->blk_count[0];
		memcpy(dest,source,sizeof(internal_reg_view->blk_size));
	}

	else if (addr== (0xffffff & ADDR_SDHC_ARG_1))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->argument1[0] = temp1;
		//fprintf(stderr,"value inside cpu_view for arg1[0] is: %x\r\n",cpu_reg_view->argument1[0]);
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->argument1[1] = temp2;
		//fprintf(stderr,"value inside cpu_view for arg1[1] is: %x\r\n",cpu_reg_view->argument1[1]);
		uint8_t temp3 = getSlice32(data_in_masked,23,16);
		cpu_reg_view->argument1[2] = temp3;
		//fprintf(stderr,"value inside cpu_view for arg1[2] is: %x\r\n",cpu_reg_view->argument1[2]);		
		uint8_t temp4 = getSlice32(data_in_masked,31,24);
		cpu_reg_view->argument1[3] = temp4;
		//fprintf(stderr,"value inside cpu_view for arg1[3] is: %x\r\n",cpu_reg_view->argument1[3]);
		void *dest = &(internal_reg_view->argument1);
		void *source = &cpu_reg_view->argument1[0];
		memcpy(dest,source,sizeof(internal_reg_view->argument1));
		//fprintf(stderr,"value inside cpu_view for arg1 is: %x\r\n",cpu_reg_view->argument1);
		//fprintf(stderr,"value inside internal_view for arg1 is: %x\r\n",internal_reg_view->argument1);
	}

	else if(addr == (0xffffff & ADDR_SDHC_TRANSFER_MODE))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->tx_mode[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->tx_mode[1] = temp2;
		void *dest = &(internal_reg_view->tx_mode);
		void *source = &cpu_reg_view->tx_mode[0];
		memcpy(dest,source,sizeof(internal_reg_view));
	}

	else if(addr == (0xffffff & ADDR_SDHC_REGISTER_COMMAND))
	{	
		uint8_t temp1 = getSlice16(data_in_masked,7,0);
		cpu_reg_view->command_reg[0] = temp1;
		uint8_t temp2 = getSlice16(data_in_masked,15,8);
		cpu_reg_view->command_reg[1] = temp2;
		void *dest = &(internal_reg_view->command_reg);
		void *source = &cpu_reg_view->command_reg[0];
		memcpy(dest,source,sizeof(internal_reg_view->command_reg));
	}

	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE0))
	{
		uint8_t temp1 = getSlice16(data_in_masked,7,0);
		cpu_reg_view->response0[0] = temp1;
		uint8_t temp2 = getSlice16(data_in_masked,15,8);
		cpu_reg_view->response0[1] = temp2;
		void *dest = &(internal_reg_view->response0);
		void *source = &cpu_reg_view->response0[0];
		memcpy(dest,source,sizeof(internal_reg_view->response0));
	}

	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE1))
	{
		uint8_t temp1 = getSlice16(data_in_masked,7,0);
		cpu_reg_view->response1[0] = temp1;
		uint8_t temp2 = getSlice16(data_in_masked,15,8);
		cpu_reg_view->response1[1] = temp2;
		void *dest = &(internal_reg_view->response1);
		void *source = &cpu_reg_view->response1[0];
		memcpy(dest,source,sizeof(internal_reg_view->response1));
	}
	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE2))
	{
		uint8_t temp1 = getSlice16(data_in_masked,7,0);
		cpu_reg_view->response2[0] = temp1;
		uint8_t temp2 = getSlice16(data_in_masked,15,8);
		cpu_reg_view->response2[1] = temp2;
		void *dest = &(internal_reg_view->response2);
		void *source = &cpu_reg_view->response2[0];
		memcpy(dest,source,sizeof(internal_reg_view->response2));
	}
	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE3))
	{
		uint8_t temp1 = getSlice16(data_in_masked,7,0);
		cpu_reg_view->response3[0] = temp1;
		uint8_t temp2 = getSlice16(data_in_masked,15,8);
		cpu_reg_view->response3[1] = temp2;
		void *dest = &(internal_reg_view->response3);
		void *source = &cpu_reg_view->response3[0];
		memcpy(dest,source,sizeof(internal_reg_view->response3));
	}
	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE4))
	{
		uint8_t temp1 = getSlice16(data_in_masked,7,0);
		cpu_reg_view->response4[0] = temp1;
		uint8_t temp2 = getSlice16(data_in_masked,15,8);
		cpu_reg_view->response4[1] = temp2;
		void *dest = &(internal_reg_view->response4);
		void *source = &cpu_reg_view->response4[0];
		memcpy(dest,source,sizeof(internal_reg_view->response4));
	}
	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE5))
	{
		uint8_t temp1 = getSlice16(data_in_masked,7,0);
		cpu_reg_view->response5[0] = temp1;
		uint8_t temp2 = getSlice16(data_in_masked,15,8);
		cpu_reg_view->response5[1] = temp2;
		void *dest = &(internal_reg_view->response5);
		void *source = &cpu_reg_view->response5[0];
		memcpy(dest,source,sizeof(internal_reg_view->response5));
	}

	else if (addr == (0xffffff & ADDR_SDHC_RESPONSE6))
	{
		uint8_t temp1 = getSlice16(data_in_masked,7,0);
		cpu_reg_view->response6[0] = temp1;
		uint8_t temp2 = getSlice16(data_in_masked,15,8);
		cpu_reg_view->response6[1] = temp2;
		void *dest = &(internal_reg_view->response6);
		void *source = &cpu_reg_view->response6[0];
		memcpy(dest,source,sizeof(internal_reg_view->response6));
	}
		else if (addr == (0xffffff & ADDR_SDHC_RESPONSE7))
	{
		uint8_t temp1 = getSlice16(data_in_masked,7,0);
		cpu_reg_view->response7[0] = temp1;
		uint8_t temp2 = getSlice16(data_in_masked,15,8);
		cpu_reg_view->response7[1] = temp2;
		void *dest = &(internal_reg_view->response7);
		void *source = &cpu_reg_view->response7[0];
		memcpy(dest,source,sizeof(internal_reg_view->response7));
	}
	else if (addr == (0xffffff & ADDR_SDHC_BUFFER_DATA_PORT))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->buffer_data_port[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->buffer_data_port[1] = temp2;
		uint8_t temp3 = getSlice32(data_in_masked,23,16);
		cpu_reg_view->buffer_data_port[2] = temp3;
		uint8_t temp4 = getSlice32(data_in_masked,31,24);
		cpu_reg_view->buffer_data_port[3] = temp4;
		void *dest = &(internal_reg_view->buffer_data_port);
		void *source = &cpu_reg_view->buffer_data_port[0];
		memcpy(dest,source,sizeof(internal_reg_view->buffer_data_port));		
	}

	else if (addr == (0xffffff & ADDR_SDHC_PRESENT_STATE))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->present_state[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->present_state[1] = temp2;
		uint8_t temp3 = getSlice32(data_in_masked,23,16);
		cpu_reg_view->present_state[2] = temp3;
		uint8_t temp4 = getSlice32(data_in_masked,31,24);
		cpu_reg_view->present_state[3] = temp4;
		void *dest = &(internal_reg_view->present_state);
		void *source = &cpu_reg_view->present_state[0];
		memcpy(dest,source,sizeof(internal_reg_view->present_state));			
	}

	else if (addr == (0xffffff & ADDR_SDHC_HOST_CONTROL_1))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->host_ctrl1 = temp1;
		void *dest = &(internal_reg_view->host_ctrl1);
		void *source = &cpu_reg_view->host_ctrl1;
		memcpy(dest,source,sizeof(internal_reg_view->host_ctrl1));			
	}

	else if (addr == (0xffffff & ADDR_SDHC_POWER_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->pwr_ctrl = temp1;
		void *dest = &(internal_reg_view->pwr_ctrl);
		void *source = &cpu_reg_view->pwr_ctrl;
		memcpy(dest,source,sizeof(internal_reg_view->pwr_ctrl));			
	}	

	else if (addr == (0xffffff & ADDR_SDHC_BLOCK_GAP_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->blk_gap_ctrl = temp1;
		void *dest = &(internal_reg_view->blk_gap_ctrl);
		void *source = &cpu_reg_view->blk_gap_ctrl;
		memcpy(dest,source,sizeof(internal_reg_view->blk_gap_ctrl));			
	}

	else if (addr == (0xffffff & ADDR_SDHC_WAKEUP_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->wakeup_ctrl = temp1;
		void *dest = &(internal_reg_view->wakeup_ctrl);
		void *source = &cpu_reg_view->wakeup_ctrl;
		memcpy(dest,source,sizeof(internal_reg_view->wakeup_ctrl));			
	}

	else if (addr == (0xffffff & ADDR_SDHC_CLOCK_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->clk_ctrl[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->clk_ctrl[1] = temp2;		
		void *dest = &(internal_reg_view->clk_ctrl);
		void *source = &(cpu_reg_view->clk_ctrl[0]);
		memcpy(dest,source,sizeof(internal_reg_view->clk_ctrl));			
	}	

	else if (addr == (0xffffff & ADDR_SDHC_TIMEOUT_CONTROL))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->timeout_ctrl = temp1;
		void *dest = &(internal_reg_view->timeout_ctrl);
		void *source = &(cpu_reg_view->timeout_ctrl);
		memcpy(dest,source,sizeof(internal_reg_view->timeout_ctrl));			
	}	

	else if (addr == (0xffffff & ADDR_SDHC_SOFTWARE_RESET))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->sw_reset = temp1;
		void *dest = &(internal_reg_view->sw_reset);
		void *source = &cpu_reg_view->sw_reset;
		memcpy(dest,source,sizeof(internal_reg_view->sw_reset));			
	}	

	else if (addr == (0xffffff & ADDR_SDHC_NORMAL_INTR_STATUS))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->normal_intr_status[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->normal_intr_status[1] = temp2;
		void *dest = &(internal_reg_view->normal_intr_status);
		void *source = &cpu_reg_view->normal_intr_status[0];
		memcpy(dest,source,sizeof(internal_reg_view->normal_intr_status));			
	}		

	else if (addr == (0xffffff & ADDR_SDHC_ERROR_INTR_STATUS))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->error_intr_status[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->error_intr_status[1] = temp2;
		void *dest = &(internal_reg_view->error_intr_status);
		void *source = &cpu_reg_view->error_intr_status[0];
		memcpy(dest,source,sizeof(internal_reg_view->error_intr_status));			
	}		

	else if (addr == (0xffffff & ADDR_SDHC_NORMAL_INTR_STATUS_EN))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->normal_intr_status_enable[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->normal_intr_status_enable[1] = temp2;
		void *dest = &(internal_reg_view->normal_intr_status_enable);
		void *source = &cpu_reg_view->normal_intr_status_enable[0];
		memcpy(dest,source,sizeof(internal_reg_view->normal_intr_status_enable));			
	}	

	else if (addr == (0xffffff & ADDR_SDHC_ERROR_INTR_STATUS_EN))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->error_intr_status_enable[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->error_intr_status_enable[1] = temp2;
		void *dest = &(internal_reg_view->error_intr_status_enable);
		void *source = &cpu_reg_view->error_intr_status_enable[0];
		memcpy(dest,source,sizeof(internal_reg_view->error_intr_status_enable));			
	}

	else if (addr == (0xffffff & ADDR_SDHC_NORMAL_INTR_SIGNAL_EN))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->normal_intr_signal_enable[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->normal_intr_signal_enable[1] = temp2;
		void *dest = &(internal_reg_view->normal_intr_signal_enable);
		void *source = &cpu_reg_view->normal_intr_signal_enable[0];
		memcpy(dest,source,sizeof(internal_reg_view->normal_intr_signal_enable));		
	}

	else if (addr == (0xffffff & ADDR_SDHC_ERROR_INTR_SIGNAL_EN))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->error_intr_signal_enable[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->error_intr_signal_enable[1] = temp2;
		void *dest = &(internal_reg_view->error_intr_signal_enable);
		void *source = &cpu_reg_view->error_intr_signal_enable[0];
		memcpy(dest,source,sizeof(internal_reg_view->error_intr_signal_enable));	
	}		

	else if (addr == (0xffffff & ADDR_SDHC_AUTO_CMD_ERROR_STATUS))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->autoCMD_error_status[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->autoCMD_error_status[1] = temp2;
		void *dest = &(internal_reg_view->autoCMD_error_status);
		void *source = &cpu_reg_view->autoCMD_error_status[0];
		memcpy(dest,source,sizeof(internal_reg_view->autoCMD_error_status));	
	}

	else if (addr == (0xffffff & ADDR_SDHC_HOST_CONTROL_2))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->host_ctrl2[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->host_ctrl2[1] = temp2;
		void *dest = &(internal_reg_view->host_ctrl2);
		void *source = &cpu_reg_view->host_ctrl2[0];
		memcpy(dest,source,sizeof(internal_reg_view->host_ctrl2));	
	}

	else if(addr == (0xffffff & ADDR_SDHC_CAPS))
	{
		uint8_t temp1 = getSlice32(data_in_masked,7,0);
		cpu_reg_view->capabilities[0] = temp1;
		uint8_t temp2 = getSlice32(data_in_masked,15,8);
		cpu_reg_view->capabilities[1] = temp2;
		uint8_t temp3 = getSlice32(data_in_masked,23,16);
		cpu_reg_view->capabilities[2] = temp3;
		uint8_t temp4 = getSlice32(data_in_masked,31,24);
		cpu_reg_view->capabilities[3] = temp4;
		void *dest = &(internal_reg_view->capabilities);
		void *source = &cpu_reg_view->capabilities[0];
		memcpy(dest,source,sizeof(internal_reg_view->capabilities));
	}
	
	//acknowledgement MUST be sent to CPU 
	//read requests will carry the data the read request was supposed to read
	//write requests will return the value 0 as acknowledgement
	sendPeripheralResponse("sdhc_to_peripheral_bridge_response", data_out);
}

