/* 
 * Print a string of hex numbers  in binary. The hex numbers are space
 * separated byte values.
 */
#include <stdio.h>
#include <stdlib.h>

#define PRINT_BYTE       0
#define PRINT_HALF_WORD  1
#define PRINT_WORD       2
#define PRINT_LONG       3

typedef struct binbyte {
unsigned char bit0:1;
unsigned char bit1:1;
unsigned char bit2:1;
unsigned char bit3:1;
unsigned char bit4:1;
unsigned char bit5:1;
unsigned char bit6:1;
unsigned char bit7:1;
} BINARYBYTE;

typedef union binrep {
  unsigned char in;
  BINARYBYTE out;
} BINREP;

typedef enum bool {
  FALSE = (1 == 0),
  TRUE = !FALSE
} BOOLEAN;

typedef unsigned long long        uint64_t;

void         print_bin       (unsigned char in);
/* void         print_in_bin    (uint64_t in, int the_type); */
void         print_in_bin    (int in);

char *       hdtobinnib      (unsigned char in);

void
print_bin  (unsigned char in)
{
  BINREP x;

  x.in = in;

  printf ("%c", (x.out.bit7 == 0) ? '0' : '1');
  printf ("%c", (x.out.bit6 == 0) ? '0' : '1');
  printf ("%c", (x.out.bit5 == 0) ? '0' : '1');
  printf ("%c", (x.out.bit4 == 0) ? '0' : '1');
  printf (" ");
  printf ("%c", (x.out.bit3 == 0) ? '0' : '1');
  printf ("%c", (x.out.bit2 == 0) ? '0' : '1');
  printf ("%c", (x.out.bit1 == 0) ? '0' : '1');
  printf ("%c", (x.out.bit0 == 0) ? '0' : '1');
}

int     htoi   (char *hin);
int     hdtoi  (char hd);

int
hdtoi  (char hd)
{
  return (hd == '1') ? 1 :
    (hd == '2') ? 2  : 
    (hd == '3') ? 3  : 
    (hd == '4') ? 4  : 
    (hd == '5') ? 5  : 
    (hd == '6') ? 6  : 
    (hd == '7') ? 7  : 
    (hd == '8') ? 8  : 
    (hd == '9') ? 9  : 
    (hd == '0') ? 0  : 
    ((hd == 'A') || (hd == 'a')) ? 10 : 
    ((hd == 'B') || (hd == 'b')) ? 11 : 
    ((hd == 'C') || (hd == 'c')) ? 12 : 
    ((hd == 'D') || (hd == 'd')) ? 13 : 
    ((hd == 'E') || (hd == 'e')) ? 14 : 
    ((hd == 'F') || (hd == 'f')) ? 15 : -1 
    ;
}

char *
hdtobinnib      (unsigned char in)
{
  return 
    (in == '0')                  ? "0000" : 
    (in == '1')                  ? "0001" :
    (in == '2')                  ? "0010" : 
    (in == '3')                  ? "0011" : 
    (in == '4')                  ? "0100" : 
    (in == '5')                  ? "0101" : 
    (in == '6')                  ? "0110" : 
    (in == '7')                  ? "0111" : 
    (in == '8')                  ? "1000" : 
    (in == '9')                  ? "1001" : 
    ((in == 'A') || (in == 'a')) ? "1010" : 
    ((in == 'B') || (in == 'b')) ? "1011" : 
    ((in == 'C') || (in == 'c')) ? "1100" : 
    ((in == 'D') || (in == 'd')) ? "1101" : 
    ((in == 'E') || (in == 'e')) ? "1110" : 
    ((in == 'F') || (in == 'f')) ? "1111" : ""
    ;
}


int
htoi   (char *hin)
{
  int ret = 0;
  int lshd = 0;
  int mshd = 0;

  /* printf ("=== LSHD = %c, MSHD = %c\n", hin[1], hin[0]); */
  lshd = hdtoi (hin[1]);
  mshd = hdtoi (hin[0]);

  if ((lshd != -1) && (mshd != -1))
    ret = (mshd * 16) + lshd;

  return ret;
}

char *hex_inp;

int
main (int argc, char *argv[])
{
  int ec = 0;
  int i = 1;
  int numnibbles  = (argc - 1) * 2;

  if (argc > 1) {
    /* printf ("#bits: %d\t#nibbles: %d\t#lsb: %d\t#msb: %d\nPrinting header ...\n",  */
    /* 	    numbits, numnibbles, lsb, msb); */
    for (i = 1; i < argc; i++) {
      printf ("%2s ", " ");
    }
    printf ("  ");
    for (i = numnibbles; i > 0; i--) {
      int nibmax = (i*4) - 1;
      int nibmin = nibmax - 3;

      printf ("%02d %02d", nibmax, nibmin);

      printf (" ");
    }

    printf ("\n");

    for (i = 1; i < argc; i++) {
      printf ("%2s ", argv[i]);
    }
    printf ("= ");
    for (i = 1; i < argc; i++) {
      printf (" %s  %s", hdtobinnib (argv[i][0]), hdtobinnib (argv[i][1]));
      /* in = htoi (argv[i]); */
      /* /\* printf ("0x%2X = %3d = ", in, in); *\/ */
      /* print_bin (in); */
      /* /\* printf ("\n"); *\/ */
      printf (" ");
    }

    printf ("\n");
  }

  return ec;
}
