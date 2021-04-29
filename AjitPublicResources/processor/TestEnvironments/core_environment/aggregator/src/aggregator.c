#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "pipeHandler.h"
#include "Pipes.h"
#include "SockPipes.h"
#include "pthreadUtils.h"
#include "aggregator.h"
#include "spi.h"
#include "processor_link.h"

SpiMasterDevice debug_spi_master;
SpiMasterDevice serial_spi_master;

void listenOnDebugCommandDaemon()
{
	while(1)
	{
		uint32_t dbg_cmd = read_uint32("ENV_to_AJIT_debug_command"); 
#ifdef DEBUG
		fprintf(stderr,"Info:aggregator:listenOnDebugCommandDaemon received command 0x%x\n", dbg_cmd);
#endif
		uint64_t nb_dbg_cmd = dbg_cmd;
		nb_dbg_cmd = (nb_dbg_cmd << 8) | ((uint64_t) 1);
		write_uint64  ("noblock_from_debug_command", nb_dbg_cmd);
	}
}

void debugSpiMasterDaemon()
{

	initSpiMasterDeviceStruct(&debug_spi_master,"debug_spi_master", "noblock_debug_to_cpu", "cpu_to_debug");
	writeSpiMasterLowDataByte(&debug_spi_master, 0);

	while(1)
	{
		uint64_t nb_debug_cmd = read_uint64("noblock_from_debug_command");
		uint64_t valid_64 = nb_debug_cmd & 0x1;
		uint64_t debug_cmd_64 = (nb_debug_cmd >> 8);
		uint32_t debug_cmd = debug_cmd_64;
#ifdef DEBUG
		if(valid_64)
			fprintf(stderr,"Info:aggregator:debugSpiDaemon received-debug-command 0x%x\n", debug_cmd);
#endif

		if(valid_64)
		{
			uint8_t d0 = (debug_cmd >> 24);
			uint8_t d1 = (debug_cmd >> 16) & 0xff;
			uint8_t d2 = (debug_cmd >> 8) & 0xff;
			uint8_t d3 = debug_cmd & 0xff;

			// scan in the command bytes.  it is guaranteed that
			// there will be no non-zero response until these
			// four bytes have been scanned in.
			// 
			// These will eventually reach the CPU.
			//
			sendByteAsHexViaSpiMaster(&debug_spi_master,  d0, 0);
			sendByteAsHexViaSpiMaster(&debug_spi_master,  d1, 0);
			sendByteAsHexViaSpiMaster(&debug_spi_master,  d2, 0);
			sendByteAsHexViaSpiMaster(&debug_spi_master,  d3, 0);
			writeSpiMasterLowDataByte(&debug_spi_master, 0);
		}
		


		// check if 4 bytes are available.
		uint32_t resp_32;
		uint8_t no_u32 =  getHexU32FromQueue(&debug_spi_master,0, &resp_32);
		if(no_u32)
		{
			// try to read back a byte.
			executeSpiMasterTransfer (&debug_spi_master, 0);	
		}
		else
		{
				write_uint32("AJIT_to_ENV_debug_response", resp_32);
#ifdef DEBUG
				fprintf(stderr,"Info:aggregator:debugSpiDaemon sent-debug-response 0x%x\n", resp_32);
#endif
		}
			
		usleep(1);
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
		write_uint16  ("noblock_from_console", ((((uint16_t) cbyte) << 8) | 1));
	}
}

