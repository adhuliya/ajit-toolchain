//Mmu.h
// AUTHOR: Neha Karanjkar

#ifndef _MMU_H_
#define _MMU_H_
#include <stdint.h>
#include <pthread.h>
#include <pthreadUtils.h>
#include "Ajit_Hardware_Configuration.h"
#include "rlut.h"
#ifdef USE_NEW_TLB
#include "tlbs.h"
#endif
#include "MmuCommands.h"

// Two threads can use an MMU for now.
// should be a power of two.
#define MMU_MAX_NUMBER_OF_THREADS  2

#define MMU_THREAD_MASK  (MMU_MAX_NUMBER_OF_THREADS-1)
//each entry in the TLB has the following fields:
typedef struct __TlbEntry
{
	uint32_t va_tag;	//virtual address tag
	uint32_t ctx_tag;	//context tag
	uint32_t pte;		//page table entry
	uint8_t	 pte_level;	//level at which this pte was found
				//in the page table hierarchy.
				//the level can be:
				//0 => PTE was found in context table
				//1 => PTE was found in Level-1 Table
				//2 => PTE was found in Level-2 Table
				//3 => PTE was found in Level-3 Table
} TlbEntry;


typedef struct _MmuState {

	uint32_t core_id;
	pthread_mutex_t mmu_mutex;

	char req_pipe[256];
	char addr_pipe[256];
	char wdata_pipe[256];
	char byte_mask_pipe[256];
	char rdata_pipe[256];

	char to_rlut_pipe[256];



	// Mmu Registers, maintained on a per-thread basis.
	uint32_t MmuControlRegister[MMU_MAX_NUMBER_OF_THREADS];
	uint32_t MmuContextTablePointerRegister[MMU_MAX_NUMBER_OF_THREADS];
	uint32_t MmuContextRegister[MMU_MAX_NUMBER_OF_THREADS];
	uint32_t MmuFaultStatusRegister[MMU_MAX_NUMBER_OF_THREADS];
	uint32_t MmuFaultAddressRegister[MMU_MAX_NUMBER_OF_THREADS];

	uint8_t  Mmu_FSR_FAULT_CLASS[MMU_MAX_NUMBER_OF_THREADS]; //The type of the last FSR fault (NONE/IACCESS_FAULT/DACCESS_FAULT)

	//Variables for keep count of Mmu events
	uint32_t Num_Mmu_bypass_accesses[MMU_MAX_NUMBER_OF_THREADS];
	uint32_t Num_Mmu_probe_requests[MMU_MAX_NUMBER_OF_THREADS];
	uint32_t Num_Mmu_flush_requests[MMU_MAX_NUMBER_OF_THREADS];
	uint32_t Num_Mmu_register_reads[MMU_MAX_NUMBER_OF_THREADS];
	uint32_t Num_Mmu_register_writes[MMU_MAX_NUMBER_OF_THREADS];
	uint32_t Num_Mmu_translated_accesses[MMU_MAX_NUMBER_OF_THREADS];
	uint32_t Num_Mmu_TLB_hits[MMU_MAX_NUMBER_OF_THREADS];


#ifdef USE_NEW_TLB
	// new TLB implementation mirrors
	// hardware TLBs.
	setAssociativeMemory* tlb_0;
	setAssociativeMemory* tlb_1;
	setAssociativeMemory* tlb_2;
	setAssociativeMemory* tlb_3;
#else
	TlbEntry TLB_entries[TLB_SIZE];
#endif

	uint32_t counter;

	uint8_t mmu_is_present;
	uint8_t multi_context;

	uint8_t lock_flag;
	uint8_t lock_cpu_id;

} MmuState;


// Mmu Behavior
MmuState* makeMmuState (uint32_t core_id);
void resetMmuState (MmuState* ms);
void printMmuStatistics(MmuState* ms);
void Mmu(MmuState* ms, int thread_id,
			uint8_t mmu_command,
			uint8_t request_type,
			uint8_t asi, uint32_t addr,	
			uint8_t byte_mask, uint64_t write_data,
			uint8_t* mae, 
			uint8_t* cacheable, 
			uint8_t* acc,
			uint64_t* read_data,
			uint32_t* mmu_fsr,
			uint32_t* synonym_invalidate_word);

void register_mmu_pipes (MmuState* ms);
#endif
