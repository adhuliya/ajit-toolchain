
/*
 * Necessary functions used for the GDB to AJIT processor server bridge
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include "Pipes.h"
#include "Ancillary.h"

#include "GDBtoAJITbridge.h"
#include "spi_common.h"

int use_debug_server = 0;
void setUseDebugServer(int s)
{
	use_debug_server = s;
}
int getUseDebugServer()
{
	return(use_debug_server);
}

int sendToGdbClient (int sockno, char* send_string, int str_length)
{
	int ret_val = write(sockno, send_string, str_length);

#ifdef GDB_DBG
	char pbuffer[4096];
	sprintf(pbuffer,"TOGDBCLIENT: %s",send_string);
	logMessageToStderr(pbuffer);
#endif
	return(ret_val);
}
int recvFromGdbClient (int sockno, char* buf, int length)
{
	int n = read(sockno, buf, length);

#ifdef GDB_DBG
	char pbuffer[4096];
	sprintf(pbuffer,"FROMGDBCLIENT: %s",buf);
	logMessageToStderr(pbuffer);
#endif
	return(n);
}

gpbState* makeGpbState (int cpu_id, int port_number)
{
	gpbState* ret_state = (gpbState*) malloc (sizeof (gpbState));
	ret_state->cpu_id = cpu_id;
	ret_state->port_number = port_number;

	ret_state->prev_cmd[0] = 0;
	ret_state->command_count = 0;
	ret_state->prev_halt = '5';

	int I;
	for (I=0; I < 16; I++)
	{
		ret_state->gpb_BP_valid[I] = 0;
		ret_state->gpb_WP_valid[I] = 0;
	}

	if(getUseDebugServer())
	{
		sprintf(ret_state->command_pipe,"COMMAND_TO_DEBUG_SERVER_%d", cpu_id);
		sprintf(ret_state->response_pipe,"RESPONSE_FROM_DEBUG_SERVER_%d", cpu_id);
	}
	else
	{
		sprintf(ret_state->command_pipe,"ENV_to_AJIT_debug_command_%d", cpu_id);
		sprintf(ret_state->response_pipe,"AJIT_to_ENV_debug_response_%d", cpu_id);
	}

	return(ret_state);
}

#define BEGINPARSE  0
#define DOLLARFOUND 1
#define HASHFOUND   2
#define ENDPARSE    3

int parse_gdb_command_buffer(int parse_state, int *message_counter, 
		char* buffer, 
		int buf_size,
		char* message,
		int   start_buf_ptr,
		int*  next_buf_ptr,
		unsigned int* checksum, 
		char* chk_bits)
{
	int I;
	int break_flag = 0;
	*next_buf_ptr = start_buf_ptr;
	for(I=start_buf_ptr; I < buf_size; I++)
	{	
		int copy_flag = 0;
		switch(parse_state) {
			case BEGINPARSE:
				(*next_buf_ptr)++;
				if ( buffer[I] == '$' )	{
					parse_state = DOLLARFOUND;
				}
				break;
			case DOLLARFOUND:
				(*next_buf_ptr)++;
				if(buffer[I] == '#') {
					parse_state = HASHFOUND;
				}
				else
				{
					copy_flag = 1;
				}
				break;
			case HASHFOUND:
				(*next_buf_ptr)++;
				chk_bits[0] = buffer[I];
				parse_state = ENDPARSE;
				message[*message_counter] = 0;
				break;
			case ENDPARSE:
				(*next_buf_ptr)++;
				chk_bits[1] = buffer[I];
				break_flag = 1;
				break;
			default:
				break;
		}

		if(copy_flag)
		{
			message[*message_counter] = buffer[I];
			(*message_counter)++;

			*checksum += (unsigned int) buffer[I];
		}

		if (break_flag)
			break;
	}

	return(parse_state);
}


// 
// GDB sometimes puts a ,4 after the address
// in the address string.  This throws off
// this shitty code.
//
uint32_t getU32FromString(char* addr_str)
{
	// make a copy of addr_str
	char tmp_buffer[33];
	strncpy(tmp_buffer,addr_str,32);

	//
	// look for a "," if there is one.
	//
	char* leading_str = strtok(tmp_buffer,",");

	//
	// do strtol on this leading string.
	//
	uint32_t rval = (uint32_t)strtol(leading_str, NULL, 16);

	// fprintf(stderr,"getU32FromString: %s -> 0x%x\n", addr_str, rval);
	return(rval);
}


// Initialise the GDB to processor software server
int gpb_init (gpbState* gpb_state)
{

	int port = gpb_state->port_number;

	int sockt, newsockt, clilen, bind_ret;
	struct sockaddr_in serv_addr, cli_addr;

	// Request to create socket with the given parameters
	sockt = socket(AF_INET, SOCK_STREAM, 0);
	if (sockt < 0) 	{
		fprintf(stderr, "\nError: gpb_init: could not create a socket.\n");
		return 11;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	// Bind to the socket wait for connection requests
	bind_ret = bind(sockt, (struct sockaddr *) &serv_addr,sizeof(serv_addr));
	if (bind_ret < 0) 	{
		fprintf(stderr,"\nError: gpb_init: The port is already taken\n");
		exit(0);
	}
	listen(sockt,5);
	clilen = sizeof(cli_addr);

	fprintf(stderr,"\nInfo: gpb_init:  waiting for the connection from GDB..");
	// Accept the connection from the other process
	newsockt = accept(sockt, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockt < 0)	{
		fprintf(stderr, "\nError: gpb_init: failed to accept the connection");
		return 11;
	}

	fprintf(stderr,"\nInfo:gpb_init: initialized the server for CPU %d, port %d, socket %d.\n", 
				gpb_state->cpu_id, gpb_state->port_number,
				newsockt);

	gpb_state->socket_number = newsockt;
	return 0;
}

//
// Receive an RSP command, and parse it.
//
int gsb_receive (gpbState* gpb_state, gsb_cmd *recvd_cmd)
{
	char buffer[4096] = {'\0'};

	char addr_str[16], data_str[16];

	char message[4096]= {'\0'};
	int  n, h, m, k,l;
	unsigned int sum=0;
	char chk[2];
	long int chkint;
	char active_cmd[4096] = {'\0'};

	chk[2] = 0;


	int parse_state = BEGINPARSE;
	int message_counter = 0;
	int end_buf_pointer;
	while ( parse_state != ENDPARSE )	{

		// Read 1024 characters from the socket buffer
		int buf_size = recvFromGdbClient(gpb_state->socket_number, buffer,1024);
		parse_state = parse_gdb_command_buffer(parse_state, &message_counter,
				buffer, buf_size, message, 
				0,&end_buf_pointer,
				&sum, chk);
	}

	//
	// increment the command count..
	//
	gpb_state->command_count++;
	
	strcpy(active_cmd, message);
	strcpy(gpb_state->prev_cmd,active_cmd);

	// chkint = strtol(chk,NULL,16);
	chkint =  getU32FromString(chk);

#ifdef GDB_DBG
	fprintf(stderr,"SWServer:gsb_receive: buffer=%s\nmessage=%s\ncheck-sum=%s\n", buffer, message, chk);
#endif

	// Compare the received checksum with the calculated one and send acknowledgement
	if (sum % 256 == chkint )
	{
		n = sendToGdbClient(gpb_state->socket_number,"+",1);
	}
	else
	{
		n = sendToGdbClient(gpb_state->socket_number,"-",1);
	}

	if (n < 0)
		fprintf(stderr, "SWServer : Error: failed to write to the socket");

	if (sum % 256 != chkint )
		n = sendToGdbClient(gpb_state->socket_number,"+",1);

	// Echo the message received
#ifdef GDB_DBG
	printf("SWServer (cpu_id=%d): Received GDB message - %s\n",gpb_state->cpu_id,message);
#endif

	// Convert the message to GDB to Server Bridge commands
	if ( strcmp(message,"qSupported:multiprocess+;qRelocInsn+") == 0 )	{	// Initial connect request from GDB
		recvd_cmd->type = 2;
		recvd_cmd->cmd = 'q';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( strcmp(message,"Hg0") == 0 || strcmp(message,"Hc-1") == 0)	{
		recvd_cmd->type = 2;
		recvd_cmd->cmd = 'H';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( strcmp(message,"?") == 0 )	{		// Reason for the last halt
		recvd_cmd->type = 2;
		recvd_cmd->cmd = '?';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( strcmp(message,"qC") == 0 )	{		// Current thread being executed
		recvd_cmd->type = 2;
		recvd_cmd->cmd = 'Q';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( strcmp(message,"qAttached") == 0 )	{	// whether the remote server attached to an existing process(1) or created a new process(0)
		recvd_cmd->type = 2;
		recvd_cmd->cmd = 'A';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( strcmp(message,"qOffsets") == 0 )	{	// memory location offsets ( data, instruction etc.. )
		recvd_cmd->type = 2;
		recvd_cmd->cmd = 'O';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( strcmp(message,"qTStatus") == 0 )	{	// Asking the stub if there is a trace experiment running right now.
		recvd_cmd->type = 2;
		recvd_cmd->cmd = 'T';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( strcmp(message,"qTfV") == 0 || strcmp(message,"qTfP") == 0)	{	// Tracepoint packets, need more info
		recvd_cmd->type = 2;
		recvd_cmd->cmd = 'f';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( strcmp(message,"g") == 0 )	{	// Read all the register contents
		recvd_cmd->type = 3;
		recvd_cmd->cmd = 'g';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( message[0] == 'p' )	{	// Read a particular register content
		for (k=1; message[k] != '\0' ; k++)	{
			addr_str[k-1] = message [k];
		}
		addr_str[k-1] = '\0';

		recvd_cmd->type = 3;
		recvd_cmd->cmd = 'p';
		recvd_cmd->address = getU32FromString(addr_str);
		recvd_cmd->data = 0;
	}
	else if ( message[0] == 'm' )	{	// Read a particular set of memory location

		l = 0;
		for (k=1; message[k] != ',' ; k++)	{		// Get the starting address for reading
			addr_str[k-1] = message[k];
			l++;
		}
		addr_str[l] = '\0';

		l += 2;
		m = 0;
		for (k=l; message[k] != '\0'; k++)	{		// Number of bytes to be read
			data_str[k-l] = message[k];
			m++;
		}
		data_str[m] = '\0';

		recvd_cmd->type = 3;
		recvd_cmd->cmd = 'm';
		recvd_cmd->address = getU32FromString(addr_str);
		recvd_cmd->data = getU32FromString(data_str);
	}
	else if ( strcmp(message,"qSymbol::") == 0  )	{
		recvd_cmd->type = 2;
		recvd_cmd->cmd = 'v';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( strcmp(message,"vCont?") == 0 )	{		// Request a list of actions supported by the ‘vCont’ packet
		recvd_cmd->type = 2;
		recvd_cmd->cmd = 'V';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( message[0] == 'M' )	{		// Write to a memory location
		recvd_cmd->type = 3;
		// Obtain the address
		for (k=1; k < 9 ; k++)	{
			addr_str[k-1] = message [k];
		}
		addr_str[8] = '\0';
		recvd_cmd->address = getU32FromString(addr_str);
		// Obtain the count
		while(message[k] != ',')
			k++;
		if (message[k+1] == '1')	{
			recvd_cmd->cmd = '1';
		}
		else if (message[k+1] == '2')	{
			recvd_cmd->cmd = '2';
		}
		else if (message[k+1] == '3')	{
			recvd_cmd->cmd = '3';
		}
		else {
			recvd_cmd->cmd = 'M';
		}
		// Obtain the data
		while(message [k] != ':')
			k++;

		for ( h = k+1 ; message[h] != '\0' ; h++)	{
			data_str[h-k-1] = message [h];
		}
		data_str[8] = '\0';
		recvd_cmd->data = getU32FromString(data_str);
#ifdef GDB_DBG
		printf("SwServer : The data %x in address %x \n",recvd_cmd->address,recvd_cmd->data);
#endif
	}
	else if ( message[0] == 'P' )	{		// Write to a register
		recvd_cmd->type = 3;
		recvd_cmd->cmd = 'P';
		// Obtain the address
		for (k=1; message[k] != '=' ; k++)	{
			addr_str[k-1] = message [k];
		}
		addr_str[k-1] = '\0';
		recvd_cmd->address = getU32FromString(addr_str);
		k++;
		// Obtain the data
		for (h=k; message[h] != '\0' ; h++)	{
			data_str[h-k] = message [h];
		}
		data_str[h-1] = '\0';
		recvd_cmd->data = getU32FromString(data_str);
	}
	else if ( message[0] == 'z' && message[1] == '0')	{
		for (k=3; message[k] != ',' ; k++)	{	// Clear a breakpoint
			addr_str[k-3] = message [k];
		}
		addr_str[k-3] = '\0';

		recvd_cmd->type = 3;
		recvd_cmd->cmd = 'z';
		recvd_cmd->address = getU32FromString(addr_str);
		recvd_cmd->data = 0;
	}
	else if ( message[0] == 'z' && ( message[1] == '2' || message[1] == '3' || message[1] == '4') )	{
		for (k=3; message[k] != ',' ; k++)	{	// Clear a watchpoint
			addr_str[k-3] = message [k];
		}
		addr_str[k-3] = '\0';

		recvd_cmd->type = 3;
		recvd_cmd->cmd = 'w';
		recvd_cmd->address = getU32FromString(addr_str);
		recvd_cmd->data = message[1] - '0';
	}
	else if ( message[0] == 'Z' && message[1] == '0'  )	{			// Set a breakpoint
		for (k=3; message[k] != ',' ; k++)	{
			addr_str[k-3] = message [k];
		}
		addr_str[k-3] = '\0';

		recvd_cmd->type = 3;
		recvd_cmd->cmd = 'Z';
		recvd_cmd->address = getU32FromString(addr_str);
		recvd_cmd->data = 0;
	}
	else if ( message[0] == 'Z' && ( message[1] == '2' || message[1] == '3' || message[1] == '4') )	{			// Set a watchpoint
		for (k=3; message[k] != ',' ; k++)	{
			addr_str[k-3] = message [k];
		}
		addr_str[k-3] = '\0';

		recvd_cmd->type = 3;
		recvd_cmd->cmd = 'W';
		recvd_cmd->address = getU32FromString(addr_str);
		recvd_cmd->data = message[1] - '1';
	}
	else if ( strcmp(message,"s") == 0 )	{		// Step
		recvd_cmd->type = 3;
		recvd_cmd->cmd = 's';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( strcmp(message,"c") == 0 || ((message[0] == 'C' ) && (message[1] == '0')))	{		// Continue
		recvd_cmd->type = 3;
		recvd_cmd->cmd = 'c';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else if ( strcmp(message,"D") == 0 || strcmp(message,"k") == 0 )	{		// Detach or kill
		recvd_cmd->type = 3;
		recvd_cmd->cmd = 'D';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}
	else	{		// Unknown message
		recvd_cmd->type = 1;
		recvd_cmd->cmd = 'e';
		recvd_cmd->address = 0;
		recvd_cmd->data = 0;
	}

	return 0;
}

// Calculate the response packet for a particular RSP command.
int gsb_compute_response(gpbState* gpb_state, gsb_cmd *cmd_in, char *rsp_out)
{
	int reg = 0;
	char resp[4096], data[1024];
	int mem = 0;
	uint8_t bp_reg_id = 0, wp_reg_id = 0;

	gpb_spi_cmd dbg_cmd = {.cmd = 'e', .reg_id = 0, .address = 0, .data = 0};
	gpb_spi_rsp dbg_rsp = {.rsp_cmd = "e", .content = 0};
	resp[0] = '\0';

	if ( cmd_in->type == 1 )	{
		strcpy(rsp_out,"");
	}
	else if ( cmd_in->type == 2 )	{
		if ( cmd_in->cmd == 'q' )	{
			strcpy(rsp_out,"PacketSize=600;multiprocess-;qRelocInsn-;TracepointSource-;StaticTracepoint-");
			dbg_cmd.cmd = 'C';
			dbg_cmd.reg_id = 0;
			dbg_cmd.address = 0;
			dbg_cmd.data = 0;
			send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
			recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);
			//read_uint32("AJIT_to_ENV_debug_response");
		}
		else if ( cmd_in->cmd == 'H' || cmd_in->cmd == 'v')	{
			strcpy(rsp_out,"OK");
		}
		else if ( cmd_in->cmd == '?' )	{
			strcpy(rsp_out,"S05");
			rsp_out[2] = gpb_state->prev_halt;
		}
		else if ( cmd_in->cmd == 'Q' )	{
			strcpy(rsp_out,"QC-1");
		}
		else if ( cmd_in->cmd == 'A' )	{
			strcpy(rsp_out,"1");
		}
		else if ( cmd_in->cmd == 'O' )	{
			strcpy(rsp_out,"Text=0;Data=0;Bss=0");
		}
		else if ( cmd_in->cmd == 'T' )	{
			strcpy(rsp_out,"T0");
		}
		else if ( cmd_in->cmd == 'V' )	{
			strcpy(rsp_out,"vCont;c:0;t:0");
		}
		else if ( cmd_in->cmd == 'f' )	{
			strcpy(rsp_out,"");
		}
		else	{
			strcpy(rsp_out,"");
		}

	}
	else if ( cmd_in->type == 3 )	{
		if ( cmd_in->cmd == 'g' )	{
			resp[0] = '\0';
			for (reg = 0; reg < 72;reg++)	{		// Read individual registers and then concatinate them
				dbg_cmd.cmd = 'r';
				dbg_cmd.reg_id = reg;
				dbg_cmd.address = 0;
				dbg_cmd.data = 0;
				send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
				recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);

				// Convert hex value to a string
				if (dbg_rsp.content == 0)	{
					sprintf(data,"%s","00000000");
				}
				else if (dbg_rsp.content < 16)	{
					sprintf(data,"%s%x","0000000",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 256)	{
					sprintf(data,"%s%x","000000",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 4096)	{
					sprintf(data,"%s%x","00000",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 65536)	{
					sprintf(data,"%s%x","0000",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 1048576)	{
					sprintf(data,"%s%x","000",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 16777216)	{
					sprintf(data,"%s%x","00",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 268435456)	{
					sprintf(data,"%s%x","0",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 4294967296)	{
					sprintf(data,"%x",dbg_rsp.content);
				}
				else	{
					sprintf(data,"%s","00000000");
				}

				strcat(resp,data);
			}
			strcpy(rsp_out,resp);

		}
		else if ( cmd_in->cmd == 'p' )	{
			dbg_cmd.cmd = 'r';
			dbg_cmd.reg_id = cmd_in->address;
			dbg_cmd.address = 0;
			dbg_cmd.data = 0;
			send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
			recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);

			// Convert hex value to a string
			if (dbg_rsp.content == 0)	{
				sprintf(data,"%s","00000000");
			}
			else if (dbg_rsp.content < 16)	{
				sprintf(data,"%s%x","0000000",dbg_rsp.content);
			}
			else if (dbg_rsp.content < 256)	{
				sprintf(data,"%s%x","000000",dbg_rsp.content);
			}
			else if (dbg_rsp.content < 4096)	{
				sprintf(data,"%s%x","00000",dbg_rsp.content);
			}
			else if (dbg_rsp.content < 65536)	{
				sprintf(data,"%s%x","0000",dbg_rsp.content);
			}
			else if (dbg_rsp.content < 1048576)	{
				sprintf(data,"%s%x","000",dbg_rsp.content);
			}
			else if (dbg_rsp.content < 16777216)	{
				sprintf(data,"%s%x","00",dbg_rsp.content);
			}
			else if (dbg_rsp.content < 268435456)	{
				sprintf(data,"%s%x","0",dbg_rsp.content);
			}
			else if (dbg_rsp.content < 4294967296)	{
				sprintf(data,"%x",dbg_rsp.content);
			}
			else	{
				sprintf(data,"%s","00000000");
			}

			strcpy(rsp_out,data);
		}
		else if ( cmd_in->cmd == 'P' )	{
			dbg_cmd.cmd = 'R';
			dbg_cmd.reg_id = cmd_in->address;
			dbg_cmd.address = 0;
			dbg_cmd.data = cmd_in->data;
			send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
			recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);
			strcpy(rsp_out,dbg_rsp.rsp_cmd);
		}
		/* else if ( cmd_in->cmd == '?' )	{	// Not supported
		   dbg_cmd.cmd = 'L';
		   dbg_cmd.reg_id = 0;
		   dbg_cmd.address = 0;
		   dbg_cmd.data = 0;
		   send_gpb_spi_cmd(&dbg_cmd);
		   recv_gpb_spi_cmd(&dbg_rsp);
		   strcpy(rsp_out,dbg_rsp.rsp_cmd);
		   } */
		else if ( cmd_in->cmd == 'm' )	{
			resp[0] = '\0';
			for (mem = 0 ; mem < (int)((cmd_in->data)/4) ; mem++)	{		// Read individual memory and then concatinate them

				dbg_cmd.cmd = 'm';
				dbg_cmd.reg_id = 0xB;	// ASI : Supervisor user data
				dbg_cmd.address = (cmd_in->address) + (mem*4);
				dbg_cmd.data = 0;
				send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);

#ifdef GDB_DBG
				printf("HwServer : Reading the memory address %x\n",dbg_cmd.address);
#endif
				recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);

				// Convert hex value to a string
				if (dbg_rsp.content == 0)	{
					sprintf(data,"%s","00000000");
				}
				else if (dbg_rsp.content < 16)	{
					sprintf(data,"%s%x","0000000",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 256)	{
					sprintf(data,"%s%x","000000",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 4096)	{
					sprintf(data,"%s%x","00000",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 65536)	{
					sprintf(data,"%s%x","0000",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 1048576)	{
					sprintf(data,"%s%x","000",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 16777216)	{
					sprintf(data,"%s%x","00",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 268435456)	{
					sprintf(data,"%s%x","0",dbg_rsp.content);
				}
				else if (dbg_rsp.content < 4294967296)	{
					sprintf(data,"%x",dbg_rsp.content);
				}
				else	{
					sprintf(data,"%s","00000000");
				}
				strcat(resp,data);
			}
			strcpy(rsp_out,resp);
		}

		else if ( cmd_in->cmd == 'M' )	{				
			dbg_cmd.cmd = 'M';
			dbg_cmd.reg_id = 0xB;	// ASI : Supervisor user data
			dbg_cmd.address = cmd_in->address;
			dbg_cmd.data = cmd_in->data;
#ifdef GDB_DBG
			printf("SwServer : Writing %x to the memory address %x asi %x \n",dbg_cmd.data, dbg_cmd.address, dbg_cmd.reg_id);
#endif
			send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
			recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);
			strcpy(rsp_out,dbg_rsp.rsp_cmd);
		}
		else if ( cmd_in->cmd == 'c' )	{
			dbg_cmd.cmd = 'c';
			dbg_cmd.reg_id = 0;
			dbg_cmd.address = 0;
			dbg_cmd.data = 0;
			send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
			recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);
			strcpy(rsp_out,dbg_rsp.rsp_cmd);
		}
		else if ( cmd_in->cmd == 's' )	{
			dbg_cmd.cmd = 's';
			dbg_cmd.reg_id = 0;
			dbg_cmd.address = 0;
			dbg_cmd.data = 0;
			send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
			recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);
			strcpy(rsp_out,dbg_rsp.rsp_cmd);
		}
		else if ( cmd_in->cmd == 'Z' )	{
			gpb_set_bp(gpb_state, cmd_in->address, &bp_reg_id);
			dbg_cmd.reg_id = bp_reg_id;
			dbg_cmd.cmd = 'b';
			dbg_cmd.address = cmd_in->address;
			dbg_cmd.data = 0;
			send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
			recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);
			strcpy(rsp_out,dbg_rsp.rsp_cmd);
		}
		else if ( cmd_in->cmd == 'z' )	{
			dbg_cmd.reg_id = gpb_clear_bp(gpb_state, cmd_in->address);
			dbg_cmd.cmd = 'B';
			dbg_cmd.address = cmd_in->address;
			dbg_cmd.data = 0;
			send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
			recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);
			strcpy(rsp_out,dbg_rsp.rsp_cmd);
		}
		else if ( cmd_in->cmd == 'W' )	{
			gpb_set_wp(gpb_state, cmd_in->address, &wp_reg_id);
			dbg_cmd.cmd = 'w';
			dbg_cmd.reg_id = wp_reg_id;
			dbg_cmd.address = cmd_in->address;
			dbg_cmd.data = cmd_in->data;
			send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
			recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);
			strcpy(rsp_out,dbg_rsp.rsp_cmd);
		}
		else if ( cmd_in->cmd == 'w' )	{
			dbg_cmd.reg_id = gpb_clear_wp(gpb_state, cmd_in->address);
			dbg_cmd.cmd = 'W';
			dbg_cmd.address = cmd_in->address;
			dbg_cmd.data = cmd_in->data;
			send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
			recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);
			strcpy(rsp_out,dbg_rsp.rsp_cmd);
		}
		else if ( cmd_in->cmd == 'D' )	{
			dbg_cmd.cmd = 'D';
			dbg_cmd.reg_id = 0;
			dbg_cmd.address = 0;
			dbg_cmd.data = 0;
			send_gpb_spi_cmd(gpb_state->command_pipe, &dbg_cmd);
			recv_gpb_spi_cmd(gpb_state->response_pipe, &dbg_rsp);
			strcpy(rsp_out,dbg_rsp.rsp_cmd);
		}
		else	{
			strcpy(rsp_out,"");
		}

	}
	else	{
		strcpy(rsp_out,"");
	}

	return 0;
}

