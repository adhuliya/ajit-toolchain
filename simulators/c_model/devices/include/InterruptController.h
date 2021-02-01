//InterruptController.h
//AUTHOR: Neha Karanjkar
//21 February 2016

#ifndef INTERRUPT_CONTROLLER_H
#define INTERRUPT_CONTROLLER_H
#include<stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"

//thread to monitor reads/writes from cpu to 
//device registers
void IRC_Control();

//thread to generate interrupt output
void IRC_Output();


//register pipes/signals used by the IRC 
void register_IRC_pipes();

//start thread
void start_IRC_threads();



//Routines used by cpu to read/write 
//IRQ registers.
void sendRequestToIRC(uint8_t request_type, uint32_t addr, uint32_t data_in);
void readResponseFromIRC(uint32_t* data_in);

#endif
