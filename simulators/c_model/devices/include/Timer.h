//Timer.h
//AUTHOR: Neha Karanjkar

#ifndef TIMER_H
#define TIMER_H
#include<stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"

//Main Timer thread
//which keeps monitoring 
//requests from cpu-side
void Timer();

//thread to generate timer output
void TimerOutput();


//register pipes/signals used by the Timer 
void register_timer_pipes();

//start Timer thread
void start_timer_threads();


//Routines used by other threads to send a request to, and 
//receive a response from the timer thread
//The timer interface supports only word access
void sendRequestToTimer(uint8_t request_type, uint32_t addr, uint32_t data32);
void readResponseFromTimer(uint32_t* data32);
#endif
