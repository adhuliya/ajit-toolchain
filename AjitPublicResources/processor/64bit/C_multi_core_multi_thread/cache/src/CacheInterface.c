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
#include <assert.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "Ajit_Hardware_Configuration.h"
#include "RequestTypeValues.h"
#include "CacheInterface.h"
#include "Ancillary.h"
#include "ASI_values.h"


int calculate_log2(int number_of_lines)
{
	int ret_val = 0;
	while(number_of_lines > 1)
	{
		ret_val++;
		number_of_lines = number_of_lines/2;
	}
	return(ret_val);
}

void lock_cache (WriteThroughAllocateCache* c)
{
	MUTEX_LOCK(c->cache_mutex);
}

void unlock_cache (WriteThroughAllocateCache* c)
{
	MUTEX_UNLOCK(c->cache_mutex);
}

//mutex for locking the 
//request pipe from caches to MMU
//so that only one cache can
//send a request at a time
pthread_mutex_t mutex_mmu_request_lock = PTHREAD_MUTEX_INITIALIZER;

uint64_t insertBytes (uint64_t x, uint8_t byte_mask, uint64_t wval)
{
	int I;
	uint64_t bmask = 0xff;
	uint64_t ret_val = 0;
	for (I=0; I < 8; I++)
	{
		if ((byte_mask >> I) & 0x1) 
		{
			ret_val = ret_val | (bmask & wval);
		}
		else
		{
			ret_val = ret_val | (bmask & x);
		}
		bmask = bmask << 8;
	}
	return(ret_val);
}


void writeIntoLine(WriteThroughAllocateCache* c, uint64_t write_data, uint32_t va, uint8_t byte_mask)
{
	int I = cacheLineId (c, va);
	int offset = cacheLineOffset (va);

	uint64_t vwal = c->cache_lines[I].cache_line[offset];
	vwal = insertBytes (vwal,byte_mask, write_data);
	c->cache_lines[I].cache_line[offset] = vwal;


}

int cacheLineId (WriteThroughAllocateCache* c, uint32_t va)
{
	va = (va >> LOG_BYTES_PER_CACHE_LINE);
	int ret_val = (va % c->number_of_lines);
	return(ret_val);
}

int cacheLineOffset (uint32_t va)
{
	int retval = ((va >> 3) & 0x7);
	return(retval);
}

uint32_t vaTag(WriteThroughAllocateCache* c, uint32_t va)
{
	uint32_t ret_val  = (va >> (LOG_BYTES_PER_CACHE_LINE + c->log_number_of_lines));
	return(ret_val);
}

uint64_t getDwordFromCache (WriteThroughAllocateCache* c, uint32_t va)
{
	int index = cacheLineId(c, va);
	int offset = cacheLineOffset(va);
	uint64_t retval = (c->cache_lines[index]).cache_line[offset];
	return(retval);
}

WriteThroughAllocateCache* makeCache (uint32_t cpu_id, int is_icache, int number_of_lines)
{
	assert(number_of_lines <= MAX_NUMBER_OF_LINES);

	WriteThroughAllocateCache* nc = (WriteThroughAllocateCache*) 
						malloc (sizeof(WriteThroughAllocateCache));
	nc->cpu_id = cpu_id;
	nc->is_icache = is_icache;

	nc->number_of_lines = number_of_lines;
	nc->log_number_of_lines = calculate_log2(number_of_lines);

	initCache(nc);	

	if(is_icache)
		sprintf(nc->from_rlut_pipe_name,"RLUT_to_ICACHE_%d", cpu_id);
	else
		sprintf(nc->from_rlut_pipe_name,"RLUT_to_DCACHE_%d", cpu_id);

	fprintf(stderr,"Info: made %s number_of_lines=%d, log_number_of_lines=%d\n",
				(is_icache ? "icache" : "dcache"),
				nc->number_of_lines, nc->log_number_of_lines);

	// ICACHE always thinks that mmu is enabled.
	if(is_icache)
	{
		nc->mmu_control_register = 1;
	}
	else
	{
		nc->mmu_control_register = 0;
	}
	nc->mmu_context_register = 0;

	return(nc);
}


