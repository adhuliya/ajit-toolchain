#ifndef _processor_link_h___
#define _processor_link_h___

#define PROCESSOR_SOCKET_LINK    1
#define PROCESSOR_RIFFA_LINK     2
//#define PROCESSOR_AXI_LINK       3


// set the type of link: sockets or riffa?
//   opens the FPGA if so specified.
//   return 0 on success, non-zero on failure.
int set_processor_link(int processor_link_type);

int close_fpga ();

// return 0 on success, non-zero on failure.
int send_u64_to_processor(uint64_t* s_word);
int recv_u64_from_processor(uint64_t* r_word);

#endif
