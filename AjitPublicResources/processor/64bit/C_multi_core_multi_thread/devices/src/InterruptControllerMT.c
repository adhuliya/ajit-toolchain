//Multi-thread ready interrupt controller.
// AUTHOR: Madhav Desai
//   Note: based on the single thread interrupt controller
//         originally written by Neha K.
//
// Defined in Ajit_Hardware_Configuration.h:
// Interrupt levels for interrupting sources in sparc
// #define TIMER_IRL  10
// #define SERIAL_IRL 12

//time in microsends for which the output 
//thread sleeps when there is no activity
#define IRC_DELTA_TIME 100 



#include "default_peripheral_device_addresses.h"
#include "Ajit_Hardware_Configuration.h"

#include "InterruptController.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
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
#include "InterruptControllerMT.h"

IrcMt irc_mt_state [MAX_NCORES][MAX_NTHREADS_PER_CORE];
pthread_t irc_mt_pthreads [MAX_NCORES][MAX_NTHREADS_PER_CORE];

//Upcomment the following to print debug
//message in interrupt controller
//#define IRC_DEBUG

DEFINE_THREAD_WITH_ARG(IrcMt_Control, virc);
DEFINE_THREAD_WITH_ARG(IrcMt_Output, virc);


uint32_t regIdOffset (uint32_t addr)
{
	uint32_t offset = ((0xfffff & addr) - (0xfffff & ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER))/4;
	return(offset);
}


void distributorDaemon ()
{
	char req_pipe_name[256];
	char resp_pipe_name[256];

	sprintf(req_pipe_name,  "peripheral_bridge_to_irc_mt_request");
	sprintf(resp_pipe_name, "irc_mt_to_peripheral_bridge_response");

	while(1)
	{
		uint8_t rwbar, byte_mask;
		uint32_t addr, data_in;
		getPeripheralAccessCommand("peripheral_bridge_to_irc_mt_request",
							&rwbar, &byte_mask, &addr, &data_in);

		uint32_t offset = regIdOffset(addr);

		uint32_t core_id   = offset / MAX_NTHREADS_PER_CORE;
		uint32_t thread_id = offset % MAX_NTHREADS_PER_CORE;

		sendPeripheralAccessCommand (irc_mt_state[core_id][thread_id].req_pipe_name,
							rwbar, byte_mask, addr, data_in);
		uint32_t resp = read_uint32(irc_mt_state[core_id][thread_id].resp_pipe_name);
		sendPeripheralResponse("irc_mt_to_peripheral_bridge_response", resp);
	}
}
DEFINE_THREAD(distributorDaemon);

			
uint16_t generateIV()
{
	uint8_t TIMER_INT    = read_uint8("TIMER_to_IRC_INT");
	uint8_t SERIAL_INT   = read_uint8("SERIAL_to_IRC_INT");
	uint8_t EXTERNAL_INT = read_uint8("EXTERNAL_INTERRUPT");

	uint16_t IV =  (((uint16_t) (TIMER_INT != 0)) << 10) |
		(((uint16_t) (SERIAL_INT != 0) ) << 12) |
		(((uint16_t) (EXTERNAL_INT != 0)) << 13);
	return(IV);
}

			
uint8_t  encodeInterrupt (uint16_t IV)
{
	uint8_t ret_val = 0;
	uint8_t I = 0;
	for(I = 1; I <= 15; I++)
	{
		if(IV & (0x1 << I))
		{
			ret_val = I;
			break;
		}
	}
	return(ret_val);
}

void initialize_IrcMt_state(IrcMt* irc)
{
	irc->control_register = 0x0;
	irc->state = sIRC_DISABLED;
	irc->irc_int_out = 0;

	pthread_mutex_init (&(irc->irc_lock), NULL);

	char pname[256];
	sprintf(pname,"ENV_to_THREAD_irl_%d_%d", irc->core_id, irc->thread_id);
	irc->ilvl_signal_name = strdup(pname);

	register_port(pname,8,1);
	set_pipe_is_written_into(pname);
	write_uint8(pname, irc->irc_int_out);

	int depth = 1;
	sprintf(pname, "peripheral_bridge_to_irc_mt_%d_%d_request", irc->core_id, irc->thread_id);
	irc->req_pipe_name = strdup(pname);
	register_pipe(pname, depth,  64, 0);

	sprintf(pname, "irc_mt_%d_%d_to_peripheral_bridge_response", irc->core_id, irc->thread_id);
	register_pipe(pname, depth, 32, 0);
	irc->resp_pipe_name = strdup(pname);
}



//
//
// register pipes/ports used by the InterruptController
//
void register_IrcMt_pipes()
{
	
	// signals coming from devices to the IRC
	// 
	register_port("TIMER_to_IRC_INT",8,1);
	register_port("SERIAL_to_IRC_INT",8,1);
	register_port("EXTERNAL_INTERRUPT",8,1);

	set_pipe_is_read_from("TIMER_to_IRC_INT");
	set_pipe_is_read_from("SERIAL_to_IRC_INT");
	set_pipe_is_read_from("EXTERNAL_INTERRUPT");
	

	//pipes between system bus and this device 
	//to read/write IRQ device registers
	int depth = 1;

	register_pipe("peripheral_bridge_to_irc_mt_request", depth,  64, 0);
	register_pipe("irc_mt_to_peripheral_bridge_response", depth, 32, 0);

	set_pipe_is_read_from("peripheral_bridge_to_irc_mt_request");
	set_pipe_is_written_into("irc_mt_to_peripheral_bridge_response");
}

