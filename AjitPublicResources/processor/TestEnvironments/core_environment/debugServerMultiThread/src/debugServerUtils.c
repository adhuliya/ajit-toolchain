#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "pipeHandler.h"
#include "Pipes.h"
#include "SockPipes.h"
#include <pthread.h>
#include "pthreadUtils.h"
#include <debugServerMultiThread.h>
#include <debugServerDefines.h>
#include <uart_interface.h>
#include "RxQueueServer.h"

MUTEX_DECL(monitor_to_debug_mutex);

void blockingToNonblockingFromGdbDaemon_MultiThread (void* ct);
void blockingToNonblockingFromCcuDaemon_MultiThread (void* ct);

DEFINE_THREAD_WITH_ARG(blockingToNonblockingFromGdbDaemon_MultiThread, ct_id);
PTHREAD_DECL(blockingToNonblockingFromGdbDaemon_MultiThread);

DEFINE_THREAD_WITH_ARG(blockingToNonblockingFromCcuDaemon_MultiThread, ct_id);
PTHREAD_DECL(blockingToNonblockingFromCcuDaemon_MultiThread);

void blockingToNonblockingFromGdbDaemon_MultiThread (void* ct_id)
{
	uint32_t CT = *((int*) ct_id);
	int CORE_ID = (CT >> 16) & 0xff;
	int THREAD_ID = (CT & 0xff);

	fprintf(stderr,"Info: start blockingToNonblockingFromGdbDaemon_MultiThread (%d,%d).\n", CORE_ID, THREAD_ID);

	char to_ds[256];
	char nb_to_ds[256];

	sprintf(to_ds,"COMMAND_TO_DEBUG_SERVER_%d_%d", CORE_ID, THREAD_ID);
	sprintf(nb_to_ds,"NOBLOCK_FROM_gdb_%d_%d", CORE_ID, THREAD_ID);

	while(1) {

		uint32_t from_gdb = read_uint32(to_ds);

#ifdef VERBOSE
		fprintf(stderr,"Info:debugServerMT; received 0x%x on pipe %s.\n", from_gdb, to_ds);
#endif

		uint64_t to_server = from_gdb;
		to_server = ((((uint64_t) 1) << 32) | to_server);

		write_uint64 (nb_to_ds, to_server);
	}
}

void blockingToNonblockingFromCcuDaemon_MultiThread (void* ct_id)
{
	uint32_t CT = *((int*) ct_id);
	int CORE_ID = (CT >> 16) & 0xff;
	int THREAD_ID = (CT & 0xff);

	fprintf(stderr,"Info: start blockingToNonblockingFromCcuDaemon_MultiThread (%d,%d).\n", CORE_ID, THREAD_ID);

	char pipe_name[256];
	sprintf(pipe_name,"NOBLOCK_FROM_ccu_%d_%d", CORE_ID, THREAD_ID);
	while(1) {

		uint32_t from_ccu;
		DebugServerConnectMode cmode = getDebugServerConnectMode();
		perThreadRecvU32FromCcuToDebugServer(CORE_ID, THREAD_ID, cmode, &from_ccu);

		uint64_t to_server = from_ccu;
		to_server = ((((uint64_t) 1) << 32) | to_server);

		write_uint64 (pipe_name, to_server);
#ifdef VERBOSE
		fprintf(stderr,"Info:blockingToNonblockingFromCcuDaemon_MT: send 0x%llx on pipe %s.\n",
					to_server, pipe_name);
#endif
	}
}


void perThreadSendU32FromDebugServerToGdb(int CORE_ID, int THREAD_ID, uint32_t word) 
{
	char pipe_name [256];
	sprintf(pipe_name,"RESPONSE_FROM_DEBUG_SERVER_%d_%d", CORE_ID, THREAD_ID);
	write_uint32(pipe_name, word);
}

