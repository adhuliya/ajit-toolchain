#include <math.h>
#include <cortos.h>

int32_t b;

void main() {
  b = (int32_t)cos(0);
  CORTOS_DEBUG("Hello There");
  cortos_exit(0);
}

