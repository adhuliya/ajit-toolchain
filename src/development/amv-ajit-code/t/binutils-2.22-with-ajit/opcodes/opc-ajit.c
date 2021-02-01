/* Table of opcodes for the AJIT.
   Copyright 1989, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999,
   2000, 2002, 2004, 2005, 2006, 2007, 2008, 2011
   Free Software Foundation, Inc.

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this file; see the file COPYING.  If not, write to the
   Free Software Foundation, 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

/* 
 * Adapted for IITB AJIT processor.  Preserved code for v7, v7 and v8,
 * and removed others like v9 and others.
 *
 * Abhijat Vichare.  February 2020.  : Start.  Adapted - tc-ajit.[ch],
 *                                     ajit-opc.[ch],   ajit.h    from
 *                                     corresponding sparc code.
 * Abhijat Vichare.  April 2020.     : Removed v9 etc. macros. Fail.
 * Abhijat Vichare.  July 2020.      : Study v9 code.
 * Abhijat Vichare.  September 2020. : Define ajit architecture
 * Abhijat Vichare.  October 2020.   : Most instructions  ok, some are
 *                                     off.  Ok for  a  first view  by
 *                                     Anshuman and Gauri.
 */


/* FIXME-someday: perhaps the ,a's and such should be embedded in the
   instruction's name rather than the args.  This would make gas faster, pinsn
   slower, but would mess up some macros a bit.  xoxorich. */

#include <stdio.h>
#include "sysdep.h"
#include "opcode/ajit.h"

/* Some defines to make life easy.  */
#define MASK_AJIT       AJIT_OPCODE_ARCH_MASK (AJIT_OPCODE_ARCH)
#define MASK_V6         AJIT_OPCODE_ARCH_MASK (AJIT_OPCODE_ARCH_V6)
#define MASK_V7         AJIT_OPCODE_ARCH_MASK (AJIT_OPCODE_ARCH_V7)
#define MASK_V8         AJIT_OPCODE_ARCH_MASK (AJIT_OPCODE_ARCH_V8)
#define MASK_V9         AJIT_OPCODE_ARCH_MASK (AJIT_OPCODE_ARCH_V9) /* Keep this to make certain macros work! */

/* Bit masks of architectures supporting the insn.  */

#define ajit             (MASK_AJIT)
#define v6               (MASK_V6 | MASK_V7 | MASK_V8)
/* v6 insns  not supported on  the ajitlet.  AMV: Not  really relevant
   for AJIT, but we keep this to make certain macros work. */
#define v6notlet        (MASK_V6 | MASK_V7 | MASK_V8)
#define v7              (MASK_V7 | MASK_V8)
#define v8              (MASK_V8)
#define v9              (MASK_V9)

/* Table of opcode architectures.
   The order is defined in opcode/ajit.h.  */

const struct ajit_opcode_arch ajit_opcode_archs[] =
{
  { "ajit", MASK_AJIT },	/* Should we be first? Not checked. But works somewhat. */
  { NULL, 0 }
};

/* const struct ajit_opcode_arch ajit_opcode_archs[] = */
/* { */
/*   { "ajit", MASK_AJIT },	/\* Should we be first? Not checked. But works somewhat. *\/ */
/*   { "v6", MASK_V6 }, */
/*   { "v7", MASK_V6 | MASK_V7 }, */
/*   { "v8", MASK_V6 | MASK_V7 | MASK_V8 }, */
/*   { NULL, 0 } */
/* }; */

/* Given NAME, return it's architecture entry.  */

enum ajit_opcode_arch_val
ajit_opcode_lookup_arch (const char *name)
{
  const struct ajit_opcode_arch *p;

  for (p = &ajit_opcode_archs[0]; p->name; ++p) {
    if (strcmp (name, p->name) == 0)
      return (enum ajit_opcode_arch_val) (p - &ajit_opcode_archs[0]);
  }

  return AJIT_OPCODE_ARCH_BAD;
}

/* Branch condition field.  */
#define COND(x)         (((x) & 0xf) << 25)

#define CONDA   (COND (0x8))
#define CONDCC  (COND (0xd))
#define CONDCS  (COND (0x5))
#define CONDE   (COND (0x1))
#define CONDG   (COND (0xa))
#define CONDGE  (COND (0xb))
#define CONDGU  (COND (0xc))
#define CONDL   (COND (0x3))
#define CONDLE  (COND (0x2))
#define CONDLEU (COND (0x4))
#define CONDN   (COND (0x0))
#define CONDNE  (COND (0x9))
#define CONDNEG (COND (0x6))
#define CONDPOS (COND (0xe))
#define CONDVC  (COND (0xf))
#define CONDVS  (COND (0x7))

#define CONDNZ  CONDNE
#define CONDZ   CONDE
#define CONDGEU CONDCC
#define CONDLU  CONDCS

#define FCONDA          (COND (0x8))
#define FCONDE          (COND (0x9))
#define FCONDG          (COND (0x6))
#define FCONDGE         (COND (0xb))
#define FCONDL          (COND (0x4))
#define FCONDLE         (COND (0xd))
#define FCONDLG         (COND (0x2))
#define FCONDN          (COND (0x0))
#define FCONDNE         (COND (0x1))
#define FCONDO          (COND (0xf))
#define FCONDU          (COND (0x7))
#define FCONDUE         (COND (0xa))
#define FCONDUG         (COND (0x5))
#define FCONDUGE        (COND (0xc))
#define FCONDUL         (COND (0x3))
#define FCONDULE        (COND (0xe))

#define FCONDNZ FCONDNE
#define FCONDZ  FCONDE

/* #define ICC             (0)     /\* v9 *\/ */
/* #define XCC             (1 << 12) /\* v9 *\/ */
/* #define FCC(x)          (((x) & 0x3) << 11) /\* v9 *\/ */
/* #define FBFCC(x)        (((x) & 0x3) << 20)     /\* v9 *\/ */

/* The order of the opcodes in the table is significant:

        * The assembler requires that all instances of the same mnemonic must
        be consecutive. If they aren't, the assembler will bomb at runtime.

        * The disassembler should not care about the order of the opcodes.  */

/* Entries for commutative arithmetic operations.  */
/* ??? More entries can make use of this.  */
#define COMMUTEOP(opcode, op3, arch_mask) \
{ opcode,       F3(2, op3, 0), F3(~2, ~op3, ~0)|ASI(~0),        "1,2,d", 0, arch_mask }, \
{ opcode,       F3(2, op3, 1), F3(~2, ~op3, ~1),                "1,i,d", 0, arch_mask }, \
{ opcode,       F3(2, op3, 1), F3(~2, ~op3, ~1),                "i,1,d", 0, arch_mask }

const struct ajit_opcode ajit_opcodes[] = {

{ "ld",	F3(3, 0x00, 0), F3(~3, ~0x00, ~0),		"[1+2],d", 0, ajit },
{ "ld",	F3(3, 0x00, 0), F3(~3, ~0x00, ~0)|RS2_G0,	"[1],d", 0, ajit }, /* ld [rs1+%g0],d */
{ "ld",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1),		"[1+i],d", 0, ajit },
{ "ld",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1),		"[i+1],d", 0, ajit },
{ "ld",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1)|RS1_G0,	"[i],d", 0, ajit },
{ "ld",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1)|SIMM13(~0),	"[1],d", 0, ajit }, /* ld [rs1+0],d */
{ "ld",	F3(3, 0x20, 0), F3(~3, ~0x20, ~0),		"[1+2],g", 0, ajit },
{ "ld",	F3(3, 0x20, 0), F3(~3, ~0x20, ~0)|RS2_G0,	"[1],g", 0, ajit }, /* ld [rs1+%g0],d */
{ "ld",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1),		"[1+i],g", 0, ajit },
{ "ld",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1),		"[i+1],g", 0, ajit },
{ "ld",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1)|RS1_G0,	"[i],g", 0, ajit },
{ "ld",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1)|SIMM13(~0),	"[1],g", 0, ajit }, /* ld [rs1+0],d */

{ "ld",	F3(3, 0x21, 0), F3(~3, ~0x21, ~0)|RD(~0),	"[1+2],F", 0, ajit },
{ "ld",	F3(3, 0x21, 0), F3(~3, ~0x21, ~0)|RS2_G0|RD(~0),"[1],F", 0, ajit }, /* ld [rs1+%g0],d */
{ "ld",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1)|RD(~0),	"[1+i],F", 0, ajit },
{ "ld",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1)|RD(~0),	"[i+1],F", 0, ajit },
{ "ld",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1)|RS1_G0|RD(~0),"[i],F", 0, ajit },
{ "ld",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1)|SIMM13(~0)|RD(~0),"[1],F", 0, ajit }, /* ld [rs1+0],d */

{ "ld",	F3(3, 0x30, 0), F3(~3, ~0x30, ~0),		"[1+2],D", 0, ajit },
{ "ld",	F3(3, 0x30, 0), F3(~3, ~0x30, ~0)|RS2_G0,	"[1],D", 0, ajit }, /* ld [rs1+%g0],d */
{ "ld",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1),		"[1+i],D", 0, ajit },
{ "ld",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1),		"[i+1],D", 0, ajit },
{ "ld",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1)|RS1_G0,	"[i],D", 0, ajit },
{ "ld",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1)|SIMM13(~0),	"[1],D", 0, ajit }, /* ld [rs1+0],d */
{ "ld",	F3(3, 0x31, 0), F3(~3, ~0x31, ~0),		"[1+2],C", 0, ajit },
{ "ld",	F3(3, 0x31, 0), F3(~3, ~0x31, ~0)|RS2_G0,	"[1],C", 0, ajit }, /* ld [rs1+%g0],d */
{ "ld",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1),		"[1+i],C", 0, ajit },
{ "ld",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1),		"[i+1],C", 0, ajit },
{ "ld",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1)|RS1_G0,	"[i],C", 0, ajit },
{ "ld",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1)|SIMM13(~0),	"[1],C", 0, ajit }, /* ld [rs1+0],d */

{ "ldd",	F3(3, 0x03, 0), F3(~3, ~0x03, ~0)|ASI(~0),	"[1+2],d", 0, ajit },
{ "ldd",	F3(3, 0x03, 0), F3(~3, ~0x03, ~0)|ASI_RS2(~0),	"[1],d", 0, ajit }, /* ldd [rs1+%g0],d */
{ "ldd",	F3(3, 0x03, 1), F3(~3, ~0x03, ~1),		"[1+i],d", 0, ajit },
{ "ldd",	F3(3, 0x03, 1), F3(~3, ~0x03, ~1),		"[i+1],d", 0, ajit },
{ "ldd",	F3(3, 0x03, 1), F3(~3, ~0x03, ~1)|RS1_G0,	"[i],d", 0, ajit },
{ "ldd",	F3(3, 0x03, 1), F3(~3, ~0x03, ~1)|SIMM13(~0),	"[1],d", 0, ajit }, /* ldd [rs1+0],d */
{ "ldd",	F3(3, 0x23, 0), F3(~3, ~0x23, ~0)|ASI(~0),	"[1+2],H", 0, ajit },
{ "ldd",	F3(3, 0x23, 0), F3(~3, ~0x23, ~0)|ASI_RS2(~0),	"[1],H", 0, ajit }, /* ldd [rs1+%g0],d */
{ "ldd",	F3(3, 0x23, 1), F3(~3, ~0x23, ~1),		"[1+i],H", 0, ajit },
{ "ldd",	F3(3, 0x23, 1), F3(~3, ~0x23, ~1),		"[i+1],H", 0, ajit },
{ "ldd",	F3(3, 0x23, 1), F3(~3, ~0x23, ~1)|RS1_G0,	"[i],H", 0, ajit },
{ "ldd",	F3(3, 0x23, 1), F3(~3, ~0x23, ~1)|SIMM13(~0),	"[1],H", 0, ajit }, /* ldd [rs1+0],d */

{ "ldd",	F3(3, 0x33, 0), F3(~3, ~0x33, ~0)|ASI(~0),	"[1+2],D", 0, ajit },
{ "ldd",	F3(3, 0x33, 0), F3(~3, ~0x33, ~0)|ASI_RS2(~0),	"[1],D", 0, ajit }, /* ldd [rs1+%g0],d */
{ "ldd",	F3(3, 0x33, 1), F3(~3, ~0x33, ~1),		"[1+i],D", 0, ajit },
{ "ldd",	F3(3, 0x33, 1), F3(~3, ~0x33, ~1),		"[i+1],D", 0, ajit },
{ "ldd",	F3(3, 0x33, 1), F3(~3, ~0x33, ~1)|RS1_G0,	"[i],D", 0, ajit },
{ "ldd",	F3(3, 0x33, 1), F3(~3, ~0x33, ~1)|SIMM13(~0),	"[1],D", 0, ajit }, /* ldd [rs1+0],d */

{ "ldsb",	F3(3, 0x09, 0), F3(~3, ~0x09, ~0)|ASI(~0),	"[1+2],d", 0, ajit },
{ "ldsb",	F3(3, 0x09, 0), F3(~3, ~0x09, ~0)|ASI_RS2(~0),	"[1],d", 0, ajit }, /* ldsb [rs1+%g0],d */
{ "ldsb",	F3(3, 0x09, 1), F3(~3, ~0x09, ~1),		"[1+i],d", 0, ajit },
{ "ldsb",	F3(3, 0x09, 1), F3(~3, ~0x09, ~1),		"[i+1],d", 0, ajit },
{ "ldsb",	F3(3, 0x09, 1), F3(~3, ~0x09, ~1)|RS1_G0,	"[i],d", 0, ajit },
{ "ldsb",	F3(3, 0x09, 1), F3(~3, ~0x09, ~1)|SIMM13(~0),	"[1],d", 0, ajit }, /* ldsb [rs1+0],d */

