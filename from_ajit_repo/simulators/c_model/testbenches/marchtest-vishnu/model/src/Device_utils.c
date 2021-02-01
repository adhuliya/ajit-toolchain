#include <stdlib.h>
#include <stdint.h>
#include "Ajit_Hardware_Configuration.h"
#include "Pipes.h"
#include "pipeHandler.h"
#include "RequestTypeValues.h"
#include "Ancillary.h"

// #define DEBUG

void getPeripheralAccessCommand(const char* req_pipe,
					uint8_t *rwbar,
					uint8_t *byte_mask,
					uint32_t *address,
					uint32_t *write_data)
{
	uint64_t cmd = read_uint64 (req_pipe);
	*rwbar 		= (cmd >> 63) & 0x1;
	*byte_mask 	= (cmd >> 59) & 0xf;
	*address   	= (cmd >> 32) & 0xffffff;
	*write_data 	= (cmd & 0xffffffff);
#ifdef DEBUG
	fprintf(stderr,"Info:getPeripheralAccessCommand: from pipe %s, rwbar=%d, byte-mask=0x%x, addr=0x%x, wdata=0x%x\n", req_pipe, *rwbar, *byte_mask, *address, *write_data);
#endif
}


void sendPeripheralResponse(const char*  response_pipe, uint32_t send_data)
{
	write_uint32 (response_pipe, send_data);
}

uint32_t insertUsingByteMask (uint32_t old_val, uint32_t new_val, uint8_t byte_mask)
{
	uint32_t wmask = 0;
	if(byte_mask & 0x1)
		wmask = wmask | 0xff;
	if(byte_mask & 0x2)
		wmask = wmask | 0xff00;
	if(byte_mask & 0x4)
		wmask = wmask | 0xff0000;
	if(byte_mask & 0x8)
		wmask = wmask | 0xff000000;

	uint32_t retval = (old_val & (~wmask)) | (new_val & wmask);
	return(retval);
}

