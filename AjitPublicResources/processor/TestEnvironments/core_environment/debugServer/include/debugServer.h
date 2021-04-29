#ifndef _debugServer__
#define _debugServer__

typedef enum __DebugServerConnectMode {
	dbg_CONNECT_WITH_PIPE_HANDLER,
	dbg_CONNECT_WITH_SOCKET,
	dbg_CONNECT_WITH_SOCKET_BYTE_MODE,
	dbg_CONNECT_WITH_UART,
	dbg_CONNECT_WITH_PCIE
} DebugServerConnectMode;

typedef enum __DebugServerGdbState {
	gdb_INACTIVE,
	gdb_IDLE,
	gdb_ccu_CONNECT_PENDING,
	gdb_ccu_CONNECTED,
	gdb_DETACH_PENDING,
	gdb_DETACHED
} DebugServerGdbState;

typedef enum _DebugServerCcuState {
	ccu_IDLE,
	ccu_gdb_CONNECT_PENDING,
	ccu_gdb_CONNECTED
} DebugServerCcuState;


typedef struct _GdbCommand {
	uint8_t gdb_wp_reg_index;

	unsigned gdb_connect_cmd: 1;
	unsigned gdb_continue_cmd : 1;
	unsigned gdb_detach_cmd : 1;
	unsigned gdb_kill_cmd : 1;
	unsigned gdb_set_bp_cmd : 1;
	unsigned gdb_clear_bp_cmd : 1;
	unsigned gdb_set_wp_cmd : 1;
	unsigned gdb_clear_wp_cmd : 1;
	unsigned gdb_read_iureg: 1;
	unsigned gdb_read_fpureg: 1;
	unsigned gdb_read_mem: 1;
	unsigned gdb_read_cntrl_re: 1;
	unsigned gdb_read_cpreg: 1;
	unsigned gdb_write_iureg: 1;
	unsigned gdb_write_fpureg: 1;
	unsigned gdb_write_mem: 1;
	unsigned gdb_write_cpreg: 1;
	unsigned gdb_write_cntrl_reg : 1;
	unsigned gdb_read_pc : 1;
	unsigned gdb_read_npc : 1;
	unsigned gdb_read_psr : 1;
	unsigned gdb_write_pc : 1;
	unsigned gdb_write_npc : 1;
	unsigned gdb_write_psr : 1;
	
	unsigned gdb_write_reset: 1;
	unsigned gdb_write_init_pc: 1;
	unsigned gdb_write_init_npc: 1;
	unsigned gdb_write_init_psr: 1;
	unsigned gdb_read_init_pc: 1;
	unsigned gdb_read_init_npc: 1;
	unsigned gdb_read_init_psr: 1;
	unsigned gdb_read_mode: 1;


} GdbCommand;

typedef struct _CcuCommand {

	uint8_t  ccu_wp_reg_index;

	unsigned ccu_send_gdb_ack : 1;
	unsigned ccu_send_gdb_error : 1;
	unsigned ccu_gdb_connect : 1;
	unsigned ccu_bp_hit : 1;
	unsigned ccu_read_wp_hit : 1;
	unsigned ccu_write_wp_hit : 1;
	unsigned ccu_thread_finish : 1;
	unsigned ccu_enter_error_mode : 1;
	unsigned ccu_intr_hit : 1;
	unsigned ccu_single_step_hit : 1;
	unsigned ccu_trap_hit : 1;
	unsigned ccu_read_response : 1;


} CcuCommand;

typedef struct __DebugServerState  {

	uint32_t PC;
	uint32_t NPC;
	uint32_t PSR;

	DebugServerGdbState gdb_state;
	DebugServerCcuState ccu_state;

	uint32_t WP_REGS[32];	


	uint32_t gdb_nwords;
	uint32_t gdb_word_1;
	uint32_t gdb_word_2;
	uint32_t gdb_word_3;

	uint32_t ccu_nwords;
	uint32_t ccu_word_1;
	uint32_t ccu_word_2;

	GdbCommand gdb_command;
	CcuCommand ccu_command;
	

} DebugServerState;



void setDebugServerConnectMode(DebugServerConnectMode val);
DebugServerConnectMode  getDebugServerConnectMode();

void initDebugServerState(DebugServerState* s);

void startDebugServer();
void stopDebugServer();

void probeGdb(DebugServerState* server_state);
void probeCcu(DebugServerState* server_state);

void parseGdbCommand (DebugServerState* server_state, uint8_t valid_flag, uint32_t command);
void parseCcuCommand (DebugServerState* server_state, uint8_t valid_flag, uint32_t command);

void sendU32FromDebugServerToGdb(uint32_t word);
void sendU32FromDebugServerToCcu(DebugServerConnectMode cmode, uint32_t word);


void recvU32FromCcuToDebugServer(DebugServerConnectMode DebugServerConnectMode, uint32_t *word);

uint8_t recvValidCcuMessage (uint8_t blocking_flag, uint32_t* read_word);
uint8_t recvValidGdbMessage (uint8_t blocking_flag, uint32_t* read_word);

void startNoblockDaemons ();

void stopNoblockDaemons  ();



#endif
