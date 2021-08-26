/**
A simple example to demonstrate running two functions on
two separate Ajit Threads.
*/

#include<math.h>
#include "cortos.h"

int b;

void main() {} // important, but kept empty

void ajit_entry_func_001() {
  b = (int)cos(0);
  cortos_exit(0); // safely exit
}

void ajit_entry_func_010() {
  b = (int)cos(0);
  cortos_exit(0); // safely exit
}
