/*
 * Necessary functions used for the Hardware server
 */

#include <stdio.h>
#include <string.h>
#include "Pipes.h"
#include "Ancillary.h"
#include "CpuInterface.h"
#include "pipeHandler.h"
#include "hwServer.h"
#include "StartHwServerThreads.h"
#include "CpuHWserverInterface.h"


// Array to store 16 breakpoints and 16 watchpoints
uint32_t BP_list[16];
uint32_t WP_list[16];
// One location corresponding to the validity of each break / watch points ( '1' means active and '0' means cleared )
int BP_valid[16];
int WP_valid[16];

int Debug_status = 0;
// Main hardware server function
int hwServer(char* result, char* log)
{
	int success = 1, i = 0;

	// Make all the break / watch points available for use
	for (i=0; i< 16 ; i++)	{
		BP_valid[i] = 0;
		WP_valid[i] = 0;
	}

	// Wait for a connect request from the other side ( either gdb / testbench )
	success = connect_gsb();

	if (success == 0)		{
		printf("Connection established with HW Server !\n");
		// Run the main hardware thread
		runServer();
	}
	else		{
		printf("Connection couldn't be established with HW server\n");
	}

	return success;
}

int connect_gsb()
{
	spi_cmd cmd_in;

	recv_spi(&cmd_in);
	// Receive the first command from gdb server bridge to hardware server serial link
	while ( cmd_in.opcode != 14 )
	{
	// Wait till the CONNECT request comes from Server to Processor Interface ( i.e, from gdb server bridge)

	recv_spi(&cmd_in);
	}
	Debug_status = 1;
	return 0;

}

