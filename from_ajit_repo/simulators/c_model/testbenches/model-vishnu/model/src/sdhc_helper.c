#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "Device_utils.h"
#include "Ancillary.h"
#include "Sdhc.h"

#define READ	1
#define	WRITE	0

#define INTERNAL_TO_CPU 0
#define CPU_TO_INTERNAL 1

// #define DEBUG

uint32_t changeAddress(uint32_t addr, uint8_t byte_mask)
{
        switch(byte_mask)
        {
        case 0xf:
        case 0xc:
        case 0x8:
                break;
        case 0x3:
                addr += sizeof(uint16_t);
                break;
        case 0x4:
                addr += sizeof(uint8_t);
                break;
        case 0x2:
                addr += (2*sizeof(uint8_t));
                break;
        case 0x1:
                addr += (3*sizeof(uint8_t));
                break;
        default:
                break;
        }
        return addr;
}


void syncBothStructs(sdhc_reg_cpu_view *cpu_view, 
                                sdhc_reg_internal_view *internal_view, 
                                uint8_t direction)
{
        void *source =  NULL, *dest = NULL;

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->argument2, dest = &cpu_view->argument2[0]) 
                                                : (source = &cpu_view->argument2[0], dest = &internal_view->argument2);
        memcpy(dest, source, sizeof(uint32_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->blk_size, dest = &cpu_view->blk_size[0]) 
                                                : (source = &cpu_view->blk_size[0], dest = &internal_view->blk_size);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->blk_count, dest = &cpu_view->blk_count[0]) 
                                                : (source = &cpu_view->blk_count[0], dest = &internal_view->blk_count);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->argument1, dest = &cpu_view->argument1[0]) 
                                                : (source = &cpu_view->argument1[0], dest = &internal_view->argument1);
        memcpy(dest, source, sizeof(uint32_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->tx_mode, dest = &cpu_view->tx_mode[0]) 
                                                : (source = &cpu_view->tx_mode[0], dest = &internal_view->tx_mode);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->command_reg, dest = &cpu_view->command_reg[0]) 
                                                : (source = &cpu_view->command_reg[0], dest = &internal_view->command_reg);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->response0, dest = &cpu_view->response0[0]) 
                                                : (source = &cpu_view->response0[0], dest = &internal_view->response0);
        memcpy(dest, source, sizeof(uint16_t));
        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->response1, dest = &cpu_view->response1[0]) 
                                                : (source = &cpu_view->response1[0], dest = &internal_view->response1);
        memcpy(dest, source, sizeof(uint16_t));
        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->response2, dest = &cpu_view->response2[0]) 
                                                : (source = &cpu_view->response2[0], dest = &internal_view->response2);
        memcpy(dest, source, sizeof(uint16_t));
        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->response3, dest = &cpu_view->response3[0]) 
                                                : (source = &cpu_view->response3[0], dest = &internal_view->response3);
        memcpy(dest, source, sizeof(uint16_t));
        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->response4, dest = &cpu_view->response4[0]) 
                                                : (source = &cpu_view->response4[0], dest = &internal_view->response4);
        memcpy(dest, source, sizeof(uint16_t));
        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->response5, dest = &cpu_view->response5[0]) 
                                                : (source = &cpu_view->response5[0], dest = &internal_view->response5);
        memcpy(dest, source, sizeof(uint16_t));
        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->response6, dest = &cpu_view->response6[0]) 
                                                : (source = &cpu_view->response6[0], dest = &internal_view->response6);
        memcpy(dest, source, sizeof(uint16_t));
        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->response7, dest = &cpu_view->response7[0]) 
                                                : (source = &cpu_view->response7[0], dest = &internal_view->response7);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->buffer_data_port, dest = &cpu_view->buffer_data_port[0]) 
                                                : (source = &cpu_view->buffer_data_port[0], dest = &internal_view->buffer_data_port);
        memcpy(dest, source, sizeof(uint32_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->present_state, dest = &cpu_view->present_state[0]) 
                                                : (source = &cpu_view->present_state[0], dest = &internal_view->present_state);
        memcpy(dest, source, sizeof(uint32_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->host_ctrl1, dest = &cpu_view->host_ctrl1) 
                                                : (source = &cpu_view->host_ctrl1, dest = &internal_view->host_ctrl1);
        memcpy(dest, source, sizeof(uint8_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->pwr_ctrl, dest = &cpu_view->pwr_ctrl) 
                                                : (source = &cpu_view->pwr_ctrl, dest = &internal_view->pwr_ctrl);
        memcpy(dest, source, sizeof(uint8_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->blk_gap_ctrl, dest = &cpu_view->blk_gap_ctrl) 
                                                : (source = &cpu_view->blk_gap_ctrl, dest = &internal_view->blk_gap_ctrl);
        memcpy(dest, source, sizeof(uint8_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->wakeup_ctrl, dest = &cpu_view->wakeup_ctrl) 
                                                : (source = &cpu_view->wakeup_ctrl, dest = &internal_view->wakeup_ctrl);
        memcpy(dest, source, sizeof(uint8_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->clk_ctrl, dest = &cpu_view->clk_ctrl[0]) 
                                                : (source = &cpu_view->clk_ctrl[0], dest = &internal_view->clk_ctrl);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->timeout_ctrl, dest = &cpu_view->timeout_ctrl) 
                                                : (source = &cpu_view->timeout_ctrl, dest = &internal_view->timeout_ctrl);
        memcpy(dest, source, sizeof(uint8_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->sw_reset, dest = &cpu_view->sw_reset) 
                                                : (source = &cpu_view->sw_reset, dest = &internal_view->sw_reset);
        memcpy(dest, source, sizeof(uint8_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->normal_intr_status, dest = &cpu_view->normal_intr_status[0]) 
                                                : (source = &cpu_view->normal_intr_status[0], dest = &internal_view->normal_intr_status);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->error_intr_status, dest = &cpu_view->error_intr_status[0]) 
                                                : (source = &cpu_view->error_intr_status[0], dest = &internal_view->error_intr_status);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->normal_intr_status_enable, dest = &cpu_view->normal_intr_status_enable[0]) 
                                                : (source = &cpu_view->normal_intr_status_enable[0], dest = &internal_view->normal_intr_status_enable);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->error_intr_status_enable, dest = &cpu_view->error_intr_status_enable[0]) 
                                                : (source = &cpu_view->error_intr_status_enable[0], dest = &internal_view->error_intr_status_enable);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->normal_intr_signal_enable, dest = &cpu_view->normal_intr_signal_enable[0]) 
                                                : (source = &cpu_view->normal_intr_signal_enable[0], dest = &internal_view->normal_intr_signal_enable);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->error_intr_signal_enable, dest = &cpu_view->error_intr_signal_enable[0]) 
                                                : (source = &cpu_view->error_intr_signal_enable[0], dest = &internal_view->error_intr_signal_enable);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->autoCMD_error_status, dest = &cpu_view->autoCMD_error_status[0]) 
                                                : (source = &cpu_view->autoCMD_error_status[0], dest = &internal_view->autoCMD_error_status);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->host_ctrl2, dest = &cpu_view->host_ctrl2[0]) 
                                                : (source = &cpu_view->host_ctrl2[0], dest = &internal_view->host_ctrl2);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->capabilities, dest = &cpu_view->capabilities[0]) 
                                                : (source = &cpu_view->capabilities[0], dest = &internal_view->capabilities);
        memcpy(dest, source, sizeof(uint64_t));
        
        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->max_current_cap, dest = &cpu_view->max_current_cap[0]) 
                                                : (source = &cpu_view->max_current_cap[0], dest = &internal_view->max_current_cap);
        memcpy(dest, source, sizeof(uint32_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->res_max_current_cap, dest = &cpu_view->res_max_current_cap[0]) 
                                                : (source = &cpu_view->res_max_current_cap[0], dest = &internal_view->res_max_current_cap);
        memcpy(dest, source, sizeof(uint32_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->force_event_autoCMD_err_stat, dest = &cpu_view->force_event_autoCMD_err_stat[0]) 
                                                : (source = &cpu_view->force_event_autoCMD_err_stat[0], dest = &internal_view->force_event_autoCMD_err_stat);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->force_event_autoCMD_err_interrupt_stat, dest = &cpu_view->force_event_autoCMD_err_interrupt_stat[0]) 
                                                : (source = &cpu_view->force_event_autoCMD_err_interrupt_stat[0], dest = &internal_view->force_event_autoCMD_err_interrupt_stat);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->ADMA_err_status, dest = &cpu_view->ADMA_err_status) 
                                                : (source = &cpu_view->ADMA_err_status, dest = &internal_view->ADMA_err_status);
        memcpy(dest, source, sizeof(uint8_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->ADMA_system_address, dest = &cpu_view->ADMA_system_address[0]) 
                                                : (source = &cpu_view->ADMA_system_address[0], dest = &internal_view->ADMA_system_address);
        memcpy(dest, source, sizeof(uint64_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->preset_value, dest = &cpu_view->preset_value[0]) 
                                                : (source = &cpu_view->preset_value[0], dest = &internal_view->preset_value);
        memcpy(dest, source, sizeof(__uint128_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->shared_bus_control, dest = &cpu_view->shared_bus_control[0]) 
                                                : (source = &cpu_view->shared_bus_control[0], dest = &internal_view->shared_bus_control);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->slot_interrupt_status, dest = &cpu_view->slot_interrupt_status[0]) 
                                                : (source = &cpu_view->slot_interrupt_status[0], dest = &internal_view->slot_interrupt_status);
        memcpy(dest, source, sizeof(uint16_t));

        (direction == INTERNAL_TO_CPU) ?  (source = &internal_view->host_controller_version, dest = &cpu_view->host_controller_version[0]) 
                                                : (source = &cpu_view->host_controller_version[0], dest = &internal_view->host_controller_version);
        memcpy(dest, source, sizeof(uint16_t));

}

uint32_t readOrWriteSdhcReg(uint32_t addr, uint8_t byte_mask, 
                                        sdhc_reg_cpu_view *cpu_view, 
                                        sdhc_reg_internal_view *internal_view,
                                        uint32_t data_in, 
                                        uint8_t rwbar)
{
        uint32_t ret_val = 0;
        void *dest, *source;

#ifdef DEBUG
                printf("Data in masked for %x = %x\n", addr, data_in_masked);
#endif
        uint8_t offset = (uint8_t)(addr - (0xFFFFFF & ADDR_SDHC_ARG_2));
        
        if ( addr == (0xFFFFFF & ADDR_SDHC_HOST_CONTROL_1)
                                || (addr == (0xFFFFFF & ADDR_SDHC_POWER_CONTROL))
                                || (addr == (0xFFFFFF & ADDR_SDHC_BLOCK_GAP_CONTROL))
                                || (addr == (0xFFFFFF & ADDR_SDHC_WAKEUP_CONTROL))
                                || (addr == (0xFFFFFF & ADDR_SDHC_TIMEOUT_CONTROL))
                                || (addr == (0xFFFFFF & ADDR_SDHC_SOFTWARE_RESET))
                                || (addr == (0xFFFFFF & ADDR_SDHC_ADMA_ERR_STAT)))
        {
                uint8_t temp = 0;
                if (!rwbar) // write
                {
                        if(byte_mask & 0x8)
			{
				temp  = getSlice32(data_in, 31, 24);
			}
			else if (byte_mask & 0x4)
			{
				temp  = getSlice32(data_in, 23, 16); 
			}
			else if (byte_mask & 0x2)
			{
				temp  = getSlice32(data_in, 15,8);
			}
			else if(byte_mask & 0x1)
			{
				temp  = getSlice32(data_in, 7,0);
			}
                        dest = &cpu_view->argument2[0] + offset;
                        source = &temp;
                }
                else if (rwbar) // read
                {
                        dest = &temp;
                        source = &cpu_view->argument2[0] + offset;
                }
                memcpy(dest, source, sizeof(uint8_t));
                ret_val = (rwbar == 0) ? 0 : (uint32_t)temp;
        }
        else if ( (addr == (0xFFFFFF & ADDR_SDHC_BLOCK_SIZE))
                        || (addr == (0xFFFFFF & ADDR_SDHC_BLOCK_COUNT))
                        || (addr == (0xFFFFFF & ADDR_SDHC_TRANSFER_MODE))
                        || (addr == (0xFFFFFF & ADDR_SDHC_REGISTER_COMMAND))
                        || (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE0))
                        || (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE1))
                        || (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE2))
                        || (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE3))
                        || (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE4))
                        || (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE5))
                        || (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE6))
                        || (addr == (0xFFFFFF & ADDR_SDHC_RESPONSE7))
                        || (addr == (0xFFFFFF & ADDR_SDHC_CLOCK_CONTROL))
                        || (addr == (0xFFFFFF & ADDR_SDHC_NORMAL_INTR_STATUS))
                        || (addr == (0xFFFFFF & ADDR_SDHC_ERROR_INTR_STATUS))
                        || (addr == (0xFFFFFF & ADDR_SDHC_NORMAL_INTR_STATUS_EN))
                        || (addr == (0xFFFFFF & ADDR_SDHC_ERROR_INTR_STATUS_EN))
                        || (addr == (0xFFFFFF & ADDR_SDHC_NORMAL_INTR_SIGNAL_EN))
                        || (addr == (0xFFFFFF & ADDR_SDHC_ERROR_INTR_SIGNAL_EN))
                        || (addr == (0xFFFFFF & ADDR_SDHC_AUTO_CMD_ERROR_STATUS))
                        || (addr == (0xFFFFFF & ADDR_SDHC_HOST_CONTROL_2))
                        || (addr == (0xFFFFFF & ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT))
                        || (addr == (0xFFFFFF & ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT))
                        || (addr == (0xFFFFFF & ADDR_SDHC_SHARED_BUS_CTRL))
                        || (addr == (0xFFFFFF & ADDR_SDHC_SLOT_INTR_STATUS))
                        || (addr == (0xFFFFFF & ADDR_SDHC_HOST_CONTROLLER_VERSION)))
        {
                uint16_t temp = 0;
                if (!rwbar) // write
                {
                        if(byte_mask & 0xc)
			{
				temp  = getSlice32(data_in, 31, 16);
			}
			else if (byte_mask & 0x3)
			{
				temp  = getSlice32(data_in, 15, 0); 
			}
                        dest = &cpu_view->argument2[0] + offset;
                        source = &temp;
                }
                else if(rwbar) // read
                {
                        dest = &temp;
                        source = &cpu_view->argument2[0] + offset;
                }
                memcpy(dest, source, sizeof(uint16_t));
                ret_val = (rwbar == 0) ? 0 : (uint32_t)temp;
        }
        else
        {
                uint32_t temp = 0;
                if(!rwbar) // write
                {
                        uint32_t temp = data_in;
                        dest = &cpu_view->argument2[0] + offset;
                        source = &temp;
                }
                if(rwbar) // read
                {
                        dest = &temp;
                        source = &cpu_view->argument2[0] + offset;
                }
                memcpy(dest, source, sizeof(uint32_t));
                ret_val = (rwbar == 0) ? 0 : (uint32_t)temp;
        }
        return ret_val;
}


