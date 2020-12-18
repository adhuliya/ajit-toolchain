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
				
char *biu_to_rlut_pipe_names[] = {"BIU_to_RLUT_0", "BIU_to_RLUT_1", "BIU_to_RLUT_2", "BIU_to_RLUT_3"};

DEFINE_THREAD(bridge_cpu_0)
DEFINE_THREAD(bridge_cpu_1)
DEFINE_THREAD(bridge_cpu_2)
DEFINE_THREAD(bridge_cpu_3)


MUTEX_DECL(peripheral_mutex);
MUTEX_DECL(memory_mutex)
MUTEX_DECL(lock_mutex)

#define __GET_PERIPHERAL_LOCK__ 	MUTEX_LOCK(peripheral_mutex)
#define __RELEASE_PERIPHERAL_LOCK__ 		MUTEX_UNLOCK(peripheral_mutex)

#define __GET_MEMORY_LOCK__ 		MUTEX_LOCK(memory_mutex)
#define __RELEASE_MEMORY_LOCK__ 	MUTEX_UNLOCK(memory_mutex)

int NCPUS = 0;
uint8_t global_lock_flag = 0;
int global_lock_owner_core = 0;

extern int global_verbose_flag;

int testAndSetGlobalLock (uint8_t l, int cpu_id)
{
	int ret_val = 0;
	MUTEX_LOCK(lock_mutex);
	if((global_lock_flag == 0) || (cpu_id == global_lock_owner_core))
	{
		ret_val = 1;
		if(l==1)		
		{
#ifdef DEBUG
			fprintf(stderr,"\nGLOCK=1, CPU-ID=%d\n",cpu_id);
#endif
			global_lock_flag = 1;
			global_lock_owner_core = cpu_id;
		}
	}
	MUTEX_UNLOCK(lock_mutex);
	return(ret_val);
}

int clearGlobalLock (uint8_t l, int cpu_id)
{
	MUTEX_LOCK(lock_mutex);
	if(cpu_id == global_lock_owner_core)
	{
		if((l == 0) && global_lock_flag)
		{
#ifdef DEBUG
			fprintf(stderr,"\nGLOCK=0, CPU-ID=%d\n",cpu_id);
#endif
			global_lock_flag = 0;
		}
	}
	MUTEX_UNLOCK(lock_mutex);
	return(0);
}


//
// To reduce redundant invalidates, we can remember the last (address,value,byte_mask) triple
// which was updated into memory from each CPU.  If the state of the memory can be proven
// to be unchanged by the current write, there is no need to generate an invalidate
// message... This needs to be thought about further..
//
// For the moment we remember the last invalidated address for each cpu. If that cpu
// has done no cache line fetches between the last invalidation and the current write
// is to the last invalidated line, then there is no need to generate an invalidate..
//
uint32_t last_line_address_invalidated[4] = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};

void register_bridge_pipes (int number_of_cpus)
{

	// Each cpu will use pipes to communicate
	// with the bridge.  However, the pipes
	// will be registered while starting the
	// cpu thread.  

	// Note that there are two IRL's  a single
	// one to AJIT and individual ones to the
	// CPU's.
	//
	// We will only register the IRL pipe to AJIT.
	//
	register_port("ENV_to_AJIT_irl", 8, 1);
}


void bridge_cpu_0 ()
{
	bridge_cpu_core (0, "AJIT_to_ENV_request_type_0",
				"AJIT_to_ENV_addr_0",
				"AJIT_to_ENV_data_0",
				"AJIT_to_ENV_byte_mask_0",
				"ENV_to_AJIT_data_0");
}

void bridge_cpu_1 ()
{
	bridge_cpu_core (1, "AJIT_to_ENV_request_type_1",
				"AJIT_to_ENV_addr_1",
				"AJIT_to_ENV_data_1",
				"AJIT_to_ENV_byte_mask_1",
				"ENV_to_AJIT_data_1");
}
void bridge_cpu_2 ()
{
	bridge_cpu_core (2, "AJIT_to_ENV_request_type_2",
				"AJIT_to_ENV_addr_2",
				"AJIT_to_ENV_data_2",
				"AJIT_to_ENV_byte_mask_2",
				"ENV_to_AJIT_data_2");
}

void bridge_cpu_3 ()
{
	bridge_cpu_core (3, "AJIT_to_ENV_request_type_3",
				"AJIT_to_ENV_addr_3",
				"AJIT_to_ENV_data_3",
				"AJIT_to_ENV_byte_mask_3",
				"ENV_to_AJIT_data_3");

}

