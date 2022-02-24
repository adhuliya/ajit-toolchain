
#ifndef CORTOS_LOCKS_H
#define CORTOS_LOCKS_H

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////

// Usage Note:
// lockIndex = cortos_reserveLockVar(); // assuming (lockIndex != -1)
// cortos_lock_acquire_buzy(lockIndex);
//   CRITICAL_SECTION_CODE...
// cortos_lock_release(lockIndex);
// cortos_freeLockVar(lockIndex);
// ----or-------or--------
// status = cortos_lock_acquire(<index: an-integer-index>);
// if (status == 1) {
//   CRITICAL_SECTION_CODE...
//   cortos_lock_release(<index: an-integer-index>);
// }

// NOTE: Use the same index to synchronize two or more threads.

#define __MAX_LOCK_VARS {{ confObj.software.locks.userLocks }}

// For Non-Cacheable Locks
// Reserve an unused lock variable id from cortos.
//   It returns the lock variable id of the lock reserved.
//   If no lock is available it returns -1.
// Once a lock is reserved it is assumed to be held by the caller,
// until it is freed.
int cortos_reserveLockVar();

// For Non-Cacheable Locks
// Free a lock variable for reuse by cortos.
void cortos_freeLockVar(int lockId);

// For Non-Cacheable Locks
int cortos_lock_acquire_buzy(int index);
int cortos_lock_acquire(int index);
void cortos_lock_release(int index);

// For Cacheable Locks
// Similar to the reserve/free API for non-cacheable locks above.
int cortos_reserveLockVar_cacheable();
void cortos_freeLockVar_cacheable(int lockId);

// For Cacheable Locks
int cortos_lock_acquire_buzy_cacheable(int index);
int cortos_lock_acquire_cacheable(int index);
void cortos_lock_release_cacheable(int index);


////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_locking_declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_locking_declarations_internal
////////////////////////////////////////////////////////////////////////////////

// For Non-Cacheable Locks
// lock functions for the internal use in CoRTOS
int __cortos_lock_acquire_buzy(int index);
int __cortos_lock_acquire(int index);
void __cortos_lock_release(int index);

// reserved lock indexes for internal use
#define __RES_LOCK_INDEX_BGET 0
#define __RES_LOCK_INDEX_PRINTF 1
#define __RES_LOCK_GET_Q_ID 2
#define __RES_LOCK_GET_LOCK_ID 3
#define __RES_LOCK_INDEX_BGET_NCRAM 4

// For Cacheable Locks: TODO (later if needed)

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_locking_declarations_internal
////////////////////////////////////////////////////////////////////////////////



#endif CORTOS_LOCKS_H
