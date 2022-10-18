#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"
#include "additional_serial.h"

void __ajit_write_serial_1_control_register_via_bypass__(uint32_t val)
{
	__AJIT_STORE_WORD_MMU_BYPASS__ (ADDR_SERIAL_1_CONTROL_REGISTER,val);
}

uint32_t __ajit_read_serial_1_control_register_via_bypass__()
{
	uint32_t val;
	__AJIT_LOAD_WORD_MMU_BYPASS__ (ADDR_SERIAL_1_CONTROL_REGISTER,val);
	return(val);
}

void __ajit_write_serial_1_tx_register_via_bypass__(uint8_t val)
{
	__AJIT_STORE_UBYTE_MMU_BYPASS__ (ADDR_SERIAL_1_TX_REGISTER,val);
}
uint8_t __ajit_read_serial_1_tx_register_via_bypass__()
{
	uint8_t val;
	__AJIT_LOAD_UBYTE_MMU_BYPASS__ (ADDR_SERIAL_1_TX_REGISTER,val);
	return(val);
}
uint8_t __ajit_read_serial_1_rx_register_via_bypass__()
{
	uint8_t val;
	__AJIT_LOAD_UBYTE_MMU_BYPASS__ (ADDR_SERIAL_1_RX_REGISTER,val);
	return(val);
}


int   __ajit_serial_1_putchar_via_bypass__  (char c)
{
	return(__ajit_serial_putchar_inner__ (0,1,c));
}

int   __ajit_serial_1_getchar_via_bypass__ ()
{
	
	char c;

	 __ajit_serial_getchar_inner_via_bypass__ (0,1, &c);

	return(c);
}

void  __ajit_serial_1_puts_via_bypass__ (char* s, uint32_t length)
{
	return(__ajit_serial_puts_inner__ (0,1,s, length));
}
void  __ajit_serial_1_gets_via_bypass__ (char* s, uint32_t length)
{
	__ajit_serial_gets_inner__ (0,1,s, length);
}

void  __ajit_serial_1_configure_via_bypass__ (uint8_t enable_tx, uint8_t enable_rx, uint8_t enable_intr)
{
	__ajit_serial_configure_inner__(0,1, enable_tx, enable_rx, enable_intr);
}
uint32_t    __ajit_read_serial_1_baud_limit_register_via_bypass__()
{
	uint32_t val;
	__AJIT_LOAD_WORD_MMU_BYPASS__ (ADDR_SERIAL_1_BAUD_LIMIT_REGISTER,val);
	return(val);
}

void        __ajit_write_serial_1_baud_limit_register_via_bypass__(uint32_t bcv)
{
	__AJIT_STORE_WORD_MMU_BYPASS__ (ADDR_SERIAL_1_BAUD_LIMIT_REGISTER,bcv);
}

uint32_t    __ajit_read_serial_1_baud_frequency_register_via_bypass__()
{
	uint32_t val;
	__AJIT_LOAD_WORD_MMU_BYPASS__ (ADDR_SERIAL_1_BAUD_FREQUENCY_REGISTER,val);
	return(val);
}

void        __ajit_write_serial_1_baud_frequency_register_via_bypass__(uint32_t bcv)
{
	__AJIT_STORE_WORD_MMU_BYPASS__ (ADDR_SERIAL_1_BAUD_FREQUENCY_REGISTER,bcv);
}


void  __ajit_serial_1_set_baudrate_via_bypass__ (uint32_t baud_rate, uint32_t clock_frequency)
{
	__ajit_serial_set_baudrate_inner__(1, 1, baud_rate, clock_frequency);
}

void	__ajit_serial_1_set_uart_reset_via_bypass__ (uint8_t reset_value)
{
	__ajit_serial_set_uart_reset_inner__(1,1, reset_value);
}

//////////  serial 1 //////////////////////////////////////////////////////////////////
void __ajit_write_serial_1_control_register_via_vmap__(uint32_t val)
{
	*((uint32_t*) ADDR_SERIAL_1_CONTROL_REGISTER) = val;
}

uint32_t __ajit_read_serial_1_control_register_via_vmap__()
{
	uint32_t ret_val = *((uint8_t*) ADDR_SERIAL_1_CONTROL_REGISTER);
	return(ret_val);
}

void __ajit_write_serial_1_tx_register_via_vmap__(uint8_t val)
{
	*((uint8_t*) ADDR_SERIAL_1_TX_REGISTER) = val;
}
uint8_t __ajit_read_serial_1_tx_register_via_vmap__()
{
	uint8_t ret_val = *((uint8_t*) ADDR_SERIAL_1_TX_REGISTER);
	return(ret_val);
}
uint8_t __ajit_read_serial_1_rx_register_via_vmap__()
{
	uint8_t ret_val = *((uint8_t*) ADDR_SERIAL_1_RX_REGISTER);
	return(ret_val);
}


int   __ajit_serial_1_putchar_via_vmap__  (char c)
{
	return(__ajit_serial_putchar_inner__ (1,1,c));
}

int   __ajit_serial_1_getchar_via_vmap__ ()
{
	
	char c;

	 __ajit_serial_getchar_inner__ (1,1, &c);

	return(c);
}

void  __ajit_serial_1_puts_via_vmap__ (char* s, uint32_t length)
{
	return(__ajit_serial_puts_inner__ (1,1,s, length));
}
void  __ajit_serial_1_gets_via_vmap__ (char* s, uint32_t length)
{
	__ajit_serial_gets_inner__ (1,1,s, length);
}

void  __ajit_serial_1_configure_via_vmap__ (uint8_t enable_tx, uint8_t enable_rx, uint8_t enable_intr)
{
	__ajit_serial_configure_inner__(1,1, enable_tx, enable_rx, enable_intr);
}
uint32_t    __ajit_read_serial_1_baud_limit_register_via_vmap__()
{
	uint32_t retval = *((uint32_t*) ADDR_SERIAL_1_BAUD_LIMIT_REGISTER);
	return(retval);
}

void        __ajit_write_serial_1_baud_limit_register_via_vmap__(uint32_t bcv)
{
	 *((uint32_t*) ADDR_SERIAL_1_BAUD_LIMIT_REGISTER) = bcv;
}

uint32_t    __ajit_read_serial_1_baud_frequency_register_via_vmap__()
{
	uint32_t retval = *((uint32_t*) ADDR_SERIAL_1_BAUD_FREQUENCY_REGISTER);
	return(retval);
}

void        __ajit_write_serial_1_baud_frequency_register_via_vmap__(uint32_t bcv)
{
	 *((uint32_t*) ADDR_SERIAL_1_BAUD_FREQUENCY_REGISTER) = bcv;
}


void  __ajit_serial_1_set_baudrate_via_vmap__ (uint32_t baud_rate, uint32_t clock_frequency)
{
	__ajit_serial_set_baudrate_inner__(1, 1, baud_rate, clock_frequency);
}

void	__ajit_serial_1_set_uart_reset_via_vmap__ (uint8_t reset_value)
{
	__ajit_serial_set_uart_reset_inner__(1,1, reset_value);
}
