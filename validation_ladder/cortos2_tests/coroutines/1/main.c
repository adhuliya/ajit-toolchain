// Program for finding jitter using timer interrupts
#include <stdint.h>
#include <stdio.h>
#include <ajit_access_routines.h>
#include <ajit_mt_irc.h>
#include <core_portme.h>
#include <cortos.h>
#include <ajit_context.h>
#include <data_struct.h>

/* two contexts */
ajit_context_t context_0 __attribute__ ((aligned(8))) ;
ajit_context_t context_1 __attribute__ ((aligned(8))) ;

ajit_context_t *cp_0 = &context_0;
ajit_context_t *cp_1 = &context_1;


/* stacks for the two contexts */
extern uint32_t stack_0[1024];
extern uint32_t stack_1[1024];

/* work for each context */
void coroutine_0 (void* ptr);
void coroutine_1 (void* ptr);

/* overlayed serial interrupt (orthogonal activity across contexts) */
int serial_interrupt_counter = 0;
volatile int volatile exit_flag = 0;
char buffer[1024];
void my_serial_interrupt_handler()
{
	uint8_t c = __ajit_read_serial_rx_register__();
	ee_printf("intr\n");


	buffer[serial_interrupt_counter] = c;
	buffer[serial_interrupt_counter+1]= 0;

	serial_interrupt_counter++;

	//__ajit_serial_puts_via_vmap__ (buffer, 1023);

	if((c == 'q') || (serial_interrupt_counter == 1022))
	{
		exit_flag = 1;
		ee_printf("exit_flag=1\n");
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


volatile int volatile first_time = 1;

int main () 
{

	cortos_printf("Starting\n");


	/* clear the contexts */
   	__ajit_context_init__(cp_0);
   	__ajit_context_init__(cp_1);

	cortos_printf("initialized two contexts\n");

	// 
	// get context cp_0.  The return point of this getcontext
	// is important, since setcontext (cp_0) will return to this
	// point if cp_0->uc_link is NULL.
	//
	__ajit_getcontext__(cp_0);
	cortos_printf("after getcontext cp_0, first_time=%d.\n", first_time);

	if(first_time)
	// first time? make the contexts (function, arg, stack, link).
	{
		first_time = 0;

		cortos_printf("making context cp_0\n");
		__ajit_context_set_stack__(cp_0, ((uint8_t*) &stack_0), 4*1024);
		cortos_printf("Setting stack of cp_0 to 0x%x\n", ((uint32_t) &stack_0));
		__ajit_makecontext__(cp_0, (void*) &coroutine_0, NULL);

		__ajit_getcontext__(cp_1);
		cortos_printf("making context cp_1\n");
		__ajit_context_set_stack__(cp_1, ((uint8_t*) &stack_1), 4*1024);
		cortos_printf("Setting stack of cp_1 to 0x%x\n", ((uint32_t) &stack_1));
		__ajit_makecontext__(cp_1, (void*) &coroutine_1, NULL);
	
		// start the proceedings from cp_0
		//   The func called from cp_0 will do setcontext(cp_1)
		//
		//   The func called from cp_1 will do setcontext(cp_0) until the
		//   exit condition is reached.
		__ajit_setcontext__(cp_0);
	}

	// when setcontext (cp_0) returns, print this and we are done.
	cortos_printf("echo %s\nDone.\n", buffer);
	return(0);
}

