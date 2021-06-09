
#ifndef __THREAD_HW_SERVER_INTERFACE__
#define __THREAD_HW_SERVER_INTERFACE__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "AjitThread.h"
#include "hwServer.h"


//gdb-related rouines:
#define GDB_INITIAL_STOP 0
#define GDB_RESET	 1
#define GDB_IFETCH	 2
#define GDB_MEM_ACCESS	 3
#define GDB_TRAP_OCCURED 4
#define DOVAL_PROC_ENTERED_ERROR_MODE 5


void thread_enable_HW_server(ThreadState* thread_state, int gdb_flag, int doval_flag);
void thread_disable_HW_server(ThreadState* thread_state);
int thread_hw_server_enabled(ThreadState* thread_state);
int thread_gdb_flag(ThreadState* thread_state);
int thread_doval_flag(ThreadState* thread_state);

//The adress argument is ignored for all message_types !=GDB_MEM_ACCESS
void inform_HW_server(ThreadState* s, uint8_t message_type,  uint32_t address);

#endif
