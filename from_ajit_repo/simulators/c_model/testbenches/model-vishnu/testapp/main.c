#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "Pipes.h"
#include "pipeHandler.h"
#include "Ancillary.h"
#include "Sdhc.h"

#define READ 1
#define WRITE 0

uint32_t appSendCmdAndReceiveResponse(uint32_t addr, uint8_t byte_mask, uint8_t rwbar, uint32_t data)
{
        uint64_t send_cmd = 0;

        send_cmd = rwbar;
        send_cmd = (send_cmd << 4) | byte_mask;
        send_cmd = (send_cmd << 27) | (addr & 0xffffff);
        send_cmd = (send_cmd << 32) | data;

        write_uint64("peripheral_bridge_to_sdhc_request", send_cmd);
        // printf("Command send from app = 0x%lx with addr = 0x%x, byte mask = 0x%x, rwbar = %d, data = 0x%x\n", send_cmd, addr, byte_mask, rwbar, data);
        return read_uint32("sdhc_to_peripheral_bridge_response");
}

uint32_t readOrWriteSdhcByte(uint32_t sdhc_reg_addr, uint32_t wdata, uint8_t rwbar)
{
        uint32_t ret_val = 0;

        switch(sdhc_reg_addr%4)
        {
        case 0:
                ret_val = appSendCmdAndReceiveResponse(sdhc_reg_addr, 0b1000, rwbar, ((wdata << 24) & 0xff000000));
                break;
        case 1:
                ret_val = appSendCmdAndReceiveResponse((sdhc_reg_addr & 0xfffffc), 0b0100, rwbar, ((wdata << 16) & 0xff0000));
                break;
        case 2:
                ret_val = appSendCmdAndReceiveResponse((sdhc_reg_addr & 0xfffffc), 0b0010, rwbar, ((wdata << 8) & 0xff00));
                break;
        case 3:
                ret_val = appSendCmdAndReceiveResponse((sdhc_reg_addr & 0xfffffc), 0b0001, rwbar, (wdata & 0xff));
                break;
        default:
                //error
                printf("\nInvalid 8b reg address at 0x%x\n", sdhc_reg_addr);
                break;
        }
        return ret_val;
}
uint32_t readOrWriteSdhcHalfWord (uint32_t sdhc_reg_addr, uint32_t wdata, uint8_t rwbar)
{
        uint32_t ret_val = 0;
        switch (sdhc_reg_addr%4)
        {
        case 0:
                ret_val = appSendCmdAndReceiveResponse(sdhc_reg_addr, 0b1100, rwbar, ((wdata << 16) & 0xffff0000));
                break;
        case 2:
                ret_val = appSendCmdAndReceiveResponse(sdhc_reg_addr & 0xfffffffc, 0b0011, rwbar, (wdata & 0xffff));
                break;
        default:
                printf("\nInvalid 16b reg address at 0x%x\n", sdhc_reg_addr);
                break;
        }
        return ret_val;
}
uint32_t readOrWriteSdhcWord (uint32_t sdhc_reg_addr, uint32_t wdata, uint8_t rwbar)
{
        uint32_t ret_val = 0;
        ret_val = appSendCmdAndReceiveResponse(sdhc_reg_addr, 0b1111, rwbar, wdata);      
        return ret_val;
}

uint32_t appReadOrWriteSdhcReg(uint32_t byte_address_of_reg,
		        size_t size_of_reg, uint32_t wdata, uint8_t rwbar)
{
        uint32_t ret_val = 0;
	switch(size_of_reg)
        {
        case 1:
                ret_val = readOrWriteSdhcByte(byte_address_of_reg, wdata, rwbar);
                break;
        case 2:
                if((byte_address_of_reg & 0b1) == 0) // check if the last bit is 0; even number, ie, a multiple of 2
                        ret_val = readOrWriteSdhcHalfWord (byte_address_of_reg, wdata, rwbar);
                else // when address is odd
                        printf("\nInvalid address 0x%x\n", byte_address_of_reg); // since all 16b registers are at multiples of 2
                break;
        case 4:
                if((byte_address_of_reg & 0b11) == 0) // check if last 2 bits are 0; multiple of 4
                        ret_val = readOrWriteSdhcWord (byte_address_of_reg, wdata, rwbar);
                else if((byte_address_of_reg & 0x1) == 0) // check if the last bit is 0; even number, ie, a multiple of 2;
                        printf("\nInvalid address 0x%x\n", byte_address_of_reg); // since all 32b regs are at multiples of 4
                else // when address is odd;
                        printf("\nInvalid address 0x%x\n", byte_address_of_reg); // since all 32b regs are at multiples of 4
                break;
        case 8: // corresponds to 64 bit access; doesn't occur

        default:
                printf("\nInvalid address 0x%x\n", byte_address_of_reg);// error.
        break;
	}

        return ret_val;
}

