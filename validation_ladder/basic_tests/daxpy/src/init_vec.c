#include <stdint.h>
extern float a[VECTORSIZE];
extern float b[VECTORSIZE];

void vectorGen()
{
  int i;
  
  for (i = 0; i < VECTORSIZE; i += 4) {

    float ti = i;
    a[i]   = ti;
    a[i+1] = ti+1.0;
    a[i+2] = ti+2.0;
    a[i+3] = ti+3.0;
    b[i] =   ti + 0.5;
    b[i+1] = ti + 1.5;
    b[i+2] = ti+ 2.5;
    b[i+3] = ti+ 3.5;
  }
}
