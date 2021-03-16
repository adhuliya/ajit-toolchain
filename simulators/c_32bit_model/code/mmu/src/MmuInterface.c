//MmuInterface.c
//AUTHOR: Neha Karanjkar



#ifdef SW
	#include <stdio.h>
#endif

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "RequestTypeValues.h"
#include "CacheInterface.h"
#include "MmuInterface.h"
#include "Ancillary.h"


void readCacheToMmuRequest(uint8_t *asi, uint32_t *addr, uint8_t *request_type, uint8_t* byte_mask, uint64_t *data, uint8_t*source)
{
	
	*asi		= read_uint8 ("CACHE_to_MMU_asi");
	*addr		= read_uint32("CACHE_to_MMU_addr");
	*request_type 	= read_uint8 ("CACHE_to_MMU_request_type");
	*byte_mask	= read_uint8 ("CACHE_to_MMU_byte_mask");
	*data		= read_uint64("CACHE_to_MMU_data");

	//read bit 7 of request type to determine if the
	//source of teh request was Dcache or Icache.
	*source 	= getBit8(*request_type,7);
	//reset bit 7 of request type
	*request_type	= setBit8(*request_type,7,0);


	#ifdef DEBUG
	if(*source==DCACHE_TYPE)
		printf("\nMMU :  read DCACHE request asi=0x%x, addr=0x%x, req_type=%d, byte_mask=0x%d, data=0x%lx",*asi,*addr,*request_type,*byte_mask,*data);
	else
		printf("\nMMU :  read ICACHE request asi=0x%x, addr=0x%x, req_type=%d, byte_mask=0x%d, data=0x%lx",*asi,*addr,*request_type,*byte_mask,*data);
	#endif
}



void sendMmuToCacheResponse(uint8_t mae, uint32_t addr, uint64_t data, uint8_t cacheable, uint8_t destination, 
					uint32_t fsr_to_cache)
{
	mae= setBit8(mae,7,destination);

	write_uint8 ("MMU_to_CACHE_mae", mae);
	write_uint64("MMU_to_CACHE_data",data);
	write_uint8 ("MMU_to_CACHE_cacheable",cacheable);
	write_uint32 ("MMU_to_CACHE_fsr",((destination == DCACHE_TYPE) ? 0 : fsr_to_cache));
	
	if(destination==DCACHE_TYPE)
	{
	#ifdef DEBUG
		printf("\nMMU :  sent response to DCACHE mae=0x%x (addr=0x%x),  data=0x%lx, cacheable=0x%x",mae,addr, data,cacheable);
	#endif
		if((mae & 0x7f) != 0)
			printf("\nMMU :mae:  sent response to DCACHE mae=0x%x, addr=0x%x, data=0x%lx, cacheable=0x%x",mae,addr, data,cacheable);
	}
	else
	{
	#ifdef DEBUG
		printf("\nMMU :  sent response to ICACHE mae=0x%x, addr=0x%x,  data=0x%lx, cacheable=0x%x, fsr=0x%x",
					mae, addr, data,cacheable, fsr_to_cache);
	#else 
		if((mae & 0x7f) != 0)
			printf("\nMMU :mae:   sent response to ICACHE mae=0x%x, addr=0x%x, data=0x%lx, cacheable=0x%x, fsr=0x%x",
					mae,addr, data,cacheable, fsr_to_cache);
	#endif
	}

}


void sendMmuToMemoryRequest(uint8_t request_type, uint64_t addr, uint64_t data,	uint8_t byte_mask)
{
	write_uint8 ("AJIT_to_ENV_request_type",request_type);
	write_uint64("AJIT_to_ENV_addr",addr);
	write_uint64("AJIT_to_ENV_data",data);
	write_uint8 ("AJIT_to_ENV_byte_mask", byte_mask);
	
	#ifdef DEBUG
	printf("\nMMU :  sent request to System Bus request_type=0x%x, addr=0x%lx, data=0x%lx, byte_mask=0x%x",request_type, addr, data, byte_mask);
	#endif

}

void readMemoryToMmuResponse(uint64_t* data)
{
	*data		= read_uint64("ENV_to_AJIT_data");
	#ifdef DEBUG
	printf("\nMMU :  read Response from System Bus : data = 0x%lx",*data);
	#endif

}


