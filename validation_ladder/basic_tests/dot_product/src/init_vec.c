#include <stdint.h>
extern float a[VECTORSIZE];
extern float b[VECTORSIZE];

void vectorGen()
{
  int i;
  
  for (i = 0; i < VECTORSIZE; i += 4) {
    float ti = ((float) i) * 0.0001;
    a[i] = ti;
    a[i+1] = ti+ 0.0001;
    a[i+2] = ti+ 0.0001;
    a[i+3] = ti+ 0.0001;
    b[i] = ti;
    b[i+1] = ti+ 0.0001;
    b[i+2] = ti+ 0.0001;
    b[i+3] = ti+ 0.0001;
  }
}
