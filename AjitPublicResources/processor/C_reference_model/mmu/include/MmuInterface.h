//MmuInterface.h
//AUTHOR: Neha Karanjkar
//
#ifndef _MMU_INTERFACE_H_
#define _MMU_INTERFACE_H_

#include <stdlib.h>
#include <stdint.h>


void readCacheToMmuRequest(uint8_t *asi, uint32_t *addr, uint8_t *request_type, uint8_t* byte_mask, uint64_t *data, uint8_t* source);
void sendMmuToCacheResponse(uint8_t mae, uint32_t addr, uint64_t data, uint8_t cacheable, uint8_t destination, uint32_t fsr_to_cache);
void sendMmuToMemoryRequest(uint8_t request_type, uint64_t addr, uint64_t data,	uint8_t byte_mask);
void readMemoryToMmuResponse(uint64_t* data);


#endif
