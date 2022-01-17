//Program for RPN calculator  using serial sw_traps
#include <stdint.h>
#include <stdio.h>
#include <setjmp.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "ajit_mt_sw_traps.h"

#define NWORDS 16
#define PRINTF ee_printf

int exit_flag = 0;

int __enable_serial()
{
	__ajit_write_serial_control_register_via_vmap__ ( TX_ENABLE | RX_ENABLE);
	return(0);
}

int __enable_serial_sw_trap()
{
	__ajit_write_serial_control_register_via_vmap__ (TX_ENABLE | RX_ENABLE |RX_INTR_ENABLE);
	return(0);
}


void __t5_handler(uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
	*((uint32_t*) arg2) = __ajit_load_word_from_physical_address__((uint64_t) arg1);
	PRINTF("in __t5_handler(0x%x, 0x%x, 0x%x) = 0x%x\n", arg1, arg2, arg3, *((uint32_t*) arg2));
}


void read_physical_memory (uint32_t address, uint32_t value_pointer)
{
	__AJIT_SW_TRAP(5);
}


int main () 
{
	__enable_serial();

	// set up software trap handler.
	ajit_initialize_sw_trap_handlers_to_null();
	ajit_set_sw_trap_handler(5, &(__t5_handler));	

	uint32_t v; 

	uint32_t index;
	for(index = 0x0; index < NWORDS; index++)
	{
		read_physical_memory (0x40000000 + (index<<2), (uint32_t) &v);
		PRINTF("0x%x = PMEM[0x%x]\n", v, 0x40000000 + (index << 2));
	}


	uint32_t rval = 0x01234567;
	uint32_t rrval = 0x0;
	__AJIT_SET_IU_REGISTER(1,rval);
	__AJIT_GET_IU_REGISTER(1,rrval);
		
	PRINTF("IU reg rval=0x%x, rrval = 0x%x\n", rval, rrval);
	

	return(0);
}
