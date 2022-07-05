//Timer.c
//AUTHOR: Neha Karanjkar
//Updated: February 2016



//The timer consists of two concurrent threads :
//
//Thread 'Timer_Control' 
//	keeps monitoring requests from cpu
//	and performs reads/writes to device registers.
//
//Thread 'Timer_Output'
//	Generates timer interrupt by counting its input
//	clock ticks.
//
//Timer Control Word :
//		bit[0] = enable
//		bits[31:1] = max_count
//
//=========================
//TIMER STATE TRANSITION :
//==========================
//	The timer operates only in one-shot mode.
//	It can be in one of following states:
//
//	TIMER_DISABLED	:
//		The timer is in disabled state upon reset,
//		and its interrupt output value is 0.
//		When the cpu writes a
//		control word with bit[0]=1,
//		the count value is cleared and the timer moves
//		to TIMER_ENABLED state.
//	
//	TIMER_ENABLED :
//		When enabled, the timer keeps counting the
//		number of ticks produced by a periodic
//		tick source. The interrupt output is 0.
//		When the count reaches "max_count",
//		interrupt output is asserted , count is cleared
//		the timer moves to TIMER_INTERRUPTING state.
//
//		The delay produced by the timer from the point it is
//		enabled is given by :
//
//		Timer period = max_count/TIMER_TICK_REAL_FREQUENCY  
//		
//	TIMER_INTERRUPTING :
//		The timer stops counting, and the interrupt output
//		remains high, until the cpu explicitly disables
//		the timer by writing bit[0]=0 
//		into the control word register.

// 	
// 	Parameters TIMER_TICK_REAL_FREQUENCY, and 
// 	TIMER_TICK_VIRTUAL_FREQUENCY are
// 	defined in Ajit_Hardware_Configuration.h.
// 	TIMER_TICK_REAL_FREQUENCY (in Hz) is the real frequency,
// 	of the tick source connected to the timer.
// 	TIMER_TICK_VIRTUAL_FREQUENCY (in Hz) is the frequency 
// 	that the linux kernel thinks exists. We so this
// 	because simulation is about a 1000x slower than
//	real hardware



#include "default_peripheral_device_addresses.h"
#include "Ajit_Hardware_Configuration.h"
#include <unistd.h>
#include "Timer.h"
#include <stdlib.h>
#include <stdint.h>
#ifdef SW
#include <stdio.h>
#include <unistd.h>
#endif
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "RequestTypeValues.h"
#include "Ancillary.h"
#include "Device_utils.h"

//Main Timer thread
//which keeps monitoring 
//requests from cpu-side
void Timer_Control();
DEFINE_THREAD(Timer_Control);

//thread to generate timer output
//as per control word sent by cpu
void Timer_Output();
DEFINE_THREAD(Timer_Output);


//mutexes for locking Timer state variables
//so that only one thread can access it at a time
pthread_mutex_t Timer_lock = PTHREAD_MUTEX_INITIALIZER;

//Timer state variables
uint32_t Timer_Control_Register;
uint8_t  Timer_State;
uint8_t  Timer_INT_OUT;  //Current value of Timer interrupt pin
unsigned int Timer_count; //Register to keep count of number of ticks 
unsigned int Timer_max_count; //max count programmed by the cpu by writing the control word.

//The Timer can be in one of teh following states
//at any point in time:
#define TIMER_DISABLED	0
#define TIMER_ENABLED 	1
#define TIMER_INTERRUPTING 2
				

void initialize_Timer_State()
{
	//////////////////////////////////////
	pthread_mutex_lock(&Timer_lock);
	//////////////////////////////////////
	Timer_Control_Register=0;
	Timer_State = TIMER_DISABLED;
	Timer_INT_OUT=0;
	Timer_count=0;
	Timer_max_count=0;
	//////////////////////////////////////
	pthread_mutex_unlock(&Timer_lock);
	//////////////////////////////////////

	write_uint8("TIMER_to_IRC_INT",0);
}


//register pipes/ports used by the timer
void register_Timer_pipes()
{
	//signal going from Timer to IRC
	register_port("TIMER_to_IRC_INT",8,1);
	set_pipe_is_written_into("TIMER_to_IRC_INT");
	set_pipe_is_read_from("TIMER_to_IRC_INT");

	//pipes between system bus and the timer
	int depth = 1;
	register_pipe("peripheral_bridge_to_timer_request", depth,  64, 0);
	register_pipe("timer_to_peripheral_bridge_response", depth, 32, 0);

	set_pipe_is_read_from("peripheral_bridge_to_timer_request");
	set_pipe_is_written_into("timer_to_peripheral_bridge_response");
	
	set_pipe_is_read_from("BUS_to_TIMER_request_type");
	set_pipe_is_read_from("BUS_to_TIMER_addr");
	set_pipe_is_read_from("BUS_to_TIMER_data");
	
	set_pipe_is_written_into("BUS_to_TIMER_request_type");
	set_pipe_is_written_into("BUS_to_TIMER_addr");
	set_pipe_is_written_into("BUS_to_TIMER_data");
	
	register_pipe("TIMER_to_BUS_data", depth, 32, 0);
	set_pipe_is_written_into("TIMER_to_BUS_data");
	
	set_pipe_is_read_from("TIMER_to_BUS_data");
}

