#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"
#include "device_addresses.h"
#include "ajit_mt_irc.h"
#include "core_portme.h"

void (*ajit_global_interrupt_handlers[16]) ();

void ajit_initialize_interrupt_handlers_to_null()
{
	int I;
	for(I = 0; I < 16; I++)
		ajit_global_interrupt_handlers[I] = NULL;
}

void ajit_set_interrupt_handler (uint32_t interrupt_level, void (* foo) ())
{
	if(interrupt_level < 16)
		ajit_global_interrupt_handlers[interrupt_level] = foo;
		
}

void ajit_generic_interrupt_handler(uint32_t tbr_value)
{
	uint8_t core_id, thread_id;
	ajit_get_core_and_thread_id(&core_id, &thread_id);
	disableInterruptController(core_id, thread_id);	

	int err = 0;
	uint32_t trap_type = (tbr_value >> 4) & 0xff;
	if((trap_type >= 0x11) && (trap_type <= 0x1f))	
	{
		uint32_t ilevel = (trap_type - 0x10);
		void (*fn_ptr)() = ajit_global_interrupt_handlers[ilevel];
		if(fn_ptr != NULL)
		{
			(*fn_ptr) ();
		}
		else
		{
			err = 1;
		}
	}
	else
		err = 1;

	enableInterruptController(core_id, thread_id);	

	if(err)
	{
		__AJIT_HALT();
	}
}

uint32_t readInterruptControlRegister(int core_id, int thread_id)
{
	uint32_t addr = ADDR_INTERRUPT_CONTROLLER_MIN + (4*((2*core_id) + thread_id));
#ifdef USE_VMAP
	uint32_t ret_val = *((uint32_t*) addr);
#else
	uint32_t ret_val = __ajit_load_word_mmu_bypass__(addr);
#endif
	return(ret_val);
}

void     writeInterruptControlRegister(int core_id, int thread_id, uint32_t value)
{
	uint32_t addr = ADDR_INTERRUPT_CONTROLLER_MIN + (4*((2*core_id) + thread_id));
#ifdef USE_VMAP
	*((uint32_t*)addr) = value;
#else
	__ajit_store_word_mmu_bypass__(value, addr);
#endif
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
// NOTE: this function does not touch bit 0.
void enableInterrupt(int core_id, int thread_id, int interrupt_id)
{
	uint32_t cv = readInterruptControlRegister(core_id,thread_id);
	cv = cv | (1 << interrupt_id);
	writeInterruptControlRegister(core_id, thread_id, cv);
}

// set bits [15:1] in control register core (core_id,thread_id) to 1.
// NOTE: this function does not touch bit 0.
void enableAllInterrupts(int core_id, int thread_id)
{
	uint32_t cv = readInterruptControlRegister(core_id,thread_id);
	cv = cv | 0xfffe;
	writeInterruptControlRegister(core_id, thread_id, cv);
}

// set bits [15:0] in control register core (core_id,thread_id) to 1.
// NOTE: this function sets bit 0.
void enableInterruptControllerAndAllInterrupts(int core_id, int thread_id)
{
	writeInterruptControlRegister(core_id, thread_id, 0xffff);
}


// Note: mask[15:1] is written into control register[15:1]
// for (core_id, thread_id).  Other bits of the control register
// are not modified.  Use with care.   This should be called
// only when the IRC is disabled.
// NOTE: this function does not touch bit 0.
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

