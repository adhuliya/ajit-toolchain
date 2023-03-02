#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include <cortos.h>

// 16 words here.
#define ACCELERATOR_REGISTERS_BASE_ADDRESS 0xffff4000
#define TEST_ARRAY_SIZE 16

volatile int interrupt_counter = 0;
volatile int volatile interrupt_flag = 0;

uint64_t  test_array[TEST_ARRAY_SIZE];

void setup()
{
	// configure uart
	__ajit_serial_configure__(1,0,0);
	__ajit_serial_set_baudrate__ (115200, 80000000);
	__ajit_serial_set_uart_reset__ (0);

	cortos_printf ("enabled serial.\n");

	// enable interrupt controller for the current thread.
	enableInterruptControllerAndAllInterrupts(0,0);
	cortos_printf ("enabled interrupt controller.\n");
}

void write_to_accelerator_register (uint32_t reg_id, uint32_t val)
{
	*((uint32_t*) (ACCELERATOR_REGISTERS_BASE_ADDRESS + (reg_id << 2))) = val;
}

uint32_t read_from_accelerator_register (uint32_t reg_id)
{
	uint32_t val = *((uint32_t*) (ACCELERATOR_REGISTERS_BASE_ADDRESS + (reg_id << 2)));
	return(val);
}

void dump_memory (uint32_t I)
{
	cortos_printf ("memory dump %d.\n", I);
	uint32_t J;
	uint32_t B = 0;
	uint8_t* ptr = (uint8_t*) &(test_array[0]);
	for(J = 0; J < (TEST_ARRAY_SIZE*8); J++)
	{
		B++;
		cortos_printf ("0x%x ", ptr[J]);
		if(B == 8)
		{
			cortos_printf ("\n");
			B = 0;
		}
	}
}


void init_shared_memory()
{
	uint32_t J;
	uint8_t* ptr = (uint8_t*) &(test_array[0]);
	for(J = 0; J < (TEST_ARRAY_SIZE*8); J++)
	{
		ptr[J] = J;
	}
}

void my_external_interrupt_handler ()
{
	interrupt_counter++;

	// disable everything!
	write_to_accelerator_register(0,0);

	// make sure it is disabled, and set interrupt flag = 1.
	interrupt_flag = (1 - read_from_accelerator_register (0));	
}

void main () 
{
	
	init_shared_memory();

	// configure the accelerator with the key.
	write_to_accelerator_register (1, 0xffffffff);
	write_to_accelerator_register (2, 0xeeeeeeee);
	write_to_accelerator_register (3, 0xdddddddd);
	write_to_accelerator_register (4, 0xcccccccc);

	// address of block.
	write_to_accelerator_register (5, (uint32_t) (&(test_array[0])));
	// number of dwords.
	write_to_accelerator_register (6, TEST_ARRAY_SIZE);
	
	
	int I;
	for(I = 0; I < 7; I++)
	{
		cortos_printf("register [%d] = 0x%x\n",
					I,
					read_from_accelerator_register(I));
	}

	for(I = 0; I < 2; I++)
	{
		// enable the accelerator
		write_to_accelerator_register (0, 0x7);

		while(!interrupt_flag)
		{
		}

		interrupt_flag = 0;

		// flush the cache to ensure that there
		// is no residual.
		__ajit_flush_dcache__();

		dump_memory (I);
	}

	cortos_printf ("Done: interrupt_counter=%d.\n", interrupt_counter);
}



