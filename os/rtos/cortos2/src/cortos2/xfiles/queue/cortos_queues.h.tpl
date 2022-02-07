#ifndef CORTOS_QUEUES_H
#define CORTOS_QUEUES_H

#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

/* Write one or more messages.
  - Returns the number of messages written from *msgs.
*/
uint32_t cortos_writeMessages(uint32_t queueId, uint8_t *msgs, uint32_t count);

/* Read one or more messages.
  - Returns the number of messages read into *msgs.
*/
uint32_t cortos_readMessages(uint32_t queueId, uint8_t *msgs, uint32_t count);


% for queue in confObj.software.queueSeq.queueSeq:
#define CORTOS_QUEUE_{{queue.getName()}} {{queue.qid}}
#define CORTOS_QUEUE_{{queue.getName()}}_LEN {{queue.length}}
#define CORTOS_QUEUE_{{queue.getName()}}_MSG_SIZE_IN_BYTES {{queue.msgSizeInBytes}}

% end

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_message_queues_declarations_internal
////////////////////////////////////////////////////////////////////////////////

// locks to synchronize the access of queues (for internal use)
int __cortos_q_lock_acquire_buzy(int index);
int __cortos_q_lock_acquire(int index);
void __cortos_q_lock_release(int index);

// queue header (for internal use)
typedef struct _CortosQueueHeader {
  uint32_t totalMsgs; // current total messages
  uint32_t readIndex;
  uint32_t writeIndex;
  uint32_t length;
  uint32_t msgSizeInBytes;
  uint8_t *queuePtr;
} CortosQueueHeader;


// initialize the queue headers
void cortos_init_queue_headers();

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

#endif // CORTOS_QUEUES_H

