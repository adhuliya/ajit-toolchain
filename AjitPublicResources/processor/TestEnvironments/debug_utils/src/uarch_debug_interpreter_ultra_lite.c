#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <uarch_debug_utils_ultra_lite.h>
#include <uarch_debug_interpreter_ultra_lite.h>
#include "device_addresses.h"
#include "StartGPBThreads.h"

#define LINESIZE 1023
FILE* log_file = NULL;


int executeCommandLineUltraLite(char* line_buffer);
int executeScriptFileUltraLite(char* file_name);
			
void printHelpMessageUltraLite()
{
	fprintf(stdout, "Possible commands\n" \
				"q                                   : quit\n" \
        			"h                                   : print help message\n"\
				"l <log-file>                        : log all executed commands into log-file\n"\
				"s <script-file>                     : execute commands in script-file\n"\
				"m  <mmap-file>                      : load mmap file to processor system memory\n" \
				"w rst 1		             : put cpu into reset \n"\
				"w mem <addr> <wdata>                : mem[addr] = wdata\n"\
				"r mem <addr>                        : ret-val=mem[addr]\n"\
				"toggle                              : toggle led. \n"\
				"go                                  : take processor out of reset and run\n"\
		);
}


void getLineFromStdinUltraLite(char* lb)
{

	lb[0] = 0;
	int idx;
	for(idx = 0; idx < LINESIZE; idx++)
	{
		char c = fgetc(stdin);
		if((c == '\r') || (c == '\n'))
		{
			lb[idx] = 0;
			break;
		}
		else
			lb[idx] = c;
	}
	fflush(stdin);
}
		
InterpreterCommandUltraLite classifyOpcodeUltraLite(int write_flag, char* id)
{
	InterpreterCommandUltraLite op = UNKNOWN;
	if(id == NULL)
		return op;

	if(strcmp(id,"rst") == 0)
		op = (write_flag ? WRST : UNKNOWN);
	else if(strcmp(id,"mem") == 0)
		op = (write_flag ? WMEM : RMEM);

	return(op);
}


int parseCommandLineUltraLite(char* lb, InterpreterCommandUltraLite* opcode, 
					char* cmd_file_name, uint32_t* arg1, 
					uint32_t* arg2, uint32_t *arg3, uint32_t* arg4)
{
	char* rest = lb;
	char* kw = strtok_r(lb," \t\n", &rest);
	*opcode = UNKNOWN;
	if(kw == NULL)
	{
		fprintf(stderr,"Error: empty command line\n");
		return(0);
	}

	if(kw[0] == 'h')
	{
		*opcode = HELP;
		return(1);
	}
	else if(kw[0] == 'q')
	{
		*opcode = QUIT;
		return(1);
	}
	else if ( (kw[0] == 's') ||
			(kw[0] == 'm') ||
			(kw[0] == 'l'))
	{
		if(kw[0] == 's')
			*opcode = SCRIPT;
		else if(kw[0] == 'm')
			*opcode = MMAP;
		else
			*opcode = LOG;

		char* id = strtok_r(rest," \t\n",&rest);
		if(id != NULL)
		{
			strncpy(cmd_file_name,id,LINESIZE);
			return(2);
		}
		else
		{
			return(0);
		}
		return(1);
	}
	else if(kw[0] == 'w')
	{
		char* id = strtok_r(rest," \t\n",&rest);
		*opcode = classifyOpcodeUltraLite(1,id);
		if(*opcode == UNKNOWN)
			return(0);
		
	}
	else if(kw[0] == 'r')
	{
		char* id = strtok_r(rest," \t\n",&rest);
		*opcode = classifyOpcodeUltraLite(0,id);
		if(*opcode == UNKNOWN)
			return(0);
	}
	else if(kw[0] == 'g')
	{
		*opcode = GO;
	}
	else if(kw[0] == 't')
	{
		*opcode = TOGGLE;
	}


	int arg_count = 1;

	char* a1 = strtok_r(rest," \t\n", &rest);
	if(a1 != NULL)
	{
		arg_count++;
		if(strstr(a1,"0x") == NULL)
			sscanf(a1,"%d", arg1);
		else
			sscanf(a1,"0x%x", arg1);
	}
	else
		return(arg_count);

	char* a2 = strtok_r(rest," \t\n", &rest);
	if(a2 != NULL)
	{
		arg_count++;
		if(strstr(a2,"0x") == NULL)
			sscanf(a2,"%d", arg2);
		else
			sscanf(a2,"0x%x", arg2);
	}
	else
		return(arg_count);

	char* a3 = strtok_r(rest," \t\n", &rest);
	if(a3 != NULL)
	{
		arg_count++;
		if(strstr(a3,"0x") == NULL)
			sscanf(a3,"%d", arg3);
		else
			sscanf(a3,"0x%x", arg3);
	}
	char* a4 = strtok_r(rest," \t\n", &rest);
	if(a4 != NULL)
	{
		arg_count++;
		if(strstr(a4,"0x") == NULL)
			sscanf(a4,"%d", arg4);
		else
			sscanf(a4,"0x%x", arg4);
	}
		
	return(arg_count);
}

