
#include <cortos_locks.h>
#include <cortos_queues.h>


CortosQueueHeader cortosQueueHeaders[{{len(confObj.software.queueSeq)}}];

% for queue in confObj.software.queueSeq.queueSeq:
uint8_t cortosQueue{{queue.qid}}[{{queue.length}}][{{queue.msgSizeInBytes}}];
% end


// initialize the queue headers
void cortos_init_queue_headers() {
  % for i, queue in enumerate(confObj.software.queueSeq.queueSeq):
  // CORTOS_QUEUE_{{queue.name}}, seq = {{i}}, queue.qid = {{queue.qid}}
  cortosQueueHeaders[{{i}}].totalMsgs   = 0;
  cortosQueueHeaders[{{i}}].readIndex   = 0;
  cortosQueueHeaders[{{i}}].writeIndex  = 0;
  cortosQueueHeaders[{{i}}].msgSizeInBytes = {{queue.msgSizeInBytes}};
  cortosQueueHeaders[{{i}}].queuePtr       = (uint8_t*) cortosQueue{{queue.qid}};
  cortosQueueHeaders[{{i}}].length         = {{queue.length}};

  % end
}

uint32_t cortos_writeMessages(uint32_t queueId, uint8_t *msgs, uint32_t count) {
  CortosQueueHeader *hdr = cortosQueueHeaders + queueId;
  uint8_t *dest = 0, *src = 0; // nullptr
  uint32_t process = count;
  uint32_t i;

  __cortos_q_lock_acquire_buzy(queueId);

  uint32_t totalMsgs      = hdr->totalMsgs;
  uint32_t writeIndex     = hdr->writeIndex;
  uint32_t length         = hdr->length;
  uint32_t msgSizeInBytes = hdr->msgSizeInBytes;
  uint8_t* queuePtr       = hdr->queuePtr;

  while ((process > 0) && (totalMsgs < hdr->length)) {
    src  = msgs + (msgSizeInBytes * (count - process));
    dest = queuePtr + (msgSizeInBytes * writeIndex);
    for (i = 0; i < msgSizeInBytes; ++i) {
      *(dest+i) = *(src+i);                     // WRITE THE MESSAGE HERE
    }
    writeIndex = (writeIndex+1) % length;
    ++totalMsgs; --process;
  }

  hdr->totalMsgs  = totalMsgs;
  hdr->writeIndex = writeIndex;

  __cortos_q_lock_release(queueId);
  return (count - process);
}


uint32_t cortos_readMessages(uint32_t queueId, uint8_t *msgs, uint32_t count) {
  CortosQueueHeader *hdr = cortosQueueHeaders + queueId;
  uint8_t *dest = 0, *src = 0; // nullptr
  uint32_t process = count;
  uint32_t i;

  __cortos_q_lock_acquire_buzy(queueId);

  uint32_t totalMsgs      = hdr->totalMsgs;
  uint32_t readIndex      = hdr->readIndex;
  uint32_t length         = hdr->length;
  uint32_t msgSizeInBytes = hdr->msgSizeInBytes;
  uint8_t* queuePtr       = hdr->queuePtr;

  while ((process > 0) && (totalMsgs > 0)) {
    dest = msgs + (msgSizeInBytes * (count - process));
    src  = queuePtr + (msgSizeInBytes * readIndex);
    for (i = 0; i < msgSizeInBytes; ++i) {
      *(dest+i) = *(src+i);                     // READ THE MESSAGE HERE
    }
    readIndex = (readIndex+1) % length;
    --totalMsgs; --process;
  }

  hdr->totalMsgs  = totalMsgs;
  hdr->readIndex  = readIndex;

  __cortos_q_lock_release(queueId);
  return (count - process);
}

