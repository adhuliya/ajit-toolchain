#ifndef _core_h____
#define _core_h____



#define MAX_NCORES 		4
#define MAX_NTHREADS_PER_CORE 	2

typedef struct _CoreState 
{
	uint32_t core_id;
	uint32_t number_of_threads;
	ThreadState*  threads[MAX_NTHREADS_PER_CORE];
	
	MmuState* mmu_state;
	WriteThroughAllocateCache* dcache;
	WriteThroughAllocateCache* icache;

	// each bit corresponds to a page...
	// There are 2^20 pages, so we need 2^15
	// words
	uint32_t page_access_status[32*1024];

} CoreState;

void init_core(CoreState* s, 
			uint32_t core_id,  
			uint32_t number_of_threads,
			uint32_t isa_mode,
			int bp_table_size,
			uint32_t icache_number_of_lines,  uint32_t icache_associativity,
			uint32_t dcache_number_of_lines,  uint32_t dcache_associativity,
			uint8_t report_traps, uint32_t init_pc);
CoreState* makeCoreState(
				uint32_t core_id, 
				uint32_t number_of_threads,
				uint32_t isa_mode,
				uint32_t bp_table_size,
				uint32_t icache_number_of_lines,  uint32_t icache_associativity,
				uint32_t dcache_number_of_lines,  uint32_t dcache_associativity,
				uint8_t report_traps, uint32_t init_pc);
			



void    setPageBit(CoreState* s, uint32_t virtual_addr);
void    dumpPageBits(CoreState* s);
void  	printCoreStatistics (CoreState* s);
		
void setThreadReportingInterval(CoreState* s, uint32_t reporting_interval);
void startThreadHardwareServers(CoreState* s);
void enableThreadHardwareServers(CoreState* s, int gdb_flag, int doval_flag);

void    startCoreThreads(CoreState* s);

#endif
