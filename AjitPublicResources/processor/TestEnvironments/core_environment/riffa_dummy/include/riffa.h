#ifndef riffa_h____
#define riffa_h____

typedef void fpga_t;

fpga_t* fpga_open(int);
void fpga_reset(void*);
void fpga_close(void*);
int fpga_send(fpga_t* fpga, int l, void* , int nwords, int offset, int last, int timeout);	
int fpga_recv(fpga_t* fpga, int offset, void* r_word, int len, int timeout);



#endif
