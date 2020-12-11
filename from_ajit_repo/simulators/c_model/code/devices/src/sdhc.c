/*	SDHC.c

AUTHORS: Saurabh Bansode, Vishnu Easwaran E

last modified: 10 Dec 2020 

Model that emulates a version 3.00 SD Host Controller
and an SD card for verification purposes.

Device Registers:
	SDHC registers, SD registers & flash memory
	 are defined in Sdhc.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#ifdef SW
#include <stdio.h>
#include <unistd.h>
#endif
#include <pthread.h>
#include "Ancillary.h"

// base address of SDHC register set is defined here.
#include "Ajit_Hardware_Configuration.h"

#include "Sdhc.h"
#include "sd.h"
#include "RequestTypeValues.h"
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"

uint32_t sdhc_tx_buffer;
uint32_t sdhc_rx_buffer;
//stores the potential address differences' values
uint32_t AddrDiffArray[33]={0,4,6,8,12,14,16,32,36,40,41,42,43,44,46,47,48,50,52,54,56,58,60,62,64,72,96,254}; 
// Address to SDHC will be base + index.
// The index points to the appropriate register.

uint32_t sdhc_register_array[32];
uint32_t *addr_sdhc_array=&sdhc_register_array[32]; //base address

// **** Thread declarations ******//
void SDHC_Control();
DEFINE_THREAD(SDHC_Control);

//Mutex for locking state variables (only control register in this case)
pthread_mutex_t Sdhc_lock = PTHREAD_MUTEX_INITIALIZER;

void sdhc_initialize()
{
	sdhc_tx_buffer=0;
	sdhc_rx_buffer=0;
}


void register_sdhc_pipes()
{
	  	//signal going from SDHC to IRC
	register_port("SDHC_to_IRC_INT",8,1);
	set_pipe_is_written_into("SDHC_to_IRC_INT");

	//pipes between system bus and SDHC device
	int depth=1;
	register_pipe("BUS_to_SDHC_request_type", depth, 8, 0);
	register_pipe("BUS_to_SDHC_addr", depth, 32, 0);  
	register_pipe("BUS_to_SDHC_data",depth,32,0);	
	register_pipe("BUS_to_SDHC_byte_mask",depth,8,0); // you will need a byte mask.
	register_pipe("SDHC_to_BUS_data", depth, 32, 0);	
	
	set_pipe_is_read_from("BUS_to_SDHC_request_type");
	set_pipe_is_read_from("BUS_to_SDHC_addr");
	set_pipe_is_read_from("BUS_to_SDHC_data");
	set_pipe_is_read_from("BUS_to_SDHC_byte_mask");
	set_pipe_is_read_from("SDHC_to_BUS_data");

	set_pipe_is_written_into("BUS_to_SDHC_request_type");
	set_pipe_is_written_into("BUS_to_SDHC_addr");
	set_pipe_is_written_into("BUS_to_SDHC_data");
	set_pipe_is_written_into("BUS_to_SDHC_byte_mask");
	set_pipe_is_written_into("SDHC_to_BUS_addr");
}

void start_sdhc_threads()
{
	sdhc_initialize();
	register_sdhc_pipes();

	PTHREAD_DECL(SDHC_Control);
	PTHREAD_CREATE(SDHC_Control);
}

uint32_t mapAddrDiffToSDHCRegArrayIndex(uint32_t AddrDiffFromUpdateRegFunction)
{
	uint32_t comp=0;
	for(uint32_t i=0;i<33;i++)
        {
		uint32_t cmp_var = AddrDiffArray[i];
            	if(cmp_var==AddrDiffFromUpdateRegFunction)
        	{
			comp=i;
			break;
		}
		else
		{
			comp=0;
		}
         }
		return comp;
}

uint32_t calculateNewValue(index, byte_mask, data_in)
{ 
	uint32_t return_data=sdhc_register_array[index];
	return_data = data_in & byte_mask; 
	return return_data;
}

uint32_t calculateNewValueMask(byte_mask)
{

}

// Bridge will generate the request.. called in the bridge.
void sendRequestToSDHC(uint8_t request_type, uint32_t addr, uint32_t byte_mask, uint32_t data32)
{
	write_uint8 ("BUS_to_SDHC_request_type", request_type);
	write_uint8 ("BUS_to_SDHC_byte_mask", byte_mask);
	write_uint32("BUS_to_SDHC_addr",addr);
	write_uint32 ("BUS_to_SDHC_data",data32); 
}

void updateRegister(uint32_t index, uint8_t byte_mask, uint32_t data_in)
{	
	index=mapAddrDiffToSDHCRegArrayIndex(index);
		// calculate the new value of register at index index.
	uint32_t updated_value = calculateNewValue(index, byte_mask, data_in);
	uint32_t updated_mask  = calculateNewValueMask(byte_mask);//?
	sdhc_register_array[index] = (sdhc_register_array[index] & (~byte_mask)) | (updated_value & updated_mask);
	sdhc_tx_buffer = sdhc_register_array[index];//load the updated value in a pipe
}

void readFromRegisterArray(uint32_t index,uint8_t byte_mask)
{
	uint32_t readValue = sdhc_register_array[index];
	readValue = readValue & byte_mask;
	sdhc_rx_buffer = readValue;
}

// called in the bridge.
void readResponseFromSDHC(uint32_t* data)
{
	*data = read_uint32("SDHC_to_BUS_data");
}

void SDHC_Control()
{
	uint8_t  request_type;
	uint8_t  byte_mask;
	uint32_t addr;
	uint32_t data_in=0;
	uint32_t data_out=0;
	
	addr_sdhc_array[0]=ADDR_SDHC_ARG_2;
	uint32_t BASE_ADDR=addr_sdhc_array[0];
while(1)
{
		//wait for a request from processor-side
	request_type = read_uint8("BUS_to_SDHC_request_type");
	byte_mask = read_uint8("BUS_to_SDHC_byte_mask");
	addr = read_uint32("BUS_to_SDHC_addr");
	data_in	= read_uint32("BUS_to_SDHC_data");
	
	uint32_t index = addr - BASE_ADDR; //calculate address of the array element in sdhc_register_array
	if(request_type==REQUEST_TYPE_WRITE)
	{
		//***lock the state variables***//
	pthread_mutex_lock(&Sdhc_lock);
	sdhc_tx_buffer=0;
		// some writes may be special, some may be just
		// modifications to registers.

		// calculate the action to be performed and potentially
		// update the register.
	updateRegister(index, byte_mask, data_in);
	pthread_mutex_unlock(&Sdhc_lock);
	write_uint32("BUS_to_SDHC_data",sdhc_tx_buffer);
	}
	else if(request_type==REQUEST_TYPE_READ)
	{
	//***lock the state variables***//
	pthread_mutex_lock(&Sdhc_lock);
	sdhc_rx_buffer=0;
	readFromRegisterArray(index, byte_mask);
	pthread_mutex_unlock(&Sdhc_lock);
	write_uint32("SDHC_to_BUS_data", sdhc_rx_buffer);
	}
}



}
