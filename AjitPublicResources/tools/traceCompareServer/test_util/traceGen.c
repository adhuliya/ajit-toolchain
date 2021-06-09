#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <pthreadUtils.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <SocketLib.h>
#include <unistd.h>


// generate a trace of consecutive integers to send to traceCompareServer.
// the numbers sent are 
//  0+offset, 1+offset, 2+offset, ...., 1023+offset
// use the offset argument to shift the numbers being sent.
int main (int argc, char* argv[])
{
	int err_val = 0;
	int offset = 0;
	if(argc < 3)
	{
		fprintf(stderr,"%s <ip-address> <port-number> <offset> \n", argv[0]);
		fprintf(stderr,"for example: %s 127.0.0.1 9999 0\n", argv[0]);
		return(1);
	}
	char* ip_address = argv[1];
	int port_id      = atoi(argv[2]);
	if(argc > 3)
		offset = atoi(argv[3]);
	
	uint32_t send_val = 0;
	uint32_t I;
	for(I = 0; I < 1024; I++)
	{
		send_val = I+offset;
		send_packet_and_wait_for_response((char*) &send_val, 4, ip_address, port_id);
		if((*((char*) &send_val)) != 0)
		{
			fprintf(stderr,"Error: wrong ack val from server %s, port %d.\n", 
						ip_address, port_id);
			err_val = 1;
			break;
		}
		fprintf(stderr,"Info: sent and received to ip_address %s, port %d.\n", 
					ip_address, port_id);
	}

	return(err_val);
}

