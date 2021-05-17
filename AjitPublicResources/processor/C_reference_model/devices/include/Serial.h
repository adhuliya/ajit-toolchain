//AUTHOR: Aniket Deshmukh

#ifndef SERIAL_H
#define SERIAL_H
#include<stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"

//Main Serial thread
//which keeps monitoring 
//requests from cpu-side
void Serial_Control();
void Serial_Recieve();
void Serial_Transmit();


//register pipes/signals used by the Serial device 
void register_serial_pipes();

//start Serial thread
void start_serial_threads();


//Routines used by other threads to send a request to, and 
//receive a response from the timer thread
//The timer interface supports only word access
void sendRequestToSerial(uint8_t request_type, uint32_t addr, uint32_t data32);
void readResponseFromSerial(uint32_t* data);
char readDisplayFromSerial();
void sendInputToSerial(char input);
#endif
