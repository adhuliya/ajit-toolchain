#include <stdlib.h>
#include <stdint.h>
#include "ajit_access_routines.h"
#include "device_addresses.h"
#include "ajit_spi_flash.h"

uint32_t ajit_spi_transfer_is_in_progress()
{
	uint32_t status = *((uint32_t*) ADDR_SPI_COMMAND_STATUS_REGISTER);
	return(status & 0x1);
}

// send a byte to the flash device.
//    first write the byte to regiser 0 in the master.
//    then initiate a transfer by writing to the command register in the master
//    spin until transfer is completed.
void ajit_spi_flash_send_byte(uint8_t dev_id, uint8_t byte_to_send, uint8_t deselect_after_send)
{
	// write 32-bits but only bottom 8-bits are used.
	*((uint32_t*) ADDR_SPI_DATA_REGISTER_LOW) = byte_to_send;

	// write 32-bits but only bottom 8-bits are used.
	uint32_t cmd = 1 | ((deselect_after_send & 0x1) << 1) | ((dev_id & 0x7) << 3);
	*((uint32_t*) ADDR_SPI_COMMAND_STATUS_REGISTER) = cmd;

	// check if it is still busy
	while(ajit_spi_transfer_is_in_progress())
	{
		// sleep for 64 clock cycles.
		__ajit_sleep__ (64);
	}
}

uint8_t ajit_spi_flash_receive_byte(uint8_t dev_id, uint8_t deselect_after_send)
{
	*((uint32_t*) ADDR_SPI_DATA_REGISTER_LOW) = 0;
	uint32_t cmd = 1 | ((deselect_after_send & 0x1) << 1) | ((dev_id & 0x7) << 3);
	*((uint32_t*) ADDR_SPI_COMMAND_STATUS_REGISTER) = cmd;

	while(1)
	{
		uint32_t status =  *((uint32_t*) ADDR_SPI_COMMAND_STATUS_REGISTER);
		if(!(status & 0x1))
			break;

		// sleep for 64 clock cycles.
		__ajit_sleep__ (64);
	}

	uint8_t recv_byte = *((uint32_t*) ADDR_SPI_DATA_REGISTER_LOW);
	return(recv_byte);
}

void ajit_spi_flash_reset (uint8_t device_id)
{
	ajit_spi_flash_send_byte(device_id, RESET_ENABLE_COMMAND, 1);	
}

void ajit_spi_flash_memory_reset(uint8_t device_id)
{
	ajit_spi_flash_send_byte(device_id, RESET_MEMORY_COMMAND, 1);	
}

void ajit_spi_set_clock_frequency (uint8_t clk_divide_count)
{
	*((uint32_t*) ADDR_SPI_CONFIG_REGISTER) = ((0x1 << 4) | (clk_divide_count & 0xf));
}

void ajit_spi_flash_generic_erase(uint8_t device_id, uint8_t erase_type, uint32_t addr)
{
	// Write enable!
	ajit_spi_flash_send_byte (device_id, WRITE_ENABLE_COMMAND, 1);

	// send command byte.
	ajit_spi_flash_send_byte (device_id, erase_type, 0);

	// send three bytes of the address, msb first.
	ajit_spi_flash_send_byte (device_id, (addr >> 16) & 0xff, 0);
	ajit_spi_flash_send_byte (device_id, (addr >> 8) & 0xff, 0);
	ajit_spi_flash_send_byte (device_id, addr & 0xff, 1);

	ajit_spi_flash_send_byte (device_id, WRITE_DISABLE_COMMAND, 1);
}

void ajit_spi_flash_subsector_erase(uint8_t device_id, uint32_t addr)
{
	ajit_spi_flash_generic_erase (device_id, SUB_SECTOR_ERASE_COMMAND, addr);
}
void ajit_spi_flash_sector_erase(uint8_t device_id, uint32_t addr)
{
	ajit_spi_flash_generic_erase (device_id, SECTOR_ERASE_COMMAND, addr);
}

void ajit_spi_flash_bulk_erase(uint8_t device_id, uint32_t addr)
{
	ajit_spi_flash_generic_erase (device_id, BULK_ERASE_COMMAND, addr);
}

void ajit_spi_flash_read (uint8_t device_id, uint32_t start_address, uint8_t* buffer, uint32_t n_bytes)
{
	// send command byte.
	ajit_spi_flash_send_byte (device_id, READ_COMMAND, 0);

	// send three bytes of the address, msb first.
	ajit_spi_flash_send_byte (device_id, (start_address >> 16) & 0xff, 0);
	ajit_spi_flash_send_byte (device_id, (start_address >> 8) & 0xff, 0);
	ajit_spi_flash_send_byte (device_id, start_address & 0xff, 0);

	int I;
	for(I = 0; I < n_bytes; I++)
	{
		uint8_t desel_flag = (I == (n_bytes-1));
		buffer[I] = ajit_spi_flash_receive_byte(device_id, desel_flag);
	}
}

void ajit_spi_flash_write(uint8_t device_id, uint32_t start_address, uint8_t* buffer, uint32_t n_bytes)
{
	// Write enable!
	ajit_spi_flash_send_byte (device_id, WRITE_ENABLE_COMMAND, 1);

	// send command byte.
	ajit_spi_flash_send_byte (device_id, WRITE_COMMAND, 0);

	// send three bytes of the address, msb first.
	ajit_spi_flash_send_byte (device_id, (start_address >> 16) & 0xff, 0);
	ajit_spi_flash_send_byte (device_id, (start_address >> 8) & 0xff, 0);
	ajit_spi_flash_send_byte (device_id, start_address & 0xff, 0);

	int I;
	for(I = 0; I < n_bytes; I++)
	{
		uint8_t desel_flag = (I == (n_bytes-1));
		ajit_spi_flash_send_byte(device_id, buffer[I], desel_flag);
	}

	ajit_spi_flash_send_byte (device_id, WRITE_DISABLE_COMMAND,  1);
}
