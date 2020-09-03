#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <pipeHandler.h>
#include "rlut.h"


void icacheDaemon()
{
	while(1)
	{
		uint32_t va = read_uint32("RLUT_to_ICACHE_invalidate");
		fprintf(stderr,"\nICACHE: invalidate line 0x%x\n", va);
	}
}
DEFINE_THREAD(icacheDaemon);

void dcacheDaemon()
{
	while(1)
	{
		uint32_t va = read_uint32("RLUT_to_DCACHE_invalidate");
		fprintf(stderr,"\nDCACHE: invalidate line 0x%x\n", va);
	}
}
DEFINE_THREAD(dcacheDaemon);

int main (int argc, char* argv [])
{
	registerRlutPipes();

	PTHREAD_DECL(icacheDaemon);
	PTHREAD_DECL(dcacheDaemon);

	PTHREAD_CREATE(icacheDaemon);
	PTHREAD_CREATE(dcacheDaemon);

	startRlutDaemon ();

	uint64_t mmu_cmd = constructMmuCommand (1,0,8,0x0,0x0);
	write_uint64 ("MMU_to_RLUT_command", mmu_cmd);

	constructMmucommand (1,0,10,0x1,0x1);
	write_uint64 ("MMU_to_RLUT_command", mmu_cmd);

	constructMmucommand (1,0,10,0x2,0x2);
	write_uint64 ("MMU_to_RLUT_command", mmu_cmd);



	write_uint32("BIU_to_RLUT_invalidate", 0x0);
	write_uint32("BIU_to_RLUT_invalidate", 0x1);
	write_uint32("BIU_to_RLUT_invalidate", 0x2);

	PTHREAD_JOIN(icacheDaemon);
	PTHREAD_JOIN(dcacheDaemon);
	
}

