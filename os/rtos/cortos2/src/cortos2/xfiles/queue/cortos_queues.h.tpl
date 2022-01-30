#ifndef CORTOS_QUEUES_H
#define CORTOS_QUEUES_H
////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

// A cortos' queue message.
typedef union _CortosMessage32Bytes {
  char charArr[32];
  int intArr[8];
  float floatArr[8];
  double doubleArr[4];

  struct {
    int a_code;
    void *a_ptr; // pointer to a location
    int a_size; // in bytes
    int a_intArr[5];
  };

  struct {
    int b_code;
    int b_intArr[7];
  };

  struct {
    int c_code;
    char c_charArr[28];
  };

  struct {
    int d_code;
    int d_val1;
    double d_d1;
    double d_d2;
    double d_d3;
  };

} CortosMessage;


/* Write a CortosMessage.
  - Returns zero if the queue is full.
  - Returns non-zero if the msg was added.
*/
int cortos_writeMessage(int queueId, CortosMessage *msg);

/* Read a CortosMessage.
  - Returns zero if the queue is empty.
  - Returns non-zero if the msg was put into the *msg location.
*/
int cortos_readMessage(int queueId, CortosMessage *msg);

// Reserve an unused queue from cortos.
//   It returns the queue id of the queue reserved.
//   If no queue is available it returns -1.
// Once a queue is reserved it is held by the caller,
// until it is freed.
int cortos_reserveQueue();

// Free a queue for reuse by cortos.
void cortos_freeQueue(int queueId);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_message_queues_declarations_internal
////////////////////////////////////////////////////////////////////////////////

int __cortos_q_lock_acquire_buzy(int index);
int __cortos_q_lock_acquire(int index);
void __cortos_q_lock_release(int index);


typedef struct _CortosQueueHeader {
  int totalMsgs; // current total messages
  int readIndex;
  int writeIndex;
  int __; // to pad 4 bytes to make it 16 bytes.
} __CortosQueueHeader;

// Details of the queue header array (one queue header per queue).
#define __Q_HEADERS_START_ADDR {{ confObj.software.queueSeq.headersStartAddr }}
#define __Q_HEADERS_END_ADDR {{ confObj.software.queueSeq.getHeadersEndAddr() }}
#define __MAX_Q_HEADERS {{ confObj.software.queueSeq.getTotalQueues() }}

// Queues available to the user (all the queues sit here).
#define __QUEUE_START_ADDR {{ confObj.software.queueSeq.msgStartAddr }}
#define __QUEUE_END_ADDR {{ confObj.software.queueSeq.getMsgEndAddr() }}
#define __MAX_QUEUES {{ confObj.software.queueSeq.getTotalQueues() }}
#define __QUEUE_MSG_SIZE_IN_BYTES {{ confObj.software.queueSeq.queueMsgSizeInBytes }}
#define __MAX_ELEMENTS_PER_QUEUE {{ confObj.software.queueSeq.elementsPerQueue }}
#define __MAX_QUEUE_SIZE_IN_BYTES {{ confObj.software.queueSeq.getTotalQueueSizeInBytes() }}


#define __Q_START_INDEX 0
#define __AJIT_Q_BASE {{ confObj.software.queueSeq.msgStartAddr }}
#define __AJIT_Q_LEN {{ confObj.software.queueSeq.elementsPerQueue }}
#define __AJIT_Q_MSG_SIZE {{ confObj.software.queueSeq.queueMsgSizeInBytes }}

#define __AJIT_Q_HEADER_BASE {{ confObj.software.queueSeq.headersStartAddr }}
#define __AJIT_Q_HEADER_SIZE {{ confObj.software.queueSeq.queueHeaderSizeInBytes }}

#define __GET_MSG_ADDR(_BASE, _INDEX) \
((_BASE) + ((_INDEX) * (__AJIT_Q_MSG_SIZE)))

#define __INCREMENT_INDEX(_INDEX) \
(((((_INDEX)+1) % __AJIT_Q_LEN)) ? \
((((_INDEX)+1) % __AJIT_Q_LEN)) : __Q_START_INDEX)

/*
This computes the base address of the queue with id `queueId`.
*/
#define __GET_Q_ADDR(_Q_ID) \
((__AJIT_Q_BASE) + \
((__AJIT_Q_MSG_SIZE) * (__AJIT_Q_LEN) * (_Q_ID)));

/*
This computes the base address of the queue header with id `queueId`.
*/
#define __GET_Q_HEADER_ADDR(_Q_ID) \
((__AJIT_Q_HEADER_BASE) + \
((__AJIT_Q_HEADER_SIZE) * (_Q_ID)));

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

#endif // CORTOS_QUEUES_H
