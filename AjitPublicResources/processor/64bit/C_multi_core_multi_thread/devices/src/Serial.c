//Serial.c
//
//AUTHOR: Neha Karanjkar, Aniket Deshmukh
//	March 2016
//
//
//Model for a serial device that supports :
//	polling-based output
//	both polling-based and interrupt-driven serial input


//THREADS :
//The Serial device consists of three concurrent threads :
//
//1. Thread 'Serial_Control' 
//	keeps monitoring requests from cpu
//	and performs reads/writes to device registers.
//
//
//2. Thread 'Serial_Tx'
//	Transmits out bytes sent by the cpu on the SERIAL_TX_to_CONSOLE pipe
//
//
//3. Thread 'Serial_Rx' 
//	Receives bytes from the environment on CONSOLE_to_SERIAL_RX pipe 
//	and maintains them in the Rx register for the cpu to read.
//
//	Interrupt mode :
//		If set up in the interrupt mode, (Rx_interrupt_enable==1),
//		the thread generates an interrupt to the cpu, when a 
//		byte is received on the CONSOLE_to_SERIAL_RX pipe.
//
//	Polling mode :
//		If Rx_interrupt_enable=0, the thread does not generate
//		an interrupt, and the cpu is expected to keep
//		polling the Rx_full bit to determine if a byte
//		has been received. 
//
//
//
//DEVICE REGISTERS :
//	There are three device registers :
//		1. Control Register (32b) 	(address = ADDR_SERIAL_CONTROL_REGISTER)
//		2. Tx register	    (8b)	(address = ADDR_SERIAL_TX_REGISTER)
//		3. Rx register	    (8b)	(address = ADDR_SERIAL_RX_REGISTER)
//
//CONTROL REGISTER :
//	The control register has the following fields:
//	bit[0] : Tx_enable   	(Transmitter enable)
//	bit[1] : Rx_enable   	(Receiver enable)
//	bit[2] : Rx_interrupt_enable 	(Receiver interrupt enable)
//	bit[3] : Tx_full 	(a value 1 indicates that the Tx register contains unsent data)
//	bit[4] : Rx_full  	(a value 1 indicates that the Rx register contains received data, yet to be read by the cpu)



//STATE TRANSITIONS
//*** See serial_device_specifications.pdf for state diagrams.***

//=========================
//TX STATE TRANSITION :
//==========================

//The transmit thread begins in the TX_DISABLED state:

//TX_DISABLED		:The transmit thread is in the disabled state and does not perform any action. Upon a
//			write to the control register with Tx_en set high, it goes to the TX_ENABLED state
//
//TX_ENABLED		:In this state, the thread waits for data to be written onto the transmit register. 
//			When data is written, the transmit thread goes to the TX_TRANSMITTING state. 
//			When the byte has been sent out to the SERIAL_TX_to_CONSOLE pipe, 
//			the thread goes back to TX_ENABLED state.
//
//TX_TRANSMITTING	:The thread writes the data in the transmit buffer to a pipe (blocking write). Therefore
//			the thread stays in this state till completion of the write. Upon completion, it sets 
//			Tx_full=0 and goes back to TX_ENABLED state


//=========================
//RX STATE TRANSITION :
//==========================

//The Rx thread begins in the RX_DISABLED state:

//RX_DISABLED           :The receive thread is in the disabled state and does not perform any action. Upon a
//                      write to the control register with RX_EN set high, it goes to the RX_ENABLED state
//
//RX_ENABLED            :In this state, the thread perform a blocking read from a pipe and stores the read value
//			in the receive buffer. It is assumed that given a finite amount of time, data will be 
//			available on the pipe. After receiving data, the thread goes into RX_DATA_RECEIVED state.
//
//RX_DATA_RECEIVED	: The Rx thread is waiting for the cpu to read data in the Rx register. 
//			In this state, if Rx_interrupt_enable ==1, the thread generates an interrupt on the SERIAL_to_IRC_INT line.
//			Else, the cpu is expected to keep polling Rx_full bit, to determine when the
//			received data is ready in Rx register to be read by the cpu.
//			
//			Upon a read from the Rx register, the Rx thread goes back to RX_ENABLED state.
//			Upon a control-word write with Rx_en=0, the thread goes into disabled state.
//