void start_timer_threads()
{
	register_Timer_pipes();
	initialize_Timer_State();
	PTHREAD_DECL(Timer_Control);
	PTHREAD_DECL(Timer_Output);
	PTHREAD_CREATE(Timer_Control);
	PTHREAD_CREATE(Timer_Output);

}



//Timer control thread
//which keeps monitoring read/write
//requests from cpu-side
void Timer_Control()
{
	uint32_t data_out=0;

	while(1)
	{
		//wait for a request from processor-side
		uint8_t rwbar, byte_mask;
		uint32_t addr, data_in;
		getPeripheralAccessCommand("peripheral_bridge_to_timer_request",
							&rwbar, &byte_mask, &addr, &data_in);
		if(rwbar)
		{
			//this is a register-read.
			//send response to cpu
			data_out = Timer_Control_Register;
		}
		else 
		{
			//lock the state variables
			pthread_mutex_lock(&Timer_lock);
			
			if(addr==(0xffffff & ADDR_TIMER_CONTROL_REGISTER))
			{
				//Cpu wants to update the control register
				Timer_Control_Register = insertUsingByteMask(Timer_Control_Register, 
											data_in, byte_mask);
			
				#ifdef DEBUG
				printf("\nTIMER: Control word 0x%x bmask 0x%x written. ",data_in, byte_mask);
				#endif


				if(getBit32(Timer_Control_Register,0)==0)
				{
					#ifdef DEBUG
					printf(" State = TIMER_DISABLED");
					printf(" Timer_count = 0x%x",Timer_count);
					printf(" Timer_max_count = 0x%x", Timer_max_count);
					#endif

					

					//Disable TIMER
					Timer_State = TIMER_DISABLED;
					//clear the interrupt line
					Timer_INT_OUT = 0;
					write_uint8("TIMER_to_IRC_INT",0);
					//clear timer count
					Timer_count=0;
					Timer_max_count=0;

				
				}
				else if (Timer_State==TIMER_DISABLED && getBit32(Timer_Control_Register,0)==1)
				{
					
					//Enable TIMER
					Timer_State = TIMER_ENABLED;
					//clear the interrupt line
					Timer_INT_OUT = 0;
					write_uint8("TIMER_to_IRC_INT",0);
					//clear count, and set max count
					Timer_count=0;
					Timer_max_count=getSlice32(Timer_Control_Register, 31,1);
					
					#ifdef DEBUG
					printf(" State = TIMER_ENABLED");
					printf(" Timer_count = 0x%x",Timer_count);
					printf(" Timer_max_count = 0x%x", Timer_max_count);
					#endif


				}
			
				data_out = 0;
			}

			//unlock state variables
			pthread_mutex_unlock(&Timer_lock);

		}
			
		//send ack to cpu
		sendPeripheralResponse("timer_to_peripheral_bridge_response", data_out);
			
	}//while(1)
}

void Timer_Output()
{
				
#ifdef DEBUG
	int number_of_interrupts = 0;
#endif 
	//
	// Timer tick period in microseconds
	//    Will loop every 10 milliseconds.
	//      Note: new C model runs 10X as fast.. make it 1 ms.
	//
	int TIMER_TICK_PERIOD = (int)1000000/(int)TIMER_TICK_REAL_FREQUENCY;

	while(1)
	{
		//lock state variables
		pthread_mutex_lock(&Timer_lock);

		if(Timer_State == TIMER_ENABLED)
		{
			//Timer is enabled.
			//Increment the count of clock ticks
			Timer_count =Timer_count +1;

			//Check if max count has been reached. 
			//If yes, the timer asserts an interrupt and
			//goes into interrupting state
			if(Timer_count >=Timer_max_count)
			{
				Timer_State = TIMER_INTERRUPTING;
				Timer_INT_OUT = TIMER_IRL;

				#ifdef DEBUG
				fprintf(stderr,"TIMER INTERRUPT (%d) SENT TO CPU\n", number_of_interrupts);
				fflush(stderr);
				number_of_interrupts++;
				#endif

				write_uint8("TIMER_to_IRC_INT", Timer_INT_OUT);
			}
		}
		else //(Timer_State == TIMER_INTERRUPTING or Timer_State == TIMER_DISABLED)
		{
			//do nothing

		}
		
		//unlock the state variables
		pthread_mutex_unlock(&Timer_lock);
			
		//Sleep and wake up on the next clock tick.
		usleep(TIMER_TICK_PERIOD);
	}//while(1)
}


//Routines used by other threads to send a request to, and 
//receive a response from the timer thread
//The timer interface supports only word access
void sendRequestToTimer(uint8_t request_type, uint32_t addr, uint32_t data32)
{
	write_uint8 ("BUS_to_TIMER_request_type", request_type);
	write_uint32("BUS_to_TIMER_addr",addr);
	write_uint32("BUS_to_TIMER_data",data32);
}

void readResponseFromTimer(uint32_t* data32)
{
	*data32 = read_uint32 ("TIMER_to_BUS_data");
}


