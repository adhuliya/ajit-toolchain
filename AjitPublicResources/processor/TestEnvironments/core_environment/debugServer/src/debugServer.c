#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "pipeHandler.h"
#include "Pipes.h"
#include "SockPipes.h"
#include "pthreadUtils.h"
#include <debugServer.h>
#include <debugServerDefines.h>

DebugServerConnectMode server_connect_mode = dbg_CONNECT_WITH_PIPE_HANDLER;
void setDebugServerConnectMode(DebugServerConnectMode val)
{
	char buf[256];
	switch(val) {
		case dbg_CONNECT_WITH_PIPE_HANDLER: 
			sprintf(buf,"PIPE_HANDLER");
			break;
		case dbg_CONNECT_WITH_SOCKET: 
			sprintf(buf,"SOCKET");
			break;
		case dbg_CONNECT_WITH_SOCKET_BYTE_MODE: 
			sprintf(buf,"SOCKET_BYTE_MODE");
			break;
		case dbg_CONNECT_WITH_UART: 
			sprintf(buf,"UART");
			break;
		case dbg_CONNECT_WITH_PCIE: 
			sprintf(buf,"PCIE");
			break;
		default:
			fprintf(stderr,"Error: setDebugServerConnectMode: unknown mode %d\n", val);
			assert(0);
	};

	server_connect_mode = val;
	fprintf(stderr,"Info: Debug server connect mode set to %s.\n", buf);
}

DebugServerConnectMode  getDebugServerConnectMode()
{
	return(server_connect_mode);
}


void initDebugServerState(DebugServerState* s)
{
	memset((void*)s, 0, sizeof(DebugServerState));	
}