{ "ldsh",	F3(3, 0x0a, 0), F3(~3, ~0x0a, ~0)|ASI_RS2(~0),	"[1],d", 0, ajit }, /* ldsh [rs1+%g0],d */
{ "ldsh",	F3(3, 0x0a, 0), F3(~3, ~0x0a, ~0)|ASI(~0),	"[1+2],d", 0, ajit },
{ "ldsh",	F3(3, 0x0a, 1), F3(~3, ~0x0a, ~1),		"[1+i],d", 0, ajit },
{ "ldsh",	F3(3, 0x0a, 1), F3(~3, ~0x0a, ~1),		"[i+1],d", 0, ajit },
{ "ldsh",	F3(3, 0x0a, 1), F3(~3, ~0x0a, ~1)|RS1_G0,	"[i],d", 0, ajit },
{ "ldsh",	F3(3, 0x0a, 1), F3(~3, ~0x0a, ~1)|SIMM13(~0),	"[1],d", 0, ajit }, /* ldsh [rs1+0],d */

{ "ldub",	F3(3, 0x01, 0), F3(~3, ~0x01, ~0)|ASI(~0),	"[1+2],d", 0, ajit },
{ "ldub",	F3(3, 0x01, 0), F3(~3, ~0x01, ~0)|ASI_RS2(~0),	"[1],d", 0, ajit }, /* ldub [rs1+%g0],d */
{ "ldub",	F3(3, 0x01, 1), F3(~3, ~0x01, ~1),		"[1+i],d", 0, ajit },
{ "ldub",	F3(3, 0x01, 1), F3(~3, ~0x01, ~1),		"[i+1],d", 0, ajit },
{ "ldub",	F3(3, 0x01, 1), F3(~3, ~0x01, ~1)|RS1_G0,	"[i],d", 0, ajit },
{ "ldub",	F3(3, 0x01, 1), F3(~3, ~0x01, ~1)|SIMM13(~0),	"[1],d", 0, ajit }, /* ldub [rs1+0],d */

{ "lduh",	F3(3, 0x02, 0), F3(~3, ~0x02, ~0)|ASI(~0),	"[1+2],d", 0, ajit },
{ "lduh",	F3(3, 0x02, 0), F3(~3, ~0x02, ~0)|ASI_RS2(~0),	"[1],d", 0, ajit }, /* lduh [rs1+%g0],d */
{ "lduh",	F3(3, 0x02, 1), F3(~3, ~0x02, ~1),		"[1+i],d", 0, ajit },
{ "lduh",	F3(3, 0x02, 1), F3(~3, ~0x02, ~1),		"[i+1],d", 0, ajit },
{ "lduh",	F3(3, 0x02, 1), F3(~3, ~0x02, ~1)|RS1_G0,	"[i],d", 0, ajit },
{ "lduh",	F3(3, 0x02, 1), F3(~3, ~0x02, ~1)|SIMM13(~0),	"[1],d", 0, ajit }, /* lduh [rs1+0],d */

{ "lda",	F3(3, 0x10, 0), F3(~3, ~0x10, ~0),		"[1+2]A,d", 0, ajit },
{ "lda",	F3(3, 0x10, 0), F3(~3, ~0x10, ~0)|RS2_G0,	"[1]A,d", 0, ajit }, /* lda [rs1+%g0],d */

{ "ldda",	F3(3, 0x13, 0), F3(~3, ~0x13, ~0),		"[1+2]A,d", 0, ajit },
{ "ldda",	F3(3, 0x13, 0), F3(~3, ~0x13, ~0)|RS2_G0,	"[1]A,d", 0, ajit }, /* ldda [rs1+%g0],d */

{ "ldsba",	F3(3, 0x19, 0), F3(~3, ~0x19, ~0),		"[1+2]A,d", 0, ajit },
{ "ldsba",	F3(3, 0x19, 0), F3(~3, ~0x19, ~0)|RS2_G0,	"[1]A,d", 0, ajit }, /* ldsba [rs1+%g0],d */

{ "ldsha",	F3(3, 0x1a, 0), F3(~3, ~0x1a, ~0),		"[1+2]A,d", 0, ajit },
{ "ldsha",	F3(3, 0x1a, 0), F3(~3, ~0x1a, ~0)|RS2_G0,	"[1]A,d", 0, ajit }, /* ldsha [rs1+%g0],d */

{ "lduba",	F3(3, 0x11, 0), F3(~3, ~0x11, ~0),		"[1+2]A,d", 0, ajit },
{ "lduba",	F3(3, 0x11, 0), F3(~3, ~0x11, ~0)|RS2_G0,	"[1]A,d", 0, ajit }, /* lduba [rs1+%g0],d */

{ "lduha",	F3(3, 0x12, 0), F3(~3, ~0x12, ~0),		"[1+2]A,d", 0, ajit },
{ "lduha",	F3(3, 0x12, 0), F3(~3, ~0x12, ~0)|RS2_G0,	"[1]A,d", 0, ajit }, /* lduha [rs1+%g0],d */

{ "st",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|ASI(~0),		"d,[1+2]", 0, ajit },
{ "st",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|ASI_RS2(~0),		"d,[1]", 0, ajit }, /* st d,[rs1+%g0] */
{ "st",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1),			"d,[1+i]", 0, ajit },
{ "st",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1),			"d,[i+1]", 0, ajit },
{ "st",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|RS1_G0,		"d,[i]", 0, ajit },
{ "st",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|SIMM13(~0),		"d,[1]", 0, ajit }, /* st d,[rs1+0] */
{ "st",	F3(3, 0x24, 0), F3(~3, ~0x24, ~0)|ASI(~0),		"g,[1+2]", 0, ajit },
{ "st",	F3(3, 0x24, 0), F3(~3, ~0x24, ~0)|ASI_RS2(~0),		"g,[1]", 0, ajit }, /* st d[rs1+%g0] */
{ "st",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1),			"g,[1+i]", 0, ajit },
{ "st",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1),			"g,[i+1]", 0, ajit },
{ "st",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1)|RS1_G0,		"g,[i]", 0, ajit },
{ "st",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1)|SIMM13(~0),		"g,[1]", 0, ajit }, /* st d,[rs1+0] */

{ "st",	F3(3, 0x34, 0), F3(~3, ~0x34, ~0)|ASI(~0),		"D,[1+2]", 0, ajit },
{ "st",	F3(3, 0x34, 0), F3(~3, ~0x34, ~0)|ASI_RS2(~0),		"D,[1]", 0, ajit }, /* st d,[rs1+%g0] */
{ "st",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1),			"D,[1+i]", 0, ajit },
{ "st",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1),			"D,[i+1]", 0, ajit },
{ "st",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1)|RS1_G0,		"D,[i]", 0, ajit },
{ "st",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1)|SIMM13(~0),		"D,[1]", 0, ajit }, /* st d,[rs1+0] */
{ "st",	F3(3, 0x35, 0), F3(~3, ~0x35, ~0)|ASI(~0),		"C,[1+2]", 0, ajit },
{ "st",	F3(3, 0x35, 0), F3(~3, ~0x35, ~0)|ASI_RS2(~0),		"C,[1]", 0, ajit }, /* st d,[rs1+%g0] */
{ "st",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1),			"C,[1+i]", 0, ajit },
{ "st",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1),			"C,[i+1]", 0, ajit },
{ "st",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1)|RS1_G0,		"C,[i]", 0, ajit },
{ "st",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1)|SIMM13(~0),		"C,[1]", 0, ajit }, /* st d,[rs1+0] */

{ "st",	F3(3, 0x25, 0), F3(~3, ~0x25, ~0)|RD_G0|ASI(~0),	"F,[1+2]", 0, ajit },
{ "st",	F3(3, 0x25, 0), F3(~3, ~0x25, ~0)|RD_G0|ASI_RS2(~0),	"F,[1]", 0, ajit }, /* st d,[rs1+%g0] */
{ "st",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0,		"F,[1+i]", 0, ajit },
{ "st",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0,		"F,[i+1]", 0, ajit },
{ "st",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0|RS1_G0,		"F,[i]", 0, ajit },
{ "st",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0|SIMM13(~0),	"F,[1]", 0, ajit }, /* st d,[rs1+0] */

{ "sta",	F3(3, 0x14, 0), F3(~3, ~0x14, ~0),		"d,[1+2]A", 0, ajit },
{ "sta",	F3(3, 0x14, 0), F3(~3, ~0x14, ~0)|RS2(~0),	"d,[1]A", 0, ajit }, /* sta d,[rs1+%g0] */

{ "stba",	F3(3, 0x15, 0), F3(~3, ~0x15, ~0),		"d,[1+2]A", 0, ajit },
{ "stba",	F3(3, 0x15, 0), F3(~3, ~0x15, ~0)|RS2(~0),	"d,[1]A", 0, ajit }, /* stba d,[rs1+%g0] */

{ "std",	F3(3, 0x07, 0), F3(~3, ~0x07, ~0)|ASI(~0),	"d,[1+2]", 0, ajit },
{ "std",	F3(3, 0x07, 0), F3(~3, ~0x07, ~0)|ASI_RS2(~0),	"d,[1]", 0, ajit }, /* std d,[rs1+%g0] */
{ "std",	F3(3, 0x07, 1), F3(~3, ~0x07, ~1),		"d,[1+i]", 0, ajit },
{ "std",	F3(3, 0x07, 1), F3(~3, ~0x07, ~1),		"d,[i+1]", 0, ajit },
{ "std",	F3(3, 0x07, 1), F3(~3, ~0x07, ~1)|RS1_G0,	"d,[i]", 0, ajit },
{ "std",	F3(3, 0x07, 1), F3(~3, ~0x07, ~1)|SIMM13(~0),	"d,[1]", 0, ajit }, /* std d,[rs1+0] */

{ "std",	F3(3, 0x26, 0), F3(~3, ~0x26, ~0)|ASI(~0),	"q,[1+2]", 0, ajit },
{ "std",	F3(3, 0x26, 0), F3(~3, ~0x26, ~0)|ASI_RS2(~0),	"q,[1]", 0, ajit }, /* std d,[rs1+%g0] */
{ "std",	F3(3, 0x26, 1), F3(~3, ~0x26, ~1),		"q,[1+i]", 0, ajit },
{ "std",	F3(3, 0x26, 1), F3(~3, ~0x26, ~1),		"q,[i+1]", 0, ajit },
{ "std",	F3(3, 0x26, 1), F3(~3, ~0x26, ~1)|RS1_G0,	"q,[i]", 0, ajit },
{ "std",	F3(3, 0x26, 1), F3(~3, ~0x26, ~1)|SIMM13(~0),	"q,[1]", 0, ajit }, /* std d,[rs1+0] */
{ "std",	F3(3, 0x27, 0), F3(~3, ~0x27, ~0)|ASI(~0),	"H,[1+2]", 0, ajit },
{ "std",	F3(3, 0x27, 0), F3(~3, ~0x27, ~0)|ASI_RS2(~0),	"H,[1]", 0, ajit }, /* std d,[rs1+%g0] */
{ "std",	F3(3, 0x27, 1), F3(~3, ~0x27, ~1),		"H,[1+i]", 0, ajit },
{ "std",	F3(3, 0x27, 1), F3(~3, ~0x27, ~1),		"H,[i+1]", 0, ajit },
{ "std",	F3(3, 0x27, 1), F3(~3, ~0x27, ~1)|RS1_G0,	"H,[i]", 0, ajit },
{ "std",	F3(3, 0x27, 1), F3(~3, ~0x27, ~1)|SIMM13(~0),	"H,[1]", 0, ajit }, /* std d,[rs1+0] */

{ "std",	F3(3, 0x36, 0), F3(~3, ~0x36, ~0)|ASI(~0),	"Q,[1+2]", 0, ajit },
{ "std",	F3(3, 0x36, 0), F3(~3, ~0x36, ~0)|ASI_RS2(~0),	"Q,[1]", 0, ajit }, /* std d,[rs1+%g0] */
{ "std",	F3(3, 0x36, 1), F3(~3, ~0x36, ~1),		"Q,[1+i]", 0, ajit },
{ "std",	F3(3, 0x36, 1), F3(~3, ~0x36, ~1),		"Q,[i+1]", 0, ajit },
{ "std",	F3(3, 0x36, 1), F3(~3, ~0x36, ~1)|RS1_G0,	"Q,[i]", 0, ajit },
{ "std",	F3(3, 0x36, 1), F3(~3, ~0x36, ~1)|SIMM13(~0),	"Q,[1]", 0, ajit }, /* std d,[rs1+0] */
{ "std",	F3(3, 0x37, 0), F3(~3, ~0x37, ~0)|ASI(~0),	"D,[1+2]", 0, ajit },
{ "std",	F3(3, 0x37, 0), F3(~3, ~0x37, ~0)|ASI_RS2(~0),	"D,[1]", 0, ajit }, /* std d,[rs1+%g0] */
{ "std",	F3(3, 0x37, 1), F3(~3, ~0x37, ~1),		"D,[1+i]", 0, ajit },
{ "std",	F3(3, 0x37, 1), F3(~3, ~0x37, ~1),		"D,[i+1]", 0, ajit },
{ "std",	F3(3, 0x37, 1), F3(~3, ~0x37, ~1)|RS1_G0,	"D,[i]", 0, ajit },
{ "std",	F3(3, 0x37, 1), F3(~3, ~0x37, ~1)|SIMM13(~0),	"D,[1]", 0, ajit }, /* std d,[rs1+0] */

{ "stda",	F3(3, 0x17, 0), F3(~3, ~0x17, ~0),		"d,[1+2]A", 0, ajit },
{ "stda",	F3(3, 0x17, 0), F3(~3, ~0x17, ~0)|RS2(~0),	"d,[1]A", 0, ajit }, /* stda d,[rs1+%g0] */

