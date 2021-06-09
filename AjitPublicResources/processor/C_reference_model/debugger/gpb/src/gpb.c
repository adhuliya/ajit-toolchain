
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

int gdb_port_number = -1;

void setPortNumber(int pn)
{
	gdb_port_number = pn;
}



int gpb ()
{
	int sock_id, port = 0;
	char packet[2048];

	gsb_cmd gdb_cmd = {.type = 1, .cmd = 'e', .address = 0, .data = 0};
	gsb_cmd actv_cmd = {.type = 1, .cmd = 'e', .address = 0, .data = 0};

	puts("Starting the software server..");

	// Initialise the software server
	assert(gdb_port_number > 0);
	gpb_init (gdb_port_number, &sock_id);

	while (1)	{

		gsb_receive(sock_id, &gdb_cmd);

		gsb_compute_response(&gdb_cmd, packet);

		if ( strcmp(packet, "T09") == 0)	// Print "AJIT: Trap Occured" on GDB
		{
			gsb_send(sock_id, "O0A414A49543A2054726170204F6363757265640A");
			strcpy(packet,"T05");
		}
		else if ( strcmp(packet, "T02") == 0)	// Print "AJIT: Interrupt" on GDB
		{
			gsb_send(sock_id, "O0A414A49543A20496E746572727570740A");
		}
		gsb_send(sock_id, packet);

#ifdef GDB_DBG
		printf("---------------------------------------------------------------------------------------------------\n");
#endif
	}

}


