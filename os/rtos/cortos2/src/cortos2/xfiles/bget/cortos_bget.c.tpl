// Main function to manage bget library.
// It provides a msg queue based communication to the bget library.

% startAddr = confObj.software.bget.getStartAddr()
% memSizeInBytes = confObj.software.bget.getSizeInBytes()

% startAddrNcram = confObj.hardware.memory.ncram.getFirstByteAddr()
% memSizeInBytesNcram = confObj.hardware.memory.ncram.getSizeInBytes()

#include "__bget.h"
#include "__bget_ncram.h"
#include "cortos_locks.h"
#include "cortos_bget.h"

#define BGET_LOCK_INDEX 2
#define BGET_NC_LOCK_INDEX 3
uint8_t* bgetLockAddr = 0;
uint8_t* bgetNcramLockAddr = 0;

void __cortos_bpool() {
  if (bgetLockAddr == 0) {

    bpool({{ startAddr }}, {{ memSizeInBytes }});

    // allocate lock
    uint8_t* lockStartAddrNc = (uint8_t*){{ confObj.software.locks.locksStartAddr }}; // non-cacheable
    allocatedLocksNc[BGET_LOCK_INDEX] = 1;
    bgetLockAddr = lockStartAddrNc + BGET_LOCK_INDEX;
  }
}


// get/allocate a memory of `size` bytes
void *cortos_bget(cortos_bufsize size) {
  void *base = 0;
  cortos_lock_acquire_buzy(bgetLockAddr);

  base = bget(size);

  cortos_lock_release(bgetLockAddr);

  return base;
}


// release/free an allocated memory chunk
void cortos_brel(void *buf) {
  cortos_lock_acquire_buzy(bgetLockAddr);

  brel(buf);

  cortos_lock_release(bgetLockAddr);
}

/////////////////////////////////////////////////////////////////////////////////////////
// BLOCK START: NCRAM realated
/////////////////////////////////////////////////////////////////////////////////////////


void __cortos_bpool_ncram() {
  if (bgetNcramLockAddr == 0) {
    bpool_ncram({{ startAddrNcram }}, {{ memSizeInBytesNcram }});

    // allocate lock
    uint8_t* lockStartAddrNc = (uint8_t*){{ confObj.software.locks.locksStartAddr }}; // non-cacheable
    allocatedLocksNc[BGET_NC_LOCK_INDEX] = 1;
    bgetNcramLockAddr = lockStartAddrNc + BGET_NC_LOCK_INDEX;
  }
}


// get/allocate a memory of `size` bytes
void *cortos_bget_ncram(cortos_bufsize size) {
  void *base = 0;
  cortos_lock_acquire_buzy(bgetNcramLockAddr);

  base = bget_ncram(size);

  cortos_lock_release(bgetNcramLockAddr);

  return base;
}


// release/free an allocated memory chunk
void cortos_brel_ncram(void *buf) {
  cortos_lock_acquire_buzy(bgetNcramLockAddr);

  brel_ncram(buf);

  cortos_lock_release(bgetNcramLockAddr);
}

/////////////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : NCRAM realated
/////////////////////////////////////////////////////////////////////////////////////////

