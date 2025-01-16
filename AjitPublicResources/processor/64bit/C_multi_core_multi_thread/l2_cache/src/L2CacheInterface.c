#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <assert.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "Ajit_Hardware_Configuration.h"
#include "RequestTypeValues.h"
#include "L2CacheInterface.h"
#include "Ancillary.h"
#include "ASI_values.h"
#include "memory.h"

extern int global_verbose_flag;
extern int use_encrypted_memory;
extern int global_enable_statistic_collection;

FILE* l2_cache_trace_file = NULL;

void lockWriteBackCache (WriteBackCache* c)
{
	MUTEX_LOCK(c->cache_mutex);
}

void unlockWriteBackCache (WriteBackCache* c)
{
	MUTEX_UNLOCK(c->cache_mutex);
}


//
// Allocate a write-back cache.
//
WriteBackCache* makeWriteBackCache (uint32_t id, int number_of_lines, int set_size)
{
	WriteBackCache* nc = (WriteBackCache*) malloc (sizeof(WriteBackCache));
	nc->id = id;

	nc->number_of_lines = number_of_lines;
	nc->log_number_of_lines = calculate_log2(number_of_lines);

	nc->number_of_sets = (number_of_lines/set_size);
	nc->log_number_of_sets = calculate_log2(nc->number_of_sets);
	nc->set_size       = set_size;
	
	initWriteBackCache(nc);	

#ifdef DEBUG_PRINT
	fprintf(stderr,"Info: made L2 cache:  associativity=%d, number_of_lines=%d, log_number_of_lines=%d\n",
				set_size,
				nc->number_of_lines, nc->log_number_of_lines);
#endif

	return(nc);
}


// initialize the cache data stucture.
void initWriteBackCache (WriteBackCache* c)
{

	c->most_recently_used_indices = (uint8_t*)  malloc (c->number_of_sets * sizeof(uint8_t));
	c->cache_lines = (WriteBackCacheLine*) malloc (c->number_of_lines * sizeof(WriteBackCacheLine));

	clearWriteBackCache (c);

	pthread_mutex_init (&(c->cache_mutex), NULL);
}

// clear the cache.
void clearWriteBackCache (WriteBackCache* c)
{
	c->number_of_accesses = 0;
	c->number_of_write_hits = 0;
	c->number_of_write_misses = 0;
	c->number_of_read_hits = 0;
	c->number_of_read_misses = 0;
	c->number_of_memory_reads = 0;
	c->number_of_memory_writes = 0;

	int I; 
	for(I = 0; I < c->number_of_sets; I++)
	{
		c->most_recently_used_indices[I] = 0;
	}

	for (I = 0; I < c->number_of_lines; I++)
	{
		c->cache_lines[I].valid = 0;
		int W;
		for(W = 0; W < L2_DWORDS_PER_CACHE_LINE; W++)
			c->cache_lines[I].dirty_dword_bits[W] = 0;
	}
}


// Find and write cache line to memory.
void writeCacheLineBackToMemory (WriteBackCache* c, uint64_t pa)
{
	int line_index; uint8_t index_in_set;
	int is_hit = lookupL2Cache (c, pa, &line_index, &index_in_set);

	// base byte address of line.
	uint64_t pa_base = (pa >> 6) << 6;

	int W;
	for (W = 0; W < L2_DWORDS_PER_CACHE_LINE; W++)
	{
		if(c->cache_lines[line_index].dirty_dword_bits[W]) 
		{
			if(use_encrypted_memory)
			{
				int write_quad_word = 0;
				if(W & 0x1)
				{
					// even dword was not dirty, but odd dword is...
					if(!c->cache_lines[line_index].dirty_dword_bits[W-1])
					{
						// encrypt and write pair W-1,W
						setQuadWordInMemory 
							(pa_base + ((W-1) << 3),
								c->cache_lines[line_index].cache_line[W-1],
								c->cache_lines[line_index].cache_line[W]);
							
					}
				}
				else
				{
					// even dword was dirty
					// encrypt and write pair W,W+1
					setQuadWordInMemory 
						(pa_base + (W << 3),
						 c->cache_lines[line_index].cache_line[W],
						 c->cache_lines[line_index].cache_line[W+1]);
				}
			}
			else
			{
				// write to memory.
				setDoubleWordInMemory(pa_base + (W << 3), c->cache_lines[line_index].cache_line[W], 0xff);
				if(global_enable_statistic_collection)
					c->number_of_memory_writes++;
			}
		}
	}
}

