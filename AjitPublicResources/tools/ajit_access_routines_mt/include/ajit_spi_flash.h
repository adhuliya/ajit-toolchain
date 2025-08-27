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
#define SECTOR_ERASE_COMMAND			 0xD8  // This is the one we use.
#define RESET_ENABLE_COMMAND			 0x66
#define RESET_MEMORY_COMMAND			 0x99

//--------------------------------------------------------------------------------------------
// Utilities.
//--------------------------------------------------------------------------------------------
// if the master transfer is still in progress.
//
// return 1 if last transfer is still in progress...
//
uint32_t ajit_spi_transfer_is_in_progress(uint32_t spim_base_addr);

// send a byte to the spi slave flash device..   deselect should be 1 if
// this is the last byte in a command transaction.
void ajit_spi_flash_send_byte(uint32_t spim_base_addr, uint8_t dev_id, uint8_t byte_to_send, uint8_t deselect_flag);

// receive a byte to the spi slave flash device..   deselect should be 1 if
// this is the last byte in a command transaction.
uint8_t ajit_spi_flash_receive_byte(uint32_t spim_base_addr, uint8_t dev_id, uint8_t deselect_flag);

//--------------------------------------------------------------------------------------------
// reset and initialization
//--------------------------------------------------------------------------------------------
// reset the flash device.
void ajit_spi_flash_reset (uint32_t spim_base_addr, uint8_t device_id);

// reset the flash memory.
void ajit_spi_flash_memory_reset(uint32_t spim_base_addr, uint8_t device_id);

//
// The SPI clock frequency will be set to  clk_freq/(2^(clk_divide_count + 1))
// so if the clk_divide count is 0, SPI clk = clk/2, and if the clk_divide_count = 0xf, then
// SPI clk = clk/65536.
//
//
// clocking-mode
// 00       master transmits mosi on falling edge, 
//          slave transmits miso on rising edge.
// 01       master transmits mosi on falling edge, 
//          slave transmits miso on falling edge.
// 10       master transmits mosi on rising edge, 
//          slave transmits miso on falling edge.
//            (idle value of clock is 1)
// 11       master transmits mosi on rising edge
//          slave transmit miso on rising edge.

// Transfer length
// 4/8/12/16 bits (default is 8)
//                                   00= 4 bits,
//                                   01= 8 bits,
//                                   10=12 bits,
//                                   11=16 bits

//
// div-count can be between 2 and 131072 (default is 16). 
// 0000 -> /2
// 0001 -> /4
// 0010 -> /8
// 0011 -> /16
// etc.
// 1111 -> 131072
// 
void ajit_spi_configure (uint32_t spim_base_addr, 
				uint32_t clocking_mode,
					uint32_t  transfer_length, 
					uint32_t clk_divide_count);

void    ajit_spi_set_transfer_length (uint32_t spim_base_addr, uint8_t tx_length);
uint8_t ajit_spi_get_register (uint32_t spim_base_addr, uint8_t reg_id);
void    ajit_spi_set_register (uint32_t spim_base_addr, uint8_t reg_id, uint8_t val);

//--------------------------------------------------------------------------------------------
// Status
//--------------------------------------------------------------------------------------------
//
//  Return '1' if the spi flash is busy executing the last command (erases and writes take time)
//
uint32_t ajit_spi_flash_is_busy(uint32_t spim_base_addr, uint8_t dev_id);

//--------------------------------------------------------------------------------------------
// Erase
//--------------------------------------------------------------------------------------------

// erase a 4KB subsector..  The subsector containing the location pointed
// to by addr is erased.
void ajit_spi_flash_subsector_erase(uint32_t spim_base_addr, uint8_t device_id, uint32_t addr);

// erase a 64KB sector..   The sector containing the location pointed
// to by addr is erased.
void ajit_spi_flash_sector_erase(uint32_t spim_base_addr, uint8_t device_id, uint32_t addr);

// erase the whole flash...
void ajit_spi_flash_bulk_erase(uint32_t spim_base_addr, uint8_t device_id, uint32_t addr);

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
void ajit_spi_flash_read (uint32_t spim_base_addr, uint8_t device_id, uint32_t start_address, 
					uint8_t* buffer, uint32_t n_bytes);

// writes n_bytes bytes into spi flash slave with id=device_id, from buffer.
//
// The bytes are written into the flash from the start_address onwards.   The address will wrap 
// around to 0 after incrementing from the max-address.
//
void ajit_spi_flash_write (uint32_t spim_base_addr,
				uint8_t device_id, uint32_t start_address, uint8_t* buffer, uint32_t n_bytes);



#endif

