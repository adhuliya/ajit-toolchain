// DummyDcacheBehavior.c
//
//Dummy Dcache Behavior
//Simply forwards requests from CPU to MMU
//and forwards MMU side messages to CPU
// AUTHOR: Neha Karanjkar


#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "CacheInterface.h"
#include "Ancillary.h"
#include "ASI_values.h"
#include "RequestTypeValues.h"
#include "Mmu.h"

extern pthread_mutex_t cache_mutex;

void cpuDcacheAccess (MmuState* ms,
			WriteThroughAllocateCache* dcache,
				uint8_t asi, uint32_t addr, uint8_t request_type, uint8_t byte_mask,
				uint64_t write_data,
				uint8_t* mae, uint64_t* read_data)
{
	
	lock_cache(dcache);

	// service all the coherency related invalidates..
	while(1)
	{
		uint32_t dcache_invalidate_word = probeCoherencyInvalidateRequest(ms->cpu_id,0);
		if(dcache_invalidate_word != 0)
		{
			uint32_t invalidate_va = (dcache_invalidate_word & 0x7fffffff);
			invalidateCacheLine(dcache, invalidate_va);
		}
		else
			break;
	}

	//the main loop ..runs forever:
	*mae=0;
	*read_data = 0;
	uint8_t	cacheable=0;
	uint8_t acc = 0;
	uint32_t mmu_fsr = 0;
	
	//clear the top-bit (thread-head bit) in asi.
	asi =asi&0x7F;

	// lock flag is the 6th bit.
	uint8_t lock_mask    = (request_type & 0x40);
	if(lock_mask != 0)
		dcache->number_of_locked_accesses++;	
	

	// the top bit is the new thread bit, which is ignored.
	// in new C ref model for 64-bit, bit 7 should be 0
	request_type = request_type & 0x3f;

#ifdef DEBUG
	fprintf(stderr,"\n\nDCACHE :  read CPU request asi=0x%x, addr=0x%x, req_type=0x%x, byte_mask=0x%x, data=0x%lx\n",asi,addr,request_type,byte_mask,write_data);
#endif

	//if this is a CCU request (made by the debugger),
	//translate this into a normal request.
	if(request_type==REQUEST_TYPE_CCU_CACHE_READ) 
	{
		request_type = REQUEST_TYPE_READ;
	}
	if(request_type==REQUEST_TYPE_CCU_CACHE_WRITE)
	{
		request_type = REQUEST_TYPE_WRITE;
	}

	uint8_t is_stbar, is_nop, is_flush,is_cached_mem_access,is_read, is_mmu_access, is_mmu_bypass;
	decodeDcacheRequest(asi, request_type,
				&is_nop, &is_stbar, &is_flush, &is_read,
				&is_cached_mem_access, &is_mmu_access, &is_mmu_bypass);
	dcache->number_of_accesses++;
	if(is_flush)
	{
		// In principle, we could communicate the
		// flush to the MMU so that it can clear the RLUT.
		// If we do not do this, there will be some spurious
		// invalidates from the RLUT to the caches.. 
		dcache->number_of_flushes++;

		// flush and forget about it.
		flushCache(dcache);
		#ifdef DEBUG
		fprintf(stderr, "Info: DCACHE-%d flushed by flush-asi 0x%x\n", dcache->cpu_id, asi);
		#endif
	}
	else if (!is_stbar && !is_nop)
	{
		uint8_t is_hit  = 0;
		if(is_cached_mem_access)
		{

			uint8_t is_raw_hit = 0;
			lookupCache(dcache,
					addr, asi, &is_raw_hit,  &acc);
			int access_ok = accessPermissionsOk(request_type, asi, acc);

			is_hit = is_raw_hit &&
					(lock_mask == 0) &&  // note: locked access must go to 
								// next level of mem hierarchy.
					access_ok;

			if(is_hit)
			{
				dcache->number_of_hits++;
				if(is_read)
					dcache->number_of_read_hits++;
				else
					dcache->number_of_write_hits++;
			}
			else
			{
				dcache->number_of_misses++;
				if(is_read)
					dcache->number_of_read_misses++;
				else
					dcache->number_of_write_misses++;
			}
		}
		else if(ASI_MMU_ACCESS(asi))
		// induced flush.
		{
			dcache->number_of_flushes++;
			flushCache(dcache);
			#ifdef DEBUG
			fprintf(stderr,"Info: DCACHE-%d flushed by ASI-MMU-ACCESS, asi 0x%x\n", dcache->cpu_id, asi);
			#endif
		}
		else
		{
			dcache->number_of_bypasses++;
		}

		int is_cacheable_based_on_mmu_status = isCacheableRequestBasedOnMmuStatus (dcache);
		
		uint8_t do_mmu_read_dword  = 
				(is_read && (is_mmu_access  || is_mmu_bypass || 
							(lock_mask != 0) || 
							!is_cacheable_based_on_mmu_status));
		uint8_t do_mmu_write_dword = 
				!is_read && (is_cached_mem_access || is_mmu_access || is_mmu_bypass
							|| !is_cacheable_based_on_mmu_status);

		uint8_t do_mmu_fetch_line = (is_cached_mem_access && !is_hit && (lock_mask == 0) &&
							is_cacheable_based_on_mmu_status);

		if(is_read && is_hit)
		{	
			*read_data = getDwordFromCache	(dcache,addr);
		}

		if(!is_read && is_hit)
		{
			writeIntoLine (dcache, write_data, addr, byte_mask);
		}

		uint32_t synonym_invalidation_word = 0;

		//forward the first request to MMU
		if(do_mmu_read_dword || do_mmu_write_dword)
		{
			uint8_t mmu_dword_command = 
				((request_type == REQUEST_TYPE_WRFSRFAR) ? MMU_WRITE_FSR :
					(do_mmu_read_dword ? MMU_READ_DWORD : 
				 		(is_hit ? MMU_WRITE_DWORD_NO_RESPONSE : MMU_WRITE_DWORD)));

			Mmu(ms, mmu_dword_command, (request_type | lock_mask),
					asi,  addr,  byte_mask, write_data,
					mae, &cacheable, &acc, read_data, &mmu_fsr, &synonym_invalidation_word);
		}
		uint8_t first_is_not_cacheable =
			(do_mmu_read_dword || do_mmu_write_dword) && !cacheable;
		// fetch the line from the mmu
		if(!(*mae) && !first_is_not_cacheable && do_mmu_fetch_line)
		{
			uint32_t line_addr = (addr & LINE_ADDR_MASK);
			uint64_t line_data[8];

			Mmu(ms, MMU_READ_LINE, request_type, asi, addr, byte_mask, write_data,
					mae, &cacheable, &acc, (uint64_t*) line_data, &mmu_fsr, 
						&synonym_invalidation_word);

			if(synonym_invalidation_word != 0)
			{
				uint32_t invalidate_va = (synonym_invalidation_word & 0x7fffffff);
				invalidateCacheLine(dcache, invalidate_va);
			}

			if(cacheable)
			{
				updateCacheLine (dcache, acc, line_addr, line_data);
				*read_data = getDwordFromCache (dcache, addr);
			}
			else
			{
				*read_data = line_data[cacheLineOffset(addr)];
			}
		}
	}

	if(asi == 0x4) // mmu control register update?
	{
		if(request_type == REQUEST_TYPE_WRITE)
		{
			updateMmuState(dcache, byte_mask, addr, write_data);
		}
	}

#ifdef DEBUG
	fprintf(stderr,"\nDCACHE :  response to CPU mae=0x%x, data=0x%lx\n",*mae,*read_data);
#endif
	unlock_cache(dcache);
}

	
