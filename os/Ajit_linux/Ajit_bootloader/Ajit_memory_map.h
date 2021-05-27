//Ajit_memory_map.h

#ifndef AJIT_MEMORY_MAP_H
#define AJIT_MEMORY_MAP_H

//Available physical memory:
#ifndef MAPTOHIGH
#define RAM_START 0x00000000
#define RAM_NUM_BYTES 0x08000000 
#define RAM_LAST_ADDR 0x08000000
#define BOOTLOADER_INITIAL_STACK_POINTER 0x00003000
#else
#define RAM_START 0xf0000000
#define RAM_NUM_BYTES 0x08000000 
#define RAM_LAST_ADDR 0xf8000000
#define BOOTLOADER_INITIAL_STACK_POINTER 0xf0003000
#endif


//Constants assumed by Linux kernel.
//These are not parameterizable...Do not change.
#define KERNEL_START   0xf0004000 //virtual address of start of kernel
#ifndef MAPTOHIGH
#define KERNEL_OFFSET  0xf0000000 //offset to be added to phy addr of kernel symbols
#else
#define KERNEL_OFFSET  0x00000000 // no offset.
#endif

#endif

