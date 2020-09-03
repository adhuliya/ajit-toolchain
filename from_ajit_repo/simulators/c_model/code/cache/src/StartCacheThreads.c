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
#include <assert.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"

#include "DummyDcache.h"
#include "DummyIcache.h"
#include "CacheInterface.h"
#include "StartCacheThreads.h"


//register pipes used by the 
//cache subsystem
void register_cache_pipes(WriteThroughAllocateCache* c)
{
	int depth = 16;
	register_pipe(c->from_rlut_pipe_name,	  depth, 32,	0);
}


void icacheInvalidateDaemon_0(void *vc)
{
	icacheInvalidate_core ((WriteThroughAllocateCache*) vc);
}
DEFINE_THREAD_WITH_ARG(icacheInvalidateDaemon_0, vc);

void icacheInvalidateDaemon_1(void *vc)
{
	icacheInvalidate_core ((WriteThroughAllocateCache*) vc);
}
DEFINE_THREAD_WITH_ARG(icacheInvalidateDaemon_1, vc);

void icacheInvalidateDaemon_2(void *vc)
{
	icacheInvalidate_core ((WriteThroughAllocateCache*) vc);
}
DEFINE_THREAD_WITH_ARG(icacheInvalidateDaemon_2, vc);

void icacheInvalidateDaemon_3(void *vc)
{
	icacheInvalidate_core ((WriteThroughAllocateCache*) vc);
}
DEFINE_THREAD_WITH_ARG(icacheInvalidateDaemon_3, vc);


void start_icache_thread(WriteThroughAllocateCache* c)
{
	register_cache_pipes(c);
	assert(c && (c->cpu_id >= 0) && (c->cpu_id < 4));
	
	PTHREAD_DECL(icacheInvalidateDaemon_0);
	PTHREAD_DECL(icacheInvalidateDaemon_1);
	PTHREAD_DECL(icacheInvalidateDaemon_2);
	PTHREAD_DECL(icacheInvalidateDaemon_3);

	if(c->cpu_id == 0)
	{
		PTHREAD_CREATE_WITH_ARG(icacheInvalidateDaemon_0, ((void*) c));
	}
	else if(c->cpu_id == 1)
	{
		PTHREAD_CREATE_WITH_ARG(icacheInvalidateDaemon_1, ((void*) c));
	}
	else if(c->cpu_id == 2)
	{
		PTHREAD_CREATE_WITH_ARG(icacheInvalidateDaemon_2, ((void*) c));
	}
	else if(c->cpu_id == 3)
	{
		PTHREAD_CREATE_WITH_ARG(icacheInvalidateDaemon_3, ((void*) c));
	}

}

void dcacheInvalidateDaemon_0(void *vc)
{
	dcacheInvalidate_core ((WriteThroughAllocateCache*) vc);
}
DEFINE_THREAD_WITH_ARG(dcacheInvalidateDaemon_0, vc);

void dcacheInvalidateDaemon_1(void *vc)
{
	dcacheInvalidate_core ((WriteThroughAllocateCache*) vc);
}
DEFINE_THREAD_WITH_ARG(dcacheInvalidateDaemon_1, vc);

void dcacheInvalidateDaemon_2(void *vc)
{
	dcacheInvalidate_core ((WriteThroughAllocateCache*) vc);
}
DEFINE_THREAD_WITH_ARG(dcacheInvalidateDaemon_2, vc);

void dcacheInvalidateDaemon_3(void *vc)
{
	dcacheInvalidate_core ((WriteThroughAllocateCache*) vc);
}
DEFINE_THREAD_WITH_ARG(dcacheInvalidateDaemon_3, vc);


void start_dcache_thread(WriteThroughAllocateCache* c)
{
	register_cache_pipes(c);
	assert(c && (c->cpu_id >= 0) && (c->cpu_id < 4));
	
	PTHREAD_DECL(dcacheInvalidateDaemon_0);
	PTHREAD_DECL(dcacheInvalidateDaemon_1);
	PTHREAD_DECL(dcacheInvalidateDaemon_2);
	PTHREAD_DECL(dcacheInvalidateDaemon_3);

	if(c->cpu_id == 0)
	{
		PTHREAD_CREATE_WITH_ARG(dcacheInvalidateDaemon_0, ((void*) c));
	}
	else if(c->cpu_id == 1)
	{
		PTHREAD_CREATE_WITH_ARG(dcacheInvalidateDaemon_1, ((void*) c));
	}
	else if(c->cpu_id == 2)
	{
		PTHREAD_CREATE_WITH_ARG(dcacheInvalidateDaemon_2, ((void*) c));
	}
	else if(c->cpu_id == 3)
	{
		PTHREAD_CREATE_WITH_ARG(dcacheInvalidateDaemon_3, ((void*) c));
	}

}

