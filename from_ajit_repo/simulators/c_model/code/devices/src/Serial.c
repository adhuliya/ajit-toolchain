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


#include "Ajit_Hardware_Configuration.h"
#include "Serial.h"
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
void Serial_Control();
DEFINE_THREAD(Serial_Control);

//Thread that receives external data through a pipe and stores it in the receive buffer
void Serial_Rx();
DEFINE_THREAD(Serial_Rx);

//Thread that transmits data present in the transmit buffer through a pipe
void Serial_Tx();
DEFINE_THREAD(Serial_Tx);

//Mutex for locking state variables (only control register in this case)
pthread_mutex_t Serial_lock = PTHREAD_MUTEX_INITIALIZER;

//Control flags (inside control register)
uint8_t Tx_enable;	
uint8_t Tx_full;	  
uint8_t Rx_enable;
uint8_t Rx_full;
uint8_t Rx_interrupt_enable;
		
//Serial internal registers
uint8_t Rx_buffer;
uint8_t Tx_buffer;

//Value of interrupt signal going from serial device to the interrupt controller
uint8_t SERIAL_INT_OUT;

//State of Tx and Rx threads.
uint8_t Rx_STATE;
uint8_t Tx_STATE;

//Possible states of Tx thread:
#define TX_DISABLED 0
#define TX_ENABLED  1
#define TX_TRANSMITTING 2 

//Possible states of Rx thread:
#define RX_DISABLED 0
#define RX_ENABLED  1
#define RX_DATA_RECEIVED 2

void initialize_serial()
{
	Tx_enable=0;	
	Tx_full=0;	  
	Rx_enable=0;
	Rx_full=0;
	Rx_interrupt_enable=0;
  
	Rx_buffer=0x0;
	Tx_buffer=0;
  	Rx_STATE=RX_DISABLED;
	Tx_STATE=TX_DISABLED;

	//initialize the interrupt output signal to 0
	SERIAL_INT_OUT = 0;
	write_uint8("SERIAL_to_IRC_INT",SERIAL_INT_OUT);				
}


//register pipes/ports used by the serial device
void register_serial_pipes()
{
	int depth = 1;
  	//signal going from Serial to IRC
	register_port("SERIAL_to_IRC_INT",8,1);
	set_pipe_is_written_into("SERIAL_to_IRC_INT");


	//pipes between the serial device and the console
	//(Keep a larger buffering for the console)
	depth=8;
	register_pipe("SERIAL_TX_to_CONSOLE", depth, 8, 0);
	set_pipe_is_written_into("SERIAL_TX_to_CONSOLE");
	set_pipe_is_read_from("SERIAL_TX_to_CONSOLE");
	
	register_pipe("CONSOLE_to_SERIAL_RX", depth, 8, 0);
	set_pipe_is_written_into("CONSOLE_to_SERIAL_RX");
	set_pipe_is_read_from("CONSOLE_to_SERIAL_RX");

	depth=1;
	register_pipe("peripheral_bridge_to_serial_request", depth,  64, 0);
	register_pipe("serial_to_peripheral_bridge_response", depth, 32, 0);

	set_pipe_is_read_from("peripheral_bridge_to_serial_request");
	set_pipe_is_written_into("serial_to_peripheral_bridge_response");
}

void start_serial_threads()
{
	register_serial_pipes();
	initialize_serial();

	PTHREAD_DECL(Serial_Control);
	PTHREAD_DECL(Serial_Rx);
	PTHREAD_DECL(Serial_Tx);

	PTHREAD_CREATE(Serial_Control);
	PTHREAD_CREATE(Serial_Rx);
	PTHREAD_CREATE(Serial_Tx);
}

