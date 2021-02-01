//-------------------------------------------------------------------------
// The CPU needs to inform the HW server that is alive...
//-------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "SparcCore.h"
#include "Ancillary.h"
#include "CpuInterface.h"
#include "Pipes.h"
#include "hwServerStruct.h"
#include "CpuHWserverInterface.h"


void cpu_enable_HW_server(ProcessorState* cpu_state, int gdb_flag, int doval_flag)
{
	cpu_state->CPU_HW_SERVER_ENABLED=1;
	cpu_state->CPU_GDB_FLAG = gdb_flag;
	cpu_state->CPU_DOVAL_FLAG = doval_flag;
}

void cpu_disable_HW_server(ProcessorState* cpu_state)
{
	cpu_state->CPU_HW_SERVER_ENABLED=0;
	cpu_state->CPU_GDB_FLAG=0;
	cpu_state->CPU_DOVAL_FLAG=0;
}

int cpu_hw_server_enabled(ProcessorState* cpu_state)
{
	return cpu_state->CPU_HW_SERVER_ENABLED;
}
int cpu_gdb_flag(ProcessorState* cpu_state)
{
	return cpu_state->CPU_GDB_FLAG;
}
int cpu_doval_flag(ProcessorState* cpu_state)
{
	return cpu_state->CPU_DOVAL_FLAG;
}

//The address argument is ignored for all message_types !=GDB_MEM_ACCESS
void inform_HW_server(ProcessorState* s, uint8_t message_type,  uint32_t address)
{
	if(!cpu_hw_server_enabled(s)) 
				return;

	if((message_type>=0 && message_type<=4) && cpu_gdb_flag(s))
	{

		// To stop the processor and make it wait for the first continue command.
		#ifdef GDB_DBG
		if(message_type==GDB_INITIAL_STOP) 	fprintf(stderr,"Info:ProcessorCore  : Initial stop (cpu-id=%d)\n", s->cpu_id);
		else if(message_type==GDB_RESET) 	fprintf(stderr,"Info:ProcessorCore  : Reset from execution (cpu-id=%d)\n", s->cpu_id);
		else if(message_type==GDB_IFETCH) 	fprintf(stderr,"Info:ProcessorCore  : Stopped ( instruction fetch ) at PC = %x (cpu-id=%d)\n", (s->status_reg).pc, s->cpu_id);
		else if(message_type==GDB_MEM_ACCESS) 	fprintf(stderr,"Info:ProcessorCore  : Stopped ( memory access ) at address = %x PC = %x (cpu-id=%d)\n", address, (s->status_reg).pc, s->cpu_id);
		else if(message_type==GDB_TRAP_OCCURED) fprintf(stderr,"Info:ProcessorCore  : Trap occured\n");
		else if(message_type==DOVAL_PROC_ENTERED_ERROR_MODE) fprintf(stderr,"Info:ProcessorCore  : Processor %d entered ERROR MODE at PC=0x%x)\n ",s->cpu_id, (s->status_reg).pc);
		#endif

		write_uint8(s->hw_server->cpu_to_hwserver_id_pipe_name, message_type);
		write_uint64(s->hw_server->cpu_to_hwserver_state_pipe_name,(uint64_t)s);

		if(message_type==GDB_MEM_ACCESS) 
			write_uint64(s->hw_server->cpu_to_hwserver_state_pipe_name,(uint64_t)address);

		// Wait for a "CONT" message from the hardware server to continue
		uint32_t serv_rsp1 = read_uint32(s->hw_server->hwserver_to_cpu_pipe_name);
		while ( serv_rsp1 != 0x434F4E54 ){ serv_rsp1 = read_uint32(s->hw_server->hwserver_to_cpu_pipe_name);}

		#ifdef GDB_DBG
		if(message_type==GDB_INITIAL_STOP) 	 fprintf(stderr,"Info:ProcessorCore  : Continuing execution (cpu-id=%d)\n", s->cpu_id);
		else if (message_type==GDB_RESET)	 fprintf(stderr,"Info:ProcessorCore  : Continued after a Reset (cpu-id=%d)\n", s->cpu_id);
		else if (message_type==GDB_IFETCH)	 fprintf(stderr,"Info:ProcessorCore  : Continued after instruction fetch\n", s->cpu_id);
		else if (message_type==GDB_MEM_ACCESS) 	 fprintf(stderr,"Info:ProcessorCore  : Continued after memory access (cpu-id=%d)\n", s->cpu_id);
		else if (message_type==GDB_TRAP_OCCURED) fprintf(stderr,"Info:ProcessorCore  : Continued after a Trap (cpu-id=%d)\n", s->cpu_id);
		#endif
	}
	if((message_type==5) && cpu_doval_flag(s))
	{

		// To stop the processor and make it wait for the first continue command.
		if(message_type==DOVAL_PROC_ENTERED_ERROR_MODE) 
			fprintf(stderr,
				"Info:ProcessorCore  : Processor entered ERROR MODE at PC=0x%x (cpu-id=%d)\n ",(s->status_reg).pc, s->cpu_id);

		write_uint8(s->hw_server->cpu_to_hwserver_id_pipe_name,message_type);
		write_uint64(s->hw_server->cpu_to_hwserver_state_pipe_name,(uint64_t)s);
		// Wait for a "CONT" message from the hardware server to continue
		uint32_t serv_rsp1 = read_uint32(s->hw_server->hwserver_to_cpu_pipe_name);
		while ( serv_rsp1 != 0x434F4E54 ){ serv_rsp1 = read_uint32(s->hw_server->hwserver_to_cpu_pipe_name);}

	}


}


