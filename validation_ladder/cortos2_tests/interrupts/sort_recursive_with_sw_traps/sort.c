#include <stdint.h>
#include <cortos.h>
#include <ajit_access_routines.h>

#define VECTOR_SIZE  32
#define TIMERCOUNT 100000
#define COUNT TIMERCOUNT
#define TIMERINITVAL ((COUNT << 1) | 1)

volatile int volatile timer_interrupt_counter = 0;

void setup_serial()
{
        __ajit_serial_configure_via_vmap__   (1, 0, 0);
}


void merge (uint32_t* GVAL, int m)
{
	int I;
	uint32_t V = GVAL[m];
	for (I = 0; I < m; I++)
	{
		if(V < GVAL[I])
		{
			// shift  entries I to m-1 up by 1.
			int J;
			for (J = m; J > I ; J--)
			{
				GVAL[J] = GVAL[J-1];
			}
			GVAL[I] = V;
			break;
		}
	}
}


// sort items 0 1 ... m
void  sort(uint32_t *GVAL, int m)
{
	if(m > 0)
        {
	   sort  (GVAL, m-1);
	   merge (GVAL, m);
        }
}


void my_timer_interrupt_handler()
{
	// clear timer control register.
	__ajit_write_timer_control_register_via_vmap__ (0x0);

	// reenable the timer, right away..
	__ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	

	// interrupt counter incremented.
	timer_interrupt_counter++;
}

// The handler for sw trap 5.
void __t5_handler(uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
	*((uint32_t*) arg2) = __ajit_load_word_from_physical_address__((uint64_t) arg1);
	//cortos_printf("in __t5_handler(0x%x, 0x%x, 0x%x) = 0x%x\n", arg1, arg2, arg3, *((uint32_t*) arg2));
}

//
//
// This is the function you use to read a physical memory location 
//
void read_physical_memory (uint32_t address, uint32_t value_pointer)
{
	// create a trap.
	__AJIT_SW_TRAP(5);
}

void set_values(uint32_t* VALUES)
{
	int I;
	for(I = 0; I < VECTOR_SIZE; I++)
	{
		uint32_t v;
		read_physical_memory(0x40000000 + (I*4), (uint32_t) &v);
		VALUES[I] = v;
	}
}

int main()
{
	setup_serial();

	cortos_printf("Starting: enabling the interrupt controller.\n");

	// enable interrupt controller for the current thread.
	enableInterruptControllerAndAllInterrupts(0,0);

	// enable the timer, right away..
	__ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	

	int I;
	uint32_t VALUES[VECTOR_SIZE];

	set_values(VALUES);

	while(1)
	{
		sort (VALUES, VECTOR_SIZE-1);
		if(timer_interrupt_counter >= VECTOR_SIZE)
			break;
		else
		{
			cortos_printf("finished  %d interrupts.\n", timer_interrupt_counter);
			set_values(VALUES);
		}

	}

	for(I = 0; I < VECTOR_SIZE; I++)
	{
		cortos_printf("0x%x\n", VALUES[I]);
	}
}
