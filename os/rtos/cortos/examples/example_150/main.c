/** A reader-writer test program.

A writer sends four values to the reader.
The reader collects the values and sums them up.
*/

#include<math.h>
#include "cortos.h"

int b;
int *i0 = SHARED_INT_ADDR_0;
int *i1 = SHARED_INT_ADDR_1;
int totalMsgs = 4;

CortosMessage msg1;
CortosMessage msg2;


void main() {} // important, but kept empty.

void cortos_entry_func_001() {
  msg1.intArr[0] = 1;
  CORTOS_TRACE("Sending Message 1");
  cortos_writeMessage(0, &msg1);

  msg1.intArr[0] = 2;
  CORTOS_TRACE("Sending Message 2");
  cortos_writeMessage(0, &msg1);

  msg1.intArr[0] = 6;
  CORTOS_TRACE("Sending Message 3");
  crotos_writeMessage(0, &msg1);

  msg1.intArr[0] = 1;
  CORTOS_TRACE("Sending Message 4");
  cortos_writeMessage(0, &msg1);

  cortos_exit(0);
}

void cortos_entry_func_010() {
  return;
}

void cortos_entry_func_101() {
  int i, status;
  i = 0;
  while(i < totalMsgs) {
    status = cortos_readMessage(0, &msg2);
    if (status) {
      CORTOS_TRACE("Received Message %d", i+1);
      *i0 += msg2.intArr[0];
      ++i;
    }
  }
  cortos_exit(0);
}

void cortos_entry_func_110() {
  return;
}