int runServer()
{
	uint8_t msg_id = 0;
	spi_rsp rsp_out;
	spi_cmd cmd_in;

	ProcessorState* ajit;
	int bp_match, wp_match;
	uint32_t mem_address;

	printf("Hardware Server started !\n");

	while(1)	{

		// Wait for a message from the processor
		msg_id = read_uint8("CPU_to_HWSERVER_id");
		ajit = (ProcessorState*) read_uint64("CPU_to_HWSERVER_state");

		if ((msg_id == GDB_INITIAL_STOP) || (msg_id == GDB_RESET))	
		{		// Processor is in initial stop state or reset
				rsp_out.rsp = 'S';
				rsp_out.id = msg_id;			// '0' for initial stop and '1' for reset
				rsp_out.data = 0;
				send_spi(&rsp_out);		// Send "S ID"

				recv_spi(&cmd_in);
				// Receive the commands from gdb server bridge to hardware server serial link

				while ( cmd_in.opcode != 16 && cmd_in.opcode != 15 )
				{
					// Wait till the "continue" comes from Server to Processor Interface ( i.e, from gdb server bridge)
					execute_spi(ajit, &cmd_in);
					recv_spi(&cmd_in);
				}
				if (cmd_in.opcode == 15 )
				{
					execute_spi(ajit, &cmd_in);
				}
					
				write_uint32("HWSERVER_to_CPU", 0x434F4E54);	// Inform the processor to "CONT"
		}
		else if (msg_id == GDB_IFETCH)	{	// Processor finished fetching instruction
			#ifdef GDB_DBG
			printf ("HWServer : Processor fetched instruction  !\n");
			#endif
			bp_match = check_for_bp(ajit->status_reg.pc);	// Check for breakpoints

			if (bp_match == 1 && Debug_status == 1)	{
				#ifdef GDB_DBG
				printf("HWServer : Breakpoint match found!\n" );
				#endif
				//clear_bp(ajit->status_reg.pc);		// Clear the active breakpoint
				rsp_out.rsp = 'S';
				rsp_out.id = 5;
				rsp_out.data = 0;
				send_spi(&rsp_out);	// Send "SIG 5" for breakpoint occurance

				recv_spi(&cmd_in);
				// Receive the commands from gdb server bridge to hardware server serial link

				while ( cmd_in.opcode != 16 && cmd_in.opcode != 15 )
				{
					// Wait till the "continue" comes from Server to Processor Interface ( i.e, from gdb server bridge)
					execute_spi(ajit, &cmd_in);
					recv_spi(&cmd_in);
				}
				if (cmd_in.opcode == 15 )
				{
					execute_spi(ajit, &cmd_in);
				}

				write_uint32("HWSERVER_to_CPU", 0x434F4E54);	// Inform the processor to "CONT"

			}
			else	
			{
				write_uint32("HWSERVER_to_CPU", 0x434F4E54);	// Inform the processor to "continue"
			}
		}
		else if (msg_id == GDB_MEM_ACCESS)	
		{	// Processor finished calculating address
			mem_address = read_uint64("CPU_to_HWSERVER_state");
			wp_match = check_for_wp(getSlice32(mem_address, 31, 0));	// Check for watchpoints

			if (wp_match == 1 && Debug_status == 1)	{
				//clear_wp(mem_address);		// Clear the active watchpoint
				rsp_out.rsp = 'S';
				rsp_out.id = 6;
				rsp_out.data = mem_address;
				send_spi(&rsp_out);	// Send "SIG 6" for watchpoint occurance

				recv_spi(&cmd_in);
				// Receive the commands from gdb server bridge to hardware server serial link

				while ( cmd_in.opcode != 16 && cmd_in.opcode != 15 )
				{
					// Wait till the "continue" comes from Server to Processor Interface ( i.e, from gdb server bridge)
					execute_spi(ajit, &cmd_in);
					recv_spi(&cmd_in);
				}
				if (cmd_in.opcode == 15 )
					execute_spi(ajit, &cmd_in);

				write_uint32("HWSERVER_to_CPU", 0x434F4E54);	// Inform the processor to "continue"
			}
			else	
			{
				write_uint32("HWSERVER_to_CPU", 0x434F4E54);	// Inform the processor to "continue"
			}
		}
		else if (msg_id == GDB_TRAP_OCCURED)	
		{	// Processor went into trap mode

			if ( Debug_status == 1 )
			{
				rsp_out.rsp = 'S';
				rsp_out.id = 9;
				rsp_out.data = ajit->trap_vector;
				send_spi(&rsp_out);	// Send "SIG 9" for trap occurance

				recv_spi(&cmd_in);
				// Receive the commands from gdb server bridge to hardware server serial link

				while ( cmd_in.opcode != 16 && cmd_in.opcode != 15 )
				{
					// Wait till the "continue" comes from Server to Processor Interface ( i.e, from gdb server bridge)
					execute_spi(ajit, &cmd_in);
					recv_spi(&cmd_in);
				}
				if (cmd_in.opcode == 15 )
				{
					execute_spi(ajit, &cmd_in);
				}
			}		
			write_uint32("HWSERVER_to_CPU", 0x434F4E54);	// Inform the processor to "continue"
		}
		else if (msg_id == DOVAL_PROC_ENTERED_ERROR_MODE)	
		{	// Processor finished execution

			if ( Debug_status == 1 )
			{
				printf ("\nReached HwServer - TA 0\n");
				rsp_out.rsp = 'T';
				rsp_out.id = 0;
				rsp_out.data = 0;
				send_spi(&rsp_out);	// Send "TA 0" for execution completion

				recv_spi(&cmd_in);
				// Receive the commands from gdb server bridge to hardware server serial link

				while ( cmd_in.opcode != 16 && cmd_in.opcode != 15)
				{
					// Wait till the "continue" comes from Server to Processor Interface ( i.e, from gdb server bridge)
					execute_spi(ajit, &cmd_in);
					recv_spi(&cmd_in);
				}
				if (cmd_in.opcode == 15 )
					execute_spi(ajit, &cmd_in);
			}

			write_uint32("HWSERVER_to_CPU", 0x434F4E54);	// Inform the processor to "CONT"

		}
		else	{
			write_uint32("HWSERVER_to_CPU", 0x434F4E54);	// Inform the processor to "CONT"
		}
	}
	return 0;
}

