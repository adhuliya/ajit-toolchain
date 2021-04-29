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
#include <debugServerMultiThread.h>
#include <debugServerDefines.h>
#include "RxQueueServer.h"

DebugServerConnectMode server_connect_mode = dbg_CONNECT_WITH_SOCKET_BYTE_MODE;
void setDebugServerConnectMode(DebugServerConnectMode val)
{
	char buf[256];
	switch(val) {
		case dbg_CONNECT_WITH_SOCKET_BYTE_MODE: 
			sprintf(buf,"SOCKET_BYTE_MODE");
			break;
		case dbg_CONNECT_WITH_UART: 
			sprintf(buf,"UART");
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


void initDebugServerState(DebugServerState* s, int CORE_ID, int THREAD_ID)
{
	memset((void*)s, 0, sizeof(DebugServerState));	
	s->CORE_ID = CORE_ID;
	s->THREAD_ID = THREAD_ID;
}



void probeCcu(DebugServerState* server_state, int CORE_ID, int THREAD_ID)
{
	//////////////////////////////////////////////  send info to ccu ////////////////////////////////////////
	uint8_t valid_gdb_cmd = ((server_state->gdb_nwords > 0) && (server_state->gdb_state != gdb_INACTIVE));
	
	// 1. check if gdb command is valid.
	// 2. parse and update server-state.
	parseGdbCommand (server_state, valid_gdb_cmd, server_state->gdb_word_1);

#ifdef VERBOSE
	if(valid_gdb_cmd)
		fprintf(stderr,"Info: probeCcu (%d,%d): gdb_command = 0x%x\n", 
					CORE_ID, THREAD_ID, server_state->gdb_word_1);
#endif

	uint8_t send_connect_ok_to_ccu =
			((server_state->ccu_state == ccu_gdb_CONNECT_PENDING) &&
				(server_state->gdb_state == gdb_ccu_CONNECT_PENDING));

#ifdef VERBOSE
	if(send_connect_ok_to_ccu)
		fprintf(stderr,"Info: probeCcu (%d,%d): send-connect-ok-to-ccu\n",
					CORE_ID, THREAD_ID);
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
		perThreadSendU32FromDebugServerToCcu (CORE_ID, THREAD_ID, server_connect_mode, words_to_ccu[IDX]);
#ifdef VERBOSE
		fprintf(stderr,"Info: probeCcu (%d,%d): sent word_to_ccu[%d] = 0x%x\n",
				CORE_ID, THREAD_ID,
				IDX, words_to_ccu[IDX]);
#endif
	}

	//////////////////////////////////////////////  get info from ccu ////////////////////////////////////////

	// clear the nwords field.
	server_state->ccu_nwords = 0;

	uint32_t ccu_word_1;
	uint8_t ccu_word_1_valid = 0;
	ccu_word_1_valid = perThreadRecvValidCcuMessage (CORE_ID, THREAD_ID, 0, &ccu_word_1);

	if (ccu_word_1_valid)
	{
#ifdef VERBOSE
		fprintf(stderr,"Info: probeCcu (%d, %d): received ccu_word_1 = 0x%x\n", 
						CORE_ID, THREAD_ID, ccu_word_1); 
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
#ifdef VERBOSE
	if(get_second_word)
		fprintf(stderr,"Info: probeCcu (%d, %d): trying to get second word.\n",
				server_state->CORE_ID, server_state->THREAD_ID);
#endif


	uint32_t ccu_word_2;
	if(get_second_word)
	{
		uint8_t ccu_word_2_valid  = 0;
		ccu_word_2_valid = perThreadRecvValidCcuMessage(CORE_ID, THREAD_ID, 1,&ccu_word_2);
#ifdef VERBOSE
		fprintf(stderr,"Info: probeCcu (%d, %d): received ccu_word_2 = 0x%x\n", 
					CORE_ID, THREAD_ID, ccu_word_2); 
#endif
		assert(ccu_word_2_valid);

		server_state->ccu_word_2 = ccu_word_2;
	}


	uint8_t get_third_word = ccu_read_pc_npc_psr;
#ifdef VERBOSE
	if(get_third_word)
		fprintf(stderr,"Info: probeCcu (%d, %d): trying to get third word.\n",
				server_state->CORE_ID, server_state->THREAD_ID);
#endif

	uint32_t ccu_word_3;
	if(get_third_word)
	{
		uint8_t ccu_word_3_valid = 0;
		ccu_word_3_valid  = perThreadRecvValidCcuMessage(CORE_ID, THREAD_ID, 1,&ccu_word_3);
#ifdef VERBOSE
		fprintf(stderr,"Info: probeCcu (%d,%d): received ccu_word_3 = 0x%x\n", 
					CORE_ID, THREAD_ID, ccu_word_3); 
#endif
		assert(ccu_word_3_valid);
	}


	uint8_t get_fourth_word = ccu_read_pc_npc_psr;

#ifdef VERBOSE
	if(get_fourth_word)
		fprintf(stderr,"Info: probeCcu (%d, %d): trying to get fourth word.\n",
				server_state->CORE_ID, server_state->THREAD_ID);
#endif

	uint32_t ccu_word_4;
	if(get_fourth_word)
	{
		uint8_t ccu_word_4_valid = 0;
		ccu_word_4_valid =   perThreadRecvValidCcuMessage(CORE_ID, THREAD_ID, 1,&ccu_word_4);
#ifdef VERBOSE
		fprintf(stderr,"Info: probeCcu (%d,%d): received ccu_word_4 = 0x%x\n", 
							CORE_ID, THREAD_ID, ccu_word_4); 
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
		fprintf(stderr,"Info: probeCcu (%d, %d): set PC=0x%x, NPC=0x%x, PSR=0x%x\n",
				server_state->CORE_ID, server_state->THREAD_ID,
				server_state->PC, server_state->NPC, server_state->PSR);
#endif
	}

	if(server_state->ccu_nwords > 0)
	{
#ifdef VERBOSE
		fprintf(stderr,"Info: leaving probeCcu (%d,%d): ccu_nwords=%d, ccu_word_1=0x%x, ccu_word_2=0x%x, pc=0x%x, npc=0x%x, psr=0x%x\n",
				server_state->CORE_ID, 
				server_state->THREAD_ID,
				server_state->ccu_nwords,
				server_state->ccu_word_1,
				server_state->ccu_word_2,
				server_state->PC,
				server_state->NPC,
				server_state->PSR);
#endif
	}
}

void probeGdb(DebugServerState* server_state, int CORE_ID, int THREAD_ID)
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
		fprintf(stderr,"Info: probeGdb (%d,%d): ccu_command = 0x%x\n", 
					CORE_ID, THREAD_ID, server_state->ccu_word_1);
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
			fprintf(stderr,"Info: probeGdb (%d,%d): trying to send first-word-to-gdb = 0x%x\n", 
						CORE_ID, THREAD_ID, first_word_to_gdb);
#endif
			perThreadSendU32FromDebugServerToGdb(CORE_ID, THREAD_ID, first_word_to_gdb);
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb (%d,%d): sent first-word-to-gdb = 0x%x\n", 
						CORE_ID, THREAD_ID, first_word_to_gdb);
#endif
		}


		uint8_t send_second_word_to_gdb = (server_state->ccu_command.ccu_read_wp_hit | server_state->ccu_command.ccu_write_wp_hit);
		uint32_t second_word_to_gdb =  server_state->WP_REGS[server_state->ccu_command.ccu_wp_reg_index];
		if(send_second_word_to_gdb)
		{
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb: trying to send second-word-to-gdb = 0x%x\n", second_word_to_gdb);
#endif
			perThreadSendU32FromDebugServerToGdb(CORE_ID, THREAD_ID, second_word_to_gdb);
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb (%d,%d): second-word-to-gdb = 0x%x\n", 
						CORE_ID, THREAD_ID, second_word_to_gdb);
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
		gdb_word_1_valid = perThreadRecvValidGdbMessage (CORE_ID, THREAD_ID, 0, &gdb_word_1);
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
			gdb_word_2_valid = perThreadRecvValidGdbMessage (CORE_ID, THREAD_ID, 1, &gdb_word_2);
			assert(gdb_word_2_valid);
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb (%d,%d): received gdb_word_2 = 0x%x\n", 
					CORE_ID, THREAD_ID, gdb_word_2);
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
			fprintf(stderr,"Info: probeGdb (%d,%d): set pc = 0x%x\n", 
						CORE_ID, THREAD_ID, gdb_word_2);
