//CacheInterface.h
//
//CPU-side and memory side interface 
//of the Dcache and Icache
//AUTHOR: Neha Karanjkar


#ifndef _CACHE_INTERFACE_H
#define _CACHE_INTERFACE_H

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"

#define ICACHE_TYPE 0
#define DCACHE_TYPE 1




 
//cpu to Dcache
void readCpuToDcacheRequest(uint8_t* asi, uint32_t* addr, uint8_t* request_type,uint8_t* byte_mask, uint64_t* data);

//Dcache to cpu
void sendDcacheToCpuResponse(uint8_t mae, uint64_t data);

//cpu to Icache
void readCpuToIcacheRequest(uint8_t* asi, uint32_t* addr);


//Icache to cpu
void sendIcacheToCpuResponse(uint8_t mae,  uint32_t addr, uint64_t instr_pair, uint32_t mmu_fsr);


//Blocking write to MMU request pipes
//Locking ensures that only one thread 
//can write at a time
void sendCacheToMmuRequest(uint8_t asi, uint32_t addr, uint8_t request_type, uint8_t byte_mask, uint64_t data);


//Dcache to MMU
void sendDcacheToMmuRequest(uint8_t asi, uint32_t addr,	uint8_t request_type, uint8_t byte_mask, uint64_t data);

//Icache to MMU
void sendIcacheToMmuRequest(uint8_t asi, uint32_t addr);

//MMU to Dcache
void readMmuToDcacheResponse(uint8_t* mae, uint64_t* data, uint8_t* cacheable);

//MMU to Icache
void readMmuToIcacheResponse(uint8_t* mae, uint64_t* data, uint8_t* cacheable, uint32_t* mmu_fsr);

//The following function
//becomes a thread. It demuxes
//messages coming from the MMU
//and sends them to the 
//ICACHE or DCACHE
//depending on value of bit 7 in mae
void demuxMMUResponse();
#endif
