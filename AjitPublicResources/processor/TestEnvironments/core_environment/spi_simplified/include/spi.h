#ifndef _spi_h_____
#define _spi_h_____
#include <pthread.h>

#define SPI_RESPONSE_DELAY_IN_NS      1	 // 1 nsec.. check this later.
#define SPIQSIZE 4096


typedef struct _SpiMasterDevice_ {
	char* name;
	char* command_pipe;
	char* response_pipe;
	pthread_mutex_t pm;
} SpiMasterDevice;


void initSpiMasterDeviceStruct (SpiMasterDevice* dev, char* dev_name, char* cmd_pipe, char* resp_pipe);

//
// Routines to interact with the SPI master.  There are two
// pipes available: a 16-bit command pipe (cmd_pipe) into which commands
// with the following format are sent
//     unused read/write-bar reg-addr write-data
//       5       1             2         8 
// There is also an 8-bit response pipe. on which responses
// from the master can be read.
//
// Note: there is no flow control. 
//

// write to lower byte of SPI master data register
void writeSpiMasterLowDataByte(SpiMasterDevice* dev, uint8_t X);

// write to upper byte of SPI master data register
void writeSpiMasterHighDataByte(SpiMasterDevice* dev, uint8_t X);

//
// write configuration.
//   transfer-length (lowest 2-bits used):  0 => 4 bits, 1 => 8 bits, 2 => 12 bits, 3 => 16 bits.
//   clk-divide-count(lowest 4-bits used): spi-clk frequency will be clk-freq/(2**(clk-divide-count + 1))
//
void writeSpiMasterConfiguration(SpiMasterDevice* dev, uint8_t transfer_length, uint8_t clk_divide_count);

// write command register
//  spi_dev_id (lowest 3-bits used): from 0 to 7.
//  irq_en : if == 1, generate interrupt after transfer has completed.
//  deselect_after_xfer:  if == 1, deselect slave after transfer.
//  start_transfer: if == 1, start SPI transfer.
void writeSpiMasterCommandRegister(SpiMasterDevice* dev,
					uint8_t spi_dev_id, uint8_t irq_en, uint8_t deselect_after_xfer,
							uint8_t start_transfer);

uint8_t executeSpiMasterTransfer(SpiMasterDevice* dev, uint8_t slave_id); // leaves slave selected.
uint8_t executeSpiMasterTransferAndDeselectSlave(SpiMasterDevice* dev, uint8_t slave_id);  // deselect slave after transfer.

//
//  byte-address: 0 => datareg-lower-byte, 
//		  1 => datareg-upper-byte, 
//		  2 => command-register (lowest bit gives busy status).
//		  3 => config-register 
//
uint8_t readSpiMasterByte(SpiMasterDevice* dev, uint8_t byte_address);


//
// Base send command.
//
uint8_t sendByteViaSpiMaster (SpiMasterDevice* dev,  uint8_t send_byte, uint8_t deselect_after_xfer, uint8_t slave_id);



// status word from spi-slave contains
// number of pending tx entries and
// number of available rx slots.
int availableTxEntries (uint8_t status);
int freeRxSlotCount (uint8_t status);
#endif