//
// All traffic to the hardware is channeled through MONITOR_to_DEBUG
//   It will be demuxed in the hardware
//
int perThreadSendBytesToCcu(int CORE_ID, int THREAD_ID, uint32_t word)
{
	// Should acquire mutex.
	MUTEX_LOCK(monitor_to_debug_mutex);	

	char pipe_name[256];
	sprintf(pipe_name, "SOC_MONITOR_to_DEBUG");

	sock_write_uint8(pipe_name, CORE_ID);
	sock_write_uint8(pipe_name, THREAD_ID);

	uint8_t  *buf = (uint8_t*) &word;
	int B;
	for(B=3; B >= 0; B--)
	{
		sock_write_uint8 (pipe_name, buf[B]);
	}
	
	MUTEX_UNLOCK(monitor_to_debug_mutex);
}

int sendBytesOverSocket( uint32_t word)
{
	uint8_t  *buf = (uint8_t*) &word;
	int B;
	for(B=3; B >= 0; B--)
		sock_write_uint8 ("SOC_MONITOR_to_DEBUG", buf[B]);
}

void perThreadSendU32FromDebugServerToCcu(int CORE_ID, int THREAD_ID,
						DebugServerConnectMode debug_connect_mode, uint32_t word)
{
	if(debug_connect_mode == dbg_CONNECT_WITH_SOCKET_BYTE_MODE)
	{
		perThreadSendBytesToCcu(CORE_ID, THREAD_ID, word);
	}
	else if(debug_connect_mode == dbg_CONNECT_WITH_UART)
		perThreadSendBytesOverUart(CORE_ID, THREAD_ID, (uint8_t*)&word, 4);	
	else
	{
		assert(0);
	}
}

void perThreadRecvU32FromCcuToDebugServer(int CORE_ID, int THREAD_ID,
				DebugServerConnectMode debug_connect_mode, uint32_t *word)
{
	perThreadRecvBytesFromRxDaemon (CORE_ID, THREAD_ID, (uint8_t*) word, 4);
#ifdef VERBOSE
	fprintf(stderr,"Info:perThreadRecvU32FromCcuToDebugServer: received 0x%x.\n", *word);
#endif
}

uint8_t perThreadRecvValidCcuMessage (int CORE_ID, int THREAD_ID, uint8_t blocking_flag, uint32_t* read_word)
{
	char pipe_name[256];
	sprintf(pipe_name, "NOBLOCK_FROM_ccu_%d_%d", CORE_ID, THREAD_ID);

	uint8_t ret_val = 0;
	while(1) {
		uint64_t rsp = read_uint64 (pipe_name);
#ifdef VERBOSE
		if(rsp != 0)
			fprintf(stderr,"Info:perThreadRecvValidCcuMessage: received 0x%llx on pipe %s.\n",
					rsp, pipe_name);
#endif

		ret_val = ((rsp >> 32) & 0x1);
		if(!blocking_flag || ret_val)
		{
			*read_word = rsp & 0xffffffff;
			break;
		}
		usleep (100);
	}
	return(ret_val);
}


uint8_t perThreadRecvValidGdbMessage (int CORE_ID, int THREAD_ID,  uint8_t blocking_flag, uint32_t* read_word)
{
	char pipe_name[256];
	sprintf(pipe_name, "NOBLOCK_FROM_gdb_%d_%d", CORE_ID, THREAD_ID);
	uint8_t ret_val = 0;
	while(1) {
		uint64_t rsp = read_uint64 (pipe_name);

		ret_val = ((rsp >> 32) & 0x1);
		if(!blocking_flag || ret_val)
		{
			*read_word = rsp & 0xffffffff;
			break;
		}
		usleep (100);
	}
	return(ret_val);
}


