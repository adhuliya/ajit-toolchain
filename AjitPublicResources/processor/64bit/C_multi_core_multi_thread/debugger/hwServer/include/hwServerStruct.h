#ifndef __HWSERVER_STRUCT__
#define __HWSERVER_STRUCT__
#include <stdint.h>
typedef struct __hwServerState {
	uint32_t core_id;
	uint32_t thread_id;

	// Array to store 16 breakpoints and 16 watchpoints
	uint32_t BP_list[16];
	uint32_t WP_list[16];
	// One location corresponding to the validity of each break / watch points ( '1' means active and '0' means cleared )
	int BP_valid[16];
	int WP_valid[16];

	int Debug_status;

	char thread_to_hwserver_id_pipe_name[256];
	char thread_to_hwserver_state_pipe_name[256];

	char hwserver_to_thread_pipe_name[256];

	char debug_command_pipe_name[256];
	char debug_response_pipe_name[256];

} hwServerState;
hwServerState* makeHwServerState(uint32_t core_id, uint32_t  thread_id);

#endif