#include "default_peripheral_device_addresses.h"
#include "Ajit_Hardware_Configuration.h"
#include "Serial.h"
#include <assert.h>
#include <unistd.h>
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



//time in microseconds for which the Tx/Rx
//threads sleeps when there is no activity
#define SERIAL_DELTA_DELAY 10

//Uncomment the following for printing out
//debug messages about device activity
//#define SERIAL_DEBUG


//Thread declarations:

//Thread that monitors data written into and read from the control registers
void Serial_Control(void* vst);
DEFINE_THREAD_WITH_ARG(Serial_Control, vst);

//Thread that receives external data through a pipe and stores it in the receive buffer
void Serial_Rx(void* vst);
DEFINE_THREAD_WITH_ARG(Serial_Rx, vst);

//Thread that transmits data present in the transmit buffer through a pipe
void Serial_Tx(void* vst);
DEFINE_THREAD_WITH_ARG(Serial_Tx, vst);


//Possible states of Tx thread:
#define TX_DISABLED 0
#define TX_ENABLED  1
#define TX_TRANSMITTING 2 

//Possible states of Rx thread:
#define RX_DISABLED 0
#define RX_ENABLED  1
#define RX_DATA_RECEIVED 2

// Two devices..
SerialState serial_devs[2];

void initialize_serial(SerialState* st)
{
	st->Tx_enable=0;	
	st->Tx_full=0;	  
	st->Rx_enable=0;
	st->Rx_full=0;
	st->Rx_interrupt_enable=0;

	st->Rx_buffer=0x0;
	st->Tx_buffer=0;
	st->Rx_STATE=RX_DISABLED;
	st->Tx_STATE=TX_DISABLED;

	//initialize the interrupt output signal to 0
	if(st->device_id == 0)
	{
		st->SERIAL_INT_OUT = 0;
		write_uint8("SERIAL_to_IRC_INT", st->SERIAL_INT_OUT);				
	}
	pthread_mutex_init (&(st->Serial_lock), NULL);

	if(st->device_id == 0)
	{
		sprintf(st->peripheral_bridge_request, "peripheral_bridge_to_serial_request");
		sprintf(st->peripheral_bridge_response, "serial_to_peripheral_bridge_response");
		sprintf(st->to_console_pipe,"SERIAL_TX_to_CONSOLE");
		sprintf(st->from_console_pipe,"CONSOLE_to_SERIAL_RX");
	}
	else
	{
		sprintf(st->peripheral_bridge_request, "peripheral_bridge_to_serial_%d_request",
				st->device_id);
		sprintf(st->peripheral_bridge_response, "serial_%d_to_peripheral_bridge_response",
				st->device_id);
		sprintf(st->to_console_pipe,"SERIAL_%d_TX_to_CONSOLE", st->device_id);
		sprintf(st->from_console_pipe,"CONSOLE_to_SERIAL_%d_RX", st->device_id);

	}
}


