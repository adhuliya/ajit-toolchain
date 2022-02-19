/**
A simple example to demonstrate running two functions on
two separate Ajit Threads.
*/

#include <math.h>
#include <cortos.h>

uint32_t b;

void main() {} // important, but kept empty

void ajit_entry_func_001() {
  b = (uint32_t)cos(0);
  cortos_exit(b); // safely exit
}

void ajit_entry_func_010() {
  b = (uint32_t)cos(0);
  cortos_exit(b); // safely exit
}
