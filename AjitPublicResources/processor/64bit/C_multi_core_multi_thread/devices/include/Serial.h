//AUTHOR: Aniket Deshmukh

#ifndef SERIAL_H
#define SERIAL_H
#include<stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"

typedef struct SerialState__ {
	uint8_t device_id;
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

	pthread_mutex_t Serial_lock;

	char peripheral_bridge_request[1024];
	char peripheral_bridge_response[1024];

	char to_console_pipe[1024];
	char from_console_pipe[1024];
	

} SerialState;

//Main Serial thread
//which keeps monitoring 
//requests from cpu-side
void Serial_Control(void* st);
void Serial_Recieve(void* st);
void Serial_Transmit(void* st);


//register pipes/signals used by the Serial device 
void register_serial_pipes(SerialState* st);

// start all serial threads...
void start_serial_threads();


//Routines used by other threads to send a request to, and 
//receive a response from the timer thread
//The timer interface supports only word access
void sendRequestToSerial(uint8_t dev_id, uint8_t request_type, uint32_t addr, uint32_t data32);
void readResponseFromSerial(uint8_t dev_id, uint32_t* data);
char readDisplayFromSerial(uint8_t dev_id);
void sendInputToSerial(uint8_t dev_id, char input);
#endif
