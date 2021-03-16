//StartCacheThreads.h

// Routine to start Dcache and Icache 
// as independent threads
// and register all pipes used
// Author : Neha Karanjkar

#ifndef _START_CACHE_THREAD_H_
#define _START_CACHE_THREAD_H_

//register pipes used by the 
//cache subsystem
void register_cache_pipes();

//start Dcache Icache and demuxMMUResponse threads
void start_cache_threads();
#endif
