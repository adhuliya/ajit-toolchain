/*
 * Author: Anshuman Dhuliya.
 *
 * Two threads increment a shared location MAX_LIMIT times.
 * The value of the shared location should be MAX_LIMIT*2.
 *
 */

#include <math.h>
#include <cortos.h>

#define MAX_LIMIT    0x1000
#define MAX_LIMIT_X2 (MAX_LIMIT << 1)

int b;
volatile int global_var;
volatile int lockVar = -1;

void main() {} // important, but keep empty.

void cortos_entry_func_001() {
  int i;
  lockVar = cortos_reserveLockVar();
  for (i = 0; i < MAX_LIMIT; ++i) {
    cortos_lock_acquire_buzy(lockVar);
    global_var += 1;
    cortos_lock_release(lockVar);
  }
  while(global_var != MAX_LIMIT_X2);
  cortos_exit(global_var); // safely exit
}

void cortos_entry_func_010() {
  return;
}

void cortos_entry_func_101() {
  int i;
  while(lockVar == -1);
  for (i = 0; i < MAX_LIMIT; ++i) {
    cortos_lock_acquire_buzy(lockVar);
    global_var += 1;
    cortos_lock_release(lockVar);
  }
  while(global_var != MAX_LIMIT_X2);
  cortos_exit(global_var); // safely exit
}

void cortos_entry_func_110() {
  // b = (int)cos(0);
}

