/** A reader-writer test program (without locks).

A writer sends four values to the reader.
The reader collects the values and sums them up.

Since there is a single reader and a single writer,
we have initialized the queue with SINGLE_RW_QUEUE,
which avoids the usage of locks.
*/

#include <math.h>
#include <cortos.h>

#define TOTAL_MESSAGES 4

CortosQueueHeader *hdr;

void main() {} // important, but kept empty.

void setup() {
  hdr = cortos_reserveQueue(
      sizeof(uint32_t) /*single msg size in bytes*/,
      2 /*length i.e. max messages in the queue*/,
      1 /*1 means non-cacheable*/);
  hdr->misc = SINGLE_RW_QUEUE;
}

void cortos_entry_func_001() {
  uint32_t sentCount, i, totalSent = 0;
  uint32_t msgs[TOTAL_MESSAGES];

  CORTOS_TRACE("Hello from Sender!");
  for (i = 0; i < TOTAL_MESSAGES; ++i) {
    msgs[i] = i;
  }

  while (totalSent < TOTAL_MESSAGES) {
    sentCount = cortos_writeMessages(hdr,
      (uint8_t*)(msgs+totalSent), (TOTAL_MESSAGES-totalSent));
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
  CORTOS_TRACE("Hello from Receiver: now queue hdr address is %lu.", hdr);
  while(i < TOTAL_MESSAGES) {
    count = cortos_readMessages(hdr, (uint8_t*)(msgs+i), TOTAL_MESSAGES-i);
    i += count;
    if (count) {
      CORTOS_DEBUG("Received %d messages. Need %d more.", count, TOTAL_MESSAGES-i);
    }
  }

  for (i = 0; i < TOTAL_MESSAGES; ++i) {
    sum += msgs[i];
  }
  CORTOS_DEBUG("Received values sum = %d", sum);

  cortos_exit(sum);
}

void cortos_entry_func_110() {
  /* do something */
  return;
}

