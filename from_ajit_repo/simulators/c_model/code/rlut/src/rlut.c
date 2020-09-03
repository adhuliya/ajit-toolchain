#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "Pipes.h"
#include "pipeHandler.h"
#include "pthreadUtils.h"
#include "rlut.h"
#include "ASI_values.h"

uint32_t ipow (uint32_t x, uint32_t e)
{
	if(e == 0)
		return 1;
	else if (e == 1)
		return(x);
	else
	{
		uint32_t eby2 = e/2;
		return (ipow(x,eby2) * ipow(x,e-eby2));
	}
}

int isBitSet(uint32_t x, uint32_t b)
{
	return ((x & (1 << b)) != 0);
}

RlutState* makeRlutState (int cpu_id)
{
	RlutState* rs = (RlutState*) malloc (sizeof(RlutState));
	rs->cpu_id = cpu_id;

	initRlut (&(rs->icache_rlut));
	initRlut (&(rs->dcache_rlut));

	sprintf(rs->rlut_to_icache_pipe_name, "RLUT_to_ICACHE_%d", cpu_id);
	sprintf(rs->rlut_to_dcache_pipe_name, "RLUT_to_DCACHE_%d", cpu_id);
	sprintf(rs->biu_to_rlut_pipe_name, "BIU_to_RLUT_%d", cpu_id);


	rs->number_of_requests_from_biu = 0;
	rs->number_of_requests_forwarded_to_icache = 0;
	rs->number_of_requests_forwarded_to_dcache = 0;

	return(rs);
}

void printStatistics(RlutState* rs)
{
	fprintf(stderr,"Statistics of RLUT for cpuid=%d:\n", rs->cpu_id);
	if (rs->number_of_requests_from_biu > 0)
	fprintf(stderr,"    number-of-biu-requests=%ld.\n", rs->number_of_requests_from_biu);
	if (rs->number_of_requests_forwarded_to_icache > 0)
	fprintf(stderr,"    number-of-requests-forwarded-to-icache=%ld.\n", rs->number_of_requests_forwarded_to_icache);
	if (rs->number_of_requests_forwarded_to_dcache > 0)
	fprintf(stderr,"    number-of-requests-forwarded-to-dcache=%ld.\n", rs->number_of_requests_forwarded_to_dcache);
		
	
}

void initBitMaps (Rlut* r)
{
	int I;
	for(I=0; I < CACHE_SIZE; I++)
	{
		r->__va_tags[I] = 0;
		r->__pa_tags[I] = 0;
		r->__pa_va_bit_map[I] = 0;
	}
}


void initRlut (Rlut* r)
{
	initBitMaps  (r);
  	pthread_mutex_init (&(r->rlut_mutex), NULL);
}


//
// insert entry.
//
void insertEntry (RlutState* rs, uint32_t pa_line_addr, uint32_t va_line_addr, uint8_t asi)
{

	uint8_t from_icache = ((asi  == ASI_USER_INSTRUCTION) || (asi == ASI_SUPERVISOR_INSTRUCTION));
	if(from_icache)
	{
		insertEntryIntoRlut (&(rs->icache_rlut), pa_line_addr, va_line_addr);
	}
	else
	{
		insertEntryIntoRlut (&(rs->dcache_rlut), pa_line_addr, va_line_addr);
	}
}