void start_IrcMt_threads(int ncores, int nthreads_per_core)
{
	
	if(ncores > MAX_NCORES) 
	{
		fprintf(stderr,"Error:start_IrcMt_Threads: max number of cores is %d\n", MAX_NCORES);
		assert(0);
	}

	if(nthreads_per_core > MAX_NTHREADS_PER_CORE) 
	{
		fprintf(stderr,"Error:start_IrcMt_Threads: max number of threads is %d\n", MAX_NTHREADS_PER_CORE);
		assert(0);
	}

	register_IrcMt_pipes();


	int I,J;
	for(I=0; I < ncores; I++)
	{
		for(J=0; J < nthreads_per_core; J++)
		{
			irc_mt_state[I][J].core_id = I;
			irc_mt_state[I][J].thread_id = J;
			
			initialize_IrcMt_state (& (irc_mt_state[I][J]));			
			PTHREAD_DECL(IrcMt_Control);
			PTHREAD_DECL(IrcMt_Output);

			PTHREAD_CREATE_WITH_ARG(IrcMt_Control, ((void*) &(irc_mt_state[I][J])));
			PTHREAD_CREATE_WITH_ARG(IrcMt_Output, ((void*) &(irc_mt_state[I][J])));
		}
	}

	PTHREAD_DECL(distributorDaemon);
	PTHREAD_CREATE(distributorDaemon);
}



//IRC_Control thread
//keeps monitoring read/write
//requests from cpu-side
void IrcMt_Control(void* virc)
{
	IrcMt* irc = (IrcMt*) virc;
	uint32_t reg_id_offset = ((irc->core_id * MAX_NTHREADS_PER_CORE) + irc->thread_id);

	uint32_t data_out=0;
	
	while(1)
	{
		//wait for a request from processor-side
		uint8_t rwbar, byte_mask;
		uint32_t addr, data_in;
		getPeripheralAccessCommand(irc->req_pipe_name, &rwbar, &byte_mask, &addr, &data_in);

		//lock the state variables
		pthread_mutex_lock(&(irc->irc_lock));
		
		if(rwbar)
		{
			//this is a register-read.
			//send response to cpu
			data_out = irc->control_register;
		}
		else 
		{
			// bottom 24 bits of address are checked.
			if(regIdOffset(addr)  == reg_id_offset)
			{
				//Cpu wants to update the control register
				irc->control_register = insertUsingByteMask(irc->control_register, data_in, byte_mask);

				#ifdef IRC_DEBUG
				printf("\nINTERRUPT CONTROLLER (%d,%d): Control word 0x%x bmask 0x%x written. ",
						irc->core_id, irc->thread_id, data_in, byte_mask);
				#endif

				if(!(data_in & 0x1))
				{
					//Disable IRC
					irc->state = sIRC_DISABLED;
					//clear the interrupt line
					irc->irc_int_out = 0;

					// for the moment, all interrupts are directed
					// only to CPU-0.
					write_uint8(irc->ilvl_signal_name, irc->irc_int_out);
					
					#ifdef IRC_DEBUG
					printf(" State (%d,%d) = IRC_DISABLED", irc->core_id, irc->thread_id);
					#endif

				}
				else if (irc->state==sIRC_DISABLED && (data_in & 0x1))
				{
					//Enable IRC
					irc->state = sIRC_ENABLED;

					//clear the interrupt line
					irc->irc_int_out = 0;

					write_uint8(irc->ilvl_signal_name, irc->irc_int_out);
					
					#ifdef IRC_DEBUG
					printf(" State (%d,%d)= IRC_ENABLED", irc->core_id, irc->thread_id);
					#endif
	
				}
			}
			//send ack to cpu
			data_out = 0;
		}
		sendPeripheralResponse(irc->resp_pipe_name, data_out);

		//unlock state variables
		pthread_mutex_unlock(&(irc->irc_lock));
			
	}//while(1)
}


void IrcMt_Output(void* virc)
{
	IrcMt* irc = (IrcMt*) virc;

	while(1)
	{


		if(irc->state == sIRC_ENABLED)
		{
			//Interrupts are enabled, but not interrupt 
			//has been asserted yet.
			
			#ifdef IRC_DEBUG
				//Assert that the interrupt line is low
				if(irc->irc_int_out!=0)				
				printf("\nINTERRUPT CONTROLLER: WARNING! Interrupt line is high in IRC_ENABLED state");
			#endif


			//examine the interrupt sources
			uint16_t IV = generateIV();

			uint16_t masked_IV = (IV & (irc->control_register & 0xfffffffe));
			irc->irc_int_out = encodeInterrupt (masked_IV);


			if(irc->irc_int_out!=0)
			{
				//lock state variables
				pthread_mutex_lock(&(irc->irc_lock));

				//an interrupt has occured.
				//Signal this to the cpu,
				//and update state
				irc->state  = sIRC_INTERRUPTING;
				write_uint8(irc->ilvl_signal_name, irc->irc_int_out);

#ifdef IRC_DEBUG
				printf("\nINTERRUPT CONTROLLER: Generated interrupt to thread (%d,%d). INT = %d\n",  
						irc->core_id, irc->thread_id,
						irc->irc_int_out);
#endif

				//unlock the state variables
				pthread_mutex_unlock(&(irc->irc_lock));

			}


		}
		else //(IRC_State == IRC_INTERRUPTING or IRC_State == IRC_DISABLED)
		{


			//Do nothing.
			usleep(IRC_DELTA_TIME);
		}
	}//while(1)
}

