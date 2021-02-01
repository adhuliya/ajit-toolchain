#include <vhdlCStubs.h>
void get_simplified_ahb_command(uint8_t* rw,uint8_t* transfer_size,uint64_t* byte_address,uint32_t* write_data)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call get_simplified_ahb_command ");
append_int(buffer,0); ADD_SPACE__(buffer);
append_int(buffer,4); ADD_SPACE__(buffer);
append_int(buffer,8); ADD_SPACE__(buffer);
append_int(buffer,8); ADD_SPACE__(buffer);
append_int(buffer,64); ADD_SPACE__(buffer);
append_int(buffer,32); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
*rw = get_uint8_t(buffer,&ss);
*transfer_size = get_uint8_t(buffer,&ss);
*byte_address = get_uint64_t(buffer,&ss);
*write_data = get_uint32_t(buffer,&ss);
return;
}
void global_storage_initializer_()
{
char buffer[1024];  char* ss;  sprintf(buffer, "call global_storage_initializer_ ");
append_int(buffer,0); ADD_SPACE__(buffer);
append_int(buffer,0); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
return;
}
uint8_t mem_load__(uint32_t address)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call mem_load__ ");
append_int(buffer,1); ADD_SPACE__(buffer);
append_uint32_t(buffer,address); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,8); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
uint8_t data = get_uint8_t(buffer,&ss);
return(data);
}
void mem_store__(uint32_t address,uint8_t data)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call mem_store__ ");
append_int(buffer,2); ADD_SPACE__(buffer);
append_uint32_t(buffer,address); ADD_SPACE__(buffer);
append_uint8_t(buffer,data); ADD_SPACE__(buffer);
append_int(buffer,0); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
return;
}
void send_simplified_ahb_response(uint8_t err,uint32_t read_data)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call send_simplified_ahb_response ");
append_int(buffer,2); ADD_SPACE__(buffer);
append_uint8_t(buffer,err); ADD_SPACE__(buffer);
append_uint32_t(buffer,read_data); ADD_SPACE__(buffer);
append_int(buffer,0); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
return;
}
