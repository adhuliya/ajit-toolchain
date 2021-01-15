//-------------------------------------------------------------------------
// Header file for cpu thread
//-------------------------------------------------------------------------

#ifndef __SPARC_CORE_H__
#define __SPARC_CORE_H__

#include "RegisterFile.h"
#include "Mmu.h"
#include "CacheInterface.h"
#include "StartCacheThreads.h"
#include "hwServerStruct.h"
#include "monitorLogger.h"
	

typedef enum _ProcessorMode
{
	_RESET_MODE_,
	_EXECUTE_MODE_,
	_ERROR_MODE_
} ProcessorMode;

// branch predictor..  
typedef struct _BranchPredictorState {
	uint32_t table_size;
	uint32_t branch_count;
	uint32_t mispredicts;
	uint32_t* pc_tags;
	uint32_t* nnpc_values;
} BranchPredictorState;
void initBranchPredictorState(BranchPredictorState* bps, uint32_t tsize);
void resetBranchPredictorState(BranchPredictorState* bps);
void addBranchPredictEntry (BranchPredictorState* bps, uint32_t pc, uint32_t nnpc);
void updateBranchPredictEntry (BranchPredictorState* bps, uint32_t idx, uint32_t nnpc);
int branchPrediction(BranchPredictorState* bps, uint32_t pc, uint32_t* bp_idx, uint32_t* nnpc);

void incrementMispredicts(BranchPredictorState* bps);
uint32_t numberOfMispredicts(BranchPredictorState* bps);
uint32_t numberOfBranches(BranchPredictorState* bps);

 


typedef struct _StatusRegisters
{
// Registers (Chapter 4 - Page 23)

//Instruction Unit(IU) Control/Status registers
	uint32_t psr;     //program status register
	uint32_t wim;     //window invalid mask register
	uint32_t tbr;     //trap base register
	uint32_t y;       //multiply/divide register
	uint32_t pc;      //program counter
	uint32_t npc;     //next program counter

	//
	// asr 31, 30 are readonly and contain a 64-bit cycle counter
	// in the hardware.
	//
	// asr 29 contains CPU-ID.
	//
	uint32_t asr[32]; //implementation dependent ancillary state registers
	uint32_t iq; 	  //implementation dependent IU deferred-trap queue

	//Floating Point Unit (FU) registers
	uint32_t fsr; 	//floating point state register
	uint32_t fq; 	//implementation dependent FU deferred-trap queue

	//Coprocessor (CP) register
	uint32_t csr; //implementation dependent CP state register
	uint32_t cq;  //implementation dependent CP deferred-trap queue
} StatusRegisters;


typedef struct _StateUpdateFlags
{
	//Flags to indicate if register values were updated
	//or a store was performed by the current instruction.
	//This information is used for logging.
	
	//register-update flags
	uint8_t psr_updated;   	//program status register updated
	uint8_t wim_updated;   //window invalid mask register updated
	uint8_t tbr_updated;   //trap base register updated
	uint8_t y_updated;     //y register updated
	
	uint8_t gpr_updated;   //general-purpose register updated
	uint8_t double_word_write; //there was a double-word gpr write
	uint8_t reg_id;        //reg-id of the updated gpr register
	uint32_t reg_val_high; //high word
	uint32_t reg_val_low;  //low word
	
	//
	// fp-register update flags (for logging).
	//
	uint8_t fpreg_updated;
	uint8_t fpreg_double_word_write;
	uint8_t fpreg_id;
	uint32_t fpreg_val_high;
	uint32_t fpreg_val_low;

	uint8_t fsr_updated;
	uint8_t ftt_updated;
	uint8_t fcc_updated;
	uint32_t fsr_val; 
	
	//store-related flags
	uint8_t  store_active;
	uint8_t  store_asi;
	uint8_t  store_byte_mask;
	uint8_t  store_double_word;
	uint32_t store_addr;
	uint32_t store_word_high;
	uint32_t store_word_low;

	//pc (because pc is updated
	//inside some instructions, and we need to remember
	//the address of the executing instruction
	//for logging)
	uint32_t pc;
}StateUpdateFlags;

typedef struct _ProcessorState
{
	uint32_t cpu_id;
	uint32_t isa_mode;
	uint32_t instruction;
	uint32_t mmu_fsr;
	uint8_t addr_space;

	uint32_t reporting_interval;
	uint32_t init_pc; // post reset PC.

	ProcessorMode mode;
	uint32_t trap_vector;
	uint8_t interrupt_level;
	uint8_t ticc_trap_type;
	uint8_t store_barrier_pending;
	StatusRegisters status_reg;
	StateUpdateFlags reg_update_flags;
	RegisterFile* register_file;

	BranchPredictorState branch_predictor;

	uint64_t num_ifetches;
	uint64_t num_instructions_executed;

	uint64_t num_fp_sp_sqroots_executed;
	uint64_t num_fp_dp_sqroots_executed;

	uint64_t num_fp_sp_divs_executed;
	uint64_t num_fp_dp_divs_executed;

	uint64_t num_iu_divs_executed;

	uint32_t num_traps;

	MmuState* mmu_state;
	WriteThroughAllocateCache* dcache;
	WriteThroughAllocateCache* icache;
	hwServerState* hw_server;
	MonitorLoggerState* monitor_logger;
	

	
	// Gdb/debug stuff.
	int CPU_HW_SERVER_ENABLED;
	int CPU_GDB_FLAG;
	int CPU_DOVAL_FLAG;

	// pipe names.
	char mode_pipe_name[256];
	char error_pipe_name[256];
	char reset_pipe_name[256];
	char ilvl_pipe_name[256];
	char logger_pipe_name[256];


	int reset_called_once;

	// each bit corresponds to a page...
	// There are 2^20 pages, so we need 2^15
	// words
	uint32_t page_access_status[32*1024];

	//input signals to the cpu hardwired to 
	//a certain value in the Ajit processor:
	uint8_t bp_fpu_present;
	uint8_t bp_fpu_exception;
	uint8_t bp_fpu_cc;
	uint8_t bp_cp_present;
	uint8_t bp_cp_exception;
	uint8_t bp_cp_cc;

	uint8_t pb_error;
	uint8_t pb_block_ldst_word;
	uint8_t pb_block_ldst_byte;

	uint8_t report_traps;
} ProcessorState;


void cpu (void* state_ptr);
void 	init(ProcessorState *s, uint32_t processor_id, uint32_t isa_mode, int bp_table_size, uint8_t report_traps, uint32_t init_pc);
void 	resetProcessorState(ProcessorState *s);

void  setPageBit(ProcessorState* s, uint32_t virtual_addr);
void  dumpPageBits(ProcessorState* s);

uint64_t getCycleEstimate (ProcessorState* s);
uint32_t getAsrValue (ProcessorState* s, int asr_id);

void  	printCpuStatistics (ProcessorState* s);

uint32_t stack_pointer(ProcessorState* s);
uint32_t frame_pointer(ProcessorState* s);
uint32_t wim(ProcessorState* s);

#endif