// Send a packet through the RSP link, to gdb
int gsb_send(gpbState* gpb_state, char *send_msg)
{
	// Calculate sum for checksum
	unsigned int sum=0;
	int i;
	for (i = 0; i < strlen(send_msg); i++)	{
		sum += (unsigned int)send_msg[i];
	}
	sum  = sum % 256;

	char pckt_out[4096];
	sprintf(pckt_out,"$%s#%02x", send_msg, sum);

#ifdef GDB_DBG
	printf("SWServer : GDB reply message - %s\n",pckt_out);
#endif
	int n = sendToGdbClient(gpb_state->socket_number,pckt_out,strlen(pckt_out));

	return(n);
}



int gpb_set_bp(gpbState* gpb_state, uint32_t address, uint8_t *reg_num)		// Set a breakpoint
{
	uint8_t i = 0;

	while (i < 16)	{
		if (gpb_state->gpb_BP_valid[i] == 0) 	{
#ifdef GDB_DBG
			printf ("SWServer (cpu-id=%d) : Set Breakpoint at PC = %x, BP Reg %u\n", 
					gpb_state->cpu_id,
					address, i);
#endif
			gpb_state->gpb_BP_list[i] = address;
			gpb_state->gpb_BP_valid[i] = 1;
			*reg_num = i;
			return 1;
		}
		i++;
	}
	return 0;
}

