#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <pthreadUtils.h>
#include "CacheInterface.h"
#include "Mmu.h"
#include "Ancillary.h"
#include "ASI_values.h"
#include "RequestTypeValues.h"

extern pthread_mutex_t cache_mutex;

int icache_forward_to_mmu(int asi)
{
	if(ASI_MMU_ACCESS(asi)
	|| ASI_USER_OR_SUPV_ACCESS(asi)
	|| ASI_MMU_PASS_THROUGH(asi)
	 )
		return 1;
	else
		return 0;
}


void cpuIcacheAccess (int core_id, int cpu_id, uint8_t context, MmuState* ms,
				WriteThroughAllocateCache* icache,
				uint8_t asi, uint32_t addr, uint8_t request_type, uint8_t byte_mask,
				uint8_t* mae, uint64_t* instr_pair, uint32_t* mmu_fsr)
{
	lock_cache (icache);
	
	// service all the coherency related invalidates..
	while(1)
	{
		uint32_t icache_invalidate_word = probeCoherencyInvalidateRequest(ms->core_id, 1);
		if(icache_invalidate_word != 0)
		{
			uint32_t invalidate_va = 
					(icache_invalidate_word & 0x7fffffff) << LOG_BYTES_PER_CACHE_LINE;
			invalidateCacheLine(icache, invalidate_va);
		}
		else
			break;
	}

#ifdef DEBUG
	fprintf(stderr,"\n\nICACHE :  read CPU request asi=0x%x, addr=0x%x, req_type=0x%x, byte_mask=0x%x\n",asi,addr,request_type,byte_mask);
#endif
	
	if(!icache->multi_context)
	{
		// If DCACHE is not a multi-context one, then context is ignored.
		context = 0;
	}

	*mae=0;
	*mmu_fsr = 0;
	*instr_pair  = 0;

	uint8_t cacheable=0;
		
	//clear the top  bit (thread-head bit) in asi.
	asi=asi&0x7F;

	// not needed in new C ref model, bit 7 should be 0.
	request_type = request_type & 0x3f;

	uint8_t is_flush, is_nop, is_ifetch;
	uint8_t acc=0;
	uint8_t is_hit  = 0;

	decodeIcacheRequest (asi, request_type, &is_nop, &is_flush, &is_ifetch);
	icache->number_of_accesses++;
	if(is_flush)
	{
		icache->number_of_flushes++;
		flushCache(icache);
	}
	else if (is_ifetch)
	{
		uint8_t is_raw_hit = 0;
		lookupCache(icache, context,
				addr, asi, &is_raw_hit,  &acc);
		int access_ok = accessPermissionsOk(request_type, asi, acc);
		is_hit = is_raw_hit && access_ok;

		if(is_hit)
		{	
			icache->number_of_hits++;
			*instr_pair = getDwordFromCache	(icache, context, addr);
			*mae = (1 << 7) | (acc << 4);
		}
		else
		{
			icache->number_of_misses++;
			uint32_t line_addr = (addr & LINE_ADDR_MASK);
			uint64_t line_data[8];
			uint32_t synonym_invalidation_word = 0;

			Mmu(ms, cpu_id, MMU_READ_LINE, REQUEST_TYPE_IFETCH, 
					asi, addr, byte_mask, 0x0,
					mae, &cacheable, &acc, (uint64_t*) line_data, 
					mmu_fsr,
					&synonym_invalidation_word);

			// mae fields
			//   7 6:4 3:2 1 0
			//   cacheable acc unused err exception.
			*mae = (cacheable << 7) | (acc << 4) | (0x3 & *mae);

			if(synonym_invalidation_word != 0)
			{
				uint32_t invalidate_va = 
					(synonym_invalidation_word & 0x7fffffff) << LOG_BYTES_PER_CACHE_LINE;
				invalidateCacheLine(icache, invalidate_va);
			}

			if(cacheable)
			{
				updateCacheLine (icache, acc, context, line_addr, line_data);
				*instr_pair = getDwordFromCache (icache, context, addr);
			}
			else
			{
				*instr_pair = line_data[cacheLineOffset(addr)];
			}
		}
	}

	if(getCacheTraceFile() != NULL)
	{
		dumpCpuIcacheAccessTrace(icache, asi, addr, request_type, byte_mask, 
							*mae, *instr_pair, *mmu_fsr, is_hit);
	}

	unlock_cache(icache);
#ifdef DEBUG
	fprintf(stderr,"\nICACHE :  response to CPU mae=0x%x, instr-pair=0x%lx, mmu-fsr=0x%x\n",
				*mae,*instr_pair, *mmu_fsr);
#endif

}




