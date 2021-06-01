/*
 * Simple C tool that accepts a description of the opcode structure of
 * a mnemonic.  It emits out C  code that will patch the GNU binutils.
 * The patch adds support for the AJIT processor.
 */

/*
 * We design this as a filter program. 
 */

#include <stdio.h>
#include <string.h>
#include "insn-desc.h"

int num_insns = 0;

AJIT_INSN insns [MAX_INSNS];

int
main (int argc, char *argv[])
{
  /* char               mnemonic [MAX_MNEMONIC_LENGTH]; /\* The mnemonic string *\/ */
  /* AJIT_INSN_SUBTYPE  subtype;			     /\* Arithmetic, Logic, ... etc. *\/ */
  /* int                num_bits;			     /\* 32 or 64 *\/ */
  /* ALIGNMENT          align;			     /\* Always BIG for SPARC & AJIT *\/ */
  /* AJIT_ORDERING      order;			     /\* Little or big endian *\/ */
  /* AJIT_INSN_LAYOUT   layout[];			     /\* An array of layout details *\/ */
  /*    AJIT_BIT_REGION_SPEC region; */
  /*       char               region_name [MAX_REGION_NAME]; */
  /*       int                start;	/\* Always non-negative. *\/ */
  /*       int                end;	/\* Always non-negative, and never less than "start". *\/ */
  /*       int                length;	/\* Computed from above two. Always non-negative. *\/ */
  /*    AJIT_REGION_MEANING  meaning; */

  strcpy (insns[0].mnemonic, "ADDD");
  insns[0].subtype = AJIT_ADD_SUB;
  insns[0].num_bits = 32;
  insns[0].align = ALIGN_WORD;
  insns[0].order = AJIT_BIG;
  strcpy (insns[0].layout[0].region.region_name, "op");
  insns[0].layout[0].region.start = 30;
  insns[0].layout[0].region.end = 31;
  insns[0].layout[0].meaning = AJIT_OP_FORMAT_ONE;
    
  /* insns[1] = { */
  /*   {"ADDD",			/\* mnemonic string *\/ */
  /*    AJIT_ADD_SUB,		/\* instruction category *\/ */
  /*    32,			/\* length *\/ */
  /*    ALIGN_WORD,		/\* alignment *\/ */
  /*    AJIT_BIG,			/\* ordering (endianness) *\/ */
  /*    {				/\* layout *\/ */
  /*      {			/\* region specification *\/ */
  /* 	 "op", */
  /* 	 30, */
  /* 	 31, */
  /* 	 2 */
  /*      }, */
  /*      AJIT_OP_FORMAT_ONE	/\* meaning *\/ */
  /*    } */
  /*   } */
  /* }; */

  printf ("Maximum instructions we can work with: %d\n", MAX_INSNS);
  printf ("Number of instructions: %d\n", num_insns);
  
  return 0;
}

           /* { */
       /*   { */
       /* 	 "rd", */
       /* 	 29, */
       /* 	 25, */
       /* 	 5 */
       /*   }, */
       /*   AJIT_SPARC_DESTINATION_REGISTER */
       /* }, */