void parseGdbCommand (DebugServerState* server_state, uint8_t valid_flag, uint32_t command)
{
	memset ((void*) &(server_state->gdb_command), 0, sizeof(GdbCommand));
	if(valid_flag)
	{
		uint32_t gdb_cmd_opcode = (command >> 16) & 0xff;
		uint32_t gdb_cmd_data   = (command & 0xffff);		
		
		server_state->gdb_command.gdb_connect_cmd = (gdb_cmd_opcode == gdb_dbg_CONNECT);
		server_state->gdb_command.gdb_continue_cmd = (gdb_cmd_opcode == gdb_dbg_CONTINUE);
		server_state->gdb_command.gdb_detach_cmd = (gdb_cmd_opcode == gdb_dbg_DETACH);
		server_state->gdb_command.gdb_detach_cmd = (gdb_cmd_opcode == gdb_dbg_KILL);

		server_state->gdb_command.gdb_set_bp_cmd = (gdb_cmd_opcode == gdb_dbg_SET_BREAK_POINT);
		server_state->gdb_command.gdb_clear_bp_cmd = (gdb_cmd_opcode == gdb_dbg_REMOVE_BREAK_POINT);
		server_state->gdb_command.gdb_set_wp_cmd = (gdb_cmd_opcode == gdb_dbg_SET_WATCH_POINT);
		server_state->gdb_command.gdb_clear_wp_cmd = (gdb_cmd_opcode == gdb_dbg_REMOVE_WATCH_POINT);

		server_state->gdb_command.gdb_read_iureg  = (gdb_cmd_opcode == gdb_dbg_READ_IUNIT_REG);
		server_state->gdb_command.gdb_read_fpureg = (gdb_cmd_opcode == gdb_dbg_READ_FPUNIT_REG);
		server_state->gdb_command.gdb_read_mem    = (gdb_cmd_opcode == gdb_dbg_READ_MEM);
		server_state->gdb_command.gdb_read_cpreg  = (gdb_cmd_opcode == gdb_dbg_READ_CPUNIT_REG);

		server_state->gdb_command.gdb_write_iureg = (gdb_cmd_opcode == gdb_dbg_WRITE_IUNIT_REG);
		server_state->gdb_command.gdb_write_fpureg = (gdb_cmd_opcode == gdb_dbg_WRITE_FPUNIT_REG);
		server_state->gdb_command.gdb_write_mem = (gdb_cmd_opcode == gdb_dbg_WRITE_MEM);
		server_state->gdb_command.gdb_write_cpreg = (gdb_cmd_opcode == gdb_dbg_WRITE_CPUNIT_REG);

		server_state->gdb_command.gdb_read_pc = (gdb_cmd_opcode == gdb_dbg_READ_CONTROL_REG) && (gdb_cmd_data & 0x1);
		server_state->gdb_command.gdb_read_npc = (gdb_cmd_opcode == gdb_dbg_READ_CONTROL_REG) && ((gdb_cmd_data >> 1) & 0x1);
		server_state->gdb_command.gdb_read_psr = (gdb_cmd_opcode == gdb_dbg_READ_IUNIT_REG) && ((gdb_cmd_data >> 9) & 0x1);

		server_state->gdb_command.gdb_write_pc = (gdb_cmd_opcode == gdb_dbg_WRITE_CONTROL_REG) && (gdb_cmd_data & 0x1);
		server_state->gdb_command.gdb_write_npc = (gdb_cmd_opcode == gdb_dbg_WRITE_CONTROL_REG) && ((gdb_cmd_data >> 1) & 0x1);
		server_state->gdb_command.gdb_write_psr = (gdb_cmd_opcode == gdb_dbg_WRITE_IUNIT_REG) && ((gdb_cmd_data >> 9) & 0x1);

		server_state->gdb_command.gdb_wp_reg_index = (gdb_cmd_data >> 14) & 0x3;

		// Added Sept 2019.
		server_state->gdb_command.gdb_write_reset = (gdb_cmd_opcode == gdb_dbg_WRITE_RESET);
		server_state->gdb_command.gdb_write_init_pc = (gdb_cmd_opcode == gdb_dbg_WRITE_INIT_PC);
		server_state->gdb_command.gdb_write_init_npc = (gdb_cmd_opcode == gdb_dbg_WRITE_INIT_NPC);
		server_state->gdb_command.gdb_write_init_psr = (gdb_cmd_opcode == gdb_dbg_WRITE_INIT_PSR);
		server_state->gdb_command.gdb_read_mode = (gdb_cmd_opcode == gdb_dbg_READ_MODE);
		server_state->gdb_command.gdb_read_init_pc = (gdb_cmd_opcode == gdb_dbg_READ_INIT_PC);
		server_state->gdb_command.gdb_read_init_npc = (gdb_cmd_opcode == gdb_dbg_READ_INIT_NPC);
		server_state->gdb_command.gdb_read_init_psr = (gdb_cmd_opcode == gdb_dbg_READ_INIT_PSR);
	}
}

