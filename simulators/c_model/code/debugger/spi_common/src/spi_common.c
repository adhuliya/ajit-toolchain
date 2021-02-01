/*
 * Necessary functions used for the Software to Ajit hardware
 */

#include <stdio.h>
#include <string.h>

#include <assert.h>
#include "Pipes.h"
#include "Ancillary.h"

#include "spi_common.h"

int NSENT = 0;
int NRECV = 0;

// function to send an SPI function
int send_gpb_spi_cmd(char* command_pipe, gpb_spi_cmd *cmd_in)
{
	uint8_t command, reg;
	uint32_t packet = 0, data, address;
	uint32_t pckt_len = 0, pckt_opcode = 0, pckt_cmd = 0;

	int CC = 0;

	command = (uint8_t) cmd_in->cmd;		// Command
	reg = (uint8_t) cmd_in->reg_id;		// Register ID
	data = (uint32_t) cmd_in->data;		// Data
	address = (uint32_t) cmd_in->address;	// Address

	#ifdef GDB_DBG
	printf ("SWServer [%d] : Command - %c %x\n", NSENT, (char)command, reg);
	#endif

	switch((char)command)	{
		case 'r' :
		case 'C' :
		case 'c' :
		case 'D' :
		case 's' :
		case 'L' :
				pckt_len = 1;
				break;
		case 'm' :
		case 'b' :
		case 'B' :
		case 'w' :
		case 'W' :
		case 'R' :
				pckt_len = 2;
				break;
		case 'M' :
				pckt_len = 3;
				break;
	}


	if ( (char)command == 'r' || (char)command == 'R' )	{	// Register read / write commands
		
		
		if ( reg < 32 || (reg >= 64 && reg <= 67) || (reg >= 77 && reg <= 108) )		{	// Read integer registers

			switch((char)command)	{	// Calculate the op-codes for the packet
				case 'r' :
						pckt_opcode = 1;
						break;
				case 'R' :
						pckt_opcode = 2;
						break;
			}

			if (reg < 32 )	{		// General purpose registers
				pckt_cmd = 0x0400 + reg;
			}
			else if (reg == 64 )	{	// Y register
				pckt_cmd = 0x0040;
			}
			else if (reg == 65 )	{	// PSR register
				pckt_cmd = 0x0200;
			}
			else if (reg == 66 )	{	// WIM register
				pckt_cmd = 0x0100;
			}
			else if (reg == 67 )	{	// TBR register
				pckt_cmd = 0x0080;
			}
			else if (reg >= 77 && reg <= 108)	{	// Ancillary State Registers
				pckt_cmd = 0x0020 + ( reg - 77);
			}


		}
		else if ( (reg >= 32 && reg < 64) || reg == 70 )		{	// Read FP registers

			switch((char)command)	{	// Calculate the op-codes for the packet
				case 'r' :
						pckt_opcode = 3;
						break;
				case 'R' :
						pckt_opcode = 4;
						break;
			}

			if (reg >= 32 && reg < 64)	{ // Geberal FP registers
				pckt_cmd = reg - 32;
			}
			else if (reg == 70 )	{	// FSR register
				pckt_cmd = 0x0020;
			}
		}
		else if ( reg == 68 || reg == 69 )			{		// Read control registers

			switch((char)command)	{	// Calculate the op-codes for the packet
				case 'r' :
						pckt_opcode = 13;
						break;
				case 'R' :
						pckt_opcode = 14;
						break;
			}

			if (reg == 68)	{ // PC
				pckt_cmd = 0x0001;
			}
			else if (reg == 69 )	{	// NPC
				pckt_cmd = 0x0002;
			}

		}
		else if ( reg == 71 )			{		// Read CPSR register
			switch((char)command)	{	// Calculate the op-codes for the packet
				case 'r' :
						pckt_opcode = 17;
						break;
				case 'R' :
						pckt_opcode = 18;
						break;
			}
			pckt_cmd = 0x0;
		}

	}
	else if ( (char)command == 'm' || (char)command == 'M' )	{	// read / write memory
			switch((char)command)	{	// Calculate the op-codes for the packet
				case 'm' :
						pckt_opcode = 6;
						break;
				case 'M' :
						pckt_opcode = 7;
						break;
			}

			pckt_cmd =  reg;			// ASI = 10
	}
	else if ( (char)command == 'b' || (char)command == 'B' || (char)command == 'w' || (char)command == 'W')	{	// Set / remove a breakpoint / watchpoint
			switch((char)command)	{	// Calculate the op-codes for the packet
				case 'b' :
						pckt_opcode = 8;
						break;
				case 'B' :
						pckt_opcode = 9;
						break;
				case 'w' :
						pckt_opcode = 10;
						break;
				case 'W' :
						pckt_opcode = 11;
						break;
			}
#ifdef GDB_DBG
			printf("SPI Common : We got Reg %d here\n", reg);
#endif
			pckt_cmd = (uint32_t) ((data%4) << 2) + (reg);			// the corresponding breakpoint / watchpoint register id
	}
	else if ( (char)command == 'c' )	{	// Continue
		pckt_opcode = 16;
		pckt_cmd = 0;
	}
	else if ( (char)command == 'C' )	{	// Connect
		pckt_opcode = 14;
		pckt_cmd = 0;
	}
	else if ( (char)command == 'D' )	{	// Detach
		pckt_opcode = 15;
		pckt_cmd = 0;
	}
	else	{
		pckt_opcode = 0;
		pckt_cmd = 0;
		assert(0);
	}


	assert(pckt_opcode != 0);

	packet = (pckt_len << 24) + (pckt_opcode << 16) + (pckt_cmd);

	write_uint32(command_pipe, packet);		// Send command through the serial line ( implemented as pipe )
	CC++;

#ifdef GDB_DBG
	printf("\nSWSERVER[%d] : sent command packet word 1:  0%x \n", NSENT, packet);
#endif

	if ( (char)command == 'm' || (char)command == 'M' || (char)command == 'b' || (char)command == 'B' || (char)command == 'w' || (char)command == 'W')	{
		write_uint32(command_pipe, address);
		CC++;
#ifdef GDB_DBG
		printf("\nSWSERVER[%d] : sent command packet word 2: 0x%x\n", NSENT, address);
#endif
	}
	if ( (char)command == 'R' || (char)command == 'M' )	{
		write_uint32(command_pipe, data);
		CC++;
#ifdef GDB_DBG
		printf("\nSWSERVER[%d]: sent command packet word 3 0%x\n", NSENT, data);
#endif
	}

#ifdef GDB_DBG
	fprintf(stderr,"SPIGPB SENT [%d] [%d]\n", NRECV, CC);
#endif
	NSENT++;
	return 0;
}

