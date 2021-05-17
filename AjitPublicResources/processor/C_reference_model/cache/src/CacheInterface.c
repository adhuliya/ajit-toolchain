//CacheInterface.c
//
//CPU-side and memory side interface 
//of the Dcache and Icache
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
#include "Ancillary.h"




//mutex for locking the 
//request pipe from caches to MMU
//so that only one cache can
//send a request at a time
pthread_mutex_t mutex_mmu_request_lock = PTHREAD_MUTEX_INITIALIZER;


 
//cpu to Dcache
void readCpuToDcacheRequest(uint8_t* asi, uint32_t* addr, uint8_t* request_type,uint8_t* byte_mask, uint64_t* data)
{
	*asi		= read_uint8 ("CPU_to_DCACHE_asi");
	*addr		= read_uint32("CPU_to_DCACHE_addr");
	*request_type 	= read_uint8 ("CPU_to_DCACHE_request_type");
	*byte_mask	= read_uint8 ("CPU_to_DCACHE_byte_mask");
	*data		= read_uint64("CPU_to_DCACHE_data");
	#ifdef DEBUG
	fprintf(stderr,"\n\nDCACHE :  read CPU request asi=0x%x, addr=0x%x, req_type=0x%x, byte_mask=0x%x, data=0x%lx\n",*asi,*addr,*request_type,*byte_mask,*data);
	#endif
}

//Dcache to cpu
void sendDcacheToCpuResponse(uint8_t mae, uint64_t data)
{

	write_uint8 ("DCACHE_to_CPU_mae", mae);
	write_uint64("DCACHE_to_CPU_data",data);
	#ifdef DEBUG
	fprintf(stderr,"\nDCACHE :  sent response to CPU mae=0x%x, data=0x%lx\n",mae,data);
	#endif

}

//cpu to Icache
void readCpuToIcacheRequest(uint8_t* asi, uint32_t* addr)
{
	*asi		= read_uint8 ("CPU_to_ICACHE_asi");
	*addr		= read_uint32("CPU_to_ICACHE_addr");
	#ifdef DEBUG
	printf("\nICACHE: read CPU request asi=0x%x, addr=0x%x",*asi,*addr);
	#endif
}


//Icache to cpu
void sendIcacheToCpuResponse(uint8_t mae, uint32_t addr, uint64_t instr_pair, uint32_t mmu_fsr)
{
	write_uint8 ("ICACHE_to_CPU_mae", mae);
	write_uint64("ICACHE_to_CPU_instr_pair",instr_pair);
	write_uint32("ICACHE_to_CPU_fsr",mmu_fsr);
	#ifdef DEBUG
	printf("\nICACHE: sent response to CPU mae=0x%x, addr=0x%x, instr_pair=0x%lx, mmu_fsr =0x%x",mae, addr, instr_pair, mmu_fsr);
	#endif
	if(mae)
		printf("\nICACHE: trapped: mae=0x%x, addr=0x%x, instr_pair=0x%lx, mmu_fsr =0x%x", mae, addr, instr_pair, mmu_fsr);
	

}


//Blocking write to MMU request pipes
//Locking ensures that only one thread 
//can write at a time
void sendCacheToMmuRequest(uint8_t asi, uint32_t addr, uint8_t request_type, uint8_t byte_mask, uint64_t data)
{
	//obtain lock
	pthread_mutex_lock(&mutex_mmu_request_lock);
	
	//write to the MMU request pipes
	write_uint8 ("CACHE_to_MMU_asi"	,asi);
	write_uint32("CACHE_to_MMU_addr",addr);
	write_uint8 ("CACHE_to_MMU_request_type",request_type);
	write_uint8 ("CACHE_to_MMU_byte_mask", byte_mask);
	write_uint64("CACHE_to_MMU_data",data);
	
	//unlock
	pthread_mutex_unlock(&mutex_mmu_request_lock);
	#ifdef DEBUG
	printf("\nCACHE :  sent request to MMU asi=0x%x, addr=0x%x, req_type=0x%x, byte_mask=0x%x, data=0x%lx",asi,addr,request_type,byte_mask,data);
	#endif

}


//Dcache to MMU
void sendDcacheToMmuRequest(uint8_t asi, uint32_t addr,	uint8_t request_type, uint8_t byte_mask, uint64_t data)
{
	
	//set bit 7 of request_type to indicate that
	//this request is going from the Dcache.
	request_type = setBit8(request_type,7,DCACHE_TYPE);
	sendCacheToMmuRequest(asi, addr, request_type, byte_mask,data);

	#ifdef DEBUG
	printf("\nDCACHE :  sent request to MMU asi=0x%x, addr=0x%x, req_type=%x, byte_mask=0x%x, data=0x%lx",asi,addr,request_type,byte_mask,data);
	#endif
}

//Icache to MMU
void sendIcacheToMmuRequest(uint8_t asi, uint32_t addr)
{
	uint8_t request_type = REQUEST_TYPE_IFETCH;
	uint8_t byte_mask    = 0;
	uint64_t data        =0;
	
	//set bit 7 of request_type to indicate that
	//this request is going from the Icache
	request_type= setBit8(request_type,7,ICACHE_TYPE);
	sendCacheToMmuRequest(asi, addr, request_type, byte_mask,data);

	#ifdef DEBUG
	printf("\nICACHE: sent request to MMU asi=0x%x, addr=0x%x, req_type=%x, byte_mask=0x%x, data=0x%lx",asi,addr,request_type,byte_mask,data);
	#endif
}

//MMU to Dcache
void readMmuToDcacheResponse(uint8_t* mae, uint64_t* data, uint8_t* cacheable)
{
	*mae		= read_uint8 ("MMU_to_DCACHE_mae");
	*data		= read_uint64("MMU_to_DCACHE_data");
	*cacheable	= read_uint8 ("MMU_to_DCACHE_cacheable");
#ifdef DEBUG
	printf("\nDCACHE :  read response from MMU mae=0x%x, cacheable=0x%x, data=0x%lx",*mae,*cacheable,*data);
#endif
}

//MMU to Icache
void readMmuToIcacheResponse(uint8_t* mae, uint64_t* data, uint8_t* cacheable, uint32_t* fsr_val)
{
	*mae		= read_uint8 ("MMU_to_ICACHE_mae");
	*data		= read_uint64("MMU_to_ICACHE_data");
	*cacheable	= read_uint8 ("MMU_to_ICACHE_cacheable");
	*fsr_val	= read_uint32("MMU_to_ICACHE_fsr");
#ifdef DEBUG
	printf("\nICACHE: read response from MMU mae=0x%x, cacheable=0x%x, data=0x%lx, fsr=0x%lx",*mae,*cacheable,*data, *fsr_val);
#endif

}


