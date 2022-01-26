//Program for RPN calculator  using serial interrupts
#include <stdint.h>
#include <stdio.h>
#include <setjmp.h>
#include "ajit_access_routines.h"
#include "core_portme.h"
#include "ajit_mt_irc.h"

#define PRINTF ee_printf

int exit_flag = 0;

int __enable_serial()
{
	__ajit_write_serial_control_register_via_vmap__ ( TX_ENABLE | RX_ENABLE);
	return(0);
}

int __enable_serial_interrupt()
{
	__ajit_write_serial_control_register_via_vmap__ (TX_ENABLE | RX_ENABLE |RX_INTR_ENABLE);
	return(0);
}


//
// Note: user defined, but will run in supervisor mode.
//
void __serial_interrupt_handler()
{
#ifdef DEBUG_MODE
	PRINTF("in __serial_interrupt_handler.\n");
#endif

	uint32_t fp_regs[34];
	uint32_t fp_addr = (uint32_t) &(fp_regs[0]);

	__AJIT_SAVE_FP_REGS__ (fp_addr);

	//
	// Read the byte from the serial device using a user-level routine!
	// We could use the supervisor-level routine also here....
	//
	uint32_t B = __ajit_read_serial_rx_register_via_vmap__();

	if(B == 'q')
	{
		exit_flag = 1;
	}
 
#ifdef DEBUG_MODE
	PRINTF("Received %c, exit flag =%d\n",B, exit_flag);
#endif

	__ajit_serial_putchar_via_vmap__(B);

	__AJIT_RESTORE_FP_REGS__ (fp_addr);
}

int main () 
{
	exit_flag = 0;

	// Note: do not forget to initialize the specific
	//       interrupt handlers.
	ajit_initialize_interrupt_handlers_to_null();
	ajit_set_interrupt_handler(12, &(__serial_interrupt_handler));	

	enableInterruptControllerAndAllInterrupts(0,0);

	__enable_serial_interrupt();
	PRINTF("Enabled serial.\n");

	while(1)
	{
		add_delay();
		if(exit_flag)
		{
			break;
		}
	}
	
	PRINTF("\nBYE(%d)\n", exit_flag);
	return(0);
}
