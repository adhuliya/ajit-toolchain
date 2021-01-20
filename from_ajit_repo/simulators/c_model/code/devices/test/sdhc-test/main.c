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

        // __ajit_bypass_write_sdhc_reg_dword(ADDR_SDHC_ARG_2, 0xFFFF);

        uint32_t data;

        data  = __ajit_bypass_read_sdhc_reg_dword(ADDR_SDHC_ARG_2);
        ee_printf("data read from register arg2 = %x \n", data);

        data  = __ajit_bypass_read_sdhc_reg_dword(ADDR_SDHC_ARG_1);
        ee_printf("data read from register arg1 = %x \n", data);


        // ee_printf("data read from SDHC arg2 register = %d \n", __ajit_bypass_read_sdhc_reg_dword(ADDR_SDHC_ARG_2));

        // SDHC interface end----------------------------------------------------


        // ee_printf("data read from serial control register = %d \n", __ajit_read_serial_control_register__());
        
        ee_printf("\n------------------------------\n\n");

       	return 0;
}
