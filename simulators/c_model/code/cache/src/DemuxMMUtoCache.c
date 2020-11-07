//DemuxMMUtoCaches.c
//
//This thread demuxes 
//messages coming from the MMU
//and sends them to the 
//ICACHE or DCACHE
//depending on value of bit 7 in mae
//AUTHOR: Neha Karanjkar

#include <stdlib.h>
#include <stdint.h>
#include "RequestTypeValues.h"
#include "CacheInterface.h"
#include "Ancillary.h"
void DemuxMMUtoCaches()
{
	uint8_t mae;
	uint64_t data;
	uint8_t cacheable;
	uint8_t destination;
	uint32_t mmu_fsr;

	while(1)
	{
		//read response from the MMU-side
		mae		= read_uint8 ("MMU_to_CACHE_mae");
		data		= read_uint64("MMU_to_CACHE_data");
		cacheable	= read_uint8 ("MMU_to_CACHE_cacheable");
		mmu_fsr		= read_uint32("MMU_to_CACHE_fsr");
		
		//read bit 7 of mae
		destination = getBit8(mae,7);
		
		//reset bit 7
		mae= setBit8(mae,7,0);
		
		if(mae & 0x7f) 
			fprintf(stderr,"DemuxMMUtoCaches: mae = %x -> %x.\n", mae, (mae & 0x7f));

		//route the message to ICACHE or DCACHE
		if(destination==ICACHE_TYPE)
		{
			//send to ICACHE
			write_uint8 ("MMU_to_ICACHE_mae", mae);
			write_uint64("MMU_to_ICACHE_data", data);
			write_uint8 ("MMU_to_ICACHE_cacheable",cacheable);
			write_uint32("MMU_to_ICACHE_fsr",mmu_fsr);
		}
		else
		{
			//send to DCACHE
			write_uint8 ("MMU_to_DCACHE_mae", mae);
			write_uint64("MMU_to_DCACHE_data", data);
			write_uint8 ("MMU_to_DCACHE_cacheable",cacheable);
		}
	}
}


