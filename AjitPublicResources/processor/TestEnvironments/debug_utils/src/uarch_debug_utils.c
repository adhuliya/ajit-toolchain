#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pipeHandler.h>
#include <Pipes.h>
#include <uarch_debug_utils.h>
#include <uart_interface.h>


uint8_t debug_connect_mode = DBG_CONNECT_WITH_PIPEHANDLER;
extern int global_verbose_flag;

void setDebugUtilsInSocketMode()
{
	debug_connect_mode = DBG_CONNECT_WITH_SOCKET;
}
void setDebugUtilsInUartMode()
{
	debug_connect_mode = DBG_CONNECT_WITH_UART;
}


int debug_utils_multi_core_mode = 0;
void setDebugUtilsInMultiCoreMode(int mcm)
{
	debug_utils_multi_core_mode = mcm;
}
int  getDebugUtilsInMultiCoreMode()
{
	return(debug_utils_multi_core_mode);
}

int debug_utils_current_core_id = 0;
void setDebugUtilsCurrentCoreId(int core_id)
{
	debug_utils_current_core_id = core_id;
}
int  getDebugUtilsCurrentCoreId()
{
	return(debug_utils_current_core_id);
}
int debug_utils_current_thread_id = 0;
void setDebugUtilsCurrentThreadId(int thread_id)
{
	debug_utils_current_thread_id = thread_id;
}
int  getDebugUtilsCurrentThreadId()
{
	return(debug_utils_current_thread_id);
}



void dbg_send_debug_command(uint32_t cmd_val)
{
	if(getDebugUtilsInMultiCoreMode())
	{
		int core_id = getDebugUtilsCurrentCoreId();
		int thread_id = getDebugUtilsCurrentThreadId();
		if(((core_id >= 0) && (core_id < 4)) &&
			((thread_id >= 0) && (thread_id <= 1)))
		{
			char pipe_name[256];
			sprintf(pipe_name, "COMMAND_TO_DEBUG_SERVER_%d_%d", core_id, thread_id);
			write_uint32(pipe_name, cmd_val);
#ifdef DEBUG_MODE
			fprintf(stderr,"Info:dbg_send_debug_command (%d,%d): 0x%x.\n", 
						core_id, thread_id, cmd_val);
#endif
		}
		else
		{
			fprintf(stderr,"Error:dbg_send_debug_command: illegal core-id %d\n", core_id);
		}
	}
	else
	{
		write_uint32("COMMAND_TO_DEBUG_SERVER", cmd_val);
	}
}

uint32_t dbg_get_debug_response()
{
	uint32_t ret_val = 0;

	if(getDebugUtilsInMultiCoreMode())
	{
		int core_id = getDebugUtilsCurrentCoreId();
		int thread_id = getDebugUtilsCurrentThreadId();
		if(((core_id >= 0) && (core_id < 4)) &&
			((thread_id >= 0) && (thread_id <= 1)))
		{
			char pipe_name[256];
			sprintf(pipe_name, "RESPONSE_FROM_DEBUG_SERVER_%d_%d", core_id, thread_id);
			ret_val = read_uint32(pipe_name);
#ifdef DEBUG_MODE
			fprintf(stderr,"Info:dbg_get_debug_response (%d,%d): 0x%x.\n", 
						core_id, thread_id, ret_val);
#endif
		}
		else
		{
			fprintf(stderr,"Error:dbg_get_debug_response: illegal core-id %d\n", core_id);
		}
	}
	else
	{
		ret_val = read_uint32("RESPONSE_FROM_DEBUG_SERVER");
	}

	return(ret_val);
}


// helper function..
uint32_t __dbg_read_reg(uint32_t op_code, uint32_t reg_bit_flag_index, uint32_t rid)
{
	uint32_t cmd_val = 0;

	cmd_val = (1 << 24);
	cmd_val = (cmd_val | (op_code << 16));
	cmd_val = (cmd_val | (1 << reg_bit_flag_index));
	cmd_val = (cmd_val | rid);

	dbg_send_debug_command( cmd_val);
	uint32_t rsp = dbg_get_debug_response();
	return(rsp);
}

uint32_t dbg_read_psr()
{
	return(__dbg_read_reg(DBG_READ_IUNIT_REG, 9, 0));
}
uint32_t dbg_read_wim()
{
	return(__dbg_read_reg(DBG_READ_IUNIT_REG, 8, 0));
}

