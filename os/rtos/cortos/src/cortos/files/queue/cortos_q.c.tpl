
// needs linking with cortos_q_lock_unlock.s

#include "cortos.h"
#include "__cortos.h"

char queueIdArray[__MAX_QUEUES];

int cortos_reserveQueue() {
  int i, qid = -1;
  __cortos_lock_acquire_buzy(__RES_LOCK_GET_Q_ID);
  for (i=0; i < __MAX_QUEUES; ++i) {
    if(queueIdArray[i] == 0) {
      queueIdArray[i] = 1;
      qid = i;
      break;
    }
  }
  __cortos_lock_release(__RES_LOCK_GET_Q_ID);
  return qid;
}

void cortos_freeQueue(int queueId) {
  if (queueId >= 0 && queueId < __MAX_QUEUES) {
    __cortos_lock_acquire_buzy(__RES_LOCK_GET_Q_ID);
    queueIdArray[queueId] = 0;
    __cortos_lock_release(__RES_LOCK_GET_Q_ID);
  }
}

int cortos_writeMessage(int queueId, CortosMessage *msg) {
  int status = 0; // 1 = msg written
  __CortosQueueHeader *header = 0;
  CortosMessage *dest = 0;

  header = __GET_Q_HEADER_ADDR(queueId);
  dest = __GET_Q_ADDR(queueId);

  __cortos_q_lock_acquire_buzy(queueId);

  // critical section
  int totalMsgs = header->totalMsgs;
  int writeIndex = header->writeIndex;

  if (totalMsgs == __AJIT_Q_LEN) {
    status = 0; // queue is full
  } else {
    dest = __GET_MSG_ADDR(dest, writeIndex);
    *dest = *msg; // WRITE WRITE WRITE, THE MESSAGE HERE

    totalMsgs += 1;
    writeIndex = __INCREMENT_INDEX(writeIndex);

    header->totalMsgs = totalMsgs;
    header->writeIndex = writeIndex;
    status = 1;
  }

  __cortos_q_lock_release(queueId);
  return status;
}


int cortos_readMessage(int queueId, CortosMessage *msg) {
  int status = 0; // 1 = msg written
  __CortosQueueHeader *header = 0;
  CortosMessage *dest = 0;

  header = __GET_Q_HEADER_ADDR(queueId);
  dest = __GET_Q_ADDR(queueId);

  __cortos_q_lock_acquire_buzy(queueId);

  // critical section
  int totalMsgs = header->totalMsgs;
  int readIndex = header->readIndex;

  if (totalMsgs == 0) {
    status = 0; // queue is empty
  } else {
    dest = __GET_MSG_ADDR(dest, readIndex);
    *msg = *dest; // READ READ READ, THE MESSAGE HERE

    totalMsgs -= 1;
    readIndex = __INCREMENT_INDEX(readIndex);

    header->totalMsgs = totalMsgs;
    header->readIndex = readIndex;
    status = 1;
  }

  __cortos_q_lock_release(queueId);
  return status;
}


