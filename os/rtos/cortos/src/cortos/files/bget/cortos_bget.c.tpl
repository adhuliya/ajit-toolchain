// Main function to manage bget library.
// It provides a msg queue based communication to the bget library.

% baseAddr = confObj.reservedMem.cortosBgetMemory.startAddr
% memSize = confObj.reservedMem.cortosBgetMemory.sizeInBytes

#include "bget.h"
#include "cortos.h"

int __mem_allocated = 0;

void __cortos_bpool() {
  if (__mem_allocated == 0) {
    // this if condition enters only once.
    cortos_res_lock_acquire_buzy(RES_LOCK_INDEX_BGET);

    bpool({{baseAddr}}, {{memSize}});

    cortos_res_lock_release(RES_LOCK_INDEX_BGET);

    __mem_allocated = 1;
  }
}


// get/allocate a memory of `size` bytes
void *cortos_bget(cortos_bufsize size) {
  void *base = 0;
  cortos_res_lock_acquire_buzy(RES_LOCK_INDEX_BGET);

  base = bget(size);

  cortos_res_lock_release(RES_LOCK_INDEX_BGET);

  return base;
}


// release/free an allocated memory chunk
void cortos_brel(void *buf) {
  cortos_res_lock_acquire_buzy(RES_LOCK_INDEX_BGET);

  brel(buf);

  cortos_res_lock_release(RES_LOCK_INDEX_BGET);
}

