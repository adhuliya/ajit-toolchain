// memory.c
//
// Model for main memory, and routines for its initialization
// using a hexdump file.
//
//AUTHOR : Neha Karanjkar



#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include "uarch_debug_utils.h"
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
uint64_t maxMemoryAddress;
unsigned int  number_of_pages = 0;


//mutexes for locking memory so that it is
//accessed by only one thread at a time
pthread_mutex_t mutex_memory_lock = PTHREAD_MUTEX_INITIALIZER;

extern int   global_verbose_flag;

// allocate only as needed.
uint8_t write_to_mem(uint32_t addr, uint8_t data)
{
	uint8_t err = 0;

	if(((uint64_t) addr) > maxMemoryAddress)
	{
		err = 1;
		addr = (addr % maxMemoryAddress);
	}

	uint32_t page_id  = (addr >> 14);
	uint32_t offset_in_page = (addr & (0xffffffff >> (32 - LOG_PAGE_SIZE)));
	if(memory_page_array[page_id] == NULL)
	{
		memory_page_array[page_id] = (uint8_t*) malloc (PAGE_SIZE*sizeof(uint8_t));
		uint32_t* ptr = (uint32_t*) (memory_page_array[page_id]);
		int i;
		for(i = 0; i < PAGE_SIZE/4; i++)
		{
			// initialize with some junk value which
			// grabs attention..
			ptr[i] = 0xdeadfeed;;
		}
	
	}
	uint8_t* page_ptr = memory_page_array[page_id];
	page_ptr[offset_in_page] = data;

	return(err);
}

uint8_t read_from_mem(uint32_t addr)
{

	uint8_t byte = 0;


	if(((uint64_t) addr) > maxMemoryAddress)
	{
		addr = (addr % maxMemoryAddress);
	}

	uint32_t page_id  = (addr >> 14);
	uint32_t offset_in_page = (addr & (0xffffffff >> (32 - LOG_PAGE_SIZE)));
	uint8_t* page_ptr = memory_page_array[page_id];

	if(page_ptr != NULL)
		byte = page_ptr[offset_in_page];

	return(byte);
}


// allocate page array.. individual pages will
// be allocated only as necessary.
int allocateMemory(unsigned int log_memory_size)
{
	if(log_memory_size > 36)
	{
		//can't have too large a memory. Exit.
#ifdef SW
		fprintf(stderr,"\nERROR: in allocateMemory() log_memoy_size = %u.\
				\nCan't allocate this large memory. Exiting",log_memory_size);
#endif
		return 0;
	}

	logMemorySize = log_memory_size;
	memorySize = (((uint64_t) 1) << ((uint64_t) log_memory_size));
	maxMemoryAddress = memorySize - 4;

	// number of pages
	number_of_pages = (1 << (log_memory_size - 14));

	// array of page pointers.
	memory_page_array = calloc (number_of_pages, sizeof (uint8_t*));
	if(memory_page_array==NULL)
	{
		//could not allocate sufficient memory. Exit
#ifdef SW
		fprintf(stderr,"\nERROR: in allocateMemory() log_memoy_size = %u.\
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
		if(feof(file)) break; 
		file_read=fscanf(file, "%x", &data);


		//check if address lies in valid memory range
		if(((uint64_t) addr) >  memorySize)
		{
#ifdef SW
			fprintf(stderr,"\n WARNING: in initializeMemory() \
					\naddress 0x%x lies outside available memory. Memory size =0x%lx",addr,memorySize);
#endif
			addr = (addr % memorySize);
		}

		write_to_mem(addr, (uint8_t) data);

	}
#ifdef DEBUG
	printf("\n Finished initializing memory from file %s.\
			\nLast address written = %x",memoryMapFile, addr);
	#endif

	fclose(file);
	return 1;
}

// to be used to initialize memory through the debug
// interface..  This will be needed to test the FPGA
// prototype.
int initializeMemoryThroughDebugInterface(char* memoryMapFile)
{
	int ret_val = dbg_load_mmap(memoryMapFile);
	return ret_val;
}



//Helper functions for accessing the memory
uint8_t	 getByteInMemory(uint32_t address, uint8_t* byte)
{
	uint8_t err = 0;
	if(address>memorySize)
	{
		#ifdef SW
		fprintf(stderr,"ERROR : address %x outside memory range", address);
		#endif
		err = 1;
	}
	pthread_mutex_lock(&mutex_memory_lock);
	*byte = read_from_mem(address);

	pthread_mutex_unlock(&mutex_memory_lock);
	return err;
}

uint8_t   setByteInMemory(uint32_t address, uint8_t byte)
{
	uint8_t err = 0;
	if(address>memorySize)
	{
		#ifdef SW
		fprintf(stderr,"ERROR : address %x outside memory range", address);
		#endif
		err = 1;
	}
	pthread_mutex_lock(&mutex_memory_lock);
	write_to_mem(address,byte);
	pthread_mutex_unlock(&mutex_memory_lock);
	return(err);
}

//last 2 bits of address are ignored
uint8_t getWordInMemory(uint32_t address, uint32_t* rval)
{
	uint8_t err = 0;
	uint32_t result = 0;
	if(address+3 > memorySize)
	{
		#ifdef SW
		fprintf(stderr,"ERROR : address %x outside memory range", address+3);
		#endif
		err = 1;
	}
	//clear last 2 bits in memory
	address=(address>>2)<<2;
	pthread_mutex_lock(&mutex_memory_lock);
	result =  read_from_mem(address);

	result=(result<<8) | read_from_mem(address+1);
	result=(result<<8) | read_from_mem(address+2);
	result=(result<<8) | read_from_mem(address+3);
	pthread_mutex_unlock(&mutex_memory_lock);

	*rval = result;
	return err;
}

uint8_t      setWordInMemory(uint32_t address, uint32_t word, uint8_t byte_mask)
{
	uint8_t err = 0;
	if(address > memorySize)
	{
		#ifdef SW
		fprintf(stderr,"ERROR : address %x outside memory range", address);
		#endif
		err = 1;
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
	return(err);
}


//last 3 bits of address are ignored
uint8_t getDoubleWordInMemory(uint32_t address, uint64_t *rval)
{
	uint8_t err = 0;
	if(address+7 > memorySize)
	{
		#ifdef SW
		fprintf(stderr,"ERROR : address %x outside memory range", address+7);
		#endif
		err = 1;
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
	*rval = result;
	return err;
}

uint8_t    setDoubleWordInMemory(uint32_t address, uint64_t double_word, uint8_t byte_mask)
{
	uint8_t err = 0;
	if(address > memorySize)
	{
		#ifdef SW
		fprintf(stderr,"ERROR : address %x outside memory range", address);
		#endif
		err = 1;
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
	return(err);
}




