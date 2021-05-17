// memory.h
//
// Model for main memory, and routines for its initialization
// using a hexdump file.
//
//AUTHOR : Neha Karanjkar



#include <stdlib.h>
#include <stdint.h>

#ifdef SW
	#include <stdio.h>
#endif



//memory is modeled simply as an array of bytes
//allocated on the heap.
extern uint8_t* memoryArray;

//log of memory size
extern unsigned int  logMemorySize;
extern long unsigned int  memorySize;


//allocate memory on the heap:
//takes argument as log of (memory size in Bytes).
//returns 1 if successful
int allocateMemory(unsigned int log_memory_size);



//initialize memory by reading a hexdump file
//the hexdump file has lines with format:
//(byte address, byte-data) 
//returns 1 on success
int initializeMemory(char* memoryMapFile);


//Helper functions for accessing the memory
uint8_t	 getByteInMemory(uint32_t address);
void     setByteInMemory(uint32_t address, uint8_t byte);
//last 2 bits of address are ignored
uint32_t getWordInMemory(uint32_t address);
void     setWordInMemory(uint32_t address, uint32_t word, uint8_t byte_mask);
//last 3 bits of address are ignored
uint64_t getDoubleWordInMemory(uint32_t address);
void    setDoubleWordInMemory(uint32_t address, uint64_t double_word, uint8_t byte_mask);


