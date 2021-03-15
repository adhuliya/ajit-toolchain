/* 
 * Program to generate the  opcode _templates_ from the various macros
 * in the SPARC implementation of assembler etc. in the GNU Binutils.
 *
 * Version 1:
 * Generate with mostly hard coding, and minimal parameterisation.
 *
 * (C) Abhijat Vichare. 2018.
 */

/* 
 *  SPARC V8 32 bit instruction structures:
 *  =======================================
 *
 *  Format 1   instructions: CALL (pdf page 67, document page 44, SPARC V8 manual)
 *  --------
 *
 *  31            24  23            16  15             8   7             0 <-- Bit offsets
 *                 3                 2                 1                 0 <-- Byte offsets
 *   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0 <-- Per byte bit offsets
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  |<->|<--                 Displacement [0:29] (30 bits long)       --->|
 *    |
 *    +----- OP field is a 2 bit field that can potentially identify 3
 *           groups of instructions.  The SPARC v8 implements 4 out of
 *           these possible 4 groups  using _three_ formats.  For this
 *           current group, OP = 0x1.
 *
 *  Format 2   instructions: SETHI & Branches (pdf page 67, document page 44, SPARC V8 manual)
 *  --------
 *
 *  Immediate 
 *  31            24  23            16  15             8   7             0 <-- Bit offsets
 *                 3                 2                 1                 0 <-- Byte offsets
 *   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0 <-- Per byte bit offsets
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  |<->|<- rd  ->|<- op->|<---  Immediate value[0:21] (22 bits long) --->|
 *    |      |        |     |
 *    |      |        |     +-- 22 bit long immediate values
 *    |      |        +--------  3 bit long field, [22:24]. 4 out of 7
 *    |      |                   possibilities implemented by SPARC V8
 *    |      +----------------- 5 bit field typically destination register
 *    +------------------------ OP = 0x0, for format 2.
 *
 *  Displacement
 *  31            24  23            16  15             8   7             0 <-- Bit offsets
 *                 3                 2                 1                 0 <-- Byte offsets
 *   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0 <-- Per byte bit offsets
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  |<->| |<cond->|<- op->|<---  Immediate value[0:21] (22 bits long) --->|
 *    |  |   |        |     |
 *    |  |   |        |     +-- 22 bit long immediate values
 *    |  |   |        +--------  3 bit long field, [22:24]. 4 out of 7
 *    |  |   |                   possibilities implemented by SPARC V8
 *    |  |   +----------------- 4 bit field, [25:28]; condition codes for branch insn
 *    |  +--------------------- 1 bit "a" field, [29]; annul flag.
 *    +------------------------ OP = 0x0, for format 2.
 *
 *  Format 3   instructions: All others (pdf page 67, document page 44, SPARC V8 manual)
 *  --------
 *
 *  ASI variant
 *  31            24  23            16  15             8   7             0 <-- Bit offsets
 *                 3                 2                 1                 0 <-- Byte offsets
 *   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0 <-- Per byte bit offsets
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  |   | [29:25] |  [24:19]    |   [18:14] | |    [12:5]       | [4:0]   |
 *    |      |          |              |     |        |             |
 *    |      |          |              |     |        |             +--- 5 bit long Source register 2 (RS2)
 *    |      |          |              |     |        +----------------- 8 bit long ASI
 *    |      |          |              |     +-------------------------- 1 bit immediate/non-immediate selector = 0
 *    |      |          |              +-------------------------------- 5 bit long Source register 1 (RS1)
 *    |      |          +----------------------------------------------- 6 bit insn opcode
 *    |      +---------------------------------------------------------- 5 bit long Destination reg (RD) 
 *    +----------------------------------------------------------------- 2 bit OP field (OP = 2 or 3)
 *
 *  SIMM variant
 *  31            24  23            16  15             8   7             0 <-- Bit offsets
 *                 3                 2                 1                 0 <-- Byte offsets
 *   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0 <-- Per byte bit offsets
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  |   | [29:25] |  [24:19]    |   [18:14] | |    [12:0]                 |
 *    |      |          |              |     |        |                    
 *    |      |          |              |     |        +----------------- 13 bit long SIMM immediate
 *    |      |          |              |     +-------------------------- 1 bit immediate/non-immediate selector = 1
 *    |      |          |              +-------------------------------- 5 bit long Source register 1 (RS1)
 *    |      |          +----------------------------------------------- 6 bit insn opcode
 *    |      +---------------------------------------------------------- 5 bit long Destination reg (RD) 
 *    +----------------------------------------------------------------- 2 bit OP field (OP = 2 or 3)
 *
 *  Floating point variant
 *  31            24  23            16  15             8   7             0 <-- Bit offsets
 *                 3                 2                 1                 0 <-- Byte offsets
 *   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0 <-- Per byte bit offsets
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *  +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 *  |   | [29:25] |  [24:19]    |   [18:14] |      [13:5]       | [4:0]   |
 *    |      |          |              |              |             |
 *    |      |          |              |              |             +--- 5 bit long Source register 2 (RS2)
 *    |      |          |              |              +----------------- 9 bit long OPf (either FPop, or CoProcOp)
 *    |      |          |              +-------------------------------- 5 bit long Source register 1 (RS1)
 *    |      |          +----------------------------------------------- 6 bit insn opcode
 *    |      +---------------------------------------------------------- 5 bit long Destination reg (RD) 
 *    +----------------------------------------------------------------- 2 bit OP field (OP = 2 or 3)
 *
 */

