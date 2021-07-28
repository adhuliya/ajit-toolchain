#include<math.h>
#include "ajit_cortos.h"

#define SIZE 80

int b;
int *i0 = SHARED_INT_ADDR_0;
int *i1 = SHARED_INT_ADDR_1;
int totalMsgs = 4;
int *arr = 0;

AjitMessage msg1;
AjitMessage msg2;


void main() {} // important, but keep empty.

void ajit_cortos_entry_func_001() {
  int *a = (int*)ajit_bget(sizeof(int) * 20);
  a[0] = 10;
  a[19] = 11;
  arr = a;
}

void ajit_cortos_entry_func_010() {
  return;
}

void ajit_cortos_entry_func_101() {
  while(arr==0);
  *i0 = arr[0];
  *i1 = arr[19];
}

void ajit_cortos_entry_func_110() {
  return;
}