int gpb_set_wp(gpbState* gpb_state, uint32_t address, uint8_t *reg_num)		// Set a watchpoint
{
	uint8_t i = 0;

	while (i < 16)	{
		if (gpb_state->gpb_WP_valid[i] == 0) 	{
#ifdef GDB_DBG
			printf ("SWServer (cpu-id=%d): Set Watchpoint at PC = %x, WP Reg %u\n", 
					gpb_state->cpu_id, address, i);
#endif
			gpb_state->gpb_WP_list[i] = address;
			gpb_state->gpb_WP_valid[i] = 1;
			*reg_num = i;
			return 1;
		}
		i++;
	}
	return i;
}

int gpb_clear_bp(gpbState* gpb_state, uint32_t address)		// Clear a watchpoint
{
	int i = 0;

	while (i < 16)	{
		if (gpb_state->gpb_BP_list[i] == address) 	{
#ifdef GDB_DBG
			printf ("SWServer (cpu-id=%d): Cleared Breakpoint at address = %x\n", 
					gpb_state->cpu_id, address);
#endif
			gpb_state->gpb_BP_valid[i] = 0;
			break;
		}
		i++;
	}
	return i;
}

int gpb_clear_wp(gpbState* gpb_state, uint32_t address)		// Clear a watchpoint
{
	int i = 0;

	while (i < 16)	{
		if (gpb_state->gpb_WP_list[i] == address) 	{
#ifdef GDB_DBG
			printf ("SWServer (cpu-id=%d) : Cleared Watchpoint at address = %x in Reg %d\n", 
					gpb_state->cpu_id, address, i);
#endif
			gpb_state->gpb_WP_valid[i] = 0;
			break;
		}
		i++;
	}
	return i;
}
