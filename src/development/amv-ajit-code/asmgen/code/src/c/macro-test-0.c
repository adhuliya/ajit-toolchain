/* 
 * Program to test  the various macros in the  SPARC implementation of
 * assembler etc. in the GNU Binutils.
 *
 * (C) Abhijat Vichare. 2018.
 */

#include <stdio.h>
#include <unistd.h>		/* for getopt() */

#define E_OK                            0
#define E_WRONG_COMMANDLINE            -1

/* Macros from SPARC header, sparc.h, of GNU Binutils 2.2. */
#define OP2(x)		(((x) & 0x7) << 22)  /* Op2 field of format2 insns.  */
#define OP3(x)		(((x) & 0x3f) << 19) /* Op3 field of format3 insns.  */
#define OP(x)		((unsigned) ((x) & 0x3) << 30) /* Op field of all insns.  */
#define OPF(x)		(((x) & 0x1ff) << 5) /* Opf field of float insns.  */
#define OPF_LOW5(x)	OPF ((x) & 0x1f)     /* V9.  */
#define OPF_LOW4(x)	OPF ((x) & 0xf)      /* V9.  */
#define F3F(x, y, z)	(OP (x) | OP3 (y) | OPF (z)) /* Format3 float insns.  */
#define F3I(x)		(((x) & 0x1) << 13)  /* Immediate field of format 3 insns.  */
#define F2(x, y)	(OP (x) | OP2(y))    /* Format 2 insns.  */
#define F3(x, y, z)	(OP (x) | OP3(y) | F3I(z)) /* Format3 insns.  */
#define F1(x)		(OP (x))
#define DISP30(x)	((x) & 0x3fffffff)
#define ASI(x)		(((x) & 0xff) << 5)  /* Asi field of format3 insns.  */
#define RS2(x)		((x) & 0x1f)         /* Rs2 field.  */
#define SIMM13(x)	((x) & 0x1fff)       /* Simm13 field.  */
#define RD(x)		(((x) & 0x1f) << 25) /* Destination register field.  */
#define RS1(x)		(((x) & 0x1f) << 14) /* Rs1 field.  */
#define RS3(x)		(((x) & 0x1f) << 9)  /* Rs3 field.  */
#define ASI_RS2(x)	(SIMM13 (x))
#define MEMBAR(x)	((x) & 0x7f)
#define SLCPOP(x)	(((x) & 0x7f) << 6)  /* Sparclet cpop.  */

/* Our test macros */
/* AJIT Additions */
#define OP_AJIT_BIT_5(x)          (((x) & 0x1) << 5)                          /* Set the 6th bit, i.e. 1st unused, for AJIT */
#define F4(x, y, z, b)            (F3(x, y, z) | OP_AJIT_BIT_5(b))            /* Just set the 5th bit, and you are done! */
#define OP_AJIT_BIT_5_AND_6(x)    (((x) & 0x3) << 5)                          /* Set the 5th and 6th bits for AJIT */
#define F5(x, y, z, b)            (F3(x, y, z) | OP_AJIT_BIT_5_AND_6 (b))     /* Just set the 5th bit, and you are done! */
#define OP_AJIT_BIT_7_THRU_9(x)   (((x) & 0x7) << 7)                          /* Set the 5th and 6th bits for AJIT */
#define F6(x, y, z, b, a)         (F5 (x, y, z, b) | OP_AJIT_BIT_7_THRU_9(a)) /* Set bits 7 through 9 too. */

