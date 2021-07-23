#ifndef __GPB__
#define __GPB__
#include <stdint.h>

typedef struct _gpbState {

	uint32_t core_id;
	uint32_t thread_id;

	int port_number;
	int socket_number;

	// Array to store 16 breakpoints and 16 watchpoints
	uint32_t gpb_BP_list[16];
	uint32_t gpb_WP_list[16];

	// One location corresponding to the validity of each break / watch points ( '1' means active and '0' means cleared )
	int gpb_BP_valid[16];
	int gpb_WP_valid[16];


	char command_pipe[256];
	char response_pipe[256];

	// Holds the previous RSP command serviced
	char prev_cmd[4096];
	int command_count;
	// Holds the ID for previous halt
	char prev_halt;
} gpbState;

gpbState* makeGpbState (uint32_t core_id, uint32_t thread_id, int port_number);

// s=1 to use DebugServer.
//   0 otherwise.
void setUseDebugServer(int s);
int getUseDebugServer();
		

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
} gsb_cmd;

int gpb_core(void*);

// Connect to a particular socket on the PC and initiate communication
int gpb_init (gpbState* gpb_state);


// Receive one GDB to Server Bridge packet and decode it
int gsb_receive (gpbState* gpb_state, gsb_cmd *recvd_cmd);

// Compute the response for a given GDB to Server Bridge packet
int gsb_compute_response(gpbState* gpb_state, gsb_cmd *cmd_in, char *rsp_out);

// Send the response packet back through the GDB to Server Bridge link
int gsb_send(gpbState* gpb_state, char *send_msg);

int gpb_set_bp(gpbState* gpb_state, uint32_t address, uint8_t *reg_num);
int gpb_set_wp(gpbState* gpb_state, uint32_t address, uint8_t* reg_num);
int gpb_clear_bp(gpbState* gpb_state, uint32_t address);
int gpb_clear_wp(gpbState* gpb_state, uint32_t address);

#endif
