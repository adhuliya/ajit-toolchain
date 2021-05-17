#include <stdio.h>

int
main (void)
{
   int x1 = 0xAA;
   int x2 = 0x3;
   int x3 = 0xCC;

   int x4 = (x1 >> x2);
   int x5 = x4 & x3;

   int i = 0;
   int j = 0;

   printf ("x1 = 0x%08X.\n", x1);
   printf ("x2 = 0x%08X.\n", x2);
   printf ("x3 = 0x%08X.\n", x3);
   printf ("x4 = 0x%08X.\n", x4);
   printf ("x5 = 0x%08X.\n", x5);

   j = x1;
   printf ("j  = 0x%08X.\n", j);
   for (i = x2; i > 0; i--) {
      j = j >> 1;
      printf ("j  = 0x%08X.\n", j);
   }

   return 0;
}

