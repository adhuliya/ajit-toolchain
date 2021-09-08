#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "Ajit_Hardware_Configuration.h"
#include "Ancillary.h"
#include "RequestTypeValues.h"
#include "Serial.h"
#include "Timer.h"
#include "InterruptController.h"
#include "bridge.h"
#include "memory.h"
#include "tlbs.h"
#include "rlut.h"
				


MUTEX_DECL(peripheral_mutex);
MUTEX_DECL(memory_mutex)
MUTEX_DECL(lock_mutex)

#define __GET_PERIPHERAL_LOCK__ 	MUTEX_LOCK(peripheral_mutex)
#define __RELEASE_PERIPHERAL_LOCK__ 		MUTEX_UNLOCK(peripheral_mutex)

#define __GET_MEMORY_LOCK__ 		MUTEX_LOCK(memory_mutex)
#define __RELEASE_MEMORY_LOCK__ 	MUTEX_UNLOCK(memory_mutex)

int NCORES = 0;
uint8_t global_lock_flag = 0;
int global_lock_owner_core = 0;

extern int global_verbose_flag;

setAssociativeMemory** snoop_filters = NULL;


void bridgeSetNcores(uint32_t ncores)
{
	NCORES = ncores;
	int I;
	snoop_filters = (setAssociativeMemory**) malloc(ncores*sizeof(setAssociativeMemory*));
	for(I = 0; I < ncores; I++)
	{
		// fully associative
		snoop_filters[I] = 
			findOrAllocateSetAssociativeMemory 
					(I + 1000,  // give it a unique id different from the mmu tlbs.
						30,
						1,
						SNOOP_FILTER_CACHE_LOG_MEM_SIZE,
						SNOOP_FILTER_CACHE_LOG_MEM_SIZE);
						
	}
}

//
// To reduce redundant invalidates, we can remember the last (address,value,byte_mask) triples
// which were updated into memory from each CPU.  If the state of the memory can be proven
// to be unchanged by the current write, there is no need to generate an invalidate
// message... This needs to be thought about further..
//
// For the moment we remember the a set of invalidated address for each cpu. If that cpu
// has done no cache line fetches between the last invalidation and the current write
// is to an invalidated line, in this set then there is no need to generate an invalidate..
//
// return 1 if there was a hit on lookup.
int updateAndLookupSnoopFilterCache (int core_id,
					uint8_t erase,
					uint8_t lookup,
					uint8_t write,
					uint32_t physical_addr_of_line)
{
	uint8_t lookup_valid = 0;
	uint64_t lookup_data = 0;
	operateOnSetAssociativeMemory(snoop_filters[core_id], 1,
                                        0,
                                        erase, 
                                        write,
                                        1, physical_addr_of_line, 0,
					lookup,  physical_addr_of_line, 0,
					&lookup_valid, &lookup_data);
	int ret_val = lookup && lookup_valid;
	return(ret_val);
}

int testAndSetGlobalLock (uint8_t l, int core_id)
{
	int ret_val = 0;
	MUTEX_LOCK(lock_mutex);
	if((global_lock_flag == 0) || (core_id == global_lock_owner_core))
	{
		ret_val = 1;
		if(l==1)		
		{
#ifdef DEBUG
			fprintf(stderr,"\nGLOCK=1, CPU-ID=%d\n",core_id);
#endif
			global_lock_flag = 1;
			global_lock_owner_core = core_id;
		}
	}
	MUTEX_UNLOCK(lock_mutex);
	return(ret_val);
}

int clearGlobalLock (uint8_t l, int core_id)
{
	MUTEX_LOCK(lock_mutex);
	if(core_id == global_lock_owner_core)
	{
		if((l == 0) && global_lock_flag)
		{
#ifdef DEBUG
			fprintf(stderr,"\nGLOCK=0, CPU-ID=%d\n",core_id);
#endif
			global_lock_flag = 0;
		}
	}
	MUTEX_UNLOCK(lock_mutex);
	return(0);
}



void register_bridge_pipes (int number_of_cpus)
{
	// no longer needed.
}

