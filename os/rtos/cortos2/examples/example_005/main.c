/* Create global variables and ensure that they are initialized to zero */
#include <math.h>
#include <cortos.h>

#define SIZE_A 100

int32_t var01[SIZE_A];
int32_t var05[SIZE_A][SIZE_A];
int64_t var07[SIZE_A][SIZE_A];
double var10[SIZE_A];

void main() {
  uint32_t sum = 0;
  double sumd = 0;
  uint32_t i, j;

  for (i = 0; i < SIZE_A; ++i) {
    sum += var01[i];
  }

  for (i = 0; i < SIZE_A; ++i) {
    for (j = 0; j < SIZE_A; ++j) {
      sum += var05[i][j];
    }
  }

  for (i = 0; i < SIZE_A; ++i) {
    for (j = 0; j < SIZE_A; ++j) {
      sum += var07[i][j];
    }
  }

  for (i = 0; i < SIZE_A; ++i) {
    sumd += var10[i];
  }

  sum += (uint32_t)sumd;

  cortos_exit(sum); // sum must be zero
}

