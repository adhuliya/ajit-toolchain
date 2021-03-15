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

#define OP_AJIT_BIT_5(x)          (((x) & 0x1) << 5)                          /* Set the bit 5 (6th bit) for AJIT */
#define OP_AJIT_BIT_5_AND_6(x)    (((x) & 0x3) << 5)                          /* Set the bits 5 and 6 for AJIT */
#define OP_AJIT_BIT_7_THRU_9(x)   (((x) & 0x7) << 7)                          /* Set bits 7 through 9 for AJIT */

#define OP_AJIT_BITS_30_TO_31(x)    (((x) & 0x03) << 30) /* op, match */
#define OP_AJIT_BITS_25_TO_29(x)    (((x) & 0x1F) << 25) /* rd */
#define OP_AJIT_BITS_19_TO_24(x)    (((x) & 0x3F) << 19) /* op3, match */
#define OP_AJIT_BITS_14_TO_18(x)    (((x) & 0x1F) << 14) /* rs1 */
#define OP_AJIT_BITS_13_TO_13(x)    (((x) & 0x01) << 13) /* i */
#define OP_AJIT_BITS_05_TO_12(x)    (((x) & 0xFF) << 05) /* ???, set to zero */
#define OP_AJIT_BITS_00_TO_04(x)    (((x) & 0x1F) << 00) /* rs2 */
#define OP_AJIT_BITS_05_TO_13(x)    (((x) & 0x1FF) << 05) /* opf */
#define OP_AJIT_BITS_08_TO_12(x)    (((x) & 0x1F) << 8)
#define OP_AJIT_BITS_00_TO_07(x)    (((x) & 0xFF) << 00)

#define F1(x)		(OP (x))
#define F2(x, y)	(OP (x) | OP2(y))    /* Format 2 insns.  */
#define F3(x, y, z)	(OP (x) | OP3(y) | F3I(z)) /* Format3 insns.  */
#define F4(x, y, z, b)            (F3(x, y, z) | OP_AJIT_BIT_5(b))            /* Format 3 with bit 5 */
#define F5(x, y, z, b)            (F3(x, y, z) | OP_AJIT_BIT_5_AND_6 (b))     /* Format 3 with bits 5 and 6 */
#define F6(x, y, z, b, a)         (F5 (x, y, z, b) | OP_AJIT_BIT_7_THRU_9(a)) /* Format 3 with bits 5-6 and 7-9 */
#define F7(a, b, c, d)            (OP(a) | OP3(b) | F3I(c))
#define F8(a, b, c)               (OP_AJIT_BITS_30_TO_31(a) | \
				   OP_AJIT_BITS_19_TO_24(b) | \
				   OP_AJIT_BITS_05_TO_13(c))
#define F9(a, b, c)               (OP_AJIT_BITS_30_TO_31(a) | \
				   OP_AJIT_BITS_19_TO_24(b) | \
				   OP_AJIT_BITS_13_TO_13(c))
#define F9d(a, b, c)              (OP_AJIT_BITS_30_TO_31(a) | \
				   OP_AJIT_BITS_19_TO_24(b) | \
				   OP_AJIT_BITS_13_TO_13(1) | \
				   SIMM13(c))
#define F10(a, b, c, d)           (OP_AJIT_BITS_30_TO_31(a) | \
				   OP_AJIT_BITS_19_TO_24(b) | \
				   OP_AJIT_BITS_13_TO_13(c) | \
				   OP_AJIT_BITS_08_TO_12(0))


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
  
int f, a1, a2, a3, a4, a5;
char bitrep[10];

int       convert_unsigned_char_to_bits      (unsigned char);
int       print_in_bits                      (char name[], int val);

void      help                               (char *);

void
help                               (char *pn)
{
  printf ("Usage: %s [options]\n", pn);
  printf ("Options are:\n");
  printf ("   -f <m-val> : Evaluate macro F<m-val>.\n");
  printf ("   -1 <val>   : Value in hexadecimal of 1st parameter of macro F<m-val>.\n");
  printf ("   -2 <val>   : Value in hexadecimal of 2nd parameter of macro F<m-val>.\n");
  printf ("   -3 <val>   : Value in hexadecimal of 3rd parameter of macro F<m-val>.\n");
  printf ("   -4 <val>   : Value in hexadecimal of 4th parameter of macro F<m-val>.\n");
  printf ("   -5 <val>   : Value in hexadecimal of 5th parameter of macro F<m-val>.\n");
  printf ("As many value arguments as required by the F... macro should be given.\n");
  printf ("\n");
}

