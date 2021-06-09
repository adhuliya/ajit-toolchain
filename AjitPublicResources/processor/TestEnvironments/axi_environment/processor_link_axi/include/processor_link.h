#ifndef _processor_link_h___
#define _processor_link_h___

/* Function declarations */
void* initialize_axi_link(char* name, char* resource_file);

int recv_u64_from_processor(void* fpga_device, uint64_t* r_word);
int send_u64_to_processor(void* fpga_device ,uint64_t* s_word);

// we will need to add read/write routines to access all the 
// devices that we want to make visible to the user.
//  e.g. serial, dram, eth etc....
//
// return 0 on success.
int write_to_axi_dram(void* fpga_device, uint32_t dram_internal_address, uint32_t dram_write_word);

// return 0 on success.
int read_from_axi_dram(void* fpga_device, uint32_t dram_internal_address, uint32_t *dram_read_word);

int close_axi_link(void* fpga_device);

#endif