//register pipes/ports used by the serial device
void register_serial_pipes(SerialState* st)
{
	int depth = 1;

	if(st->device_id == 0)
	{
		//signal going from Serial to IRC
		register_port("SERIAL_to_IRC_INT",8,1);
		set_pipe_is_written_into("SERIAL_to_IRC_INT");


		//pipes between the serial device and the console
		//(Keep a larger buffering for the console)
		depth=8;
		register_pipe("SERIAL_TX_to_CONSOLE", depth, 8, 0);
		set_pipe_is_written_into("SERIAL_TX_to_CONSOLE");
		set_pipe_is_read_from("SERIAL_TX_to_CONSOLE");

		register_pipe("SERIAL_1_TX_to_CONSOLE", depth, 8, 0);
		set_pipe_is_written_into("SERIAL_1_TX_to_CONSOLE");
		set_pipe_is_read_from("SERIAL_1_TX_to_CONSOLE");

		register_pipe("CONSOLE_to_SERIAL_RX", depth, 8, 0);
		set_pipe_is_written_into("CONSOLE_to_SERIAL_RX");
		set_pipe_is_read_from("CONSOLE_to_SERIAL_RX");

		register_pipe("CONSOLE_to_SERIAL_1_RX", depth, 8, 0);
		set_pipe_is_written_into("CONSOLE_to_SERIAL_1_RX");
		set_pipe_is_read_from("CONSOLE_to_SERIAL_1_RX");

		depth=1;
		register_pipe("peripheral_bridge_to_serial_request", depth,  64, 0);
		register_pipe("serial_to_peripheral_bridge_response", depth, 32, 0);

		set_pipe_is_read_from("peripheral_bridge_to_serial_request");
		set_pipe_is_written_into("serial_to_peripheral_bridge_response");
	}
	else if(st->device_id == 1)
	{
		//signal going from Serial to IRC
		register_port("SERIAL_1_to_IRC_INT",8,1);
		set_pipe_is_written_into("SERIAL_1_to_IRC_INT");


		//pipes between the serial device and the console
		//(Keep a larger buffering for the console)
		depth=8;
		register_pipe("SERIAL_1_TX_to_CONSOLE", depth, 8, 0);
		set_pipe_is_written_into("SERIAL_1_TX_to_CONSOLE");
		set_pipe_is_read_from("SERIAL_1_TX_to_CONSOLE");

		register_pipe("CONSOLE_to_SERIAL_1_RX", depth, 8, 0);
		set_pipe_is_written_into("CONSOLE_to_SERIAL_1_RX");
		set_pipe_is_read_from("CONSOLE_to_SERIAL_1_RX");

		depth=1;
		register_pipe("peripheral_bridge_to_serial_1_request", depth,  64, 0);
		register_pipe("serial_1_to_peripheral_bridge_response", depth, 32, 0);

		set_pipe_is_read_from("peripheral_bridge_to_serial_1_request");
		set_pipe_is_written_into("serial_1_to_peripheral_bridge_response");
	}
	else
	{
		fprintf(stderr,"Error: only 2 serial devices are supported.\n");
		assert(0);
	}
}

void start_serial_threads()
{

	int I;
	for(I = 0; I < 2; I++)
	{
		SerialState* st = &(serial_devs[I]);
		st->device_id = I;

		register_serial_pipes(st);
		initialize_serial(st);

		PTHREAD_DECL(Serial_Control);
		PTHREAD_DECL(Serial_Rx);
		PTHREAD_DECL(Serial_Tx);

		PTHREAD_CREATE_WITH_ARG(Serial_Control,st);
		PTHREAD_CREATE_WITH_ARG(Serial_Rx,st);
		PTHREAD_CREATE_WITH_ARG(Serial_Tx,st);
	}
}



