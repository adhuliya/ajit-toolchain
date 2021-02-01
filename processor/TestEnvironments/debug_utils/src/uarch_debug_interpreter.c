#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <uarch_debug_utils.h>
#include <uarch_debug_interpreter.h>
#include "StartGPBThreads.h"
#define LINESIZE 1023

FILE* log_file = NULL;

int debug_interpreter_multi_core_mode = 0;
void setDebugInterpreterInMultiCoreMode(int mcm) 
{
	debug_interpreter_multi_core_mode = mcm;
	setDebugUtilsInMultiCoreMode(mcm);
}

int getDebugInterpreterInMultiCoreMode()
{
	return(debug_interpreter_multi_core_mode);
}

int debug_interpreter_current_core_id = 0;

int executeCommandLine(char* line_buffer);
int executeScriptFile(char* file_name);
			
void printHelpMessage()
{
	fprintf(stdout, "Possible commands\n" \
				"q                                   : quit\n" \
        			"h                                   : print help message\n"\
				"c <core-id>                         : switch to core core-id\n"
				"l <log-file>                        : log all executed commands into log-file\n"\
				"g start <port-id>                   : GDB server start on port port-id\n"\
				"g stop                              : GDB server stop\n"\
				"s <script-file>                     : execute commands in script-file\n"\
				"m  <mmap-file>                      : load mmap file to processor system memory\n" \
				"w rst <rst-val>                     : write reset value\n"\
				"r mode                              : read processor-mode\n"\
				"w ipc/inpc/ipsr/psr/tbr/y/wim <write-val>  : write value to ipc/inpc/ etc.\n"\
				"r ipc/inpc/ipsr/psr/tbr/y/wim              : read value from ipc/inpc/ etc.\n"\
				"   note: by ipc,inpc,ipsr we mean the init values of pc/npc/psr post-reset.\n"\
				"w asr   <asr-id> <asr-val>          : write asr-val to asr[asr-id]\n"\
				"r asr   <asr-id>                    : read asr-val from asr[asr-id]\n"\
				"w iureg <iureg-id> <iureg-val>      : write iureg-val to iureg[iureg-id]\n"\
				"r iureg <iureg-id>                  : read iureg-val from iureg[iureg-id]\n"\
				"w fpreg <fpreg-id> <fpreg-val>      : write fpreg-val to fpreg[fpreg-id]\n"\
				"r fpreg <fpreg-id>                  : read fpreg-val from fpreg[fpreg-id]\n"\
				"w mem <asi> <addr> <wdata>          : mem<asi>[addr] = wdata\n"\
				"r mem <asi> <addr>                  : ret-val=mem<asi>[addr]\n"
				"d <asi> <addr>  <n-words>           : dumps memory contents from addr to addr+(n-words*4)\n"
		);
}


void getLineFromStdin(char* lb)
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
		
InterpreterCommand classifyOpcode(int write_flag, char* id)
{
	InterpreterCommand op = UNKNOWN;
	if(id == NULL)
		return op;

	if(strcmp(id,"rst") == 0)
		op = (write_flag ? WRST : UNKNOWN);
	else if(strcmp(id,"mode") == 0)
		op = (!write_flag ? RMODE : UNKNOWN);
	else if(strcmp(id,"ipc") == 0)
		op = (write_flag ? WIPC : RIPC);
	else if(strcmp(id,"inpc") == 0)
		op = (write_flag ? WINPC : RINPC);
	else if(strcmp(id,"ipsr") == 0)
		op = (write_flag ? WIPSR : RIPSR);
	else if(strcmp(id,"psr") == 0)
		op = (write_flag ? WPSR : RPSR);
	else if(strcmp(id,"tbr") == 0)
		op = (write_flag ? WTBR : RTBR);
	else if(strcmp(id,"wim") == 0)
		op = (write_flag ? WWIM : RWIM);
	else if(strcmp(id,"y") == 0)
		op = (write_flag ? WY : RY);
	else if(strcmp(id,"asr") == 0)
		op = (write_flag ? WASR : RASR);
	else if(strcmp(id,"iureg") == 0)
		op = (write_flag ? WIUREG : RIUREG);
	else if(strcmp(id,"fpreg") == 0)
		op = (write_flag ? WFPREG : RFPREG);
	else if(strcmp(id,"mem") == 0)
		op = (write_flag ? WMEM : RMEM);

	return(op);
}


