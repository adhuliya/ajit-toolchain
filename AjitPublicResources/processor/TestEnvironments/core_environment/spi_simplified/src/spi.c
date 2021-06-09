#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "pipeHandler.h"
#include "Pipes.h"
#include "pthreadUtils.h"
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

void initSpiMasterDeviceStruct (SpiMasterDevice* dev, char* dev_name, char* cmd_pipe, char* resp_pipe)
{
	dev->name = strdup(dev_name);
	dev->command_pipe = strdup(cmd_pipe);
	dev->response_pipe = strdup(resp_pipe);
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
// incoming data is pushed to q.
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

//
// spi-master needs a command sequence to transfer a byte.
//
uint8_t sendByteViaSpiMaster(SpiMasterDevice* dev, uint8_t send_byte, uint8_t deselect_after_xfer, uint8_t slave_id)
{
	writeSpiMasterLowDataByte(dev, send_byte);
	uint8_t r = 0;

	if(deselect_after_xfer)
		r = executeSpiMasterTransferAndDeselectSlave(dev, slave_id);
	else
		r = executeSpiMasterTransfer(dev, slave_id);

	return(r);
}

int availableTxEntries (uint8_t status)
{
	int ret_val =  (status >> 4);
	return(ret_val);
}

int freeRxSlotCount (uint8_t status)
{
	int ret_val = status & 0xf;
	return(ret_val);
}