//Control thread. Handles CPU requests
void Serial_Control(void* vst)
{
	SerialState* st = (SerialState*) vst;
	fprintf(stderr,"Info: created Serial_Control thread for Serial %d.\n", st->device_id);

	while(1)
	{
		//wait for a request from processor-side
		uint8_t rwbar, byte_mask;
		uint32_t addr, data_in;
		getPeripheralAccessCommand(st->peripheral_bridge_request,
				&rwbar, &byte_mask, &addr, &data_in);
		uint32_t data_out=0;

		int reg_id = (addr >> 2) & 0x7;

		if(!rwbar)
		{

			//***lock the state variables***
			pthread_mutex_lock(&(st->Serial_lock));

			if(reg_id == 0)
				// control register
			{
				uint32_t data_in_masked = insertUsingByteMask(0, data_in, byte_mask);

				//Cpu has written a new control word
				st->Tx_enable = getBit32(data_in_masked, 0);	
				st->Rx_enable = getBit32(data_in_masked, 1);
				st->Rx_interrupt_enable = getBit32(data_in_masked, 2);

				//Tx_ full and Rx_full are read only bits, 
				//and are updated upon reads/writes to Tx and Rx registers


				//update Tx state
				if(st->Tx_STATE==TX_DISABLED && st->Tx_enable==1) 
				{
					st->Tx_STATE = TX_ENABLED;
#ifdef SERIAL_DEBUG
					fprintf(stderr, "\nSERIAL %d TX: Changing state to TX_ENABLED\n",
							st->device_id);
#endif
				}
				else if(st->Tx_STATE==TX_ENABLED  && st->Tx_enable==0) 
				{
					st->Tx_STATE = TX_DISABLED;
					st->Tx_full=0;
#ifdef SERIAL_DEBUG
					fprintf(stderr, "\nSERIAL %d TX: Changing state to TX_DISABLED\n",
							st->device_id);
#endif
				}

				//Update Rx state
				if(st->Rx_STATE==RX_DISABLED && st->Rx_enable==1) 
				{
					st->Rx_STATE = RX_ENABLED;
					st->Rx_full=0;
#ifdef SERIAL_DEBUG
					fprintf(stderr,"\nSERIAL %d RX: Changing state to RX_ENABLED\n",
							st->device_id);
#endif
				}
				else if(st->Rx_STATE==RX_DATA_RECEIVED && st->Rx_enable==0) 
				{
					st->Rx_STATE = RX_DISABLED;
					st->Rx_full=0;
					st->Rx_buffer=0;

					//de-assert the interrupt
					if(st->device_id == 0)
					{
						st->SERIAL_INT_OUT = 0;
						write_uint8("SERIAL_to_IRC_INT", st->SERIAL_INT_OUT);
					}

#ifdef SERIAL_DEBUG
					fprintf(stderr, "\nSERIAL %d RX: Changing state to RX_DISABLED\n",
							st->device_id);
#endif
				}
			}
			else if(reg_id == 1)
			{

				if(st->Tx_STATE==TX_ENABLED)
				{				
					//
					//  write to Tx register: The address is word aligned, but
					//  Tx register is a byte.
					//
					if(byte_mask & 0x8)
					{
						st->Tx_buffer  = getSlice32(data_in, 31, 24);
					}
					else if (byte_mask & 0x4)
					{
						st->Tx_buffer  = getSlice32(data_in, 23, 16); 
					}
					else if (byte_mask & 0x2)
					{
						st->Tx_buffer  = getSlice32(data_in, 15,8);
					}
					else if(byte_mask & 0x1)
					{
						st->Tx_buffer  = getSlice32(data_in, 7,0);
					}
					else
					{
						fprintf(stderr,"Error: write to serial %d tx with byte-mask=0?\n",
								st->device_id);
					}

					st->Tx_full = 1;
					st->Tx_STATE = TX_TRANSMITTING;

#ifdef SERIAL_DEBUG
					fprintf(stderr, "\nSERIAL: data 0x%x written to Tx register\n", st->Tx_buffer);
#endif

				}
			}


			//***unlock the state variables***
			pthread_mutex_unlock(&(st->Serial_lock));

			//Send ack to the cpu
			data_out = 0;
		}
		else 
		{

			//***lock the state variables***
			pthread_mutex_lock(&(st->Serial_lock));

			if(reg_id == 0)
			{
				//Send the contents of control word to cpu
				data_out = ((uint32_t) st->Rx_full<<4 ) | 
					( (uint32_t) st->Tx_full<<3) | 
					((uint32_t) st->Rx_interrupt_enable<<2) | 
					((uint32_t) st->Rx_enable<<1) | 
					(uint32_t) st->Tx_enable;

			}
			else if(reg_id == 2)
			{				
				// The address is always assumed to be word aligned.  So the 
				// Rx buffer is placed at the most significant byte.
				if(byte_mask & 0x8)
				{
					data_out = setSlice32(0, 31,24,(uint32_t) st->Rx_buffer); 
				}
				else if(byte_mask & 0x4)
				{
					data_out = setSlice32(0, 23,16,(uint32_t) st->Rx_buffer); 
				}
				else if(byte_mask & 0x2)
				{
					data_out = setSlice32(0, 15,8,(uint32_t) st->Rx_buffer); 
				}
				else if(byte_mask & 0x1)
				{
					data_out = setSlice32(0, 7,0,(uint32_t) st->Rx_buffer); 
				}
				else
				{
					fprintf(stderr,"Error: serial %d read with byte-mask 0 for serial rx register?\n", st->device_id);
					data_out = 0x0;
				}

				if(st->Rx_STATE==RX_DATA_RECEIVED) 
				{
					st->Rx_STATE = RX_ENABLED;
					st->Rx_full = 0;
					if(st->device_id == 0)
					{
						//update the int pin
						st->SERIAL_INT_OUT=0;
						write_uint8("SERIAL_to_IRC_INT", st->SERIAL_INT_OUT);
					}
				}
#ifdef SERIAL_DEBUG
				fprintf(stderr,"\nSERIAL %d: data=0x%x received from Rx register\n", 
						st->device_id, data_out);
#endif


			}
			else if(reg_id == 1)
			{		
				// all register addresses are word-aligned!
				data_out = setSlice32(0, 31,24,(uint32_t) st->Tx_buffer);
			}

			//***unlock the state variables***
			pthread_mutex_unlock(&(st->Serial_lock));


		}
#ifdef SERIAL_DEBUG	
		fprintf(stderr, "\nSERIAL_CONTROL %d: Received request_type= ", st->device_id);

		if(rwbar==0x1) fprintf(stderr, "READ"); else fprintf(stderr, "WRITE");

		fprintf(stderr, ", addr=0x%x, data_in=0x%x, data_out=0x%x", addr,data_in,data_out);
#endif

		//send response to the cpu
		sendPeripheralResponse(st->peripheral_bridge_response, data_out);
	}	
}


