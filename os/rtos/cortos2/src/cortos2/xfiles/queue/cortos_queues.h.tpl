#ifndef CORTOS_QUEUES_H
#define CORTOS_QUEUES_H

#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

// 24 byte queue header (for internal use)
typedef struct _CortosQueueHeader {
  uint32_t totalMsgs; // current total messages
  uint32_t readIndex;
  uint32_t writeIndex;
  uint32_t length;
  uint32_t msgSizeInBytes;
  uint8_t *lock;
} CortosQueueHeader;

% if confObj.software.bget.enable:
/* Reserve a cortos queue.
  msgSizeInBytes - size of each message in bytes
  length - the number of messages the queue can hold
  nc - if 1, allocates the queue in the non-cacheable memory region
       else uses the cacheable region
  It returns the pointer to the header of the queue.
  The queue starts immediately after the header.
*/
CortosQueueHeader*
cortos_reserveQueue(uint32_t msgSizeInBytes, uint32_t length, uint8_t nc);

/* Free a reserved queue. */
void cortos_freeQueue(CortosQueueHeader *hdr);

% end

/* Write one or more messages.
  - Returns the number of messages written from *msgs.
*/
uint32_t cortos_writeMessages(CortosQueueHeader *hdr, uint8_t *msgs, uint32_t count);

/* Read one or more messages.
  - Returns the number of messages read into *msgs.
*/
uint32_t cortos_readMessages(CortosQueueHeader *hdr, uint8_t *msgs, uint32_t count);


////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_message_queues_declarations
////////////////////////////////////////////////////////////////////////////////

#endif // CORTOS_QUEUES_H