// return 1 if OK, 0 if not OK.
int sysMemBusRequest (int core_id,
				uint8_t request_type,
				uint8_t byte_mask,
				uint32_t addr,
				uint64_t data64,
				uint64_t *rdata)
{

	// get the lock bit.
	uint8_t set_mem_access_lock = ((request_type & SET_LOCK_FLAG) != 0);

	// acquire and set lock for atomic operations.	
	if (!testAndSetGlobalLock(set_mem_access_lock, core_id))
		return(0);

#ifdef DEBUG
	fprintf(stderr,"\nMEMORY ACCESS from CPU %d :  received request from MMU  addr=0x%x, req_type=%d, byte_mask=0x%d, data=0x%lx",core_id, addr,request_type,byte_mask,data64);
#endif


	// clear the top 2 bits of the request since they
	// are not used.
	request_type     = request_type & 0x3f;
	memDescriptorList* mdl = lookupMem(addr);
	if(mdl != NULL)
	{

		// DCACHE request.
		__GET_MEMORY_LOCK__;

		if( (request_type==REQUEST_TYPE_IFETCH)
				|| (request_type==REQUEST_TYPE_READ)) 
		{

			if(request_type == REQUEST_TYPE_READ)
			{
				//
				// if the cpu accesses the main memory, invalidate
				// the last-line-address buffer.
				//
				uint32_t line_addr = (addr >> LOG_BYTES_PER_CACHE_LINE);
				updateAndLookupSnoopFilterCache(core_id, 1,0,0, line_addr);
			}

			*rdata = getDoubleWordInMemory(addr);

			if(global_verbose_flag) {
				fprintf(stderr,"0x%" PRIx64 " = MEM[0x%x] CPU=%d lock=%d\n", data64, addr, core_id, global_lock_flag);
			}

		}
		else if(request_type == REQUEST_TYPE_WRITE)
		{
			setDoubleWordInMemory(addr, data64, byte_mask);

			//send back the written doubleword so that
			//a copy can be maintained in 
			//our write-allocate cache if necessary
			*rdata = getDoubleWordInMemory(addr);

			if(global_verbose_flag) {
				fprintf(stderr,"MEM[0x%x] = 0x%" PRIx64 " bmask=0x%x CPU=%d lock=%d\n", addr,data64,byte_mask, core_id, global_lock_flag);
			}

			uint32_t line_addr = (addr >> LOG_BYTES_PER_CACHE_LINE);
			int COREID;

			for (COREID= 0;  COREID< NCORES; COREID++)
			{
				if(COREID!= core_id)
				{
					int lookup_hit = 
						updateAndLookupSnoopFilterCache(core_id, 0, 1, 1, line_addr);

					if(!lookup_hit)
					{
						uint32_t icache_inval_dat =
							lookupRlutInManager(COREID,line_addr,1);
						if(icache_inval_dat != 0)
							write_uint32(getCacheInvalPipeName(COREID,1),
									icache_inval_dat);

						uint32_t dcache_inval_dat =
							lookupRlutInManager(COREID,line_addr,0);
						if(dcache_inval_dat != 0)
							write_uint32(getCacheInvalPipeName(COREID,0),
									dcache_inval_dat);
					}
				}
			}

		}
		else
		{
			//this is an invalid request
			fprintf(stderr,"\nWarning: invalid request type %d to memoryAccess thread",request_type);
		}

		if(global_verbose_flag)
			fprintf(stderr,"\nInfo: core=%d executed memory access rwbar=%d, addr=0x%lx, byte_mask=0x%x, wdata=0x%llx, rdata=0x%llx\n", core_id, (request_type != REQUEST_TYPE_WRITE), addr, byte_mask, data64, *rdata);


		__RELEASE_MEMORY_LOCK__;

	}
	else 
	{
		peripheralDescriptorList* pdl = lookupPeripheral(addr); 	
		if(pdl != NULL)
		{
			__GET_PERIPHERAL_LOCK__

				uint8_t rwbar = (request_type == REQUEST_TYPE_READ);
			*rdata = executePeripheralAccess(pdl, rwbar, addr, byte_mask, data64);
			if(global_verbose_flag)
				fprintf(stderr,"\nInfo: core=%d executed peripheral access rwbar=%d, addr=0x%lx, byte_mask=0x%x, wdata=0x%llx, rdata=0x%llx\n", core_id, rwbar, addr, byte_mask, data64, *rdata);

			__RELEASE_PERIPHERAL_LOCK__

		}
		else
		{
			fprintf(stderr,"\nWarning: unmapped address 0x%x at bridge.\n",addr);
		}
	}


	// clear lock for atomic operations
	if(request_type!=REQUEST_TYPE_IFETCH)
		clearGlobalLock(set_mem_access_lock, core_id);

#ifdef DEBUG
	fprintf(stderr,"\nbridge: Memory access response=0x%" PRIx64 "\n", data64);
#endif
	return(1);
}


