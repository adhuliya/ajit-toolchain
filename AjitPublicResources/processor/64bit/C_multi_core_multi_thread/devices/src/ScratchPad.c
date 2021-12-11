//scratch_pad.c
#include "default_peripheral_device_addresses.h"
#include "Ajit_Hardware_Configuration.h"
#include "ScratchPad.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "RequestTypeValues.h"
#include "Ancillary.h"
#include "Device_utils.h"

uint32_t scratch_pad_memory[32];

void scratch_pad_control();
DEFINE_THREAD(scratch_pad_control);
pthread_mutex_t sp_lock = PTHREAD_MUTEX_INITIALIZER;

void register_scratch_pad_pipes()
{
	//pipes between system bus and the timer
	int depth = 1;
	register_pipe("peripheral_bridge_to_scratch_pad_request", depth,  64, 0);
	register_pipe("scratch_pad_to_peripheral_bridge_response", depth, 32, 0);

	set_pipe_is_read_from("peripheral_bridge_to_scratch_pad_request");
	set_pipe_is_written_into("scratch_pad_to_peripheral_bridge_response");
}

void start_scratch_pad_threads()
{
	register_scratch_pad_pipes();
	PTHREAD_DECL(scratch_pad_control);
	PTHREAD_CREATE(scratch_pad_control);
}



void scratch_pad_control()
{

	uint32_t I;
	uint32_t data_out = 0;
	for(I = 0; I < 32; I++)
		scratch_pad_memory[I] = 0;

	while(1)
	{
		//wait for a request from processor-side
		uint8_t rwbar, byte_mask;
		uint32_t addr, data_in;
		getPeripheralAccessCommand("peripheral_bridge_to_scratch_pad_request",
							&rwbar, &byte_mask, &addr, &data_in);
		if(rwbar)
		{
			data_out = scratch_pad_memory[(addr & 0x7f) >> 2];
#ifdef DEBUGMODE
			fprintf(stderr,"Info: 0x%x = scratch_pad_memory[0x%x]\n",
						data_out, (addr & 0x7f) >> 2);
#endif
		}
		else 
		{
			//lock the state variables
			pthread_mutex_lock(&sp_lock);
			scratch_pad_memory[(addr & 0x7f) >> 2] = data_in;	
			pthread_mutex_unlock(&sp_lock);

#ifdef DEBUGMODE
			fprintf(stderr,"Info: scratch_pad_memory[0x%x] = 0x%x.\n",
						(addr & 0x7f) >> 2, data_in);
#endif

		}
			
		//send ack to cpu
		sendPeripheralResponse("scratch_pad_to_peripheral_bridge_response", data_out);
			
	}//while(1)
}