uint32_t dbg_read_tbr()
{
	return(__dbg_read_reg(DBG_READ_IUNIT_REG, 7, 0));
}
uint32_t dbg_read_y()
{
	return(__dbg_read_reg(DBG_READ_IUNIT_REG, 6, 0));
}
uint32_t dbg_read_asr(uint32_t asr_id)
{
	return(__dbg_read_reg(DBG_READ_IUNIT_REG, 5, asr_id));
}


uint32_t dbg_read_iunit_register(uint32_t reg_id)
{
	return(__dbg_read_reg(DBG_READ_IUNIT_REG, 10, reg_id));
}
uint32_t dbg_read_fsr()
{
	return(__dbg_read_reg(DBG_READ_FPUNIT_REG, 5, 0));
}
uint32_t dbg_read_fpunit_register(uint32_t reg_id)
{
	return(__dbg_read_reg(DBG_READ_FPUNIT_REG, 6, reg_id));
}
uint32_t dbg_read_mem(uint32_t asi, uint32_t addr)
{
	uint32_t cmd_val = (2 << 24);
	cmd_val = (cmd_val | (DBG_READ_MEM << 16));
	cmd_val = (cmd_val | asi);
	dbg_send_debug_command( cmd_val);
	dbg_send_debug_command( addr);
	uint32_t ret_val = dbg_get_debug_response();
	return(ret_val);
}


uint32_t __dbg_write_reg(uint32_t op_code, uint32_t flag_index, uint32_t rid, uint32_t val)
{
	uint32_t cmd_val = 0;

	cmd_val = (2 << 24);
	cmd_val = (cmd_val | (op_code << 16));
	cmd_val = (cmd_val | (1 << flag_index));
	cmd_val = (cmd_val | rid);

	dbg_send_debug_command( cmd_val);
	dbg_send_debug_command( val);
	uint32_t ret_val = dbg_get_debug_response();
	return(ret_val);
}

uint32_t dbg_write_psr(uint32_t val)
{
	return(__dbg_write_reg(DBG_WRITE_IUNIT_REG, 9, 0, val));
}
uint32_t dbg_write_wim(uint32_t val)
{
	return(__dbg_write_reg(DBG_WRITE_IUNIT_REG, 8, 0, val));
}
uint32_t dbg_write_tbr(uint32_t val)
{
	return(__dbg_write_reg(DBG_WRITE_IUNIT_REG, 7, 0, val));
}
uint32_t dbg_write_y(uint32_t val)
{
	return(__dbg_write_reg(DBG_WRITE_IUNIT_REG, 6, 0, val));
}
uint32_t dbg_write_asr(uint32_t asr_id, uint32_t val)
{
	return(__dbg_write_reg(DBG_WRITE_IUNIT_REG, 5, asr_id, val));
}
uint32_t dbg_write_fsr(uint32_t val)
{
	return(__dbg_write_reg(DBG_WRITE_FPUNIT_REG, 5, 0, val));
}
uint32_t dbg_write_iunit_register(uint32_t reg_id, uint32_t val)
{
	return(__dbg_write_reg(DBG_WRITE_IUNIT_REG,  10, reg_id, val));
}
uint32_t dbg_write_fpunit_register(uint32_t reg_id, uint32_t val)
{
	return(__dbg_write_reg(DBG_WRITE_FPUNIT_REG, 6, reg_id, val));
}
uint32_t dbg_write_mem(uint32_t asi, uint32_t addr, uint32_t data)
{
	uint32_t cmd_val = (3 << 24);
	cmd_val = (cmd_val | (DBG_WRITE_MEM << 16));
	cmd_val = (cmd_val | asi);
	dbg_send_debug_command( cmd_val);
	dbg_send_debug_command( addr);
	dbg_send_debug_command( data);
	uint32_t ret_val = dbg_get_debug_response();
	return(ret_val);
}

uint32_t dbg_set_watch_point(uint32_t addr)
{
	return(DBG_ERROR);
}

uint32_t dbg_set_break_point(uint32_t addr)
{
	return(DBG_ERROR);
}

uint32_t dbg_remove_watch_point(uint32_t addr)
{
	return(DBG_ERROR);
}
uint32_t dbg_remove_break_point(uint32_t addr)
{
	return(DBG_ERROR);
}

uint32_t dbg_exec_instruction(uint32_t instr)
{
	return(DBG_ERROR);
}

