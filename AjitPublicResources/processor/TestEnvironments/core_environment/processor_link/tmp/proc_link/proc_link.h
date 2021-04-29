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

/* FIFO INTERFACE CONTROL ADDRESS */

#define AXI_TO_FIFO_START_REGISTER 0x44a10000 // Write '1' to bit 0 

#define FIFO_TO_AXI_START_REGISTER 0x44a00000 // Write '1' to bit 0 

/* FIFO INTERFACE DATA ADDRESS */

#define AXI_TO_FIFO_DATA_REGISTER_1 0x44a10010 // Write a 32 bit number to it

#define AXI_TO_FIFO_DATA_REGISTER_2 0x44a10014 // Write a 32 bit number to it

#define FIFO_TO_AXI_DATA_REGISTER_1 0x44a00010 // Write a 32 bit number to it

#define FIFO_TO_AXI_DATA_REGISTER_2 0x44a00014 // Write a 32 bit number to it

/* FIFO INTERFACE SUCCESS STATUS REGISTER */

#define AXI_TO_FIFO_SUCCESS_REGISTER 0x44a1001c // Read bit 0 / The address can also be 0x44a10020 

#define FIFO_TO_AXI_SUCCESS_REGISTER 0x44a0001c // Read bit 0 / The address can also be 0x44a00020

/* ERROR Routine */ 

#define PRINT_ERROR \
	do { \
		fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
		__LINE__, __FILE__, errno, strerror(errno)); exit(1); \
	} while(0)

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)
