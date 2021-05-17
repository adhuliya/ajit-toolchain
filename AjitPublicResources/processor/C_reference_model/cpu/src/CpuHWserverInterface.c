//-------------------------------------------------------------------------
// Describes the cpu thread 
//-------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "SparcCore.h"
#include "Ancillary.h"
#include "CpuInterface.h"
#include "Pipes.h"
#include "CpuHWserverInterface.h"

static int CPU_HW_SERVER_ENABLED =0;
static int CPU_GDB_FLAG=0;
static int CPU_DOVAL_FLAG=0;

void cpu_enable_HW_server(int gdb_flag, int doval_flag)
{
	CPU_HW_SERVER_ENABLED=1;
	CPU_GDB_FLAG = gdb_flag;
	CPU_DOVAL_FLAG = doval_flag;
}

void cpu_disable_HW_server()
{
	CPU_HW_SERVER_ENABLED=0;
	CPU_GDB_FLAG=0;
	CPU_DOVAL_FLAG=0;
}

int cpu_hw_server_enabled()
{
	return CPU_HW_SERVER_ENABLED;
}
int cpu_gdb_flag()
{
	return CPU_GDB_FLAG;
}
int cpu_doval_flag()
{
	return CPU_DOVAL_FLAG;
}

//The adress argument is ignored for all message_types !=GDB_MEM_ACCESS
void inform_HW_server(uint8_t message_type, ProcessorState* s, uint32_t address)
{
	if(!cpu_hw_server_enabled()) return;

	if((message_type>=0 && message_type<=4) && cpu_gdb_flag())
	{

		// To stop the processor and make it wait for the first continue command.
		#ifdef GDB_DBG
		if(message_type==GDB_INITIAL_STOP) 	fprintf(stderr,"Info:ProcessorCore  : Initial stop\n");
		else if(message_type==GDB_RESET) 	fprintf(stderr,"Info:ProcessorCore  : Reset from execution\n");
		else if(message_type==GDB_IFETCH) 	fprintf(stderr,"Info:ProcessorCore  : Stopped ( instruction fetch ) at PC = %x\n", (s->status_reg).pc);
		else if(message_type==GDB_MEM_ACCESS) 	fprintf(stderr,"Info:ProcessorCore  : Stopped ( memory access ) at address = %x PC = %x\n", address, (s->status_reg).pc);
		else if(message_type==GDB_TRAP_OCCURED) fprintf(stderr,"Info:ProcessorCore  : Trap occured\n");
		else if(message_type==DOVAL_PROC_ENTERED_ERROR_MODE) fprintf(stderr,"Info:ProcessorCore  : Processor entered ERROR MODE at PC=0x%x\n ",(s->status_reg).pc);
		#endif

		write_uint8("CPU_to_HWSERVER_id",message_type);
		write_uint64("CPU_to_HWSERVER_state",(uint64_t)s);
		if(message_type==GDB_MEM_ACCESS) write_uint64("CPU_to_HWSERVER_state",(uint64_t)address);

		// Wait for a "CONT" message from the hardware server to continue
		uint32_t serv_rsp1 = read_uint32("HWSERVER_to_CPU");
		while ( serv_rsp1 != 0x434F4E54 ){ serv_rsp1 = read_uint32("HWSERVER_to_CPU");}

		#ifdef GDB_DBG
		if(message_type==GDB_INITIAL_STOP) 	 fprintf(stderr,"Info:ProcessorCore  : Continuing execution\n");
		else if (message_type==GDB_RESET)	 fprintf(stderr,"Info:ProcessorCore  : Continued after a Reset\n");
		else if (message_type==GDB_IFETCH)	 fprintf(stderr,"Info:ProcessorCore  : Continued after instruction fetch\n");
		else if (message_type==GDB_MEM_ACCESS) 	 fprintf(stderr,"Info:ProcessorCore  : Continued after memory access\n");
		else if (message_type==GDB_TRAP_OCCURED) fprintf(stderr,"Info:ProcessorCore  : Continued after a Trap\n");
		#endif
	}
	if((message_type==5) && cpu_doval_flag())
	{

		// To stop the processor and make it wait for the first continue command.
		if(message_type==DOVAL_PROC_ENTERED_ERROR_MODE) fprintf(stderr,"Info:ProcessorCore  : Processor entered ERROR MODE at PC=0x%x\n ",(s->status_reg).pc);
		write_uint8("CPU_to_HWSERVER_id",message_type);
		write_uint64("CPU_to_HWSERVER_state",(uint64_t)s);
		// Wait for a "CONT" message from the hardware server to continue
		uint32_t serv_rsp1 = read_uint32("HWSERVER_to_CPU");
		while ( serv_rsp1 != 0x434F4E54 ){ serv_rsp1 = read_uint32("HWSERVER_to_CPU");}

	}


}


