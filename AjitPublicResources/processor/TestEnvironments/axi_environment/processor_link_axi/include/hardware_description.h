#ifndef _hardware_description_h___ 
#define _hardware_description_h___ 

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

/* DRAM ADDRESS RANGES | SIZE : 2GB FOR DATA AND 2GB FOR DEVICES */

#define RAM_UPPER_LIMIT 0x7FFFFFFF

#define RAM_LOWER_LIMIT 0x00000000

#endif
