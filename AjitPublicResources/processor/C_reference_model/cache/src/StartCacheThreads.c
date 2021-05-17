//StartCacheThreads.c
//
// Routine to start Dcache and Icache 
// as independent threads
// and register all pipes used
//
// AUTHOR: Neha Karanjkar

#ifdef SW
#include<stdio.h>
#endif
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"

#include "DummyDcache.h"
#include "DummyIcache.h"
#include "CacheInterface.h"
#include "StartCacheThreads.h"

void DummyIcache();
void DummyDcache();
void DemuxMMUtoCaches();
DEFINE_THREAD(DummyIcache);
DEFINE_THREAD(DummyDcache);
DEFINE_THREAD(DemuxMMUtoCaches);


//register pipes used by the 
//cache subsystem
void register_cache_pipes()
{
	int depth = 2;

	//MMU-side pipes
	register_pipe("CACHE_to_MMU_asi",	  depth, 8,	0);
	register_pipe("CACHE_to_MMU_addr",	  depth, 32,	0);
	register_pipe("CACHE_to_MMU_request_type",depth, 8,	0);
	register_pipe("CACHE_to_MMU_byte_mask",	  depth, 8,	0);
	register_pipe("CACHE_to_MMU_data",	  depth, 64,	0);

	set_pipe_is_written_into("CACHE_to_MMU_asi");
	set_pipe_is_written_into("CACHE_to_MMU_addr");
	set_pipe_is_written_into("CACHE_to_MMU_request_type");
	set_pipe_is_written_into("CACHE_to_MMU_byte_mask");
	set_pipe_is_written_into("CACHE_to_MMU_data");
	
	
	register_pipe("MMU_to_CACHE_mae",	  depth, 8,	0);
	register_pipe("MMU_to_CACHE_data",	  depth, 64,	0);
	register_pipe("MMU_to_CACHE_cacheable",  depth, 8,	0);
	register_pipe("MMU_to_CACHE_fsr",  depth, 32,	0);
	
	set_pipe_is_read_from("MMU_to_CACHE_mae");
	set_pipe_is_read_from("MMU_to_CACHE_data");
	set_pipe_is_read_from("MMU_to_CACHE_cacheable");
	set_pipe_is_read_from("MMU_to_CACHE_fsr");
	
	
	//Pipes internal to the cache subsystem.
	//They're both read from and written to by the cache
	register_pipe("MMU_to_DCACHE_mae",	  depth, 8,	0);
	register_pipe("MMU_to_DCACHE_data",	  depth, 64,	0);
	register_pipe("MMU_to_DCACHE_cacheable",  depth, 8,	0);

	set_pipe_is_read_from("MMU_to_DCACHE_mae");
	set_pipe_is_read_from("MMU_to_DCACHE_data");
	set_pipe_is_read_from("MMU_to_DCACHE_cacheable");
	set_pipe_is_written_into("MMU_to_DCACHE_mae");
	set_pipe_is_written_into("MMU_to_DCACHE_data");
	set_pipe_is_written_into("MMU_to_DCACHE_cacheable");
	
	register_pipe("MMU_to_ICACHE_mae",	  depth, 8,	0);
	register_pipe("MMU_to_ICACHE_data",	  depth, 64,	0);
	register_pipe("MMU_to_ICACHE_cacheable",  depth, 8,	0);	
	register_pipe("MMU_to_ICACHE_fsr",  depth, 32,	0);
	
	set_pipe_is_read_from("MMU_to_ICACHE_mae");
	set_pipe_is_read_from("MMU_to_ICACHE_data");
	set_pipe_is_read_from("MMU_to_ICACHE_cacheable");
	set_pipe_is_read_from("MMU_to_ICACHE_fsr");
	set_pipe_is_written_into("MMU_to_ICACHE_mae");
	set_pipe_is_written_into("MMU_to_ICACHE_data");
	set_pipe_is_written_into("MMU_to_ICACHE_cacheable");
	set_pipe_is_written_into("MMU_to_ICACHE_fsr");

}

void start_cache_threads()
{
	register_cache_pipes();
	PTHREAD_DECL(DemuxMMUtoCaches);
	PTHREAD_CREATE(DemuxMMUtoCaches);
	PTHREAD_DECL(DummyIcache);
	PTHREAD_DECL(DummyDcache);
	PTHREAD_CREATE(DummyIcache);
	PTHREAD_CREATE(DummyDcache);
}

