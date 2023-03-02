#ifndef __tlbs_h____
#define __tlbs_h____
#include <stdint.h>
#include <pthread.h>

typedef struct setAssociativeMemory__ setAssociativeMemory;
struct setAssociativeMemory__ {
	// configuration 
	uint8_t model_id;
	uint8_t tag_width;
	uint8_t data_width;
	uint8_t log_mem_size;
	uint8_t log_set_size;
	uint8_t log_number_of_sets;

	uint32_t set_index_mask;

	uint32_t mem_size;
	uint32_t set_size;
	
	uint8_t*  valids;
	uint16_t* last_modified_index_per_set;
	uint64_t* tags;
	uint64_t* data;

	pthread_mutex_t  pm;
	setAssociativeMemory* next;
};

void generateName(setAssociativeMemory* ms, char* name);

setAssociativeMemory* findOrAllocateSetAssociativeMemory(uint8_t model_id,
								uint8_t tag_width, uint8_t data_width,
								uint8_t log_mem_size, uint8_t log_set_size);

void setAssociativeMemoryCModel (uint8_t model_id,  
					uint8_t twidth, uint8_t data_width, uint8_t log_mem_size,
					uint8_t log_set_size, 
					uint8_t ignore_collisions,
					uint8_t clear_flag, uint8_t erase_flag, uint8_t write_flag,
					uint64_t write_data, uint64_t write_tag, uint16_t write_set_id,
					uint8_t lookup_flag, uint64_t lookup_tag, uint16_t lookup_set_id,
					uint8_t* lookup_valid, uint64_t* lookup_data);

void fullyAssociativeMemoryCModel ( 	uint8_t model_id, 
					uint8_t twidth, uint8_t data_width, uint8_t log_mem_size, 
					uint8_t ignore_collisions,
					uint8_t clear_flag,  uint8_t erase_flag, uint8_t write_flag,
					uint64_t write_data, uint64_t write_tag, 
					uint8_t lookup_flag, uint64_t lookup_tag, 
					uint8_t* lookup_valid, uint64_t* lookup_data);


void clearSetAssociativeMemory(setAssociativeMemory* m);
void eraseFromSetAssociativeMemory(setAssociativeMemory* m, uint64_t write_tag, uint16_t write_set_id);
void writeIntoSetAssociativeMemory(setAssociativeMemory* m, uint64_t write_tag, uint64_t write_data, 
										uint16_t write_set_id);
int lookupSetAssociativeMemory(setAssociativeMemory* m, uint64_t lookup_tag, uint16_t lookup_set_id,
						uint64_t* lookup_data);

void operateOnSetAssociativeMemory(setAssociativeMemory* m, 
					uint8_t ignore_collisions,
					uint8_t clear_flag,
					uint8_t erase_flag, 
					uint8_t write_flag,
					uint64_t write_data,uint64_t write_tag, 
					uint16_t write_set_id,
					uint8_t lookup_flag, uint64_t lookup_tag, uint16_t lookup_set_id, 
					uint8_t* lookup_valid, uint64_t* lookup_data);
int searchForTag(setAssociativeMemory* m, int set_id, uint64_t tag);
#endif