// returns PSR value.
uint32_t   dbg_dump_iunit_state_registers(FILE* fp)
{
	uint32_t psr_val = dbg_read_psr();

	get_file_print_lock(fp);
	fprintf(fp,"debug>\tPSR\t=\t%x\n", psr_val);
	release_file_print_lock(fp);

	uint32_t rv = dbg_read_wim();
	get_file_print_lock(fp);
	fprintf(fp,"debug>\tWIM\t=\t%x\n", rv);
	release_file_print_lock(fp);

	rv = dbg_read_tbr();
	get_file_print_lock(fp);
	fprintf(fp,"debug>\tTBR\t=\t%x\n", rv);
	release_file_print_lock(fp);

	rv = dbg_read_y();
	get_file_print_lock(fp);
	fprintf(fp,"debug>\t  Y\t=\t%x\n", rv);
	release_file_print_lock(fp);

	return(psr_val);
}

// psr-val specified cwp
void   dbg_dump_iunit_gp_registers(uint32_t psr_val, FILE* fp)
{
	uint32_t cwp = (psr_val & 0x1f);
	uint32_t rv, I;
	fprintf(stderr, "debug>\tfor CWP=%d\n", cwp);
	for(I=0; I < 32; I++)
	{
		rv = dbg_read_iunit_register(I);
		get_file_print_lock(fp);
		fprintf(fp,"debug>\tREG[%d]\t=\t%x\n", I, rv);
		release_file_print_lock(fp);
	}
}

void   dbg_dump_iunit_ancillary_registers(FILE* fp)
{
	uint32_t rv;
	uint32_t I;

	for(I=0; I < 32; I++)
	{
		rv = dbg_read_asr(I);
		get_file_print_lock(fp);
		fprintf(fp,"debug>\tASR[%d]\t=\t%x\n", I, rv);
		release_file_print_lock(fp);
	}
}

void   dbg_dump_iunit_registers(FILE* fp)
{
	uint32_t psr_val = dbg_dump_iunit_state_registers(fp);
	dbg_dump_iunit_gp_registers(psr_val, fp);
	dbg_dump_iunit_ancillary_registers(fp);
}

void    dbg_dump_fpunit_registers(FILE* fp)
{
	uint32_t I;
	uint32_t rv = dbg_read_fsr();
	get_file_print_lock(fp);
	fprintf(fp,"debug>\tFSR\t=\t%x\n", rv);
	release_file_print_lock(fp);

	for(I=0; I < 32; I++)
	{
		rv = dbg_read_fpunit_register(I);
		get_file_print_lock(fp);
		fprintf(fp,"debug>\tFPREG[%d]\t=\t%x\n", I, rv);
		release_file_print_lock(fp);
	}
}
void    dbg_dump_memory(uint32_t asi, uint32_t start_word_address, uint32_t stop_word_address, FILE* fp)
{
	uint32_t I;
	for(I = start_word_address; I < stop_word_address; I++)
	{
		uint32_t rv = dbg_read_mem(asi,4*I);
		get_file_print_lock(fp);
		fprintf(fp,"debug>\tMEM[%d]\t=\t%x\n", I, rv);
		release_file_print_lock(fp);
	}
}

uint32_t dbg_connect ()
{
	uint32_t cmd_val = (1 << 24);
	cmd_val = (cmd_val | (DBG_CONNECT << 16));
	dbg_send_debug_command( cmd_val);
	uint32_t resp = dbg_get_debug_response();
	return(resp);
}

uint32_t dbg_continue()
{
	uint32_t cmd_val = (1 << 24);
	cmd_val = (cmd_val | (DBG_CONTINUE << 16));
	dbg_send_debug_command( cmd_val);
	uint32_t resp = dbg_get_debug_response();
	return(resp);
}

uint32_t dbg_detach  ()
{
	uint32_t cmd_val = (1 << 24);
	cmd_val = (cmd_val | (DBG_DETACH << 16));
	dbg_send_debug_command( cmd_val);
	uint32_t resp = dbg_get_debug_response();
	return(resp);
}

