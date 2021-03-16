//StartMmuThreads.h
//
// Routine to start Mmu thread and 
//register all pipes used
//
// AUTHOR: Neha Karanjkar
#ifndef _START_MMU_THREADS_H_
#define _START_MMU_THREADS_H_

#include <stdlib.h>
#include <stdint.h>



//register pipes used 
void register_mmu_pipes();

void start_mmu_threads();
#endif
