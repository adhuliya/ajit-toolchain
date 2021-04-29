#include "proc_link.h"

int fpga_open()
{
	
	char *filename = SYS_FILE;
	
	int fd;

	if((fd = open(filename, O_RDWR | O_SYNC)) ==-1) PRINT_ERROR;
	
	return fd;

}

int fpga_close( void* map_base, int fd)
{

	if(munmap(map_base, MAP_SIZE) == -1) PRINT_ERROR;
	close(fd);
	return 0;

}

int recv_u64_from_processor(uint64_t* r_word)

{
	void *map_base, *start_addr, *data_lower_addr, *data_higher_addr;
	uint64_t read_result_lower,read_result_higher,read_result;
	off_t data_lower_target, data_higher_target; 
	int fd;

	fd = fpga_open();
        
	if(fd!=0){return -1;} 
	
	data_lower_target = FIFO_TO_AXI_DATA_REGISTER_1 - FIFO_TO_AXI_START_REGISTER; //strtoul(/*split the 64 bit word for addr*/,0,0);
	
	data_higher_target = FIFO_TO_AXI_DATA_REGISTER_2 - FIFO_TO_AXI_START_REGISTER; //strtoul(/*split the 64 bit word for addr*/,0,0);

	//printf("Target offset is 0x%x, page size is %ld\n",(int) target, sysconf(_SC_PAGE_SIZE));

	map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, FIFO_TO_AXI_START_REGISTER & ~MAP_MASK);
	
	if(map_base == (void*) -1) PRINT_ERROR;

	/* 
	*  One read for data_valid signal 
	*  and the two reads for two 32 bit values
	*  then merge those to form read_result 
	*/

	while(*((uint32_t *) FIFO_TO_AXI_SUCCESS_REGISTER) == 1){
	/* Wait until the data valid signal is '1' */
	sleep(0.001);
	}

	data_lower_addr = map_base + (data_lower_target & MAP_MASK);
	read_result_lower = *((uint32_t *) data_lower_addr);
	
	data_higher_addr = map_base + (data_higher_target & MAP_MASK);
	read_result_higher = *((uint32_t *) data_higher_addr);
	
	//int type_width = 8;
	//printf("Value at offset 0x%X (%p) : 0x%0*lX\n",(int) target, virt_addr, type_width, read_result);

	read_result = (uint64_t) read_result_higher << 32 | read_result_lower ;	
	*r_word = read_result;
	return 0;
}

int send_u64_to_processor(uint64_t* s_word)

{
	void *map_base, *start_addr, *data_lower_addr, *data_higher_addr;
	uint32_t write_val_lower, write_val_higher;
	off_t start_target, data_lower_target, data_higher_target; 
	int fd;

	fd = fpga_open();

	if(fd!=0){return -1;} 

	data_lower_target  = AXI_TO_FIFO_DATA_REGISTER_1 - AXI_TO_FIFO_START_REGISTER; //strtoul(/*split the 64 bit word for addr*/,0,0);

	data_higher_target = AXI_TO_FIFO_DATA_REGISTER_2 - AXI_TO_FIFO_START_REGISTER; //strtoul(/*split the 64 bit word for addr*/,0,0);
	
	write_val_lower  = *(s_word) && 0x0000FFFF; /* split the 64 bit word for lower nibble  */
	write_val_higher = *(s_word) && 0xFFFF0000; /* split the 64 bit word for higher nibble */

	//printf("Target offset is 0x%x, page size is %ld\n",(int) target, sysconf(_SC_PAGE_SIZE));

	map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, AXI_TO_FIFO_START_REGISTER & ~MAP_MASK);
	
	if(map_base == (void*) -1) PRINT_ERROR;

	/* Two writes for data_lower and data_higher
	*  And 1 write for start bit and then
	*  wait for write_success to come.
	*/

	/* Write data_lower */

	data_lower_addr = map_base + (data_lower_target & MAP_MASK);

	*((uint32_t *) data_lower_addr) = write_val_lower;

	/* Write data_higher */

	data_higher_addr = map_base + (data_higher_target & MAP_MASK);

	*((uint32_t *) data_higher_addr) = write_val_higher;

	/* Write start bit */

	start_addr = map_base + (start_target & MAP_MASK);

	*((uint32_t *) start_addr) = 1;

	/* int type_width = 8;
	*  printf("0x%0*lX value written at offset 0x%X (%p)",type_width, write_val_1, (int) target, virt_addr);
	*/
	
	while(*((uint32_t *) AXI_TO_FIFO_SUCCESS_REGISTER) == 1){
	/* Wait until write success is 1 */
	sleep(0.001);
	}
	
	return 0;
}

void main()
{

}