#endif
		}

		if(server_state->gdb_command.gdb_write_npc)
		{
			server_state->NPC = gdb_word_2;
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb (%d,%d): set npc = 0x%x\n", 
						CORE_ID, THREAD_ID, gdb_word_2);
#endif
		}

		if(server_state->gdb_command.gdb_write_psr)
		{
			server_state->PSR = gdb_word_2;
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb (%d,%d): set psr = 0x%x\n", 
						CORE_ID, THREAD_ID, gdb_word_2);
#endif
		}

		get_third_word_from_gdb = server_state->gdb_command.gdb_write_mem;
		if(get_third_word_from_gdb)
		{
			uint8_t gdb_word_3_valid = 0;
			gdb_word_3_valid = perThreadRecvValidGdbMessage (CORE_ID, THREAD_ID, 1, &gdb_word_3);
			assert(gdb_word_3_valid);
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb (%d,%d): received gdb_word_2 = 0x%x\n", 
							CORE_ID, THREAD_ID, gdb_word_3);
#endif
		}

		uint8_t send_pc_or_npc = (server_state->gdb_command.gdb_read_pc ||
				server_state->gdb_command.gdb_read_npc);	
		send_quick_response_to_gdb = send_pc_or_npc;
		if(send_pc_or_npc)
		{
			uint32_t quick_debug_response_word = 
				(server_state->gdb_command.gdb_read_pc ? server_state->PC : server_state->NPC);
			perThreadSendU32FromDebugServerToGdb(CORE_ID, THREAD_ID,  quick_debug_response_word);
#ifdef VERBOSE
			fprintf(stderr,"Info: probeGdb (%d,%d): sent quick-response = 0x%x\n", 
						CORE_ID, THREAD_ID, quick_debug_response_word);
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
		fprintf(stderr,"Info: leaving probeGdb (%d,%d): gdb_nwords=%d, gdb_word_1=0x%x, gdb_word_2=0x%x, gdb_word_3=0x%x, pc=0x%x, npc=0x%x, psr=0x%x\n",
				CORE_ID, THREAD_ID, 
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

void perThreadDebugServerDaemon(void* vid)
{
	uint32_t core_thread_id = *((int*) vid);
	int CORE_ID   = (core_thread_id >> 16) & 0xff;
	int THREAD_ID = (core_thread_id & 0xff);

	DebugServerState server_state;
	initDebugServerState(&server_state, CORE_ID, THREAD_ID);

	while(1) 
	{
		probeCcu(&server_state, CORE_ID, THREAD_ID);
		probeGdb(&server_state, CORE_ID, THREAD_ID);
		usleep(100);
	}
}

DEFINE_THREAD_WITH_ARG (perThreadDebugServerDaemon, core_id);

void startPerThreadDebugServerDaemons (int ncores, int nthreads_per_core)
{
	fprintf(stderr,"Info: entered startPerThreadDebugServerDaemons ncores=%d nthreads=%d.\n",
				ncores, nthreads_per_core);
	
	int C, T;
	for(C = 0; C < ncores; C++)
	{
		for(T = 0; T < nthreads_per_core; T++)
		{
			startPerThreadNoblockDaemon(C, T);

			uint32_t core_thread_id = (C << 16) | T;

			uint32_t* vptr = (uint32_t*) malloc(sizeof(uint32_t));
			*vptr = core_thread_id;

			PTHREAD_DECL(perThreadDebugServerDaemon);
			PTHREAD_CREATE_WITH_ARG(perThreadDebugServerDaemon,((void*)vptr));
		}
	}
}

