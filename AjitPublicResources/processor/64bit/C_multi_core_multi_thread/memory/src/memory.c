// memory.c
//
// Model for main memory, and routines for its initialization
// using a hexdump file.
//
//AUTHOR : Neha Karanjkar



#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"

#ifdef SW
	#include <stdio.h>
#endif


#define LOG_PAGE_SIZE 14
#define PAGE_SIZE   (1 << LOG_PAGE_SIZE)  // 14-bits within page 16kB

// memory is modeled simply as an array of pages
// each of which is (2**LOG_PAGE_SIZE) in size.  We will allocate
// a new page only if it is actually used.
//allocated on the heap.
uint8_t** memory_page_array = NULL;


//log of memory size
unsigned int  logMemorySize = 0;
uint64_t memorySize = 0;
unsigned int  number_of_pages = 0;

extern int global_verbose_flag;
int randomize_flag = 0;
void setRandomizeFlag(int val)
{
	randomize_flag = val;
}



//mutexes for locking memory so that it is
//accessed by only one thread at a time
pthread_mutex_t mutex_memory_lock = PTHREAD_MUTEX_INITIALIZER;


// allocate only as needed.
void write_to_mem(uint32_t addr, uint8_t data)
{
	uint32_t page_id  = (addr >> 14);
	uint32_t offset_in_page = (addr & (0xffffffff >> (32 - LOG_PAGE_SIZE)));

	if(memory_page_array[page_id] == NULL)
	{
		uint8_t* new_chunk = NULL;
		if(randomize_flag != 0)
		{
			new_chunk =  (uint8_t*) malloc (PAGE_SIZE*sizeof(uint8_t));
			uint32_t* new_chunk_32 = (uint32_t*) new_chunk;

			// initialize memory to random values...
			// to catch uninitialized issues (sometimes :-())
			//
			int I;
			for(I = 0; I < (PAGE_SIZE >> 2); I++)
			{
				new_chunk_32[I] = rand();
			}
		}
		else
		{
			new_chunk =  (uint8_t*) calloc (1, PAGE_SIZE*sizeof(uint8_t));
		}
		memory_page_array[page_id] = new_chunk;
	}
	uint8_t* page_ptr = memory_page_array[page_id];
	page_ptr[offset_in_page] = data;
}

uint8_t read_from_mem(uint32_t addr)
{
	uint8_t ret_val = 0;
	uint32_t page_id  = (addr >> 14);
	uint32_t offset_in_page = (addr & (0xffffffff >> (32 - LOG_PAGE_SIZE)));
	uint8_t* page_ptr = memory_page_array[page_id];

	if(page_ptr != NULL)
		ret_val = page_ptr[offset_in_page];
	else if(randomize_flag)
		ret_val = rand();

	return(ret_val);
}


// allocate page array.. individual pages will
// be allocated only as necessary.
int allocateMemory(unsigned int log_memory_size)
{
	if(log_memory_size > 36)
	{
		//can't have too large a memory. Exit.
#ifdef SW
		fprintf(stderr,"\nERROR: in allocateMemory() log_memory_size = %u.\
				\nCan't allocate this large memory. Exiting",log_memory_size);
#endif
		return 0;
	}

	logMemorySize = log_memory_size;
	memorySize = (((uint64_t) 1) << ((uint64_t) log_memory_size));

	// number of pages
	number_of_pages = (1 << (log_memory_size - 14));

	// array of page pointers.
	memory_page_array = calloc (number_of_pages, sizeof (uint8_t*));
	if(memory_page_array==NULL)
	{
		//could not allocate sufficient memory. Exit
#ifdef SW
		fprintf(stderr,"\nERROR: in allocateMemory() log_memory_size = %u.\
				\nmalloc() returned failure ",log_memory_size);
#endif
		return 0;
	}
	return 1;
}



//initialize memory by reading a hexdump file
//the hexdump file has lines with format:
//(byte address, byte-data) 
//returns 1 on success
int initializeMemory(char* memoryMapFile)
{
	//memory has to be allocated before this function
	//is called. Check
	if(memory_page_array==NULL)
	{
#ifdef SW
		fprintf(stderr,"\n ERROR: in initializeMemory() \
				\nMemory has not been allocated before initialization");
#endif
		return 0;
	}
	FILE * file;
	file= fopen(memoryMapFile, "r");
	if(!file)
	{
#ifdef SW
		fprintf(stderr,"\n ERROR: file %s could not be opened for reading!\n",memoryMapFile);
#endif
		return 0;
	}

#ifdef DEBUG
	printf("\n opened memory map file %s\n",memoryMapFile);
#endif
	uint32_t addr;
	uint32_t  data;
	int file_read=0;

	while (1)
	{
		file_read=fscanf(file, "%x", &addr);
		if(feof(file) || (file_read == 0)) break; 
		file_read=fscanf(file, "%x", &data);


		//check if address lies in valid memory range
		if(((uint64_t) addr) >  memorySize)
		{
#ifdef DEBUG

			fprintf(stderr,"\n WARNING: in initializeMemory() address 0x%x lies outside available memory. Memory size =0x%lx... wrap-around.",addr,memorySize);

#endif
			addr = addr % memorySize;
		}

		write_to_mem(addr, (uint8_t) data);

	}
#ifdef DEBUG
	fprintf(stderr,"Info:memory:Finished initializing memory from file %s. Last address written = %x",memoryMapFile, addr);
#endif

	fclose(file);
	return 1;
}


