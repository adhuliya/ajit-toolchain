#ifndef __SPI_COMMON__
#define __SPI_COMMON__
#include <stdint.h>
/*
 * The functions and data structures to be used
 * for communicating over the server to the Ajit processor.
 */

#define SPI_CONNECT_WITH_PIPEHANDLER 0
#define SPI_CONNECT_WITH_SOCKET      1
#define SPI_CONNECT_WITH_UART        2

void setSpiInConnectSocketMode();
void setSpiInConnectUartMode();
void setSpiMaxMemAddress(uint32_t max_mem_address);


// Data structure to represent Server to Processor Interface commands
typedef struct gpb_debug_link_command	{
	char cmd;
	int reg_id;
	uint32_t address;
	uint32_t data;
}gpb_spi_cmd;

// Data structure to represent Server to Processor Interface responses
typedef struct gpb_debug_link_response	{
	char rsp_cmd[256];
	uint32_t content;
}gpb_spi_rsp;

// Send the data given in 'command' through the server to processor interface
int send_gpb_spi_cmd(gpb_spi_cmd *cmd_ptr);

// Receives the response from server to processor interface and fills the 'response' structure
int recv_gpb_spi_cmd(gpb_spi_rsp *resp_ptr);

#endif
