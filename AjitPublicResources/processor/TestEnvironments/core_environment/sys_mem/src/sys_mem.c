#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "BitVectors.h"
#include "memory.h"
#include "pthreadUtils.h"
#include "pipeHandler.h"
#include "Pipes.h"
#include "SockPipes.h"

// to convert arbitrary length pipes into something useful.
#include "simplified_ahb_c_interface__aa_c_model.h"

uint8_t use_socket_flag = 0;
uint8_t verbose_flag = 0;
uint8_t use_simplified_ahb_pipes = 0;
uint32_t memory_address_mask = 0xffffffff;

void setSysmemSocketFlag(uint8_t v)
{
	use_socket_flag = v;
}

void setSysmemVerboseFlag(uint8_t v)
{
	verbose_flag = v;
}

void setSysmemUseSimplifiedAhbPipes(uint8_t v)
{
	use_simplified_ahb_pipes = v;
}

void setSysmemMemAddressMask(uint32_t mem_mask)
{
	memory_address_mask = mem_mask;
}

void getAhbPipeRequest (uint8_t* read_write_bar_8,
				uint8_t* transfer_size,
					uint32_t *addr_32,
						uint32_t* write_data)
{
	uint64_t ctrl_addr;
	if(use_simplified_ahb_pipes)
	{
		uint64_t addr_64 = 0;
		simplified_ahb_c_interface__get_simplified_ahb_command(use_socket_flag,
									 read_write_bar_8,
									 transfer_size,
									 &addr_64,
									 write_data);			
		*addr_32 = addr_64 & memory_address_mask;
	}
	else
	{
		if(use_socket_flag)
		{
			ctrl_addr = sock_read_uint64("BRIDGE_to_AHBLITE_CONTROLLER_CTRL_ADDR");
			*write_data = sock_read_uint32("BRIDGE_to_AHBLITE_CONTROLLER_DATA");
		}
		else
		{
			ctrl_addr = read_uint64("BRIDGE_to_AHBLITE_CONTROLLER_CTRL_ADDR");
			*write_data = read_uint32("BRIDGE_to_AHBLITE_CONTROLLER_DATA");
		}


		*addr_32 = (ctrl_addr & memory_address_mask);

		// transfer type
		//   0  byte
		//   1  2-bytes
		//   2  4-bytes.
		*transfer_size = (ctrl_addr >> 36) & 0x7; // transfer-size

		// read/write is bit 39.
		ctrl_addr = (ctrl_addr >> 39);
		*read_write_bar_8 = (ctrl_addr & 0x1);
	}
}


void doAhbMemAccess (uint8_t read_write_bar, uint8_t transfer_type, 
					uint32_t addr_32, uint32_t write_word, uint8_t *err, uint32_t *read_word)
{
	*err = 0;
	uint32_t ret_word = 0;
	if(read_write_bar)
	{
		*err = getWordInMemory (addr_32, &ret_word);
		if(verbose_flag)
		{
			fprintf(stderr,"Info:sysmem: 0x%x = mem[0x%x]\n", ret_word, addr_32);
		}
	}
	else {
		if(verbose_flag)
		{
			fprintf(stderr,"Info:sysmem: mem[0x%x] = 0x%x [transfer-type=0x%x]\n", addr_32,
							write_word, transfer_type);
		}

		if(transfer_type == 0)
		{
			uint32_t shift_amount = 8*(7 - (addr_32 & 0x3)); 
			uint8_t wbyte = (write_word >> shift_amount) & 0xff;
			uint8_t err_0 = setByteInMemory(addr_32, wbyte);
			*err = *err || err_0;
		}
		else if(transfer_type == 1)
		{
			uint32_t shift_amount = 16*(1 - ((addr_32 >> 1) & 0x1)); 
			uint16_t whword  = (write_word >> shift_amount) & 0xffff;
			uint8_t lbyte = whword & 0xff;
			uint8_t hbyte = (whword >> 8) & 0xff;

			uint8_t err_1 = setByteInMemory	(addr_32, hbyte);
			uint8_t err_2 = setByteInMemory	(addr_32+1, lbyte);

			*err = (err_1 || err_2 || *err);
		}
		else
		{
			*err = setWordInMemory(addr_32, write_word, 0xf);
		}

		ret_word = 0;
	}
	*read_word = ret_word;



	if(*err)
	{
		fprintf(stderr,"Error:sys_mem: max memory address exceeded (read_write_bar=%d, addr=0x%x), wrap-around.\n",
				read_write_bar, addr_32); 
	}

#ifdef DEBUG
	if(verbose_flag)
	{
		fprintf(stderr,"Info:sys_mem: read=0x%x, addr= 0x%x, write_data =0x%x, read_data = 0x%x, err= %x.\n",
				read_write_bar, addr_32, write_word, ret_word, err);
	}
#endif

	return;
}

void sendAhbPipeResponse (uint8_t err, uint32_t ret_word)
{
	if(use_simplified_ahb_pipes)
	{
		simplified_ahb_c_interface__send_simplified_ahb_response(use_socket_flag, err,ret_word);
	}
	else
	{

		// always send a response..
		if(use_socket_flag)
		{
			sock_write_uint32 ("AHBLITE_CONTROLLER_to_BRIDGE_DATA", ret_word);
			sock_write_uint8 ("AHBLITE_CONTROLLER_to_BRIDGE_ERROR", 0);
		}
		else
		{
			write_uint32 ("AHBLITE_CONTROLLER_to_BRIDGE_DATA", ret_word);
			write_uint8  ("AHBLITE_CONTROLLER_to_BRIDGE_ERROR", 0);
		}
	}
}

void envSysmemDaemon ()
{
	while(1)
	{
		uint8_t err = 0;
		uint8_t read_write_bar, transfer_size;
		uint32_t addr_32, write_word, read_word;

		getAhbPipeRequest (&read_write_bar, &transfer_size, &addr_32, &write_word);
		doAhbMemAccess (read_write_bar, transfer_size, addr_32, write_word, &err, &read_word);
		sendAhbPipeResponse (err, read_word);

	}
}

DEFINE_THREAD(envSysmemDaemon);

void startSysmemThreads()
{
	if(use_simplified_ahb_pipes)
	{
		simplified_ahb_c_interface____init_aa_globals__();
	}
	else
	{
		register_pipe ("BRIDGE_to_AHBLITE_CONTROLLER_CTRL_ADDR", 2, 64, 0);
		register_pipe ("BRIDGE_to_AHBLITE_CONTROLLER_DATA", 2, 32, 0);

		register_pipe ("AHBLITE_CONTROLLER_to_BRIDGE_DATA", 2, 32, 0);
		register_pipe ("AHBLITE_CONTROLLER_to_BRIDGE_ERROR", 2, 8, 0);
	}

	PTHREAD_DECL(envSysmemDaemon);
	PTHREAD_CREATE(envSysmemDaemon);
}

