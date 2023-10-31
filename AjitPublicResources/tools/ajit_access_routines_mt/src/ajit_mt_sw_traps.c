#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"
#include "device_addresses.h"
#include "ajit_mt_sw_traps.h"

void (*ajit_global_sw_trap_handlers[NUMBER_OF_GENERIC_SW_TRAPS_SUPPORTED]) (uint32_t, uint32_t, uint32_t);

void ajit_initialize_sw_trap_handlers_to_null()
{
	int I;
	for(I = 0; I < NUMBER_OF_GENERIC_SW_TRAPS_SUPPORTED; I++)
		ajit_global_sw_trap_handlers[I] = NULL;
}

void ajit_set_sw_trap_handler (uint32_t sw_trap_index, void (* foo) (uint32_t, uint32_t, uint32_t))
{
	if(sw_trap_index < NUMBER_OF_GENERIC_SW_TRAPS_SUPPORTED)
		ajit_global_sw_trap_handlers[sw_trap_index] = foo;
		
}

void ajit_generic_sw_trap_handler(uint32_t tbr_value, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
	int err = 0;
	uint32_t trap_index = ((tbr_value >> 4) & 0xff) - 0x80;
	if(trap_index < NUMBER_OF_GENERIC_SW_TRAPS_SUPPORTED)
	{
		void (*fn_ptr) (uint32_t, uint32_t, uint32_t) = ajit_global_sw_trap_handlers[trap_index];
		if(fn_ptr != NULL)
		{
			(*fn_ptr) (arg1, arg2, arg3);
		}
		else
		{
			err = 1;
		}
	}
	else
		err = 1;


	if(err)
	{
		__AJIT_HALT();
	}
}

