#ifndef  __rlut_h___
#define  __rlut_h___

// base page size is 4kB
#define BASE_PAGE_SIZE 		4096  // bytes
#define LOG_BASE_PAGE_SIZE 	  12  // bytes
#define PHYSICAL_ADDR_WIDTH	  36
#define VIRTUAL_ADDR_WIDTH	  32


#define PA_VA_OVERLAP_IDX_MASK    0x3f // bottom 6 bits of index for 512 line cache.

#define LOG_CACHE_LINE_SIZE    6    // bytes.
#define CACHE_LINE_SIZE       64    // bytes.

// these three should be consistent
// with each other.
#define CACHE_SIZE       512	// lines
#define LOG_CACHE_SIZE   9	// lines
#define CACHE_LINE_INDEX_MASK 0x1ff

#define MAX_N_CPUS		 4	

#include "tlbs.h"

//
// The RLUT needs to maintain the reverse translation
// state of those physical addresses which are represented
// in the VIVT cache.
//
// Let us take the case of a 32KB VIVT cache.
// The PA's which can be in the cache can be
// organized into the following sets.
//    set 0:  
//        pa[14:6] = 0
//        and pa[17:15] = 0,1,2,..., 7
//    set 1:
//        pa[14:6] = 1
//        and pa[17:15] = 0,1,2,..., 7
//
// For cache sizes < 4KB, there is no synonym
// possible.  For cache size 32KB, there can
// be 8 synonyms if we are not careful.  This
// RLUT ensures the following:
//     Each PA represented in the VIVT will have
//     exactly 1 synonym.
// 
// Everytime there is a cache miss, and a new
// line is loaded into cache, the RLUT updates
// the set associative cache (alluded to above)
// with the PA/VA pair.  If there is a hit,
// the previous VA mapped to the PA is invalidated
// in the VIVT cache.
//
typedef struct __Rlut {

	int       is_icache_rlut;
	int 	  cpu_id;
	int       cache_size_in_lines;
	int 	  cache_set_size;
	int 	  data_width;
	
	// PA -> VA
	setAssociativeMemory* pa_tlb;

	uint32_t  number_of_requests_from_mmu;
	uint32_t  number_of_requests_from_biu;
	uint32_t  number_of_synonym_invalidates;
	uint32_t  number_of_coherency_invalidates;

	pthread_mutex_t rlut_mutex;
} Rlut;

void initRlut(Rlut* r, int cpu_id, int is_icache, int cache_size_in_lines, int cache_set_size);
void     flushRlut(Rlut* r);

// return (1 << 32) | va[31:6] on match
//         0 otherwise.
uint32_t lookupAndUpdateRlut(Rlut* r, uint32_t pa_line_addr, uint32_t va_line_addr);
uint32_t lookupRlut(Rlut* r, uint32_t pa_line_addr);

// print stats.
void printRlutStatistics(Rlut* r);


typedef struct __RlutManager {
	int number_of_cpus;
	Rlut icache_rluts[MAX_N_CPUS];
	Rlut dcache_rluts[MAX_N_CPUS];
} RlutManager;

void setupRlutManager (int ncpus, int icache_size_in_lines, int icache_associativity, int dcache_size_in_lines, int dcache_associativity);
uint32_t lookupAndUpdateRlutInManager(int cpu_id, uint32_t pa_line_addr, uint32_t va_line_addr, int icache_flag);
uint32_t lookupRlutInManager(int cpu_id, uint32_t pa_line_addr, int icache_flag);
void flushRlutInManager(int cpu_id, int icache_flag);
void printRlutStatisticsInManager();
char* getCacheInvalPipeName(int cpu_id, int icache_flag);

#endif
