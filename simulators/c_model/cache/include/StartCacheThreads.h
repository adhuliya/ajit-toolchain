//StartCacheThreads.h

// Routine to start Dcache and Icache 
// as independent threads
// and register all pipes used
// Author : Neha Karanjkar

#ifndef _START_CACHE_THREAD_H_
#define _START_CACHE_THREAD_H_
#include "CacheInterface.h"

void register_cache_pipes(WriteThroughAllocateCache* c);
void start_icache_thread(WriteThroughAllocateCache* c);
void start_dcache_thread(WriteThroughAllocateCache* c);

#endif