#include <stdio.h>
#include <unistd.h>		/* for getopt() */

#define E_OK                            0
#define E_WRONG_COMMANDLINE            -1

#define MAX_BITFIELD_NAME               10

typedef enum {
  fundef = 0,
  f0,
  f1,
  f2,
  maxformats,
} INSN_FORMAT;

typedef struct {
  char name[MAX_BITFIELD_NAME+1]; /* Set using info from data sheets */
  unsigned char  start;		  /* Set using info from data sheets */
  unsigned char  end;		  /* Set using info from data sheets */
  unsigned short length;	  /* = (end - start + 1); */
  unsigned int   mask;		  /* To be computed from the start and end values. */
} BITFIELD;

typedef struct {
  unsigned short num_bit_fields;
  INSN_FORMAT format;
  BITFIELD *list;		/* implemented as an calloc'd array. */
} INSN_LAYOUT;

INSN_LAYOUT *insn_layout;	/* We should be reading this off some CSV file. */

char bitrep[10];

int       convert_unsigned_char_to_bits      (unsigned char);
int       print_in_bits                      (char name[], int val);

void      help                               (char *);

int
main (int argc, char *argv[])
{
  int   ec      = E_OK;
  char *options = "x:y:i:b:h";
  int   optval  = 0;

  
  if (argc == 1) {
    printf ("Input CSV file for : ");
    scanf ("%x", &x);
    printf ("Value in hexadecimal of OP3 field: ");
    scanf ("%x", &y);
    printf ("Value in hexadecimal of IMM field: ");
    scanf ("%x", &i);
    printf ("Value in hexadecimal of I field: ");
    scanf ("%x", &b);
  } else if (argc == 9) {
    optval = getopt (argc, argv, options);
    while (optval != -1) {
      switch (optval) {
      case 'x': {sscanf (optarg, "%x", &x); break;}
      case 'y': {sscanf (optarg, "%x", &y); break;}
      case 'i': {sscanf (optarg, "%x", &i); break;}
      case 'b': {sscanf (optarg, "%x", &b); break;}
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
    ec = -1;
  }
  
  return ec;
}

void
help                               (char *pn)
{
  printf ("Usage: %s [options]\n", pn);
  printf ("Options are:\n");
  printf ("   -x <val> : Value in hexadecimal of OP field.\n");
  printf ("   -y <val> : Value in hexadecimal of OP3 field.\n");
  printf ("   -i <val> : Value in hexadecimal of IMM field.\n");
  printf ("   -b <val> : Value in hexadecimal of I field.\n");
  printf ("\n");
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
