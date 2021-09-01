#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"
#include "device_addresses.h"
#include "ajit_mt_irc.h"


uint32_t readInterruptControlRegister(int core_id, int thread_id)
{
	uint32_t addr = ADDR_INTERRUPT_CONTROLLER_MIN + (4*((2*core_id) + thread_id));
	uint32_t ret_val = __ajit_load_word_mmu_bypass__(addr);
	return(ret_val);
}

void     writeInterruptControlRegister(int core_id, int thread_id, uint32_t value)
{
	uint32_t addr = ADDR_INTERRUPT_CONTROLLER_MIN + (4*((2*core_id) + thread_id));
	__ajit_store_word_mmu_bypass__(addr,value);

}


// set bit [0] = 1 in control register for core, thread
void enableInterruptController(int core_id, int thread_id)
{
	uint32_t cv = readInterruptControlRegister(core_id,thread_id);
	cv = cv | 0x1;
	writeInterruptControlRegister(core_id, thread_id, cv);
}

// set bit [0] = 0 in control register for core, thread
void disableInterruptController(int core_id, int thread_id)
{
	uint32_t cv = readInterruptControlRegister(core_id,thread_id);
	cv = cv &  (~ 0x1);
	writeInterruptControlRegister(core_id, thread_id, cv);
}


// set bit [interrupt_id] = 1 in control register for core, thread
void enableInterrupt(int core_id, int thread_id, int interrupt_id)
{
	uint32_t cv = readInterruptControlRegister(core_id,thread_id);
	cv = cv | (1 << interrupt_id);
	writeInterruptControlRegister(core_id, thread_id, cv);
}

// enable all 15 interrupts on core/thread.
void enableAllInterrupts(int core_id, int thread_id)
{
	uint32_t cv = readInterruptControlRegister(core_id,thread_id);
	cv = cv | 0xfffe;
	writeInterruptControlRegister(core_id, thread_id, cv);
}

// Note: mask[15:1] is written into control register[15:1]
// for (core_id, thread_id).  Other bits of the control register
// are not modified.  Use with care.   This should be called
// only when the IRC is disabled.
void setInterruptMask(int core_id, int thread_id, uint32_t mask)
{
	uint32_t cv = readInterruptControlRegister(core_id,thread_id);

	// selects bits [15:1]
	uint32_t insert_mask = ((~ 0x1) & 0xffff);

	// bits [15:1] are updated.
	cv = (cv & (~insert_mask)) | (insert_mask & mask);

	writeInterruptControlRegister(core_id, thread_id, cv);
}


// set bit [interrupt_id] = 0 in control register for core, thread
void disableInterrupt(int core_id, int thread_id, int interrupt_id)
{
	uint32_t cv = readInterruptControlRegister(core_id,thread_id);
	cv = cv &  (~(1 << interrupt_id));
	writeInterruptControlRegister(core_id, thread_id, cv);
}

