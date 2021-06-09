#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "pipeHandler.h"
#include "Pipes.h"
#include "SockPipes.h"
#include "pthreadUtils.h"
#include "aggregator.h"
#include "processor_link.h"


void listenOnDebugCommandDaemon()
{
	while(1)
	{
		uint32_t dbg_cmd = read_uint32("ENV_to_AJIT_debug_command"); 
#ifdef DEBUG
		fprintf(stderr,"Info:aggregator:listenOnDebugCommandDaemon received command 0x%x\n", dbg_cmd);
#endif
		uint16_t byte_3 = (dbg_cmd >> 24) & 0xff;
		uint16_t byte_2 = (dbg_cmd >> 16) & 0xff;
		uint16_t byte_1 = (dbg_cmd >> 8) & 0xff;
		uint16_t byte_0 = dbg_cmd & 0xff;
	
		write_uint16  ("noblock_from_debug_command", (byte_3 | 0x100));
		write_uint16  ("noblock_from_debug_command", (byte_2 | 0x100));
		write_uint16  ("noblock_from_debug_command", (byte_1 | 0x100));
		write_uint16  ("noblock_from_debug_command", (byte_0 | 0x100));

	}
}

// return 1 on valid command-byte
uint8_t probeDebugCommand (uint8_t* debug_cmd_byte)
{
	uint16_t nb_debug_cmd = read_uint16("noblock_from_debug_command");
	uint8_t valid = nb_debug_cmd >> 8;
	*debug_cmd_byte = (nb_debug_cmd & 0xff);
#ifdef DEBUG
	if(valid)
		fprintf(stderr,"Info:aggregator:probeDebugCommand: debug_command-byte= 0x%x\n", debug_cmd);
#endif
	return(valid);
}

		
void sendDebugResponse(uint8_t debug_data)
{
	static int counter = 0;
	static uint32_t send_word = 0;

#ifdef DEBUG
		fprintf(stderr,"Info:aggregator:sendDebugResponse: debug_response-byte= 0x%x\n", debug_data);
#endif

	send_word = (send_word << 8) | debug_data;
	counter++;
	if(counter == 4)
	{
		write_uint32("AJIT_to_ENV_debug_response", send_word);
		counter = 0;
		send_word = 0;
#ifdef DEBUG
		fprintf(stderr,"Info:aggregator:sendDebugResponse: debug_response-word= 0x%x\n", send_word);
#endif
	}
}

// listen on CONSOLE_to_SERIAL_Rx pipe. As soon
// as you get a byte, send it to noblock_console_to_cpu
// pipe.
void listenOnSerialRxDaemon()
{
	while(1)
	{
		uint8_t cbyte = read_uint8("CONSOLE_to_SERIAL_RX"); 
#ifdef DEBUG
		fprintf(stderr,"Info:aggregator:serialRxDaemon received-console-byte 0x%x\n", cbyte);
#endif
		uint16_t u16_cbyte = cbyte;
		u16_cbyte = u16_cbyte | 0x100;
		write_uint16  ("noblock_from_console", u16_cbyte);
	}
}

uint8_t probeConsole(uint8_t *serial_byte_in)
{
	uint16_t from_console = read_uint16("noblock_from_console");
	uint8_t console_valid = (from_console >> 8);
	uint8_t console_byte  = (from_console & 0xff);

#ifdef DEBUG
	if(console_valid)
		fprintf(stderr,"Info:aggregator:probeConsole console-byte= 0x%x\n", console_byte);
#endif
	*serial_byte_in = console_byte;
	return(console_valid);
}
      
//
// TODO: figure out a way to send GPIO data to the CPU
//
void sendToCpu ()
{
	uint8_t debug_command_byte = 0;
	uint8_t debug_valid = probeDebugCommand(&debug_command_byte);

	uint8_t serial_byte = 0;
	uint8_t serial_valid = probeConsole (&serial_byte);

	uint8_t valids = ((serial_valid << 1) | debug_valid);

	uint8_t rbyte = read_uint8("ENV_to_AJIT_reset");

	// 64-bit word split as follows
	// 32       8          8          8        8
	// unused reset_val serial_data debug_data valids
	// 
	uint64_t send_word = rbyte;
	send_word = (send_word << 8) | serial_byte;
	send_word = (send_word << 8) | debug_command_byte;
	send_word = (send_word << 8) | valids;
	


	int tx_status = send_u64_to_processor(&send_word);
	assert (tx_status == 0);

#ifdef DEBUG
	if(valids != 0)
		fprintf(stderr,"Info:aggregator:sendToCpu: sent 0x%llx on RIFFA_to_CPU.\n", send_word);
#endif

}