// read a line from memory into cache..  the valid bit etc
// is assumed to have been set earlier..
void readWriteBackCacheLineFromMemory    (WriteBackCache* c, uint64_t pa)
{
	int line_index; uint8_t index_in_set;
	int is_hit = lookupL2Cache (c, pa, &line_index, &index_in_set);
	assert(is_hit);

	// base address of line.
	uint64_t pa_base = (pa >> 6) << 6;

	int W;
	for (W = 0; W < L2_DWORDS_PER_CACHE_LINE; W++)
	{
		if(use_encrypted_memory)
		{
			if((W & 0x1) == 0)
			{
				// If it is an even dword...

				uint64_t dw0, dw1;
				getQuadWordInMemory (pa_base + (W  << 3), &dw0, &dw1);
				c->cache_lines[line_index].cache_line[W] = dw0;
				c->cache_lines[line_index].cache_line[W+1] = dw1;
				c->cache_lines[line_index].dirty_dword_bits[W] = 0;
				c->cache_lines[line_index].dirty_dword_bits[W+1] = 0;
			}
		}
		else
		{
			uint64_t dw = getDoubleWordInMemory(pa_base + (W << 3));
			c->cache_lines[line_index].cache_line[W] = dw;
			c->cache_lines[line_index].dirty_dword_bits[W] = 0;
			if(global_enable_statistic_collection)
				c->number_of_memory_reads++;
		}
	}
}


// Find a line suitable for accomodating pa.  
// Also reports hit, replace status, index in set.
int allocateWriteBackCacheLine (WriteBackCache* c, 
						uint64_t pa, 
						uint8_t* hit, 
						uint64_t* replace_base_address,
						uint8_t* replace_flag)
{
	int ret_val = 0;
	int found = 0;
	*hit = 0;
	*replace_flag = 0;
	*replace_base_address = 0;

	// find set id to which pa belongs.
	uint32_t set_id = writeBackCacheSetId(c,pa);

	uint8_t I;
	for(I = 0; I < c->set_size; I++)
	{
		// candidate for new cache line...
		int J = (set_id*c->set_size) + I;

		// candidate is a hit on pa?
		uint8_t is_a_hit = 
			(c->cache_lines[J].valid) && 
				(writeBackCachePaTag(c, pa) == c->cache_lines[J].pa_tag);
		if(is_a_hit)
		{
			// return candidate if pa is a hit
			// or if no line at candidate.
			found = 1;	
			*hit = 1;

			ret_val = J;
			return(ret_val);
		}
	}

	// See if there is an invalid line in the set..
	for(I = 0; I < c->set_size; I++)
	{
		// candidate for new cache line...
		int J = (set_id*c->set_size) + I;

		// candidate is a hit on pa?
		uint8_t is_a_hit = 
			(c->cache_lines[J].valid) && 
				(writeBackCachePaTag(c, pa) == c->cache_lines[J].pa_tag);
		if(!is_a_hit && !(c->cache_lines[J].valid))
		{
			// found invalid line.
			found = 1;	
			*hit = 0;

			ret_val = J;
			return(ret_val);
		}
	}
	
	

	if(!found)
	// did not find an open/hit line.  find replacement.
	//   not most recently used...
	{
		uint8_t index_within_set = (c->most_recently_used_indices[set_id] + 1) % c->set_size;

		// line-index.
		ret_val      = (set_id * c->set_size) + index_within_set;

		// replace-address:   pa_tag & set_id & index-within-set 
		*replace_base_address = 
			calculateLinePa (c, c->cache_lines[ret_val].pa_tag, set_id);
		*replace_flag = 1;

	}

	return(ret_val);
}

// invalidate a line..
void 	invalidateWriteBackCacheLine (WriteBackCache* c, uint32_t line_index)
{
	c->cache_lines[line_index].valid = 0;
	int W;
	for(W = 0; W < L2_DWORDS_PER_CACHE_LINE; W++)
	{
		c->cache_lines[line_index].dirty_dword_bits[W] = 0;
	}
}