void parseCcuCommand (DebugServerState* server_state, uint8_t valid_flag, uint32_t command)
{
	uint8_t ccu_cmd_opcode = (command >> 16) & 0xff;
	uint32_t ccu_cmd_data = command & 0xffff;

	uint32_t trap_hit = (ccu_cmd_data & 0x1);
	uint32_t single_step_hit = ((ccu_cmd_data >> 1) & 0x1);
	uint32_t intr_hit = ((ccu_cmd_data >> 2) & 0x1);

	memset ((void*) &(server_state->ccu_command), 0, sizeof(CcuCommand));

	if(valid_flag) 
	{
		server_state->ccu_command.ccu_send_gdb_ack = (ccu_cmd_opcode == ccu_dbg_OK);
		server_state->ccu_command.ccu_send_gdb_error = (ccu_cmd_opcode == ccu_dbg_ERROR);
		server_state->ccu_command.ccu_gdb_connect = (ccu_cmd_opcode == ccu_dbg_CONNECT_RQST);
		server_state->ccu_command.ccu_bp_hit = (ccu_cmd_opcode == ccu_dbg_BP_HIT);
		server_state->ccu_command.ccu_read_wp_hit = (ccu_cmd_opcode == ccu_dbg_READ_WP_HIT);
		server_state->ccu_command.ccu_write_wp_hit = (ccu_cmd_opcode == ccu_dbg_WRITE_WP_HIT);
		server_state->ccu_command.ccu_thread_finish = (ccu_cmd_opcode == ccu_dbg_THREAD_FINISH);
		server_state->ccu_command.ccu_enter_error_mode = (ccu_cmd_opcode == ccu_dbg_ERROR_MODE);
		server_state->ccu_command.ccu_read_response = (ccu_cmd_opcode == ccu_dbg_READ_RESPONSE);
		server_state->ccu_command.ccu_intr_hit = intr_hit;
		server_state->ccu_command.ccu_single_step_hit = single_step_hit;
		server_state->ccu_command.ccu_trap_hit = trap_hit;

		server_state->ccu_command.ccu_wp_reg_index = (ccu_cmd_data & 0x3);
	}

}

void startPerThreadNoblockDaemon (int CORE_ID, int THREAD_ID)
{
	fprintf(stderr,"Info: starting per thread noblock daemon core=%d, thread=%d.\n", CORE_ID, THREAD_ID);

	char pname_command_to_debug_server[256];
	sprintf(pname_command_to_debug_server, "COMMAND_TO_DEBUG_SERVER_%d_%d", CORE_ID, THREAD_ID);

	char pname_response_from_debug_server[256];
	sprintf(pname_command_to_debug_server, "RESPONSE_FROM_DEBUG_SERVER_%d_%d", CORE_ID, THREAD_ID);

	char pname_from_gdb[256];
	sprintf(pname_from_gdb, "NOBLOCK_FROM_gdb_%d_%d", CORE_ID, THREAD_ID);

	char pname_from_ccu[256];
	sprintf(pname_from_ccu, "NOBLOCK_FROM_ccu_%d_%d", CORE_ID, THREAD_ID);


	register_pipe (pname_command_to_debug_server, 8 , 32, 0);
	register_pipe (pname_response_from_debug_server, 8 , 32, 0);

	register_pipe (pname_from_gdb, 8 , 64, PIPE_FIFO_NON_BLOCK_READ);
	register_pipe (pname_from_ccu, 8, 64, PIPE_FIFO_NON_BLOCK_READ);

	int CT_ID = (CORE_ID << 16) | THREAD_ID;
	uint32_t* vptr = (uint32_t*) malloc(sizeof(uint32_t));
	*vptr = CT_ID;


	PTHREAD_CREATE_WITH_ARG (blockingToNonblockingFromGdbDaemon_MultiThread, ((void*) vptr));
	PTHREAD_CREATE_WITH_ARG (blockingToNonblockingFromCcuDaemon_MultiThread, ((void*) vptr));
}

void stopPerThreadNoblockDaemon(int CORE_ID, int THREAD_ID)
{
	// do nothing..
}
