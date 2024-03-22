//CacheInterface.h
//
//CPU-side and memory side interface 
//of the Dcache and Icache
//AUTHOR: Neha Karanjkar


#ifndef _CACHE_INTERFACE_H
#define _CACHE_INTERFACE_H

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "Ajit_Hardware_Configuration.h"
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "Mmu.h"

#define ICACHE_TYPE 0
#define DCACHE_TYPE 1


#define MAX_NUMBER_OF_LINES  	512

// line offset is bit 7 down to 4
// line is 64 bytes..   so line address mask should
// mask off bottom 6 bits.
#define LINE_ADDR_MASK			(~0x3f)

//
// line is 8 dwords..
//   so offset of dword in line is specified by
//   bottom 3 bits of dword address.
#define DWORD_ADDR_OFFSET_MASK		0x7

typedef struct _CacheLine {
	uint64_t  cache_line[BYTES_PER_CACHE_LINE/8];
	uint8_t  acc;
	uint8_t  valid;
	uint32_t va_tag;
} CacheLine;


	
typedef struct _WriteThroughAllocateCache {

	uint32_t core_id;

	uint64_t number_of_accesses;
	uint64_t number_of_flushes;
	uint64_t number_of_bypasses;

	uint64_t number_of_hits;
	uint64_t number_of_misses;

	uint64_t number_of_write_hits;
	uint64_t number_of_write_misses;

	uint64_t number_of_read_hits;
	uint64_t number_of_read_misses;

	uint64_t number_of_invalidate_requests;
	uint64_t number_of_invalidates;

	uint32_t number_of_locked_accesses;
	
	int is_icache;
	int number_of_lines;
	int log_number_of_lines;


	int number_of_sets;
	int log_number_of_sets;
	int set_size;
	int last_updated_offset_in_set[MAX_NUMBER_OF_LINES];

	CacheLine cache_lines[MAX_NUMBER_OF_LINES];
	char from_rlut_pipe_name [256];

	// these are used by the DCACHE to
	// decide the handling of a request.
	//   (for example, on a miss, do
	//        not fetch the line, but
	//        just fetch the word.)
	uint32_t mmu_control_register[MMU_MAX_NUMBER_OF_THREADS];
	uint8_t  mmu_context_register[MMU_MAX_NUMBER_OF_THREADS];

	uint8_t  lock_flag;
	uint8_t  lock_core_id;

	uint8_t multi_context;

	pthread_mutex_t cache_mutex;
	
} WriteThroughAllocateCache;


uint32_t allocateCacheLine (WriteThroughAllocateCache* c, uint8_t context, uint32_t va);
uint32_t cacheSetId	  (WriteThroughAllocateCache* c, uint32_t va);

int cacheLineId (WriteThroughAllocateCache* c, uint8_t context, uint32_t va);
int cacheLineOffset (uint32_t va);
uint32_t vaTag(WriteThroughAllocateCache* c, uint8_t context, uint32_t va);


WriteThroughAllocateCache* makeCache (uint32_t core_id, int is_icache, int number_of_lines, int set_size);
void initCache (WriteThroughAllocateCache* c);
void lookupCache (WriteThroughAllocateCache* c,
			uint8_t context,
			uint32_t va, uint8_t asi, 
			uint8_t *hit,  uint8_t *acc);
void updateCacheLine (WriteThroughAllocateCache* c,
			uint8_t acc, 
			uint8_t context,
			uint32_t line_addr, uint64_t* line_data);
void invalidateCacheLine (WriteThroughAllocateCache* c, uint32_t va_line_address);
void flushCache (WriteThroughAllocateCache* c);
void decodeDcacheRequest (uint8_t asi, 
				uint8_t request_type,
				uint8_t *is_nop,
				uint8_t *is_stbar,
				uint8_t *is_flush,
				uint8_t *is_read,
				uint8_t *is_mem_access,
				uint8_t *is_mmu_access,
				uint8_t *is_mmu_bypass);
void decodeIcacheRequest (uint8_t asi, 
				uint8_t request_type,
				uint8_t *is_nop,
				uint8_t *is_flush,
				uint8_t *is_ifetch);

uint64_t getDwordFromCache (WriteThroughAllocateCache* c, uint8_t context, uint32_t va);
void     writeIntoLine(WriteThroughAllocateCache* c, uint64_t write_data, uint8_t context, uint32_t va, uint8_t byte_mask);

void cpuIcacheAccess (int core_id, 
			int cpu_id, 
			uint8_t context,
			MmuState* ms, 
			WriteThroughAllocateCache* icache,
			uint8_t asi, uint32_t addr, uint8_t request_type, uint8_t byte_mask,
				uint8_t* mae, uint64_t* instr_pair, uint32_t* mmu_fsr);
void dumpCpuIcacheAccessTrace
		(WriteThroughAllocateCache* icache,
			uint8_t asi, uint32_t addr, uint8_t request_type, uint8_t byte_mask,
				uint8_t mae, uint64_t instr_pair, uint32_t mmu_fsr, uint8_t is_hit);
 
void cpuDcacheAccess (int core_id, 
			int cpu_id, 
			uint8_t context, 
			MmuState* ms, 
			WriteThroughAllocateCache* dcache,
			uint8_t asi, uint32_t addr, uint8_t request_type, uint8_t byte_mask,
				uint64_t write_data,
				uint8_t* mae, uint64_t* read_data);
void dumpCpuDcacheAccessTrace 
		     (WriteThroughAllocateCache* dcache,
			uint8_t asi, uint32_t addr, uint8_t request_type, uint8_t byte_mask,
				uint64_t write_data,
				uint8_t mae, uint64_t read_data, uint8_t is_hit);


void printCacheStatistics (WriteThroughAllocateCache* c);

void lock_cache (WriteThroughAllocateCache* c);
void unlock_cache (WriteThroughAllocateCache* c);

int accessPermissionsOk (uint8_t request_type, uint8_t asi, uint8_t acc);
uint32_t probeCoherencyInvalidateRequest(int core_id, int icache_flag);
				
void updateMmuState (WriteThroughAllocateCache* c, 
			int cpu_id, 
			uint8_t   byte_mask,
			uint32_t  waddr,
			uint64_t  write_dword);
int isCacheableRequestBasedOnMmuStatus (WriteThroughAllocateCache* c, int cpu_id);
int isMmuContextPointerWrite (uint8_t asi, uint32_t va);

void setCacheTraceFile(FILE* fp);
FILE* getCacheTraceFile();
						
#endif
