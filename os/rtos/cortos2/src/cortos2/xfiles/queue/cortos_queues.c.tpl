
#include <cortos_locks.h>
#include <cortos_queues.h>
#include <cortos_utils.h>
% if confObj.software.bget.enable:
#include <cortos_bget.h>
% end

% if confObj.software.bget.enable:
CortosQueueHeader*
cortos_reserveQueue(uint32_t msgSizeInBytes, uint32_t length, uint8_t nc) {
  uint8_t* queue = 0;
  uint32_t size = sizeof(CortosQueueHeader) + (msgSizeInBytes * length);
  if (nc) {
    queue = (uint8_t*)cortos_bget_ncram(size);
  } else {
    queue = (uint8_t*)cortos_bget(size);
  }
  if (queue == 0) return 0;

  // initialize the queue header
  CortosQueueHeader *hdr;
  hdr = (CortosQueueHeader*)queue;
  hdr->totalMsgs = 0;
  hdr->readIndex = 0;
  hdr->writeIndex = 0;
  hdr->msgSizeInBytes = msgSizeInBytes;
  hdr->length = length;
  hdr->lock = cortos_reserveLock(1);

  return hdr;
}

void cortos_freeQueue(CortosQueueHeader *hdr) {
  cortos_freeLock(hdr->lock);
  if (cortos_IsNcRamAddr((void*)hdr)) {
    cortos_brel_ncram((void*)hdr);
  } else {
    cortos_brel((void*)hdr);
  }
}
% end


uint32_t cortos_writeMessages(CortosQueueHeader *hdr, uint8_t *msgs, uint32_t count) {
  uint8_t *dest = 0, *src = 0; // nullptr
  uint32_t process = count;
  uint32_t i;

  cortos_lock_acquire_buzy(hdr->lock);

  uint32_t totalMsgs      = hdr->totalMsgs;
  uint32_t writeIndex     = hdr->writeIndex;
  uint32_t length         = hdr->length;
  uint32_t msgSizeInBytes = hdr->msgSizeInBytes;
  uint8_t* queuePtr       = (uint8_t*)(hdr + 1);

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

  cortos_lock_release(hdr->lock);
  return (count - process);
}


uint32_t cortos_readMessages(CortosQueueHeader *hdr, uint8_t *msgs, uint32_t count) {
  uint8_t *dest = 0, *src = 0; // nullptr
  uint32_t process = count;
  uint32_t i;

  cortos_lock_acquire_buzy(hdr->lock);              // ACQUIRE LOCK

  uint32_t totalMsgs      = hdr->totalMsgs;
  uint32_t readIndex      = hdr->readIndex;
  uint32_t length         = hdr->length;
  uint32_t msgSizeInBytes = hdr->msgSizeInBytes;
  uint8_t* queuePtr       = (uint8_t*)(hdr + 1);

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

  cortos_lock_release(hdr->lock);              // RELEASE LOCK
  return (count - process);
}