void consoleDaemon()
{
	initSpiMasterDeviceStruct(&serial_spi_master,"serial_spi_master", "noblock_serial_to_cpu", "cpu_to_serial");
	writeSpiMasterLowDataByte(&serial_spi_master, 0);

	while(1)
	{
		uint16_t from_console = read_uint16("noblock_from_console");
		uint8_t console_valid = from_console & 0x1;
		uint8_t console_byte  = (from_console >> 8);

		if(console_valid)
		{
			uint8_t h0, h1;
			convertToHex(console_byte, &h0, &h1);	
			writeSpiMasterLowDataByte(&serial_spi_master, h0);
			executeSpiMasterTransfer(&serial_spi_master, 0);	
			writeSpiMasterLowDataByte(&serial_spi_master, h1);
			executeSpiMasterTransfer(&serial_spi_master, 0);	
			writeSpiMasterLowDataByte(&serial_spi_master, 0);
		}

		uint8_t rx_byte;
		uint8_t no_byte  = getHexByteFromQueue(&serial_spi_master, 0, &rx_byte);
		if(no_byte)
		{
			executeSpiMasterTransfer(&serial_spi_master, 0);	
		}
		else
		{
				write_uint8("SERIAL_TX_to_CONSOLE",rx_byte);
#ifdef DEBUG
				fprintf(stderr,"Info:aggregator:serialTxDaemon sent-console-byte 0x%x\n", rx_byte);
#endif
		}
		usleep(1);
	}
}

//
// TODO: figure out a way to send GPIO data to the CPU
//
void sendToCpu ()
{
	uint16_t d_halfword = read_uint16("noblock_debug_to_cpu");
	uint16_t c_halfword = read_uint16("noblock_serial_to_cpu");

	uint8_t valids = ((((c_halfword != 0) ? 1 : 0) << 1) | ((d_halfword != 0) ? 1 : 0));

	uint8_t rbyte = read_uint8("ENV_to_AJIT_reset");
	uint8_t gpio_in = read_uint8("ENV_to_AJIT_gpio_in");

	// 64-bit word split as follows
	// 8       8         8          16          16       8
	// unused gpio_in reset_val serial_data debug_data valids
	// 
	uint64_t send_word = gpio_in;
	send_word = (send_word << 8) | rbyte;
	send_word = (send_word << 16) | ((uint64_t) c_halfword); 
	send_word = (send_word << 16) | ((uint64_t) d_halfword); 
	send_word = (send_word << 8) | valids;
	

#ifdef DEBUG
	fprintf(stderr,"Info:aggregator:sendToCpuDaemon: received 0x%x from noblock_debug_to_cpu.\n",
			d_halfword);
	fprintf(stderr,"Info:aggregator:sendToCpuDaemon: received 0x%x from noblock_serial_to_cpu.\n",
			c_halfword);
#endif

	int tx_status = send_u64_to_processor(&send_word);
	assert (tx_status == 0);

#ifdef DEBUG
	if(valids != 0)
		fprintf(stderr,"Info:aggregator:sendToCpuDaemon: sent 0x%llx on RIFFA_to_CPU.\n", send_word);
#endif

}

uint32_t receiveFromCpu(uint16_t last_counter, uint8_t* last_cpu_mode, uint8_t* last_gpio_out)
{
	uint16_t ret_val = last_counter;
	uint64_t rx_word = 0;

	int rx_status = recv_u64_from_processor(&rx_word);
	assert (rx_status == 0);

	uint64_t counter_64 = (rx_word >> 48);
	uint32_t counter = counter_64;

	// observed counter values must be strictly increasing.
	if(counter == 0)
	{
		fprintf(stderr,"Warning: zero-counter word from processor ignored.\n");
		return(ret_val);;
	}
	else
	{
		uint16_t nc = (last_counter + 1);
		nc = ((nc == 0) ? 1 : nc);
		if(nc != counter)
		{
			fprintf(stderr,"Error: in received word from processor.. expected counter = %d, observed= %d\n",
					nc, counter);
		}

		ret_val = counter;
	}

	uint8_t valids = rx_word & 0xff;
	uint8_t debug_data = (rx_word >> 8) & 0xff;
	uint8_t serial_data = (rx_word >> 16) & 0xff;
	uint8_t cpu_mode = (rx_word >> 24) & 0xff;
	uint8_t gpio_out = (rx_word >> 32) & 0xff;
#ifdef DEBUG
	if(valids != 0)
	{
		fprintf(stderr,"Info:aggregator:listenOnCpuDaemon: received 0x%llx on CPU_to_RIFFA.\n", rx_word);
		fprintf(stderr,"Info:aggregator:listenOnCpuDaemon: valids=0x%x, debug_data=0x%x, serial_data=0x%x, processor_mode = 0x%x, gpio_out = 0x%x\n", valids, debug_data, serial_data, cpu_mode, gpio_out);
	}
#endif

	if(cpu_mode != *last_cpu_mode)
	{
		fprintf(stderr,"Info:aggregator:listenOnCpuDaemon: cpu mode changed to 0x%x from 0x%x.\n",
				cpu_mode, *last_cpu_mode);
		*last_cpu_mode = cpu_mode;
	}
	write_uint8("AJIT_to_ENV_processor_mode", cpu_mode);

	if(gpio_out != *last_gpio_out)
	{
		fprintf(stderr,"Info:aggregator:listenOnCpuDaemon: gpio_out changed to 0x%x from 0x%x.\n",
				gpio_out, *last_gpio_out);
		*last_gpio_out = gpio_out;
	}
	write_uint8("AJIT_to_ENV_gpio_out", gpio_out);


	uint8_t serial_valid = (valids >> 1);
	uint8_t debug_valid = valids & 0x1;

	if(serial_valid)
		write_uint8("cpu_to_serial", serial_data);

	if(debug_valid)
		write_uint8("cpu_to_debug", debug_data);

	return(ret_val);
}


