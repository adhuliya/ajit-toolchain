#ifndef _bridge_h___
#define _bridge_h___

// 8-entry snoop filter cache.
#define SNOOP_FILTER_CACHE_LOG_MEM_SIZE 	 	3

typedef struct  __memDescriptorList memDescriptorList;
struct __memDescriptorList
{
	char mem_name[256];

	uint64_t min_address;
	uint64_t max_address;

	memDescriptorList* next;

	// 0 no read, no write
	// 1 no read, write 
	// 2 read, nowrite
	// 3 read, write.
	uint8_t rw_permissions;
};

typedef struct  __peripheralDescriptorList peripheralDescriptorList;
struct __peripheralDescriptorList
{
	char peripheral_name[256];
	char request_pipe_name[256];
	char response_pipe_name[256];

	uint64_t min_address;
	uint64_t max_address;

	peripheralDescriptorList* next;
};


typedef struct  __bridgeTargets {

	memDescriptorList* md_list;
	peripheralDescriptorList* pd_list;

} bridgeTargets;


void bridgeSetNcores(uint32_t ncores);

void initBridgeTargets();
void setupBridgeTargetsAndPeripherals(char* file_name);

void addMem(char* ram_name, uint8_t permissions, uint64_t minaddr, uint64_t maxaddr);
memDescriptorList* lookupMem(uint64_t addr);

void addPeripheral(char* periph_name, uint64_t min_addr, uint64_t max_addr);
peripheralDescriptorList* lookupPeripheral(uint64_t addr);

int sysMemBusRequest (int core_id,
				int thread_id,
				uint8_t request_type,
				uint8_t byte_mask,
				uint32_t addr,
				uint64_t data64,
				uint64_t *rdata);

uint64_t executePeripheralAccess(peripheralDescriptorList* pdl, 
					uint8_t read_write_bar, 
					uint64_t addr, 
					uint8_t byte_mask, 
					uint64_t write_data);



void bridge_cpu_core (int cpu_id,
				char* req_pipe_name, char* addr_pipe_name, 
				char* wdata_pipe_name,  char* byte_mask_pipe_name,
					char* rdata_pipe_name );
void register_bridge_pipes (int number_of_cpus);
void start_bridge_daemons (int number_of_cpus);



#endif
