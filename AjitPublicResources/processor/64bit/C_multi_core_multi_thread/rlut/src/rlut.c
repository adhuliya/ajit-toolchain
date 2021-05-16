#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "Pipes.h"
#include "pipeHandler.h"
#include "pthreadUtils.h"
#include "tlbs.h"
#include "rlut.h"
#include "ASI_values.h"
char *dcache_inval_pipe_names[] = 
		{
			"NOBLOCK_RLUT_DCACHE_INVALIDATE_0", 
			"NOBLOCK_RLUT_DCACHE_INVALIDATE_1", 
			"NOBLOCK_RLUT_DCACHE_INVALIDATE_2", 
			"NOBLOCK_RLUT_DCACHE_INVALIDATE_3", 
		};
char *icache_inval_pipe_names[] = 
		{
			"NOBLOCK_RLUT_ICACHE_INVALIDATE_0", 
			"NOBLOCK_RLUT_ICACHE_INVALIDATE_1", 
			"NOBLOCK_RLUT_ICACHE_INVALIDATE_2", 
			"NOBLOCK_RLUT_ICACHE_INVALIDATE_3", 
		};

char* getCacheInvalPipeName(int cpu_id, int icache_flag)
{
	assert(cpu_id < 4);
	assert(cpu_id >= 0);
	if(icache_flag)
		return (icache_inval_pipe_names[cpu_id]);
	else
		return (dcache_inval_pipe_names[cpu_id]);
}

RlutManager rlut_manager;

int myLog2(int x)
{
	int ret_val = 0;
	while (x > 1)
	{
		ret_val++;
		x = (x >> 1);
	}
	return(ret_val);
}


// Technically, there is no reason to keep the entire
// VA line address in the RLUT.  We know that bits [5:0] of
// the VA line address are the same as the PA to which it
// is mapped.
uint32_t reduceVaLineAddr(uint32_t va_line_addr)
{
	// data_width should be 3 for 512 line cache.
	int data_width = ((LOG_CACHE_SIZE + LOG_CACHE_LINE_SIZE) - LOG_BASE_PAGE_SIZE);
	uint32_t ret_val = (va_line_addr >> (LOG_BASE_PAGE_SIZE - LOG_CACHE_LINE_SIZE)) & ((1 << data_width)  - 1);
	return(ret_val);
}


// Given bits [8:6] of the VA, the line address is obatined by concatenating
// bits [5:0] of the PA line address to them.
uint32_t reconstructVaLineAddr(uint32_t pa_line_addr, uint32_t reduced_va_line_addr)
{
	uint32_t ret_val = (reduced_va_line_addr << (LOG_BASE_PAGE_SIZE - LOG_CACHE_LINE_SIZE));
	ret_val = ret_val | (pa_line_addr & ((1 << (LOG_BASE_PAGE_SIZE - LOG_CACHE_LINE_SIZE))-1));
	return(ret_val);
}

					
	
uint32_t generateTag(Rlut* r, uint32_t pa_line_addr)
{
	uint32_t ret_val = pa_line_addr >> r->pa_tlb->log_number_of_sets;
	return(ret_val);
}


uint32_t generateSetIndex(Rlut* r, uint32_t pa_line_addr)
{
	uint32_t ret_val = pa_line_addr & ((r->pa_tlb->mem_size/r->pa_tlb->set_size) - 1);
	return(ret_val);
}

void initRlut(Rlut* r, int cpu_id, int is_icache, int cache_size_in_lines)
{
	r->is_icache_rlut = is_icache;
	r->cpu_id = cpu_id;
	r->cache_size_in_lines = cache_size_in_lines;
	r->number_of_requests_from_mmu = 0;
	r->number_of_requests_from_biu = 0;
	r->number_of_synonym_invalidates = 0;
	r->number_of_coherency_invalidates = 0;
	
	int mem_size   = cache_size_in_lines;
	int set_size   = cache_size_in_lines * CACHE_LINE_SIZE / BASE_PAGE_SIZE;
	int tag_width  = (PHYSICAL_ADDR_WIDTH - LOG_CACHE_LINE_SIZE) - myLog2(set_size);
	int data_width = ((LOG_CACHE_SIZE + LOG_CACHE_LINE_SIZE) - LOG_BASE_PAGE_SIZE);

	r->pa_tlb      = findOrAllocateSetAssociativeMemory((is_icache ? 9 : 10),
									tag_width, 
									data_width, 
									myLog2(mem_size),
									myLog2(set_size));

  	pthread_mutex_init (&(r->rlut_mutex), NULL);
}

void printRlutStatistics(Rlut* r)
{
	fprintf(stderr,"Info: RLUT %d %s:  mmu-reqs = %d, biu-reqs=%d, syn-invalidates=%d, coh-invalidates=%d\n",
			r->cpu_id, 
			r->is_icache_rlut ? "icache" : "dcache",
			r->number_of_requests_from_mmu,
			r->number_of_requests_from_biu,
			r->number_of_synonym_invalidates,
			r->number_of_coherency_invalidates);
}

void printRlutStatisticsInManager()
{
	int I;
	for(I = 0; I < rlut_manager.number_of_cpus; I++)
	{
		printRlutStatistics(&(rlut_manager.icache_rluts[I]));
		printRlutStatistics(&(rlut_manager.dcache_rluts[I]));
	}
}