void aggregatorDaemon()
{
	uint8_t pmode = 0;
	uint8_t gpio_out = 0;
	uint16_t counter = 0;
	while(1)
	{
		sendToCpu();
		counter = receiveFromCpu(counter, &pmode, &gpio_out);
	}
}


// register pipes, start threads
// pipes
//   noblock_debug_to_cpu  w=16, d=8
//   cpu_to_debug	   w=8,  d=64
//
//   noblock_serial_to_cpu w=16, d=8
//   cpu_to_serial	   w=8,  d=64
//
//   
DEFINE_THREAD(listenOnDebugCommandDaemon);
DEFINE_THREAD(debugSpiMasterDaemon);
DEFINE_THREAD(listenOnSerialRxDaemon);
DEFINE_THREAD(consoleDaemon);
DEFINE_THREAD(aggregatorDaemon);

PTHREAD_DECL(listenOnDebugCommandDaemon);
PTHREAD_DECL(debugSpiMasterDaemon);
PTHREAD_DECL(listenOnSerialRxDaemon);
PTHREAD_DECL(consoleDaemon);
PTHREAD_DECL(aggregatorDaemon);

void startAggregatorDaemons()
{
	register_signal ("ENV_to_AJIT_reset", 8);
	register_signal ("ENV_to_AJIT_gpio_in", 8);
	register_signal ("AJIT_to_ENV_gpio_out", 8);

	register_pipe ("noblock_debug_to_cpu", 64, 16, PIPE_FIFO_NON_BLOCK_READ);
	register_pipe ("noblock_from_console", 64, 16, PIPE_FIFO_NON_BLOCK_READ);
	register_pipe ("noblock_from_debug_command", 64, 64, PIPE_FIFO_NON_BLOCK_READ);
	register_pipe ("cpu_to_debug", 64, 8, PIPE_FIFO_MODE);

	register_pipe ("noblock_serial_to_cpu", 64, 16, PIPE_FIFO_NON_BLOCK_READ);
	register_pipe ("cpu_to_serial", 64, 8, PIPE_FIFO_MODE);



	PTHREAD_CREATE(listenOnDebugCommandDaemon);
	PTHREAD_CREATE(debugSpiMasterDaemon);
	PTHREAD_CREATE(listenOnSerialRxDaemon);
	PTHREAD_CREATE(consoleDaemon);
	PTHREAD_CREATE(aggregatorDaemon);
}

void stopAggregatorDaemons()
{
	PTHREAD_CANCEL(listenOnDebugCommandDaemon);
	PTHREAD_CANCEL(debugSpiMasterDaemon);
	PTHREAD_CANCEL(listenOnSerialRxDaemon);
	PTHREAD_CANCEL(consoleDaemon);
	PTHREAD_CANCEL(aggregatorDaemon);
}


