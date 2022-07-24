// This is a simple example that demonstrates a Hello World program.

#include <math.h>
#include <cortos.h>

uint32_t b;

/// A startup function that is called by thread 0,0.
/// This is the first user function to run on bootup.
/// All threads wait for this function to finish.
/// The user can add any system level initialization to this function.
void setup() {
  b = 13;
}

void main() {
  // printing is similar to calling printf()
  CORTOS_DEBUG("Hello There. Value of b is %d", b);
  b = (uint32_t) cos(0);
  #ifdef CORTOS_ENV
  CORTOS_DEBUG("CORTOS_ENV has been defined!");
  #endif
  cortos_exit(b);
}
