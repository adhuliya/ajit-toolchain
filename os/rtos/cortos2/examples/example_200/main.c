/** Allocate memory and share between two threads. */

#include <math.h>
#include <cortos.h>

#define SIZE 80

uint32_t totalMsgs = 4;
uint32_t * volatile arr = 0;
volatile int flag = 0;

void main() {} // important, but keep empty.

void cortos_entry_func_001() {
  arr = (uint32_t*)cortos_bget(sizeof(uint32_t) * 20);
  if (arr == 0) {
    CORTOS_ERROR("Memory not allocated!");
    arr = 1;  // to make the other thread terminate
  }
  arr[0]  = 0x0F;
  arr[19] = 0xF0;
  flag = 1;
  CORTOS_INFO("Thread 0,0 finished! (%d, %d).", arr[0], arr[19]);
  cortos_exit(arr[0]+arr[19]); // safely exit
}

void cortos_entry_func_010() {
  return;
}

void cortos_entry_func_101() {
  uint32_t sum;

  while(flag==0);

  sum += arr[0];
  sum += arr[19];

  CORTOS_INFO("Thread 0,1 finished! (%d, %d).", arr[0], arr[19]);

  cortos_brel(arr);
  cortos_exit(sum); // safely exit
}

void cortos_entry_func_110() {
  return;
}
