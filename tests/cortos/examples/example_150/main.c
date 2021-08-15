#include<math.h>
#include "cortos.h"

int b;
int *i0 = SHARED_INT_ADDR_0;
int *i1 = SHARED_INT_ADDR_1;
int totalMsgs = 4;

CortosMessage msg1;
CortosMessage msg2;


void main() {} // important, but keep empty.

void cortos_entry_func_001() {
  msg1.intArr[0] = 1;
  CORTOS_TRACE("Sending Message 1");
  writeCortosMessage(0, &msg1);

  msg1.intArr[0] = 2;
  CORTOS_TRACE("Sending Message 2");
  writeCortosMessage(0, &msg1);

  msg1.intArr[0] = 6;
  CORTOS_TRACE("Sending Message 3");
  writeCortosMessage(0, &msg1);

  msg1.intArr[0] = 1;
  CORTOS_TRACE("Sending Message 4");
  writeCortosMessage(0, &msg1);

  cortos_exit(0);
}

void cortos_entry_func_010() {
  return;
}

void cortos_entry_func_101() {
  int i, status;
  i = 0;
  while(i < totalMsgs) {
    status = readCortosMessage(0, &msg2);
    CORTOS_TRACE("Received Message %d", i+1);
    if (status) {
      *i0 += msg2.intArr[0];
      ++i;
    }
  }
  cortos_exit(0);
}

void cortos_entry_func_110() {
  return;
}