// to be used to initialize memory through the debug
// interface..  This will be needed to test the FPGA
// prototype.
int dbg_load_mmap(char* memoryMapFile)
{
	FILE * file;
	file= fopen(memoryMapFile, "r");
	if(!file)
	{
		#ifdef SW
		fprintf(stderr,"\n ERROR: file %s could not be opened for reading!\n",memoryMapFile);
		#endif
		return 1;
	}
	
	#ifdef DEBUG
	printf("\n opened memory map file %s\n",memoryMapFile);
	#endif
	uint32_t addr;
	uint32_t  data;
	int file_read=0;

	int number_of_bytes_read = 0;
	int current_word_address = -1;
	int current_read_word    = 0;
	int written_word_count = 0;

	while (1)
	{
		int eof_reached = 0;
		data = 0;
		
		file_read=fscanf(file, "%x", &addr);
		if (feof(file)) 
		{
			eof_reached = 1;
		}
		else
		{
			file_read=fscanf(file, "%x", &data);
		}

		if(number_of_bytes_read == 0)
		{
			current_word_address = (addr & 0xfffffffc);
			if(!eof_reached)
				current_read_word = (data <<  8*(3 - (addr & 0x3)));
		}

		uint32_t masked_addr = addr & 0xfffffffc;
		if ((current_word_address != masked_addr) || (eof_reached))
		{
			dbg_write_mem(0x20, current_word_address, current_read_word);
			if(global_verbose_flag)
			{
				uint32_t read_back = dbg_read_mem(0x20, current_word_address);
				fprintf(stderr,"Info: initialized mem[0x%x] = 0x%x.\n",  current_word_address,
										current_read_word);
				if(read_back != current_read_word)
					fprintf(stderr,"Error: read-back mem[0x%x] = 0x%x, expected 0x%x.\n",  
										current_word_address, 
										read_back,
										current_read_word);
			}


			current_word_address = masked_addr;
			current_read_word = (data <<  8*(3 - (addr & 0x3)));

			written_word_count++;

			if((written_word_count % 1024) == 0)
			{
				fprintf(stderr,"Info: initialized %d words..\n", written_word_count);
			}
		}
		else if (current_word_address == masked_addr)
		{
			current_read_word = current_read_word | (data <<  8*(3 - (addr & 0x3)));
		}

		number_of_bytes_read++;

		if(eof_reached)
			break;

	}
	fprintf(stderr, "\n Finished initializing memory from file %s.\
			\nLast address written = %x.\n",memoryMapFile, addr);

	fclose(file);
	return 0;
}
uint32_t dbg_write_reset(uint32_t rval)
{
	uint32_t cmd_val = (1 << 24); // 1-word comand
	cmd_val = cmd_val | (DBG_WRITE_RESET << 16);
	cmd_val = cmd_val | (rval & 0x1f);

	dbg_send_debug_command( cmd_val);
	uint32_t resp = dbg_get_debug_response();
	return(resp);
}

uint32_t dbg_write_init_pc(uint32_t rval)
{
	uint32_t cmd_val = (2 << 24);
	cmd_val = cmd_val | (DBG_WRITE_INIT_PC << 16);

	dbg_send_debug_command( cmd_val);
	dbg_send_debug_command( rval);

	uint32_t ret_val = dbg_get_debug_response();
	return(ret_val);
}
uint32_t dbg_read_init_pc()
{
	uint32_t cmd_val = (1 << 24);
	cmd_val = cmd_val | (DBG_READ_INIT_PC << 16);

	dbg_send_debug_command( cmd_val);

	uint32_t ret_val = dbg_get_debug_response();
	return(ret_val);
}
uint32_t dbg_write_init_npc(uint32_t rval)
{
	uint32_t cmd_val = (2 << 24);
	cmd_val = cmd_val | (DBG_WRITE_INIT_NPC << 16);

	dbg_send_debug_command( cmd_val);
	dbg_send_debug_command( rval);

	uint32_t ret_val = dbg_get_debug_response();
	return(ret_val);
}

uint32_t dbg_read_init_npc()
{
	uint32_t cmd_val = (1 << 24);
	cmd_val = cmd_val | (DBG_READ_INIT_NPC << 16);

	dbg_send_debug_command( cmd_val);

	uint32_t ret_val = dbg_get_debug_response();
	return(ret_val);
	return(0);
}
uint32_t dbg_write_init_psr(uint32_t rval)
{
	uint32_t cmd_val = (2 << 24);
	cmd_val = cmd_val | (DBG_WRITE_INIT_PSR << 16);

	dbg_send_debug_command( cmd_val);
	dbg_send_debug_command( rval);

	uint32_t ret_val = dbg_get_debug_response();
	return(ret_val);
}
uint32_t dbg_read_init_psr()
{
	uint32_t cmd_val = (1 << 24);
	cmd_val = cmd_val | (DBG_READ_INIT_PSR << 16);

	dbg_send_debug_command( cmd_val);

	uint32_t ret_val = dbg_get_debug_response();
	return(ret_val);
	return(0);
}
uint32_t dbg_read_mode()
{
	uint32_t cmd_val = (1 << 24);
	cmd_val = cmd_val | (DBG_READ_MODE << 16);

	dbg_send_debug_command( cmd_val);

	uint32_t ret_val = dbg_get_debug_response();
	return(ret_val);
	return(0);
}
