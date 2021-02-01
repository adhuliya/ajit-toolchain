#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "memory.h"
#include "pthreadUtils.h"
#include "pipeHandler.h"
#include "Pipes.h"

// reads 16-bit address pipe BRIDGE_to_BOOTMEM_addr
// returns 32-bit word on BOOTMEM_to_BRIDGE_data
void envBootmemDaemon () 
{
	while (1)
	{
		uint16_t addr = read_uint16("BRIDGE_to_BOOTMEM_addr");
		uint32_t data = getWordInMemory(addr);
		write_uint32("BOOTMEM_to_BRIDGE_data", data);
	}
}

DEFINE_THREAD(envBootmemDaemon)
void startBootmemThreads()
{
	register_pipe ("BRIDGE_to_BOOTMEM_addr",1,16,0);
	register_pipe ("BOOTMEM_to_BRIDGE_data",1,32,0);

	PTHREAD_DECL(envBootmemDaemon);
	PTHREAD_CREATE(envBootmemDaemon);
}
