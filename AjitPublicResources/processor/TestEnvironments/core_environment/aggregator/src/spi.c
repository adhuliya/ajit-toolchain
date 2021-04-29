#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "pipeHandler.h"
#include "Pipes.h"
#include "pthreadUtils.h"
#include "aggregator.h"
#include "spi.h"

//
// Note: commands to SPI master consist of a 16-bit word.
//       with the following fields.
// 15    14:11  10   9:8      7:0 
//  1    0      rw  reg-id  reg-val
//
// The top-bit is to kept 1 so that the all-zero combination
// is avoided.
//
//

MUTEX_DECL(_qmutex__);

void convertToHex(uint8_t b, uint8_t *h0, uint8_t *h1)
{
	uint8_t x0 = b >> 4;
	uint8_t x1 = b & 0xf;
	
	*h0 = TOHEX(x0);
	*h1 = TOHEX(x1);
}

void initHexQueue(HexQueue* q)
{
	pthread_mutex_init (&(q->pm), NULL);
	MUTEX_LOCK(q->pm);
		q->size = 0;
		q->read_pointer = 0;
		q->write_pointer = 0;
		int I;
		for(I = 0; I < HEXQSIZE; I++)
			q->byte_array[I] = 0;
	MUTEX_UNLOCK(q->pm);
}

// return 0 on success.
uint8_t pushToHexQueue(HexQueue* q, uint8_t h)
{
	uint8_t ret_val = 0;
	MUTEX_LOCK(q->pm);
	if(q->size < HEXQSIZE)
	{
		q->byte_array[q->write_pointer] = h;
		q->write_pointer += 1;
		if(q->write_pointer == HEXQSIZE)
			q->write_pointer = 0;
		q->size += 1;
	}
	else
		ret_val = 1;

	MUTEX_UNLOCK(q->pm);
	return(ret_val);
}

// return 0 on success, 1 on empty.
uint8_t popFromHexQueue(HexQueue* q, uint8_t* h)
{
	uint8_t ret_val = 0;
	*h = 0;
	MUTEX_LOCK(q->pm);
	if(q->size > 0)
	{
		*h = q->byte_array[q->read_pointer];
		q->read_pointer += 1;
		if(q->read_pointer == HEXQSIZE)
			q->read_pointer = 0;
		q->size -= 1;
	}
	else
		ret_val = 1;

	MUTEX_UNLOCK(q->pm);
	return(ret_val);
}

void initSpiMasterDeviceStruct (SpiMasterDevice* dev, char* dev_name, char* cmd_pipe, char* resp_pipe)
{
	dev->name = strdup(dev_name);
	dev->command_pipe = strdup(cmd_pipe);
	dev->response_pipe = strdup(resp_pipe);
	int i;
	for(i = 0; i < 8; i++)
		initHexQueue(&(dev->q[i]));
	pthread_mutex_init (&(dev->pm), NULL);	
}

//
// Note: for every command, a response is generated.
//    Thus, it is important to read the response pipe for every
//    write to the command pipe!
//      
void writeSpiMasterLowDataByte(SpiMasterDevice* dev, uint8_t X)
{
	MUTEX_LOCK(dev->pm);
	uint16_t mval = (1 << 15);
	mval = X | mval; // rw=0, addr=0, data=idx.
	write_uint16(dev->command_pipe,mval);
	//usleep (SPI_RESPONSE_DELAY_IN_NS);
	uint8_t rval = read_uint8(dev->response_pipe);
	MUTEX_UNLOCK(dev->pm);
	return;
}

void writeSpiMasterHighDataByte(SpiMasterDevice* dev, uint8_t X)
{
	MUTEX_LOCK(dev->pm);
	uint16_t mval = 1;	

	mval = (mval << 8) | X;
	mval = mval | (1 < 15);

	write_uint16(dev->command_pipe,mval);
	//usleep (SPI_RESPONSE_DELAY_IN_NS);
	uint8_t rval = read_uint8(dev->response_pipe);
	MUTEX_UNLOCK(dev->pm);
	return;
}

