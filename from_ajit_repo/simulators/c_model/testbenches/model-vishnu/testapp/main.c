#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "Pipes.h"
#include "pipeHandler.h"
#include "Ancillary.h"
#include "Sdhc.h"

#define READ 1
#define WRITE 0

#define BYTE 0b1
#define HWORD 0b11
#define WORD 0b1111

uint32_t appReadOrWriteSdhcReg(uint32_t addr, uint8_t byte_mask, uint8_t rwbar, uint32_t data)
{
        uint32_t ret = 0;
        uint64_t send_cmd = 0;

        addr = addr & 0xFFFFFF;

        send_cmd = setSlice64(send_cmd, 63, 32, addr);
        if (rwbar == READ) send_cmd = setSlice64(send_cmd, 63, 63, 1);
        else if (rwbar == WRITE) send_cmd = setSlice64(send_cmd, 63, 63, 0);
        send_cmd = setSlice64(send_cmd, 62, 59, byte_mask);
        send_cmd = setSlice64(send_cmd, 31, 0, data);

        write_uint64("peripheral_bridge_to_sdhc_request", send_cmd);
        ret = read_uint32("sdhc_to_peripheral_bridge_response");
        return ret;
}
uint32_t appReadFromSdhcReg(uint32_t addr, uint8_t byte_mask)
{
        uint8_t rwbar = READ;
        uint32_t data = 0;
        return appReadOrWriteSdhcReg(addr, byte_mask, rwbar, data);
}
uint32_t appWriteToSdhcReg(uint32_t addr, uint8_t byte_mask, uint32_t data)
{
        uint8_t rwbar = WRITE;
        return appReadOrWriteSdhcReg(addr, byte_mask, rwbar, data);
}