// read a dword from the specified cache line..
uint64_t readFromWriteBackCacheLine (WriteBackCache* c, uint32_t line_index, uint32_t offset_in_line)
{
	uint64_t ret_val;
	ret_val = c->cache_lines[line_index].cache_line[offset_in_line];
	return(ret_val);
}

// write a dword to the specified cache line.
uint64_t writeToWriteBackCacheLine 
		(WriteBackCache* c, uint32_t line_index, uint32_t offset_in_line,
						uint64_t wdword, uint8_t byte_mask)
{
	uint64_t oval = c->cache_lines[line_index].cache_line[offset_in_line];
	uint64_t nval = insert_bytes_into_dword (oval, byte_mask, wdword);

	c->cache_lines[line_index].cache_line[offset_in_line] = nval;
	c->cache_lines[line_index].dirty_dword_bits[offset_in_line] = 1;
	return(nval);
}

// Set-id for physical address
uint32_t writeBackCacheSetId    (WriteBackCache* c, uint64_t pa)
{
	uint32_t set_index =  
		(pa >> LOG_BYTES_PER_CACHE_LINE) % c->number_of_sets;
	return(set_index);	
}

// Offset into cache line.
uint32_t writeBackCacheLineOffset (uint64_t pa)
{
	int retval = ((pa >> 3) & 0x7);
	return(retval);
}

// return: is_hit
//    line index is kept in *line_index.
int lookupL2Cache (WriteBackCache* c, uint64_t pa, int* line_index, uint8_t* index_in_set)
{
	int ret_val = 0;
	uint32_t set_id = writeBackCacheSetId(c,pa);

	*line_index = -1;
	*index_in_set = -1;

	uint8_t I; 
	for(I = 0; I < c->set_size; I++)
	{
		// candidate location for line.
		int J = (set_id*c->set_size) + I;

		// candidate is a hit on pa?
		uint8_t is_a_hit = 
			(c->cache_lines[J].valid) && 
				(writeBackCachePaTag(c, pa) == c->cache_lines[J].pa_tag);
		if(is_a_hit)
		{
			ret_val = 1;
			*line_index = J;
			*index_in_set = I;
			break;
		}
	}
	return(ret_val);
}

// calculate pa of line based on tag and set-id.
uint64_t calculateLinePa (WriteBackCache* c, uint64_t pa_tag, uint32_t set_id)
{
	uint64_t pa_tag_left_shifted = (pa_tag << (LOG_BYTES_PER_CACHE_LINE + c->log_number_of_sets));
	uint64_t set_id_left_shifted = (set_id << LOG_BYTES_PER_CACHE_LINE);
	uint64_t pa = (pa_tag_left_shifted | set_id_left_shifted);
	return(pa);
}



// calculate tag corresponding to pa.
uint32_t writeBackCachePaTag(WriteBackCache* c, uint64_t pa)
{
	uint32_t ret_val  = 
		(pa >> (LOG_BYTES_PER_CACHE_LINE + c->log_number_of_sets));
	return(ret_val);
}

void printWriteBackCacheStatistics (WriteBackCache* c)
{
	fprintf(stderr,"Statistics for WB Cache id=%d\n", c->id);
	if(c->number_of_accesses > 0)
		fprintf(stderr,"    number-of-accesses=%ld\n", c->number_of_accesses);
	if(c->number_of_write_hits > 0)
		fprintf(stderr,"    number-of-write_hits=%ld\n", c->number_of_write_hits);
	if(c->number_of_write_misses > 0)
		fprintf(stderr,"    number-of-write_misses=%ld\n", c->number_of_write_misses);
	if(c->number_of_read_hits > 0)
		fprintf(stderr,"    number-of-read_hits=%ld\n", c->number_of_read_hits);
	if(c->number_of_read_misses > 0)
		fprintf(stderr,"    number-of-read_misses=%ld\n", c->number_of_read_misses);
	if(c->number_of_memory_reads > 0)
		fprintf(stderr,"    number-of-memory-reads=%ld\n", c->number_of_memory_reads);
	if(c->number_of_memory_writes > 0)
		fprintf(stderr,"    number-of-memory-writes=%ld\n", c->number_of_memory_writes);
}

