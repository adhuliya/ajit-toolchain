//-------------------------------------------------------------------------
// The CPU needs to inform the HW server that is alive...
//-------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "AjitThread.h"
#include "Ancillary.h"
#include "ThreadInterface.h"
#include "Pipes.h"
#include "hwServerStruct.h"
#include "ThreadHWserverInterface.h"




void thread_enable_HW_server(ThreadState* thread_state, int gdb_flag, int doval_flag)
{
	thread_state->THREAD_HW_SERVER_ENABLED=1;
	thread_state->THREAD_GDB_FLAG = gdb_flag;
	thread_state->THREAD_DOVAL_FLAG = doval_flag;
}

void thread_disable_HW_server(ThreadState* thread_state)
{
	thread_state->THREAD_HW_SERVER_ENABLED=0;
	thread_state->THREAD_GDB_FLAG=0;
	thread_state->THREAD_DOVAL_FLAG=0;
}

int thread_hw_server_enabled(ThreadState* thread_state)
{
	return thread_state->THREAD_HW_SERVER_ENABLED;
}
int thread_gdb_flag(ThreadState* thread_state)
{
	return thread_state->THREAD_GDB_FLAG;
}
int thread_doval_flag(ThreadState* thread_state)
{
	return thread_state->THREAD_DOVAL_FLAG;
}

//The address argument is ignored for all message_types !=GDB_MEM_ACCESS
void inform_HW_server(ThreadState* s, uint8_t message_type,  uint32_t address)
{
	if(!thread_hw_server_enabled(s)) 
				return;

	if((message_type>=0 && message_type<=4) && thread_gdb_flag(s))
	{

		// To stop the processor and make it wait for the first continue command.
		#ifdef GDB_DBG
		if(message_type==GDB_INITIAL_STOP) 	
			fprintf(stderr,"Info:Thread  : Initial stop thread=%d, core=%d\n", s->thread_id, s->core_id);
		else if(message_type==GDB_RESET) 	
			fprintf(stderr,"Info:Thread  : Reset from execution thread=%d, core=%d\n", s->thread_id, s->core_id);
		else if(message_type==GDB_IFETCH) 	
			fprintf(stderr,"Info:Thread  : Stopped ( instruction fetch ) at PC = %x %s\n", 
					(s->status_reg).pc, s->thread_id, s->core_id);
		else if(message_type==GDB_MEM_ACCESS) 	
			fprintf(stderr,"Info:Thread  : Stopped ( memory access ) at address = %x PC = %x thread=%d, core=%d\n", s->thread_id, s->core_id);
		else if(message_type==GDB_TRAP_OCCURED) 
			fprintf(stderr,"Info:Thread  : Trap occured thread=%d, core=%d\n", s->thread_id, s->core_id);
		else if(message_type==DOVAL_PROC_ENTERED_ERROR_MODE) 
			fprintf(stderr,"Info:Thread  : Thread %d entered ERROR MODE at PC=0x%x) thread=%d, core=%d\n ",
					s->thread_id, s->core_id, (s->status_reg).pc);
		#endif

		write_uint8(s->hw_server->thread_to_hwserver_id_pipe_name, message_type);
		write_uint64(s->hw_server->thread_to_hwserver_state_pipe_name,(uint64_t)s);

		if(message_type==GDB_MEM_ACCESS) 
			write_uint64(s->hw_server->thread_to_hwserver_state_pipe_name,(uint64_t)address);

		// Wait for a "CONT" message from the hardware server to continue
		uint32_t serv_rsp1 = read_uint32(s->hw_server->hwserver_to_thread_pipe_name);
		while ( serv_rsp1 != 0x434F4E54 ){ serv_rsp1 = read_uint32(s->hw_server->hwserver_to_thread_pipe_name);}

		#ifdef GDB_DBG
		if(message_type==GDB_INITIAL_STOP) 	 fprintf(stderr,"Info:Thread  : Continuing execution (cpu-id=%d)\n", s->thread_id);
		else if (message_type==GDB_RESET)	 fprintf(stderr,"Info:Thread  : Continued after a Reset (cpu-id=%d)\n", s->thread_id);
		else if (message_type==GDB_IFETCH)	 fprintf(stderr,"Info:Thread  : Continued after instruction fetch\n", s->thread_id);
		else if (message_type==GDB_MEM_ACCESS) 	 fprintf(stderr,"Info:Thread  : Continued after memory access (cpu-id=%d)\n", s->thread_id);
		else if (message_type==GDB_TRAP_OCCURED) fprintf(stderr,"Info:Thread  : Continued after a Trap (cpu-id=%d)\n", s->thread_id);
		#endif
	}
	if((message_type==5) && thread_doval_flag(s))
	{

		// To stop the processor and make it wait for the first continue command.
		if(message_type==DOVAL_PROC_ENTERED_ERROR_MODE) 
			fprintf(stderr,
				"Info:Thread  : Thread entered ERROR MODE at PC=0x%x thread=%d, core=%d\n ",
							(s->status_reg).pc, s->thread_id, s->core_id);

		write_uint8(s->hw_server->thread_to_hwserver_id_pipe_name,message_type);
		write_uint64(s->hw_server->thread_to_hwserver_state_pipe_name,(uint64_t)s);
		// Wait for a "CONT" message from the hardware server to continue
		uint32_t serv_rsp1 = read_uint32(s->hw_server->hwserver_to_thread_pipe_name);
		while ( serv_rsp1 != 0x434F4E54 ){ serv_rsp1 = read_uint32(s->hw_server->hwserver_to_thread_pipe_name);}

	}


}


