//MmuInterface.h
//AUTHOR: Neha Karanjkar, Madhav Desai
//
#ifndef _MMU_INTERFACE_H_
#define _MMU_INTERFACE_H_

#include <stdlib.h>
#include <stdint.h>
#include "Mmu.h"

void sendMmuToMemoryRequest(MmuState* ms, uint8_t request_type, uint64_t addr, uint64_t data,	uint8_t byte_mask);
void readMemoryToMmuResponse(MmuState* ms, uint64_t* data);

#endif
