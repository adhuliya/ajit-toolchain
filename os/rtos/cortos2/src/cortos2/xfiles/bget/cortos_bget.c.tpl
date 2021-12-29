// Main function to manage bget library.
// It provides a msg queue based communication to the bget library.

% startAddr = confObj.software.bget.getStartAddr()
% memSizeInBytes = confObj.software.bget.getSizeInBytes()

#include "__bget.h"
#include "__cortos.h"

int __mem_allocated = 0;

void __cortos_bpool() {
  if (__mem_allocated == 0) {
    // this if condition enters only once.
    __cortos_lock_acquire_buzy(__RES_LOCK_INDEX_BGET);

    bpool({{ startAddr }}, {{ memSizeInBytes }});

    __cortos_lock_release(__RES_LOCK_INDEX_BGET);

    __mem_allocated = 1;
  }
}


// get/allocate a memory of `size` bytes
void *cortos_bget(cortos_bufsize size) {
  void *base = 0;
  __cortos_lock_acquire_buzy(__RES_LOCK_INDEX_BGET);

  base = bget(size);

  __cortos_lock_release(__RES_LOCK_INDEX_BGET);

  return base;
}


// release/free an allocated memory chunk
void cortos_brel(void *buf) {
  __cortos_lock_acquire_buzy(__RES_LOCK_INDEX_BGET);

  brel(buf);

  __cortos_lock_release(__RES_LOCK_INDEX_BGET);
}