{ "sth",	F3(3, 0x06, 0), F3(~3, ~0x06, ~0)|ASI(~0),	"d,[1+2]", 0, ajit },
{ "sth",	F3(3, 0x06, 0), F3(~3, ~0x06, ~0)|ASI_RS2(~0),	"d,[1]", 0, ajit }, /* sth d,[rs1+%g0] */
{ "sth",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1),		"d,[1+i]", 0, ajit },
{ "sth",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1),		"d,[i+1]", 0, ajit },
{ "sth",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1)|RS1_G0,	"d,[i]", 0, ajit },
{ "sth",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1)|SIMM13(~0),	"d,[1]", 0, ajit }, /* sth d,[rs1+0] */

{ "stha",	F3(3, 0x16, 0), F3(~3, ~0x16, ~0),		"d,[1+2]A", 0, ajit },
{ "stha",	F3(3, 0x16, 0), F3(~3, ~0x16, ~0)|RS2(~0),	"d,[1]A", 0, ajit }, /* stha ,[rs1+%g0] */

{ "swap",	F3(3, 0x0f, 0), F3(~3, ~0x0f, ~0)|ASI(~0),	"[1+2],d", 0, ajit },
{ "swap",	F3(3, 0x0f, 0), F3(~3, ~0x0f, ~0)|ASI_RS2(~0),	"[1],d", 0, ajit }, /* swap [rs1+%g0],d */
{ "swap",	F3(3, 0x0f, 1), F3(~3, ~0x0f, ~1),		"[1+i],d", 0, ajit },
{ "swap",	F3(3, 0x0f, 1), F3(~3, ~0x0f, ~1),		"[i+1],d", 0, ajit },
{ "swap",	F3(3, 0x0f, 1), F3(~3, ~0x0f, ~1)|RS1_G0,	"[i],d", 0, ajit },
{ "swap",	F3(3, 0x0f, 1), F3(~3, ~0x0f, ~1)|SIMM13(~0),	"[1],d", 0, ajit }, /* swap [rs1+0],d */

{ "swapa",	F3(3, 0x1f, 0), F3(~3, ~0x1f, ~0),		"[1+2]A,d", 0, ajit },
{ "swapa",	F3(3, 0x1f, 0), F3(~3, ~0x1f, ~0)|RS2(~0),	"[1]A,d", 0, ajit }, /* swapa [rs1+%g0],d */

{ "restore",	F3(2, 0x3d, 0), F3(~2, ~0x3d, ~0)|ASI(~0),			"1,2,d", 0, ajit },
{ "restore",	F3(2, 0x3d, 0), F3(~2, ~0x3d, ~0)|RD_G0|RS1_G0|ASI_RS2(~0),	"", 0, ajit }, /* restore %g0,%g0,%g0 */
{ "restore",	F3(2, 0x3d, 1), F3(~2, ~0x3d, ~1),				"1,i,d", 0, ajit },
{ "restore",	F3(2, 0x3d, 1), F3(~2, ~0x3d, ~1)|RD_G0|RS1_G0|SIMM13(~0),	"", 0, ajit }, /* restore %g0,0,%g0 */

{ "rett",	F3(2, 0x39, 0), F3(~2, ~0x39, ~0)|RD_G0|ASI(~0),	"1+2", F_UNBR|F_DELAYED, ajit }, /* rett rs1+rs2 */
{ "rett",	F3(2, 0x39, 0), F3(~2, ~0x39, ~0)|RD_G0|ASI_RS2(~0),	"1", F_UNBR|F_DELAYED, ajit },	/* rett rs1,%g0 */
{ "rett",	F3(2, 0x39, 1), F3(~2, ~0x39, ~1)|RD_G0,		"1+i", F_UNBR|F_DELAYED, ajit }, /* rett rs1+X */
{ "rett",	F3(2, 0x39, 1), F3(~2, ~0x39, ~1)|RD_G0,		"i+1", F_UNBR|F_DELAYED, ajit }, /* rett X+rs1 */
{ "rett",	F3(2, 0x39, 1), F3(~2, ~0x39, ~1)|RD_G0|RS1_G0,		"i", F_UNBR|F_DELAYED, ajit }, /* rett X+rs1 */
{ "rett",	F3(2, 0x39, 1), F3(~2, ~0x39, ~1)|RD_G0|RS1_G0,		"i", F_UNBR|F_DELAYED, ajit },	/* rett X */
{ "rett",	F3(2, 0x39, 1), F3(~2, ~0x39, ~1)|RD_G0|SIMM13(~0),	"1", F_UNBR|F_DELAYED, ajit },	/* rett rs1+0 */

{ "save",	F3(2, 0x3c, 0), F3(~2, ~0x3c, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "save",	F3(2, 0x3c, 1), F3(~2, ~0x3c, ~1),		"1,i,d", 0, ajit },
{ "save",	F3(2, 0x3c, 1), F3(~2, ~0x3c, ~1),		"i,1,d", 0, ajit }, /* Sun assembler compatibility */
{ "save",	0x81e00000,	~0x81e00000,			"", F_ALIAS, ajit },

{ "jmpl",	F3(2, 0x38, 0), F3(~2, ~0x38, ~0)|ASI(~0),	"1+2,d", F_JSR|F_DELAYED, ajit },
{ "jmpl",	F3(2, 0x38, 0), F3(~2, ~0x38, ~0)|ASI_RS2(~0),	"1,d", F_JSR|F_DELAYED, ajit }, /* jmpl rs1+%g0,d */
{ "jmpl",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|SIMM13(~0),	"1,d", F_JSR|F_DELAYED, ajit }, /* jmpl rs1+0,d */
{ "jmpl",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|RS1_G0,	"i,d", F_JSR|F_DELAYED, ajit }, /* jmpl %g0+i,d */
{ "jmpl",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1),		"1+i,d", F_JSR|F_DELAYED, ajit },
{ "jmpl",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1),		"i+1,d", F_JSR|F_DELAYED, ajit },

{ "flush",	F3(2, 0x3b, 0), F3(~2, ~0x3b, ~0)|ASI(~0),	"1+2", 0, ajit },
{ "flush",	F3(2, 0x3b, 0), F3(~2, ~0x3b, ~0)|ASI_RS2(~0),	"1", 0, ajit }, /* flush rs1+%g0 */
{ "flush",	F3(2, 0x3b, 1), F3(~2, ~0x3b, ~1)|SIMM13(~0),	"1", 0, ajit }, /* flush rs1+0 */
{ "flush",	F3(2, 0x3b, 1), F3(~2, ~0x3b, ~1)|RS1_G0,	"i", 0, ajit }, /* flush %g0+i */
{ "flush",	F3(2, 0x3b, 1), F3(~2, ~0x3b, ~1),		"1+i", 0, ajit },
{ "flush",	F3(2, 0x3b, 1), F3(~2, ~0x3b, ~1),		"i+1", 0, ajit },

{ "stbar",	F3(2, 0x28, 0)|RS1(0xf), F3(~2, ~0x28, ~0)|RD_G0|RS1(~0xf)|SIMM13(~0), "", 0, ajit },

{ "sll",	F3(2, 0x25, 0),      F3(~2, ~0x25, ~0)|(1<<12)|(0x7f<<5),	"1,2,d", 0, ajit },
{ "sll",	F3(2, 0x25, 1),      F3(~2, ~0x25, ~1)|(1<<12)|(0x7f<<5),	"1,X,d", 0, ajit },
{ "slld",	F5(2, 0x25, 1, 0x2), F5(~2, ~0x25, ~1, ~0x2),	        "1,Y,d", 0, ajit }, /* AJIT */
{ "slld",	F5(2, 0x25, 0, 0x2), F5(~2, ~0x25, ~0, ~0x2),	        "1,2,d", 0, ajit }, /* AJIT */
{ "sra",	F3(2, 0x27, 0),      F3(~2, ~0x27, ~0)|(1<<12)|(0x7f<<5),	"1,2,d", 0, ajit },
{ "sra",	F3(2, 0x27, 1),      F3(~2, ~0x27, ~1)|(1<<12)|(0x7f<<5),	"1,X,d", 0, ajit },
{ "srad",	F5(2, 0x27, 1, 0x2), F5(~2, ~0x27, ~1, ~0x2),	        "1,Y,d", 0, ajit }, /* AJIT */
{ "srad",	F5(2, 0x27, 0, 0x2), F5(~2, ~0x27, ~0, ~0x2),	        "1,2,d", 0, ajit }, /* AJIT */
{ "srl",	F3(2, 0x26, 0),      F3(~2, ~0x26, ~0)|(1<<12)|(0x7f<<5),	"1,2,d", 0, ajit },
{ "srl",	F3(2, 0x26, 1),      F3(~2, ~0x26, ~1)|(1<<12)|(0x7f<<5),	"1,X,d", 0, ajit },
{ "srld",	F5(2, 0x26, 1, 0x2), F5(~2, ~0x26, ~1, ~0x2),	        "1,Y,d", 0, ajit }, /* AJIT */
{ "srld",	F5(2, 0x26, 0, 0x2), F5(~2, ~0x26, ~0, ~0x2),	        "1,2,d", 0, ajit }, /* AJIT */