void writeToSdhcReg(uint32_t addr, 
                        uint8_t byte_mask, 
                        sdhc_reg_cpu_view *cpu_view, 
                        sdhc_reg_internal_view *internal_view, 
                        uint32_t data_in)
{
        readOrWriteSdhcReg(addr, byte_mask, cpu_view, internal_view, data_in, WRITE);
}

uint32_t checkAndReadSdhcReg(uint32_t addr, 
                                sdhc_reg_cpu_view *cpu_view, 
                                sdhc_reg_internal_view *internal_view)
{
        syncBothStructs(cpu_view, internal_view, INTERNAL_TO_CPU);
        readFromsdhcReg(addr, cpu_view, internal_view);
}

uint32_t readFromsdhcReg(uint32_t addr, 
                                sdhc_reg_cpu_view *cpu_view, 
                                sdhc_reg_internal_view *internal_view)
{
        // printf("\nData read from register in model: 0x%x\n", addr);
        return readOrWriteSdhcReg(addr, 0, cpu_view, internal_view, 0, READ);
}

void checkAndWriteSdhcReg(uint32_t addr, 
                                uint8_t byte_mask, 
                                sdhc_reg_cpu_view *cpu_view,
                                sdhc_reg_internal_view *internal_view, 
                                uint32_t data_in)
{
        writeToSdhcReg(addr, byte_mask, cpu_view, internal_view, data_in);
        syncBothStructs(cpu_view, internal_view, CPU_TO_INTERNAL);
}