//Control thread. Handles CPU requests
void Serial_Control()
{

	while(1)
	{
		//wait for a request from processor-side
		uint8_t rwbar, byte_mask;
		uint32_t addr, data_in;
		getPeripheralAccessCommand("peripheral_bridge_to_serial_request",
							&rwbar, &byte_mask, &addr, &data_in);
		
		uint32_t data_out=0;
		if(!rwbar)
		{
			
			//***lock the state variables***
			pthread_mutex_lock(&Serial_lock);
			
			if(addr==(0xffffff & ADDR_SERIAL_CONTROL_REGISTER))
			{
				uint32_t data_in_masked = insertUsingByteMask(0, data_in, byte_mask);

				//Cpu has written a new control word
				Tx_enable = getBit32(data_in_masked, 0);	
        			Rx_enable = getBit32(data_in_masked, 1);
        			Rx_interrupt_enable = getBit32(data_in_masked, 2);

              			//Tx_ full and Rx_full are read only bits, 
				//and are updated upon reads/writes to Tx and Rx registers

				
				//update Tx state
				if(Tx_STATE==TX_DISABLED && Tx_enable==1) 
				{
					Tx_STATE = TX_ENABLED;
					#ifdef SERIAL_DEBUG
					fprintf(stderr, "\nSERIAL TX: Changing state to TX_ENABLED\n");
					#endif
				}
				else if(Tx_STATE==TX_ENABLED  && Tx_enable==0) 
				{
					Tx_STATE = TX_DISABLED;
					Tx_full=0;
					#ifdef SERIAL_DEBUG
					fprintf(stderr, "\nSERIAL TX: Changing state to TX_DISABLED\n");
					#endif
				}
				
				//Update Rx state
				if(Rx_STATE==RX_DISABLED && Rx_enable==1) 
				{
					Rx_STATE = RX_ENABLED;
					Rx_full=0;
					#ifdef SERIAL_DEBUG
					fprintf(stderr,"\nSERIAL RX: Changing state to RX_ENABLED\n");
					#endif
				}
				else if(Rx_STATE==RX_DATA_RECEIVED && Rx_enable==0) 
				{
					Rx_STATE = RX_DISABLED;
					Rx_full=0;
					Rx_buffer=0;
					//de-assert the interrupt
					SERIAL_INT_OUT = 0;
					write_uint8("SERIAL_to_IRC_INT", SERIAL_INT_OUT);
					
					#ifdef SERIAL_DEBUG
					fprintf(stderr, "\nSERIAL RX: Changing state to RX_DISABLED\n");
					#endif
				}
			}
			else if(addr== (0xffffff & ADDR_SERIAL_TX_REGISTER))
			{

				if(Tx_STATE==TX_ENABLED)
				{				
					//
					//  write to Tx register: The address is word aligned, but
					//  Tx register is a byte.
					//
					switch(byte_mask)
					{
						case 8 : {Tx_buffer  = getSlice32(data_in, 31, 24); break;}
						default:
							fprintf(stderr,"Error: write to serial tx must be to a word-aligned byte\n");
							break;
					}
					Tx_full = 1;
					Tx_STATE = TX_TRANSMITTING;

					#ifdef SERIAL_DEBUG
					fprintf(stderr, "\nSERIAL: data 0x%x written to Tx register\n",Tx_buffer);
					#endif

				}
			}

			
			//***unlock the state variables***
			pthread_mutex_unlock(&Serial_lock);
			
			//Send ack to the cpu
      			data_out = 0;
		}
		else 
		{
      			
			//***lock the state variables***
			pthread_mutex_lock(&Serial_lock);
			
			if(addr== (0xffffff & ADDR_SERIAL_CONTROL_REGISTER))
			{
				//Send the contents of control word to cpu
				data_out = ((uint32_t)Rx_full<<4 ) | ( (uint32_t)Tx_full<<3) | ((uint32_t)Rx_interrupt_enable<<2) | ((uint32_t)Rx_enable<<1) | (uint32_t)Tx_enable;
			
			}
			else if(addr==(0xffffff & ADDR_SERIAL_RX_REGISTER))
			{				
				// The address is always assumed to be word aligned.  So the 
				// Rx buffer is placed at the most significant byte.
				switch(byte_mask)
				{
					case 8 : {data_out = setSlice32(0, 31,24,(uint32_t)Rx_buffer); break;}
					default:
						fprintf(stderr,"Error: read is not a word-aligned byte for serial rx register\n");
				}
				if(Rx_STATE==RX_DATA_RECEIVED) 
				{
					Rx_STATE = RX_ENABLED;
					Rx_full = 0;
					//update the int pin
					SERIAL_INT_OUT=0;
					write_uint8("SERIAL_to_IRC_INT", SERIAL_INT_OUT);
				}
				#ifdef SERIAL_DEBUG
				fprintf(stderr,"\nSERIAL: data=0x%x received from Rx register\n",data_out);
				#endif

			
			}
      			else if(addr==(0xffffff & ADDR_SERIAL_TX_REGISTER))
			{		
        			//choose a byte in the 32b data line
				//to place Tx contents, depending on its address
				switch(ADDR_SERIAL_TX_REGISTER%4)
				{
					case 0 : {data_out = setSlice32(0, 31,24,(uint32_t)Tx_buffer); break;}
					case 1 : {data_out = setSlice32(0, 23,16,(uint32_t)Tx_buffer); break;}
					case 2 : {data_out = setSlice32(0, 15, 8,(uint32_t)Tx_buffer); break;}
					case 3 : {data_out = setSlice32(0,  7, 0,(uint32_t)Tx_buffer); break;}
				}

			}
		
			//***unlock the state variables***
			pthread_mutex_unlock(&Serial_lock);
		

		}
#ifdef SERIAL_DEBUG	
		fprintf(stderr, "\nSERIAL_CONTROL: Received request_type= ");

		if(request_type==0x1) fprintf(stderr, "READ"); else fprintf(stderr, "WRITE");

		fprintf(stderr, ", addr=0x%x, data_in=0x%x, data_out=0x%x", addr,data_in,data_out);
#endif

		//send response to the cpu
		sendPeripheralResponse("serial_to_peripheral_bridge_response", data_out);
	}	
}