uint8_t receiveFromCpu(uint8_t last_counter, uint8_t* last_cpu_mode, uint8_t* last_gpio_out)
{
	uint8_t ret_val = last_counter;
	uint64_t rx_word = 0;

	// rx_status format.
	// counter  logger-data serial-data debug-data ZERO3 chip-mode log-valid serial-valid debug-valid
	//  8            32          8        8         3         2        1         1             1
	int rx_status = recv_u64_from_processor(&rx_word);
	assert (rx_status == 0);

	uint64_t counter_64 = (rx_word >> 56);
	uint8_t counter = counter_64 & 0xff;

	// observed counter values must be strictly increasing.
	if(counter == 0)
	{
		fprintf(stderr,"Warning: zero-counter word from processor ignored.\n");
		return(ret_val);;
	}
	else
	{
		uint8_t nc = (last_counter + 1);
		nc = ((nc == 0) ? 1 : nc);
		if(nc != counter)
		{
			fprintf(stderr,"Error: in received word from processor.. expected counter = %d, observed= %d\n",
					nc, counter);
		}

		ret_val = counter;
	}

	// format of u64 from cpu is
	// counter  logger-data serial-data debug-data ZERO3 chip-mode log-valid serial-valid debug-valid
	//  8            32          8        8         3         2        1         1             1
	uint8_t valids = rx_word & 0xff;
	uint8_t debug_data = (rx_word >> 8) & 0xff;
	uint8_t serial_data = (rx_word >> 16) & 0xff;
	uint8_t cpu_mode = (valids >> 3) & 0x3;
	uint32_t logger_data = (rx_word >> 24) & 0xffffffff;

#ifdef DEBUG
	if(valids != 0)
	{
		fprintf(stderr,"Info:aggregator:receiveFromCpu: received 0x%llx on CPU_to_RIFFA.\n", rx_word);
		fprintf(stderr,"Info:aggregator:receiveFromCpu: valids=0x%x, debug_data=0x%x, serial_data=0x%x, processor_mode = 0x%x.\n", valids, debug_data, serial_data, cpu_mode);
	}
#endif

	if(cpu_mode != *last_cpu_mode)
	{
		fprintf(stderr,"Info:aggregator:receiveFromCpu: cpu mode changed to 0x%x from 0x%x.\n",
				cpu_mode, *last_cpu_mode);
		*last_cpu_mode = cpu_mode;
	}
	write_uint8("AJIT_to_ENV_processor_mode", cpu_mode);


	uint8_t logger_valid = (valids >> 2) & 0x1;
	uint8_t serial_valid = (valids >> 1) & 0x1;
	uint8_t debug_valid  = valids & 0x1;

	if(serial_valid)
		write_uint8("SERIAL_TX_to_CONSOLE", serial_data);

	if(debug_valid)
		sendDebugResponse(debug_data);

	if(logger_valid)
		write_uint32("AJIT_to_ENV_logger", logger_data);

	return(ret_val);
}


void aggregatorDaemon()
{
	uint8_t pmode = 0;
	uint8_t gpio_out = 0;
	uint8_t counter = 0;
	while(1)
	{
		sendToCpu();
		counter = receiveFromCpu(counter, &pmode, &gpio_out);
	}
}


// register pipes, start threads
// pipes
//
//   noblock_serial_to_cpu w=16, d=8
//   cpu_to_serial	   w=8,  d=64
//
//   
DEFINE_THREAD(listenOnDebugCommandDaemon);
DEFINE_THREAD(listenOnSerialRxDaemon);
DEFINE_THREAD(aggregatorDaemon);

PTHREAD_DECL(listenOnDebugCommandDaemon);
PTHREAD_DECL(listenOnSerialRxDaemon);
PTHREAD_DECL(aggregatorDaemon);

void startAggregatorDaemons()
{
	register_signal ("ENV_to_AJIT_reset", 8);
	register_signal ("ENV_to_AJIT_gpio_in", 8);
	register_signal ("AJIT_to_ENV_gpio_out", 8);

	register_pipe ("noblock_from_console", 64, 16, PIPE_FIFO_NON_BLOCK_READ);
	register_pipe ("noblock_from_debug_command", 64, 16, PIPE_FIFO_NON_BLOCK_READ);




	PTHREAD_CREATE(listenOnDebugCommandDaemon);
	PTHREAD_CREATE(listenOnSerialRxDaemon);
	PTHREAD_CREATE(aggregatorDaemon);
}

void stopAggregatorDaemons()
{
	PTHREAD_CANCEL(listenOnDebugCommandDaemon);
	PTHREAD_CANCEL(listenOnSerialRxDaemon);
	PTHREAD_CANCEL(aggregatorDaemon);
}


