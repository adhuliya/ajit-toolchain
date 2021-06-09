//InterruptController.c
//AUTHOR: Neha Karanjkar
//21 February 2016

//The InterruptController consists of two threads :
//
//'IRC_Control' 
//	keeps monitoring requests from cpu.
//	and performs reads/writes to device registers
//
//
//'IRC_Output'
//	Generates interrupt output by reading the 
//	values on its input interrupt pins.
//	Selects the interrupt with highest priority,
//	encodes it into an 8-bit value and sends it 
//	to the cpu on the cpu's interrupt line
//	
//
//IRC state variables:
//	1. IRC_Control_Register :
//		Bit[0] is Enable bit. All other bits are currently ignored.
//	2. IRC_State :
//		State can be one of 
//			IRC_DISABLED, 
//			IRC_ENABLED, or 
//			IRC_INTERRUPTING
//	3. IRC_INT_OUT :
//		Current value of the interrupt signal going from 
//		the interrupt controller to the cpu
	
//Defined in Ajit_Hardware_Configuration.h:
//Interrupt levels for interrupting sources in sparc
//#define TIMER_IRL  0x10
//#define SERIAL_IRL 0x12

//time in microsends for which the output 
//thread sleeps when there is no activity
#define IRC_DELTA_TIME 100 



#include "Ajit_Hardware_Configuration.h"
#include "InterruptController.h"
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

//Upcomment the following to print debug
//message in interrupt controller
//#define IRC_DEBUG

//thread to monitor reads/writes from cpu to 
//device registers
void IRC_Control();
DEFINE_THREAD(IRC_Control);

//thread to generate interrupt output
void IRC_Output();
DEFINE_THREAD(IRC_Output);


//mutexes for locking state variables
//so that only one thread can access it at a time
pthread_mutex_t IRC_lock = PTHREAD_MUTEX_INITIALIZER;




//Possible states of the interrupt controller :
#define IRC_DISABLED		0
#define IRC_ENABLED		1
#define IRC_INTERRUPTING 	2

// state variables:
uint32_t IRC_Control_Register;
uint8_t  IRC_State;
uint8_t  IRC_INT_OUT;


void initialize_IRC_State()
{
	IRC_Control_Register=0;
	IRC_State = IRC_DISABLED;
	IRC_INT_OUT=0;
	set_pipe_is_written_into("ENV_to_CPU_irl");
	write_uint8("ENV_to_CPU_irl", IRC_INT_OUT);
}



//register pipes/ports used by the InterruptController
void register_IRC_pipes()
{
	//external interrupt signal to IRC
	register_port("ENV_to_AJIT_irl",8,1);
	set_pipe_is_read_from("ENV_to_AJIT_irl");

	// 
	// signal forwarded from IRC to CPU
	//
	register_port("ENV_to_CPU_irl",8,1);
	set_pipe_is_written_into("ENV_to_CPU_irl");
	
	//signals coming from devices to the IRC
	register_port("TIMER_to_IRC_INT",8,1);
	register_port("SERIAL_to_IRC_INT",8,1);
	
	set_pipe_is_read_from("TIMER_to_IRC_INT");
	set_pipe_is_read_from("SERIAL_to_IRC_INT");
	

	//pipes between system bus and this device 
	//to read/write IRQ device registers
	int depth = 1;
	register_pipe("BUS_to_IRC_request_type", depth, 8, 0);
	register_pipe("BUS_to_IRC_addr", depth, 32, 0);
	register_pipe("BUS_to_IRC_data", depth, 32, 0);
	
	set_pipe_is_read_from("BUS_to_IRC_request_type");
	set_pipe_is_read_from("BUS_to_IRC_addr");
	set_pipe_is_read_from("BUS_to_IRC_data");
	//memory access thread writes to these pipes
	set_pipe_is_written_into("BUS_to_IRC_request_type");
	set_pipe_is_written_into("BUS_to_IRC_addr");
	set_pipe_is_written_into("BUS_to_IRC_data");
	
	register_pipe("IRC_to_BUS_data", depth, 32, 0);
	set_pipe_is_written_into("IRC_to_BUS_data");
	set_pipe_is_read_from("IRC_to_BUS_data");
}

void start_IRC_threads()
{
	register_IRC_pipes();
	initialize_IRC_State();
	PTHREAD_DECL(IRC_Control);
	PTHREAD_DECL(IRC_Output);
	PTHREAD_CREATE(IRC_Control);
	PTHREAD_CREATE(IRC_Output);
}



