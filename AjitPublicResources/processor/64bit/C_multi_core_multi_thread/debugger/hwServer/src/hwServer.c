/*
 * Necessary functions used for the Hardware server
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Pipes.h"
#include "Ancillary.h"
#include "Mmu.h"
#include "AjitThread.h"
#include "hwServerStruct.h"
#include "CacheInterface.h"
#include "ThreadInterface.h"
#include "pipeHandler.h"
#include "hwServer.h"
#include "StartHwServerThreads.h"
#include "ThreadHWserverInterface.h"
#include "Mmu.h"


int SPIHWSENT = 0;
int SPIHWRECV = 0;

hwServerState* makeHwServerState(uint32_t core_id, uint32_t  thread_id)
{
	hwServerState* hs = (hwServerState*) malloc(sizeof(hwServerState));
	hs->Debug_status = 0;

	int I;
	for (I=0; I < 16; I++)
	{
		hs->BP_valid[I] = 0;
		hs->WP_valid[I] = 0;
	}
	sprintf(hs->thread_to_hwserver_id_pipe_name,"THREAD_to_HWSERVER_id_%d_%d", 
								core_id, thread_id);
	sprintf(hs->thread_to_hwserver_state_pipe_name,"THREAD_to_HWSERVER_state_%d_%d", 
								core_id, thread_id);

	sprintf(hs->hwserver_to_thread_pipe_name,"HWSERVER_to_THREAD_%d_%d", 
								core_id, thread_id);

	sprintf(hs->debug_command_pipe_name,"ENV_to_AJIT_debug_command_%d_%d", core_id, thread_id);
	sprintf(hs->debug_response_pipe_name,"AJIT_to_ENV_debug_response_%d_%d", core_id, thread_id);

	return(hs);
}


void hwServer_core(void* vhs)
{
	hwServerState* hs = (hwServerState*) vhs;

	int success = 1;


	// Wait for a connect request from the other side ( either gdb / testbench )
	success = connect_gsb(hs);

	if (success == 0)		{
		printf("Connection established with HW Server !\n");
		// Run the main hardware thread
		runServer(hs);
	}
	else		{
		printf("Connection couldn't be established with HW server\n");
		assert(0);
	}

	return;
}

int connect_gsb(hwServerState* hs)
{
	spi_cmd cmd_in;

	recv_spi(hs, &cmd_in);
	// Receive the first command from gdb server bridge to hardware server serial link
	while ( cmd_in.opcode != 14 )
	{
		// Wait till the CONNECT request comes from Server to Processor Interface ( i.e, from gdb server bridge)

		recv_spi(hs, &cmd_in);
	}

	hs->Debug_status = 1;
	return 0;

}

int runServer(hwServerState* hs)
{
	uint8_t msg_id = 0;
	spi_rsp rsp_out;
	spi_cmd cmd_in;

	ThreadState* ajit;
	int bp_match, wp_match;
	uint32_t mem_address;


	while(1)	{

		// Wait for a message from the processor
		msg_id = read_uint8(hs->thread_to_hwserver_id_pipe_name);
		ajit = (ThreadState*) read_uint64(hs->thread_to_hwserver_state_pipe_name);

		if ((msg_id == GDB_INITIAL_STOP) || (msg_id == GDB_RESET))	
		{		// Processor is in initial stop state or reset
			printf("Hardware Server for cpu-id %d started !\n", ajit->thread_id);

			rsp_out.rsp = 'S';
			rsp_out.id = msg_id;			// '0' for initial stop and '1' for reset
			rsp_out.data = 0;
			send_spi(hs, &rsp_out);		// Send "S ID"

			recv_spi(hs, &cmd_in);
			// Receive the commands from gdb server bridge to hardware server serial link

			while ( cmd_in.opcode != 16 && cmd_in.opcode != 15 )
			{
				// Wait till the "continue" comes from Server to Processor Interface ( i.e, from gdb server bridge)
				execute_spi(ajit, hs, &cmd_in);
				recv_spi(hs, &cmd_in);
			}
			if (cmd_in.opcode == 15 )
			{
				execute_spi(ajit, hs, &cmd_in);
			}

			// Inform the processor to "CONT"
			write_uint32(hs->hwserver_to_thread_pipe_name, 0x434F4E54);
#ifdef GDB_DBG
			printf ("HWServer (cpu-id %d): post-Initial-stop: signalled cpu to continue  !\n", 
					hs->thread_id);
#endif
		}
		else if (msg_id == GDB_IFETCH)	{	// Processor finished fetching instruction
#ifdef GDB_DBG
			printf ("HWServer (cpu-id %d): post-Ifetch: Processor fetched instruction  !\n",
					hs->thread_id);
#endif
			bp_match = check_for_bp(hs,ajit->status_reg.pc);	// Check for breakpoints

			if (bp_match == 1 && hs->Debug_status == 1)	{
#ifdef GDB_DBG
				printf("HWServer (core-id=%d,thread-id=%d) : Breakpoint match found!\n", 
							hs->core_id, hs->thread_id);
#endif
				//clear_bp(ajit->status_reg.pc);		// Clear the active breakpoint
				rsp_out.rsp = 'S';
				rsp_out.id = 5;
				rsp_out.data = 0;
				send_spi(hs, &rsp_out);	// Send "SIG 5" for breakpoint occurance

				recv_spi(hs, &cmd_in);
				// Receive the commands from gdb server bridge to hardware server serial link

				while ( cmd_in.opcode != 16 && cmd_in.opcode != 15 )
				{
					// Wait till the "continue" comes from Server to Processor Interface ( i.e, from gdb server bridge)
					execute_spi(ajit,hs, &cmd_in);
					recv_spi(hs, &cmd_in);
				}
				if (cmd_in.opcode == 15 )
				{
					execute_spi(ajit, hs, &cmd_in);
				}

				// Inform the processor to "CONT"
				write_uint32(hs->hwserver_to_thread_pipe_name, 0x434F4E54);	
#ifdef GDB_DBG
				printf ("HWServer (cpu-id %d): post-Ifetch-breakpoint: signalled cpu to continue  !\n",
						hs->thread_id);
#endif

			}
			else	
			{
				// Inform the processor to "continue"
				write_uint32(hs->hwserver_to_thread_pipe_name, 0x434F4E54);
#ifdef GDB_DBG
				printf ("HWServer (cpu-id %d): post-Ifetch-no-breakpoint: signalled cpu to continue  !\n",
						hs->thread_id);
#endif
			}
		}
		else if (msg_id == GDB_MEM_ACCESS)	
		{	// Processor finished calculating address
			mem_address = read_uint64(hs->thread_to_hwserver_state_pipe_name);
			wp_match = check_for_wp(hs,getSlice32(mem_address, 31, 0));	// Check for watchpoints
#ifdef GDB_DBG
			printf ("HWServer (cpu-id %d): post-mem-access: cpu accessed location 0x%x  !\n",
					hs->thread_id,  mem_address);
#endif

			if (wp_match == 1 && hs->Debug_status == 1)	{
				//clear_wp(mem_address);		// Clear the active watchpoint
				rsp_out.rsp = 'S';
				rsp_out.id = 6;
				rsp_out.data = mem_address;
				send_spi(hs, &rsp_out);	// Send "SIG 6" for watchpoint occurance

				recv_spi(hs, &cmd_in);
				// Receive the commands from gdb server bridge to hardware server serial link

				while ( cmd_in.opcode != 16 && cmd_in.opcode != 15 )
				{
					// Wait till the "continue" comes from Server to Processor Interface ( i.e, from gdb server bridge)
					execute_spi(ajit,hs, &cmd_in);
					recv_spi(hs, &cmd_in);
				}
				if (cmd_in.opcode == 15 )
					execute_spi(ajit,hs, &cmd_in);

				// Inform the processor to "continue"
				write_uint32(hs->hwserver_to_thread_pipe_name, 0x434F4E54);
#ifdef GDB_DBG
				printf ("HWServer (cpu-id %d): post-mem-access-watchpoint: signalled cpu to continue  !\n",
						hs->thread_id);
#endif
			}
			else	
			{
				// Inform the processor to "continue"
				write_uint32(hs->hwserver_to_thread_pipe_name, 0x434F4E54);
#ifdef GDB_DBG
				printf ("HWServer (cpu-id %d): post-mem-access-no-watchpoint: signalled cpu to continue  !\n",
						hs->thread_id);
#endif
			}
		}
		else if (msg_id == GDB_TRAP_OCCURED)	
		{	// Processor went into trap mode

#ifdef GDB_DBG
			printf ("HWServer (cpu-id %d): post-trap: cpu trapped  !\n", hs->thread_id);
#endif
			if ( hs->Debug_status == 1 )
			{
				rsp_out.rsp = 'S';
				rsp_out.id = 9;
				rsp_out.data = ajit->trap_vector;
				send_spi(hs, &rsp_out);	// Send "SIG 9" for trap occurance

				recv_spi(hs, &cmd_in);
				// Receive the commands from gdb server bridge to hardware server serial link

				while ( cmd_in.opcode != 16 && cmd_in.opcode != 15 )
				{
					// Wait till the "continue" comes from Server to Processor Interface ( i.e, from gdb server bridge)
					execute_spi(ajit,hs, &cmd_in);
					recv_spi(hs,&cmd_in);
				}
				if (cmd_in.opcode == 15 )
				{
					execute_spi(ajit,hs, &cmd_in);
				}
			}		
			// Inform the processor to "continue"
			write_uint32(hs->hwserver_to_thread_pipe_name, 0x434F4E54);
#ifdef GDB_DBG
			printf ("HWServer (cpu-id %d): post-trap: signalled cpu to continue  !\n",
					hs->thread_id);
#endif
		}
		else if (msg_id == DOVAL_PROC_ENTERED_ERROR_MODE)	
		{	// Processor finished execution

			if ( hs->Debug_status == 1 )
			{
				printf ("\nReached HwServer - TA 0 (cpu-id=%d)\n", hs->thread_id);
				rsp_out.rsp = 'T';
				rsp_out.id = 0;
				rsp_out.data = 0;
				send_spi(hs, &rsp_out);	// Send "TA 0" for execution completion

				recv_spi(hs, &cmd_in);
				// Receive the commands from gdb server bridge to hardware server serial link

				while ( cmd_in.opcode != 16 && cmd_in.opcode != 15)
				{
					// Wait till the "continue" comes from Server to Processor Interface ( i.e, from gdb server bridge)
					execute_spi(ajit,hs,  &cmd_in);
					recv_spi(hs, &cmd_in);
				}
				if (cmd_in.opcode == 15 )
					execute_spi(ajit, hs, &cmd_in);
			}

			// Inform the processor to "continue"
			write_uint32(hs->hwserver_to_thread_pipe_name, 0x434F4E54);

		}
		else	{
			// Inform the processor to "continue"
			write_uint32(hs->hwserver_to_thread_pipe_name, 0x434F4E54);
		}
	}
	return 0;
}

//Recieve a single command from the Server to Processor Interface (SPI)
int recv_spi(hwServerState* hs, spi_cmd *cmd_out)
{

	int CC = 0;
	uint32_t spi_string;
	spi_string = read_uint32(hs->debug_command_pipe_name);		// Receive command through the serial line ( implemented as pipe )
	CC++;
#ifdef GDB_DBG
	printf ("HWSERVER[%d]: Recieved message word 1:  0x%x  (cpu-id=%d)\n", SPIHWRECV, spi_string, hs->thread_id);
#endif

	uint8_t length =  getSlice32(spi_string, 31, 24);
	cmd_out->opcode = (uint8_t) getSlice32(spi_string, 23, 16);
	cmd_out->command =  (uint16_t) getSlice32(spi_string, 15, 0);


	assert(cmd_out->opcode != 0);

	if (length == 1)	{
		cmd_out->address = 0;
		cmd_out->data = 0;
	}
	else if (length == 2)	{
		uint32_t word_2 = read_uint32(hs->debug_command_pipe_name);
		CC++;
#ifdef GDB_DBG
		printf ("HWSERVER : Recieved message word 2:  0x%x  (cpu-id=%d)\n", word_2, hs->thread_id);
#endif
		if ( cmd_out->opcode == 2 || cmd_out->opcode == 4 || cmd_out->opcode == 18 )	{
			cmd_out->address = 0;
			cmd_out->data = word_2;		// Read the second word as data
		}
		else if ( cmd_out->opcode == 8 || cmd_out->opcode == 9 || cmd_out->opcode == 10 || cmd_out->opcode == 11 || cmd_out->opcode == 6)		{
			cmd_out->address = word_2;		// Read the second word as address
			cmd_out->data = 0;
		}

	}
	else if (length == 3)	{
		cmd_out->address = read_uint32(hs->debug_command_pipe_name);		// Receive address through the serial line
		CC++;
		cmd_out->data = read_uint32(hs->debug_command_pipe_name);		// Receive content through the serial line
		CC++;
#ifdef GDB_DBG
		printf ("HWSERVER : Recieved message words 2,3:  0x%x 0x%x (cpu-id=%d)\n", cmd_out->address,
				cmd_out->data, hs->thread_id);
#endif
	}

	if ( cmd_out->opcode == 15 )
	{
		hs->Debug_status = 0;
	}

#ifdef GDB_DBG
	char pbuffer[256];
	sprintf(pbuffer,"SPIHWRECV [%d] [%d]", SPIHWRECV,CC);
	logMessageToStderr(pbuffer);
#endif

	SPIHWRECV++;
	return 0;
}

//Send a single command from the Server to Processor Interface (SPI)
int send_spi(hwServerState* hs, spi_rsp *rsp_in)
{
	uint32_t send_word = 0;

	if (rsp_in-> rsp == 'O')	{
		send_word = 0x00004F4B;
		// Send back "OK" message to the software server
		write_uint32(hs->debug_response_pipe_name, send_word);
#ifdef GDB_DBG
		printf ("HWSERVER[%d]: Sent message word 1:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif
	}
	else if (rsp_in-> rsp == 'S')	{
		// Send back "SIG ID" message to the software server
#ifdef GDB_DBG
		printf ("HWServer : rsp=S. Sending SPI message - SIG %i (cpu-id=%d)\n",rsp_in-> id,
				hs->thread_id);	// Just to check
#endif
		if (rsp_in-> id == 0)	{
			send_word = 0x53494700;
			write_uint32(hs->debug_response_pipe_name, send_word);		// SIG00 - Initial dummy breakpoint
#ifdef GDB_DBG
			printf ("HWSERVER[%d]: Sent message word 1:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif
		}
		else if	(rsp_in-> id == 1)	{
			send_word = 0x53494703;
			write_uint32(hs->debug_response_pipe_name, send_word);		// SIG03 - processor reset = Quit
#ifdef GDB_DBG
			printf ("HWSERVER[%d]: Sent message word 1:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif
		}
		else if	(rsp_in-> id == 5)	{
			send_word = 0x53494705;
			write_uint32(hs->debug_response_pipe_name, send_word);		// SIG05 - Breakpoint hit
#ifdef GDB_DBG
			printf ("HWSERVER[%d]: Sent message word 1:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif
		}
		else if	(rsp_in-> id == 6)	{

			send_word = 0x53494706;
			write_uint32(hs->debug_response_pipe_name, send_word);		// SIG06 - Watchpoint hit
#ifdef GDB_DBG
			printf ("HWSERVER[%d]: Sent message word 1:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif

			send_word = rsp_in->data;	
			write_uint32(hs->debug_response_pipe_name, rsp_in-> data);
#ifdef GDB_DBG
			printf ("HWSERVER[%d]: Sent message word 2:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif
		}
		else if	(rsp_in-> id == 2)	{
			send_word = 0x53494721;
			write_uint32(hs->debug_response_pipe_name, send_word);		// SIG21 - Breakpoint registers are full
#ifdef GDB_DBG
			printf ("HWSERVER[%d]: Sent message word 1:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif
		}
		else if	(rsp_in-> id == 3)	{
			send_word = 0x53494722;
			write_uint32(hs->debug_response_pipe_name, send_word);		// SIG22 - Watchpoint registers are full
#ifdef GDB_DBG
			printf ("HWSERVER[%d]: Sent message word 1:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif
		}
		else if	(rsp_in-> id == 9)	{
			send_word = 0x53494709;
			write_uint32(hs->debug_response_pipe_name, send_word);		// SIG9 - Processor trapped
#ifdef GDB_DBG
			printf ("HWSERVER[%d]: Sent message word 1:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif
			send_word = rsp_in->data;
			write_uint32(hs->debug_response_pipe_name, send_word);
#ifdef GDB_DBG
			printf ("HWSERVER[%d]: Sent message word 2:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif

		}
		else
		{
			assert(0);
		}
	}
	else if (rsp_in-> rsp == 'T')	{	// If the reply is 'TA 0' hit

		send_word = 0x54412030;
		// Send back 'TA 0' Message
		write_uint32(hs->debug_response_pipe_name, send_word);
#ifdef GDB_DBG
		printf ("HWSERVER[%d]: Sent message word 1:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif
	}
	else if (rsp_in-> rsp == 'C')	{	// If the reply is data / memory content

		send_word = rsp_in->data;
		// Send back Memory/Register message to the software server
		write_uint32(hs->debug_response_pipe_name, send_word);
#ifdef GDB_DBG
		printf ("HWSERVER[%d]: Sent message word 1:  0x%x  (cpu-id=%d)\n", SPIHWSENT, send_word, hs->thread_id);
#endif
	}
	else
	{
		assert(0);
	}

#ifdef GDB_DBG
	char pbuffer[256];
	sprintf(pbuffer,"SPIHWSENT [%d]", SPIHWSENT);
	logMessageToStderr(pbuffer);
#endif

	SPIHWSENT++;
	return 0;
}


int check_for_bp(hwServerState* hs, uint32_t address)		// Check for the existance of a break point
{
	int i = 0;

	while (i < 16)	{
		if (hs->BP_valid[i] == 1 && hs->BP_list[i] == address) 	{
#ifdef GDB_DBG
			printf ("HWServer : Breakpoint reached at PC = %x (cpu-id %d)\n", address,
					hs->thread_id);
#endif
			return 1;
		}
		i++;
	}
	return 0;
}


int clear_bp(hwServerState* hs, uint32_t address)		// Clear a breakpoint
{
	int i = 0;

	while (i < 16)	{
		if (hs->BP_list[i] == address) 	{
#ifdef GDB_DBG
			printf ("HWServer : Cleared Breakpoint at PC = %x (cpu-id=%d)\n", 
					address, hs->thread_id);
#endif
			hs->BP_valid[i] = 0;
			break;
		}
		i++;
	}
	return 0;
}

int set_bp(hwServerState* hs, uint8_t reg_id, uint32_t address)		// Set a breakpoint
{
	int i = (int)reg_id;
#ifdef GDB_DBG
	printf ("HWServer : Set Breakpoint at PC = %x Reg = %d (cpu-id=%d)\n", address,i, hs->thread_id);
#endif
	hs->BP_list[i] = address;
	hs->BP_valid[i] = 1;
	return 1;
}


int check_for_wp(hwServerState* hs, uint32_t address)		// Check for the existance of a watch point
{
	int i = 0;

	while (i < 16)	{
		if (hs->WP_valid[i] == 1 && hs->WP_list[i] == address) 	{
#ifdef GDB_DBG
			printf ("HWServer : Watchpoint reached at Address = %x (cpu-id=%d)\n", 
					address, hs->thread_id);
#endif
			return 1;
		}
		i++;
	}
	return 0;
}

int clear_wp(hwServerState* hs, uint32_t address)		// Clear a watchpoint
{
	int i = 0;

	while (i < 16)	{
		if (hs->WP_list[i] == address) 	{
#ifdef GDB_DBG
			printf ("HWServer : Cleared Watchpoint at address = %x in Reg %d (cpu-id=%d)\n", 
					address, i, hs->thread_id);
#endif
			hs->WP_valid[i] = 0;
			break;
		}
		i++;
	}
	return 0;
}

int set_wp(hwServerState* hs, uint8_t reg_id, uint32_t address)		// Set a watchpoint
{
	int i = (int)reg_id;
#ifdef GDB_DBG
	printf ("HWServer : Set Watchpoint at PC = %x in WP Reg %d (cpu-id=%d)\n", address, i,
			hs->thread_id);
#endif
	hs->WP_list[i] = address;
	hs->WP_valid[i] = 1;
	return 1;

}

int execute_spi(ThreadState *ajit_state, hwServerState* hs, spi_cmd *cmd_exe)	// Execute a single SPI command
{
	uint32_t reg_data, mem_data;
	uint8_t read_mae, write_mae, byte_mask;
	int bp_success = 0, wp_success = 0;
	spi_rsp rsp_out;

	RegisterFile* rf = ajit_state->register_file;


	if (cmd_exe->opcode == 1)	{		// Read integer register content
		if ( getSlice32(cmd_exe->command, 10, 10) == 1)		{		// General purpose registers
			uint8_t cwp = getSlice32(ajit_state->status_reg.psr, 4, 0);	// Get the current window state
			reg_data = readRegister(rf, (uint8_t)getSlice32(cmd_exe->command, 4, 0), cwp);		// Read register contents
		}
		else if ( getSlice32(cmd_exe->command, 9, 9) == 1)		{		// Read PSR
			reg_data = ajit_state->status_reg.psr;
		}
		else if ( getSlice32(cmd_exe->command, 8, 8) == 1)		{		// Read WIM
			reg_data = ajit_state->status_reg.wim;
		}
		else if ( getSlice32(cmd_exe->command, 7, 7) == 1)		{		// Read TBR
			reg_data = ajit_state->status_reg.tbr;
		}
		else if ( getSlice32(cmd_exe->command, 6, 6) == 1)		{		// Read Y
			reg_data = ajit_state->status_reg.y;
		}
		else if ( getSlice32(cmd_exe->command, 5, 5) == 1)		{		// Read ASR
			reg_data = getAsrValue(ajit_state, (int)getSlice32(cmd_exe->command, 4, 0));
				//ajit_state->status_reg.asr[(int)getSlice32(cmd_exe->command, 4, 0)];
		}
		rsp_out.rsp = 'C';
		rsp_out.id = 0;
		rsp_out.data = reg_data;
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 2)	{		// Write integer register content

		reg_data = cmd_exe->data;
		if ( getSlice32(cmd_exe->command, 10, 10) == 1)		{		// General purpose registers
			uint8_t cwp = getSlice32(ajit_state->status_reg.psr, 4, 0);	// Get the current window state			
			writeRegister(ajit_state->status_reg.pc, 
				rf, (uint8_t)getSlice32(cmd_exe->command, 4, 0), cwp, reg_data);		// Write register contents
		}
		else if ( getSlice32(cmd_exe->command, 9, 9) == 1)		{		// Write PSR
			ajit_state->status_reg.psr = reg_data;
		}
		else if ( getSlice32(cmd_exe->command, 8, 8) == 1)		{		// Write WIM
			ajit_state->status_reg.wim = reg_data;
		}
		else if ( getSlice32(cmd_exe->command, 7, 7) == 1)		{		// Write TBR
			ajit_state->status_reg.tbr = reg_data;
		}
		else if ( getSlice32(cmd_exe->command, 6, 6) == 1)		{		// Write Y
			ajit_state->status_reg.y = reg_data;
		}
		else if ( getSlice32(cmd_exe->command, 5, 5) == 1)		{		// Write ASR
			ajit_state->status_reg.asr[(int)getSlice32(cmd_exe->command, 4, 0)] = reg_data;
		}
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 3)	{		// Read FP register content
		if ( getSlice32(cmd_exe->command, 5, 5) == 1)		{
			reg_data = ajit_state->status_reg.fsr;				// Read FSR register
		}
		else	{
			reg_data = readFRegister(rf, (uint8_t)(getSlice32(cmd_exe->command, 4, 0)));		// Read FLOATING POINT register contents
		}
		rsp_out.rsp = 'C';
		rsp_out.id = 0;
		rsp_out.data = reg_data;
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 4)	{		// Write FP register content
		if ( getSlice32(cmd_exe->command, 5, 5) == 1)		{
			ajit_state->status_reg.fsr = cmd_exe->data;				// Write FSR register
		}
		else	{
			writeFRegister(rf, (uint8_t)(getSlice32(cmd_exe->command, 4, 0)), cmd_exe->data );		// Write FLOATING POINT register contents
		}
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 13)	{		// Read PC, NPC
		if ( getSlice32(cmd_exe->command, 0, 0) == 1)		{
			reg_data = ajit_state->status_reg.pc;				// Read PC
		}
		else if ( getSlice32(cmd_exe->command, 1, 1) == 1) {
			reg_data = ajit_state->status_reg.npc;		// Read NPC
		}

		rsp_out.rsp = 'C';
		rsp_out.id = 0;
		rsp_out.data = reg_data;
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 17 )	{	// Read CPSR
		reg_data = ajit_state->status_reg.csr;
		rsp_out.rsp = 'C';
		rsp_out.id = 0;
		rsp_out.data = reg_data;
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 18 )	{	// Write to CPSR
		ajit_state->status_reg.csr = cmd_exe->data;
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 6)	{		// Read memory content
		readDataToDebug(ajit_state->core_id, ajit_state->thread_id, getThreadContext(ajit_state),
				ajit_state->mmu_state,  ajit_state->dcache,
				(uint8_t)getSlice32(cmd_exe->command, 7, 0), 
				0xFF, // byte-mask..
				cmd_exe->address, &read_mae, &mem_data);	// Populate mem_data with memory content

		rsp_out.rsp = 'C';
		rsp_out.id = 0;
		rsp_out.data = mem_data;
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 7)	{
		if ((uint8_t)getSlice32(cmd_exe->command, 11, 8) == 1 )	{
			byte_mask = 0x1;
		}
		else if ((uint8_t)getSlice32(cmd_exe->command, 11, 8) == 2 )	{
			byte_mask = 0x3;
		}
		else if ((uint8_t)getSlice32(cmd_exe->command, 11, 8) == 3 )	{
			byte_mask = 0x7;
		}
		else	{
			byte_mask = 0xF;
		}


		writeDataFromDebug(ajit_state->core_id, ajit_state->thread_id, getThreadContext(ajit_state),
				ajit_state->mmu_state, ajit_state->dcache,
				(uint8_t)getSlice32(cmd_exe->command, 7, 0), 
				cmd_exe->address, byte_mask, cmd_exe->data, 
				&write_mae); // write to cmd_exe->address
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 8)	{	// Set BP
		bp_success = set_bp(hs, (uint8_t)cmd_exe->command, cmd_exe->address);
		if ( bp_success == 1)	{
			rsp_out.rsp = 'O';		// Send "OK" reply
			rsp_out.id = 0;
			rsp_out.data = 0;
		}
		else	{		// Send "SIG2" reply
			rsp_out.rsp = 'S';
			rsp_out.id = 2;
			rsp_out.data = 0;
		}
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 9)	{	// Clear BP
		clear_bp(hs,cmd_exe->address);
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 10)	{	// Set WP
#ifdef GDB_DBG
		printf("We got Reg %d here !\n", (int)cmd_exe->command);
#endif
		wp_success = set_wp(hs, (uint8_t)cmd_exe->command, cmd_exe->address);
		if ( wp_success == 1)	{
			rsp_out.rsp = 'O';		// Send "OK" reply
			rsp_out.id = 0;
			rsp_out.data = 0;
		}
		else	{		// Send "SIG3" reply
			rsp_out.rsp = 'S';
			rsp_out.id = 3;
			rsp_out.data = 0;
		}
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 11)	{	// Clear WP
		clear_wp(hs, cmd_exe->address);
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(hs, &rsp_out);
	}
	else if (cmd_exe->opcode == 15)	{
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(hs, &rsp_out);
	}
	else
	{
		assert(0);
	}

	return(0);
}
