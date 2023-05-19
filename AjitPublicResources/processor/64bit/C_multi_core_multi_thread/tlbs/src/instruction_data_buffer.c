#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <assert.h>
#include "tlbs.h"
#include "instruction_data_buffer.h"

int __myLog2__(int x)
{
	int ret_val = 0;
	while (x > 1)
	{
		ret_val++;
		x = (x >> 1);
	}
	return(ret_val);
}

void initInstructionDataBuffer 
	(InstructionDataBuffer* ib, 
			int core_id, 
			int cpu_id, int is_instr_buffer, int number_of_entries, int set_size)
{
	ib->core_id = core_id;
	ib->cpu_id = cpu_id;
	ib->is_instruction_buffer = is_instr_buffer;

	ib->number_of_entries = number_of_entries;
	ib->set_size = set_size;
	ib->number_of_sets = number_of_entries/set_size;


	ib->number_of_requests_from_cpu = 0;
	ib->number_of_hits = 0;
	ib->number_of_updates = 0;
	ib->number_of_flushes = 0;


	// 29 bit virtual address, 
	int tag_width = (29 - __myLog2__(set_size));
	ib->tlb =
		 findOrAllocateSetAssociativeMemory(((core_id+1)*10000) + cpu_id,
							tag_width, 
							8,
							__myLog2__(number_of_entries),
							__myLog2__(set_size));

	ib->acc = (uint8_t*) malloc (number_of_entries*sizeof(uint64_t));
}

uint32_t generateIDbufferTag(InstructionDataBuffer* ib, uint32_t va)
{
	uint32_t tag = (va >> (3 + ib->tlb->log_number_of_sets));
	return(tag);
}

uint32_t generateIDbufferSetIndex(InstructionDataBuffer* ib, uint32_t va)
{
	uint32_t set_index = (va >> 3) & ((ib->tlb->mem_size/ ib->tlb->set_size)-1);
	return(set_index);
}

// return 1 on hit.
int lookupInstructionDataBuffer (InstructionDataBuffer* ib, 
					uint32_t va, 
					uint8_t*  acc,
					uint64_t* ipair)
{
	uint8_t hit = 0;
	uint32_t lookup_tag = generateIDbufferTag (ib, va);
	uint32_t lookup_set_id =  generateIDbufferSetIndex (ib, va);

	operateOnSetAssociativeMemory (ib->tlb,
					1, // ignore collisions.
					0, // clear
					0, // erase
					0,  // write
					0, // write-data
					0, // write-tag
					0, // write-set-id
					1,  // lookup
					lookup_tag,
					lookup_set_id, 
					&hit,
					ipair);

	ib->number_of_requests_from_cpu++;
	if(hit != 0)
	{
		int idx = searchForTag (ib->tlb, lookup_set_id, lookup_tag);
		*acc    = ib->acc[idx];
		ib->number_of_hits++;
	}

	return((hit != 0));
}

int insertIntoInstructionDataBuffer (InstructionDataBuffer* ib, uint32_t va, uint8_t acc, uint64_t ipair)
{
	uint32_t insert_tag = generateIDbufferTag (ib, va);
	uint32_t insert_set_id =  generateIDbufferSetIndex (ib, va);

	operateOnSetAssociativeMemory (ib->tlb,
					1, // ignore collisions.
					0, // clear
					0, // erase
					1,  // write
					ipair, // write-data
					insert_tag, // write-tag
					insert_set_id, // write-set-id
					0,  // lookup
					0,
					0, 
					NULL,
					NULL);
	int idx = searchForTag (ib->tlb, insert_set_id, insert_tag);
	ib->acc[idx] = acc;

	ib->number_of_updates++;

	return(0);
}

void clearInstructionDataBuffer (InstructionDataBuffer* ib)
{
	operateOnSetAssociativeMemory (ib->tlb,
					1, // ignore collisions.
					1, // clear
					0, // erase
					0,  // write
					0, // write-data
					0, // write-tag
					0, // write-set-id
					0,  // lookup
					0,
					0, 
					NULL,
					NULL);
	ib->number_of_flushes++;
}


void invalidateLineInInstructionDataBuffer(InstructionDataBuffer* db,  uint32_t line_address)
{
	uint32_t I;
	for(I = 0; I < 8; I++)
	{
		invalidateDwordInInstructionDataBuffer(db, line_address + (I << 3));
	}
}

void invalidateDwordInInstructionDataBuffer(InstructionDataBuffer* db, uint32_t dword_address)
{
	uint32_t write_tag = generateIDbufferTag (db, dword_address);
	uint32_t write_set_id =  generateIDbufferSetIndex (db, dword_address);
	uint8_t  lv = 0;
	uint64_t ld = 0;

	operateOnSetAssociativeMemory (db->tlb,
					0, // ignore collision
					0, // clear
					1, // erase
					0, // write
					0, // write-data
					write_tag,
					write_set_id,
					0, // lookup
					0, 0, // lookup-tag, lookup-set-id
					&lv, &ld);
}


void reportInstructionDataBufferStatistics(InstructionDataBuffer* ib)
{
	fprintf(stderr,"Statistics for %s buffer for cpu %d,%d.\n", 
				(ib->is_instruction_buffer ? "instruction" : "data"),
				ib->core_id, ib->cpu_id);
	fprintf(stderr,"           number of cpu requests=%d.\n", ib->number_of_requests_from_cpu);
	fprintf(stderr,"           number of hits =%d.\n", ib->number_of_hits);
	fprintf(stderr,"           number of updates =%d.\n", ib->number_of_updates);
	fprintf(stderr,"           number of flushes =%d.\n", ib->number_of_flushes);
	
}