void probeCcu(DebugServerState* server_state)
{
	//////////////////////////////////////////////  send info to ccu ////////////////////////////////////////
	uint8_t valid_gdb_cmd = ((server_state->gdb_nwords > 0) && (server_state->gdb_state != gdb_INACTIVE));

	// 1. check if gdb command is valid.
	// 2. parse and update server-state.
	parseGdbCommand (server_state, valid_gdb_cmd, server_state->gdb_word_1);

#ifdef VERBOSE
	if(valid_gdb_cmd)
		fprintf(stderr,"Info: probeCcu: gdb_command = 0x%x\n", server_state->gdb_word_1);
#endif

	uint8_t send_connect_ok_to_ccu =
		((server_state->ccu_state == ccu_gdb_CONNECT_PENDING) &&
		 (server_state->gdb_state == gdb_ccu_CONNECT_PENDING));

#ifdef VERBOSE
	if(send_connect_ok_to_ccu)
		fprintf(stderr,"Info: probeCcu: send-connect-ok-to-ccu\n");
#endif

	uint8_t send_first_word_to_ccu =
		send_connect_ok_to_ccu ||
		server_state->gdb_command.gdb_continue_cmd  ||
		server_state->gdb_command.gdb_kill_cmd  ||
		server_state->gdb_command.gdb_set_bp_cmd  ||
		server_state->gdb_command.gdb_set_wp_cmd  ||
		server_state->gdb_command.gdb_clear_bp_cmd  ||
		server_state->gdb_command.gdb_clear_wp_cmd ||
		server_state->gdb_command.gdb_read_iureg  ||
		server_state->gdb_command.gdb_read_fpureg  ||
		server_state->gdb_command.gdb_read_mem  ||
		server_state->gdb_command.gdb_read_cpreg  ||
		server_state->gdb_command.gdb_write_iureg  ||
		server_state->gdb_command.gdb_write_fpureg  ||
		server_state->gdb_command.gdb_write_mem  ||
		server_state->gdb_command.gdb_write_cpreg  ||
		server_state->gdb_command.gdb_write_init_pc  ||
		server_state->gdb_command.gdb_write_init_npc  ||
		server_state->gdb_command.gdb_write_init_psr  ||
		server_state->gdb_command.gdb_write_reset  ||
		server_state->gdb_command.gdb_read_init_pc  ||
		server_state->gdb_command.gdb_read_init_npc  ||
		server_state->gdb_command.gdb_read_init_psr  ||
		server_state->gdb_command.gdb_read_mode  ||
		server_state->gdb_command.gdb_detach_cmd ;
	uint32_t words_to_ccu[4];
	uint32_t n_words_to_ccu = send_first_word_to_ccu;
	words_to_ccu[0] = (send_connect_ok_to_ccu  ?
			((1 << 24) | (gdb_dbg_CONNECT << 16) | 0) : 
			server_state->gdb_word_1);

	uint8_t send_pc_npc_psr_to_ccu =  
		send_connect_ok_to_ccu ||
		server_state->gdb_command.gdb_continue_cmd ||
		server_state->gdb_command.gdb_detach_cmd;
	uint8_t send_second_word_to_ccu  =
		(server_state->gdb_nwords > 1) || send_pc_npc_psr_to_ccu;

	n_words_to_ccu += send_second_word_to_ccu;
	words_to_ccu[1] = (send_pc_npc_psr_to_ccu ? server_state->PC : server_state->gdb_word_2);
	if(send_second_word_to_ccu && !send_pc_npc_psr_to_ccu)
		assert (server_state->gdb_nwords > 1);

	uint8_t send_third_word_to_ccu  =
		(server_state->gdb_nwords > 2) || send_pc_npc_psr_to_ccu;
	n_words_to_ccu += send_third_word_to_ccu;
	words_to_ccu[2] = (send_pc_npc_psr_to_ccu ? server_state->NPC : server_state->gdb_word_3);
	if(send_third_word_to_ccu && !send_pc_npc_psr_to_ccu)
		assert (server_state->gdb_nwords > 2);


	uint8_t send_fourth_word_to_ccu  = send_pc_npc_psr_to_ccu;
	n_words_to_ccu += send_fourth_word_to_ccu;
	words_to_ccu[3] = server_state->PSR;

	int IDX;
	for(IDX = 0; IDX < n_words_to_ccu; IDX++)
	{
		sendU32FromDebugServerToCcu (server_connect_mode, words_to_ccu[IDX]);
#ifdef VERBOSE
		fprintf(stderr,"Info: probeCcu: sent word_to_ccu[%d] = 0x%x\n",
				IDX, words_to_ccu[IDX]);
#endif
	}

	//////////////////////////////////////////////  get info from ccu ////////////////////////////////////////

	// clear the nwords field.
	server_state->ccu_nwords = 0;

	uint32_t ccu_word_1;
	uint8_t ccu_word_1_valid = 0;
	ccu_word_1_valid = recvValidCcuMessage (0, &ccu_word_1);
	if (ccu_word_1_valid)
	{
#ifdef VERBOSE
		fprintf(stderr,"Info: probeCcu: received ccu_word_1 = 0x%x\n", ccu_word_1); 
#endif
		server_state->ccu_word_1 = ccu_word_1;
	}

	parseCcuCommand (server_state, ccu_word_1_valid, ccu_word_1);

	uint8_t ccu_read_pc_npc_psr = (server_state->ccu_command.ccu_bp_hit ||
			server_state->ccu_command.ccu_read_wp_hit ||
			server_state->ccu_command.ccu_write_wp_hit ||
			server_state->ccu_command.ccu_trap_hit ||
			server_state->ccu_command.ccu_intr_hit ||
			server_state->ccu_command.ccu_gdb_connect);
	uint8_t get_second_word = (ccu_read_pc_npc_psr || server_state->ccu_command.ccu_read_response);


	uint32_t ccu_word_2;
	if(get_second_word)
	{
		uint8_t ccu_word_2_valid  = 0;
		ccu_word_2_valid = recvValidCcuMessage(1,&ccu_word_2);
#ifdef VERBOSE
		fprintf(stderr,"Info: probeCcu: received ccu_word_2 = 0x%x\n", ccu_word_2); 
#endif
		assert(ccu_word_2_valid);

		server_state->ccu_word_2 = ccu_word_2;
	}


	uint8_t get_third_word = ccu_read_pc_npc_psr;

	uint32_t ccu_word_3;
	if(get_third_word)
	{
		uint8_t ccu_word_3_valid = 0;
		ccu_word_3_valid  = recvValidCcuMessage(1,&ccu_word_3);
#ifdef VERBOSE
		fprintf(stderr,"Info: probeCcu: received ccu_word_3 = 0x%x\n", ccu_word_3); 
#endif
		assert(ccu_word_3_valid);
	}


	uint8_t get_fourth_word = ccu_read_pc_npc_psr;
	uint32_t ccu_word_4;
	if(get_fourth_word)
	{
		uint8_t ccu_word_4_valid = 0;
		ccu_word_4_valid =   recvValidCcuMessage(1,&ccu_word_4);
#ifdef VERBOSE
		fprintf(stderr,"Info: probeCcu: received ccu_word_4 = 0x%x\n", ccu_word_4); 
#endif
		assert(ccu_word_4_valid);
	}

	DebugServerCcuState next_ccu_state = server_state->ccu_state;
	switch(server_state->ccu_state) 
	{
		case ccu_IDLE:
			next_ccu_state = (server_state->ccu_command.ccu_gdb_connect ?
					ccu_gdb_CONNECT_PENDING : ccu_IDLE);	
			break;
		case ccu_gdb_CONNECT_PENDING:
			next_ccu_state = ((server_state->gdb_state == gdb_ccu_CONNECT_PENDING) ?
					ccu_gdb_CONNECTED : ccu_gdb_CONNECT_PENDING);
			break;
		case ccu_gdb_CONNECTED:
			next_ccu_state = ((server_state->ccu_command.ccu_send_gdb_ack &&
						(server_state->gdb_state == gdb_DETACH_PENDING)) ?
					ccu_IDLE : ccu_gdb_CONNECTED);
			break;
		default:
			break;
	};
	server_state->ccu_state = next_ccu_state;

	if(ccu_word_1_valid)
		server_state->ccu_nwords = (server_state->ccu_command.ccu_read_response ? 2 : 1);
	else
		server_state->ccu_nwords = 0;

	if(ccu_read_pc_npc_psr) 
	{
		server_state->PC  = ccu_word_2;
		server_state->NPC = ccu_word_3;
		server_state->PSR = ccu_word_4;

#ifdef VERBOSE
		fprintf(stderr,"Info: probeCcu: set PC=0x%x, NPC=0x%x, PSR=0x%x\n",
				server_state->PC, server_state->NPC, server_state->PSR);
#endif
	}

	if(server_state->ccu_nwords > 0)
	{
#ifdef VERBOSE
		fprintf(stderr,"Info: leaving probeCcu: ccu_nwords=%d, ccu_word_1=0x%x, ccu_word_2=0x%x, pc=0x%x, npc=0x%x, psr=0x%x\n",
				server_state->ccu_nwords,
				server_state->ccu_word_1,
				server_state->ccu_word_2,
				server_state->PC,
				server_state->NPC,
				server_state->PSR);
#endif
	}
}

