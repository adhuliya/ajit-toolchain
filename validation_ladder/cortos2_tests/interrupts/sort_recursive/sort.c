#include <stdint.h>

#define VECTOR_SIZE  64
#define TIMERCOUNT 100
#define COUNT TIMERCOUNT
#define TIMERINITVAL ((COUNT << 1) | 1)
#define INTERRUPT_LIMIT 32

volatile int volatile timer_interrupt_counter = 0;

void setup_serial()
{
        __ajit_serial_configure_via_vmap__   (1, 0, 0);
}


void merge (int* GVAL, int m)
{
	int I;
	int V = GVAL[m];
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
void  sort(int *GVAL, int m)
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

	//ee_printf("Timer Intr!\n");

	// interrupt counter incremented.
	timer_interrupt_counter++;
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
	int VALUES[VECTOR_SIZE];

	for(I = 0; I < VECTOR_SIZE; I++)
	{
		VALUES[I] = VECTOR_SIZE - I;
	}

	int iterations = 0;
	while(1)
	{
		sort (VALUES, VECTOR_SIZE-1);
		if(timer_interrupt_counter >= INTERRUPT_LIMIT)
			break;
		else
		{
			cortos_printf("finished  %d interrupts, %d iterations\n", 
						timer_interrupt_counter, iterations);
			for(I = 0; I < VECTOR_SIZE; I++)
			{
				VALUES[I] = iterations + VECTOR_SIZE - I;
			}
		}
		iterations++;
	}

	for(I = 0; I < VECTOR_SIZE; I++)
	{
		cortos_printf("%d\n", VALUES[I]);
	}
}
