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
#include <debugServer.h>
#include <debugServerDefines.h>
#include <uart_interface.h>

void blockingToNonblockingFromGdbDaemon ();
void blockingToNonblockingFromCcuDaemon ();

DEFINE_THREAD (blockingToNonblockingFromGdbDaemon);
DEFINE_THREAD (blockingToNonblockingFromCcuDaemon);

PTHREAD_DECL (blockingToNonblockingFromGdbDaemon);
PTHREAD_DECL (blockingToNonblockingFromCcuDaemon);

void startNoblockDaemons () 
{
	register_pipe ("COMMAND_TO_DEBUG_SERVER", 8 , 32, 0);
	register_pipe ("RESPONSE_FROM_DEBUG_SERVER", 8 , 32, 0);

	register_pipe ("NOBLOCK_FROM_gdb", 8 , 64, PIPE_FIFO_NON_BLOCK_READ);
	register_pipe ("NOBLOCK_FROM_ccu", 8, 64, PIPE_FIFO_NON_BLOCK_READ);

	PTHREAD_CREATE (blockingToNonblockingFromGdbDaemon);
	PTHREAD_CREATE (blockingToNonblockingFromCcuDaemon);
}

void stopNoblockDaemons ()
{
	PTHREAD_CANCEL (blockingToNonblockingFromGdbDaemon);
	PTHREAD_CANCEL (blockingToNonblockingFromCcuDaemon);
}


void blockingToNonblockingFromGdbDaemon ()
{
	while(1) {

		uint32_t from_gdb = read_uint32("COMMAND_TO_DEBUG_SERVER");
		uint64_t to_server = from_gdb;
		to_server = ((((uint64_t) 1) << 32) | to_server);

		write_uint64 ("NOBLOCK_FROM_gdb", to_server);
	}
}

void blockingToNonblockingFromCcuDaemon ()
{
	while(1) {

		uint32_t from_ccu;
		DebugServerConnectMode cmode = getDebugServerConnectMode();
		recvU32FromCcuToDebugServer(cmode, &from_ccu);

		uint64_t to_server = from_ccu;
		to_server = ((((uint64_t) 1) << 32) | to_server);

		write_uint64 ("NOBLOCK_FROM_ccu", to_server);

	}
}

void sendU32FromDebugServerToGdb(uint32_t word) 
{
	write_uint32("RESPONSE_FROM_DEBUG_SERVER", word);
}

int sendBytesOverSocket( uint32_t word)
{
	uint8_t  *buf = (uint8_t*) &word;
	int B;
	for(B=3; B >= 0; B--)
		sock_write_uint8 ("MONITOR_to_DEBUG", buf[B]);
}


int recvBytesOverSocket(uint32_t *word)
{
	uint8_t  *buf = (uint8_t*) word;
	int B;
	for(B=3; B >= 0; B--)
		buf[B] = sock_read_uint8 ("DEBUG_to_MONITOR");
}



// normal mode: for single core case.
void sendU32FromDebugServerToCcu(DebugServerConnectMode debug_connect_mode, uint32_t word)
{
	if((debug_connect_mode == dbg_CONNECT_WITH_PIPE_HANDLER) ||
			(debug_connect_mode == dbg_CONNECT_WITH_PCIE))
		write_uint32("ENV_to_AJIT_debug_command", word);
	else if(debug_connect_mode == dbg_CONNECT_WITH_UART)
		sendBytesOverUart((uint8_t*)&word, 4);	
	else
	{
		if(debug_connect_mode == dbg_CONNECT_WITH_SOCKET_BYTE_MODE)
		{
			sendBytesOverSocket(word);
		}
		else
		{
			sock_write_uint32("ENV_to_AJIT_debug_command", word);
		}
	}
}


void recvU32FromCcuToDebugServer(DebugServerConnectMode debug_connect_mode, uint32_t *word)
{
	if((debug_connect_mode == dbg_CONNECT_WITH_PIPE_HANDLER) || (debug_connect_mode == dbg_CONNECT_WITH_PCIE))
		*word = read_uint32("AJIT_to_ENV_debug_response");
	else if(debug_connect_mode == dbg_CONNECT_WITH_UART)
		recvBytesOverUart ((uint8_t*) word, 4, 0); // non-block flag.
	else
	{
		if(debug_connect_mode == dbg_CONNECT_WITH_SOCKET_BYTE_MODE)
		{
			recvBytesOverSocket(word);
		}
		else
		{
			*word = sock_read_uint32("AJIT_to_ENV_debug_response");
		}
	}
}

uint8_t recvValidCcuMessage (uint8_t blocking_flag, uint32_t* read_word)
{
	uint8_t ret_val = 0;
	while(1) {
		uint64_t rsp = read_uint64 ("NOBLOCK_FROM_ccu");

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


uint8_t recvValidGdbMessage (uint8_t blocking_flag, uint32_t* read_word)
{
	uint8_t ret_val = 0;
	while(1) {
		uint64_t rsp = read_uint64 ("NOBLOCK_FROM_gdb");

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
