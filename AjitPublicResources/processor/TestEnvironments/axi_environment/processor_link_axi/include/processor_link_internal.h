#ifndef _processor_link_internal_h___
#define _processor_link_internal_h___

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

#define SYS_FILE "/sys/bus/pci/devices/0000:0a:00.0/"

#define PRINT_ERROR \
	do { \
		fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
		__LINE__, __FILE__, errno, strerror(errno)); exit(1); \
	} while(0)

// Base address of RAM

#define RAM_BASE_ADDRESS 0x00000000 

// FPGA structure definition

struct FPGA_device{

	void* map_base;
	int fd;
	char* name;
	char* resource_file;

};

typedef struct FPGA_device FPGA;

// Function to create new FPGA device
//FPGA* new_fpga(char* fpga_name, char* resource_file);

//
// open the FPGA, returns a positive FPGA id on success.
//
FPGA* open_fpga (char* name, char* resource_file);

//
// close the FPGA, return 0 on success.
// 
int close_fpga (FPGA* fpga_device);

// return 0 on success
int fpga_axi_write(FPGA* fpga_device, uint32_t addr, uint32_t data);

// return 0 on success
int fpga_axi_read(FPGA* fpga_device, uint32_t addr, uint32_t *data);

//#define MAP_SIZE 4194304UL
#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#endif