void dumpL2CacheAccessTrace (WriteBackCache* c, 
					uint64_t addr, 
					uint8_t rwbar, 
					uint8_t byte_mask,
					uint64_t wdata, uint64_t rdata)
{
	if(rwbar)
	{
		fprintf(stderr," l2c %d  read  addr=0x%llx rdata=0x%llx\n", 
						c->id, 
						addr, 
						rdata);
	}
	else
	{
		fprintf(stderr," l2c %d  write  addr=0x%llx bmask=0x%x, wdata=0x%llx\n", 
						c->id, 
						addr, 
						byte_mask,
						wdata);
	}
}


void setL2CacheTraceFile(FILE* fp) 
{
	l2_cache_trace_file = fp;
}

// write back cache access....
//      
uint64_t doWriteBackCacheAccess (WriteBackCache* c,
				uint8_t rwbar,
				uint8_t bmask,
				uint64_t pa, 
				uint64_t wdata)
{
#ifdef DEBUG_PRINT
	fprintf(stderr,"Info: doWriteBackCacheAccess cache=%d, rwbar=%d, bmask=0x%x, pa=0x%llx, wdata=0x%llx\n",
			c->id, rwbar, bmask, pa, wdata);
#endif
	/*
		1. Look up in the cache. 
                2. if hit, access line update dirty bits and return.
		   else find line to (optionally) replace.
		3. If replace is required, write out the old
                   line.
		4. read in the new line.
		5. if write miss, write into the new line
		6. return the read-value (or written value).
	*/

	if(global_enable_statistic_collection)
		c->number_of_accesses++;

	// 1.
	uint8_t is_hit; 
	int line_index;
	uint8_t index_in_set;
	is_hit = lookupL2Cache(c, pa,&line_index, &index_in_set);

	
	if(!is_hit)
	{

		
		if(global_enable_statistic_collection)
		{
			if(rwbar) c->number_of_read_misses++;
			else c->number_of_write_misses++;
		}

#ifdef DEBUG_PRINT
		fprintf(stderr,"Info: miss\n");
#endif


		//2: find line to replace..
		uint8_t replace_flag;	
		uint64_t replace_pa;

		line_index = allocateWriteBackCacheLine (c, pa, &is_hit,  &replace_pa, &replace_flag);
		if(replace_flag)
		{
#ifdef DEBUG_PRINT
			fprintf(stderr,"Info: replace line %d\n", line_index);
#endif

			// 3. write back line to be replaced.
			writeCacheLineBackToMemory(c, replace_pa);
		}

		//4: update new line.

		// update tags etc.
		c->cache_lines[line_index].valid = 1;
		c->cache_lines[line_index].pa_tag = writeBackCachePaTag(c, pa);

		int W;
		for(W = 0; W < L2_DWORDS_PER_CACHE_LINE; W++)
		{
			c->cache_lines[line_index].dirty_dword_bits[W] = 0;
		}

#ifdef DEBUG_PRINT
		fprintf(stderr,"Info: fetch line %d\n", line_index);
#endif

		// .. read from memory.	
		readWriteBackCacheLineFromMemory (c, pa);
		
	}
	else
	{
#ifdef DEBUG_PRINT
		fprintf(stderr,"Info: hit\n");
#endif
		if(global_enable_statistic_collection)
		{
			if(rwbar)
				c->number_of_read_hits++;
			else
				c->number_of_write_hits++;
		}
	}


	is_hit = lookupL2Cache(c, pa,&line_index, &index_in_set);
	int set_id = writeBackCacheSetId(c, pa);
	c->most_recently_used_indices[set_id] = index_in_set;

	uint32_t offset_in_line = (pa >> 3) & 0x7;
	uint64_t ret_val =  wdata;
	if(rwbar)
		ret_val = readFromWriteBackCacheLine (c, line_index, offset_in_line);
	else
		ret_val = writeToWriteBackCacheLine (c, line_index, offset_in_line, wdata, bmask);

#ifdef DEBUG_PRINT
	fprintf(stderr,"Info: doWriteBackCacheAccess cache=%d, rdata=0x%llx\n",
			c->id, ret_val);
#endif
	return(ret_val);
}

