#ifndef __instruction_data_buffer___
#define __instruction_data_buffer___
typedef struct __InstructionDataBuffer {

	int core_id;
	int cpu_id;
	int is_instruction_buffer;

	int number_of_entries;
	int set_size;
	int number_of_sets;

	int number_of_requests_from_cpu;
	int number_of_hits;
	int number_of_updates;
	int number_of_flushes;

	uint8_t*  acc;
	setAssociativeMemory* tlb;

} InstructionDataBuffer;

void initInstructionDataBuffer (InstructionDataBuffer* ib,  
				int core_id, int cpu_id, int is_instr_buffer, int number_of_entries, int set_size);

// return 1 on hit.
int lookupInstructionDataBuffer (InstructionDataBuffer* ib, 
					uint32_t va, 
					uint8_t* acc,
					uint64_t* ipair);
// return index of added entry..
int insertIntoInstructionDataBuffer (InstructionDataBuffer* ib, uint32_t va, uint8_t acc, uint64_t ipair);

void clearInstructionDataBuffer (InstructionDataBuffer* ib);
void reportInstructionDataBufferStatistics(InstructionDataBuffer* ib);

uint32_t generateIDbufferTag(InstructionDataBuffer* ib, uint32_t va);
uint32_t generateIDbufferSetIndex(InstructionDataBuffer* ib, uint32_t va);

// invalidation..
void invalidateLineInInstructionDataBuffer(InstructionDataBuffer* db,  uint32_t line_address);
void invalidateDwordInInstructionDataBuffer(InstructionDataBuffer* db, uint32_t dword_address);




#endif
