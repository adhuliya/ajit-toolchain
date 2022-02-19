
#include <cortos_locks.h>

char syncLockVars[__MAX_LOCK_VARS];
char syncLockVarsCacheable[__MAX_LOCK_VARS];

int cortos_reserveLockVar() {
  int i, lid = -1;
  __cortos_lock_acquire_buzy(__RES_LOCK_GET_LOCK_ID);
  for (i=0; i < __MAX_LOCK_VARS; ++i) {
    if(syncLockVars[i] == 0) {
      syncLockVars[i] = 1;
      lid = i;
      break;
    }
  }
  __cortos_lock_release(__RES_LOCK_GET_LOCK_ID);
  return lid;
}


void cortos_freeLockVar(int lockId) {
  if (lockId >= 0 && lockId < __MAX_LOCK_VARS) {
    __cortos_lock_acquire_buzy(__RES_LOCK_GET_LOCK_ID);
    syncLockVars[lockId] = 0;
    __cortos_lock_release(__RES_LOCK_GET_LOCK_ID);
  }
}

int cortos_reserveLockVar_cacheable() {
  int i, lid = -1;
  __cortos_lock_acquire_buzy(__RES_LOCK_GET_LOCK_ID);
  for (i=0; i < __MAX_LOCK_VARS; ++i) {
    if(syncLockVarsCacheable[i] == 0) {
      syncLockVarsCacheable[i] = 1;
      lid = i;
      break;
    }
  }
  __cortos_lock_release(__RES_LOCK_GET_LOCK_ID);
  return lid;
}


void cortos_freeLockVar_cacheable(int lockId) {
  if (lockId >= 0 && lockId < __MAX_LOCK_VARS) {
    __cortos_lock_acquire_buzy(__RES_LOCK_GET_LOCK_ID);
    syncLockVarsCacheable[lockId] = 0;
    __cortos_lock_release(__RES_LOCK_GET_LOCK_ID);
  }
}

