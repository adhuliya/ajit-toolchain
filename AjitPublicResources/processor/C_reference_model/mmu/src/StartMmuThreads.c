//StartMmuThreads.c
//
// Routine to start Mmu thread and 
//register all pipes used
//
// AUTHOR: Neha Karanjkar
#ifdef SW
#include <stdio.h>
#endif
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "Pipes.h"
#include "pipeHandler.h"

#include "Mmu.h"
#include "CacheInterface.h"
#include "StartMmuThreads.h"



void Mmu();
DEFINE_THREAD(Mmu);


//register pipes used 
void register_mmu_pipes()
{
	int depth = 2;
	register_pipe("CACHE_to_MMU_asi",	  depth, 8,	0);
	register_pipe("CACHE_to_MMU_addr",	  depth, 32,	0);
	register_pipe("CACHE_to_MMU_request_type",depth, 8,	0);
	register_pipe("CACHE_to_MMU_byte_mask",	  depth, 8,	0);
	register_pipe("CACHE_to_MMU_data",	  depth, 64,	0);
	
	set_pipe_is_read_from("CACHE_to_MMU_asi");
	set_pipe_is_read_from("CACHE_to_MMU_addr");
	set_pipe_is_read_from("CACHE_to_MMU_request_type");
	set_pipe_is_read_from("CACHE_to_MMU_byte_mask");
	set_pipe_is_read_from("CACHE_to_MMU_data");

	register_pipe("MMU_to_CACHE_mae",	  depth, 8,	0);
	register_pipe("MMU_to_CACHE_data",	  depth, 64,	0);
	register_pipe("MMU_to_CACHE_cacheable",  depth, 8,	0);
	
	set_pipe_is_written_into("MMU_to_CACHE_mae");
	set_pipe_is_written_into("MMU_to_CACHE_data");
	set_pipe_is_written_into("MMU_to_CACHE_cacheable");
	

	// 36 bits are used for addr, but in C we have to go to 64
	register_pipe("AJIT_to_ENV_request_type", depth, 8,	0);
	register_pipe("AJIT_to_ENV_addr",	  depth, 64,	0);
	register_pipe("AJIT_to_ENV_data",	  depth, 64,	0);
	register_pipe("AJIT_to_ENV_byte_mask",	  depth, 8,	0);
	
	set_pipe_is_written_into("AJIT_to_ENV_request_type");
	set_pipe_is_written_into("AJIT_to_ENV_addr");
	set_pipe_is_written_into("AJIT_to_ENV_data");
	set_pipe_is_written_into("AJIT_to_ENV_byte_mask");
	
	register_pipe("ENV_to_AJIT_data",	  depth, 64,	0);
	set_pipe_is_read_from("ENV_to_AJIT_data");

}

void start_mmu_threads()
{
	register_mmu_pipes();
	PTHREAD_DECL(Mmu);
	PTHREAD_CREATE(Mmu);
}

