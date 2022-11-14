
#include <cortos_locks.h>

uint8_t* lockStartAddr   = 0x40019000;
uint8_t* lockStartAddrNc = 0x4001a000; // non-cacheable
volatile uint8_t allocatedLocks[CORTOS_MAX_LOCKS];
volatile uint8_t allocatedLocksNc[CORTOS_MAX_LOCKS]; // non-cacheable
uint8_t* cortos_reservedLockAddr;
uint8_t* lockAddr;
#define LOGGING_LOCK_INDEX 0

void cortos_init_locks() {
  // lock for reserving locks
  uint8_t* lockStartAddr   = (uint8_t*)0x40019000;
  uint8_t* lockStartAddrNc = (uint8_t*)0x4001a000; // non-cacheable
  allocatedLocksNc[LOGGING_LOCK_INDEX] = 1;
  cortos_reservedLockAddr = lockStartAddrNc + LOGGING_LOCK_INDEX;
}

uint8_t* cortos_reserveLock(uint32_t nc) {
  int i = 0;
  char* resArr = nc ? allocatedLocksNc : allocatedLocks;
  lockAddr = nc ? lockStartAddrNc : lockStartAddr;

  cortos_lock_acquire_buzy(cortos_reservedLockAddr);

  for (; i < CORTOS_MAX_LOCKS; ++i) {
    if(resArr[i] == 0) {
      resArr[i] = 1;
      break;
    }
  }

  cortos_lock_release(cortos_reservedLockAddr);
  return (lockAddr + i);
}

void cortos_freeLock(uint8_t *lock) {
  if (lock >= lockStartAddr && lock < (lockStartAddr + CORTOS_MAX_LOCKS)) {
    cortos_lock_acquire_buzy(cortos_reservedLockAddr);
    allocatedLocks[lock - lockStartAddr] = 0;
    cortos_lock_release(cortos_reservedLockAddr);
  } else {
    cortos_lock_acquire_buzy(cortos_reservedLockAddr);
    allocatedLocksNc[lock - lockStartAddrNc] = 0;
    cortos_lock_release(cortos_reservedLockAddr);
  }
}

