#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <pipeHandler.h>
#include "aggregator.h"
#include "processor_link.h"

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

	uint8_t   riffa_flag = 0;
	int opt;
	while ((opt = getopt(argc, argv, "F")) != -1) {
		switch(opt) {
			case 'F':
				riffa_flag = 1;
				break;
			default: 
				fprintf(stderr,"Error: unknown option %c\n", opt);
				break;
		}
	}

	if(riffa_flag)
	{
		int link_status = set_processor_link (PROCESSOR_RIFFA_LINK);
		assert(link_status == 0);
	}

	init_pipe_handler();
	startAggregatorDaemons();
	
	PTHREAD_DECL(modeDaemon);
	PTHREAD_CREATE(modeDaemon);

	write_uint8 ("CONSOLE_to_SERIAL_RX", 'a');
	uint8_t r0 = read_uint8("SERIAL_TX_to_CONSOLE");
	if(r0 == 'a')
		fprintf(stderr,"Got a.\n");

	write_uint8 ("CONSOLE_to_SERIAL_RX", 'b');
	uint8_t r1 = read_uint8("SERIAL_TX_to_CONSOLE");
	if(r1 == 'b')
		fprintf(stderr,"Got b.\n");
		

	return(0);
}