void probeGdb(DebugServerState* server_state)
{
	uint8_t connect_ok = (server_state->gdb_state == gdb_ccu_CONNECT_PENDING) &&
		(server_state->ccu_state == ccu_gdb_CONNECTED);
	uint8_t gdb_detached = (server_state->gdb_state == gdb_DETACHED);
	uint8_t gdb_inactive = (server_state->gdb_state == gdb_DETACHED);

	uint8_t ccu_command_exists = (server_state->ccu_nwords > 0);
	uint8_t send_continue_to_ccu = 0;
	if(ccu_command_exists)
	{
		parseCcuCommand(server_state, ccu_command_exists, server_state->ccu_word_1);
#ifdef VERBOSE
		fprintf(stderr,"Info: probeGdb: ccu_command = 0x%x\n", server_state->ccu_word_1);
#endif

		send_continue_to_ccu =
			(gdb_detached && 
			 (server_state->ccu_command.ccu_bp_hit ||
			  server_state->ccu_command.ccu_read_wp_hit ||
			  server_state->ccu_command.ccu_write_wp_hit ||
			  server_state->ccu_command.ccu_thread_finish));
		uint8_t send_first_word_to_gdb = ((~gdb_detached) &&
				(
				 server_state->ccu_command.ccu_send_gdb_ack ||
				 server_state->ccu_command.ccu_send_gdb_error ||
				 server_state->ccu_command.ccu_bp_hit ||
				 server_state->ccu_command.ccu_read_wp_hit ||
				 server_state->ccu_command.ccu_write_wp_hit ||
				 server_state->ccu_command.ccu_thread_finish ||
				 server_state->ccu_command.ccu_read_response ||
				 server_state->ccu_command.ccu_enter_error_mode)); 
		uint32_t first_word_to_gdb = 0;
		first_word_to_gdb = (server_state->ccu_command.ccu_bp_hit ? dbg_gdb_BP_HIT : 0) |
			(server_state->ccu_command.ccu_read_wp_hit ? dbg_gdb_READ_WP_HIT : 0) |
			(server_state->ccu_command.ccu_write_wp_hit ? dbg_gdb_WRITE_WP_HIT : 0) |
			(server_state->ccu_command.ccu_thread_finish ? dbg_gdb_TRAP_HIT : 0) |
			(server_state->ccu_command.ccu_send_gdb_ack ? dbg_gdb_OK : 0) |
			(server_state->ccu_command.ccu_send_gdb_error ? dbg_gdb_ERROR : 0) |
			(server_state->ccu_command.ccu_enter_error_mode ? dbg_gdb_ERROR_MODE : 0) |
			(server_state->ccu_command.ccu_read_response ? server_state->ccu_word_2 : 0);
		uint8_t use_default = !(server_state->ccu_command.ccu_bp_hit ||
				server_state->ccu_command.ccu_read_wp_hit  ||
				server_state->ccu_command.ccu_write_wp_hit  ||
				server_state->ccu_command.ccu_thread_finish  ||
				server_state->ccu_command.ccu_send_gdb_ack ||
				server_state->ccu_command.ccu_send_gdb_error ||
				server_state->ccu_command.ccu_enter_error_mode ||
				server_state->ccu_command.ccu_read_response);
		if(use_default)
			first_word_to_gdb = server_state->ccu_word_1;
		if(send_first_word_to_gdb)
		{
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb: trying to send first-word-to-gdb = 0x%x\n", first_word_to_gdb);
#endif
			sendU32FromDebugServerToGdb(first_word_to_gdb);
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb: sent first-word-to-gdb = 0x%x\n", first_word_to_gdb);
#endif
		}


		uint8_t send_second_word_to_gdb = (server_state->ccu_command.ccu_read_wp_hit | server_state->ccu_command.ccu_write_wp_hit);
		uint32_t second_word_to_gdb =  server_state->WP_REGS[server_state->ccu_command.ccu_wp_reg_index];
		if(send_second_word_to_gdb)
		{
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb: trying to send second-word-to-gdb = 0x%x\n", second_word_to_gdb);
#endif
			sendU32FromDebugServerToGdb(second_word_to_gdb);
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb: second-word-to-gdb = 0x%x\n", second_word_to_gdb);
#endif
		}
	}

	uint8_t gdb_in_invalid_state = (gdb_inactive || gdb_detached);

	uint32_t gdb_word_1;
	uint32_t gdb_word_2;
	uint32_t gdb_word_3;
	uint8_t send_quick_response_to_gdb = 0;
	uint32_t get_second_word_from_gdb  = 0;
	uint32_t get_third_word_from_gdb  = 0;
	uint8_t  gdb_word_1_valid = 0;
	if(!gdb_in_invalid_state)
	{
		gdb_word_1_valid = recvValidGdbMessage (0, &gdb_word_1);
#ifdef VERBOSE
		if(gdb_word_1_valid)
			fprintf(stderr,"Info: probeGdb: received gdb_word_1 = 0x%x\n", gdb_word_1);
#endif
		parseGdbCommand (server_state, gdb_word_1_valid, gdb_word_1);

		get_second_word_from_gdb =
			(
			 server_state->gdb_command.gdb_set_bp_cmd  ||
			 server_state->gdb_command.gdb_set_wp_cmd  ||
			 server_state->gdb_command.gdb_clear_bp_cmd  ||
			 server_state->gdb_command.gdb_clear_wp_cmd ||
			 server_state->gdb_command.gdb_write_iureg  ||
			 server_state->gdb_command.gdb_write_fpureg  ||
			 server_state->gdb_command.gdb_write_cntrl_reg  ||
			 server_state->gdb_command.gdb_write_mem  ||
			 server_state->gdb_command.gdb_write_init_pc  ||
			 server_state->gdb_command.gdb_write_init_npc  ||
			 server_state->gdb_command.gdb_write_init_psr  ||
			 server_state->gdb_command.gdb_write_cpreg  ||
			 server_state->gdb_command.gdb_read_mem
			);

		if(get_second_word_from_gdb)
		{
			uint8_t gdb_word_2_valid = 0;
			gdb_word_2_valid = recvValidGdbMessage (1, &gdb_word_2);
			assert(gdb_word_2_valid);
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb: received gdb_word_2 = 0x%x\n", gdb_word_2);
#endif
		}

		if(server_state->gdb_command.gdb_set_wp_cmd)
		{
			server_state->WP_REGS[server_state->gdb_command.gdb_wp_reg_index] = gdb_word_2;
		}	

		if(server_state->gdb_command.gdb_write_pc)
		{
			server_state->PC = gdb_word_2;
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb: set pc = 0x%x\n", gdb_word_2);
#endif
		}

		if(server_state->gdb_command.gdb_write_npc)
		{
			server_state->NPC = gdb_word_2;
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb: set npc = 0x%x\n", gdb_word_2);
#endif
		}

		if(server_state->gdb_command.gdb_write_psr)
		{
			server_state->PSR = gdb_word_2;
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb: set psr = 0x%x\n", gdb_word_2);
#endif
		}

		get_third_word_from_gdb = server_state->gdb_command.gdb_write_mem;
		if(get_third_word_from_gdb)
		{
			uint8_t gdb_word_3_valid = 0;
			gdb_word_3_valid = recvValidGdbMessage (1, &gdb_word_3);
			assert(gdb_word_3_valid);
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb: received gdb_word_2 = 0x%x\n", gdb_word_3);
#endif
		}

		uint8_t send_pc_or_npc = (server_state->gdb_command.gdb_read_pc ||
				server_state->gdb_command.gdb_read_npc);	
		send_quick_response_to_gdb = send_pc_or_npc;
		if(send_pc_or_npc)
		{
			uint32_t quick_debug_response_word = 
				(server_state->gdb_command.gdb_read_pc ? server_state->PC : server_state->NPC);
			sendU32FromDebugServerToGdb(quick_debug_response_word);
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb: sent quick-response = 0x%x\n", quick_debug_response_word);
#endif
		}
	}

	DebugServerGdbState next_gdb_state = server_state->gdb_state;
	switch(server_state->gdb_state)
	{
		case gdb_INACTIVE:
			next_gdb_state = gdb_IDLE;
			break;
		case gdb_IDLE:
			next_gdb_state = 
				((!gdb_in_invalid_state && server_state->gdb_command.gdb_connect_cmd) ?
				 gdb_ccu_CONNECT_PENDING : gdb_IDLE);
			break;
		case gdb_ccu_CONNECT_PENDING:
			if(server_state->ccu_state == ccu_gdb_CONNECTED)
				next_gdb_state = gdb_ccu_CONNECTED;
			break;
		case gdb_ccu_CONNECTED:
			next_gdb_state = 
				((!gdb_in_invalid_state && server_state->gdb_command.gdb_detach_cmd) ?
				 gdb_DETACH_PENDING :
				 ((!gdb_in_invalid_state && server_state->gdb_command.gdb_kill_cmd) ?
				  gdb_DETACHED : gdb_ccu_CONNECTED));
			break;
		case gdb_DETACH_PENDING:
			if(server_state->ccu_state == ccu_IDLE)
				next_gdb_state = gdb_DETACHED;
			break;
		case gdb_DETACHED:
			break;
		default:
			break;
	}	
	server_state->gdb_state = next_gdb_state;

	server_state->gdb_nwords = 0;
	if(send_continue_to_ccu)
		server_state->gdb_nwords = 1;
	else if(!gdb_in_invalid_state)
	{
		if(get_third_word_from_gdb)
			server_state->gdb_nwords = 3;
		else if(get_second_word_from_gdb)
			server_state->gdb_nwords = 2;
		else if(gdb_word_1_valid)
			server_state->gdb_nwords = 1;
	}

	server_state->gdb_word_1 = (send_continue_to_ccu ?
			((1 << 24) | (gdb_dbg_CONTINUE << 16)) : gdb_word_1);
	server_state->gdb_word_2 = ((!gdb_in_invalid_state && get_second_word_from_gdb) ? gdb_word_2 : 0);
	server_state->gdb_word_3 = ((!gdb_in_invalid_state && get_third_word_from_gdb)  ? gdb_word_3 : 0);

	if(server_state->gdb_nwords > 0)
	{
#ifdef VERBOSE
		fprintf(stderr,"Info: leaving probeGdb: gdb_nwords=%d, gdb_word_1=0x%x, gdb_word_2=0x%x, gdb_word_3=0x%x, pc=0x%x, npc=0x%x, psr=0x%x\n",
				server_state->gdb_nwords,
				server_state->gdb_word_1,
				server_state->gdb_word_2,
				server_state->gdb_word_3, 
				server_state->PC,
				server_state->NPC,
				server_state->PSR);
#endif
	}


}

void debugServerDaemon()
{
	DebugServerState server_state;
	initDebugServerState(&server_state);

	while(1) 
	{
		probeCcu(&server_state);
		probeGdb(&server_state);
		usleep(100);
	}
}


DEFINE_THREAD (debugServerDaemon);
PTHREAD_DECL  (debugServerDaemon);
void startDebugServer()
{
	fprintf(stderr,"Info: Debug Server started.\n");

	startNoblockDaemons();
	PTHREAD_CREATE (debugServerDaemon);
}
void stopDebugServer()
{
	stopNoblockDaemons();
	PTHREAD_CANCEL (debugServerDaemon);
}