int parseCommandLine(char* lb, InterpreterCommand* opcode, 
					char* cmd_file_name, uint32_t* arg1, uint32_t* arg2, uint32_t *arg3)
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
	else if(kw[0] == 'd')
	{
		*opcode = DUMPMEM;
	}
	else if(kw[0] == 'w')
	{
		char* id = strtok_r(rest," \t\n",&rest);
		*opcode = classifyOpcode(1,id);
		if(*opcode == UNKNOWN)
			return(0);
		
	}
	else if(kw[0] == 'r')
	{
		char* id = strtok_r(rest," \t\n",&rest);
		*opcode = classifyOpcode(0,id);
		if(*opcode == UNKNOWN)
			return(0);
	}
	else if(kw[0] == 'g')
	{
		char* id = strtok_r(rest," \t\n",&rest);
		if(id == NULL)
		{
			fprintf(stderr,"Error: incomplete g command\n");
			return(0);
		}
		if(strcmp(id,"start") == 0)
		{
			*opcode = GDBSTART;
		}
		else if (strcmp(id,"stop") == 0)
		{
			*opcode = GDBSTOP;
		}
		else
		{
			fprintf(stderr,"Error: unknown command: g %s\n", id);
			return(0);
		}
	}
	else if(kw[0] == 'c')
	{
		*opcode = SETCORE;
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
		
	return(arg_count);
}

