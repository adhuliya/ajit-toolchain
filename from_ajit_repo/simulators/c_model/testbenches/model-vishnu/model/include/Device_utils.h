#ifndef __device_utils_h____
#define __device_utils_h____

void getPeripheralAccessCommand(const char* req_pipe,
                                        uint8_t *rwbar,
                                        uint8_t *byte_mask,
                                        uint32_t *address,
                                        uint32_t *write_data);
void sendPeripheralResponse(const char*  response_pipe,
                                        uint32_t send_data);


uint32_t insertUsingByteMask (uint32_t old_val, uint32_t new_val, uint8_t byte_mask);

#endif
