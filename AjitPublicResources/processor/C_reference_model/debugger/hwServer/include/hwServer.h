#ifndef __HWSERVER__
#define __HWSERVER__
#include <stdint.h>

#include "SparcCore.h"
#include "RegisterFile.h"
/*
 * The functions and data structures to be used
 * for communicating over the server to processor interfaces.
 */

// Data structures to represent Server to Processor Interface commands
typedef struct debug_link_command	{
	uint8_t opcode;
	uint16_t command;
	uint32_t address;
	uint32_t data;
}spi_cmd;

typedef struct debug_link_response	{
	char rsp;
	int id;
	uint32_t data;
}spi_rsp;

// Establish connection with GDB server bridge
int connect_gsb();

// Send and receive Server to Processor Interface commands
int recv_spi(spi_cmd *cmd_out);
int send_spi(spi_rsp *rsp_in);

// Main function describing the hardware server

// Hardware server thread
int runServer();

int execute_spi(ProcessorState *ajit_state, spi_cmd *cmd_exe);	// Execute a single SPI command

int check_for_bp(uint32_t address);		// Check for the existance of a break point

int clear_bp(uint32_t address);		// clear a break point

int set_bp(uint8_t reg_id, uint32_t address);		// Set a breakpoint

int check_for_wp(uint32_t address);		// Check for the existance of a watch point

int clear_wp(uint32_t address);		// clear a watch point

int set_wp(uint8_t reg_id, uint32_t address);		// Set a watchpoint

#endif