typedef union i2uc
{
  int x;
  unsigned char y[sizeof(int)];
} INT2UCHAR;

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
int       print_in_bits                      (char name[], int val);

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
  char *options = "x:y:i:b:a:h";
  int   optval  = 0;

  
  if (argc == 1) {
    printf ("Value in hexadecimal of OP field: ");
    scanf ("%x", &x);
    printf ("Value in hexadecimal of OP3 field: ");
    scanf ("%x", &y);
    printf ("Value in hexadecimal of IMM field: ");
    scanf ("%x", &i);
    printf ("Value in hexadecimal of I field: ");
    scanf ("%x", &b);
    printf ("Value in hexadecimal of bits 7 through 9: ");
    scanf ("%x", &a);
  } else if (argc == 11) {
    optval = getopt (argc, argv, options);
    while (optval != -1) {
      switch (optval) {
      case 'x': {sscanf (optarg, "%x", &x); break;}
      case 'y': {sscanf (optarg, "%x", &y); break;}
      case 'i': {sscanf (optarg, "%x", &i); break;}
      case 'b': {sscanf (optarg, "%x", &b); break;}
      case 'a': {sscanf (optarg, "%x", &a); break;}
      case 'h':
      default:  {help (argv[0]); break;}
      }
      optval = getopt (argc, argv, options);
    }
  } else {
    fprintf (stderr, "Error: Incomplete or incorrect command line of program %s.\n", argv[0]);
    help (argv[0]);
    ec = E_WRONG_COMMANDLINE;
  }

  if (ec == E_OK) {
    printf ("%-40s   %10s 31   27   23   19   15   11    7    3  0\n", " ", " ");
    print_in_bits ("x", x);
    print_in_bits ("y", y);
    print_in_bits ("i", i);
    print_in_bits ("b", b);
    print_in_bits ("a", a);
    printf ("\n");
    print_in_bits ("~x", ~x);
    print_in_bits ("~y", ~y);
    print_in_bits ("~i", ~i);
    print_in_bits ("~b", ~b);
    print_in_bits ("~a", ~a);
    printf ("\n");
    printf ("%-40s   %10s 31   27   23   19   15   11    7    3  0\n", " ", " ");
    print_in_bits ("OP(x)", OP(x));
    print_in_bits ("OP3(y)", OP3(y));
    print_in_bits ("F3I(i)", F3I(i));
    print_in_bits ("F3(x, y, i)", F3(x, y, i));
    printf ("\n");
    print_in_bits ("OP(~x)", OP(~x));
    print_in_bits ("OP3(~y)", OP3(~y));
    print_in_bits ("F3I(~i)", F3I(~i));
    print_in_bits ("F3(~x, ~y, ~i)", F3(~x, ~y, ~i));
    printf ("\n");
    printf ("%-40s   %10s 31   27   23   19   15   11    7    3  0\n", " ", " ");
    print_in_bits ("OP_AJIT_BIT_5(b)", OP_AJIT_BIT_5(b));
    print_in_bits ("F4(x, y, i, b)", F4(x, y, i, b));
    print_in_bits ("OP_AJIT_BIT_5(~b)", OP_AJIT_BIT_5(~b));
    print_in_bits ("F4(~x, ~y, ~i, ~b)", F4(~x, ~y, ~i, ~b));
    printf ("\n");
    print_in_bits ("OP_AJIT_BIT_5_AND_6 (b)", OP_AJIT_BIT_5_AND_6(b));
    print_in_bits ("F5(x, y, i, b)", F5(x, y, i, b));
    print_in_bits ("F5(~x, ~y, ~i, ~b)", F5(~x, ~y, ~i, ~b));
    print_in_bits ("(1<<12)", (1<<12));
    print_in_bits ("(0x7f<<5)", (0x7f<<5));
    print_in_bits ("OP_AJIT_BIT_5_AND_6 (~b)", OP_AJIT_BIT_5_AND_6(~b));
    print_in_bits ("F5(~x, ~y, ~i, ~b)|(1<<12)|(0x7f<<5)", F5(~x, ~y, ~i, ~b)|(1<<12)|(0x7f<<5));
    printf ("\n");
    printf ("%-40s   %10s 31   27   23   19   15   11    7    3  0\n", " ", " ");
    print_in_bits ("OP_AJIT_BIT_7_THRU_9 (a)", OP_AJIT_BIT_7_THRU_9(a));
    print_in_bits ("F6(x, y, i, b, a)", F6(x, y, i, b, a));
    print_in_bits ("OP_AJIT_BIT_7_THRU_9 (~a)", OP_AJIT_BIT_7_THRU_9(~a));
    print_in_bits ("F6(~x, ~y, ~i, ~b, ~a)", F6(~x, ~y, ~i, ~b, ~a));
    printf ("\n");
    print_in_bits ("Final OpCode template", F6(x, y, i, b, a));
    printf ("\n");
  }
  
  return ec;
}

int
print_in_bits                      (char name[], int val)
{
  int ec = 0;
  int j  = 0;

  INT2UCHAR x;

  x.x = val;

  printf ("%-40s = 0x%08X (", name, val);
  for (j = sizeof (int) - 1; j >= 0; j--) {
    convert_unsigned_char_to_bits (x.y[j]);
    printf ("%s%s", bitrep, (j == 0) ? "" : " ");
  }
  printf (")\n");
  
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
