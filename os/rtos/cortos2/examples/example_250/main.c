/** Allocate memory and send its pointer via queue.
*/
#include <math.h>
#include <cortos.h>

#define SIZE 20

CortosQueueHeader * volatile hdr;

void main() {} // important, but keep empty.

void startup_initialization() {
  hdr = cortos_reserveQueue(
      sizeof(uint32_t*) /*single msg size in bytes*/,
      2 /*length i.e. max messages in the queue*/,
      1 /*1 means non-cacheable*/);
  CORTOS_DEBUG("startup: hdr = %lu", hdr);
}

void cortos_entry_func_001() {
  // allocate memory and write data
  int sentCount = 0;
  CORTOS_DEBUG("Acquiring Memory! %lu", hdr);
  uint32_t *arr = (uint32_t*)cortos_bget(sizeof(uint32_t) * SIZE);
  arr[0]      = 0xF0;
  arr[SIZE-1] = 0x0F;

  CORTOS_TRACE("This will not get logged.");

  CORTOS_DEBUG("Sending Message!");
  while (sentCount == 0) {
    sentCount = cortos_writeMessages(hdr, (uint8_t*)(&arr), 1);
  }
  CORTOS_DEBUG("Message Sent!");

  cortos_exit(0); //safely exit
}

void cortos_entry_func_010() {
  /* do something */
  return;
}

void cortos_entry_func_101() {
  // wait for a message
  uint32_t *arr;
  CORTOS_DEBUG("Waiting for Message!");
  while(!cortos_readMessages(hdr, (uint8_t*)&arr, 1));

  CORTOS_DEBUG("Received Message!");

  // process the message
  uint32_t i0, i1;
  i0 = arr[0];
  i1 = arr[SIZE-1];

  CORTOS_DEBUG("Releasing Memory!");
  // release the memory
  cortos_brel(arr);

  cortos_exit(i0+i1); //safely exit
}

void cortos_entry_func_110() {
  /* do something */
  return;
}