void start_bridge_daemons  (int number_of_cpus)
{
	NCPUS = number_of_cpus;
	
	PTHREAD_DECL (bridge_cpu_0);
	PTHREAD_DECL (bridge_cpu_1);
	PTHREAD_DECL (bridge_cpu_2);
	PTHREAD_DECL (bridge_cpu_3);

	PTHREAD_CREATE (bridge_cpu_0);
	
	if(number_of_cpus > 1)
		PTHREAD_CREATE (bridge_cpu_1);
	if(number_of_cpus > 2)
		PTHREAD_CREATE (bridge_cpu_2);
	if(number_of_cpus > 3)
		PTHREAD_CREATE (bridge_cpu_3);
}

void bridge_cpu_core (int cpu_id,
			char* req_pipe_name, char* addr_pipe_name, 
				char* wdata_pipe_name,  char* byte_mask_pipe_name,
					char* rdata_pipe_name )
{
	uint8_t request_type;
	uint32_t addr;
	uint64_t data64;
	uint8_t byte_mask;

	while (1)
	{
#ifdef DEBUG
		fprintf(stderr,"\nInfo:bridge: bridge-req-start-%d\n", cpu_id);
#endif
		request_type = read_uint8 (req_pipe_name);
		//upper 32 bits of address on the
		//system bus are currently ignored
		addr         = read_uint64(addr_pipe_name);
		data64       = read_uint64(wdata_pipe_name);
		byte_mask    = read_uint8 (byte_mask_pipe_name);

#ifdef DEBUG
		fprintf(stderr,"\nMEMORY ACCESS from CPU %d :  received request from MMU  addr=0x%x, req_type=%d, byte_mask=0x%d, data=0x%lx",cpu_id, addr,request_type,byte_mask,data64);
#endif

		// get the lock bit.
		uint8_t set_mem_access_lock = ((request_type & SET_LOCK_FLAG) != 0);

		// clear the top 2 bits of the request since they
		// are not used.
		request_type     = request_type & 0x3f;
		memDescriptorList* mdl = lookupMem(addr);
		if(mdl != NULL)
		{
			// acquire and set lock for atomic operations.	
			while (!testAndSetGlobalLock(set_mem_access_lock, cpu_id))
			{
				// sleep until you acquire the lock..
				usleep (100);
			}

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
					last_line_address_invalidated[cpu_id] = 0xffffffff;
				}

				data64 = getDoubleWordInMemory(addr);

				if(global_verbose_flag) {
					fprintf(stderr,"0x%" PRIx64 " = MEM[0x%x] CPU=%d lock=%d\n", data64, addr, cpu_id, global_lock_flag);
				}

				write_uint64(rdata_pipe_name, data64);

			}
			else if(request_type == REQUEST_TYPE_WRITE)
			{
				setDoubleWordInMemory(addr, data64, byte_mask);

				//send back the written doubleword so that
				//a copy can be maintained in 
				//our write-allocate cache if necessary
				data64 = getDoubleWordInMemory(addr);

				if(global_verbose_flag) {
					fprintf(stderr,"MEM[0x%x] = 0x%" PRIx64 " bmask=0x%x CPU=%d lock=%d\n", addr,data64,byte_mask, cpu_id, global_lock_flag);
				}

				uint32_t line_addr = (addr >> LOG_BYTES_PER_CACHE_LINE);
				int CPUID;

				for (CPUID= 0;  CPUID< NCPUS; CPUID++)
				{
					if(CPUID!= cpu_id)
					{
						if(line_addr != last_line_address_invalidated[CPUID])
						{
							write_uint32(biu_to_rlut_pipe_names[CPUID],
									line_addr | 0x80000000);
							last_line_address_invalidated[CPUID] = line_addr;
						}
					}
					else
					{
						last_line_address_invalidated[CPUID] = 0xffffffff;
					}
				}
				write_uint64(rdata_pipe_name, data64);
			}
			else
			{
				//this is an invalid request
				fprintf(stderr,"\nERROR: invalid request type %d to memoryAccess thread",request_type);
				assert(0);
			}

			__RELEASE_MEMORY_LOCK__;

			// clear lock for atomic operations
			if(request_type!=REQUEST_TYPE_IFETCH)
				clearGlobalLock(set_mem_access_lock, cpu_id);
		}
		else 
		{
			peripheralDescriptorList* pdl = lookupPeripheral(addr); 	
			if(pdl != NULL)
			{
				__GET_PERIPHERAL_LOCK__

				uint8_t rwbar = (request_type == REQUEST_TYPE_READ);
				data64 = executePeripheralAccess(pdl, rwbar, addr, byte_mask, data64);
				write_uint64(rdata_pipe_name, data64);

				__RELEASE_PERIPHERAL_LOCK__
				
			}
			else
			{
				fprintf(stderr,"\nERROR: unmapped address 0x%x at bridge.\n",addr);
				assert(0);
			}
		}


#ifdef DEBUG
		fprintf(stderr,"\nbridge: Memory access response=0x%" PRIx64 "\n", data64);
#endif

#ifdef DEBUG
		fprintf(stderr,"\nbrige-req-done-%d\n", cpu_id);
#endif
	}
}