//
// Execute SPI master transfer, using cmd-pipe and resp-pipe pair,
// incoming data is pushed to q if it is a hex character.
//
uint8_t executeSpiMasterTransferAndDeselectSlave(SpiMasterDevice* dev, uint8_t slave_id)
{
	uint16_t mval = 0;
	mval = (mval << 2) | 2;
	mval = (mval << 8) | ((slave_id & 0x3) << 4) | 3; // bit 1 is deselect-slave
	mval = mval | (1 << 15);
	MUTEX_LOCK(dev->pm);
	write_uint16(dev->command_pipe,mval);
	//usleep (SPI_RESPONSE_DELAY_IN_NS);
	uint8_t rval = read_uint8(dev->response_pipe);   
	MUTEX_UNLOCK(dev->pm);

	rval = readSpiMasterByte (dev, 0); // read byte 0.
	if(ISHEX(rval)) 
		pushToHexQueue(&(dev->q[slave_id & 0x3]), rval);

	return(rval);
}

//
// Execute SPI master transfer, using cmd-pipe and resp-pipe pair,
// incoming data is pushed to q if it is a hex character.
//
uint8_t executeSpiMasterTransfer(SpiMasterDevice* dev, uint8_t slave_id)
{
	uint16_t mval = 0;
	mval = (mval << 2) | 2;
	mval = (mval << 8) | ((slave_id & 0x3) << 4) |  1;
	mval = mval | (1 << 15);
	MUTEX_LOCK(dev->pm);
	write_uint16(dev->command_pipe,mval);
	//usleep (SPI_RESPONSE_DELAY_IN_NS);
	uint8_t rval = read_uint8(dev->response_pipe);   
	MUTEX_UNLOCK(dev->pm);

	rval = readSpiMasterByte (dev, 0); // read byte 0.
	if(ISHEX(rval)) 
		pushToHexQueue(&(dev->q[slave_id & 0x3]), rval);

	return(rval);
}

void writeSpiMasterConfiguration(SpiMasterDevice* dev,
					 uint8_t transfer_length, uint8_t clk_divide_count)
{
	uint8_t X = transfer_length;
	X = (X << 4) | (clk_divide_count & 0xf);
	uint16_t cmd = 3;
	cmd = (cmd << 8) | X;
	cmd = cmd | (1 << 15);
	MUTEX_LOCK(dev->pm);
	write_uint16(dev->command_pipe, cmd);
	//usleep (SPI_RESPONSE_DELAY_IN_NS);
	uint8_t rval = read_uint8(dev->response_pipe);
	MUTEX_UNLOCK(dev->pm);
}
	
void writeSpiMasterCommandRegister(SpiMasterDevice* dev,
							uint8_t spi_dev_id, 
							uint8_t irq_en, 
							uint8_t deselect_after_xfer,
							uint8_t start_transfer)
{
	uint8_t X = spi_dev_id & 0x7;
	X = (X  << 1) | (irq_en & 0x1);
	X = (X  << 1) | (deselect_after_xfer & 0x1);
	X = (X  << 1) | (start_transfer & 0x1);
	uint8_t cmd = 2; // control register address.
	cmd = (cmd << 8) | X;
	cmd = cmd | (1 << 15); // set the top bit to 1.
	
	MUTEX_LOCK(dev->pm);
	write_uint16(dev->command_pipe,  cmd);
	//usleep (SPI_RESPONSE_DELAY_IN_NS);
	uint8_t rval = read_uint8(dev->response_pipe);
	MUTEX_UNLOCK(dev->pm);
}

// return non-zero byte from SpiMaster.
//   If there is already a hex-char in q, return it.
//   Else, keep transferring bytes from slave to master
//   and stop as soon as you have a hex-char in q.
uint8_t readHexCharFromSpiMaster(SpiMasterDevice* dev, uint8_t slave_id)
{
	uint8_t resp;
	// first, pop from q..
	uint8_t pop_not_ok = popFromHexQueue(&(dev->q[slave_id & 0x3]), &resp);
	if(pop_not_ok)
	{
		writeSpiMasterLowDataByte(dev, 0);
		while (!ISHEX(resp))
		{
			// will update q.
			executeSpiMasterTransfer(dev, slave_id);
			// pop from q.
			pop_not_ok = popFromHexQueue(&(dev->q[slave_id & 0x3]), &resp);
		}
	}
	return(resp);
}

