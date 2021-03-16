#ifndef __GPB__
#define __GPB__
#include <stdint.h>
/*
 * The functions and data structures to be used
 * for communicating over the gdb to server and server to processor interfaces.
 */

// Data structure to represent GDB to Server Bridge commands
typedef struct rsp_link_command	{
	int type;
	char cmd;
	uint32_t address;
	uint32_t data; 	
}gsb_cmd;

// Connect to a particular socket on the PC and initiate communication
int gpb_init (int port, int *socket_no);

// Receive one GDB to Server Bridge packet and decode it
int gsb_receive (int socket_no, gsb_cmd *recvd_cmd);

// Compute the response for a given GDB to Server Bridge packet
int gsb_compute_response(gsb_cmd *cmd_in, char *rsp_out);

// Send the response packet back through the GDB to Server Bridge link
int gsb_send(int socket_no, char *send_msg);

int gpb_set_bp(uint32_t address, uint8_t *reg_num);
int gpb_set_wp(uint32_t address, uint8_t* reg_num);
int gpb_clear_bp(uint32_t address);
int gpb_clear_wp(uint32_t address);

#endif
