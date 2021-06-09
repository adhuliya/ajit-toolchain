//-------------------------------------------------------------------------
// Header file for cpu thread
//-------------------------------------------------------------------------

#ifndef __SPARC_CORE_H__
#define __SPARC_CORE_H__

typedef enum _ProcessorMode
{
	_RESET_MODE_,
	_EXECUTE_MODE_,
	_ERROR_MODE_
} ProcessorMode;

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
	uint32_t instruction;
	uint32_t mmu_fsr;
	uint8_t addr_space;
	ProcessorMode mode;
	uint32_t trap_vector;
	uint8_t interrupt_level;
	uint8_t ticc_trap_type;
	uint8_t store_barrier_pending;
	StatusRegisters status_reg;
	StateUpdateFlags reg_update_flags;

} ProcessorState;


#endif
