#include<math.h>
#include "ajit_cortos.h"

int b;
int *i0 = SHARED_INT_ADDR_0;
int *i1 = SHARED_INT_ADDR_1;
int totalMsgs = 4;

AjitMessage msg1;
AjitMessage msg2;


void main() {} // important, but keep empty.

void ajit_cortos_entry_func_001() {
  msg1.intArr[0] = 1;
  writeAjitMessage(0, &msg1);

  msg1.intArr[0] = 2;
  writeAjitMessage(0, &msg1);

  msg1.intArr[0] = 6;
  writeAjitMessage(0, &msg1);

  msg1.intArr[0] = 1;
  writeAjitMessage(0, &msg1);
}

void ajit_cortos_entry_func_010() {
  return;
}

void ajit_cortos_entry_func_101() {
  int i, status;
  while(i < totalMsgs) {
    status = readAjitMessage(0, &msg2);
    if (status) {
      *i0 += msg2.intArr[0];
      ++i;
    }
  }
}

void ajit_cortos_entry_func_110() {
  return;
}


