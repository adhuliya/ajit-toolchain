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
#include "Mmu.h"
#include "MmuInterface.h"
#include "Ancillary.h"


void register_mmu_pipes (MmuState* ms)
{
	int depth = 2;

 	// 36 bits are used for addr, but in C we have to go to 64
        register_pipe(ms->req_pipe, depth, 8,     0);
        register_pipe(ms->addr_pipe,         depth, 64,    0);
        register_pipe(ms->wdata_pipe,         depth, 64,    0);
        register_pipe(ms->byte_mask_pipe,    depth, 8,     0);

        register_pipe(ms->rdata_pipe,         depth, 64,    0);
}

void sendMmuToMemoryRequest(MmuState* ms,
				uint8_t request_type, 
				uint64_t addr, uint64_t data,	uint8_t byte_mask)
{
	write_uint8 (ms->req_pipe,request_type);
	write_uint64(ms->addr_pipe,addr);
	write_uint64(ms->wdata_pipe,data);
	write_uint8 (ms->byte_mask_pipe, byte_mask);
	
	#ifdef DEBUG
	printf("\nMMU :  sent request to System Bus request_type=0x%x, addr=0x%lx, data=0x%lx, byte_mask=0x%x",request_type, addr, data, byte_mask);
	#endif

}

void readMemoryToMmuResponse(MmuState* ms, uint64_t* data)
{
	*data		= read_uint64(ms->rdata_pipe);
	#ifdef DEBUG
	printf("\nMMU :  read Response from System Bus : data = 0x%lx",*data);
	#endif

}