//Transmit thread. Performs transmit only when Tx_enable is set.
//Is transmitting data when Tx_full is set.
void Serial_Tx()
{
	//temporary variables
	uint8_t tx_state;

	while(1)
	{

		//***lock the state variables***
		pthread_mutex_lock(&Serial_lock);
		tx_state  =Tx_STATE;
		//***unlock the state variables***
		pthread_mutex_unlock(&Serial_lock);


		if(tx_state==TX_TRANSMITTING)
		{
			//transmit a byte
			write_uint8("SERIAL_TX_to_CONSOLE", Tx_buffer);


			//***lock the state variables***
			pthread_mutex_lock(&Serial_lock);
			//clear Tx_buffer, and de-assert Tx_full and Tx_enable
			Tx_full=0;
			Tx_STATE = TX_ENABLED;
			//***unlock the state variables***
			pthread_mutex_unlock(&Serial_lock);
		}
		else
		{
			//delta delay
			usleep(SERIAL_DELTA_DELAY);

		}

	}		
}


void Serial_Rx()
{
	//temp variables
	uint8_t rx_state;
	uint8_t rx_data;
	uint8_t rx_interrupt_enable;

	while(1)
	{	

		//***lock state variables***
		pthread_mutex_lock(&Serial_lock);
		rx_state = Rx_STATE;
		rx_interrupt_enable = Rx_interrupt_enable;
		//***unlock state variables***
		pthread_mutex_unlock(&Serial_lock);

		if(rx_state==RX_ENABLED)
		{

			//wait for data on the Rx pipe
			rx_data = read_uint8("CONSOLE_to_SERIAL_RX");
#ifdef SERIAL_DEBUG
			fprintf(stderr,"\nSERIAL RX: character read on serial Rx line =%c\n",rx_data);
#endif

			//***lock state variables***
			pthread_mutex_lock(&Serial_lock);

#ifdef SERIAL_DEBUG
			fprintf(stderr,"\nSERIAL : Changing state to RX_DATA_RECEIVED\n");
#endif
			Rx_STATE = RX_DATA_RECEIVED;
			Rx_full=1;
			Rx_buffer=rx_data;


			//If Rx_interrupt_enable=1, we interrupt the cpu.
			if(rx_interrupt_enable)
			{
				SERIAL_INT_OUT = SERIAL_IRL;
				write_uint8("SERIAL_to_IRC_INT", SERIAL_INT_OUT);
			}
			//***unlock state variables***
			pthread_mutex_unlock(&Serial_lock);
		}	
		else
		{
			//delta delay
			usleep(SERIAL_DELTA_DELAY);
		}
	}
}



//Routines used by other threads to send a request to, and 
//receive a response from the serial thread
void sendRequestToSerial(uint8_t request_type, uint32_t addr, uint32_t data32)
{
	write_uint8 ("BUS_to_SERIAL_request_type", request_type);
  	write_uint32("BUS_to_SERIAL_addr",addr);
	write_uint32("BUS_to_SERIAL_data",data32);
	
}

void readResponseFromSerial(uint32_t* data)
{
	*data = read_uint32("SERIAL_to_BUS_data");
}



