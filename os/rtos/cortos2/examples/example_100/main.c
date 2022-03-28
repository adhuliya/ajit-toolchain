/*
 * Author: Anshuman Dhuliya.
 *
 * Two threads increment a shared location MAX_LIMIT times.
 * The value of the shared location should be MAX_LIMIT*2.
 *
 */

#include <math.h>
#include <cortos.h>

//#define MAX_LIMIT    0x20
#define MAX_LIMIT    0x1000
#define MAX_LIMIT_X2 (MAX_LIMIT << 1)

int b;
volatile int global_var;
volatile uint8_t * volatile lockPtr = 0;

void main() {} // important, but keep empty.

void cortos_entry_func_001() {
  int i;
  lockPtr = cortos_reserveLock(1);
  CORTOS_DEBUG("001 reserved lock");
  for (i = 0; i < MAX_LIMIT; ++i) {
    cortos_lock_acquire_buzy(lockPtr);
    global_var += 1;
    CORTOS_DEBUG("001 %d", global_var);
    cortos_lock_release(lockPtr);
  }
  CORTOS_DEBUG("001 done: %d", global_var);
  while(global_var != MAX_LIMIT_X2);
  cortos_exit(global_var); // safely exit
}

void cortos_entry_func_010() {
  return;
}

void cortos_entry_func_101() {
  int i;
  while(lockPtr == 0);
  for (i = 0; i < MAX_LIMIT; ++i) {
    cortos_lock_acquire_buzy(lockPtr);
    global_var += 1;
    CORTOS_DEBUG("101 %d", global_var);
    cortos_lock_release(lockPtr);
  }
  CORTOS_DEBUG("101 done: %d", global_var);
  while(global_var != MAX_LIMIT_X2);
  cortos_exit(global_var); // safely exit
}

void cortos_entry_func_110() {
  // b = (int)cos(0);
}

