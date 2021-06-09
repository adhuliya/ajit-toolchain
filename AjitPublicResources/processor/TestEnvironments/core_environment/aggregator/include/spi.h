#ifndef _spi_h_____
#define _spi_h_____
#include <pthread.h>

#define SPI_RESPONSE_DELAY_IN_NS      1	 // 1 nsec.. check this later.

#define HEXQSIZE 4096

#define TOHEX(x)  ((x < 10) ? (48 +x) : (55 + x))
#define TOBINARY(h) ( ((h >= 48) & (h <= 57)) ?   (h - 48) : ( ((h >= 65) & (h <= 70)) ? (h - 55) : (((h >= 97) & (h <= 102)) ? (h - 87) : 0)))
#define ISHEX(h) ( ((h >= 48) & (h <= 57)) || ((h >= 65) & (h <= 70)) || ((h >= 97) & (h <= 102))) 

typedef struct _HexQueue_ {
	uint8_t byte_array [HEXQSIZE];
	int read_pointer;
	int write_pointer;
	int size;
	pthread_mutex_t pm;
} HexQueue;

void initHexQueue(HexQueue* q);

// return 0 on success, 1 on failure because full.
uint8_t pushToHexQueue(HexQueue* q, uint8_t h);
// return 0 on success, 1 on failure because empty.
uint8_t popFromHexQueue(HexQueue* q, uint8_t* h);


typedef struct _SpiMasterDevice_ {
	char* name;
	char* command_pipe;
	char* response_pipe;
	HexQueue q [8]; // one for each slave.
	pthread_mutex_t pm;
} SpiMasterDevice;


void initSpiMasterDeviceStruct (SpiMasterDevice* dev, char* dev_name, char* cmd_pipe, char* resp_pipe);

// return 0 on success.
uint8_t getHexByteFromQueue (SpiMasterDevice* dev, int slave_id, uint8_t* ret_byte);
uint8_t getHexU32FromQueue (SpiMasterDevice* dev, int slave_id, uint32_t* ret_u32);

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
void writeSpiMasterLowDataByte(SpiMasterDevice* dev, uint8_t x);

// write to upper byte of SPI master data register
void writeSpiMasterHighDataByte(SpiMasterDevice* dev, uint8_t x);

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
uint8_t readHexCharFromSpiMaster(SpiMasterDevice* dev, uint8_t slave_id);

//
//  byte-address: 0 => datareg-lower-byte, 
//		  1 => datareg-upper-byte, 
//		  2 => command-register (lowest bit gives busy status).
//		  3 => config-register 
//
uint8_t readSpiMasterByte(SpiMasterDevice* dev, uint8_t byte_address);


void sendByteAsHexViaSpiMaster (SpiMasterDevice* dev,  uint8_t send_byte, uint8_t slave_id);
uint8_t getByteFromHexViaSpiMaster(SpiMasterDevice* dev, uint8_t slave_id);

uint8_t sendByteViaSpiMaster (SpiMasterDevice* dev,  uint8_t send_byte, 
					uint8_t deselect_after_xfer, uint8_t slave_id);


#endif