//Recieve a single command from the Server to Processor Interface (SPI)
int recv_spi(spi_cmd *cmd_out)
{
	uint32_t spi_string;
	spi_string = read_uint32("ENV_to_AJIT_debug_command");		// Receive command through the serial line ( implemented as pipe )

	uint8_t length =  getSlice32(spi_string, 31, 24);
	cmd_out->opcode = (uint8_t) getSlice32(spi_string, 23, 16);
	cmd_out->command =  (uint16_t) getSlice32(spi_string, 15, 0);

	#ifdef GDB_DBG
	printf ("HWSERVER : Recieved message - %x %x\n", cmd_out->opcode, cmd_out->command);
	#endif

	if (length == 1)	{
		cmd_out->address = 0;
		cmd_out->data = 0;
	}
	else if (length == 2)	{
		if ( cmd_out->opcode == 2 || cmd_out->opcode == 4 || cmd_out->opcode == 18 )	{
			cmd_out->address = 0;
			cmd_out->data = read_uint32("ENV_to_AJIT_debug_command");		// Read the second word as data
		}
		else if ( cmd_out->opcode == 8 || cmd_out->opcode == 9 || cmd_out->opcode == 10 || cmd_out->opcode == 11 || cmd_out->opcode == 6)		{
			cmd_out->address = read_uint32("ENV_to_AJIT_debug_command");		// Read the second word as address
			cmd_out->data = 0;
		}

	}
	else if (length == 3)	{
		cmd_out->address = read_uint32("ENV_to_AJIT_debug_command");		// Receive address through the serial line
		cmd_out->data = read_uint32("ENV_to_AJIT_debug_command");		// Receive content through the serial line
	}
	
	if ( cmd_out->opcode == 15 )
	{
		Debug_status = 0;
	}
	return 0;
}

//Send a single command from the Server to Processor Interface (SPI)
int send_spi(spi_rsp *rsp_in)
{

	if (rsp_in-> rsp == 'O')	{
		// Send back "OK" message to the software server
		write_uint32("AJIT_to_ENV_debug_response", 0x00004F4B);
		#ifdef GDB_DBG
		printf ("HWServer : rsp=0. Sending SPI message - OK\n");	// Just to check
		#endif
	}
	else if (rsp_in-> rsp == 'S')	{
		// Send back "SIG ID" message to the software server
		#ifdef GDB_DBG
		printf ("HWServer : rsp=S. Sending SPI message - SIG %i\n",rsp_in-> id);	// Just to check
		#endif
		if (rsp_in-> id == 0)	{
			write_uint32("AJIT_to_ENV_debug_response", 0x53494700);		// SIG00 - Initial dummy breakpoint
		}
		else if	(rsp_in-> id == 1)	{
			write_uint32("AJIT_to_ENV_debug_response", 0x53494703);		// SIG03 - processor reset = Quit
		}
		else if	(rsp_in-> id == 5)	{
			write_uint32("AJIT_to_ENV_debug_response", 0x53494705);		// SIG05 - Breakpoint hit
		}
		else if	(rsp_in-> id == 6)	{
			write_uint32("AJIT_to_ENV_debug_response", 0x53494706);		// SIG06 - Watchpoint hit
			write_uint32("AJIT_to_ENV_debug_response", rsp_in-> data);
		}
		else if	(rsp_in-> id == 2)	{
			write_uint32("AJIT_to_ENV_debug_response", 0x53494721);		// SIG21 - Breakpoint registers are full
		}
		else if	(rsp_in-> id == 3)	{
			write_uint32("AJIT_to_ENV_debug_response", 0x53494722);		// SIG22 - Watchpoint registers are full
		}
		else if	(rsp_in-> id == 9)	{
			write_uint32("AJIT_to_ENV_debug_response", 0x53494709);		// SIG9 - Processor trapped
			write_uint32("AJIT_to_ENV_debug_response", rsp_in-> data);
		}
		else	{
			printf("Error : Unknown SIG ID");
		}

	}
	else if (rsp_in-> rsp == 'T')	{	// If the reply is 'TA 0' hit
		// Send back 'TA 0' Message
		write_uint32("AJIT_to_ENV_debug_response", 0x54412030);
		#ifdef GDB_DBG
		printf("HWServer : rsp=T. Sending SPI message - %x\n",rsp_in->data);
		#endif
	}
	else if (rsp_in-> rsp == 'C')	{	// If the reply is data / memory content
		// Send back Memory/Register message to the software server
		write_uint32("AJIT_to_ENV_debug_response", rsp_in->data);
		#ifdef GDB_DBG
		printf("HWServer : rsp=C. Sending SPI message - %x\n",rsp_in->data);
		#endif
	}

	return 0;
}


