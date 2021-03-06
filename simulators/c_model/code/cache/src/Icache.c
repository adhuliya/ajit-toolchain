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

int icache_forward_to_mmu(asi)
{
	if(ASI_MMU_ACCESS(asi)
	|| ASI_USER_OR_SUPV_ACCESS(asi)
	|| ASI_MMU_PASS_THROUGH(asi)
	 )
		return 1;
	else
		return 0;
}


void cpuIcacheAccess (MmuState* ms,
				WriteThroughAllocateCache* icache,
				uint8_t asi, uint32_t addr, uint8_t request_type, uint8_t byte_mask,
				uint8_t* mae, uint64_t* instr_pair, uint32_t* mmu_fsr)
{
	lock_cache (icache);

#ifdef DEBUG
	fprintf(stderr,"\n\nICACHE :  read CPU request asi=0x%x, addr=0x%x, req_type=0x%x, byte_mask=0x%x\n",asi,addr,request_type,byte_mask);
#endif
	

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
	decodeIcacheRequest (asi, request_type, &is_nop, &is_flush, &is_ifetch);
	icache->number_of_accesses++;
	if(is_flush)
	{
		icache->number_of_flushes++;
		flushCache(icache);
	}
	else if (is_ifetch)
	{
		uint8_t is_hit  = 0;
		uint8_t is_raw_hit = 0;
		lookupCache(icache,
				addr, asi, &is_raw_hit,  &acc);
		int access_ok = accessPermissionsOk(request_type, asi, acc);
		is_hit = is_raw_hit && access_ok;

		if(is_hit)
		{	
			icache->number_of_hits++;
			*instr_pair = getDwordFromCache	(icache,addr);
		}
		else
		{
			icache->number_of_misses++;
			uint32_t line_addr = (addr & LINE_ADDR_MASK);
			uint64_t line_data[8];

			Mmu(ms, MMU_READ_LINE, REQUEST_TYPE_IFETCH, 
					asi, addr, byte_mask, 0x0,
					mae, &cacheable, &acc, (uint64_t*) line_data, mmu_fsr);

			if(cacheable)
			{
				updateCacheLine (icache, acc, line_addr, line_data);
				*instr_pair = getDwordFromCache (icache, addr);
			}
			else
			{
				*instr_pair = line_data[cacheLineOffset(addr)];
			}
		}
	}

	unlock_cache(icache);
#ifdef DEBUG
	fprintf(stderr,"\nICACHE :  response to CPU mae=0x%x, instr-pair=0x%lx, mmu-fsr=0x%x\n",
				*mae,*instr_pair, *mmu_fsr);
#endif

}


void icacheInvalidate_core (WriteThroughAllocateCache* icache)
{
	while(1)
	{
		uint32_t va_line_address = read_uint32(icache->from_rlut_pipe_name);

		lock_cache(icache);

		invalidateCacheLine(icache, va_line_address);
		
		unlock_cache(icache);
		
	}
}
	


