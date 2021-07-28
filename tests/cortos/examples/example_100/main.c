/*
 * Author: Anshuman Dhuliya.
 *
 * Two threads increment a shared location MAX_LIMIT times.
 * The value of the shared location should be MAX_LIMIT*2.
 *
 */

#include<math.h>
#include "ajit_cortos.h"

#define MAX_LIMIT 1000

int b;
int *i0 = SHARED_INT_ADDR_0;
int *i1 = SHARED_INT_ADDR_1;

void main() {} // important, but keep empty.

void ajit_cortos_entry_func_001() {
  int i;
  for (i = 0; i < MAX_LIMIT; ++i) {
    ajit_lock_acquire_buzy(0);
    *i0 += 1;
    ajit_lock_release(0);
  }
}

void ajit_cortos_entry_func_010() {
  return;
}

void ajit_cortos_entry_func_101() {
  int i;
  for (i = 0; i < MAX_LIMIT; ++i) {
    ajit_lock_acquire_buzy(0);
    *i0 += 1;
    ajit_lock_release(0);
  }
}

void ajit_cortos_entry_func_110() {
  // b = (int)cos(0);
}