void initCache (WriteThroughAllocateCache* c)
{
	c->number_of_accesses = 0;
	c->number_of_flushes  = 0;
	c->number_of_bypasses = 0;
	c->number_of_hits = 0;
	c->number_of_misses = 0;
	c->number_of_write_hits = 0;
	c->number_of_write_misses = 0;
	c->number_of_read_hits = 0;
	c->number_of_read_misses = 0;
	c->number_of_invalidates = 0;
	c->number_of_locked_accesses=0;

	flushCache(c);	

	pthread_mutex_init (&(c->cache_mutex), NULL);
}

void invalidateCacheLine (WriteThroughAllocateCache* c, uint32_t va_line_address)
{
	c->number_of_invalidate_requests++;
	int I = (va_line_address % c->number_of_lines);
	if(c->cache_lines[I].valid)
	{
		uint32_t va_tag = (va_line_address >> c->log_number_of_lines);
		if(c->cache_lines[I].va_tag == va_tag)
		{
			c->cache_lines[I].valid = 0;
			c->number_of_invalidates++;
		}	
	}
}

void lookupCache (WriteThroughAllocateCache* c,
			uint32_t va, uint8_t asi, 
			uint8_t *hit,   uint8_t *acc)
{
	int I = cacheLineId(c, va);
	uint32_t va_tag = vaTag (c, va);

	*hit = 0;
	*acc = 0;

	if(c->cache_lines[I].valid)
	{
		if(c->cache_lines[I].va_tag == va_tag)
		{
			*hit = 1;
			*acc = c->cache_lines[I].acc;
		}
	}
}

void updateCacheLine (WriteThroughAllocateCache* c,
			uint8_t acc, 
			uint32_t line_addr, 
			uint64_t* line_data)
{
	int I = cacheLineId (c, line_addr);

	c->cache_lines[I].valid = 1;
	c->cache_lines[I].acc = acc;
	c->cache_lines[I].va_tag = vaTag(c, line_addr);

	int J;
	for (J=0; J < BYTES_PER_CACHE_LINE/8; J++)
		c->cache_lines[I].cache_line[J] = line_data[J];
}

void flushCache (WriteThroughAllocateCache* c)
{
	int I;
	for (I = 0; I < c->number_of_lines; I++)
	{
		c->cache_lines[I].valid = 0;
	}
}

void decodeDcacheRequest (uint8_t asi, 
		uint8_t request_type,
		uint8_t *is_nop,
		uint8_t *is_stbar,
		uint8_t *is_flush,
		uint8_t *is_read,
		uint8_t *is_cached_mem_access,
		uint8_t *is_mmu_access,
		uint8_t *is_mmu_bypass)
{
	*is_stbar      = 	(request_type==REQUEST_TYPE_STBAR);
	*is_nop        = 	(request_type==REQUEST_TYPE_NOP);
	*is_flush      =        ((asi >= 0x10) &&  (asi <= 0x14));
	*is_read       =  	(request_type == REQUEST_TYPE_READ);
	*is_cached_mem_access =     ((request_type == REQUEST_TYPE_READ) ||
			(request_type == REQUEST_TYPE_WRITE)) &&
		(asi >= 0x8) &&
		(asi <= 0xB);

	*is_mmu_access =    ASI_MMU_ACCESS(asi) || (request_type == REQUEST_TYPE_WRFSRFAR);
	*is_mmu_bypass =    ASI_MMU_PASS_THROUGH(asi);
}

void decodeIcacheRequest (uint8_t asi, 
		uint8_t request_type,
		uint8_t *is_nop,
		uint8_t *is_flush,
		uint8_t *is_ifetch)
{
	*is_nop        = 	(request_type==REQUEST_TYPE_NOP);
	*is_flush      =        (request_type == REQUEST_TYPE_WRITE) &&
		(((asi >= 0x10) &&  (asi <= 0x14)) ||
		 ((asi >= 0x18) && (asi <= 0x1C)));
	// ifetch
	*is_ifetch     =     (request_type == REQUEST_TYPE_IFETCH) && (asi >= 0x8) && (asi <= 0x9);
}

