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


// line offset is bit 7 down to 4
// line is 64 bytes..   so line address mask should
// mask off bottom 6 bits.
#define LINE_ADDR_MASK			(~0x3f)

//
// line is 8 dwords..
//   so offset of dword in line is specified by
//   bottom 3 bits of dword address.
#define DWORD_ADDR_OFFSET_MASK		0x7

#define NUMBER_OF_CACHE_LINES		512
#define LOG_NUMBER_OF_CACHE_LINES	9


typedef struct _CacheLine {
	uint64_t  cache_line[BYTES_PER_CACHE_LINE/8];
	uint8_t  acc;
	uint8_t  valid;
	uint32_t va_tag;
} CacheLine;

int cacheLineId (uint32_t va);
int cacheLineOffset (uint32_t va);
uint32_t vaTag(uint32_t va);

	
typedef struct _WriteThroughAllocateCache {

	uint32_t cpu_id;

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



	CacheLine cache_lines[NUMBER_OF_CACHE_LINES];
	char from_rlut_pipe_name [256];

	pthread_mutex_t cache_mutex;
	
} WriteThroughAllocateCache;

WriteThroughAllocateCache* makeCache (uint32_t cpu_id, int is_icache);
void initCache (WriteThroughAllocateCache* c);
void lookupCache (WriteThroughAllocateCache* c,
			uint32_t va, uint8_t asi, 
			uint8_t *hit,  uint8_t *acc);
void updateCacheLine (WriteThroughAllocateCache* c,
			uint8_t acc, 
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

uint64_t getDwordFromCache (WriteThroughAllocateCache* c, uint32_t va);
void     writeIntoLine(WriteThroughAllocateCache* c, uint64_t write_data, uint32_t va, uint8_t byte_mask);

void cpuIcacheAccess (MmuState* ms, 
			WriteThroughAllocateCache* icache,
			uint8_t asi, uint32_t addr, uint8_t request_type, uint8_t byte_mask,
				uint8_t* mae, uint64_t* instr_pair, uint32_t* mmu_fsr);
 
void cpuDcacheAccess (MmuState* ms, 
			WriteThroughAllocateCache* dcache,
			uint8_t asi, uint32_t addr, uint8_t request_type, uint8_t byte_mask,
				uint64_t write_data,
				uint8_t* mae, uint64_t* read_data);

void icacheInvalidate_core (WriteThroughAllocateCache* icache);
void dcacheInvalidate_core (WriteThroughAllocateCache* dcache);

void printCacheStatistics (WriteThroughAllocateCache* c);

void lock_cache (WriteThroughAllocateCache* c);
void unlock_cache (WriteThroughAllocateCache* c);

int accessPermissionsOk (uint8_t request_type, uint8_t asi, uint8_t acc);
				
#endif
