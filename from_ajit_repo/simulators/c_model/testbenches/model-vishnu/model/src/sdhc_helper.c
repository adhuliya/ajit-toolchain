#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "Device_utils.h"
#include "Ancillary.h"
#include "Sdhc.h"

#define READ	1
#define	WRITE	0

// #define DEBUG

uint32_t getAbsoluteAddress(uint32_t addr, uint8_t byte_mask)
{
        switch(byte_mask)
        {
        case 0b1111:
        case 0b1100:
        case 0b1000:
                break;
        case 0b0011:
                addr += sizeof(uint16_t);
                break;
        case 0b0100:
                addr += sizeof(uint8_t);
                break;
        case 0b0010:
                addr += (2*sizeof(uint8_t));
                break;
        case 0b0001:
                addr += (3*sizeof(uint8_t));
                break;
        default:
                break;
        }
        return addr;
}

uint32_t readOrWriteSdhcReg(uint32_t addr, uint8_t byte_mask, 
                                        sdhc_reg_cpu_view *cpu_view,
                                        uint32_t data_in, 
                                        uint8_t rwbar)
{
        uint32_t ret_val = 0;
        void *dest, *source;

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
                ret_val = (rwbar == WRITE) ? 0 : (uint32_t)temp;
        }
        else if ( (addr == (0xFFFFFF & ADDR_SDHC_BLOCK_SIZE))
                        || (addr == (0xFFFFFF & ADDR_SDHC_BLOCK_COUNT))
                        || (addr == (0xFFFFFF & ADDR_SDHC_TRANSFER_MODE))
                        || (addr == (0xFFFFFF & ADDR_SDHC_REGISTER_COMMAND))
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
                ret_val = (rwbar == WRITE) ? 0 : (uint32_t)temp;
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
                ret_val = (rwbar == WRITE) ? 0 : (uint32_t)temp;
        }
        return ret_val;
}

uint32_t writeToSdhcReg(uint32_t addr, 
                        uint8_t byte_mask, 
                        sdhc_reg_cpu_view *cpu_view, 
                        uint32_t data_in)
{
        return readOrWriteSdhcReg(addr, byte_mask, cpu_view, data_in, WRITE);
}
uint32_t checkAndWriteSdhcReg(uint32_t addr, 
                                uint8_t byte_mask, 
                                sdhc_reg_cpu_view *cpu_view, 
                                uint32_t data_in)
{
        return writeToSdhcReg(addr, byte_mask, cpu_view, data_in);
}


uint32_t readFromsdhcReg(uint32_t addr, 
                                uint8_t byte_mask,
                                sdhc_reg_cpu_view *cpu_view)
{
        return readOrWriteSdhcReg(addr, byte_mask, cpu_view, 0, READ);
}
uint32_t checkAndReadSdhcReg(uint32_t addr, 
                                uint8_t byte_mask,
                                sdhc_reg_cpu_view *cpu_view)
{
        uint32_t return_data = readFromsdhcReg(addr, byte_mask, cpu_view);
        
        switch(byte_mask)
        {
        case 0b1111:
        case 0b0011:
        case 0b0001:
                break;
        case 0b0010:
                return_data <<= 8;
                break;
        case 0b1100:
        case 0b0100:
                return_data <<= 16;
                break;
        case 0b1000:
                return_data <<= 24;
                break;
        default:
                break;
        }

#ifdef DEBUG
        printf("\nData returned after a READ: 0x%x\n", addr);
#endif

        return return_data;
}
