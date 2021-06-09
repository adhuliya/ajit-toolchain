#ifndef _RxQueueServer_h___
#define _RxQueueServer_h___

#define MCBUFSIZE 		(16*1024)
#define NCORES 	   		4
#define NTHREADS_PER_CORE   	2

typedef struct __MultiThreadRxQueue {
	// big buffer.. keep writing regardless of 
	// whether it gets full
	uint8_t buffer[MCBUFSIZE];

	uint32_t write_pointer;
	uint32_t read_pointer;

	pthread_mutex_t lock;
} MultiThreadRxQueue;

void initMultiThreadRxQueue (MultiThreadRxQueue* mcrq);

void pushByte(MultiThreadRxQueue* mcrq, uint8_t b);

// return 0 on success.
int popByte(MultiThreadRxQueue* mcrq, uint8_t *b);

// daemon.
void startMultiThreadRxDaemon();


//
// return 0 if OK.
//    either reads from socket or 
//    from uart.
//
int recvByteFromDut(uint8_t* buf);
void perThreadRecvBytesFromRxDaemon (int CORE_ID, int THREAD_ID, uint8_t*  buf, int count);

// usually pname = SOC_DEBUG_to_MONITOR
void setRxQueueServerInSocketMode(char* pname);
#endif
