#include<math.h>
#include "ajit_cortos.h"

#define SIZE 80

int *i0 = SHARED_INT_ADDR_0;
int *i1 = SHARED_INT_ADDR_1;

AjitMessage msg1;
AjitMessage msg2;


void main() {} // important, but keep empty.

void ajit_cortos_entry_func_001() {
  // allocate memory and write data
  int *a = (int*)ajit_bget(sizeof(int) * 20);
  a[0] = 10;
  a[19] = 11;

  // send ajit message
  msg1.a_code = 1;
  msg1.a_ptr = a;
  writeAjitMessage(0, &msg1);
}

void ajit_cortos_entry_func_010() {
  return;
}

void ajit_cortos_entry_func_101() {
  // wait for a message
  while(!readAjitMessage(0, &msg2));

  // process the message
  int *arr = (int*)msg2.a_ptr;
  *i0 = arr[0];
  *i1 = arr[19];

  // release the memory
  ajit_brel(msg2.a_ptr);
}

void ajit_cortos_entry_func_110() {
  return;
}


