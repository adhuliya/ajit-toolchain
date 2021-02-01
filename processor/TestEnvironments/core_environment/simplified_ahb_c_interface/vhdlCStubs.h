#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <Pipes.h>
#include <SocketLib.h>
void get_simplified_ahb_command(uint8_t* rw,uint8_t* transfer_size,uint64_t* byte_address,uint32_t* write_data);
void global_storage_initializer_();
uint8_t mem_load__(uint32_t address);
void mem_store__(uint32_t address,uint8_t data);
void send_simplified_ahb_response(uint8_t err,uint32_t read_data);
