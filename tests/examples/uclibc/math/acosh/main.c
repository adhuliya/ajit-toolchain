#include<math.h>
#include<float.h>

int b;
void main() {
  // b sould be 710475
  // DBL_MAX == max representable finite floating point number
  b = (int)(acosh(DBL_MAX) * 1000);
}
