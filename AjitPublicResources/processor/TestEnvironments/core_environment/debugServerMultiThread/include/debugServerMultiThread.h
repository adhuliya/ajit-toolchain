#ifndef _debugServerMultiThread__
#define _debugServerMultiThread__

typedef enum __DebugServerConnectMode {
	dbg_CONNECT_WITH_SOCKET_BYTE_MODE,
	dbg_CONNECT_WITH_UART
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

	int CORE_ID;
	int THREAD_ID; 

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

typedef struct __perThreadDebugServerState {

	int core_id;
	int thread_id;

	char request_pipe_name[256];
	char response_pipe_name[256];

	DebugServerState debug_server_state;

} perCoreDebugServerState;

void initPerThreadDebugServerState(int core_id);


void setDebugServerConnectMode(DebugServerConnectMode val);
DebugServerConnectMode  getDebugServerConnectMode();

void initDebugServerState(DebugServerState* s, int CORE_ID, int THREAD_ID);

void probeGdb(DebugServerState* server_state, int CORE_ID, int THREAD_ID);
void probeCcu(DebugServerState* server_state, int CORE_ID, int THREAD_ID);

void parseGdbCommand (DebugServerState* server_state, uint8_t valid_flag, uint32_t command);
void parseCcuCommand (DebugServerState* server_state, uint8_t valid_flag, uint32_t command);

void perThreadSendU32FromDebugServerToGdb(int CORE_ID, int THREAD_ID, uint32_t word);
void perThreadSendU32FromDebugServerToCcu(int CORE_ID, int THREAD_ID, DebugServerConnectMode cmode, uint32_t word);

void perThreadRecvU32FromCcuToDebugServer(int CORE_ID, int THREAD_ID,
						DebugServerConnectMode DebugServerConnectMode, uint32_t *word);

uint8_t perThreadRecvValidCcuMessage (int CORE_ID, int THREAD_ID, uint8_t blocking_flag, uint32_t* read_word);
uint8_t perThreadRecvValidGdbMessage (int CORE_ID,  int THREAD_ID, uint8_t blocking_flag, uint32_t* read_word);

void startPerThreadNoblockDaemon (int CORE_ID, int THREAD_ID);
void startPerThreadDebugServerDaemons (int ncores, int nthreads);

int perThreadRecvBytesFromCcu(int CORE_ID, int THREAD_ID, uint32_t *word);
int perThreadSendBytesToCcu(int CORE_ID, int THREAD_ID, uint32_t word);

#endif
