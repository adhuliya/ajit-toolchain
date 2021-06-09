#include <stdlib.h>
#include <stdint.h>

#ifdef SW
	#include <stdio.h>
#endif



void axi_init_ram_through_debug_interface(void* fpga, char* mmap_file_name);
void axi_init_ram(void*fpga, char* mmap_file_name);