//Transmit thread. Performs transmit only when Tx_enable is set.
//Is transmitting data when Tx_full is set.
void Serial_Tx(void* vst)
{
	SerialState* st = (SerialState*) vst;
	fprintf(stderr,"Info: created Serial_Tx thread for Serial %d.\n", st->device_id);

	//temporary variables
	uint8_t tx_state;

	while(1)
	{

		//***lock the state variables***
		pthread_mutex_lock(& st->Serial_lock);
		tx_state  = st->Tx_STATE;
		//***unlock the state variables***
		pthread_mutex_unlock(& st->Serial_lock);


		if(tx_state==TX_TRANSMITTING)
		{
			//transmit a byte
			write_uint8(st->to_console_pipe, st->Tx_buffer);


			//***lock the state variables***
			pthread_mutex_lock(& st->Serial_lock);
			//clear Tx_buffer, and de-assert Tx_full and Tx_enable
			st->Tx_full=0;
			st->Tx_STATE = TX_ENABLED;
			//***unlock the state variables***
			pthread_mutex_unlock(& st->Serial_lock);
		}
		else
		{
			//delta delay
			usleep(SERIAL_DELTA_DELAY);

		}

	}		
}


void Serial_Rx(void* vst)
{
	SerialState* st = (SerialState*) vst;
	fprintf(stderr,"Info: created Serial_Rx thread for Serial %d.\n", st->device_id);

	//temp variables
	uint8_t rx_state;
	uint8_t rx_data;
	uint8_t rx_interrupt_enable;

	while(1)
	{	

		//***lock state variables***
		pthread_mutex_lock(& st->Serial_lock);
		rx_state = st->Rx_STATE;
		rx_interrupt_enable = st->Rx_interrupt_enable;
		//***unlock state variables***
		pthread_mutex_unlock(& st->Serial_lock);

		if(rx_state==RX_ENABLED)
		{

			//wait for data on the Rx pipe
			rx_data = read_uint8(st->from_console_pipe);
#ifdef SERIAL_DEBUG
			fprintf(stderr,"\nSERIAL %d RX: character read on serial Rx line =%c\n",
					st->device_id, rx_data);
#endif

			//***lock state variables***
			pthread_mutex_lock(& st->Serial_lock);

#ifdef SERIAL_DEBUG
			fprintf(stderr,"\nSERIAL %d: Changing state to RX_DATA_RECEIVED\n",
					st->device_id);
#endif
			st->Rx_STATE = RX_DATA_RECEIVED;
			st->Rx_full=1;
			st->Rx_buffer=rx_data;


			//If Rx_interrupt_enable=1, we interrupt the cpu.
			if(rx_interrupt_enable && (st->device_id == 0))
			{
				st->SERIAL_INT_OUT = SERIAL_IRL;
				write_uint8("SERIAL_to_IRC_INT", st->SERIAL_INT_OUT);
			}
			//***unlock state variables***
			pthread_mutex_unlock(& st->Serial_lock);
		}	
		else
		{
			//delta delay
			usleep(SERIAL_DELTA_DELAY);
		}
	}
}