void insertEntryIntoRlut (Rlut* r, uint32_t pa_line_addr, uint32_t va_line_addr)
{
	MUTEX_LOCK(r->rlut_mutex);

	// tag and index for the physical address.
	uint32_t pa_tag = (pa_line_addr >> LOG_CACHE_SIZE);
	uint16_t pa_idx = pa_line_addr & CACHE_LINE_INDEX_MASK; 
	uint8_t new_pa_entry = 0;

	//
	// if pa tag does not match, clear the existing
	// list and overwrite tag.
	//
	uint16_t pa_tag_match 	 = (isBitSet(r->__pa_tags[pa_idx],31) && 
					((r->__pa_tags[pa_idx] & 0x7fffffff) == pa_tag));

        if (!pa_tag_match)
	{
		r->__pa_tags [pa_idx] = (1 << 31) | pa_tag;
		r->__pa_va_bit_map [pa_idx] = 0;

		new_pa_entry = 1;
	}

	//
	// append to list
	//
	uint32_t va_tag = (va_line_addr >> LOG_CACHE_SIZE);
	uint16_t va_idx = va_line_addr & CACHE_LINE_INDEX_MASK; 
	uint16_t va_outer_index = (va_idx >> (LOG_BASE_PAGE_SIZE - LOG_CACHE_LINE_SIZE));

	//
	// since the caches are direct mapped, there can
	// be at most one va-tag for this index in the
	// cache.
	//
	uint32_t curr_va_tag = r->__va_tags[va_idx];

	if(new_pa_entry || (curr_va_tag != va_tag))
	{
		r->__va_tags[va_idx] = va_tag;
	}

	r->__pa_va_bit_map[pa_idx] = r->__pa_va_bit_map[pa_idx] | (1 << va_outer_index);
	MUTEX_UNLOCK(r->rlut_mutex);
}

void lookupEntryAndInvalidate (RlutState* rs, uint32_t pa_line_addr)
{
	int ival = 
		lookupEntryAndInvalidateFromRlut(&(rs->icache_rlut), pa_line_addr, 
								rs->rlut_to_icache_pipe_name);
	rs->number_of_requests_forwarded_to_icache += ival;
	int dval = 
		lookupEntryAndInvalidateFromRlut(&(rs->dcache_rlut), pa_line_addr, 
								rs->rlut_to_dcache_pipe_name);
	rs->number_of_requests_forwarded_to_dcache += dval;
}

int lookupEntryAndInvalidateFromRlut (Rlut* r, uint32_t pa_line_addr, char* pipe_name)
{
	
	MUTEX_LOCK(r->rlut_mutex);

	int ret_val = 0;
	uint32_t pa_tag = (pa_line_addr >> LOG_CACHE_SIZE);
	uint16_t pa_idx = pa_line_addr & CACHE_LINE_INDEX_MASK; 

	uint32_t saved_pa_tag = r->__pa_tags[pa_idx];
	if (isBitSet(saved_pa_tag,31) && ((saved_pa_tag & 0x7fffffff) == pa_tag)) 
	//
	// is pa present in rlut?
	//
	{

		// yes, pa is present.

		// find all the va's that match this pa.
		uint32_t __pa_va_bit_map = r->__pa_va_bit_map[pa_idx];

		uint8_t va_outer_index;
		uint8_t max_val;
		for (va_outer_index = 0, max_val = ipow(2, (LOG_CACHE_SIZE - 
						(LOG_BASE_PAGE_SIZE - LOG_CACHE_LINE_SIZE)));
			va_outer_index < max_val;
			va_outer_index++)
		{
			
			// outer index present?
			if (isBitSet(__pa_va_bit_map, va_outer_index))
			{
				// reconstruct the va-index.
				uint32_t va_index = (va_outer_index << 
							      (LOG_BASE_PAGE_SIZE - LOG_CACHE_LINE_SIZE)) |
							(pa_idx & PA_VA_OVERLAP_IDX_MASK);
				// lookup the va-tag.
				uint32_t va_tag = r->__va_tags[pa_idx];

				// reconstruct the va line address using pa-idx and va-outer-index.
				uint32_t reconstructed_va_line_addr =
					((va_tag & 0xfffff) << LOG_CACHE_SIZE) | va_index;

				write_uint32 (pipe_name, reconstructed_va_line_addr);
				ret_val++;
			}
		}

		// clear the entry for pa, it has been invalidated..
		r->__pa_tags[pa_idx] = 0;
		r->__pa_va_bit_map[pa_idx] = 0;
	}

	MUTEX_UNLOCK(r->rlut_mutex);
	return(ret_val);
}


