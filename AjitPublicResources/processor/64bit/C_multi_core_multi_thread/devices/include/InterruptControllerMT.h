//InterruptControllerMT.h
//AUTHOR: Madhav Desai

#ifndef INTERRUPT_CONTROLLER_MT_H
#define INTERRUPT_CONTROLLER_MT_H
#include<stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"

typedef enum __IrcState {
	sIRC_DISABLED,
	sIRC_ENABLED,
	sIRC_INTERRUPTING
} IrcState;

typedef struct __IrcMt {
	uint32_t control_register;
	IrcState state;

	char* req_pipe_name;
	char* resp_pipe_name;
	char* ilvl_signal_name;

	pthread_mutex_t irc_lock;


	uint8_t  core_id;
	uint8_t  thread_id;
	uint8_t  irc_int_out;
} IrcMt;


//thread to monitor reads/writes from cpu to 
//device registers
void IrcMt_Control(void* irc);

//thread to generate interrupt output
void IrcMt_Output(void* irc);


//register pipes/signals used by the IRC 
void register_IrcMt_pipes();

//start thread
void start_IrcMt_threads(int ncores, int nthreads_per_core);



//Routines used by cpu to read/write 
//IRQ registers.
void sendRequestToIrcMt(IrcMt* irc, uint8_t request_type, uint32_t addr, uint32_t data_in);
void readResponseFromIrcMt(IrcMt* irc, uint32_t* data_in);

#endif
