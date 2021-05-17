#include <stdio.h>
#include <stdlib.h>

int nums = 1;			/* generate at least one number! */

int
main (int argc, char *argv[])
{
  int seed = rand ();
  int i = 0;

  if (argc == 2)
    nums = atoi (argv[1]);

  srand (seed);
  for (i = 0; i < nums; i++) {
    printf ("%d\n", rand());
  }

  return nums;
}

