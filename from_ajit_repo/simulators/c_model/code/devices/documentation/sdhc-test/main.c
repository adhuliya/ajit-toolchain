#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "ajit_access_routines.h"
#include "core_portme.h"

#include "sdhc_access.h"

int __enable_serial()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	return(0);
}

int __enable_serial_interrupt()
{
	__ajit_write_serial_control_register__ (TX_ENABLE | RX_ENABLE |RX_INTR_ENABLE);
	return(0);
}

int ajit_main()
{
       	__enable_serial();
        __enable_serial_interrupt();

       	ee_printf("\n\n March test for SDHC regs\n\n");
	
        ee_printf("\n------------------------------\n\n");

        // SDHC interface begin--------------------------------------------------

        uint32_t data=0;

        __ajit_write_sdhc_reg_word_bypass(ADDR_SDHC_ARG_2, 0x87654321 );                // 0x654321
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_BLOCK_SIZE, 0x4321 );              // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_BLOCK_COUNT, 0x4321 );             // 0x4321
        __ajit_write_sdhc_reg_word_bypass(ADDR_SDHC_ARG_1, 0x87654321 );                // 0x654321
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_TRANSFER_MODE, 0x4321 );           // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_REGISTER_COMMAND, 0x4321 );        // 0x4321
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE0, 0x4321 );               // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE1, 0x4321 );               // 0x4321
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE2, 0x4321 );               // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE3, 0x4321 );               // 0x4321
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE4, 0x4321 );               // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE5, 0x4321 );               // 0x4321
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE6, 0x4321 );               // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE7, 0x4321 );               // 0x4321
        __ajit_write_sdhc_reg_word_bypass(ADDR_SDHC_BUFFER_DATA_PORT, 0x87654321 );     // 0x654321
        __ajit_write_sdhc_reg_word_bypass(ADDR_SDHC_PRESENT_STATE, 0x87654321 );        // 0x654321
        __ajit_write_sdhc_reg_byte_bypass(ADDR_SDHC_HOST_CONTROL_1, 0x21 );             // 0
        __ajit_write_sdhc_reg_byte_bypass(ADDR_SDHC_POWER_CONTROL, 0x21 );              // 0
        __ajit_write_sdhc_reg_byte_bypass(ADDR_SDHC_BLOCK_GAP_CONTROL, 0x21 );          // 0
        __ajit_write_sdhc_reg_byte_bypass(ADDR_SDHC_WAKEUP_CONTROL, 0x21 );             // 0x21
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_CLOCK_CONTROL, 0x4321 );           // 0
        __ajit_write_sdhc_reg_byte_bypass(ADDR_SDHC_TIMEOUT_CONTROL, 0x21 );            // 0
        __ajit_write_sdhc_reg_byte_bypass(ADDR_SDHC_SOFTWARE_RESET, 0x21 );             // 0x21
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_NORMAL_INTR_STATUS, 0x4321 );      // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_ERROR_INTR_STATUS, 0x4321 );       // 0x4321
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_NORMAL_INTR_STATUS_EN, 0x4321 );   // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_ERROR_INTR_STATUS_EN, 0x4321 );    // 0     
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_NORMAL_INTR_SIGNAL_EN, 0x4321 );   // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_ERROR_INTR_SIGNAL_EN, 0x4321 );    // 0x4321
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_AUTO_CMD_ERROR_STATUS, 0x4321 );   // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_HOST_CONTROL_2, 0x4321 );          // 0x4321
        __ajit_write_sdhc_reg_word_bypass(ADDR_SDHC_CAPS, 0x87654321 );                 // 0x654321
        __ajit_write_sdhc_reg_word_bypass(ADDR_SDHC_MAX_CURRENT_CAPS, 0x87654321 );     // 0x654321
        __ajit_write_sdhc_reg_word_bypass(ADDR_SDHC_MAX_CURRENT_CAPS_RES, 0x87654321 ); // 0x654321
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT, 0x4321 );      // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT, 0x4321 ); // 0x4321
        __ajit_write_sdhc_reg_byte_bypass(ADDR_SDHC_ADMA_ERR_STAT, 0x21 );              //0
        __ajit_write_sdhc_reg_word_bypass(ADDR_SDHC_ADMA_SYSTEM_ADDR, 0x87654321 );     // 0x654321
        __ajit_write_sdhc_reg_word_bypass(ADDR_SDHC_HOST_PRESET_VALUES, 0x87654321 );   // 0x654321
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_SHARED_BUS_CTRL, 0x4321 );         // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_SLOT_INTR_STATUS, 0x4321 );        // 0
        __ajit_write_sdhc_reg_hword_bypass(ADDR_SDHC_HOST_CONTROLLER_VERSION, 0x4321 ); // 0x4321
        
        ee_printf( " reg value arg2 = 0x%x @ 0x%x\n",                                   __ajit_read_sdhc_reg_word_bypass(ADDR_SDHC_ARG_2), ADDR_SDHC_ARG_2);
        ee_printf( " reg value blk size = 0x%x @ 0x%x\n",                               __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_BLOCK_SIZE), ADDR_SDHC_BLOCK_SIZE);
        ee_printf( " reg value blk count = 0x%x @ 0x%x\n",                              __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_BLOCK_COUNT), ADDR_SDHC_BLOCK_COUNT);
        ee_printf( " reg value arg1 = 0x%x @ 0x%x\n",                                   __ajit_read_sdhc_reg_word_bypass(ADDR_SDHC_ARG_1), ADDR_SDHC_ARG_1);
        ee_printf( " reg value tx mode = 0x%x @ 0x%x\n",                                __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_TRANSFER_MODE), ADDR_SDHC_TRANSFER_MODE);
        ee_printf( " reg value register command = 0x%x @ 0x%x\n",                       __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_REGISTER_COMMAND), ADDR_SDHC_REGISTER_COMMAND);
        ee_printf( " reg value response 0 = 0x%x @ 0x%x\n",                             __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE0), ADDR_SDHC_RESPONSE0);
        ee_printf( " reg value response 1 = 0x%x @ 0x%x\n",                             __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE1), ADDR_SDHC_RESPONSE1);
        ee_printf( " reg value response 2 = 0x%x @ 0x%x\n",                             __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE2), ADDR_SDHC_RESPONSE2);
        ee_printf( " reg value response 3 = 0x%x @ 0x%x\n",                             __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE3), ADDR_SDHC_RESPONSE3);
        ee_printf( " reg value response 4 = 0x%x @ 0x%x\n",                             __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE4), ADDR_SDHC_RESPONSE4);
        ee_printf( " reg value response 5 = 0x%x @ 0x%x\n",                             __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE5), ADDR_SDHC_RESPONSE5);
        ee_printf( " reg value response 6 = 0x%x @ 0x%x\n",                             __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE6), ADDR_SDHC_RESPONSE6);
        ee_printf( " reg value response 7 = 0x%x @ 0x%x\n",                             __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_RESPONSE7), ADDR_SDHC_RESPONSE1);
        ee_printf( " reg value buffr data port = 0x%x @ 0x%x\n",                        __ajit_read_sdhc_reg_word_bypass(ADDR_SDHC_BUFFER_DATA_PORT), ADDR_SDHC_BUFFER_DATA_PORT);
        ee_printf( " reg value present state = 0x%x @ 0x%x\n",                          __ajit_read_sdhc_reg_word_bypass(ADDR_SDHC_PRESENT_STATE), ADDR_SDHC_PRESENT_STATE);
        ee_printf( " reg value host ctrl 1 = 0x%x @ 0x%x\n",                            __ajit_read_sdhc_reg_byte_bypass(ADDR_SDHC_HOST_CONTROL_1), ADDR_SDHC_HOST_CONTROL_1);
        ee_printf( " reg value power ctrl = 0x%x @ 0x%x\n",                             __ajit_read_sdhc_reg_byte_bypass(ADDR_SDHC_POWER_CONTROL), ADDR_SDHC_POWER_CONTROL);
        ee_printf( " reg value blk gap ctrl = 0x%x @ 0x%x\n",                           __ajit_read_sdhc_reg_byte_bypass(ADDR_SDHC_BLOCK_GAP_CONTROL), ADDR_SDHC_BLOCK_GAP_CONTROL);
        ee_printf( " reg value wakeup trl = 0x%x @ 0x%x\n",                             __ajit_read_sdhc_reg_byte_bypass(ADDR_SDHC_WAKEUP_CONTROL), ADDR_SDHC_WAKEUP_CONTROL);
        ee_printf( " reg value clk ctrl = 0x%x @ 0x%x\n",                               __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_CLOCK_CONTROL), ADDR_SDHC_CLOCK_CONTROL);
        ee_printf( " reg value timeout ctrl = 0x%x @ 0x%x\n",                           __ajit_read_sdhc_reg_byte_bypass(ADDR_SDHC_TIMEOUT_CONTROL), ADDR_SDHC_TIMEOUT_CONTROL);
        ee_printf( " reg value software reset = 0x%x @ 0x%x\n",                         __ajit_read_sdhc_reg_byte_bypass(ADDR_SDHC_SOFTWARE_RESET), ADDR_SDHC_SOFTWARE_RESET);
        ee_printf( " reg value nrml intr status = 0x%x @ 0x%x\n",                       __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_NORMAL_INTR_STATUS), ADDR_SDHC_NORMAL_INTR_STATUS);
        ee_printf( " reg value error_intr_status = 0x%x @ 0x%x\n",                      __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_ERROR_INTR_STATUS), ADDR_SDHC_ERROR_INTR_STATUS);
        ee_printf( " reg value normal_intr_status_enable = 0x%x @ 0x%x\n",              __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_NORMAL_INTR_STATUS_EN), ADDR_SDHC_NORMAL_INTR_STATUS_EN);
        ee_printf( " reg value error_intr_status_enable = 0x%x @ 0x%x\n",               __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_ERROR_INTR_STATUS_EN), ADDR_SDHC_ERROR_INTR_STATUS_EN);
        ee_printf( " reg value normal_intr_signal_enable = 0x%x @ 0x%x\n",              __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_NORMAL_INTR_SIGNAL_EN), ADDR_SDHC_NORMAL_INTR_SIGNAL_EN);
        ee_printf( " reg value error_intr_signal_enable = 0x%x @ 0x%x\n",               __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_ERROR_INTR_SIGNAL_EN), ADDR_SDHC_ERROR_INTR_SIGNAL_EN);
        ee_printf( " reg value autoCMD_error_status = 0x%x @ 0x%x\n",                   __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_AUTO_CMD_ERROR_STATUS), ADDR_SDHC_AUTO_CMD_ERROR_STATUS);
        ee_printf( " reg value host_ctrl2 = 0x%x @ 0x%x\n",                             __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_HOST_CONTROL_2), ADDR_SDHC_HOST_CONTROL_2);
        ee_printf( " reg value capabilities = 0x%x @ 0x%x\n",                           __ajit_read_sdhc_reg_word_bypass(ADDR_SDHC_CAPS), ADDR_SDHC_CAPS);
        ee_printf( " reg value max_current_cap = 0x%x @ 0x%x\n",                        __ajit_read_sdhc_reg_word_bypass(ADDR_SDHC_MAX_CURRENT_CAPS), ADDR_SDHC_MAX_CURRENT_CAPS);
        ee_printf( " reg value res_max_current_cap = 0x%x @ 0x%x\n",                    __ajit_read_sdhc_reg_word_bypass(ADDR_SDHC_MAX_CURRENT_CAPS_RES), ADDR_SDHC_MAX_CURRENT_CAPS_RES);
        ee_printf( " reg value force_event_autoCMD_err_stat = 0x%x @ 0x%x\n",           __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT), ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT);
        ee_printf( " reg value force_event_autoCMD_err_interrupt_stat = 0x%x @ 0x%x\n", __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT), ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERR_INTRSTAT);
        ee_printf( " reg value ADMA_err_status = 0x%x @ 0x%x\n",                        __ajit_read_sdhc_reg_byte_bypass(ADDR_SDHC_ADMA_ERR_STAT), ADDR_SDHC_ADMA_ERR_STAT);
        ee_printf( " reg value ADMA_system_address = 0x%x @ 0x%x\n",                    __ajit_read_sdhc_reg_word_bypass(ADDR_SDHC_ADMA_SYSTEM_ADDR), ADDR_SDHC_ADMA_SYSTEM_ADDR);
        ee_printf( " reg value preset_value = 0x%x @ 0x%x\n",                           __ajit_read_sdhc_reg_word_bypass(ADDR_SDHC_HOST_PRESET_VALUES), ADDR_SDHC_HOST_PRESET_VALUES);
        ee_printf( " reg value shared_bus_control = 0x%x @ 0x%x\n",                     __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_SHARED_BUS_CTRL), ADDR_SDHC_SHARED_BUS_CTRL);
        ee_printf( " reg value slot_interrupt_status = 0x%x @ 0x%x\n",                  __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_SLOT_INTR_STATUS), ADDR_SDHC_SLOT_INTR_STATUS);
        ee_printf( " reg value host_controller_version = 0x%x @ 0x%x\n\n",              __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_HOST_CONTROLLER_VERSION), ADDR_SDHC_HOST_CONTROLLER_VERSION);

        // uint16_t blk_size = 0x4321;
        // uint8_t ablk_size[2];

        // memcpy(&ablk_size, &blk_size, sizeof(uint16_t));
        
        // memcpy(ADDR_SDHC_BLOCK_SIZE, &ablk_size[0], sizeof(uint16_t));
        // ee_printf( " reg value blk size = 0x%x @ 0x%x\n",                               __ajit_read_sdhc_reg_hword_bypass(ADDR_SDHC_BLOCK_SIZE), ADDR_SDHC_BLOCK_SIZE);
        
        ee_printf("\n------------------------------\n\n");

       	return 0;
}
