//A testbench for testing routines in memory.h
//
//AUTHOR: Neha Karanjkar
#include"memory.h"
#include<stdio.h>

int main(int argc, char** argv)
{
	if(argc<2) 
	{
		printf("\n enter log_memory_size as argument");
		exit(1);
	}

	printf("\n In memoryTestbench.c");
	unsigned int log_size=atoi(argv[1]);
	int success = allocateMemory(log_size);
	if(!success)
	{
		printf("\n Failure to allocate memory!");
		exit(1);
	}
	else
	{
		printf("\n Allocated memory of size %lu Bytes\n",memorySize);
		initializeMemory("test_memmap_input.txt");

		
		//test memory helper routines
		uint32_t address = 0xf0004000;
		printf("\naddress	= %8x",address);
		printf("\nByte		= 0x%4x", getByte(address));
		printf("\nWord		= 0x%8x", getWord(address));
		printf("\ndoubleWord	= 0x%16lx", getDoubleWord(address));
		

		setDoubleWord(address, 0x0000000000000000, 0xFFFF);
		printf("\ndoubleWord	= 0x%16lx", getDoubleWord(address));
		
		//check setByte
		setByte(address, 0x01);
		setByte(address+1, 0x02);
		setByte(address+2, 0x03);
		setByte(address+3, 0x04);
		printf("\ndoubleWord	= 0x%16lx", getDoubleWord(address));
		
		//check setWord
		setWord(address, 0xEEEEEEEE,0xA); 
		printf("\ndoubleWord	= 0x%16lx", getDoubleWord(address));
		
		//check setDoubleword
		setDoubleWord(address, 0xBBBBBBBBBBBBBBBB, 0x55);
		printf("\ndoubleWord	= 0x%16lx", getDoubleWord(address));
		
		free(memoryArray);
	}
	printf("\n");
	return 0;
};
