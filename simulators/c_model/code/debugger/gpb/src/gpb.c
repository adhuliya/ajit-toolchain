
/*
 * GDB server bridge that communicates with GDB through sockets
 * on the host machine and translates them to debug link
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "GDBtoAJITbridge.h"
#include "StartGPBThreads.h"
#include "spi_common.h"


int gpb_core (void* vgpb_state)
{
	gpbState* gpb_state = (gpbState*) vgpb_state;

	char packet[4096];

	gsb_cmd gdb_cmd = {.type = 1, .cmd = 'e', .address = 0, .data = 0};

	fprintf(stderr,"\nINFO:gpb_core: Starting the server for CPU %d, port %d", 
				gpb_state->cpu_id, gpb_state->port_number);

	// Initialise the software server
	assert(gpb_state->port_number > 0);
	gpb_init (gpb_state);

	while (1)	{

		gsb_receive(gpb_state, &gdb_cmd);

		gsb_compute_response(gpb_state, &gdb_cmd, packet);

		if ( strcmp(packet, "T09") == 0)	// Print "AJIT: Trap Occured" on GDB
		{
			gsb_send(gpb_state, "O0A414A49543A2054726170204F6363757265640A");
			strcpy(packet,"T05");
		}
		else if ( strcmp(packet, "T02") == 0)	// Print "AJIT: Interrupt" on GDB
		{
			gsb_send(gpb_state, "O0A414A49543A20496E746572727570740A");
		}
		gsb_send(gpb_state, packet);

#ifdef GDB_DBG
		printf("---------------------------------------------------------------------------------------------------\n");
#endif
	}

}