void printCacheStatistics (WriteThroughAllocateCache* c)
{
	fprintf(stderr,"Statistics for %s cpuid=%d\n", (c->is_icache ? "ICACHE" : "DCACHE"), c->cpu_id);
	if(c->number_of_accesses > 0)
		fprintf(stderr,"    number-of-accesses=%ld\n", c->number_of_accesses);
	if(c->number_of_locked_accesses > 0)
		fprintf(stderr,"    number-of-locked-accesses=%d\n", c->number_of_locked_accesses);
	if(c->number_of_flushes > 0)
		fprintf(stderr,"    number-of-flushes=%ld\n", c->number_of_flushes);
	if(c->number_of_bypasses > 0)
		fprintf(stderr,"    number-of-bypasses=%ld\n", c->number_of_bypasses);
	if(c->number_of_hits > 0)
		fprintf(stderr,"    number-of-hits=%ld\n", c->number_of_hits);
	if(c->number_of_misses > 0)
		fprintf(stderr,"    number-of-misses=%ld\n", c->number_of_misses);
	if(c->number_of_write_hits > 0)
		fprintf(stderr,"    number-of-write_hits=%ld\n", c->number_of_write_hits);
	if(c->number_of_write_misses > 0)
		fprintf(stderr,"    number-of-write_misses=%ld\n", c->number_of_write_misses);
	if(c->number_of_read_hits > 0)
		fprintf(stderr,"    number-of-read_hits=%ld\n", c->number_of_read_hits);
	if(c->number_of_read_misses > 0)
		fprintf(stderr,"    number-of-read_misses=%ld\n", c->number_of_read_misses);
	if(c->number_of_invalidate_requests > 0)
		fprintf(stderr,"    number-of-invalidate-requests=%ld\n", c->number_of_invalidate_requests);
	if(c->number_of_invalidates > 0)
		fprintf(stderr,"    number-of-invalidates=%ld\n", c->number_of_invalidates);
}

int accessPermissionsOk (uint8_t request_type, uint8_t asi, uint8_t acc)
{
	int ret_val = 0;
	int is_supervisor = (asi == ASI_SUPERVISOR_INSTRUCTION) || (asi == ASI_SUPERVISOR_DATA);
	int ifetch = (asi == ASI_SUPERVISOR_INSTRUCTION) || (asi == ASI_USER_INSTRUCTION);
	int is_write = (request_type == REQUEST_TYPE_WRITE);
	switch(acc) {
		case 0: // read : read
			ret_val = (!ifetch && !is_write);
			break;
		case 1: // read/write : read/write
			ret_val = !ifetch;
			break;
		case 2: // read/exec: read/exec
			ret_val = !is_write;
			break;
		case 3: // read/write/exec : read/write/exec
			ret_val = 1;
			break;
		case 4: // exec : exec
			ret_val = ifetch;
			break;
		case 5: // read : read/write
			ret_val = (is_supervisor ? !ifetch : !(ifetch || is_write));
			break;
		case 6: // no-access: read/exec
			ret_val = is_supervisor && !is_write;
			break;
		case 7: 
			ret_val = is_supervisor;
			break;
	
	}
	return(ret_val);
}

uint32_t probeCoherencyInvalidateRequest(int cpu_id, int icache_flag)
{
	uint32_t ret_val  = 0;
	ret_val = read_uint32 (getCacheInvalPipeName(cpu_id,icache_flag));
	return(ret_val);
}


void updateMmuState (WriteThroughAllocateCache* c, 
			uint8_t   byte_mask,
			uint32_t  waddr,
			uint64_t  write_dword)
{
	assert(!c->is_icache);

	uint32_t mask_value   = 0;	
	uint32_t upper_word = (write_dword >> 32) & 0xffffffff;

	int I;
	for(I = 7; I >= 4; I--)
	{
		if((byte_mask >> I) & 0x1) 
		{
			mask_value = (mask_value >> 8) | 0xff000000;
		}
	}
	uint32_t ctrl_reg_value = 0;

	switch ((waddr >> 8) & 0x7)
	{
		case 0:
			ctrl_reg_value = c->mmu_control_register;
			c->mmu_control_register = (ctrl_reg_value & (~mask_value)) | (upper_word & mask_value);
			break;
		case 2:
			ctrl_reg_value = c->mmu_context_register;
			c->mmu_context_register = (ctrl_reg_value & (~mask_value)) | (upper_word & mask_value);
			break;
		default:
			break;
	}
#ifdef DEBUG
	fprintf(stderr,"Info:cache: updated mmu state : control=0x%x, context=0x%x\n", 
					c->mmu_control_register,
					c->mmu_context_register);
#endif
}

int isCacheableRequestBasedOnMmuStatus (WriteThroughAllocateCache* c)
{
	int ret_val = 0;
	if((c->mmu_control_register  & 0x1) || (c->mmu_control_register & (0x1 << 8)))
		ret_val = 1;
	return(ret_val);
}
