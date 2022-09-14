#include <stdint.h>

#define VECTOR_SIZE  64
#define TIMERCOUNT 100000
#define COUNT TIMERCOUNT
#define TIMERINITVAL ((COUNT << 1) | 1)
#define INTERRUPT_LIMIT 1024

volatile int volatile timer_interrupt_counter[2] = {0, 0};

void setup()
{
        __ajit_serial_configure_via_vmap__   (1, 0, 0);
	cortos_printf("Starting: enabling the interrupt controller.\n");

	// enable interrupt controller for the two threads.
	// initially thread 0 takes the interrupt.
	enableInterruptController(0,0);
	enableInterrupt(0, 0, 10);

	enableInterruptController(0,1);


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

	uint8_t core_id, thread_id;
	ajit_get_core_and_thread_id(&core_id, &thread_id);


	// rotate timer interrupt..
	disableInterrupt(core_id, thread_id, 10);
	enableInterrupt (core_id, (1 - thread_id), 10);	

	// interrupt counter incremented.
	timer_interrupt_counter[thread_id] += 1;


	// reenable the timer, right away..
	__ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	

}


void core_routine(int thread_id)
{
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
		if(timer_interrupt_counter[thread_id] >= INTERRUPT_LIMIT)
			break;
		else
		{
			if((iterations % 64) == 0)
			{
				cortos_printf("Thread %d: finished  %d interrupts.\n", 
							thread_id,
							timer_interrupt_counter[thread_id]);

			}
			for(I = 0; I < VECTOR_SIZE; I++)
			{
				VALUES[I] = iterations + VECTOR_SIZE - I;
			}
		}
		iterations++;
	}

	cortos_printf("Thread %d finished %d iterations %d interrupts.\n", 
					thread_id, iterations, timer_interrupt_counter[thread_id]);

	for(I = 0; I < VECTOR_SIZE; I++)
	{
		cortos_printf("Thread %d: %d\n", thread_id, VALUES[I]);
	}
}

int main_00()
{
	__ajit_write_timer_control_register_via_vmap__ (TIMERINITVAL);	

	core_routine(0);
	return(0);
}

int main_01()
{
	core_routine(1);
	return(0);
}
