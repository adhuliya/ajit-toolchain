/* 
 * Program to test  the various macros in the  SPARC implementation of
 * assembler etc. in the GNU Binutils.
 *
 * (C) Abhijat Vichare. 2018.
 */

#include <stdio.h>
#include <unistd.h>		/* for getopt() */
#include <opcode/sparc.h>	/* For Binutils sparc data structures */

#define E_OK                            0
#define E_WRONG_COMMANDLINE            -1

#include "gas-macros.h"		/* This file copies the macros in opcodes/sparc-opc.c into itself. */

typedef union i2uc
{
  int x;
  unsigned char y[sizeof(int)];
} INT2UCHAR;

typedef union ul2uc
{
  unsigned long x;
  unsigned char y[sizeof(unsigned long)];
} ULONG2UCHAR;

typedef union c2b
{
  struct bits {
    unsigned int b7:1;
    unsigned int b6:1;
    unsigned int b5:1;
    unsigned int b4:1;
    unsigned int b3:1;
    unsigned int b2:1;
    unsigned int b1:1;
    unsigned int b0:1;
  } x;
  unsigned char in;
} UCHAR2BITS;

int x, y, i, b, a;
char bitrep[10];

int       convert_unsigned_char_to_bits      (unsigned char);
/* int       print_in_bits                      (char name[], unsigned long val); */
int       print_in_bits                      (unsigned long val);
void      print_bit_offsets                  (void);

void      help                               (char *);

void
help                               (char *pn)
{
  printf ("Usage: %s [options]\n", pn);
  printf ("Options are:\n");
  printf ("   -x <val> : Value in hexadecimal of OP field.\n");
  printf ("   -y <val> : Value in hexadecimal of OP3 field.\n");
  printf ("   -i <val> : Value in hexadecimal of IMM field.\n");
  printf ("   -b <val> : Value in hexadecimal of I field.\n");
  printf ("   -a <val> : Value in hexadecimal of bits 7 through 9.\n");
  printf ("\n");
}

int
main (int argc, char *argv[])
{
  int   ec      = E_OK;
  /* char *options = "x:y:i:b:a:h"; */
  /* int   optval  = 0; */
  const int lines_between_bit_offsets = 10;

  int   i       = 0;

  printf ("== II There are %d opcodes for Sparc + Ajit.\n\n", sparc_num_opcodes);

      /* if ((opcode->match & insn) == opcode->match */
      /*     && (opcode->lose & insn) == 0) */

  printf ("| %-4s | %-10s | %39s | %39s | %39s | \n",
	  "SrNo", "Name", "Match", "Lose", "Match ^ Lose");
  /* printf ("| %-10s | %39s | %39s | %39s | \n", "Name", "Match", "Lose", "Match ^ Lose"); */
  for (i = 0; i < sparc_num_opcodes; i++) {
    unsigned long m = sparc_opcodes[i].match;
    unsigned long l = sparc_opcodes[i].lose;

    if (i % lines_between_bit_offsets == 0)
      print_bit_offsets ();

    printf ("| %04d ", i);
    printf ("| %-10s | ", sparc_opcodes[i].name);
    print_in_bits (l);
    printf (" | ");
    print_in_bits (m);
    printf (" | ");
    print_in_bits ((l ^ m));
    printf (" | ");
    printf ("\n");
  }

  return ec;
}

void
print_bit_offsets                  (void)
{
  printf ("| %4s | %-10s |", " ", "Offsets");
  /* printf (" %39s | %39s |"); */
  /* printf ("                                        "); */
  printf ("31   27   23   19   15   11  8 7  4 3  0");
  printf (" |");
  printf ("31   27   23   19   15   11  8 7  4 3  0");
  printf (" |");
  printf ("31   27   23   19   15   11  8 7  4 3  0");
  printf (" | ");
  printf ("\n");

  /* printf ("| %-10s | %39s | %39s | \n", "Name", "Match", "Lose"); */

  return;
}

/* int */
/* print_in_bits                      (char name[], unsigned long val) */
int
print_in_bits                      (unsigned long val)
{
  int ec = 0;
  int j  = 0;

  /* INT2UCHAR x; */
  ULONG2UCHAR x;

  x.x = val;

  /* printf ("%-40s = 0x%08lX (", name, val); */
  /* for (j = sizeof (unsigned long) - 1; j >= 0; j--) { */
  for (j = (sizeof (unsigned long)/2) - 1; j >= 0; j--) {
    convert_unsigned_char_to_bits (x.y[j]);
    printf ("%s%s", bitrep, (j == 0) ? "" : " ");
  }
  /* printf (")\n"); */
  
  return ec;
}

/* int */
/* convert_unsigned_char_to_bits (unsigned char in, char *br[]) */
int
convert_unsigned_char_to_bits (unsigned char in)
{
  int ec = 0;
  int j;
  UCHAR2BITS x;

  for (j = 0; j < 10; bitrep[j++] = 0); /* Clear up previous conversion. */
  
  x.in = in;

  bitrep[9] = 0;		/* NULL string terminator. */
  
  bitrep[0] = (x.x.b0 == 0) ? '0' : '1';
  bitrep[1] = (x.x.b1 == 0) ? '0' : '1';
  bitrep[2] = (x.x.b2 == 0) ? '0' : '1';
  bitrep[3] = (x.x.b3 == 0) ? '0' : '1';
  bitrep[4] = ' ';		/* Separate the nibbles. */
  bitrep[5] = (x.x.b4 == 0) ? '0' : '1';
  bitrep[6] = (x.x.b5 == 0) ? '0' : '1';
  bitrep[7] = (x.x.b6 == 0) ? '0' : '1';
  bitrep[8] = (x.x.b7 == 0) ? '0' : '1';

  return ec;
}
