#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <pipeHandler.h>
#include <Pipes.h>
#include <uarch_debug_utils.h>
#include <uarch_bist.h>

#define DESELECT    1

#define  WRITE_COMMAND			 0x2
#define  READ_COMMAND			 0x3
#define  WRITE_DISABLE_COMMAND 		 0x4
#define  READ_STATUS_COMMAND 		 0x5
#define  WRITE_ENABLE_COMMAND 		 0x6
// #define  BULK_ERASE_COMMAND 		 0xC7  This is set by ADM...
#define  SECTOR_ERASE_COMMAND            0xd8
#define  RESET_ENABLE_COMMAND 		 0x66
#define  RESET_MEMORY_COMMAND 		 0x99



///////////////////////////////////////////////////////////////////////////////////////////////////////
// Base routines to access SPI master registers
///////////////////////////////////////////////////////////////////////////////////////////////////////
void writeSpiMasterRegister (uint32_t base_address, uint8_t reg_id, uint8_t wbyte)
{
	uint32_t r_addr = (base_address + (reg_id << 2));
	dbg_write_mem (0x20, r_addr, (uint32_t) wbyte);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Base routines to access SPI master registers
///////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t readSpiMasterRegister (uint32_t base_address, uint8_t reg_id)
{
	uint32_t r_addr = (base_address + (reg_id << 2));
	uint32_t ret_val = dbg_read_mem (0x20, r_addr);

	return(ret_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// transfer byte to mosi, and return miso byte.
//////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t executeSpiMasterTransfer (uint32_t base_address, uint8_t deselect_after_transfer)
{
	uint32_t device_id = 0;

	uint32_t command =  ((device_id & 0x7) << 4) | ((deselect_after_transfer & 0x1) << 1) | 1;
	writeSpiMasterRegister (base_address, 2, command);

	while(1)
	{
		uint32_t status = readSpiMasterRegister (base_address,2);
		if(!(status & 0x1))
			break;

		usleep (1024);
	}
	uint32_t rval = readSpiMasterRegister (base_address, 0);
	return(rval);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
// write byte to master register, do transfer and return received byte.
///////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t sendByteOverSpi (uint32_t base_address, uint8_t dev_id, uint8_t wval, uint8_t deselect_option)
{
	// write to reg 0
	writeSpiMasterRegister (base_address, 0, (uint32_t) wval);

	// enable transfer command
	uint32_t ret_val = executeSpiMasterTransfer (base_address, deselect_option);

	// read the post-transfer byte.
	return(ret_val);
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Flash status... send command and fetch response..
//////////////////////////////////////////////////////////////////////////////////////////////
uint8_t readFlashStatusRegister (uint32_t base_address, uint8_t device_id)
{
   sendByteOverSpi (base_address, device_id, READ_STATUS_COMMAND, !DESELECT);
   uint32_t ret_val = sendByteOverSpi (base_address, device_id, 0, DESELECT);

   return(ret_val);
}



///////////////////////////////////////////////////////////////////////////////////
// Busy wait on status.
///////////////////////////////////////////////////////////////////////////////////
void busyWaitOnFlash (uint32_t  base_address, uint8_t dev_id, uint8_t wait_on_wel)
{
	while(1) 
	{
		uint32_t status = readFlashStatusRegister (base_address, dev_id);
		uint32_t not_done =  ((status & 0x1) ||
						(wait_on_wel ? ((status >> 1) & 0x1) : 0));

		if(!not_done)
			break;

		usleep (1024);
	}


}

///////////////////////////////////////////////////////////////////////////////////
// Reset flash and flash memory.
///////////////////////////////////////////////////////////////////////////////////
void resetFlashMem (uint32_t base_address)
{
	// write reset command.
	sendByteOverSpi (base_address, 0, RESET_ENABLE_COMMAND, DESELECT);

	usleep (1024);

	// write reset memory command.
	sendByteOverSpi (base_address, 0, RESET_MEMORY_COMMAND, DESELECT);

	// busy wait.
	busyWaitOnFlash (base_address, 0, 1);
}

///////////////////////////////////////////////////////////////////////////////////
// Write-enable enable or disable...
///////////////////////////////////////////////////////////////////////////////////
void writeEnableDisableSpiFlash (uint32_t base_address, uint8_t enable)
{
     uint32_t ed_cmd = (enable ?  WRITE_ENABLE_COMMAND : WRITE_DISABLE_COMMAND);
     sendByteOverSpi (base_address, 0, ed_cmd, DESELECT);

     busyWaitOnFlash (base_address, 0, 0);
}



///////////////////////////////////////////////////////////////////////////////////
// read back four bytes..
///////////////////////////////////////////////////////////////////////////////////
uint32_t recvU32 (uint32_t base_address, uint8_t dev_id, uint8_t deselect_after)
{
	uint8_t bytes[4];
	int I; 

	for(I = 3; I >= 0; I--)
	{
		uint8_t desel = ((I == 0) ? deselect_after : 0);
		bytes[I] = sendByteOverSpi (base_address, dev_id, 0, desel);
	}
	uint32_t ret_val =
		((((uint32_t) bytes[3]) & 0xff) << 24) |
		((((uint32_t) bytes[2]) & 0xff) << 16) |
		((((uint32_t) bytes[1]) & 0xff) << 8) |
		(((uint32_t) bytes[0]) & 0xff);

	return(ret_val);
}


// send 1/2/3/4 bytes..
void sendU32 (uint32_t base_address, uint8_t dev_id, uint32_t wdata, int n_bytes, uint8_t deselect_after)
{
	uint8_t bytes[4];

	// upto four bytes to be sent (note: lower bytes will be sent).
	bytes[3] = (wdata >> 24) & 0xff;
	bytes[2] = (wdata >> 16) & 0xff;
	bytes[1] = (wdata >> 8) & 0xff;
	bytes[0] = wdata & 0xff;

	int I;
	for(I = (n_bytes-1); I >= 0; I--)
	{
		uint8_t desel = ((I == 0) ? deselect_after : 0);
		sendByteOverSpi (base_address, dev_id, bytes[I], desel);
	}
}


/////////////////////////////////////////////////////////////////////////////////
//  Erase! use erase opcode!!
/////////////////////////////////////////////////////////////////////////////////
struct timespec ts, tf;
int spi_flash_erase (uint32_t spi_master_base_address, 
				uint8_t erase_opcode, 
				uint32_t sector_start_address,
				uint32_t number_of_sectors)
{
	fprintf (stderr, "Info: starting flash" 
			" erase (opcode=0x%x, sector-start-addr=0x%x, n-sectors=%d).." 
			" this will take a while. \n", erase_opcode, sector_start_address, number_of_sectors);

	int I;
	uint32_t current_address = sector_start_address;
	for(I = 0; I < number_of_sectors; I++)	
	{
		clock_gettime (CLOCK_REALTIME, &ts);

		// reset the flash
		resetFlashMem (spi_master_base_address);

		// enable the flash memory..
		writeEnableDisableSpiFlash (spi_master_base_address, 1);

		// base addr, device id = 0, 
		sendByteOverSpi (spi_master_base_address, 0, erase_opcode, !DESELECT);
		sendU32 (spi_master_base_address, 0, current_address, 3, DESELECT);

		busyWaitOnFlash (spi_master_base_address, 0, 1);

		clock_gettime (CLOCK_REALTIME, &tf);
		fprintf(stderr,"Info: completed sector erase (addr = 0x%x, elapsed time = %d seconds)\n", 
					current_address, (int) (tf.tv_sec - ts.tv_sec));

		current_address += 0x10000;
	}

	return(0);
}

/////////////////////////////////////////////////////////////////////////////////
//  Read 32-bit word from flash memory..
/////////////////////////////////////////////////////////////////////////////////
uint32_t spi_flash_read_mem (uint32_t spi_master_base_address, uint32_t addr, int nbytes_in_address)
{

	// send command.
	sendByteOverSpi (spi_master_base_address, 0, READ_COMMAND, !DESELECT);

	// send the address bytes.
	sendU32 (spi_master_base_address, 0, addr, nbytes_in_address, !DESELECT);

	// read back 4 bytes and deselect
	uint32_t rdata = recvU32    (spi_master_base_address, 0, DESELECT);
	return(rdata);
}

/////////////////////////////////////////////////////////////////////////////////
//  Write 32-bit word into flash memory..
/////////////////////////////////////////////////////////////////////////////////
void spi_flash_write_mem (uint32_t spi_master_base_address, uint32_t addr, uint32_t wdata, int nbytes_in_address)
{
	// enable flash write.
	writeEnableDisableSpiFlash (spi_master_base_address, 1);

	// send command.
	sendByteOverSpi (spi_master_base_address, 0, WRITE_COMMAND, !DESELECT);

	// address
	sendU32    (spi_master_base_address, 0, addr, nbytes_in_address, !DESELECT);
	// write-data.
	sendU32    (spi_master_base_address, 0, wdata, 4, DESELECT);

	// disable write.
	writeEnableDisableSpiFlash (spi_master_base_address, 0);
}

//////////////////////////////////////////////////////////////////////////////
// find active sectors (at most 4096)
//////////////////////////////////////////////////////////////////////////////
void spi_flash_calculate_active_sectors (char* mmap_file_name, 
						uint8_t* active_sector_flags,
						uint32_t max_number_of_sectors)
{
	FILE * file;
	file= fopen(mmap_file_name, "r");
	if(!file)
	{
		fprintf(stderr,"Error:spi_flash_calculate_active_sectors: file %s could not be opened for reading!\n",mmap_file_name);
		return;
	}

	int I;
	for(I = 0; I < max_number_of_sectors; I++)
		active_sector_flags[I] = 0;

	int sector_count = 0;

	uint32_t addr = 0;
	uint32_t data = 0;
	while (1)
	{
		int eof_reached = 0;
		
		int file_read=fscanf(file, "%x", &addr);
		if (feof(file)) 
		{
			eof_reached = 1;
			break;
		}
		else
		{
			file_read=fscanf(file, "%x", &data);
		}

		int sector_index = (addr >> 16) & (max_number_of_sectors-1);
		
		if(active_sector_flags[sector_index] == 0)
		{
			sector_count++;
			active_sector_flags[sector_index] = 1;
		}
		
	}
	fprintf(stderr,"Info: need to erase %d sectors\n", sector_count);
	fclose (file);
}