//Helper functions for accessing the memory
uint8_t	 getByteInMemory(uint32_t address)
{
	if(address>memorySize)
	{
#ifdef SW
		//fprintf(stderr,"WARNING : address %x outside memory range, wrap-around", address);
#endif
		address = address % memorySize;
	}
	pthread_mutex_lock(&mutex_memory_lock);
	uint8_t byte = read_from_mem(address);

	pthread_mutex_unlock(&mutex_memory_lock);
	return byte;
}


void     setByteInMemory(uint32_t address, uint8_t byte)
{
	if(address>memorySize)
	{
#ifdef SW
		//fprintf(stderr,"WARNING : address %x outside memory range", address);
#endif
		address = address % memorySize;
	}
	pthread_mutex_lock(&mutex_memory_lock);
	write_to_mem(address,byte);
	pthread_mutex_unlock(&mutex_memory_lock);
}

//last 2 bits of address are ignored
uint32_t getWordInMemory(uint32_t address)
{
	if(address+3 > memorySize)
	{
#ifdef SW
		//fprintf(stderr,"WARNING : address %x outside memory range", address+3);
#endif
		address = address % memorySize;
	}
	//clear last 2 bits in memory
	address=(address>>2)<<2;
	pthread_mutex_lock(&mutex_memory_lock);
	uint32_t result =  read_from_mem(address);

	result=(result<<8) | read_from_mem(address+1);
	result=(result<<8) | read_from_mem(address+2);
	result=(result<<8) | read_from_mem(address+3);
	pthread_mutex_unlock(&mutex_memory_lock);
	return result;
}

void     setWordInMemory(uint32_t address, uint32_t word, uint8_t byte_mask)
{
	if(address > memorySize)
	{
#ifdef SW
		//fprintf(stderr,"WARNING : address %x outside memory range", address);
#endif
		address = address % memorySize;
	}
	//clear last 2 bits in memory
	address=(address>>2)<<2;
	pthread_mutex_lock(&mutex_memory_lock);
	if(byte_mask &(1<<3)) 
		write_to_mem(address,    (word & 0xFF000000)>>24);
	if(byte_mask &(1<<2)) 
		write_to_mem(address + 1,(word & 0x00FF0000)>>16);
	if(byte_mask &(1<<1)) 
		write_to_mem(address + 2,(word & 0x0000FF00)>>8);
	if(byte_mask &(1<<0)) 
		write_to_mem(address + 3,(word & 0x000000FF)>>0);
	pthread_mutex_unlock(&mutex_memory_lock);
}


//last 3 bits of address are ignored
uint64_t getDoubleWordInMemory(uint32_t address)
{
	if(address+7 > memorySize)
	{
#ifdef SW
		//fprintf(stderr,"WARNING : address %x outside memory range", address+7);
#endif
		address = address % memorySize;
	}
	//clear last 3 bits of address
	address=(address>>3)<<3;
	pthread_mutex_lock(&mutex_memory_lock);
	uint64_t result =  read_from_mem(address+0);
	result=(result<<8) | read_from_mem(address+1);
	result=(result<<8) | read_from_mem(address+2);
	result=(result<<8) | read_from_mem(address+3);
	result=(result<<8) | read_from_mem(address+4);
	result=(result<<8) | read_from_mem(address+5);
	result=(result<<8) | read_from_mem(address+6);
	result=(result<<8) | read_from_mem(address+7);
	pthread_mutex_unlock(&mutex_memory_lock);
	return result;
}

void    setDoubleWordInMemory(uint32_t address, uint64_t double_word, uint8_t byte_mask)
{
	if(address > memorySize)
	{
#ifdef SW
		//fprintf(stderr,"WARNING : address %x outside memory range.. wrap-around.", address);
#endif
		address = address % memorySize;
	}
	//clear last 3 bits of address
	address=(address>>3)<<3;
	pthread_mutex_lock(&mutex_memory_lock);
	if(byte_mask &(1<<7)) 
		write_to_mem(address, (double_word >> 56));
	if(byte_mask &(1<<6)) 
		write_to_mem(address + 1, (double_word >> 48));
	if(byte_mask &(1<<5)) 
		write_to_mem(address + 2, (double_word >> 40));
	if(byte_mask &(1<<4)) 
		write_to_mem(address + 3, (double_word >> 32));
	if(byte_mask &(1<<3)) 
		write_to_mem(address + 4, (double_word >> 24));
	if(byte_mask &(1<<2)) 
		write_to_mem(address + 5, (double_word >> 16));
	if(byte_mask &(1<<1)) 
		write_to_mem(address + 6, (double_word >> 8));
	if(byte_mask &(1<<0)) 
		write_to_mem(address + 7, double_word);

	pthread_mutex_unlock(&mutex_memory_lock);
}

void accessMemU64 (uint8_t rwbar, uint8_t bmask, uint32_t addr, uint64_t wdata, uint64_t* rdata)
{
	if(rwbar == 0)
	{
		setDoubleWordInMemory (addr, wdata, bmask);
		*rdata = 0;
	}
	else
	{
		*rdata = getDoubleWordInMemory (addr);	
	}
}

void     vGetDoubleWordInMemory(uint32_t address, uint64_t* rd)
{
	*rd = getDoubleWordInMemory(address);
}