{ "mulscc",	F3(2, 0x24, 0), F3(~2, ~0x24, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "mulscc",	F3(2, 0x24, 1), F3(~2, ~0x24, ~1),		"1,i,d", 0, ajit },

{ "orcc",	F3(2, 0x12, 0), F3(~2, ~0x12, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "orcc",	F3(2, 0x12, 1), F3(~2, ~0x12, ~1),		"1,i,d", 0, ajit },
{ "orcc",	F3(2, 0x12, 1), F3(~2, ~0x12, ~1),		"i,1,d", 0, ajit },

/* This is not a commutative instruction.  */
{ "orncc",	F3(2, 0x16, 0), F3(~2, ~0x16, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "orncc",	F3(2, 0x16, 1), F3(~2, ~0x16, ~1),		"1,i,d", 0, ajit },

/* This is not a commutative instruction.  */
{ "orn",	F3(2, 0x06, 0), F3(~2, ~0x06, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "orn",	F3(2, 0x06, 1), F3(~2, ~0x06, ~1),		"1,i,d", 0, ajit },

{ "tst",	F3(2, 0x12, 0), F3(~2, ~0x12, ~0)|RD_G0|ASI_RS2(~0),	"1", 0, ajit }, /* orcc rs1, %g0, %g0 */

{ "wr",	F3(2, 0x30, 0),		F3(~2, ~0x30, ~0)|ASI(~0),		"1,2,m", 0, ajit }, /* wr r,r,%asrX */
{ "wr",	F3(2, 0x30, 1),		F3(~2, ~0x30, ~1),			"1,i,m", 0, ajit }, /* wr r,i,%asrX */
{ "wr",	F3(2, 0x30, 0),		F3(~2, ~0x30, ~0)|RS1_G0|ASI(~0),	"2,m", F_ALIAS, ajit }, /* wr %g0,rs2,%asrX */
{ "wr",	F3(2, 0x30, 1),		F3(~2, ~0x30, ~1)|RS1_G0,		"i,m", F_ALIAS, ajit }, /* wr %g0,i,%asrX */
{ "wr",	F3(2, 0x30, 0),		F3(~2, ~0x30, ~0)|ASI_RS2(~0),		"1,m", F_ALIAS, ajit }, /* wr rs1,%g0,%asrX */
{ "wr",	F3(2, 0x30, 0),		F3(~2, ~0x30, ~0)|RD_G0|ASI(~0),	"1,2,y", 0, ajit }, /* wr r,r,%y */
{ "wr",	F3(2, 0x30, 1),		F3(~2, ~0x30, ~1)|RD_G0,		"1,i,y", 0, ajit }, /* wr r,i,%y */
{ "wr",	F3(2, 0x30, 0),		F3(~2, ~0x30, ~0)|RD_G0|RS1_G0|ASI(~0),	"2,y", F_ALIAS, ajit }, /* wr %g0,rs2,%y */
{ "wr",	F3(2, 0x30, 1),		F3(~2, ~0x30, ~1)|RD_G0|RS1_G0,		"i,y", F_ALIAS, ajit }, /* wr %g0,i,%y */
{ "wr",	F3(2, 0x30, 0),		F3(~2, ~0x30, ~0)|RD_G0|ASI_RS2(~0),	"1,y", F_ALIAS, ajit }, /* wr rs1,%g0,%y */
{ "wr",	F3(2, 0x31, 0),		F3(~2, ~0x31, ~0)|RD_G0|ASI(~0),	"1,2,p", 0, ajit }, /* wr r,r,%psr */
{ "wr",	F3(2, 0x31, 1),		F3(~2, ~0x31, ~1)|RD_G0,		"1,i,p", 0, ajit }, /* wr r,i,%psr */
{ "wr",	F3(2, 0x31, 0),		F3(~2, ~0x31, ~0)|RD_G0|RS1_G0|ASI(~0),	"2,p", F_ALIAS, ajit }, /* wr %g0,rs2,%psr */
{ "wr",	F3(2, 0x31, 1),		F3(~2, ~0x31, ~1)|RD_G0|RS1_G0,		"i,p", F_ALIAS, ajit }, /* wr %g0,i,%psr */
{ "wr",	F3(2, 0x31, 0),		F3(~2, ~0x31, ~0)|RD_G0|ASI_RS2(~0),	"1,p", F_ALIAS, ajit }, /* wr rs1,%g0,%psr */
{ "wr",	F3(2, 0x32, 0),		F3(~2, ~0x32, ~0)|RD_G0|ASI(~0),	"1,2,w", 0, ajit }, /* wr r,r,%wim */
{ "wr",	F3(2, 0x32, 1),		F3(~2, ~0x32, ~1)|RD_G0,		"1,i,w", 0, ajit }, /* wr r,i,%wim */
{ "wr",	F3(2, 0x32, 0),		F3(~2, ~0x32, ~0)|RD_G0|RS1_G0|ASI(~0),	"2,w", F_ALIAS, ajit }, /* wr %g0,rs2,%wim */
{ "wr",	F3(2, 0x32, 1),		F3(~2, ~0x32, ~1)|RD_G0|RS1_G0,		"i,w", F_ALIAS, ajit }, /* wr %g0,i,%wim */
{ "wr",	F3(2, 0x32, 0),		F3(~2, ~0x32, ~0)|RD_G0|ASI_RS2(~0),	"1,w", F_ALIAS, ajit }, /* wr rs1,%g0,%wim */
{ "wr",	F3(2, 0x33, 0),		F3(~2, ~0x33, ~0)|RD_G0|ASI(~0),	"1,2,t", 0, ajit }, /* wr r,r,%tbr */
{ "wr",	F3(2, 0x33, 1),		F3(~2, ~0x33, ~1)|RD_G0,		"1,i,t", 0, ajit }, /* wr r,i,%tbr */
{ "wr",	F3(2, 0x33, 0),		F3(~2, ~0x33, ~0)|RD_G0|RS1_G0|ASI(~0),	"2,t", F_ALIAS, ajit }, /* wr %g0,rs2,%tbr */
{ "wr",	F3(2, 0x33, 1),		F3(~2, ~0x33, ~1)|RD_G0|RS1_G0,		"i,t", F_ALIAS, ajit }, /* wr %g0,i,%tbr */
{ "wr",	F3(2, 0x33, 0),		F3(~2, ~0x33, ~0)|RD_G0|ASI_RS2(~0),	"1,t", F_ALIAS, ajit }, /* wr rs1,%g0,%tbr */

{ "rd",	F3(2, 0x28, 0),			F3(~2, ~0x28, ~0)|SIMM13(~0),		"M,d", 0, ajit }, /* rd %asrX,r */
{ "rd",	F3(2, 0x28, 0),			F3(~2, ~0x28, ~0)|RS1_G0|SIMM13(~0),	"y,d", 0, ajit }, /* rd %y,r */
{ "rd",	F3(2, 0x29, 0),			F3(~2, ~0x29, ~0)|RS1_G0|SIMM13(~0),	"p,d", 0, ajit }, /* rd %psr,r */
{ "rd",	F3(2, 0x2a, 0),			F3(~2, ~0x2a, ~0)|RS1_G0|SIMM13(~0),	"w,d", 0, ajit }, /* rd %wim,r */
{ "rd",	F3(2, 0x2b, 0),			F3(~2, ~0x2b, ~0)|RS1_G0|SIMM13(~0),	"t,d", 0, ajit }, /* rd %tbr,r */

/* ??? This group seems wrong.  A three operand move?  */
{ "mov",	F3(2, 0x30, 0), F3(~2, ~0x30, ~0)|ASI(~0),		"1,2,m", F_ALIAS, ajit }, /* wr r,r,%asrX */
{ "mov",	F3(2, 0x30, 1), F3(~2, ~0x30, ~1),			"1,i,m", F_ALIAS, ajit }, /* wr r,i,%asrX */

{ "mov",	F3(2, 0x28, 0), F3(~2, ~0x28, ~0)|SIMM13(~0),		"M,d", F_ALIAS, ajit }, /* rd %asr1,r */
{ "mov",	F3(2, 0x28, 0), F3(~2, ~0x28, ~0)|RS1_G0|SIMM13(~0),	"y,d", F_ALIAS, ajit }, /* rd %y,r */
{ "mov",	F3(2, 0x29, 0), F3(~2, ~0x29, ~0)|RS1_G0|SIMM13(~0),	"p,d", F_ALIAS, ajit }, /* rd %psr,r */
{ "mov",	F3(2, 0x2a, 0), F3(~2, ~0x2a, ~0)|RS1_G0|SIMM13(~0),	"w,d", F_ALIAS, ajit }, /* rd %wim,r */
{ "mov",	F3(2, 0x2b, 0), F3(~2, ~0x2b, ~0)|RS1_G0|SIMM13(~0),	"t,d", F_ALIAS, ajit }, /* rd %tbr,r */

{ "mov",	F3(2, 0x30, 0), F3(~2, ~0x30, ~0)|RS1_G0|ASI(~0),	"2,m", F_ALIAS, ajit }, /* wr %g0,rs2,%asrX */
{ "mov",	F3(2, 0x30, 1), F3(~2, ~0x30, ~1)|RS1_G0,		"i,m", F_ALIAS, ajit }, /* wr %g0,i,%asrX */
{ "mov",	F3(2, 0x30, 0), F3(~2, ~0x30, ~0)|ASI_RS2(~0),		"1,m", F_ALIAS, ajit }, /* wr rs1,%g0,%asrX */
{ "mov",	F3(2, 0x30, 1), F3(~2, ~0x30, ~1)|SIMM13(~0),		"1,m", F_ALIAS, ajit }, /* wr rs1,0,%asrX */
{ "mov",	F3(2, 0x30, 0), F3(~2, ~0x30, ~0)|RD_G0|RS1_G0|ASI(~0),	"2,y", F_ALIAS, ajit }, /* wr %g0,rs2,%y */
{ "mov",	F3(2, 0x30, 1), F3(~2, ~0x30, ~1)|RD_G0|RS1_G0,		"i,y", F_ALIAS, ajit }, /* wr %g0,i,%y */
{ "mov",	F3(2, 0x31, 0), F3(~2, ~0x31, ~0)|RD_G0|RS1_G0|ASI(~0),	"2,p", F_ALIAS, ajit }, /* wr %g0,rs2,%psr */
{ "mov",	F3(2, 0x31, 1), F3(~2, ~0x31, ~1)|RD_G0|RS1_G0,		"i,p", F_ALIAS, ajit }, /* wr %g0,i,%psr */
{ "mov",	F3(2, 0x32, 0), F3(~2, ~0x32, ~0)|RD_G0|RS1_G0|ASI(~0),	"2,w", F_ALIAS, ajit }, /* wr %g0,rs2,%wim */
{ "mov",	F3(2, 0x32, 1), F3(~2, ~0x32, ~1)|RD_G0|RS1_G0,		"i,w", F_ALIAS, ajit }, /* wr %g0,i,%wim */
{ "mov",	F3(2, 0x33, 0), F3(~2, ~0x33, ~0)|RD_G0|RS1_G0|ASI(~0),	"2,t", F_ALIAS, ajit }, /* wr %g0,rs2,%tbr */
{ "mov",	F3(2, 0x33, 1), F3(~2, ~0x33, ~1)|RD_G0|RS1_G0,		"i,t", F_ALIAS, ajit }, /* wr %g0,i,%tbr */

{ "mov",	F3(2, 0x02, 0), F3(~2, ~0x02, ~0)|RS1_G0|ASI(~0),	"2,d", 0, ajit }, /* or %g0,rs2,d */
{ "mov",	F3(2, 0x02, 1), F3(~2, ~0x02, ~1)|RS1_G0,		"i,d", 0, ajit }, /* or %g0,i,d	*/

{ "or",	F3(2, 0x02, 0), F3(~2, ~0x02, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "or",	F3(2, 0x02, 1), F3(~2, ~0x02, ~1),		"1,i,d", 0, ajit },
{ "or",	F3(2, 0x02, 1), F3(~2, ~0x02, ~1),		"i,1,d", 0, ajit },
{ "or",	F3(2, 0x02, 0), F3(~2, ~0x02, ~0)|ASI(~0),	"1,2,d", 0, ajit },

{ "ord",	F4(2, 0x02, 0, 1), F4(~2, ~0x02, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */
{ "ordcc",	F4(2, 0x12, 0, 1), F4(~2, ~0x12, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */
{ "ordn",	F4(2, 0x06, 0, 1), F4(~2, ~0x06, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */
{ "ordncc",	F4(2, 0x16, 0, 1), F4(~2, ~0x16, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */

{ "bset",	F3(2, 0x02, 0), F3(~2, ~0x02, ~0)|ASI(~0),	"2,r", F_ALIAS, ajit },	/* or rd,rs2,rd */
{ "bset",	F3(2, 0x02, 1), F3(~2, ~0x02, ~1),		"i,r", F_ALIAS, ajit },	/* or rd,i,rd */

/* This is not a commutative instruction.  */
{ "andn",	F3(2, 0x05, 0), F3(~2, ~0x05, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "andn",	F3(2, 0x05, 1), F3(~2, ~0x05, ~1),		"1,i,d", 0, ajit },
{ "anddn",	F4(2, 0x05, 0, 1), F4(~2, ~0x05, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */

/* This is not a commutative instruction.  */
{ "andncc",	F3(2, 0x15, 0), F3(~2, ~0x15, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "andncc",	F3(2, 0x15, 1), F3(~2, ~0x15, ~1),		"1,i,d", 0, ajit },
{ "anddncc",	F4(2, 0x15, 0, 1), F4(~2, ~0x15, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */

{ "bclr",	F3(2, 0x05, 0), F3(~2, ~0x05, ~0)|ASI(~0),	"2,r", F_ALIAS, ajit },	/* andn rd,rs2,rd */
{ "bclr",	F3(2, 0x05, 1), F3(~2, ~0x05, ~1),		"i,r", F_ALIAS, ajit },	/* andn rd,i,rd */

{ "cmp",	F3(2, 0x14, 0), F3(~2, ~0x14, ~0)|RD_G0|ASI(~0),	"1,2", 0, ajit },	/* subcc rs1,rs2,%g0 */
{ "cmp",	F3(2, 0x14, 1), F3(~2, ~0x14, ~1)|RD_G0,		"1,i", 0, ajit },	/* subcc rs1,i,%g0 */

{ "sub",	F3(2, 0x04, 0), F3(~2, ~0x04, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "sub",	F3(2, 0x04, 1), F3(~2, ~0x04, ~1),		"1,i,d", 0, ajit },
{ "subd",	F4(2, 0x04, 0, 1), F4(~2, ~0x04, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */

{ "subcc",	F3(2, 0x14, 0), F3(~2, ~0x14, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "subcc",	F3(2, 0x14, 1), F3(~2, ~0x14, ~1),		"1,i,d", 0, ajit },
{ "subdcc",	F4(2, 0x14, 0, 1), F4(~2, ~0x14, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */

{ "subx",	F3(2, 0x0c, 0), F3(~2, ~0x0c, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "subx",	F3(2, 0x0c, 1), F3(~2, ~0x0c, ~1),		"1,i,d", 0, ajit },

{ "subxcc",	F3(2, 0x1c, 0), F3(~2, ~0x1c, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "subxcc",	F3(2, 0x1c, 1), F3(~2, ~0x1c, ~1),		"1,i,d", 0, ajit },

{ "vsubd8",	F6(2, 0x04, 0, 2, 1), F6(~2, ~0x04, ~0, ~2, ~1),	"1,2,d", 0, ajit }, /* AJIT */
{ "vsubd16",	F6(2, 0x04, 0, 2, 2), F6(~2, ~0x04, ~0, ~2, ~3),	"1,2,d", 0, ajit }, /* AJIT */
{ "vsubd32",	F6(2, 0x04, 0, 2, 4), F6(~2, ~0x04, ~0, ~2, ~4),	"1,2,d", 0, ajit }, /* AJIT */

{ "and",	F3(2, 0x01, 0), F3(~2, ~0x01, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "and",	F3(2, 0x01, 1), F3(~2, ~0x01, ~1),		"1,i,d", 0, ajit },
{ "and",	F3(2, 0x01, 1), F3(~2, ~0x01, ~1),		"i,1,d", 0, ajit },
{ "andd",	F4(2, 0x01, 0, 1), F4(~2, ~0x01, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */

{ "andcc",	F3(2, 0x11, 0), F3(~2, ~0x11, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "andcc",	F3(2, 0x11, 1), F3(~2, ~0x11, ~1),		"1,i,d", 0, ajit },
{ "andcc",	F3(2, 0x11, 1), F3(~2, ~0x11, ~1),		"i,1,d", 0, ajit },
{ "anddcc",	F4(2, 0x11, 0, 1), F4(~2, ~0x11, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */

{ "dec",	F3(2, 0x04, 1)|SIMM13(0x1), F3(~2, ~0x04, ~1)|SIMM13(~0x0001), "r", F_ALIAS, ajit },	/* sub rd,1,rd */
{ "dec",	F3(2, 0x04, 1),		    F3(~2, ~0x04, ~1),		       "i,r", F_ALIAS, ajit },	/* sub rd,imm,rd */
{ "deccc",	F3(2, 0x14, 1)|SIMM13(0x1), F3(~2, ~0x14, ~1)|SIMM13(~0x0001), "r", F_ALIAS, ajit },	/* subcc rd,1,rd */
{ "deccc",	F3(2, 0x14, 1),		    F3(~2, ~0x14, ~1),		       "i,r", F_ALIAS, ajit },	/* subcc rd,imm,rd */
{ "inc",	F3(2, 0x00, 1)|SIMM13(0x1), F3(~2, ~0x00, ~1)|SIMM13(~0x0001), "r", F_ALIAS, ajit },	/* add rd,1,rd */
{ "inc",	F3(2, 0x00, 1),		    F3(~2, ~0x00, ~1),		       "i,r", F_ALIAS, ajit },	/* add rd,imm,rd */
{ "inccc",	F3(2, 0x10, 1)|SIMM13(0x1), F3(~2, ~0x10, ~1)|SIMM13(~0x0001), "r", F_ALIAS, ajit },	/* addcc rd,1,rd */
{ "inccc",	F3(2, 0x10, 1),		    F3(~2, ~0x10, ~1),		       "i,r", F_ALIAS, ajit },	/* addcc rd,imm,rd */

{ "btst",	F3(2, 0x11, 0), F3(~2, ~0x11, ~0)|RD_G0|ASI(~0), "1,2", F_ALIAS, ajit },	/* andcc rs1,rs2,%g0 */
{ "btst",	F3(2, 0x11, 1), F3(~2, ~0x11, ~1)|RD_G0, "i,1", F_ALIAS, ajit },	/* andcc rs1,i,%g0 */

{ "neg",	F3(2, 0x04, 0), F3(~2, ~0x04, ~0)|RS1_G0|ASI(~0), "2,d", F_ALIAS, ajit }, /* sub %g0,rs2,rd */
{ "neg",	F3(2, 0x04, 0), F3(~2, ~0x04, ~0)|RS1_G0|ASI(~0), "O", F_ALIAS, ajit }, /* sub %g0,rd,rd */

{ "add",	F3(2, 0x00, 0), F3(~2, ~0x00, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "add",	F3(2, 0x00, 1), F3(~2, ~0x00, ~1),		"1,i,d", 0, ajit },
{ "add",	F3(2, 0x00, 1), F3(~2, ~0x00, ~1),		"i,1,d", 0, ajit },

{ "addd",	F4(2, 0x00, 0, 1), F4(~2, ~0x00, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */

{ "addcc",	F3(2, 0x10, 0), F3(~2, ~0x10, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "addcc",	F3(2, 0x10, 1), F3(~2, ~0x10, ~1),		"1,i,d", 0, ajit },
{ "addcc",	F3(2, 0x10, 1), F3(~2, ~0x10, ~1),		"i,1,d", 0, ajit },

{ "adddcc",	F4(2, 0x10, 0,1), F4(~2, ~0x10, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */

{ "addx",	F3(2, 0x08, 0), F3(~2, ~0x08, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "addx",	F3(2, 0x08, 1), F3(~2, ~0x08, ~1),		"1,i,d", 0, ajit },
{ "addx",	F3(2, 0x08, 1), F3(~2, ~0x08, ~1),		"i,1,d", 0, ajit },

{ "addxcc",	F3(2, 0x18, 0), F3(~2, ~0x18, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "addxcc",	F3(2, 0x18, 1), F3(~2, ~0x18, ~1),		"1,i,d", 0, ajit },
{ "addxcc",	F3(2, 0x18, 1), F3(~2, ~0x18, ~1),		"i,1,d", 0, ajit },

{ "vaddd8",	F6(2, 0x00, 0, 2, 1), F6(~2, ~0x00, ~0, ~2, ~1),	"1,2,d", 0, ajit }, /* AJIT */
{ "vaddd16",	F6(2, 0x00, 0, 2, 2), F6(~2, ~0x00, ~0, ~2, ~2),	"1,2,d", 0, ajit }, /* AJIT */
{ "vaddd32",	F6(2, 0x00, 0, 2, 4), F6(~2, ~0x00, ~0, ~2, ~4),	"1,2,d", 0, ajit }, /* AJIT */

{ "smul",	F3(2, 0x0b, 0), F3(~2, ~0x0b, ~0)|ASI(~0),	"1,2,d", F_MUL32, ajit },
{ "smul",	F3(2, 0x0b, 1), F3(~2, ~0x0b, ~1),		"1,i,d", F_MUL32, ajit },
{ "smul",	F3(2, 0x0b, 1), F3(~2, ~0x0b, ~1),		"i,1,d", F_MUL32, ajit },
{ "smuld",	F4(2, 0x0b, 0, 1), F4(~2, ~0x0b, ~0, ~1),	"1,2,d", F_MUL32, ajit }, /* AJIT */
{ "smulcc",	F3(2, 0x1b, 0), F3(~2, ~0x1b, ~0)|ASI(~0),	"1,2,d", F_MUL32, ajit },
{ "smulcc",	F3(2, 0x1b, 1), F3(~2, ~0x1b, ~1),		"1,i,d", F_MUL32, ajit },
{ "smulcc",	F3(2, 0x1b, 1), F3(~2, ~0x1b, ~1),		"i,1,d", F_MUL32, ajit },
{ "smuldcc",	F4(2, 0x1b, 0, 1), F4(~2, ~0x1b, ~0, ~1),	"1,2,d", F_MUL32, ajit }, /* AJIT */
{ "umul",	F3(2, 0x0a, 0), F3(~2, ~0x0a, ~0)|ASI(~0),	"1,2,d", F_MUL32, ajit },
{ "umul",	F3(2, 0x0a, 1), F3(~2, ~0x0a, ~1),		"1,i,d", F_MUL32, ajit },
{ "umul",	F3(2, 0x0a, 1), F3(~2, ~0x0a, ~1),		"i,1,d", F_MUL32, ajit },
{ "umulcc",	F3(2, 0x1a, 0), F3(~2, ~0x1a, ~0)|ASI(~0),	"1,2,d", F_MUL32, ajit },
{ "umulcc",	F3(2, 0x1a, 1), F3(~2, ~0x1a, ~1),		"1,i,d", F_MUL32, ajit },
{ "umulcc",	F3(2, 0x1a, 1), F3(~2, ~0x1a, ~1),		"i,1,d", F_MUL32, ajit },
{ "umuld",	F4(2, 0x0a, 0, 1), F4(~2, ~0x0a, ~0, ~1),	"1,2,d", F_MUL32, ajit }, /* AJIT */
{ "umuldcc",	F4(2, 0x1a, 0, 1), F4(~2, ~0x1a, ~0, ~1),	"1,2,d", F_MUL32, ajit }, /* AJIT */

{ "vumuld8",	F6(2, 0x0a, 0, 2, 1), F6(~2, ~0x0a, ~0, ~2, ~1),	"1,2,d", 0, ajit }, /* AJIT */
{ "vumuld16",	F6(2, 0x0a, 0, 2, 2), F6(~2, ~0x0a, ~0, ~2, ~3),	"1,2,d", 0, ajit }, /* AJIT */
{ "vumuld32",	F6(2, 0x0a, 0, 2, 4), F6(~2, ~0x0a, ~0, ~2, ~4),	"1,2,d", 0, ajit }, /* AJIT */
{ "vsmuld8",	F6(2, 0x1a, 0, 2, 1), F6(~2, ~0x1a, ~0, ~2, ~1),	"1,2,d", 0, ajit }, /* AJIT */
{ "vsmuld16",	F6(2, 0x1a, 0, 2, 2), F6(~2, ~0x1a, ~0, ~2, ~3),	"1,2,d", 0, ajit }, /* AJIT */
{ "vsmuld32",	F6(2, 0x1a, 0, 2, 4), F6(~2, ~0x1a, ~0, ~2, ~4),	"1,2,d", 0, ajit }, /* AJIT */

{ "sdiv",	F3(2, 0x0f, 0), F3(~2, ~0x0f, ~0)|ASI(~0),	"1,2,d", F_DIV32, ajit },
{ "sdiv",	F3(2, 0x0f, 1), F3(~2, ~0x0f, ~1),		"1,i,d", F_DIV32, ajit },
{ "sdiv",	F3(2, 0x0f, 1), F3(~2, ~0x0f, ~1),		"i,1,d", F_DIV32, ajit },
{ "sdivcc",	F3(2, 0x1f, 0), F3(~2, ~0x1f, ~0)|ASI(~0),	"1,2,d", F_DIV32, ajit },
{ "sdivcc",	F3(2, 0x1f, 1), F3(~2, ~0x1f, ~1),		"1,i,d", F_DIV32, ajit },
{ "sdivcc",	F3(2, 0x1f, 1), F3(~2, ~0x1f, ~1),		"i,1,d", F_DIV32, ajit },
{ "sdivd",	F4(2, 0x0f, 0, 1), F4(~2, ~0x0f, ~0, ~1),	"1,2,d", F_DIV32, ajit }, /* AJIT */
{ "sdivdcc",	F4(2, 0x1f, 0, 1), F4(~2, ~0x1f, ~0, ~1),	"1,2,d", F_DIV32, ajit }, /* AJIT */
{ "udiv",	F3(2, 0x0e, 0), F3(~2, ~0x0e, ~0)|ASI(~0),	"1,2,d", F_DIV32, ajit },
{ "udiv",	F3(2, 0x0e, 1), F3(~2, ~0x0e, ~1),		"1,i,d", F_DIV32, ajit },
{ "udiv",	F3(2, 0x0e, 1), F3(~2, ~0x0e, ~1),		"i,1,d", F_DIV32, ajit },
{ "udivcc",	F3(2, 0x1e, 0), F3(~2, ~0x1e, ~0)|ASI(~0),	"1,2,d", F_DIV32, ajit },
{ "udivcc",	F3(2, 0x1e, 1), F3(~2, ~0x1e, ~1),		"1,i,d", F_DIV32, ajit },
{ "udivcc",	F3(2, 0x1e, 1), F3(~2, ~0x1e, ~1),		"i,1,d", F_DIV32, ajit },
{ "udivdcc",	F4(2, 0x1e, 0, 1), F4(~2, ~0x1e, ~0, ~1),	"1,2,d", F_DIV32, ajit }, /* AJIT */
{ "udivd",	F4(2, 0x0e, 0, 1), F4(~2, ~0x0e, ~0, ~1),	"1,2,d", F_DIV32, ajit }, /* AJIT */

/* AJIT Additions 1 */
/* CSWAP family */
{ "cswapd",     F3(3, 0x2f, 0), F3(~3, ~0x2f, ~0), "[1+2]A,d", 0, ajit }, /* AJIT */
{ "cswapd",     F3(3, 0x2f, 1), F3(~3, ~0x2f, ~1), "[1+i],d",  0, ajit }, /* AJIT */
{ "cswapda",    F3(3, 0x3f, 0), F3(~3, ~0x3f, ~0), "[1+2]A,d", 0, ajit }, /* AJIT */
{ "cswapda",    F3(3, 0x3f, 1), F3(~3, ~0x3f, ~1), "[1+i],d",  0, ajit }, /* AJIT */
/* End AJIT Additions 1 */

{ "call",	F1(0x1), F1(~0x1), "L", F_JSR|F_DELAYED, ajit },
{ "call",	F1(0x1), F1(~0x1), "L,#", F_JSR|F_DELAYED, ajit },

{ "call",	F3(2, 0x38, 0)|RD(0xf), F3(~2, ~0x38, ~0)|RD(~0xf)|ASI(~0),	"1+2", F_JSR|F_DELAYED, ajit }, /* jmpl rs1+rs2,%o7 */
{ "call",	F3(2, 0x38, 0)|RD(0xf), F3(~2, ~0x38, ~0)|RD(~0xf)|ASI(~0),	"1+2,#", F_JSR|F_DELAYED, ajit },
{ "call",	F3(2, 0x38, 0)|RD(0xf), F3(~2, ~0x38, ~0)|RD(~0xf)|ASI_RS2(~0),	"1", F_JSR|F_DELAYED, ajit }, /* jmpl rs1+%g0,%o7 */
{ "call",	F3(2, 0x38, 0)|RD(0xf), F3(~2, ~0x38, ~0)|RD(~0xf)|ASI_RS2(~0),	"1,#", F_JSR|F_DELAYED, ajit },
{ "call",	F3(2, 0x38, 1)|RD(0xf), F3(~2, ~0x38, ~1)|RD(~0xf),		"1+i", F_JSR|F_DELAYED, ajit }, /* jmpl rs1+i,%o7 */
{ "call",	F3(2, 0x38, 1)|RD(0xf), F3(~2, ~0x38, ~1)|RD(~0xf),		"1+i,#", F_JSR|F_DELAYED, ajit },
{ "call",	F3(2, 0x38, 1)|RD(0xf), F3(~2, ~0x38, ~1)|RD(~0xf),		"i+1", F_JSR|F_DELAYED, ajit }, /* jmpl i+rs1,%o7 */
{ "call",	F3(2, 0x38, 1)|RD(0xf), F3(~2, ~0x38, ~1)|RD(~0xf),		"i+1,#", F_JSR|F_DELAYED, ajit },
{ "call",	F3(2, 0x38, 1)|RD(0xf), F3(~2, ~0x38, ~1)|RD(~0xf)|RS1_G0,	"i", F_JSR|F_DELAYED, ajit }, /* jmpl %g0+i,%o7 */
{ "call",	F3(2, 0x38, 1)|RD(0xf), F3(~2, ~0x38, ~1)|RD(~0xf)|RS1_G0,	"i,#", F_JSR|F_DELAYED, ajit },
{ "call",	F3(2, 0x38, 1)|RD(0xf), F3(~2, ~0x38, ~1)|RD(~0xf)|SIMM13(~0),	"1", F_JSR|F_DELAYED, ajit }, /* jmpl rs1+0,%o7 */
{ "call",	F3(2, 0x38, 1)|RD(0xf), F3(~2, ~0x38, ~1)|RD(~0xf)|SIMM13(~0),	"1,#", F_JSR|F_DELAYED, ajit },

/* Conditional instructions.

   Because this part of the table was such a mess earlier, I have
   macrofied it so that all the branches and traps are generated from
   a single-line description of each condition value.  John Gilmore. */

/* Define branches -- one annulled, one without, etc. */
#define br(opcode, mask, lose, flags) \
 { opcode, (mask)|ANNUL, (lose),       ",a l",   (flags), ajit }, \
 { opcode, (mask)      , (lose)|ANNUL, "l",     (flags), ajit }

#define tr(opcode, mask, lose, flags) \
 { opcode, (mask)|IMMED, (lose)|RS1_G0,		"i",     (flags), ajit }, /* %g0 + imm */ \
 { opcode, (mask)|IMMED, (lose),		"1+i",   (flags), ajit }, /* rs1 + imm */ \
 { opcode, (mask)|IMMED, (lose),		"i+1",   (flags), ajit }, /* imm + rs1 */ \
 { opcode, (mask), IMMED|(lose),		"1+2",   (flags), ajit }, /* rs1 + rs2 */ \
 { opcode, (mask), IMMED|(lose)|RS2_G0,		"1",     (flags), ajit } /* rs1 + %g0 */

#define cond(bop, top, mask, flags) \
  br(bop,  F2(0, 2)|(mask), F2(~0, ~2)|((~mask)&COND(~0)), F_DELAYED|(flags)), \
  tr(top,  F3(2, 0x3a, 0)|(mask), F3(~2, ~0x3a, 0)|((~mask)&COND(~0)), ((flags) & ~(F_UNBR|F_CONDBR)))

/* Define all the conditions, all the branches, all the traps.  */

/* Standard branch, trap mnemonics */
cond ("b",	"ta",   CONDA, F_UNBR),
/* Alternative form (just for assembly, not for disassembly) */
cond ("ba",	"t",    CONDA, F_UNBR|F_ALIAS),

cond ("bcc",	"tcc",  CONDCC, F_CONDBR),
cond ("bcs",	"tcs",  CONDCS, F_CONDBR),
cond ("be",	"te",   CONDE, F_CONDBR),
cond ("beq",	"teq",  CONDE, F_CONDBR|F_ALIAS),
cond ("bg",	"tg",   CONDG, F_CONDBR),
cond ("bgt",	"tgt",  CONDG, F_CONDBR|F_ALIAS),
cond ("bge",	"tge",  CONDGE, F_CONDBR),
cond ("bgeu",	"tgeu", CONDGEU, F_CONDBR|F_ALIAS), /* for cc */
cond ("bgu",	"tgu",  CONDGU, F_CONDBR),
cond ("bl",	"tl",   CONDL, F_CONDBR),
cond ("blt",	"tlt",  CONDL, F_CONDBR|F_ALIAS),
cond ("ble",	"tle",  CONDLE, F_CONDBR),
cond ("bleu",	"tleu", CONDLEU, F_CONDBR),
cond ("blu",	"tlu",  CONDLU, F_CONDBR|F_ALIAS), /* for cs */
cond ("bn",	"tn",   CONDN, F_CONDBR),
cond ("bne",	"tne",  CONDNE, F_CONDBR),
cond ("bneg",	"tneg", CONDNEG, F_CONDBR),
cond ("bnz",	"tnz",  CONDNZ, F_CONDBR|F_ALIAS), /* for ne */
cond ("bpos",	"tpos", CONDPOS, F_CONDBR),
cond ("bvc",	"tvc",  CONDVC, F_CONDBR),
cond ("bvs",	"tvs",  CONDVS, F_CONDBR),
cond ("bz",	"tz",   CONDZ, F_CONDBR|F_ALIAS), /* for e */

#undef cond
#undef br
#undef tr

/* Coprocessor branches.  */
#define CBR(opcode, mask, lose, flags, arch) \
 { opcode, (mask), ANNUL | (lose), "l",    flags | F_DELAYED, arch }, \
 { opcode, (mask) | ANNUL, (lose), ",a l", flags | F_DELAYED, arch }

/* Floating point branches.  */
#define FBR(opcode, mask, lose, flags) \
 { opcode, (mask), ANNUL | (lose), "l",    flags | F_DELAYED | F_FBR, ajit }, \
 { opcode, (mask) | ANNUL, (lose), ",a l", flags | F_DELAYED | F_FBR, ajit }

#define CONDFC(fop, cop, mask, flags) \
  FBR(fop, F2(0, 6)|COND(mask), F2(~0, ~6)|COND(~(mask)), flags), \
  CBR(cop, F2(0, 7)|COND(mask), F2(~0, ~7)|COND(~(mask)), flags, ajit)

#define CONDFCL(fop, cop, mask, flags) \
  FBR(fop, F2(0, 6)|COND(mask), F2(~0, ~6)|COND(~(mask)), flags), \
  CBR(cop, F2(0, 7)|COND(mask), F2(~0, ~7)|COND(~(mask)), flags, ajit)

#define CONDF(fop, mask, flags) \
  FBR(fop, F2(0, 6)|COND(mask), F2(~0, ~6)|COND(~(mask)), flags)

CONDFC  ("fb",    "cb",    0x8, F_UNBR),
CONDFCL ("fba",	  "cba",   0x8, F_UNBR|F_ALIAS),
CONDFC  ("fbe",	  "cb0",   0x9, F_CONDBR),
CONDF   ("fbz",            0x9, F_CONDBR|F_ALIAS),
CONDFC  ("fbg",	  "cb2",   0x6, F_CONDBR),
CONDFC  ("fbge",  "cb02",  0xb, F_CONDBR),
CONDFC  ("fbl",	  "cb1",   0x4, F_CONDBR),
CONDFC  ("fble",  "cb01",  0xd, F_CONDBR),
CONDFC  ("fblg",  "cb12",  0x2, F_CONDBR),
CONDFCL ("fbn",	  "cbn",   0x0, F_UNBR),
CONDFC  ("fbne",  "cb123", 0x1, F_CONDBR),
CONDF   ("fbnz",           0x1, F_CONDBR|F_ALIAS),
CONDFC  ("fbo",	  "cb012", 0xf, F_CONDBR),
CONDFC  ("fbu",	  "cb3",   0x7, F_CONDBR),
CONDFC  ("fbue",  "cb03",  0xa, F_CONDBR),
CONDFC  ("fbug",  "cb23",  0x5, F_CONDBR),
CONDFC  ("fbuge", "cb023", 0xc, F_CONDBR),
CONDFC  ("fbul",  "cb13",  0x3, F_CONDBR),
CONDFC  ("fbule", "cb013", 0xe, F_CONDBR),

#undef CONDFC
#undef CONDFCL
#undef CONDF
#undef CBR
#undef FBR

{ "jmp",	F3(2, 0x38, 0), F3(~2, ~0x38, ~0)|RD_G0|ASI(~0),	"1+2", F_UNBR|F_DELAYED, ajit }, /* jmpl rs1+rs2,%g0 */
{ "jmp",	F3(2, 0x38, 0), F3(~2, ~0x38, ~0)|RD_G0|ASI_RS2(~0),	"1", F_UNBR|F_DELAYED, ajit }, /* jmpl rs1+%g0,%g0 */
{ "jmp",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|RD_G0,		"1+i", F_UNBR|F_DELAYED, ajit }, /* jmpl rs1+i,%g0 */
{ "jmp",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|RD_G0,		"i+1", F_UNBR|F_DELAYED, ajit }, /* jmpl i+rs1,%g0 */
{ "jmp",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|RD_G0|RS1_G0,		"i", F_UNBR|F_DELAYED, ajit }, /* jmpl %g0+i,%g0 */
{ "jmp",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|RD_G0|SIMM13(~0),	"1", F_UNBR|F_DELAYED, ajit }, /* jmpl rs1+0,%g0 */

{ "nop",	F2(0, 4), 0xfeffffff, "", 0, ajit }, /* sethi 0, %g0 */

{ "set",	F2(0x0, 0x4), F2(~0x0, ~0x4), "S0,d", F_ALIAS, ajit },

{ "sethi",	F2(0x0, 0x4), F2(~0x0, ~0x4), "h,d", 0, ajit },

{ "taddcc",	F3(2, 0x20, 0), F3(~2, ~0x20, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "taddcc",	F3(2, 0x20, 1), F3(~2, ~0x20, ~1),		"1,i,d", 0, ajit },
{ "taddcc",	F3(2, 0x20, 1), F3(~2, ~0x20, ~1),		"i,1,d", 0, ajit },
{ "taddcctv",	F3(2, 0x22, 0), F3(~2, ~0x22, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "taddcctv",	F3(2, 0x22, 1), F3(~2, ~0x22, ~1),		"1,i,d", 0, ajit },
{ "taddcctv",	F3(2, 0x22, 1), F3(~2, ~0x22, ~1),		"i,1,d", 0, ajit },

{ "tsubcc",	F3(2, 0x21, 0), F3(~2, ~0x21, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "tsubcc",	F3(2, 0x21, 1), F3(~2, ~0x21, ~1),		"1,i,d", 0, ajit },
{ "tsubcctv",	F3(2, 0x23, 0), F3(~2, ~0x23, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "tsubcctv",	F3(2, 0x23, 1), F3(~2, ~0x23, ~1),		"1,i,d", 0, ajit },

{ "unimp",	F2(0x0, 0x0), 0xffc00000, "n", 0, ajit },

/* This *is* a commutative instruction.  */
{ "xnor",	F3(2, 0x07, 0), F3(~2, ~0x07, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "xnor",	F3(2, 0x07, 1), F3(~2, ~0x07, ~1),		"1,i,d", 0, ajit },
{ "xnor",	F3(2, 0x07, 1), F3(~2, ~0x07, ~1),		"i,1,d", 0, ajit },
{ "xnord",	F4(2, 0x07, 0, 1), F4(~2, ~0x07, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */
/* This *is* a commutative instruction.  */
{ "xnorcc",	F3(2, 0x17, 0), F3(~2, ~0x17, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "xnorcc",	F3(2, 0x17, 1), F3(~2, ~0x17, ~1),		"1,i,d", 0, ajit },
{ "xnorcc",	F3(2, 0x17, 1), F3(~2, ~0x17, ~1),		"i,1,d", 0, ajit },
{ "xnordcc",	F4(2, 0x17, 0, 1), F4(~2, ~0x17, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */
{ "xor",	F3(2, 0x03, 0), F3(~2, ~0x03, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "xor",	F3(2, 0x03, 1), F3(~2, ~0x03, ~1),		"1,i,d", 0, ajit },
{ "xor",	F3(2, 0x03, 1), F3(~2, ~0x03, ~1),		"i,1,d", 0, ajit },
{ "xorcc",	F3(2, 0x13, 0), F3(~2, ~0x13, ~0)|ASI(~0),	"1,2,d", 0, ajit },
{ "xorcc",	F3(2, 0x13, 1), F3(~2, ~0x13, ~1),		"1,i,d", 0, ajit },
{ "xorcc",	F3(2, 0x13, 1), F3(~2, ~0x13, ~1),		"i,1,d", 0, ajit },
{ "xordcc",	F4(2, 0x13, 0, 1), F4(~2, ~0x13, ~0, ~1),	"1,2,d", 0, ajit }, /* AJIT */

{ "not",	F3(2, 0x07, 0), F3(~2, ~0x07, ~0)|ASI(~0), "1,d", F_ALIAS, ajit }, /* xnor rs1,%0,rd */
{ "not",	F3(2, 0x07, 0), F3(~2, ~0x07, ~0)|ASI(~0), "r", F_ALIAS, ajit }, /* xnor rd,%0,rd */

{ "btog",	F3(2, 0x03, 0), F3(~2, ~0x03, ~0)|ASI(~0),	"2,r", F_ALIAS, ajit }, /* xor rd,rs2,rd */
{ "btog",	F3(2, 0x03, 1), F3(~2, ~0x03, ~1),		"i,r", F_ALIAS, ajit }, /* xor rd,i,rd */

/* AJIT Additions 2 */
/* SIMD II instructions */
/* AJIT ISA V2: Aug 27, 2020. Changed success on: Sep 27, 2020. */
{ "adddreduce8",  F6(2, 0x2d, 0, 0x0, 0x1), F6(~2, ~0x2d, ~0, ~0x0, ~0x1), "1,2,d", 0, ajit }, /* AJIT */
{ "adddreduce16", F6(2, 0x2d, 0, 0x0, 0x2), F6(~2, ~0x2d, ~0, ~0x0, ~0x2), "1,2,d", 0, ajit }, /* AJIT */
{ "ordreduce8",   F6(2, 0x2e, 0, 0x0, 0x1), F6(~2, ~0x2e, ~0, ~0x0, ~0x1), "1,2,d", 0, ajit }, /* AJIT */
{ "ordreduce16",  F6(2, 0x2e, 0, 0x0, 0x2), F6(~2, ~0x2e, ~0, ~0x0, ~0x2), "1,2,d", 0, ajit }, /* AJIT */
{ "anddreduce8",  F6(2, 0x2f, 0, 0x0, 0x1), F6(~2, ~0x2f, ~0, ~0x0, ~0x1), "1,2,d", 0, ajit }, /* AJIT */
{ "anddreduce16", F6(2, 0x2f, 0, 0x0, 0x2), F6(~2, ~0x2f, ~0, ~0x0, ~0x2), "1,2,d", 0, ajit }, /* AJIT */
{ "xordreduce8",  F6(2, 0x3e, 0, 0x0, 0x1), F6(~2, ~0x3e, ~0, ~0x0, ~0x1), "1,2,d", 0, ajit }, /* AJIT */
{ "xordreduce16", F6(2, 0x3e, 0, 0x0, 0x2), F6(~2, ~0x3e, ~0, ~0x0, ~0x2), "1,2,d", 0, ajit }, /* AJIT */
{ "zbytedpos",    F7(2, 0x3f, 0x0, 0x0),    F7(~2, ~0x3f, ~0x0, ~0x0),     "1,2,d", 0, ajit }, /* AJIT */
{ "zbytedpos",    F7(2, 0x3f, 0x1, 0x0),    F7(~2, ~0x3f, ~0x1, ~0x0),     "1,i,d", 0, ajit }, /* AJIT */
/* End AJIT Additions 2 */

/* FPop1 and FPop2 are not instructions.  Don't accept them.  */

{ "fdtoi",	F3F(2, 0x34, 0x0d2), F3F(~2, ~0x34, ~0x0d2)|RS1_G0, "B,g", F_FLOAT, ajit },
{ "fstoi",	F3F(2, 0x34, 0x0d1), F3F(~2, ~0x34, ~0x0d1)|RS1_G0, "f,g", F_FLOAT, ajit },
{ "fqtoi",	F3F(2, 0x34, 0x0d3), F3F(~2, ~0x34, ~0x0d3)|RS1_G0, "R,g", F_FLOAT, ajit },

{ "fitod",	F3F(2, 0x34, 0x0c8), F3F(~2, ~0x34, ~0x0c8)|RS1_G0, "f,H", F_FLOAT, ajit },
{ "fitos",	F3F(2, 0x34, 0x0c4), F3F(~2, ~0x34, ~0x0c4)|RS1_G0, "f,g", F_FLOAT, ajit },
{ "fitoq",	F3F(2, 0x34, 0x0cc), F3F(~2, ~0x34, ~0x0cc)|RS1_G0, "f,J", F_FLOAT, ajit },

{ "fdtoq",	F3F(2, 0x34, 0x0ce), F3F(~2, ~0x34, ~0x0ce)|RS1_G0, "B,J", F_FLOAT, ajit },
{ "fdtos",	F3F(2, 0x34, 0x0c6), F3F(~2, ~0x34, ~0x0c6)|RS1_G0, "B,g", F_FLOAT, ajit },
{ "fqtod",	F3F(2, 0x34, 0x0cb), F3F(~2, ~0x34, ~0x0cb)|RS1_G0, "R,H", F_FLOAT, ajit },
{ "fqtos",	F3F(2, 0x34, 0x0c7), F3F(~2, ~0x34, ~0x0c7)|RS1_G0, "R,g", F_FLOAT, ajit },
{ "fstod",	F3F(2, 0x34, 0x0c9), F3F(~2, ~0x34, ~0x0c9)|RS1_G0, "f,H", F_FLOAT, ajit },
{ "fstoq",	F3F(2, 0x34, 0x0cd), F3F(~2, ~0x34, ~0x0cd)|RS1_G0, "f,J", F_FLOAT, ajit },

{ "fdivd",	F3F(2, 0x34, 0x04e), F3F(~2, ~0x34, ~0x04e), "v,B,H", F_FLOAT, ajit },
{ "fdivq",	F3F(2, 0x34, 0x04f), F3F(~2, ~0x34, ~0x04f), "V,R,J", F_FLOAT, ajit },
{ "fdivx",	F3F(2, 0x34, 0x04f), F3F(~2, ~0x34, ~0x04f), "V,R,J", F_FLOAT|F_ALIAS, ajit },
{ "fdivs",	F3F(2, 0x34, 0x04d), F3F(~2, ~0x34, ~0x04d), "e,f,g", F_FLOAT, ajit },
{ "fmuld",	F3F(2, 0x34, 0x04a), F3F(~2, ~0x34, ~0x04a), "v,B,H", F_FLOAT, ajit },
{ "fmulq",	F3F(2, 0x34, 0x04b), F3F(~2, ~0x34, ~0x04b), "V,R,J", F_FLOAT, ajit },
{ "fmulx",	F3F(2, 0x34, 0x04b), F3F(~2, ~0x34, ~0x04b), "V,R,J", F_FLOAT|F_ALIAS, ajit },
{ "fmuls",	F3F(2, 0x34, 0x049), F3F(~2, ~0x34, ~0x049), "e,f,g", F_FLOAT, ajit },

{ "fdmulq",	F3F(2, 0x34, 0x06e), F3F(~2, ~0x34, ~0x06e), "v,B,J", F_FLOAT, ajit },
{ "fdmulx",	F3F(2, 0x34, 0x06e), F3F(~2, ~0x34, ~0x06e), "v,B,J", F_FLOAT|F_ALIAS, ajit },
{ "fsmuld",	F3F(2, 0x34, 0x069), F3F(~2, ~0x34, ~0x069), "e,f,H", F_FLOAT|F_FSMULD, ajit },

{ "fsqrtd",	F3F(2, 0x34, 0x02a), F3F(~2, ~0x34, ~0x02a)|RS1_G0, "B,H", F_FLOAT, ajit },
{ "fsqrtq",	F3F(2, 0x34, 0x02b), F3F(~2, ~0x34, ~0x02b)|RS1_G0, "R,J", F_FLOAT, ajit },
{ "fsqrtx",	F3F(2, 0x34, 0x02b), F3F(~2, ~0x34, ~0x02b)|RS1_G0, "R,J", F_FLOAT|F_ALIAS, ajit },
{ "fsqrts",	F3F(2, 0x34, 0x029), F3F(~2, ~0x34, ~0x029)|RS1_G0, "f,g", F_FLOAT, ajit },

{ "fabss",	F3F(2, 0x34, 0x009), F3F(~2, ~0x34, ~0x009)|RS1_G0, "f,g", F_FLOAT, ajit },
{ "fmovs",	F3F(2, 0x34, 0x001), F3F(~2, ~0x34, ~0x001)|RS1_G0, "f,g", F_FLOAT, ajit },
{ "fnegs",	F3F(2, 0x34, 0x005), F3F(~2, ~0x34, ~0x005)|RS1_G0, "f,g", F_FLOAT, ajit },

{ "faddd",	F3F(2, 0x34, 0x042), F3F(~2, ~0x34, ~0x042), "v,B,H", F_FLOAT, ajit },
{ "faddq",	F3F(2, 0x34, 0x043), F3F(~2, ~0x34, ~0x043), "V,R,J", F_FLOAT, ajit },
{ "faddx",	F3F(2, 0x34, 0x043), F3F(~2, ~0x34, ~0x043), "V,R,J", F_FLOAT|F_ALIAS, ajit },
{ "fadds",	F3F(2, 0x34, 0x041), F3F(~2, ~0x34, ~0x041), "e,f,g", F_FLOAT, ajit },
{ "fsubd",	F3F(2, 0x34, 0x046), F3F(~2, ~0x34, ~0x046), "v,B,H", F_FLOAT, ajit },
{ "fsubq",	F3F(2, 0x34, 0x047), F3F(~2, ~0x34, ~0x047), "V,R,J", F_FLOAT, ajit },
{ "fsubx",	F3F(2, 0x34, 0x047), F3F(~2, ~0x34, ~0x047), "V,R,J", F_FLOAT|F_ALIAS, ajit },
{ "fsubs",	F3F(2, 0x34, 0x045), F3F(~2, ~0x34, ~0x045), "e,f,g", F_FLOAT, ajit },

/* AJIT Additions 3 */
/* SIMD Floating point ops */
/* AJIT ISA V2: Aug 27, 2020. Changed success on: Sep 27, 2020. */
{ "vfadd32",      F3F(2, 0x34, 0x142), F3F(~2, ~0x34, ~0x142), "v,B,H", F_FLOAT, ajit }, /* rs1, rs2, rd are even numbered! */ /* AJIT */
{ "vfadd16",      F3F(2, 0x34, 0x143), F3F(~2, ~0x34, ~0x143), "v,B,H", F_FLOAT, ajit }, /* rs1, rs2, rd are even numbered! */ /* AJIT */
{ "vfsub32",      F3F(2, 0x34, 0x144), F3F(~2, ~0x34, ~0x144), "v,B,H", F_FLOAT, ajit }, /* rs1, rs2, rd are even numbered! */ /* AJIT */
{ "vfsub16",      F3F(2, 0x34, 0x145), F3F(~2, ~0x34, ~0x145), "v,B,H", F_FLOAT, ajit }, /* rs1, rs2, rd are even numbered! */ /* AJIT */
{ "vfmul32",      F3F(2, 0x34, 0x146), F3F(~2, ~0x34, ~0x146), "v,B,H", F_FLOAT, ajit }, /* rs1, rs2, rd are even numbered! */ /* AJIT */
{ "vfmul16",      F3F(2, 0x34, 0x147), F3F(~2, ~0x34, ~0x147), "v,B,H", F_FLOAT, ajit }, /* rs1, rs2, rd are even numbered! */ /* AJIT */
/* AJIT ISA V2: Aug 27, 2020. Changed success on: Sep 27, 2020. */
/* AJIT ISA V2: New additions */
{ "vfi16toh",     F3F(2, 0x34, 0x148), F3F(~2, ~0x34, ~0x148), "v,B,H", F_FLOAT, ajit }, /* rs1, rs2, rd are even numbered! */ /* AJIT */
{ "vfhtoi16",     F3F(2, 0x34, 0x149), F3F(~2, ~0x34, ~0x149), "v,B,H", F_FLOAT, ajit }, /* rs1, rs2, rd are even numbered! */ /* AJIT */
{ "faddreduce16", F3F(2, 0x34, 0x150), F3F(~2, ~0x34, ~0x150), "v,g",   F_FLOAT, ajit }, /* AJIT */
{ "fstoh",        F3F(2, 0x34, 0x151), F3F(~2, ~0x34, ~0x151), "e,g",   F_FLOAT, ajit }, /* AJIT */
{ "fhtos",        F3F(2, 0x34, 0x152), F3F(~2, ~0x34, ~0x152), "e,g",   F_FLOAT, ajit }, /* AJIT */
/* End AJIT Additions 3 */


#define CMPFCC(x)	(((x)&0x3)<<25)

{ "fcmpd",	          F3F(2, 0x35, 0x052),            F3F(~2, ~0x35, ~0x052)|RD_G0,  "v,B",   F_FLOAT, ajit },
{ "fcmped",	          F3F(2, 0x35, 0x056),            F3F(~2, ~0x35, ~0x056)|RD_G0,  "v,B",   F_FLOAT, ajit },
{ "fcmpq",	          F3F(2, 0x35, 0x053),            F3F(~2, ~0x35, ~0x053)|RD_G0,	 "V,R", F_FLOAT, ajit },
{ "fcmpeq",	          F3F(2, 0x35, 0x057),            F3F(~2, ~0x35, ~0x057)|RD_G0,	 "V,R", F_FLOAT, ajit },
{ "fcmpx",	          F3F(2, 0x35, 0x053),            F3F(~2, ~0x35, ~0x053)|RD_G0,	 "V,R", F_FLOAT|F_ALIAS, ajit },
{ "fcmpex",	          F3F(2, 0x35, 0x057),            F3F(~2, ~0x35, ~0x057)|RD_G0,	 "V,R", F_FLOAT|F_ALIAS, ajit },
{ "fcmps",	          F3F(2, 0x35, 0x051),            F3F(~2, ~0x35, ~0x051)|RD_G0, "e,f",   F_FLOAT, ajit },
{ "fcmpes",	          F3F(2, 0x35, 0x055),            F3F(~2, ~0x35, ~0x055)|RD_G0, "e,f",   F_FLOAT, ajit },

/* These are marked F_ALIAS, so that they won't conflict with sparclite insns
   present.  Otherwise, the F_ALIAS flag is ignored.  */
{ "cpop1",	F3(2, 0x36, 0), F3(~2, ~0x36, ~1), "[1+2],d", F_ALIAS, ajit },
{ "cpop2",	F3(2, 0x37, 0), F3(~2, ~0x37, ~1), "[1+2],d", F_ALIAS, ajit },

};				/* AMV: End of opcodes table. */

const int ajit_num_opcodes = ((sizeof ajit_opcodes)/(sizeof ajit_opcodes[0]));

#include <string.h>

int   amv_list_ajit_opcodes (void);

int
amv_list_ajit_opcodes (void)
{
  FILE *tmp = fopen ("/tmp/ajit-opcodes.lst", "w");
  /* FILE *tmp = fopen ("/dev/null", "w"); */

  if (tmp != NULL) {
    int i = ajit_num_opcodes;

    /* fprintf (tmp, "%4s | %-14s | %-18s | %-18s | %-10s | %-10s\n", */
    /*               "Num", "Name", "Match", "Lose", "Flags", "Flags"); */

    /* for (i = 0; i < ajit_num_opcodes; i++) { */
    /*            /\* "%04d | %-11s | 0x%lX | 0x%lX | %-10s | 0x%X | 0x%X | 0x%lX | %-10s\n", *\/ */
    /*   fprintf (tmp,  */
    /*            "%04d | %-14s | 0x%016lX | 0x%016lX | 0x%08X | %d\n", */
    /*            i, */
    /*            ajit_opcodes[i].name, */
    /*            ajit_opcodes[i].match, */
    /*            ajit_opcodes[i].lose, */
    /*            ajit_opcodes[i].flags, */
    /*            ajit_opcodes[i].flags */
    /*            ); */
    /* } */

    fprintf (tmp, "%4s | %-14s | %-18s | %-18s | %-10s | %-10s | %-10s | %-10s | %-10s\n",
          "Num", "Name", "Match", "Lose", "Args", "Flags", "Arch", "M&L", "Status");

    for (i = 0; i < ajit_num_opcodes; i++) {
            /* "%04d | %-14s | 0x%lX | 0x%lX | %-10s | 0x%X | 0x%X | 0x%lX | %-10s\n", */
      fprintf (tmp,
            "%04d | %-14s | 0x%016lX | 0x%016lX | %-10s | 0x%08X | 0x%08X | 0x%08lX | %-10s\n",
            i,
            ajit_opcodes[i].name,
            ajit_opcodes[i].match,
            ajit_opcodes[i].lose,
            ajit_opcodes[i].args,
            ajit_opcodes[i].flags,
            ajit_opcodes[i].architecture,
            (ajit_opcodes[i].match & ajit_opcodes[i].lose),
            ((ajit_opcodes[i].match & ajit_opcodes[i].lose) == 0x0) ? "Ok" : "NOT Ok"
            );
    }

    fclose (tmp);
  }

  return 0;
}


/* Utilities for argument parsing.  */

typedef struct
{
  int value;
  const char *name;
} arg;

/* Look up NAME in TABLE.  */

static int
lookup_name (const arg *table, const char *name)
{
  const arg *p;

  for (p = table; p->name; ++p)
    if (strcmp (name, p->name) == 0)
      return p->value;

  return -1;
}

/* Look up VALUE in TABLE.  */

static const char *
lookup_value (const arg *table, int value)
{
  const arg *p;

  for (p = table; p->name; ++p)
    if (value == p->value)
      return p->name;

  return NULL;
}

/* Handle ASI's.  */

static arg asi_table[] =
{
  /* These are in the v9 architecture manual.  */
  /* The shorter versions appear first, they're here because Sun's as has them.
     Sun's as uses #ASI_P_L instead of #ASI_PL (which appears in the
     UltraAJIT architecture manual).  */
  { 0x04, "#ASI_N" },
  { 0x0c, "#ASI_N_L" },
  { 0x10, "#ASI_AIUP" },
  { 0x11, "#ASI_AIUS" },
  { 0x18, "#ASI_AIUP_L" },
  { 0x19, "#ASI_AIUS_L" },
  { 0x80, "#ASI_P" },
  { 0x81, "#ASI_S" },
  { 0x82, "#ASI_PNF" },
  { 0x83, "#ASI_SNF" },
  { 0x88, "#ASI_P_L" },
  { 0x89, "#ASI_S_L" },
  { 0x8a, "#ASI_PNF_L" },
  { 0x8b, "#ASI_SNF_L" },
  { 0x04, "#ASI_NUCLEUS" },
  { 0x0c, "#ASI_NUCLEUS_LITTLE" },
  { 0x10, "#ASI_AS_IF_USER_PRIMARY" },
  { 0x11, "#ASI_AS_IF_USER_SECONDARY" },
  { 0x18, "#ASI_AS_IF_USER_PRIMARY_LITTLE" },
  { 0x19, "#ASI_AS_IF_USER_SECONDARY_LITTLE" },
  { 0x80, "#ASI_PRIMARY" },
  { 0x81, "#ASI_SECONDARY" },
  { 0x82, "#ASI_PRIMARY_NOFAULT" },
  { 0x83, "#ASI_SECONDARY_NOFAULT" },
  { 0x88, "#ASI_PRIMARY_LITTLE" },
  { 0x89, "#ASI_SECONDARY_LITTLE" },
  { 0x8a, "#ASI_PRIMARY_NOFAULT_LITTLE" },
  { 0x8b, "#ASI_SECONDARY_NOFAULT_LITTLE" },
  /* These are UltraAJIT and Niagara extensions.  */
  { 0x14, "#ASI_PHYS_USE_EC" },
  { 0x15, "#ASI_PHYS_BYPASS_EC_E" },
  { 0x16, "#ASI_BLK_AIUP_4V" },
  { 0x17, "#ASI_BLK_AIUS_4V" },
  { 0x1c, "#ASI_PHYS_USE_EC_L" },
  { 0x1d, "#ASI_PHYS_BYPASS_EC_E_L" },
  { 0x1e, "#ASI_BLK_AIUP_L_4V" },
  { 0x1f, "#ASI_BLK_AIUS_L_4V" },
  { 0x20, "#ASI_SCRATCHPAD" },
  { 0x21, "#ASI_MMU" },
  { 0x23, "#ASI_BLK_INIT_QUAD_LDD_AIUS" },
  { 0x24, "#ASI_NUCLEUS_QUAD_LDD" },
  { 0x25, "#ASI_QUEUE" },
  { 0x26, "#ASI_QUAD_LDD_PHYS_4V" },
  { 0x2c, "#ASI_NUCLEUS_QUAD_LDD_L" },
  { 0x30, "#ASI_PCACHE_DATA_STATUS" },
  { 0x31, "#ASI_PCACHE_DATA" },
  { 0x32, "#ASI_PCACHE_TAG" },
  { 0x33, "#ASI_PCACHE_SNOOP_TAG" },
  { 0x34, "#ASI_QUAD_LDD_PHYS" },
  { 0x38, "#ASI_WCACHE_VALID_BITS" },
  { 0x39, "#ASI_WCACHE_DATA" },
  { 0x3a, "#ASI_WCACHE_TAG" },
  { 0x3b, "#ASI_WCACHE_SNOOP_TAG" },
  { 0x3c, "#ASI_QUAD_LDD_PHYS_L" },
  { 0x40, "#ASI_SRAM_FAST_INIT" },
  { 0x41, "#ASI_CORE_AVAILABLE" },
  { 0x41, "#ASI_CORE_ENABLE_STAT" },
  { 0x41, "#ASI_CORE_ENABLE" },
  { 0x41, "#ASI_XIR_STEERING" },
  { 0x41, "#ASI_CORE_RUNNING_RW" },
  { 0x41, "#ASI_CORE_RUNNING_W1S" },
  { 0x41, "#ASI_CORE_RUNNING_W1C" },
  { 0x41, "#ASI_CORE_RUNNING_STAT" },
  { 0x41, "#ASI_CMT_ERROR_STEERING" },
  { 0x41, "#ASI_DCACHE_INVALIDATE" },
  { 0x41, "#ASI_DCACHE_UTAG" },
  { 0x41, "#ASI_DCACHE_SNOOP_TAG" },
  { 0x42, "#ASI_DCACHE_INVALIDATE" },
  { 0x43, "#ASI_DCACHE_UTAG" },
  { 0x44, "#ASI_DCACHE_SNOOP_TAG" },
  { 0x45, "#ASI_LSU_CONTROL_REG" },
  { 0x45, "#ASI_DCU_CONTROL_REG" },
  { 0x46, "#ASI_DCACHE_DATA" },
  { 0x47, "#ASI_DCACHE_TAG" },
  { 0x48, "#ASI_INTR_DISPATCH_STAT" },
  { 0x49, "#ASI_INTR_RECEIVE" },
  { 0x4a, "#ASI_UPA_CONFIG" },
  { 0x4a, "#ASI_JBUS_CONFIG" },
  { 0x4a, "#ASI_SAFARI_CONFIG" },
  { 0x4a, "#ASI_SAFARI_ADDRESS" },
  { 0x4b, "#ASI_ESTATE_ERROR_EN" },
  { 0x4c, "#ASI_AFSR" },
  { 0x4d, "#ASI_AFAR" },
  { 0x4e, "#ASI_EC_TAG_DATA" },
  { 0x50, "#ASI_IMMU" },
  { 0x51, "#ASI_IMMU_TSB_8KB_PTR" },
  { 0x52, "#ASI_IMMU_TSB_16KB_PTR" },
  { 0x54, "#ASI_ITLB_DATA_IN" },
  { 0x55, "#ASI_ITLB_DATA_ACCESS" },
  { 0x56, "#ASI_ITLB_TAG_READ" },
  { 0x57, "#ASI_IMMU_DEMAP" },
  { 0x58, "#ASI_DMMU" },
  { 0x59, "#ASI_DMMU_TSB_8KB_PTR" },
  { 0x5a, "#ASI_DMMU_TSB_64KB_PTR" },
  { 0x5b, "#ASI_DMMU_TSB_DIRECT_PTR" },
  { 0x5c, "#ASI_DTLB_DATA_IN" },
  { 0x5d, "#ASI_DTLB_DATA_ACCESS" },
  { 0x5e, "#ASI_DTLB_TAG_READ" },
  { 0x5f, "#ASI_DMMU_DEMAP" },
  { 0x60, "#ASI_IIU_INST_TRAP" },
  { 0x63, "#ASI_INTR_ID" },
  { 0x63, "#ASI_CORE_ID" },
  { 0x63, "#ASI_CESR_ID" },
  { 0x66, "#ASI_IC_INSTR" },
  { 0x67, "#ASI_IC_TAG" },
  { 0x68, "#ASI_IC_STAG" },
  { 0x6e, "#ASI_IC_PRE_DECODE" },
  { 0x6f, "#ASI_IC_NEXT_FIELD" },
  { 0x6f, "#ASI_BRPRED_ARRAY" },
  { 0x70, "#ASI_BLK_AIUP" },
  { 0x71, "#ASI_BLK_AIUS" },
  { 0x72, "#ASI_MCU_CTRL_REG" },
  { 0x74, "#ASI_EC_DATA" },
  { 0x75, "#ASI_EC_CTRL" },
  { 0x76, "#ASI_EC_W" },
  { 0x77, "#ASI_UDB_ERROR_W" },
  { 0x77, "#ASI_UDB_CONTROL_W" },
  { 0x77, "#ASI_INTR_W" },
  { 0x77, "#ASI_INTR_DATAN_W" },
  { 0x77, "#ASI_INTR_DISPATCH_W" },
  { 0x78, "#ASI_BLK_AIUPL" },
  { 0x79, "#ASI_BLK_AIUSL" },
  { 0x7e, "#ASI_EC_R" },
  { 0x7f, "#ASI_UDBH_ERROR_R" },
  { 0x7f, "#ASI_UDBL_ERROR_R" },
  { 0x7f, "#ASI_UDBH_CONTROL_R" },
  { 0x7f, "#ASI_UDBL_CONTROL_R" },
  { 0x7f, "#ASI_INTR_R" },
  { 0x7f, "#ASI_INTR_DATAN_R" },
  { 0xc0, "#ASI_PST8_P" },
  { 0xc1, "#ASI_PST8_S" },
  { 0xc2, "#ASI_PST16_P" },
  { 0xc3, "#ASI_PST16_S" },
  { 0xc4, "#ASI_PST32_P" },
  { 0xc5, "#ASI_PST32_S" },
  { 0xc8, "#ASI_PST8_PL" },
  { 0xc9, "#ASI_PST8_SL" },
  { 0xca, "#ASI_PST16_PL" },
  { 0xcb, "#ASI_PST16_SL" },
  { 0xcc, "#ASI_PST32_PL" },
  { 0xcd, "#ASI_PST32_SL" },
  { 0xd0, "#ASI_FL8_P" },
  { 0xd1, "#ASI_FL8_S" },
  { 0xd2, "#ASI_FL16_P" },
  { 0xd3, "#ASI_FL16_S" },
  { 0xd8, "#ASI_FL8_PL" },
  { 0xd9, "#ASI_FL8_SL" },
  { 0xda, "#ASI_FL16_PL" },
  { 0xdb, "#ASI_FL16_SL" },
  { 0xe0, "#ASI_BLK_COMMIT_P", },
  { 0xe1, "#ASI_BLK_COMMIT_S", },
  { 0xe2, "#ASI_BLK_INIT_QUAD_LDD_P" },
  { 0xf0, "#ASI_BLK_P", },
  { 0xf1, "#ASI_BLK_S", },
  { 0xf8, "#ASI_BLK_PL", },
  { 0xf9, "#ASI_BLK_SL", },
  { 0, 0 }
};

/* Return the value for ASI NAME, or -1 if not found.  */

int
ajit_encode_asi (const char *name)
{
  return lookup_name (asi_table, name);
}

/* Return the name for ASI value VALUE or NULL if not found.  */

const char *
ajit_decode_asi (int value)
{
  return lookup_value (asi_table, value);
}

/* Handle membar masks.  */

static arg membar_table[] =
{
  { 0x40, "#Sync" },
  { 0x20, "#MemIssue" },
  { 0x10, "#Lookaside" },
  { 0x08, "#StoreStore" },
  { 0x04, "#LoadStore" },
  { 0x02, "#StoreLoad" },
  { 0x01, "#LoadLoad" },
  { 0, 0 }
};

/* Return the value for membar arg NAME, or -1 if not found.  */

int
ajit_encode_membar (const char *name)
{
  return lookup_name (membar_table, name);
}

/* Return the name for membar value VALUE or NULL if not found.  */

const char *
ajit_decode_membar (int value)
{
  return lookup_value (membar_table, value);
}

/* Handle prefetch args.  */

static arg prefetch_table[] =
{
  { 0, "#n_reads" },
  { 1, "#one_read" },
  { 2, "#n_writes" },
  { 3, "#one_write" },
  { 4, "#page" },
  { 16, "#invalidate" },
  { 17, "#unified", },
  { 20, "#n_reads_strong", },
  { 21, "#one_read_strong", },
  { 22, "#n_writes_strong", },
  { 23, "#one_write_strong", },
  { 0, 0 }
};

/* Return the value for prefetch arg NAME, or -1 if not found.  */

int
ajit_encode_prefetch (const char *name)
{
  return lookup_name (prefetch_table, name);
}

/* Return the name for prefetch value VALUE or NULL if not found.  */

const char *
ajit_decode_prefetch (int value)
{
  return lookup_value (prefetch_table, value);
}

/* Handle ajitlet coprocessor registers.  */

static arg ajitlet_cpreg_table[] =
{
  { 0, "%ccsr" },
  { 1, "%ccfr" },
  { 2, "%cccrcr" },
  { 3, "%ccpr" },
  { 4, "%ccsr2" },
  { 5, "%cccrr" },
  { 6, "%ccrstr" },
  { 0, 0 }
};

/* Return the value for ajitlet cpreg arg NAME, or -1 if not found.  */

int
ajit_encode_ajitlet_cpreg (const char *name)
{
  return lookup_name (ajitlet_cpreg_table, name);
}

/* Return the name for ajitlet cpreg value VALUE or NULL if not found.  */

const char *
ajit_decode_ajitlet_cpreg (int value)
{
  return lookup_value (ajitlet_cpreg_table, value);
}
