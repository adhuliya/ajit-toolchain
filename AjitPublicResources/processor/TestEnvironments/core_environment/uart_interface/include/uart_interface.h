#ifndef _uart_interface_h___
#define _uart_interface_h___


// This should be called before setupDebugUartLink
// if you need to make the reads non-blocking.
void setUartBlockingFlag(int x);

// setup debug uart link.
int setupDebugUartLink(char* device);


//
// return baudrate.
//
int getBaudRate();



//
// open serial device and initialize..
//
void initComPort(int* sfd, char* device);

//
// send bytes, and return number of bytes sent (should be = count)
//   buf is sent in the following order  count-1, count-2 ... ,0 
int sendBytesOverUart(uint8_t *buf, int count);
int sendByteArrayBase(uint8_t *buf, int count, int downto_flag);
int sendByte(uint8_t b);

int perThreadSendBytesOverUart(int CORE_ID, int THREAD_ID, uint8_t *buf, int count);


//
// return number of bytes received.
//  if noblock_flag == 1, then return after first
//  try.  Otherwise, keep reading until success.
//
// returned bytes are kept in *buf.
//   buf is received in the following order  count-1, count-2 ... ,0 
int recvBytesOverUart(uint8_t* buf,  int count, int noblock_flag);
int recvBytesOverUartBase(uint8_t* buf,  int count, int noblock_flag, int downto_flag);
uint8_t recvByte();


#endif