void readAllSdhcReg()
{
        printf(" reg value arg2 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ARG_2, 0b1111));
        printf(" reg value blk size = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_BLOCK_SIZE, 0b11));
        printf(" reg value blk count = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_BLOCK_COUNT, 0b11));
        printf(" reg value arg1 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ARG_1, 0b1111));
        printf(" reg value tx mode = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_TRANSFER_MODE, 0b11));
        printf(" reg value register command = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_REGISTER_COMMAND, 0b11));
        printf(" reg value response 0 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE0, 0b11));
        printf(" reg value response 1 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE1, 0b11));
        printf(" reg value response 2 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE2, 0b11));
        printf(" reg value response 3 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE3, 0b11));
        printf(" reg value response 4 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE4, 0b11));
        printf(" reg value response 5 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE5, 0b11));
        printf(" reg value response 6 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE6, 0b11));
        printf(" reg value response 7 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_RESPONSE7, 0b11));
        printf(" reg value buffr data port = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_BUFFER_DATA_PORT, 0b1111));
        printf(" reg value present state = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_PRESENT_STATE, 0b1111));
        printf(" reg value host ctrl 1 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_HOST_CONTROL_1, 0b1));
        printf(" reg value power ctrl = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_POWER_CONTROL, 0b1));
        printf(" reg value blk gap ctrl = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_BLOCK_GAP_CONTROL, 0b1));
        printf(" reg value wakeup trl = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_WAKEUP_CONTROL, 0b1));
        printf(" reg value clk ctrl = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_CLOCK_CONTROL, 0b1));
        printf(" reg value timeout ctrl = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_TIMEOUT_CONTROL, 0b1));
        printf(" reg value software reset = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_SOFTWARE_RESET, 0b1));
        printf(" reg value nrml intr status = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_NORMAL_INTR_STATUS, 0b11));
        printf(" reg value error_intr_status = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ERROR_INTR_STATUS, 0b11));
        printf(" reg value normal_intr_status_enable = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_NORMAL_INTR_STATUS_EN, 0b11));
        printf(" reg value error_intr_status_enable = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ERROR_INTR_STATUS_EN, 0b11));
        printf(" reg value normal_intr_signal_enable = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_NORMAL_INTR_SIGNAL_EN, 0b11));
        printf(" reg value error_intr_signal_enable = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ERROR_INTR_SIGNAL_EN, 0b11));
        printf(" reg value autoCMD_error_status = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_AUTO_CMD_ERROR_STATUS, 0b11));
        printf(" reg value host_ctrl2 = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_HOST_CONTROL_2, 0b11));
        printf(" reg value capabilities = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_CAPS, 0b1111));
        printf(" reg value max_current_cap = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_MAX_CURRENT_CAPS, 0b1111));
        printf(" reg value res_max_current_cap = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_MAX_CURRENT_CAPS_RES, 0b1111));
        printf(" reg value force_event_autoCMD_err_stat = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT, 0b11));
        printf(" reg value force_event_autoCMD_err_interrupt_stat = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT, 0b11));
        printf(" reg value ADMA_err_status = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ADMA_ERR_STAT, 0b1));
        printf(" reg value ADMA_system_address = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_ADMA_SYSTEM_ADDR, 0b1111));
        printf(" reg value preset_value = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_HOST_PRESET_VALUES, 0b1111));
        printf(" reg value shared_bus_control = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_SHARED_BUS_CTRL, 0b11));
        printf(" reg value slot_interrupt_status = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_SLOT_INTR_STATUS, 0b11));
        printf(" reg value host_controller_version = 0x%x\n", appReadFromSdhcReg(ADDR_SDHC_HOST_CONTROLLER_VERSION, 0b11));
}
int main()
{

        startSdhcThreads();

        printf("\n\n ****** March test for internal regiser sync function ****** \n\n");

        printf("\n----------reading from each reg start ----------\n\n");

        readAllSdhcReg();
        
        printf("\n----------reading from each reg done ----------\n\n");
        printf("\n\n ****** March test for internal regiser sync function done ****** \n\n");
               
        printf("\n\n ****** March test for SDHC regs ******\n\n");
        printf("\n----------writing to each reg start ----------\n\n");

        appWriteToSdhcReg(ADDR_SDHC_ARG_2, 0b1111, 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_BLOCK_SIZE, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_BLOCK_COUNT, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_ARG_1, 0b1111, 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_TRANSFER_MODE, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_REGISTER_COMMAND, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE0, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE1, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE2, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE3, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE4, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE5, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE6, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_RESPONSE7, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_BUFFER_DATA_PORT, 0b1111, 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_PRESENT_STATE, 0b1111, 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_HOST_CONTROL_1, 0b1, 0x21);
        appWriteToSdhcReg(ADDR_SDHC_POWER_CONTROL, 0b1, 0x21);
        appWriteToSdhcReg(ADDR_SDHC_BLOCK_GAP_CONTROL, 0b1, 0x21);
        appWriteToSdhcReg(ADDR_SDHC_WAKEUP_CONTROL, 0b1, 0x21);
        appWriteToSdhcReg(ADDR_SDHC_CLOCK_CONTROL, 0b1, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_TIMEOUT_CONTROL, 0b1, 0x21);
        appWriteToSdhcReg(ADDR_SDHC_SOFTWARE_RESET, 0b1, 0x21);
        appWriteToSdhcReg(ADDR_SDHC_NORMAL_INTR_STATUS, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_ERROR_INTR_STATUS, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_NORMAL_INTR_STATUS_EN, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_ERROR_INTR_STATUS_EN, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_NORMAL_INTR_SIGNAL_EN, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_ERROR_INTR_SIGNAL_EN, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_AUTO_CMD_ERROR_STATUS, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_HOST_CONTROL_2, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_CAPS, 0b1111, 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_MAX_CURRENT_CAPS, 0b1111, 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_MAX_CURRENT_CAPS_RES, 0b1111, 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_ADMA_ERR_STAT, 0b1, 0x21);
        appWriteToSdhcReg(ADDR_SDHC_ADMA_SYSTEM_ADDR, 0b1111, 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_HOST_PRESET_VALUES, 0b1111, 0x87654321);
        appWriteToSdhcReg(ADDR_SDHC_SHARED_BUS_CTRL, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_SLOT_INTR_STATUS, 0b11, 0x4321);
        appWriteToSdhcReg(ADDR_SDHC_HOST_CONTROLLER_VERSION, 0b11, 0x4321);

        printf("\n----------writing to each reg done----------\n\n");

        printf("\n----------reading from each reg start ----------\n\n");

        readAllSdhcReg();

        printf("\n----------reading from each reg done----------\n\n");

        printf("\n ****** end of march test ******\n\n");

               return 0;
}