void     flushRlut(Rlut* r)
{
	clearSetAssociativeMemory (r->pa_tlb);
}

uint32_t lookupAndUpdateRlut(Rlut* r, uint32_t pa_line_addr, uint32_t va_line_addr)
{
	pthread_mutex_lock(&(r->rlut_mutex));

	r->number_of_requests_from_mmu += 1;

	uint32_t pa_tag = generateTag(r, pa_line_addr);
	uint32_t pa_set_id = generateSetIndex(r, pa_line_addr);

	uint32_t va_reduced = reduceVaLineAddr (va_line_addr);

	uint8_t hit = 0;
	uint64_t hit_va_64 = 0;

	operateOnSetAssociativeMemory (r->pa_tlb,
					0, // clear
					0, // erase
					1,  // write
					va_reduced,
					pa_tag,
					pa_set_id,
					1,  // lookup
					pa_tag,
					pa_set_id, 
					&hit,
					&hit_va_64);
					
	uint32_t hit_va = hit_va_64;

	uint32_t ret_val = 0;
	if(hit && (hit_va != va_reduced))
	{
		ret_val = (hit ? ((hit << 31) | reconstructVaLineAddr(pa_line_addr, hit_va)) : 0);
		r->number_of_synonym_invalidates += 1;
#ifdef DEBUG
		fprintf(stderr,"Info: Synonym invalidate.  for pa=0x%x va=0x%x hit_va=0%x\n", 
						pa_line_addr << 6, 
						va_line_addr << 6,
						hit_va << 6);
#endif
	}

	pthread_mutex_unlock(&(r->rlut_mutex));
	return(ret_val);
}

uint32_t lookupRlut(Rlut* r, uint32_t pa_line_addr)
{
	pthread_mutex_lock(&(r->rlut_mutex));

	r->number_of_requests_from_biu += 1;

	uint32_t pa_tag = generateTag(r, pa_line_addr);
	uint32_t pa_set_id = generateSetIndex(r, pa_line_addr);

	uint8_t hit = 0;
	uint64_t hit_va_64 = 0;
	operateOnSetAssociativeMemory (r->pa_tlb,
					0, // clear
					0, // erase
					0,  // write
					0,
					0,
					0,
					1,  // lookup
					pa_tag,
					pa_set_id, 
					&hit,
					&hit_va_64);
					
	uint32_t hit_va = hit_va_64;
	uint32_t ret_val = (hit ? ((hit << 31) | reconstructVaLineAddr(pa_line_addr, hit_va)) : 0);

	if(hit)
	{
#ifdef DEBUG
		fprintf(stderr,"Info: Coherence invalidate.  for pa=0x%x  hit_va=0%x\n", 
						pa_line_addr << 6, 
						reconstructVaLineAddr(pa_line_addr, hit_va);
#endif
		r->number_of_coherency_invalidates += 1;
	}

	pthread_mutex_unlock(&(r->rlut_mutex));
	return(ret_val);
}

void setupRlutManager (int ncpus, int icache_size_in_lines, int dcache_size_in_lines)
{
	assert(ncpus <= MAX_N_CPUS);

	rlut_manager.number_of_cpus = ncpus;
	int I;
	for(I = 0; I < ncpus; I++)
	{
		initRlut(&(rlut_manager.icache_rluts[I]),  I , 1, icache_size_in_lines);
		initRlut(&(rlut_manager.dcache_rluts[I]),  I , 0, dcache_size_in_lines);
		
		register_pipe(dcache_inval_pipe_names[I], 2, 32, PIPE_FIFO_NON_BLOCK_READ);
		register_pipe(icache_inval_pipe_names[I], 2, 32, PIPE_FIFO_NON_BLOCK_READ);
	}
}

uint32_t lookupAndUpdateRlutInManager(int cpu_id, uint32_t pa_line_addr, uint32_t va_line_addr, int icache_flag)
{
	assert(cpu_id < rlut_manager.number_of_cpus);
	assert(cpu_id >= 0);

	uint32_t ret_val = 0;
	if(icache_flag)
		ret_val = lookupAndUpdateRlut(&(rlut_manager.icache_rluts[cpu_id]), pa_line_addr, va_line_addr);
	else
		ret_val = lookupAndUpdateRlut(&(rlut_manager.dcache_rluts[cpu_id]), pa_line_addr, va_line_addr);
	
	return(ret_val);
}

//  this is called from the BIU/bridge 
uint32_t lookupRlutInManager(int cpu_id, uint32_t pa_line_addr, int icache_flag)
{
	assert(cpu_id < rlut_manager.number_of_cpus);
	assert(cpu_id >= 0);

	uint32_t ret_val = 0;
	if(icache_flag)
		ret_val = lookupRlut(&(rlut_manager.icache_rluts[cpu_id]), pa_line_addr);
	else
		ret_val = lookupRlut(&(rlut_manager.dcache_rluts[cpu_id]), pa_line_addr);
	
	return(ret_val);
}

void flushRlutInManager(int cpu_id, int icache_flag)
{
	assert(cpu_id < rlut_manager.number_of_cpus);
	assert(cpu_id >= 0);

	if(icache_flag)
		flushRlut(&(rlut_manager.icache_rluts[cpu_id]));
	else
		flushRlut(&(rlut_manager.dcache_rluts[cpu_id]));
}

