/* 
 * Program to verify bit operators in C.
 */

#include <stdio.h>

unsigned char op1 = 0xAA;
unsigned char op2 = 0x55;
unsigned char op3 = 0xA5;
unsigned char op4 = 0x5A;

int
main (int c, char *v[])
{
  printf ("== %-15s: 0x%02X %s 0x%02X = 0x%02X\n",
	  "Bit XOR", op1, "^", op2, (op1 ^ op2));
  printf ("== %-15s: 0x%02X %s 0x%02X = 0x%02X\n",
	  "Bit  OR", op1, "|", op2, (op1 | op2));
  printf ("== %-15s: 0x%02X %s 0x%02X = 0x%02X\n",
	  "Bit AND", op1, "&", op2, (op1 & op2));
  printf ("\n");

  printf ("== %-15s: 0x%02X %s 0x%02X = 0x%02X\n",
	  "Bit XOR", op1, "^", op1, (op1 ^ op1));
  printf ("== %-15s: 0x%02X %s 0x%02X = 0x%02X\n",
	  "Bit  OR", op1, "|", op1, (op1 | op1));
  printf ("== %-15s: 0x%02X %s 0x%02X = 0x%02X\n",
	  "Bit AND", op1, "&", op1, (op1 & op1));
  printf ("\n");

  return 0;
}
