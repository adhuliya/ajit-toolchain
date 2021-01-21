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

       	ee_printf("\n\nHello world\n\n");
	
        ee_printf("\n------------------------------\n\n");

        // SDHC interface begin--------------------------------------------------

        uint32_t data;

        // 32b registers
        ee_printf("data read from SDHC arg2 register = 0x%x \n", 
                        __ajit_bypass_read_sdhc_reg_dword(ADDR_SDHC_ARG_2)); ;

        ee_printf("data read from SDHC arg1 register = 0x%x \n", 
                        __ajit_bypass_read_sdhc_reg_dword(ADDR_SDHC_ARG_1));        

        // 16b registers

        ee_printf("data read from SDHC blk size register = 0x%x \n", 
                        __ajit_bypass_read_sdhc_reg_word(ADDR_SDHC_BLOCK_SIZE));

        // 8bit registers

        ee_printf("data read from SDHC host cntrl 1 register = 0x%x \n", 
                        __ajit_bypass_read_sdhc_reg_byte(ADDR_SDHC_HOST_CONTROL_1));

        // SDHC interface end----------------------------------------------------

        ee_printf("\n------------------------------\n\n");

       	return 0;
}
