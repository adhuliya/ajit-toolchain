// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <cortos.h>
#include <ajit_context.h>
#include <data_struct.h>

ajit_context_t context_0 __attribute__ ((aligned(8))) ;
ajit_context_t context_1 __attribute__ ((aligned(8))) ;

ajit_context_t *cp_0 = &context_0;
ajit_context_t *cp_1 = &context_1;

CoroutineControl cp_0_ctrl;
CoroutineControl cp_1_ctrl;

extern uint32_t stack_0[1024];
extern uint32_t stack_1[1024];

void coroutine_0 (void* ptr);
void coroutine_1 (void* ptr);

int serial_interrupt_counter = 0;
int exit_flag = 0;
char buffer[1024];
void my_serial_interrupt_handler()
{
	uint8_t c = __ajit_read_serial_rx_register__();

	buffer[serial_interrupt_counter] = c;
	buffer[serial_interrupt_counter+1]= 0;

	serial_interrupt_counter++;

	//__ajit_serial_puts_via_vmap__ (buffer, 1023);

	if((c == 'q') || (serial_interrupt_counter == 1022))
		exit_flag = 1;
}

void coroutine_yield(int active_context) 
{
	if(exit_flag)
		cortos_printf("Done: %s.\n", buffer);
	if(active_context == 0)
	{
		__ajit_swapcontext__(cp_0,cp_1);
	}
	else if(active_context == 1)
	{
		__ajit_swapcontext__(cp_1,cp_0);
	}

}

void setup ()
{
	// enable serial 0 device..  enable_tx, enable_rx, enable_interrupts	
	__ajit_serial_configure__ (1, 1, 1);
	// set baud rate.
	__ajit_serial_set_baudrate__ (115200, CLK_FREQUENCY);
	// bring uart out of reset.
	__ajit_serial_set_uart_reset__ (0);

	cortos_printf ("enabled serial\n");


	// enable interrupt controller for the current thread.
	enableInterruptControllerAndAllInterrupts(0,0);
}


#define FILL_CONTEXT_AND_RETURN 0
int main () 
{

	cortos_printf("Starting\n");

   	__ajit_context_init__(cp_0);
   	__ajit_context_init__(cp_1);

	cortos_printf("initialized two contexts\n");

	// 
	// make context..
	//
	cortos_printf("making context cp_0\n");
	__ajit_getcontext__(cp_0);
	__ajit_context_set_stack__(cp_0, ((uint8_t*) &stack_0), 4*1024);
	cortos_printf("Setting stack of cp_0 to 0x%x\n", ((uint32_t) &stack_0));
	__ajit_makecontext__(cp_0, (void*) &coroutine_0, NULL);

	//__ajit_print_mcontext__(cp_0);

	cortos_printf("making context cp_1\n");
	__ajit_getcontext__(cp_1);
	__ajit_context_set_stack__(cp_1, ((uint8_t*) &stack_1), 4*1024);
	__ajit_makecontext__(cp_1, (void*) &coroutine_1, NULL);
	cortos_printf("Setting stack of cp_1 to 0x%x\n", ((uint32_t) &stack_1));
	//__ajit_print_mcontext__(cp_1);

	__ajit_setcontext__(cp_0);
	cortos_printf("echo %s\nDone.\n", buffer);
	return(0);
}