//IRC_Control thread
//keeps monitoring read/write
//requests from cpu-side
void IRC_Control()
{
	uint8_t  request_type;
	uint32_t addr;
	uint32_t data_in=0;
	uint32_t data_out=0;
	
	while(1)
	{
		//wait for a request from processor-side
		request_type	= read_uint8 ("BUS_to_IRC_request_type");
		addr		= read_uint32("BUS_to_IRC_addr");
		data_in		= read_uint32("BUS_to_IRC_data");

		//lock the state variables
		pthread_mutex_lock(&IRC_lock);
		
		if(request_type==REQUEST_TYPE_READ)
		{
			//this is a register-read.
			//send response to cpu
			data_out = IRC_Control_Register;
			write_uint32("IRC_to_BUS_data",data_out);
		}
		else if (request_type==REQUEST_TYPE_WRITE)
		{
			
			if(addr==ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER)
			{
				//Cpu wants to update the control register
				IRC_Control_Register = data_in;
				#ifdef IRC_DEBUG
				printf("\nINTERRUPT CONTROLLER: Control word 0x%x written. ",data_in);
				#endif

				if(getBit32(data_in,0)==0)
				{
					//Disable IRC
					IRC_State = IRC_DISABLED;
					//clear the interrupt line
					IRC_INT_OUT = 0;
					write_uint8("ENV_to_CPU_irl",IRC_INT_OUT);
					
					#ifdef IRC_DEBUG
					printf(" State = IRC_DISABLED");
					#endif

				}
				else if (IRC_State==IRC_DISABLED && getBit32(data_in,0)==1)
				{
					//Enable IRC
					IRC_State = IRC_ENABLED;
					//clear the interrupt line
					IRC_INT_OUT = 0;
					write_uint8("ENV_to_CPU_irl",IRC_INT_OUT);
					
					#ifdef IRC_DEBUG
					printf(" State = IRC_ENABLED");
					#endif
	
				}


			}
			//send ack to cpu
			data_out = 0;
			write_uint32("IRC_to_BUS_data",data_out);
		}

		//unlock state variables
		pthread_mutex_unlock(&IRC_lock);
			
	}//while(1)
}


void IRC_Output()
{
	while(1)
	{
		//lock state variables
		pthread_mutex_lock(&IRC_lock);


		if(IRC_State == IRC_ENABLED)
		{
			//Interrupts are enabled, but not interrupt 
			//has been asserted yet.
			
			#ifdef IRC_DEBUG
				//Assert that the interrupt line is low
				if(IRC_INT_OUT!=0)				
				printf("\nINTERRUPT CONTROLLER: WARNING! Interrupt line is high in IRC_ENABLED state");
			#endif


			//examine the interrupt sources
			uint8_t TIMER_INT    = read_uint8("TIMER_to_IRC_INT");
			uint8_t SERIAL_INT   = read_uint8("SERIAL_to_IRC_INT");
			uint8_t EXTERNAL_INT = read_uint8("ENV_to_AJIT_irl");

			//Find out the highest priority interrupt
			if(TIMER_INT !=0) IRC_INT_OUT = TIMER_IRL;
			else if(SERIAL_INT !=0) IRC_INT_OUT = SERIAL_IRL;
			else if(EXTERNAL_INT !=0) IRC_INT_OUT = EXTERNAL_INT;
			else IRC_INT_OUT=0;

			if(IRC_INT_OUT!=0)
			{
				//an interrupt has occured.
				//Signal this to the cpu,
				//and update state
				IRC_State  = IRC_INTERRUPTING;
				write_uint8("ENV_to_CPU_irl", IRC_INT_OUT);
				
				#ifdef IRC_DEBUG
				printf("\nINTERRUPT CONTROLLER: Generated interrupt to processor. INT = %d\n", IRC_INT_OUT);
				#endif

			}
			
			//unlock the state variables
			pthread_mutex_unlock(&IRC_lock);

		}
		else //(IRC_State == IRC_INTERRUPTING or IRC_State == IRC_DISABLED)
		{
			
			//unlock the state variables
			pthread_mutex_unlock(&IRC_lock);

			//Do nothing.
			usleep(IRC_DELTA_TIME);
		}
	}//while(1)
}


//Routines used by cpu to read/write 
//IRQ registers.
//The interface supports only word accesses
void sendRequestToIRC(uint8_t request_type, uint32_t addr, uint32_t data_in)
{
	write_uint8 ("BUS_to_IRC_request_type", request_type);
	write_uint32("BUS_to_IRC_addr",addr);
	write_uint32("BUS_to_IRC_data",data_in);
}

void readResponseFromIRC(uint32_t* data_in)
{
	*data_in = read_uint32 ("IRC_to_BUS_data");
}


