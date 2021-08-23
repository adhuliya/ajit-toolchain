#include<math.h>
#include "cortos.h"

int b;

void main() {
  b = (int)cos(0);
  CORTOS_DEBUG("Hello There");
  cortos_exit(0);
}

