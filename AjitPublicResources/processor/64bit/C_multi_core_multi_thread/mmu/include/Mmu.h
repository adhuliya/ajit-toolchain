//Mmu.h
// AUTHOR: Neha Karanjkar

#ifndef _MMU_H_
#define _MMU_H_
#include <stdint.h>
#include "Ajit_Hardware_Configuration.h"
#include "rlut.h"
#ifdef USE_NEW_TLB
#include "tlbs.h"
#endif
#include "MmuCommands.h"

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

	uint32_t cpu_id;

	char req_pipe[256];
	char addr_pipe[256];
	char wdata_pipe[256];
	char byte_mask_pipe[256];
	char rdata_pipe[256];

	char to_rlut_pipe[256];

	//Mmu Registers
	uint32_t MmuControlRegister;
	uint32_t MmuContextTablePointerRegister;
	uint32_t MmuContextRegister;
	uint32_t MmuFaultStatusRegister;
	uint32_t MmuFaultAddressRegister;
	uint8_t  Mmu_FSR_FAULT_CLASS; //The type of the last FSR fault (NONE/IACCESS_FAULT/DACCESS_FAULT)

	//Variables for keep count of Mmu events
	uint32_t Num_Mmu_bypass_accesses;
	uint32_t Num_Mmu_probe_requests;
	uint32_t Num_Mmu_flush_requests;
	uint32_t Num_Mmu_register_reads;
	uint32_t Num_Mmu_register_writes;
	uint32_t Num_Mmu_translated_accesses;
	uint32_t Num_Mmu_TLB_hits;


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


	uint8_t lock_flag;

} MmuState;


// Mmu Behavior
MmuState* makeMmuState (uint32_t cpu_id);
void resetMmuState (MmuState* ms);
void printMmuStatistics(MmuState* ms);
void Mmu(MmuState* ms,
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
