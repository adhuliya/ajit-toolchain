// DummyIcacheBehavior.c
//
//Dummy Icache Behavior
//Simply forwards requests from CPU to MMU
//and forwards MMU side messages to CPU
// AUTHOR: Neha Karanjkar


#include <stdlib.h>
#include <stdint.h>
#include "CacheInterface.h"
#include "Ancillary.h"
#include "ASI_values.h"
#include "RequestTypeValues.h"
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



//Dummy Icache Behavior
//Simply forwards the request to MMU
//and forwards MMU response to CPU
void DummyIcache()
{
	//temporary variables:
	uint8_t asi;
	uint32_t addr;
	uint64_t data;
	uint8_t  mae;
	uint8_t cacheable;
	uint32_t mmu_fsr;
	
	//the main loop ..runs forever:
	while(1)
	{
		//reset temporary variables
		asi=0;
		addr=0;
		data=0;
		mae=0;
		cacheable=0;
		
		
		
		//wait for a request from cpu-side
		readCpuToIcacheRequest(&asi, &addr);
		
		//clear the top  bit (thread-head bit) in asi.
		asi=asi&0x7F;

		if(icache_forward_to_mmu(asi))
		{	
			//forward the request to MMU
			sendIcacheToMmuRequest(asi,addr);
			//wait for a response from MMU
			readMmuToIcacheResponse(&mae, &data, &cacheable, &mmu_fsr);
		}
		else
		{
			data=0;
			mae=0;
			mmu_fsr=0;
		}
		//send the response back to cpu
		sendIcacheToCpuResponse(mae, addr, data, mmu_fsr);
	}
}

