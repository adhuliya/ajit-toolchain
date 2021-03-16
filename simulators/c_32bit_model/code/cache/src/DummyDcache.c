// DummyDcacheBehavior.c
//
//Dummy Dcache Behavior
//Simply forwards requests from CPU to MMU
//and forwards MMU side messages to CPU
// AUTHOR: Neha Karanjkar


#include <stdlib.h>
#include <stdint.h>
#include "CacheInterface.h"
#include "Ancillary.h"
#include "ASI_values.h"
#include "RequestTypeValues.h"

int dcache_forward_to_mmu(asi,request_type)
{
	if((request_type==REQUEST_TYPE_STBAR) 
	 || (request_type==REQUEST_TYPE_NOP))
		return 0;
	else if(request_type ==REQUEST_TYPE_WRFSRFAR)
	{
		return 1;
	}
	else
	{
		//ifetch/read/write
		if(ASI_MMU_ACCESS(asi)
		|| ASI_USER_OR_SUPV_ACCESS(asi)
		|| ASI_MMU_PASS_THROUGH(asi)
		)
			return 1;
		else
			return 0;
	}
}

//Dummy Dcache Behavior
//Simply forwards the request to MMU
//and forwards MMU response to CPU
void DummyDcache()
{
	//temporary variables:
	uint8_t asi;
	uint32_t addr;
	uint8_t request_type;
	uint8_t byte_mask;
	uint64_t data;
	uint8_t  mae;
	uint8_t cacheable;
	
	//the main loop ..runs forever:
	while(1)
	{
		//reset temporary variables
		asi=0;
		addr=0;
		request_type=0;
		byte_mask=0;
		data=0;
		mae=0;
		cacheable=0;
		
		
		//wait for a request from cpu-side
		readCpuToDcacheRequest(&asi, &addr, &request_type, &byte_mask, &data);

		//clear the top-bit (thread-head bit) in asi.
		asi =asi&0x7F;

		//if this is a CCU request (made by the debugger),
		//translate this into a normal mmu-bypass request.
		if(request_type==REQUEST_TYPE_CCU_CACHE_READ) {request_type = REQUEST_TYPE_READ;}
		if(request_type==REQUEST_TYPE_CCU_CACHE_WRITE){request_type = REQUEST_TYPE_WRITE;}

		if(dcache_forward_to_mmu(asi,request_type))
		{
			//forward the request to MMU
			sendDcacheToMmuRequest(asi,addr,request_type,byte_mask,data);
			//wait for a response from MMU
			readMmuToDcacheResponse(&mae, &data, &cacheable);
		}
		else 
		{
			data=0;
			mae=0;
		}

		//send the response back to cpu
		sendDcacheToCpuResponse(mae,data);
	}
}

