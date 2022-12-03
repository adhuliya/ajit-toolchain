#ifndef ajit_spi_flash___
#define ajit_spi_flash___
#include "device_addresses.h"
#include "ajit_access_routines.h"

/*
	These routines can be used for SPI flash memories with sizes
	from 1Mb (128KBytes) to 128Mb (16MBytes).

	For all these routines, it is assumed that the SPI master
	is memory mapped.  Addresses are as in device_addresses.h.

	Author Madhav Desai.
*/

// Opcodes for flash
#define WRITE_COMMAND				 0x2
#define READ_COMMAND				 0x3
#define WRITE_DISABLE_COMMAND			 0x4
#define READ_STATUS_COMMAND			 0x5
#define WRITE_ENABLE_COMMAND			 0x6
#define SUB_SECTOR_ERASE_COMMAND		 0x20
#define SECTOR_ERASE_COMMAND			 0xD8
#define BULK_ERASE_COMMAND			 0xC7
#define RESET_ENABLE_COMMAND			 0x66
#define RESET_MEMORY_COMMAND			 0x99

//--------------------------------------------------------------------------------------------
// Utilities.
//--------------------------------------------------------------------------------------------
// if the master transfer is still in progress.
//
// return 1 if last transfer is still in progress...
//
uint32_t ajit_spi_transfer_is_in_progress();

// send a byte to the spi slave flash device..   deselect should be 1 if
// this is the last byte in a command transaction.
void ajit_spi_flash_send_byte(uint8_t dev_id, uint8_t byte_to_send, uint8_t deselect_flag);

// receive a byte to the spi slave flash device..   deselect should be 1 if
// this is the last byte in a command transaction.
uint8_t ajit_spi_flash_receive_byte(uint8_t dev_id, uint8_t deselect_flag);

//--------------------------------------------------------------------------------------------
// reset and initialization
//--------------------------------------------------------------------------------------------
// reset the flash device.
void ajit_spi_flash_reset (uint8_t device_id);

// reset the flash memory.
void ajit_spi_flash_memory_reset(uint8_t device_id);

// The SPI clock frequency will be set to  clk_freq/(2^(clk_divide_count + 1))
// so if the clk_divide count is 0, SPI clk = clk/2, and if the clk_divide_count = 0xf, then
// SPI clk = clk/65536.
void ajit_spi_set_clock_frequency (uint8_t clk_divide_count);

//--------------------------------------------------------------------------------------------
// Status
//--------------------------------------------------------------------------------------------
//
//  Return '1' if the spi flash is busy executing the last command (erases and writes take time)
//
uint32_t ajit_spi_flash_is_busy(uint8_t dev_id);

//--------------------------------------------------------------------------------------------
// Erase
//--------------------------------------------------------------------------------------------

// erase a 4KB subsector..  The subsector containing the location pointed
// to by addr is erased.
void ajit_spi_flash_subsector_erase(uint8_t device_id, uint32_t addr);

// erase a 64KB sector..   The sector containing the location pointed
// to by addr is erased.
void ajit_spi_flash_sector_erase(uint8_t device_id, uint32_t addr);

// erase the whole flash...
void ajit_spi_flash_bulk_erase(uint8_t device_id, uint32_t addr);

//--------------------------------------------------------------------------------------------
// Read/Write.    
//--------------------------------------------------------------------------------------------
//
// reads n_bytes bytes from spi flash with id=device_id, and puts them in 
// buffer.. buffer must have enough space, obviously.  
//
// The bytes are read from the start_address onwards.   The address will wrap 
// around to 0 after incrementing from the max address.
//
void ajit_spi_flash_read (uint8_t device_id, uint32_t start_address, uint8_t* buffer, uint32_t n_bytes);

// writes n_bytes bytes into spi flash slave with id=device_id, from buffer.
//
// The bytes are written into the flash from the start_address onwards.   The address will wrap 
// around to 0 after incrementing from the max-address.
//
void ajit_spi_flash_write (uint8_t device_id, uint32_t start_address, uint8_t* buffer, uint32_t n_bytes);



#endif