// byte-address 0: lower byte in shift-reg in master.
//              1: upper byte in shift-reg in master.
//              2: status reg (bit 0 indicates busy).
//              3: config reg (reads as 0).
// After you do a byte transfer, you must read reg-0 to
// see what has been scanned n.
uint8_t readSpiMasterByte(SpiMasterDevice* dev, uint8_t byte_address)
{
	uint16_t cmd = 0x1;
	cmd = (cmd << 2) | (byte_address & 0x3);
	cmd = (cmd << 8); // write 0
	cmd = cmd | (1 << 15); // set the top bit to 1.

	MUTEX_LOCK(dev->pm);
	write_uint16(dev->command_pipe, cmd);
	//usleep(SPI_RESPONSE_DELAY_IN_NS);	
	uint8_t ret_val = read_uint8(dev->response_pipe);
	MUTEX_UNLOCK(dev->pm);
	return(ret_val);
}


// spi-master needs a command sequence to transfer a byte.
void sendByteAsHexViaSpiMaster(SpiMasterDevice* dev, uint8_t send_byte, uint8_t slave_id)
{
	uint8_t x0 = send_byte >> 4;
	uint8_t x1 = send_byte & 0xf;

	uint8_t h0 = TOHEX(x0);
	uint8_t h1 = TOHEX(x1);

	writeSpiMasterLowDataByte(dev, h0);
	uint8_t r_h0 = executeSpiMasterTransfer(dev, slave_id);
	writeSpiMasterLowDataByte(dev, h1);
	uint8_t r_h1 = executeSpiMasterTransfer(dev, slave_id);

	writeSpiMasterLowDataByte(dev, 0);
}


uint8_t getByteFromHexViaSpiMaster(SpiMasterDevice* dev, uint8_t slave_id)
{
	uint8_t h0 = readHexCharFromSpiMaster(dev, slave_id);
	uint8_t h1 = readHexCharFromSpiMaster(dev, slave_id);

	uint8_t x = (TOBINARY(h0) << 4) | TOBINARY(h1);
	return(x);
}

// spi-master needs a command sequence to transfer a byte.
uint8_t sendByteViaSpiMaster(SpiMasterDevice* dev, uint8_t send_byte, uint8_t deselect_after_xfer, uint8_t slave_id)
{
	writeSpiMasterLowDataByte(dev, send_byte);
	uint8_t r = 0;

	if(deselect_after_xfer)
		r = executeSpiMasterTransferAndDeselectSlave(dev, slave_id);
	else
		r = executeSpiMasterTransfer(dev, slave_id);

	writeSpiMasterLowDataByte(dev, 0);
	return(r);
}


uint8_t getByteViaSpiMaster(SpiMasterDevice* dev, uint8_t slave_id)
{
	uint8_t x = readSpiMasterByte(dev,0);
	return(x);
}


uint8_t getHexByteFromQueue (SpiMasterDevice* dev, int slave_id, uint8_t* ret_byte)
{
	slave_id = slave_id & 0x3;
	*ret_byte = 0;
	uint8_t ret_val = 1;
	uint8_t h0, h1;
	int qsize = 0;
	MUTEX_LOCK(dev->pm);
	qsize = dev->q[slave_id].size;
	if(qsize > 1)
	{
		ret_val = 0;
		uint8_t p_ok = popFromHexQueue(&(dev->q[slave_id]), &h0);
		p_ok = popFromHexQueue(&(dev->q[slave_id]), &h1);
		
		*ret_byte = (TOBINARY(h0) << 4) | TOBINARY(h1);
	}
	MUTEX_UNLOCK(dev->pm);
	return(ret_val);
}

uint8_t getHexU32FromQueue (SpiMasterDevice* dev, int slave_id, uint32_t* ret_u32)
{
	slave_id = slave_id & 0x3;
	*ret_u32 = 0;
	uint8_t ret_val = 1;
	uint8_t h0, h1;
	int qsize = 0;
	MUTEX_LOCK(dev->pm);
	qsize = dev->q[slave_id].size;
	if(qsize > 7) // at least 8 hex-chars should be present.
	{
		ret_val = 0;
		int IDX;
		for(IDX = 0; IDX < 4; IDX++)
		{
			uint8_t p_ok = popFromHexQueue(&(dev->q[slave_id]), &h0);
			p_ok = popFromHexQueue(&(dev->q[slave_id]), &h1);
		
			*ret_u32 = ((*ret_u32) << 8) | (TOBINARY(h0) << 4) | TOBINARY(h1);
		}
	}
	MUTEX_UNLOCK(dev->pm);
	return(ret_val);
}

