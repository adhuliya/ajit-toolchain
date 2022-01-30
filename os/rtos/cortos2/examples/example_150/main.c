/** A reader-writer test program.

A writer sends four values to the reader.
The reader collects the values and sums them up.
*/

#include <math.h>
#include <cortos.h>

#define TOTAL_MESSAGES 4

volatile uint32_t queueId = -1;

CortosMessage msg1;
CortosMessage msg2;

void main() {} // important, but kept empty.

void cortos_entry_func_001() {
  uint32_t msg_counter = 0, i;
  queueId = cortos_reserveQueue();

  for (i = 0; i < TOTAL_MESSAGES; ++i) {
    msg1.intArr[0] = 0x1 << i;
    CORTOS_TRACE("Sending Message %d: value = %d.", i, msg1.intArr[0]);
    cortos_writeMessage(queueId, &msg1);
    msg_counter += 1;
  }

  cortos_exit(msg_counter);
}

void cortos_entry_func_010() {
  /* do something */
  return;
}

void cortos_entry_func_101() {
  uint32_t sum = 0;
  uint32_t i = 0, status;

  while(queueId == -1);

  while(i < TOTAL_MESSAGES) {
    status = cortos_readMessage(queueId, &msg2);
    if (status) {
      CORTOS_TRACE("Received Message %d: value = %d.", i, msg2.intArr[0]);
      sum += msg2.intArr[0];
      ++i;
    }
  }

  cortos_exit(sum);
}

void cortos_entry_func_110() {
  /* do something */
  return;
}
