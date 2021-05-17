
#ifndef __CPU_HW_SERVER_INTERFACE__
#define __CPU_HW_SERVER_INTERFACE__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "SparcCore.h"


//gdb-related rouines:
#define GDB_INITIAL_STOP 0
#define GDB_RESET	 1
#define GDB_IFETCH	 2
#define GDB_MEM_ACCESS	 3
#define GDB_TRAP_OCCURED 4
#define DOVAL_PROC_ENTERED_ERROR_MODE 5


void cpu_enable_HW_server(int gdb_flag, int doval_flag);
void cpu_disable_HW_server();
int cpu_hw_server_enabled();
int cpu_gdb_flag();
int cpu_doval_flag();

//The adress argument is ignored for all message_types !=GDB_MEM_ACCESS
void inform_HW_server(uint8_t message_type, ProcessorState* s, uint32_t address);

#endif