int  executeInterpreterCommandUltraLite(int nargs, InterpreterCommandUltraLite op,
					char* cmd_file_name,
					uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
	int err = 0;
	uint32_t rval, count, addr;
	switch(op)
	{
        	case HELP:  // "h"
			printHelpMessageUltraLite();
			break;
		case SCRIPT:
			err = executeScriptFileUltraLite(cmd_file_name);
			break;
		case LOG:
			log_file = fopen(cmd_file_name,"w");

			if(log_file != NULL)
			{
				fprintf(stderr,"Info: opened log-file %s\n", cmd_file_name);
			}
			else
			{
				fprintf(stderr,"Error: could not open log-file %s\n", cmd_file_name);
				err = 1;
			}
			break;
		case MMAP:
			if(nargs < 2)
			{
				fprintf(stderr,"Error: not enough args\n");
				err = 1;
				break;
			}
			err = dbg_load_mmap_ultra_lite(cmd_file_name);
			fprintf(stdout,"mmap returns 0x%x\n", err);
			break;
		case WRST:  // "w rst 1"
			if((nargs > 1) && (arg1 == 1))
			{
				rval = dbg_write_reset_ultra_lite(arg1);
				fprintf(stdout,"w rst returns 0x%x\n", rval);
			}
			else
			{
				fprintf(stderr,"Error: w rst: either not enough args, or arg is not 1.\n");
				err = 1;
			}
			break;
		case WMEM:   // "w mem <addr> <wdata>"
			if(nargs < 3)
			{
				fprintf(stderr,"Error: w mem: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_mem_ultra_lite(arg1, arg2);
			fprintf(stdout,"w mem returns 0x%x\n", rval);
			break;
		case RMEM:  // "r mem <asi> <addr>
			if(nargs < 2)
			{
				fprintf(stderr,"Error: r mem: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_read_mem_ultra_lite(arg1);
			fprintf(stdout,"r mem returns 0x%x\n", rval);
			break;
		case GO:
			fprintf(stdout,"Bringing the processor out of reset... uart will be shared by CPU!\n");
			rval = dbg_go_ultra_lite();
			break;
		case TOGGLE:
			fprintf(stdout,"Toggling the led.\n");
			rval = dbg_toggle_ultra_lite();
			break;
		default:
			fprintf(stderr,"Error: unknown opcode\n");
			
	}

	return(err);
}

int executeScriptFileUltraLite(char* file_name)
{
	int err = 0;
	FILE* sf = fopen(file_name,"r");
	if(sf == NULL)
	{
		fprintf(stderr,"Error: could not open script file %s\n", file_name);
		return(1);
	}

	while(!feof(sf))
	{
		char line_buffer[LINESIZE];
		char* v = fgets(line_buffer, LINESIZE, sf);
		if(v == NULL)
			break;
		fprintf(stdout,"Executing command %s\n", line_buffer);

		err = executeCommandLineUltraLite(line_buffer);
		
	}

	fclose(sf);
	return(err);
}

// returns 0 on success, 1 on error, 2 on quit
int executeCommandLineUltraLite(char* line_buffer)
{
	char cmd_file[LINESIZE+1];

	InterpreterCommandUltraLite icmd;
	uint32_t arg1, arg2, arg3, arg4;


	int n = parseCommandLineUltraLite(line_buffer, &icmd, cmd_file, &arg1, &arg2, &arg3, &arg4);

	int err = 0;
	if(icmd == QUIT)
	{
		fprintf(stderr,"q command.. quitting.\n");
		if(log_file != NULL)
			fclose(log_file);

		err = 2;
	}
	else if(n > 0)
	{
		err = executeInterpreterCommandUltraLite(n, icmd, cmd_file, arg1, arg2, arg3, arg4);
	}
			
	if(err == 1)
		fprintf(stderr,"Error: command not executed correctly\n");
	

	return(err);
}





void startDebugInterpreterUltraLite()
{
	char line_buffer[1024];

	fprintf(stdout,"Starting AJIT ultra-lite debug interpreter:  type h for help at prompt.\n");

	// Configure readline to auto-complete paths when the tab key is hit.
    	//rl_bind_key('\t', rl_complete);

	char  prompt_buffer[64];
	while(1)
	{
		sprintf(prompt_buffer,"ajit_ultra_lite> ");

		char* input_line = readline(prompt_buffer);
		//fprintf(stderr,"command-line=%s\n", input_line);

		char log_buffer[LINESIZE+1];
		strncpy (log_buffer, input_line, LINESIZE);
		
		int err = executeCommandLineUltraLite(input_line);

		if((log_file != NULL) && !err)
			fprintf(log_file,"%s\n", log_buffer);

		free(input_line);

		if(err == 2)
			break;
	}
}



