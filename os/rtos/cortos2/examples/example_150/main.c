/** A reader-writer test program.

A writer sends four values to the reader.
The reader collects the values and sums them up.
*/

#include <math.h>
#include <cortos.h>

#define TOTAL_MESSAGES 4

void main() {} // important, but kept empty.

void cortos_entry_func_001() {
  uint32_t sentCount, i, totalSent = 0;
  uint32_t msgs[TOTAL_MESSAGES];

  CORTOS_TRACE("Hello from Sender!");
  for (i = 0; i < TOTAL_MESSAGES; ++i) {
    msgs[i] = i;
  }

  while (totalSent < TOTAL_MESSAGES) {
    sentCount = cortos_writeMessages(CORTOS_QUEUE_BOB,
      (uint8_t*)(msgs+totalSent), TOTAL_MESSAGES);
    CORTOS_DEBUG("Sending %d messages: sent %d.",
      TOTAL_MESSAGES-totalSent, sentCount);
    totalSent += sentCount;
  }

  cortos_exit(totalSent);
}

void cortos_entry_func_010() {
  /* do something */
  return;
}

void cortos_entry_func_101() {
  uint32_t sum = 0;
  uint32_t i = 0, count;
  uint32_t msgs[TOTAL_MESSAGES];

  CORTOS_TRACE("Hello from Receiver!");
  while(i < TOTAL_MESSAGES) {
    count = cortos_readMessages(CORTOS_QUEUE_BOB, (uint8_t*)(msgs+i), TOTAL_MESSAGES-i);
    i += count;
    if (count) {
      CORTOS_DEBUG("Received %d messages. Need %d more.", count, TOTAL_MESSAGES-i);
    }
  }

  for (i = 0; i < TOTAL_MESSAGES; ++i) {
    sum += msgs[i];
  }

  cortos_exit(sum);
}

void cortos_entry_func_110() {
  /* do something */
  return;
}
