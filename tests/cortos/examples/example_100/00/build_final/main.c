#include<math.h>
#include "ajit_cortos.h"

int b;

void main() {}

void ajit_entry_func_001() {
  int status;

  status = ajit_lock_acquire(0);
  if (status == 1) {
    // CRITICAL_SECTION_CODE...
    b = (int)cos(0);
    ajit_lock_release(0);
  }
}

void ajit_entry_func_010() {
  b = (int)cos(0);
}
