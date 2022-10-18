
#ifndef CORTOS_LOCKS_H
#define CORTOS_LOCKS_H

#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////

#define CORTOS_MAX_LOCKS 256

extern volatile uint8_t allocatedLocks[CORTOS_MAX_LOCKS];
extern volatile uint8_t allocatedLocksNc[CORTOS_MAX_LOCKS]; // non-cacheable

////////////////////////////////////////////////////////////////////////////////
// Usage Note:
// lock = cortos_reserveLock(1); // non-cacheable lock
// cortos_lock_acquire_buzy(lock);
//   CRITICAL_SECTION_CODE...
// cortos_lock_release(lock);
// cortos_freeLock(lock);
// ----or-------or--------
// lock = cortos_reserveLock(1); // non-cacheable lock
// status = cortos_lock_acquire(<lock pointer>);
// if (status == 1) {
//   CRITICAL_SECTION_CODE...
//   cortos_lock_release(<lock pointer>);
// }
// cortos_freeLock(lock);
////////////////////////////////////////////////////////////////////////////////

#define CORTOS_MAX_LOCK_VARS 256

// For Cacheable/Non-Cacheable Locks
// Reserve an unused lock variable id from cortos.
//   It returns the lock variable id of the lock reserved.
//   If no lock is available it returns -1.
// Once a lock is reserved it is assumed to be held by the caller,
// until it is freed.
uint8_t* cortos_reserveLock(uint32_t nc);

// For Cacheable/Non-Cacheable Locks
// Free a lock variable for reuse by cortos.
void cortos_freeLock(uint8_t* lock);

// For Cacheable or Non-Cacheable Locks
int cortos_lock_acquire_buzy(uint8_t *lock);
int cortos_lock_acquire(uint8_t *lock);
void cortos_lock_release(uint8_t *lock);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////

#endif // CORTOS_LOCKS_H
