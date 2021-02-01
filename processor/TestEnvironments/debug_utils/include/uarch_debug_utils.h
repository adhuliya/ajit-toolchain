#ifndef __UARCH_DEBUG_UTILS__H__
#define __UARCH_DEBUG_UTILS__H__

//
// author: Madhav Desai.
//

// consistent with Aa/cpu/includes/cpu_constants.aa
#define DBG_READ_IUNIT_REG        1
#define DBG_WRITE_IUNIT_REG       2
#define DBG_READ_FPUNIT_REG       3
#define DBG_WRITE_FPUNIT_REG      4
#define DBG_READ_MEM		  6
#define DBG_WRITE_MEM		  7
#define DBG_SET_BREAK_POINT       8
#define DBG_REMOVE_BREAK_POINT    9 
#define DBG_SET_WATCH_POINT       10
#define DBG_REMOVE_WATCH_POINT    11 
#define DBG_CONNECT	     	  14 
#define DBG_DETACH	     	  15 
#define DBG_CONTINUE	     	  16 
// New: added in Sept. 2019.
#define DBG_WRITE_RESET   	  24 
#define DBG_WRITE_INIT_PC         25   
#define DBG_WRITE_INIT_NPC        26  
#define DBG_WRITE_INIT_PSR        27  
#define DBG_READ_INIT_PC          28 
#define DBG_READ_INIT_NPC         29
#define DBG_READ_INIT_PSR         30
#define DBG_READ_MODE             31

#define DBG_OK  		  0
#define DBG_ERROR 		  1  

// connection modes.
#define DBG_CONNECT_WITH_PIPEHANDLER 0
#define DBG_CONNECT_WITH_SOCKET      1
#define DBG_CONNECT_WITH_UART        2
	
void setDebugUtilsInMultiCoreMode(int mcm);
int  getDebugUtilsInMultiCoreMode();
void setDebugUtilsCurrentCoreId(int core_id);
int  getDebugUtilsCurrentCoreId();


uint32_t dbg_read_psr();
uint32_t dbg_read_wim();
uint32_t dbg_read_tbr();
uint32_t dbg_read_y();
uint32_t dbg_read_asr(uint32_t asr_id);
uint32_t dbg_read_fsr();
uint32_t dbg_read_iunit_register(uint32_t reg_id);
uint32_t dbg_read_fpunit_register(uint32_t reg_id);
uint32_t dbg_read_mem(uint32_t asi, uint32_t addr);

uint32_t dbg_write_psr(uint32_t val);
uint32_t dbg_write_wim(uint32_t val);
uint32_t dbg_write_tbr(uint32_t val);
uint32_t dbg_write_y(uint32_t val);
uint32_t dbg_write_asr(uint32_t asr_id, uint32_t val);
uint32_t dbg_write_fsr(uint32_t val);
uint32_t dbg_write_iunit_register(uint32_t reg_id, uint32_t val);
uint32_t dbg_write_fpunit_register(uint32_t reg_id, uint32_t val);
uint32_t dbg_write_mem(uint32_t asi, uint32_t addr, uint32_t data);

uint32_t dbg_set_watch_point(uint32_t addr);
uint32_t dbg_set_break_point(uint32_t addr);

uint32_t dbg_remove_watch_point(uint32_t addr);
uint32_t dbg_remove_break_point(uint32_t addr);

uint32_t dbg_connect();
uint32_t dbg_continue();
uint32_t dbg_detach  ();

uint32_t dbg_write_reset(uint32_t rval);
uint32_t dbg_write_init_pc(uint32_t rval);
uint32_t dbg_write_init_psr(uint32_t rval);
uint32_t dbg_read_init_pc();
uint32_t dbg_write_init_npc(uint32_t rval);
uint32_t dbg_read_init_npc();
uint32_t dbg_read_init_psr();
uint32_t dbg_read_mode();

// dump commands... very useful.
void    dbg_dump_iunit_registers(FILE* fp);
uint32_t    dbg_dump_iunit_state_registers(FILE* fp); // returns PSR.
void    dbg_dump_iunit_gp_registers(uint32_t psr_val, FILE* fp);
void    dbg_dump_iunit_ancillary_registers(FILE* fp);
void    dbg_dump_fpunit_registers(FILE* fp);
void    dbg_dump_memory(uint32_t asi, uint32_t start_word_address, uint32_t stop_word_address, FILE* fp);

void setDebugConnectMode(uint8_t cmode);
void setDebugUtilsInSocketMode();
void setDebugUtilsInUartMode();

int dbg_load_mmap(char* memmap_filename);

void startDebugInterpreter();
#endif
