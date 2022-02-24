#include <math.h>
#include <cortos.h>

uint32_t b;

void main() {
  b = (uint32_t)cos(0);
  CORTOS_DEBUG("Hello There");
  #ifdef CORTOS_ENV
  CORTOS_DEBUG("CORTOS_ENV defined!");
  #endif
  cortos_exit(b);
}