int check_for_bp(uint32_t address)		// Check for the existance of a break point
{
	int i = 0;

	while (i < 16)	{
		if (BP_valid[i] == 1 && BP_list[i] == address) 	{
			#ifdef GDB_DBG
			printf ("HWServer : Breakpoint reached at PC = %x\n", address);
			#endif
			return 1;
		}
		i++;
	}
	return 0;
}


int clear_bp(uint32_t address)		// Clear a breakpoint
{
	int i = 0;

	while (i < 16)	{
		if (BP_list[i] == address) 	{
			#ifdef GDB_DBG
			printf ("HWServer : Cleared Breakpoint at PC = %x\n", address);
			#endif
			BP_valid[i] = 0;
			break;
		}
		i++;
	}
	return 0;
}

int set_bp(uint8_t reg_id, uint32_t address)		// Set a breakpoint
{
	int i = (int)reg_id;
	#ifdef GDB_DBG
	printf ("HWServer : Set Breakpoint at PC = %x Reg = %d\n", address,i);
	#endif
	BP_list[i] = address;
	BP_valid[i] = 1;
	return 1;
}


int check_for_wp(uint32_t address)		// Check for the existance of a watch point
{
	int i = 0;

	while (i < 16)	{
		if (WP_valid[i] == 1 && WP_list[i] == address) 	{
			#ifdef GDB_DBG
			printf ("HWServer : Watchpoint reached at Address = %x\n", address);
			#endif
			return 1;
		}
		i++;
	}
	return 0;
}

int clear_wp(uint32_t address)		// Clear a watchpoint
{
	int i = 0;

	while (i < 16)	{
		if (WP_list[i] == address) 	{
			#ifdef GDB_DBG
			printf ("HWServer : Cleared Watchpoint at address = %x in Reg %d\n", address, i);
			#endif
			WP_valid[i] = 0;
			break;
		}
		i++;
	}
	return 0;
}

int set_wp(uint8_t reg_id, uint32_t address)		// Set a watchpoint
{
	int i = (int)reg_id;
	#ifdef GDB_DBG
	printf ("HWServer : Set Watchpoint at PC = %x in WP Reg %d\n", address, i);
	#endif
	WP_list[i] = address;
	WP_valid[i] = 1;
	return 1;

}

