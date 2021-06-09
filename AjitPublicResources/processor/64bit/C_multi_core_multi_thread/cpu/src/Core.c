#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "AjitThread.h"
#include "Core.h"
#include "ThreadInterface.h"
#include "ThreadHWserverInterface.h"
#include "StartHwServerThreads.h"
#include "StartAjitThreads.h"

void  setPageBit(CoreState* s, uint32_t virtual_addr)
{
	uint32_t page_id = (virtual_addr >> 12);
	uint32_t idx = page_id >> 5;

	uint32_t offset = (page_id & 0x1f);
	s->page_access_status[idx] = s->page_access_status[idx] | (1 << offset);
}

void  dumpPageBits(CoreState* s)
{
	fprintf(stderr,"Info: for Core %d: 4kB pages accessed are (starting virtual-address of the page is shown):\n", s->core_id);
	uint32_t I;
	for(I = 0; I < (32*1024); I++)
	{
		uint32_t prec = s->page_access_status[I];
		if(prec  != 0)
		{
			uint32_t J;
			for(J=0; J < 32; J++)
			{
				if((prec >> J)	 &  0x1) 
				{
					uint32_t pid = (I << 5) + J;
					fprintf(stderr,"     0x%08x\n", (pid << 12));
				}
			}
		}
	}
}


void  	printCoreStatistics (CoreState* s) 
{
	
	dumpPageBits(s);

	printMmuStatistics(s->mmu_state);
	printCacheStatistics(s->icache);
	printCacheStatistics(s->dcache);

}

void init_core(CoreState* s, 
			uint32_t core_id,  
			uint32_t number_of_threads,
			uint32_t isa_mode,
			int bp_table_size,
			int icache_number_of_lines, int dcache_number_of_lines,
			uint8_t report_traps, uint32_t init_pc)
{
	s->core_id = core_id;
	s->number_of_threads =  number_of_threads;

	// make the memory subsystem.
	s->mmu_state      =  makeMmuState (core_id);
	s->icache         =  makeCache (core_id, 1, icache_number_of_lines);
	s->dcache         =  makeCache (core_id, 0, dcache_number_of_lines);

	// make the threads.
	uint32_t I;
	for(I = 0; I < number_of_threads; I++)
	{
		s->threads[I] = makeThreadState(core_id, I, isa_mode, bp_table_size, report_traps, init_pc);
		s->threads[I]->mmu_state = s->mmu_state;
		s->threads[I]->dcache = s->dcache;
		s->threads[I]->icache = s->icache;
		s->threads[I]->parent_core_state = (CoreState*) s;
	
		char irl_buffer[256];
		sprintf(irl_buffer,"ENV_to_AJIT_irl_%d_%d", core_id, I);

		register_port(irl_buffer, 8, 1);
	}

	// page access bits.
	for(I=0; I < (32*1024); I++)
	{
		s->page_access_status[I] = 0;	
	}

	resetMmuState (s->mmu_state);
	flushCache (s->dcache);
	flushCache (s->icache);
}


CoreState*  makeCoreState(	uint32_t core_id,  
				uint32_t number_of_threads,
				uint32_t isa_mode, 
				uint32_t bp_table_size, 
				uint32_t icache_number_of_lines, uint32_t dcache_number_of_lines,
				uint8_t report_traps,
				uint32_t init_pc)
{
	CoreState* s = (CoreState*) malloc(sizeof(CoreState));
	init_core (s, core_id, number_of_threads, isa_mode, bp_table_size, 
				icache_number_of_lines, dcache_number_of_lines,
					report_traps, init_pc);
	return(s);
}

void startCoreThreads(CoreState* s)
{
	int I;
	for(I = 0; I < s->number_of_threads; I++)
	{
		start_ajit_thread(s->threads[I]);	
	}
}

void setThreadReportingInterval(CoreState* s, uint32_t reporting_interval)
{
	int I;
	for(I = 0; I < s->number_of_threads; I++)
	{
		s->threads[I]->reporting_interval = reporting_interval;
	}
}

void startThreadHardwareServers(CoreState* s)
{
	int I;
	for(I = 0; I < s->number_of_threads; I++)
	{
		s->threads[I]->hw_server = start_hw_server(s->core_id, I);
	}
}
void enableThreadHardwareServers(CoreState* s, int gdb_flag, int doval_flag)
{
	int I;
	for(I = 0; I < s->number_of_threads; I++)
	{
		thread_enable_HW_server(s->threads[I], gdb_flag, doval_flag);
	}
}

