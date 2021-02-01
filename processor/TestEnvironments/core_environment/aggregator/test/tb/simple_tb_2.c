#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <pipeHandler.h>
#include "aggregator.h"

#define ORDER 16
void Exit(int sig)
{
	fprintf(stderr, "## Break! ##\n");
	exit(0);
}


void modeDaemon () 
{
	while(1)
	{
		uint8_t pmode = read_uint8 ("AJIT_to_ENV_processor_mode");
		usleep (1000);
	}
}

DEFINE_THREAD(modeDaemon);

int main(int argc, char* argv[])
{
	uint32_t result[ORDER];
	signal(SIGINT,  Exit);
  	signal(SIGTERM, Exit);
	uint8_t idx;

	init_pipe_handler();
	startAggregatorDaemons();
	
	PTHREAD_DECL(modeDaemon);
	PTHREAD_CREATE(modeDaemon);

	write_uint32 ("ENV_to_AJIT_debug_command", 0x0f0f0f0f);
	uint32_t r0 = read_uint32("AJIT_to_ENV_debug_response");
	if(r0 == 0x0f0f0f0f)
		fprintf(stderr,"Got 0x0f0f0f0f.\n");


	//write_uint32 ("ENV_to_AJIT_debug_command", 0xf0f0f0f0);
	//uint32_t r1 = read_uint32("AJIT_to_ENV_debug_response");
	//if(r1 == 0xf0f0f0f0)
		//fprintf(stderr,"Got 0xf0f0f0f0.\n");
		

	return(0);
}