// function to generate the SPI response commands from hardware automatically
int recv_gpb_spi_cmd(char* response_pipe, gpb_spi_rsp *rsp_out)
{
	uint32_t response = 0;
	char sig_id[16];
	char data[256];

	response = read_uint32(response_pipe);
#ifdef GDB_DBG
	printf("SWSERVER[%d] : Received SPI response - %x (on pipe %s)\n",NRECV, response, response_pipe);
#endif
	if ( response == 0x00004F4B )	{
		(rsp_out->rsp_cmd)[0] = 'O'; // Received OK
		(rsp_out->rsp_cmd)[1] = 'K';
		(rsp_out->rsp_cmd)[2] = '\0';
		rsp_out->content = 0;
	}
	else if ((response == 0x53494706 ) || (response == 0x53494707))	{
		if (response == 0x53494706 )
			strcpy(rsp_out->rsp_cmd,"T05rwatch:");
		else
			strcpy(rsp_out->rsp_cmd,"T05watch:");

		uint32_t recv_data = read_uint32(response_pipe);

		// Convert hex value to a string
		if (recv_data == 0)	{
			sprintf(data,"%s","00000000");
		}
		else if (recv_data < 16)	{
			sprintf(data,"%s%x","0000000",recv_data);
		}
		else if (recv_data < 256)	{
			sprintf(data,"%s%x","000000",recv_data);
		}
		else if (recv_data < 4096)	{
			sprintf(data,"%s%x","00000",recv_data);
		}
		else if (recv_data < 65536)	{
			sprintf(data,"%s%x","0000",recv_data);
		}
		else if (recv_data < 1048576)	{
			sprintf(data,"%s%x","000",recv_data);
		}
		else if (recv_data < 16777216)	{
			sprintf(data,"%s%x","00",recv_data);
		}
		else if (recv_data < 268435456)	{
			sprintf(data,"%s%x","0",recv_data);
		}
		else if (recv_data < 4294967296)	{
			sprintf(data,"%x",recv_data);
		}
		else	{
			sprintf(data,"%s","00000000");
		}

		strcat(rsp_out->rsp_cmd,data);
		strcat(rsp_out->rsp_cmd,";");
	}
	else if ( response == 0x53494709 )	{
		
		strcpy(rsp_out->rsp_cmd,"T09");
		//uint32_t recv_data = read_uint32(response_pipe);
		
	}
	else if (getSlice32(response, 31, 8) == 0x00534947)	{
		(rsp_out->rsp_cmd)[0] = 'T';
		(rsp_out->rsp_cmd)[1] = '0';
		sprintf(sig_id,"%i",(int)getSlice32(response, 7, 0));
		#ifdef GDB_DBG
		printf("SWServer : Sig - %s\n",sig_id);
		#endif
		(rsp_out->rsp_cmd)[2] = sig_id[0];
		(rsp_out->rsp_cmd)[3] = '\0';
		rsp_out->content = 0;
	}
	else	{
		rsp_out->content = response;
		rsp_out->rsp_cmd[0] = '\0';
	}

#ifdef GDB_DBG
	fprintf(stderr,"\nSPIGPB RECVD [%d]\n", NRECV);
#endif
	NRECV++;
	return 0;
}