int
main (int argc, char *argv[])
{
  int   ec      = E_OK;
  char *options = "f:1:2:3:4:5:h";
  int   optval  = 0;

  if (argc == 1) {
    printf ("Macro number to evaluate : ");
    scanf ("%x", &f);
    printf ("Value in hexadecimal of 1st parameter of macro F%d : ", f);
    scanf ("%x", &a1);
    if (f > 1) {
      printf ("Value in hexadecimal of 2nd parameter of macro F%d : ", f);
      scanf ("%x", &a2);
      if (f > 2) {
	if ((f == 3) || (f == 8) || (f == 9)) {
	  printf ("Value in hexadecimal of 3rd parameter of macro F%d : ", f);
	  scanf ("%x", &a3);
	}
	if ((f == 4) || (f == 5) || (f == 7) || (f == 10)) {
	  printf ("Value in hexadecimal of 4th parameter of macro F%d : ", f);
	  scanf ("%x", &a4);
	}
	if (f == 6) {
	  printf ("Value in hexadecimal of 5th parameter of macro F%d : ", f);
	  scanf ("%x", &a5);
	}
      }
    }
  } else if ((argc > 1) && (argc < 13)) {
    optval = getopt (argc, argv, options);
    while (optval != -1) {
      switch (optval) {
      case 'f': {sscanf (optarg, "%x", &f); break;}
      case '1': {sscanf (optarg, "%x", &a1); break;}
      case '2': {sscanf (optarg, "%x", &a2); break;}
      case '3': {sscanf (optarg, "%x", &a3); break;}
      case '4': {sscanf (optarg, "%x", &a4); break;}
      case '5': {sscanf (optarg, "%x", &a5); break;}
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
    unsigned int the_val = 0;
    unsigned int the_inv_val = 0;
    char the_msg [1024];
    char the_inv_msg [1024];

    switch (f) {
    case 1:  {the_val = F1  (a1);
	the_inv_val = F1 (~a1);
	sprintf (the_msg, "F%d (0x%X)",                         f, a1);
	sprintf (the_inv_msg, "F%d (~0x%X) = F%d (0x%X)",       f, a1, f, ~a1);
	break; }
    case 2:  {the_val = F2  (a1, a2);
	the_inv_val = F2 (~a1, ~a2);
	sprintf (the_msg, "F%d (0x%X, 0x%X)",                   f, a1, a2);
	sprintf (the_inv_msg, "F%d (~0x%X, ~0x%X) = F%d (0x%X, 0x%X)", f, a1, a2, f, ~a1, ~a2);
	break; }
    case 3:  {the_val = F3  (a1, a2, a3);          
	the_inv_val = F3 (~a1, ~a2, ~a3);
	sprintf (the_msg, "F%d (0x%X, 0x%X, 0x%X)",             f, a1, a2, a3);
	sprintf (the_inv_msg, "F%d (~0x%X, ~0x%X, ~0x%X) = F%d (0x%X, 0x%X, 0x%X)", f, a1, a2, a3, f, ~a1, ~a2, ~a3);
	break; }
    case 4:  {the_val = F4  (a1, a2, a3, a4);      
	the_inv_val = F4 (~a1, ~a2, ~a3, ~a4);
	sprintf (the_msg, "F%d (0x%X, 0x%X, 0x%X, 0x%X)",       f, a1, a2, a3, a4);
	sprintf (the_inv_msg, "F%d (~0x%X, ~0x%X, ~0x%X, ~0x%X) = F%d (0x%X, 0x%X, 0x%X, 0x%X)",
		 f, a1, a2, a3, a4, f, ~a1, ~a2, ~a3, ~a4);
	break; }
    case 5:  {the_val = F5  (a1, a2, a3, a4);      
	the_inv_val = F5 (~a1, ~a2, ~a3, ~a4);
	sprintf (the_msg, "F%d (0x%X, 0x%X, 0x%X, 0x%X)",       f, a1, a2, a3, a4);
	sprintf (the_inv_msg, "F%d (~0x%X, ~0x%X, ~0x%X, ~0x%X) = F%d (0x%X, 0x%X, 0x%X, 0x%X)",
		 f, a1, a2, a3, a4, f, ~a1, ~a2, ~a3, ~a4);
	break; }
    case 6:  {the_val = F6  (a1, a2, a3, a4, a5);  
	the_inv_val = F6 (~a1, ~a2, ~a3, ~a4, ~a5);                 
	sprintf (the_msg, "F%d (0x%X, 0x%X, 0x%X, 0x%X, 0x%X)", f, a1, a2, a3, a4, a5);
	sprintf (the_inv_msg, "F%d (~0x%X, ~0x%X, ~0x%X, ~0x%X, ~0x%X) = F%d (0x%X, 0x%X, 0x%X, 0x%X, 0x%X)",
		 f, a1, a2, a3, a4, a5, f, ~a1, ~a2, ~a3, ~a4, ~a5);
	break; }
    case 7:  {the_val = F7  (a1, a2, a3, a4);      
	the_inv_val = F7 (~a1, ~a2, ~a3, ~a4);
	sprintf (the_msg, "F%d (0x%X, 0x%X, 0x%X, 0x%X)",       f, a1, a2, a3, a4);
	sprintf (the_inv_msg, "F%d (~0x%X, ~0x%X, ~0x%X, ~0x%X) = F%d (0x%X, 0x%X, 0x%X, 0x%X)",
		 f, a1, a2, a3, a4, f, ~a1, ~a2, ~a3, ~a4);
	break; }
    case 8:  {the_val = F8  (a1, a2, a3);          
	the_inv_val = F8 (~a1, ~a2, ~a3);
	sprintf (the_msg, "F%d (0x%X, 0x%X, 0x%X)",             f, a1, a2, a3);
	sprintf (the_inv_msg, "F%d (~0x%X, ~0x%X, ~0x%X) = F%d (0x%X, 0x%X, 0x%X)", f, a1, a2, a3, f, ~a1, ~a2, ~a3);
	break; }
    case 9:  {the_val = F9  (a1, a2, a3);          
	the_inv_val = F9 (~a1, ~a2, ~a3);
	sprintf (the_msg, "F%d (0x%X, 0x%X, 0x%X)",             f, a1, a2, a3);
	sprintf (the_inv_msg, "F%d (~0x%X, ~0x%X, ~0x%X) = F%d (0x%X, 0x%X, 0x%X)", f, a1, a2, a3, f, ~a1, ~a2, ~a3);
	break; }
    case 10: {the_val = F10 (a1, a2, a3, a4);      
	the_inv_val = F10 (~a1, ~a2, ~a3, ~a4);
	sprintf (the_msg, "F%d (0x%X, 0x%X, 0x%X, 0x%X)",       f, a1, a2, a3, a4);
	sprintf (the_inv_msg, "F%d (~0x%X, ~0x%X, ~0x%X, ~0x%X) = F%d (0x%X, 0x%X, 0x%X, 0x%X)",
		 f, a1, a2, a3, a4, f, ~a1, ~a2, ~a3, ~a4);
	break; }
    case 11: {the_val = F9d (a1, a2, a3);          
	the_inv_val = F9d (~a1, ~a2, ~a3);
	sprintf (the_msg, "F%d (0x%X, 0x%X, 0x%X)",             f, a1, a2, a3);
	sprintf (the_inv_msg, "F%d (~0x%X, ~0x%X, ~0x%X) = F%d (0x%X, 0x%X, 0x%X)", f, a1, a2, a3, f, ~a1, ~a2, ~a3);
	break; }
    }

    printf ("MATCH bit pattern for %s:\n", the_msg);
    printf ("   31   27   23   19   15   11    7    3  0\n");
    print_in_bits ("    ", the_val);
    printf ("\n");
    printf ("LOSE  bit pattern for %s:\n", the_inv_msg);
    print_in_bits ("    ", the_inv_val);
    /* printf ("%-40s   %10s 31   27   23   19   15   11    7    3  0\n", " ", " "); */
    /* print_in_bits ("x", x); */
    /* print_in_bits ("y", y); */
    /* print_in_bits ("i", i); */
    /* print_in_bits ("b", b); */
    /* print_in_bits ("a", a); */
    /* printf ("\n"); */
    /* print_in_bits ("~x", ~x); */
    /* print_in_bits ("~y", ~y); */
    /* print_in_bits ("~i", ~i); */
    /* print_in_bits ("~b", ~b); */
    /* print_in_bits ("~a", ~a); */
    /* printf ("\n"); */
    /* printf ("%-40s   %10s 31   27   23   19   15   11    7    3  0\n", " ", " "); */
    /* print_in_bits ("OP(x)", OP(x)); */
    /* print_in_bits ("OP3(y)", OP3(y)); */
    /* print_in_bits ("F3I(i)", F3I(i)); */
    /* print_in_bits ("F3(x, y, i)", F3(x, y, i)); */
    /* printf ("\n"); */
    /* print_in_bits ("OP(~x)", OP(~x)); */
    /* print_in_bits ("OP3(~y)", OP3(~y)); */
    /* print_in_bits ("F3I(~i)", F3I(~i)); */
    /* print_in_bits ("F3(~x, ~y, ~i)", F3(~x, ~y, ~i)); */
    /* printf ("\n"); */
    /* printf ("%-40s   %10s 31   27   23   19   15   11    7    3  0\n", " ", " "); */
    /* print_in_bits ("OP_AJIT_BIT_5(b)", OP_AJIT_BIT_5(b)); */
    /* print_in_bits ("F4(x, y, i, b)", F4(x, y, i, b)); */
    /* print_in_bits ("OP_AJIT_BIT_5(~b)", OP_AJIT_BIT_5(~b)); */
    /* print_in_bits ("F4(~x, ~y, ~i, ~b)", F4(~x, ~y, ~i, ~b)); */
    /* printf ("\n"); */
    /* print_in_bits ("OP_AJIT_BIT_5_AND_6 (b)", OP_AJIT_BIT_5_AND_6(b)); */
    /* print_in_bits ("F5(x, y, i, b)", F5(x, y, i, b)); */
    /* print_in_bits ("F5(~x, ~y, ~i, ~b)", F5(~x, ~y, ~i, ~b)); */
    /* print_in_bits ("(1<<12)", (1<<12)); */
    /* print_in_bits ("(0x7f<<5)", (0x7f<<5)); */
    /* print_in_bits ("OP_AJIT_BIT_5_AND_6 (~b)", OP_AJIT_BIT_5_AND_6(~b)); */
    /* print_in_bits ("F5(~x, ~y, ~i, ~b)|(1<<12)|(0x7f<<5)", F5(~x, ~y, ~i, ~b)|(1<<12)|(0x7f<<5)); */
    /* printf ("\n"); */
    /* printf ("%-40s   %10s 31   27   23   19   15   11    7    3  0\n", " ", " "); */
    /* print_in_bits ("OP_AJIT_BIT_7_THRU_9 (a)", OP_AJIT_BIT_7_THRU_9(a)); */
    /* print_in_bits ("F6(x, y, i, b, a)", F6(x, y, i, b, a)); */
    /* print_in_bits ("OP_AJIT_BIT_7_THRU_9 (~a)", OP_AJIT_BIT_7_THRU_9(~a)); */
    /* print_in_bits ("F6(~x, ~y, ~i, ~b, ~a)", F6(~x, ~y, ~i, ~b, ~a)); */
    /* printf ("\n"); */
    /* print_in_bits ("Final OpCode template", F6(x, y, i, b, a)); */
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

  /* printf ("%-40s = 0x%08X (", name, val); */
  printf ("%s", name);
  for (j = sizeof (int) - 1; j >= 0; j--) {
    convert_unsigned_char_to_bits (x.y[j]);
    printf ("%s%s", bitrep, (j == 0) ? "" : " ");
  }
  printf (" = 0x%08X", val);
  printf ("\n");
  
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
