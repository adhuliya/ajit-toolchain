//L2CacheInterface.h


#ifndef _WB_PA_CACHE_INTERFACE_H
#define _WB_PA_CACHE_INTERFACE_H

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "Ajit_Hardware_Configuration.h"
#include "pthreadUtils.h"

// These are fixed.
#define L2_BYTES_PER_CACHE_LINE			64
#define L2_DWORDS_PER_CACHE_LINE		(L2_BYTES_PER_CACHE_LINE/8)
#define L2_LINE_ADDR_MASK			(~0x3f)
#define L2_DWORD_ADDR_OFFSET_MASK		0x7

typedef struct __WriteBackCacheLine__ {
	uint64_t  pa_tag;
	uint8_t   dirty_dword_bits[L2_BYTES_PER_CACHE_LINE/8];
	uint64_t  cache_line[L2_BYTES_PER_CACHE_LINE/8];
	uint8_t   valid;
} WriteBackCacheLine;


	
typedef struct __WriteBackCache__ {

	uint32_t id;


	// statistics!
	uint64_t number_of_accesses;

	uint64_t number_of_write_hits;
	uint64_t number_of_write_misses;

	uint64_t number_of_read_hits;
	uint64_t number_of_read_misses;

	uint64_t number_of_memory_reads;
	uint64_t number_of_memory_writes;
	
	// configuration..
	int number_of_lines;
	int log_number_of_lines;

	int number_of_sets;
	int log_number_of_sets;
	int set_size;

	// for replacement
	uint8_t *most_recently_used_indices;

	// the lines.
	WriteBackCacheLine  *cache_lines;

	pthread_mutex_t cache_mutex;
	
} WriteBackCache;

// make the cache (note associativity = set size).
WriteBackCache* makeWriteBackCache (uint32_t id, int number_of_lines, int set_size);
void initWriteBackCache (WriteBackCache* c);
void clearWriteBackCache (WriteBackCache* c);

void setupAndEnableAES (FILE* fp, WriteBackCache* c);
			
			

// Write the specified line back to memory... if it is valid..
// Note: only dirty dwords are written back...  Note that the
//    pa will need to be specified so that we can figure
//    out the destination address.
void writeWriteBackCacheLineBackToMemory (WriteBackCache* c, uint64_t pa);
void readWriteBackCacheLineFromMemory    (WriteBackCache* c, uint64_t pa);



// Find a line suitable for the pa.  Also reports hit, replace status.
int  	 allocateWriteBackCacheLine   
	(WriteBackCache* c, uint64_t pa, uint8_t* hit, uint64_t* replace_base_addr,
			uint8_t* replace_flag);
void 	 invalidateWriteBackCacheLine (WriteBackCache* c, uint32_t line_index);
uint64_t readFromWriteBackCacheLine (WriteBackCache* c, uint32_t line_index, uint32_t offset_in_line);
uint64_t writeToWriteBackCacheLine 
		(WriteBackCache* c, uint32_t line_index, uint32_t offset_in_line,
						uint64_t wdword, uint8_t byte_mask);

// return: is_hit
//    line index is kept in *line_index.
int lookupL2Cache (WriteBackCache* c, uint64_t pa, int* line_index, uint8_t* index_in_set);

uint32_t writeBackCacheSetId	     (WriteBackCache* c, uint64_t pa);
uint32_t writeBackCacheLineOffset (uint64_t pa);
uint32_t writeBackCachePaTag(WriteBackCache* c, uint64_t pa);
uint64_t calculateLinePa (WriteBackCache* c, uint64_t pa_tag, uint32_t set_id);

uint64_t doWriteBackCacheAccess
	(WriteBackCache* l2_cache, uint8_t rwbar, uint8_t byte_mask, uint64_t pa, uint64_t write_dword);


uint64_t calculatePaForLine (WriteBackCache* c, int line_index);
void printWriteBackCacheStatistics (WriteBackCache* c);
void lockWriteBackCache   (WriteBackCache* c);
void unlockWriteBackCache (WriteBackCache* c);

void setL2CacheTraceFile(FILE* fp) ;
void dumpL2CacheAccessTrace (WriteBackCache* c, uint64_t addr, uint8_t rwbar, uint8_t byte_mask,
					uint64_t wdata, uint64_t rdata);
						
#endif