uint32_t appReadFromSdhcReg(uint32_t byte_address_of_reg, size_t size_of_reg)
{
        return appReadOrWriteSdhcReg(byte_address_of_reg, size_of_reg, 0, READ);
}
uint32_t appWriteToSdhcReg(uint32_t byte_address_of_reg, size_t size_of_reg, uint32_t wdata)
{
        return appReadOrWriteSdhcReg(byte_address_of_reg, size_of_reg, wdata, WRITE);
}

void readAllSdhcReg()
{
        printf(" reg value arg2 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ARG_2, sizeof(uint32_t)));
        printf(" reg value blk size = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_BLOCK_SIZE, sizeof(uint16_t)));
        printf(" reg value blk count = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_BLOCK_COUNT, sizeof(uint16_t)));
        printf(" reg value arg1 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ARG_1, sizeof(uint32_t)));
        printf(" reg value tx mode = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_TRANSFER_MODE, sizeof(uint16_t)));
        printf(" reg value register command = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_REGISTER_COMMAND, sizeof(uint16_t)));
        printf(" reg value response 0 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE0, sizeof(uint16_t)));
        printf(" reg value response 1 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE1, sizeof(uint16_t)));
        printf(" reg value response 2 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE2, sizeof(uint16_t)));
        printf(" reg value response 3 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE3, sizeof(uint16_t)));
        printf(" reg value response 4 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE4, sizeof(uint16_t)));
        printf(" reg value response 5 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE5, sizeof(uint16_t)));
        printf(" reg value response 6 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE6, sizeof(uint16_t)));
        printf(" reg value response 7 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE7, sizeof(uint16_t)));
        printf(" reg value buffr data port = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_BUFFER_DATA_PORT, sizeof(uint32_t)));
        printf(" reg value present state = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_PRESENT_STATE, sizeof(uint32_t)));
        printf(" reg value host ctrl 1 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_HOST_CONTROL_1, sizeof(uint8_t)));
        printf(" reg value power ctrl = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_POWER_CONTROL, sizeof(uint8_t)));
        printf(" reg value blk gap ctrl = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_BLOCK_GAP_CONTROL, sizeof(uint8_t)));
        printf(" reg value wakeup trl = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_WAKEUP_CONTROL, sizeof(uint8_t)));
        printf(" reg value clk ctrl = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_CLOCK_CONTROL, sizeof(uint8_t)));
        printf(" reg value timeout ctrl = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_TIMEOUT_CONTROL, sizeof(uint8_t)));
        printf(" reg value software reset = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_SOFTWARE_RESET, sizeof(uint8_t)));
        printf(" reg value nrml intr status = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_NORMAL_INTR_STATUS, sizeof(uint16_t)));
        printf(" reg value error_intr_status = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ERROR_INTR_STATUS, sizeof(uint16_t)));
        printf(" reg value normal_intr_status_enable = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_NORMAL_INTR_STATUS_EN, sizeof(uint16_t)));
        printf(" reg value error_intr_status_enable = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ERROR_INTR_STATUS_EN, sizeof(uint16_t)));
        printf(" reg value normal_intr_signal_enable = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_NORMAL_INTR_SIGNAL_EN, sizeof(uint16_t)));
        printf(" reg value error_intr_signal_enable = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ERROR_INTR_SIGNAL_EN, sizeof(uint16_t)));
        printf(" reg value autoCMD_error_status = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_AUTO_CMD_ERROR_STATUS, sizeof(uint16_t)));
        printf(" reg value host_ctrl2 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_HOST_CONTROL_2, sizeof(uint16_t)));
        printf(" reg value capabilities = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_CAPS, sizeof(uint32_t)));
        printf(" reg value max_current_cap = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_MAX_CURRENT_CAPS, sizeof(uint32_t)));
        printf(" reg value res_max_current_cap = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_MAX_CURRENT_CAPS_RES, sizeof(uint32_t)));
        printf(" reg value force_event_autoCMD_err_stat = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT, sizeof(uint16_t)));
        printf(" reg value force_event_autoCMD_err_interrupt_stat = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT, sizeof(uint16_t)));
        printf(" reg value ADMA_err_status = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ADMA_ERR_STAT, sizeof(uint8_t)));
        printf(" reg value ADMA_system_address = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ADMA_SYSTEM_ADDR, sizeof(uint32_t)));
        printf(" reg value preset_value = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_HOST_PRESET_VALUES, sizeof(uint32_t)));
        printf(" reg value shared_bus_control = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_SHARED_BUS_CTRL, sizeof(uint16_t)));
        printf(" reg value slot_interrupt_status = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_SLOT_INTR_STATUS, sizeof(uint16_t)));
        printf(" reg value host_controller_version = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_HOST_CONTROLLER_VERSION, sizeof(uint16_t)));
}
int main()
{

        startSdhcThreads();

        printf("\n\n ****** March test for internal register sync function ****** \n\n");

        printf("\n----------reading from each reg start ----------\n\n");

        readAllSdhcReg();
        
        printf("\n----------reading from each reg done ----------\n\n");
        printf("\n\n ****** March test for internal register sync function done ****** \n\n");
               
        printf("\n\n ****** March test for SDHC regs ******\n\n");
        printf("\n----------writing to each reg start ----------\n\n");

        appWriteToSdhcReg(ADDR_SDHC_ARG_2, sizeof(uint32_t), 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_BLOCK_SIZE, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_BLOCK_COUNT, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_ARG_1, sizeof(uint32_t), 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_TRANSFER_MODE, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_REGISTER_COMMAND, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE0, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE1, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE2, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE3, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE4, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE5, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE6, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE7, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_BUFFER_DATA_PORT, sizeof(uint32_t), 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_PRESENT_STATE, sizeof(uint32_t), 0xfeedbeef);
        appWriteToSdhcReg(ADDR_SDHC_HOST_CONTROL_1, sizeof(uint8_t), 0x12);
        appWriteToSdhcReg(ADDR_SDHC_POWER_CONTROL, sizeof(uint8_t), 0x34);
        appWriteToSdhcReg(ADDR_SDHC_BLOCK_GAP_CONTROL, sizeof(uint8_t), 0x56);
        appWriteToSdhcReg(ADDR_SDHC_WAKEUP_CONTROL, sizeof(uint8_t), 0x78);
        appWriteToSdhcReg(ADDR_SDHC_CLOCK_CONTROL, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_TIMEOUT_CONTROL, sizeof(uint8_t), 0x12);
        appWriteToSdhcReg(ADDR_SDHC_SOFTWARE_RESET, sizeof(uint8_t), 0x34);
        appWriteToSdhcReg(ADDR_SDHC_NORMAL_INTR_STATUS, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_ERROR_INTR_STATUS, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_NORMAL_INTR_STATUS_EN, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_ERROR_INTR_STATUS_EN, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_NORMAL_INTR_SIGNAL_EN, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_ERROR_INTR_SIGNAL_EN, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_AUTO_CMD_ERROR_STATUS, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_HOST_CONTROL_2, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_CAPS, sizeof(uint32_t), 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_MAX_CURRENT_CAPS, sizeof(uint32_t), 0x12345678);
        appWriteToSdhcReg(ADDR_SDHC_MAX_CURRENT_CAPS_RES, sizeof(uint32_t), 0xfeedbeef);
        appWriteToSdhcReg(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_ADMA_ERR_STAT, sizeof(uint8_t), 0x21);
        appWriteToSdhcReg(ADDR_SDHC_ADMA_SYSTEM_ADDR, sizeof(uint32_t), 0x12345678);
        appWriteToSdhcReg(ADDR_SDHC_HOST_PRESET_VALUES, sizeof(uint32_t), 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_SHARED_BUS_CTRL, sizeof(uint16_t), 0x8765);
        appWriteToSdhcReg(ADDR_SDHC_SLOT_INTR_STATUS, sizeof(uint16_t), 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_HOST_CONTROLLER_VERSION, sizeof(uint16_t), 0x8765);

        printf("\n----------writing to each reg done----------\n\n");

        printf("\n----------reading from each reg start ----------\n\n");

        readAllSdhcReg();

        printf("\n----------reading from each reg done----------\n\n");

        printf("\n ****** end of march test ******\n\n");

        return 0;
}
