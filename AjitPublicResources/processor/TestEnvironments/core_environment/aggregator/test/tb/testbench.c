#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>
#include <pthread.h>
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


void debugSendDaemon () 
{
	uint32_t idx;
	for(idx = 0; idx < ORDER; idx++)
	{
		write_uint32("ENV_to_AJIT_debug_command", idx);
	}
}

void debugReceiveDaemon () 
{
	uint32_t idx;
	for(idx = 0; idx < ORDER; idx++)
	{
		uint32_t r = read_uint32("AJIT_to_ENV_debug_response");
		if(r != idx)
		{
			fprintf(stderr,"Error: debug-response=0x%x, expected=0x%x.\n",
						r, idx);
		}
		else
			fprintf(stderr,"Info: debug-response=0x%x.\n", r);
	}
}

	
void serialSendDaemon () 
{
	uint8_t idx;
	for(idx = 0; idx < ORDER; idx++)
	{
		write_uint8 ("CONSOLE_to_SERIAL_RX", idx);
	}
}

void serialReceiveDaemon () 
{
	uint8_t idx;
	for(idx = 0; idx < ORDER; idx++)
	{
		uint8_t r = read_uint8("SERIAL_TX_to_CONSOLE");
		if(r != idx)
		{
			fprintf(stderr,"Error: serial-response=0x%x, expected=0x%x.\n",
						r, idx);
		}
		else
			fprintf(stderr,"Info: serial-response=0x%x.\n", r);

	}
}

void modeDaemon () 
{
	while(1)
	{
		uint8_t pmode = read_uint8 ("AJIT_to_ENV_processor_mode");
		usleep (1000);
	}
}

DEFINE_THREAD(debugSendDaemon);
DEFINE_THREAD(debugReceiveDaemon);
DEFINE_THREAD(serialSendDaemon);
DEFINE_THREAD(serialReceiveDaemon);
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
	
	PTHREAD_DECL(debugSendDaemon);
	PTHREAD_DECL(serialSendDaemon);
	PTHREAD_DECL(debugReceiveDaemon);
	PTHREAD_DECL(serialReceiveDaemon);
	PTHREAD_DECL(modeDaemon);

	PTHREAD_CREATE(debugSendDaemon);
	PTHREAD_CREATE(serialSendDaemon);
	PTHREAD_CREATE(debugReceiveDaemon);
	PTHREAD_CREATE(serialReceiveDaemon);
	PTHREAD_CREATE(modeDaemon);


	PTHREAD_JOIN(debugReceiveDaemon);
	PTHREAD_JOIN(serialReceiveDaemon);
	return(0);
}