int  executeInterpreterCommand(int nargs, InterpreterCommand op,
					char* cmd_file_name,
					uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
	int err = 0;
	uint32_t rval, count, addr;
	switch(op)
	{
        	case HELP:  // "h"
			printHelpMessage();
			break;
		case GDBSTART:
			if(nargs < 2)
			{
				fprintf(stderr,"Error: not enough args\n");
				err = 1;
			}
			else
			{
#ifdef MULTICORE
				// start gdb server on port arg1 for core core-id..
				per_core_start_gpb_thread (debug_interpreter_current_core_id, arg1);
#else
				// start gdb server on port arg1
				start_gpb_threads(1, &arg1);
#endif
			}
			break;
		case GDBSTOP:

#ifdef MULTICORE
			// stop gdb server for current core.
			per_core_stop_gpb_thread(debug_interpreter_current_core_id);
#else
			// stop gdb server.
			stop_gpb_threads(1);
#endif

			break;
		case SETCORE:
			debug_interpreter_current_core_id = arg1;	
			setDebugUtilsCurrentCoreId(debug_interpreter_current_core_id);
			fprintf(stderr,"Info: setting current core-id = %d\n", debug_interpreter_current_core_id);
			break;
		case SCRIPT:
			err = executeScriptFile(cmd_file_name);
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
			err = dbg_load_mmap(cmd_file_name);
			fprintf(stdout,"mmap returns 0x%x\n", err);
			break;
		case WRST:  // "w rst"
			if(nargs > 1)
			{
				rval = dbg_write_reset(arg1);
				fprintf(stdout,"w rst returns 0x%x\n", rval);
			}
			else
			{
				fprintf(stderr,"Error: w rst: not enough args\n");
				err = 1;
			}
			break;
		case RMODE: // "r mode"
			rval = dbg_read_mode();
			fprintf(stdout,"r mode returns 0x%x\n", rval);
			break;
		case WIPC:   // "w ipc"
			if(nargs < 2)
			{
				fprintf(stderr,"Error: w ipc: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_init_pc(arg1);
			fprintf(stdout,"w pc returns 0x%x\n", rval);
			break;
		case RIPC:   // "r ipc"
			rval = dbg_read_init_pc();
			fprintf(stdout,"r ipc returns 0x%x\n", rval);
			break;
		case WINPC:  // "w inpc"
			if(nargs < 2)
			{
				fprintf(stderr,"Error: w npc: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_init_npc(arg1);
			fprintf(stdout,"w npc returns 0x%x\n", rval);
			break;
		case RINPC:  // "r inpc"
			rval = dbg_read_init_npc();
			fprintf(stdout,"r npc returns 0x%x\n", rval);
			break;
		case WPSR:  // "w psr"
			if(nargs < 2)
			{
				fprintf(stderr,"Error: w psr: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_psr(arg1);
			fprintf(stdout,"w psr returns 0x%x\n", rval);
			break;
		case RPSR:  // "r psr"
			rval = dbg_read_psr();
			fprintf(stdout,"r psr returns 0x%x\n", rval);
			break;
		case WIPSR:  // "w ipsr"
			if(nargs < 2)
			{
				fprintf(stderr,"Error: w ipsr: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_init_psr(arg1);
			fprintf(stdout,"w ipsr returns 0x%x\n", rval);
			break;
		case RIPSR:  // "r ipsr"
			rval = dbg_read_init_psr();
			fprintf(stdout,"r ipsr returns 0x%x\n", rval);
			break;
		case WTBR:    // "w tbr"
			if(nargs < 2)
			{
				fprintf(stderr,"Error: w tbr: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_tbr(arg1);
			fprintf(stdout,"w tbr returns 0x%x\n", rval);
			break;
		case RTBR:    // "r tbr"
			rval = dbg_read_tbr();
			fprintf(stdout,"r tbr returns 0x%x\n", rval);
			break;
		case WY:    // "w y"
			if(nargs < 2)
			{
				fprintf(stderr,"Error: w y: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_y(arg1);
			fprintf(stdout,"w y returns 0x%x\n", rval);
			break;
		case RY:    // "r y"
			rval = dbg_read_y();
			fprintf(stdout,"r y returns 0x%x\n", rval);
			break;
		case WWIM:  // "w wim"
			if(nargs < 2)
			{
				fprintf(stderr,"Error: w wim: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_wim(arg1);
			fprintf(stdout,"w wim returns 0x%x\n", rval);
			break;
		case RWIM:  // "r wim"
			rval = dbg_read_wim();
			fprintf(stdout,"r wim returns 0x%x\n", rval);
			break;
		case WASR:  // "w asr <asr-id> <asr-val>"
			if(nargs < 3)
			{
				fprintf(stderr,"Error: w asr: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_asr(arg1, arg2);
			fprintf(stdout,"w asr returns 0x%x\n", rval);
			break;
		case RASR:  // "r asr <asr-id>"
			if(nargs < 2)
			{
				fprintf(stderr,"Error: r asr: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_read_asr(arg1);
			fprintf(stdout,"r asr returns 0x%x\n", rval);
			break;
		case WIUREG: // "w iureg <reg-id> <reg-val>"
			if(nargs < 3)
			{
				fprintf(stderr,"Error: w iureg: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_iunit_register(arg1, arg2);
			fprintf(stdout,"w iureg returns 0x%x\n", rval);
			break;
		case RIUREG: // "r iureg <reg-id>"
			if(nargs < 2)
			{
				fprintf(stderr,"Error: r iureg: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_read_iunit_register(arg1);
			fprintf(stdout,"r iureg returns 0x%x\n", rval);
			break;
		case WFPREG: // "w fpreg <reg-id> <reg-val>"
			if(nargs < 3)
			{
				fprintf(stderr,"Error: w fpreg: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_fpunit_register(arg1, arg2);
			fprintf(stdout,"w fpreg returns 0x%x\n", rval);
			break;
		case RFPREG: // "r fpreg <reg-id>"
			if(nargs < 2)
			{
				fprintf(stderr,"Error: r fpreg: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_read_fpunit_register(arg1);
			fprintf(stdout,"r fpreg returns 0x%x\n", rval);
			break;
		case WMEM:   // "w mem <asi> <addr> <wdata>"
			if(nargs < 4)
			{
				fprintf(stderr,"Error: w mem: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_write_mem(arg1, arg2, arg3);
			fprintf(stdout,"w mem returns 0x%x\n", rval);
			break;
		case RMEM:  // "r mem <asi> <addr>
			if(nargs < 3)
			{
				fprintf(stderr,"Error: r mem: not enough args\n");
				err = 1;
				break;
			}
			rval = dbg_read_mem(arg1, arg2);
			fprintf(stdout,"r mem returns 0x%x\n", rval);
			break;
		case DUMPMEM:  // "r mem <asi> <addr>
			if(nargs < 3)
			{
				fprintf(stderr,"Error: d command: not enough args\n");
				err = 1;
				break;
			}
			
			for(count = 0; count < arg3; count++)
			{
				addr = arg2 + (count*4);
				rval = dbg_read_mem(arg1, addr);
				fprintf(stdout,"asi=0x%x, mem[0x%x] = 0x%x\n", arg1, addr, rval);
			}
			break;
		default:
			fprintf(stderr,"Error: unknown opcode\n");
			
	}

	return(err);
}

int executeScriptFile(char* file_name)
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

		err = executeCommandLine(line_buffer);
		
	}

	fclose(sf);
	return(err);
}

// returns 0 on success, 1 on error, 2 on quit
int executeCommandLine(char* line_buffer)
{
	char cmd_file[LINESIZE+1];

	InterpreterCommand icmd;
	uint32_t arg1, arg2, arg3;


	int n = parseCommandLine(line_buffer, &icmd, cmd_file, &arg1, &arg2, &arg3);

	int err = 0;
	if(icmd == QUIT)
	{
		fprintf(stderr,"q command.. quitting.\n");
		dbg_write_mem (0x20, 0x0, 0x0);	
		if(log_file != NULL)
			fclose(log_file);

		err = 2;
	}
	else if(n > 0)
	{
		err = executeInterpreterCommand(n, icmd, cmd_file, arg1, arg2, arg3);
	}
			
	if(err == 1)
		fprintf(stderr,"Error: command not executed correctly\n");
	

	return(err);
}





void startDebugInterpreter()
{
	char line_buffer[1024];

	fprintf(stdout,"Starting AJIT debug interpreter:  type h for help at prompt.\n");

	// Configure readline to auto-complete paths when the tab key is hit.
    	//rl_bind_key('\t', rl_complete);

	while(1)
	{
		char* input_line = readline("ajit> ");
		//fprintf(stderr,"command-line=%s\n", input_line);

		char log_buffer[LINESIZE+1];
		strncpy (log_buffer, input_line, LINESIZE);
		
		int err = executeCommandLine(input_line);

		if((log_file != NULL) && !err)
			fprintf(log_file,"%s\n", log_buffer);

		free(input_line);

		if(err == 2)
			break;
	}
}

