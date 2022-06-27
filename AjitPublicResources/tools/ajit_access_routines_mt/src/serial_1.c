#include <stdint.h>
#include <stdio.h>

#include "ajit_access_routines.h"
#include "serial_1.h"

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
	uint32_t ctrl_reg =0;
	ctrl_reg = *((uint32_t*) ADDR_SERIAL_1_CONTROL_REGISTER);
	int ret_val = 0;
	if(ctrl_reg & TX_ENABLE)
	{	
		if(!(ctrl_reg & TX_FULL))
		{
			*((uint8_t*) ADDR_SERIAL_1_TX_REGISTER) = c;
			ret_val =  ((int) c);
		}
	}
	return (ret_val);
}

int   __ajit_serial_1_getchar_via_vmap__ ()
{
	int ret_val = 0;
	uint32_t ctrl_reg = *((uint32_t*) ADDR_SERIAL_1_CONTROL_REGISTER);
	if(ctrl_reg & RX_ENABLE)
	{
		if (ctrl_reg & RX_FULL)
		{
			uint32_t rx_val = 0;
			rx_val = *((uint8_t*) ADDR_SERIAL_1_RX_REGISTER);
			ret_val = (int) rx_val;
		}
	}
	return(ret_val);
}

void  __ajit_serial_1_puts_via_vmap__ (char* s, uint32_t length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		int rval = 0;
		while(rval == 0)
			rval =  __ajit_serial_1_putchar_via_vmap__ (s[i]);
	}
}
void  __ajit_serial_1_gets_via_vmap__ (char* s, uint32_t length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		int rval = 0;
		while(rval == 0)
		  rval = __ajit_serial_1_getchar_via_vmap__();

		s[i] = rval;
	}
}

void  __ajit_serial_1_configure_via_vmap__ (uint8_t enable_tx, uint8_t enable_rx, uint8_t enable_intr)
{
	uint32_t cval = *((uint32_t*) ADDR_SERIAL_1_CONTROL_REGISTER);


	if(enable_tx)
	{
		cval = cval | 1;
	}
	else
	{
		cval = cval & (~1);
	}

	if(enable_rx) 
	{
		cval = cval | 2;
	}
	else
	{
		cval = cval & (~2);
	}

	if(enable_intr)
	{
		cval = cval | 4;
	}
	else
	{
		cval = cval & (~4);
	}
	*((uint32_t*) ADDR_SERIAL_1_CONTROL_REGISTER) = cval;
}