void  parseMmuCommand(uint64_t mmu_cmd, 
		uint8_t *valid,
		uint8_t *insert, 
		uint8_t *flush, 
		uint8_t *asi,
		uint32_t *pa_line_addr, 
		uint32_t *va_line_addr)
{
	// bottom 23 bits of command
	*va_line_addr = (mmu_cmd & 0x7fffff);

	// bits [49:23] of command.
	*pa_line_addr = ((mmu_cmd >> 23) & 0x7ffffff);

	// bits [57:50] of command
	*asi = ((mmu_cmd >> 50) & 0xff);

	// bits [62:60] of command.
	uint8_t opcode = (mmu_cmd >> 60) & 0x7;

	*insert = (opcode == 1);
	*flush  = (opcode == 2);

	// top bit of command.
	*valid =  (mmu_cmd >> 63) & 0x1;

}

uint64_t constructMmuCommand (uint8_t insert, uint8_t flush, uint8_t asi, uint32_t pa_line_addr,
		uint32_t va_line_addr)
{
	uint64_t mmu_cmd = 1;
	mmu_cmd = (mmu_cmd << 3) | (insert ?  1  : 2);
	mmu_cmd = (mmu_cmd << 10) | asi;
	mmu_cmd = (mmu_cmd << 27) | (pa_line_addr & 0x7ffffff);
	mmu_cmd = (mmu_cmd << 23) | (va_line_addr & 0x7fffff);

	return(mmu_cmd);
}


int applyBiuCommand(uint32_t biu_cmd, RlutState* rs)
{
	uint8_t  valid = biu_cmd >> 31;
	uint32_t pa_line_addr = (biu_cmd & 0x7fffffff);

	if(valid)
	{
		
		rs->number_of_requests_from_biu++;
		lookupEntryAndInvalidate(rs, pa_line_addr);	
	}
	return(valid);
}


void flushRlut (Rlut* r)
{
	initBitMaps(r);
}


void registerRlutPipes (RlutState* rs)
{
	// non-blocking.
	register_pipe (rs->biu_to_rlut_pipe_name, 4, 32, PIPE_FIFO_NON_BLOCK_READ);
	set_watermark (rs->biu_to_rlut_pipe_name, 4);
}


void rlutDaemon_core(void *vrs)
{

	RlutState* rs = (RlutState*) vrs;

	while (1)
	{
		uint32_t biu_cmd = read_uint32(rs->biu_to_rlut_pipe_name);
		if(biu_cmd != 0)
		{
			applyBiuCommand (biu_cmd, rs);
		}
	}
	return;
}


void rlutDaemon_0 (void* vrs)
{
	rlutDaemon_core(vrs);
}
void rlutDaemon_1 (void* vrs)
{
	rlutDaemon_core(vrs);
}
void rlutDaemon_2 (void* vrs)
{
	rlutDaemon_core(vrs);
}
void rlutDaemon_3 (void* vrs)
{
	rlutDaemon_core(vrs);
}

DEFINE_THREAD_WITH_ARG(rlutDaemon_0, vrs);
DEFINE_THREAD_WITH_ARG(rlutDaemon_1, vrs);
DEFINE_THREAD_WITH_ARG(rlutDaemon_2, vrs);
DEFINE_THREAD_WITH_ARG(rlutDaemon_3, vrs);


void startRlutDaemon (RlutState* rs)
{
	registerRlutPipes (rs);
	
	PTHREAD_DECL(rlutDaemon_0);
	PTHREAD_DECL(rlutDaemon_1);
	PTHREAD_DECL(rlutDaemon_2);
	PTHREAD_DECL(rlutDaemon_3);

	if(rs->cpu_id == 0)
		PTHREAD_CREATE_WITH_ARG(rlutDaemon_0, ((void*) rs));
	if(rs->cpu_id == 1)
		PTHREAD_CREATE_WITH_ARG(rlutDaemon_1, ((void*) rs));
	if(rs->cpu_id == 2)
		PTHREAD_CREATE_WITH_ARG(rlutDaemon_2, ((void*) rs));
	if(rs->cpu_id == 3)
		PTHREAD_CREATE_WITH_ARG(rlutDaemon_3, ((void*) rs));
}