int execute_spi(ProcessorState *ajit_state, spi_cmd *cmd_exe)	// Execute a single SPI command
{
	uint32_t reg_data, mem_data;
	uint8_t read_mae, write_mae, byte_mask;
	int bp_success = 0, wp_success = 0;
	spi_rsp rsp_out;


	if (cmd_exe->opcode == 1)	{		// Read integer register content
		if ( getSlice32(cmd_exe->command, 10, 10) == 1)		{		// General purpose registers
			uint8_t cwp = getSlice32(ajit_state->status_reg.psr, 4, 0);	// Get the current window state
			reg_data = readRegister((uint8_t)getSlice32(cmd_exe->command, 4, 0), cwp);		// Read register contents
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
			reg_data = ajit_state->status_reg.asr[(int)getSlice32(cmd_exe->command, 4, 0)];
		}
		rsp_out.rsp = 'C';
		rsp_out.id = 0;
		rsp_out.data = reg_data;
		send_spi(&rsp_out);
	}
	else if (cmd_exe->opcode == 2)	{		// Write integer register content

		reg_data = cmd_exe->data;
		if ( getSlice32(cmd_exe->command, 10, 10) == 1)		{		// General purpose registers
			uint8_t cwp = getSlice32(ajit_state->status_reg.psr, 4, 0);	// Get the current window state			
			writeRegister((uint8_t)getSlice32(cmd_exe->command, 4, 0), cwp, reg_data);		// Write register contents
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
		send_spi(&rsp_out);
	}
	else if (cmd_exe->opcode == 3)	{		// Read FP register content
		if ( getSlice32(cmd_exe->command, 5, 5) == 1)		{
			reg_data = ajit_state->status_reg.fsr;				// Read FSR register
		}
		else	{
			reg_data = readFRegister((uint8_t)(getSlice32(cmd_exe->command, 4, 0)));		// Read FLOATING POINT register contents
		}
		rsp_out.rsp = 'C';
		rsp_out.id = 0;
		rsp_out.data = reg_data;
		send_spi(&rsp_out);
	}
	else if (cmd_exe->opcode == 4)	{		// Write FP register content
		if ( getSlice32(cmd_exe->command, 5, 5) == 1)		{
			ajit_state->status_reg.fsr = cmd_exe->data;				// Write FSR register
		}
		else	{
			writeFRegister((uint8_t)(getSlice32(cmd_exe->command, 4, 0)), cmd_exe->data );		// Write FLOATING POINT register contents
		}
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(&rsp_out);
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
		send_spi(&rsp_out);
	}
	else if (cmd_exe->opcode == 17 )	{	// Read CPSR
			reg_data = ajit_state->status_reg.csr;
			rsp_out.rsp = 'C';
			rsp_out.id = 0;
			rsp_out.data = reg_data;
			send_spi(&rsp_out);
	}
	else if (cmd_exe->opcode == 18 )	{	// Write to CPSR
			ajit_state->status_reg.csr = cmd_exe->data;
			rsp_out.rsp = 'O';		// Send "OK" reply
			rsp_out.id = 0;
			rsp_out.data = 0;
			send_spi(&rsp_out);
	}
	else if (cmd_exe->opcode == 6)	{		// Read memory content
		readDataToDebug((uint8_t)getSlice32(cmd_exe->command, 7, 0), cmd_exe->address, &read_mae, &mem_data);	// Populate mem_data with memory content

		rsp_out.rsp = 'C';
		rsp_out.id = 0;
		rsp_out.data = mem_data;
		send_spi(&rsp_out);
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


		writeDataFromDebug((uint8_t)getSlice32(cmd_exe->command, 7, 0), cmd_exe->address, byte_mask, cmd_exe->data, &write_mae); // write to cmd_exe->address
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(&rsp_out);
	}
	else if (cmd_exe->opcode == 8)	{	// Set BP
		bp_success = set_bp((uint8_t)cmd_exe->command, cmd_exe->address);
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
		send_spi(&rsp_out);
	}
	else if (cmd_exe->opcode == 9)	{	// Clear BP
		clear_bp(cmd_exe->address);
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(&rsp_out);
	}
	else if (cmd_exe->opcode == 10)	{	// Set WP
		#ifdef GDB_DBG
		printf("We got Reg %d here !\n", (int)cmd_exe->command);
		#endif
		wp_success = set_wp((uint8_t)cmd_exe->command, cmd_exe->address);
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
		send_spi(&rsp_out);
	}
	else if (cmd_exe->opcode == 11)	{	// Clear WP
		clear_wp(cmd_exe->address);
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(&rsp_out);
	}
	else if (cmd_exe->opcode == 15)	{
		rsp_out.rsp = 'O';		// Send "OK" reply
		rsp_out.id = 0;
		rsp_out.data = 0;
		send_spi(&rsp_out);
	}

	return(0);
}
