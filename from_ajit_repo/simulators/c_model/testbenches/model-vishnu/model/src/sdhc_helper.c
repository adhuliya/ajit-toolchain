#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "Device_utils.h"
#include "Ancillary.h"
#include "Sdhc.h"
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"

#define READ	1
#define	WRITE	0
#define SDHC_IRL 11
uint8_t SDHC_INT_OUT;
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

        uint8_t offset = (uint8_t)(addr - ADDR_SDHC_ARG_2);
        
        if ( (addr == ADDR_SDHC_HOST_CONTROL_1)
                                || (addr == ADDR_SDHC_POWER_CONTROL)
                                || (addr == ADDR_SDHC_BLOCK_GAP_CONTROL)
                                || (addr == ADDR_SDHC_WAKEUP_CONTROL)
                                || (addr == ADDR_SDHC_TIMEOUT_CONTROL)
                                || (addr == ADDR_SDHC_SOFTWARE_RESET)
                                || (addr == ADDR_SDHC_ADMA_ERR_STAT))
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
        else if ( (addr == ADDR_SDHC_BLOCK_SIZE)
                        || (addr == ADDR_SDHC_BLOCK_COUNT)
                        || (addr == ADDR_SDHC_TRANSFER_MODE)
                        || (addr == ADDR_SDHC_REGISTER_COMMAND)
                        || (addr == ADDR_SDHC_CLOCK_CONTROL)
                        || (addr == ADDR_SDHC_NORMAL_INTR_STATUS)
                        || (addr == ADDR_SDHC_ERROR_INTR_STATUS)
                        || (addr == ADDR_SDHC_NORMAL_INTR_STATUS_EN)
                        || (addr == ADDR_SDHC_ERROR_INTR_STATUS_EN)
                        || (addr == ADDR_SDHC_NORMAL_INTR_SIGNAL_EN)
                        || (addr == ADDR_SDHC_ERROR_INTR_SIGNAL_EN)
                        || (addr == ADDR_SDHC_AUTO_CMD_ERROR_STATUS)
                        || (addr == ADDR_SDHC_HOST_CONTROL_2)
                        || (addr == ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT)
                        || (addr == ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT)
                        || (addr == ADDR_SDHC_SHARED_BUS_CTRL)
                        || (addr == ADDR_SDHC_SLOT_INTR_STATUS)
                        || (addr == ADDR_SDHC_HOST_CONTROLLER_VERSION))
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
#ifdef DEBUG
              fprintf(stderr,"lower byte of NISEn register is: 0x%x\r\n",cpu_view->normal_intr_status_enable[0]);
              fprintf(stderr,"upper byte of NISEn register is: 0x%x\r\n",cpu_view->normal_intr_status_enable[1]);
#endif 
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
        uint32_t ret_val =0;
        if (addr == ADDR_SDHC_NORMAL_INTR_STATUS_EN
                | addr == ADDR_SDHC_NORMAL_INTR_SIGNAL_EN
                | addr == ADDR_SDHC_ERROR_INTR_STATUS_EN
                | addr == ADDR_SDHC_ERROR_INTR_SIGNAL_EN)
        {
                ret_val = writeToSdhcReg(addr, byte_mask, cpu_view, data_in);
        }
        else if (addr == ADDR_SDHC_PRESENT_STATE)
        {
               ret_val=0;
        }
        
        return ret_val;
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

void setFlagsForReadWriteOperations(uint32_t addr, uint8_t rwbar, 
                                        sdhc_reg_cpu_view *cpu_reg_view, 
                                        sdhc_flags_for_events *sdhc_flags)
{
#ifdef DEBUG
        fprintf(stderr,"address in setFlags functions is 0x%x\r\n",addr);
#endif        
        switch (addr)
        {
        case ADDR_SDHC_NORMAL_INTR_STATUS_EN:
                sdhc_flags->NormalInterruptCardInsertedStatusEnabled = getBit8(cpu_reg_view->normal_intr_status_enable[0],6);
                sdhc_flags->NormalInterruptCardRemovalStatusEnabled = getBit8(cpu_reg_view->normal_intr_status_enable[0],7);                
                fprintf(stderr,"NI_StatusEnableCardInsertion flag set during write o/p is: 0x%x\r\n",sdhc_flags->NormalInterruptCardInsertedStatusEnabled);
                fprintf(stderr,"NI_StatusEnableCardRemoval flag set during write o/p is: 0x%x\r\n",sdhc_flags->NormalInterruptCardRemovalStatusEnabled);
        break;
        
        case ADDR_SDHC_NORMAL_INTR_SIGNAL_EN:
                sdhc_flags->NormalInterruptCardInsertedSignalEnabled = getBit8(cpu_reg_view->normal_intr_signal_enable[0],6);
                sdhc_flags->NormalInterruptCardRemovalSignalEnabled = getBit8(cpu_reg_view->normal_intr_signal_enable[0],7);
                fprintf(stderr,"NI_SignalEnableCardInserted flag set during write o/p is: 0x%x\r\n",sdhc_flags->NormalInterruptCardInsertedStatusEnabled);
                fprintf(stderr,"NI_SignalEnableCardRemoval flag set during write o/p is: 0x%x\r\n",sdhc_flags->NormalInterruptCardRemovalStatusEnabled);
        break;

        case ADDR_SDHC_PRESENT_STATE:
                sdhc_flags->PresentStateRegisterCardInsterted = getBit8(cpu_reg_view->present_state[2],0);
                fprintf(stderr,"PSR: flag set during write o/p is: 0x%x\r\n",sdhc_flags->PresentStateRegisterCardInsterted);        
        default:
                break;
        }
}

//if any bits in normal_intr_signal_en reg are set, they are 
//to be compared with the bits of normal_intr_stat reg and,
//if both are 1, interrupt has to be generated for that bit
void checkNormalInterrupts(struct sdhc_reg_cpu_view *cpu_reg_view,
                                sdhc_flags_for_events *sdhc_flags)
{	
        cpu_reg_view->normal_intr_status[0] = (cpu_reg_view->normal_intr_status_enable[0]) & 0xFF;//7:0
        cpu_reg_view->normal_intr_status[1] = (cpu_reg_view->normal_intr_status_enable[1]) & 0x1F;//upper byte's 5:0
        
        // To find which bit of the normal_interrrupt_status_enable register
	// has been set and reflect those in normal_interrupt_status register

	uint16_t intr_flag=0;
        //card insertion check
	if ( (cpu_reg_view->present_state[2]>>0) & 0x1 )
	{	
                sdhc_flags->NormalInterruptCardInsertedInterrupt=1;
		uint8_t norm_intr_stat_val = getBit8(cpu_reg_view->normal_intr_status[0],6);
		uint8_t norm_intr_sig_en_val = getBit8(cpu_reg_view->normal_intr_signal_enable[0],6);
		intr_flag = (norm_intr_sig_en_val & norm_intr_stat_val);
	}
        //card removal check
	else if ( ((cpu_reg_view->present_state[2]>>0) & 0x1) == 0)
	{
		sdhc_flags->NormalInterruptCardRemovalInterrupt=1;
		uint8_t norm_intr_stat_val = getBit8(cpu_reg_view->normal_intr_status[0],7);
		uint8_t norm_intr_sig_en_val = getBit8(cpu_reg_view->normal_intr_signal_enable[0],7);
		intr_flag = (norm_intr_sig_en_val & norm_intr_stat_val);
	}
	//checks for error interrupts
        else if ( (cpu_reg_view->normal_intr_status[1]>>7) & 0x1)
	{
		intr_flag=1; 
	}
	//	TODO: more checks for other interrupts sources to be added

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

