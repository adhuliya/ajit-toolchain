/* AJIT ELF support for BFD.
   Copyright 1996, 1997, 1998, 1999, 2000, 2001, 2003, 2008, 2010,
   2011
   Free Software Foundation, Inc.
   By Doug Evans, Cygnus Support, <dje@cygnus.com>.

   This file is part of BFD, the Binary File Descriptor library.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#ifndef _ELF_AJIT_H
#define _ELF_AJIT_H

/* Processor specific flags for the ELF header e_flags field.  */

/* These are defined by Sun.  */

#define EF_AJIT_32PLUS_MASK	0xffff00	/* bits indicating V8+ type */
#define EF_AJIT_32PLUS		0x000100	/* generic V8+ features */
#define EF_AJIT_SUN_US1	0x000200	/* Sun UltraAJIT1 extensions */
#define EF_AJIT_HAL_R1		0x000400	/* HAL R1 extensions */
#define EF_AJIT_SUN_US3	0x000800	/* Sun UltraAJITIII extensions */

#define EF_AJIT_LEDATA         0x800000	/* little endian data */

/* This name is used in the V9 ABI.  */
#define EF_AJIT_EXT_MASK	0xffff00	/* reserved for vendor extensions */

/* V9 memory models */
#define EF_AJITV9_MM		0x3		/* memory model mask */
#define EF_AJITV9_TSO		0x0		/* total store ordering */
#define EF_AJITV9_PSO		0x1		/* partial store ordering */
#define EF_AJITV9_RMO		0x2		/* relaxed store ordering */

/* Section indices.  */

#define SHN_BEFORE	SHN_LORESERVE		/* Used with SHF_ORDERED and...  */
#define SHN_AFTER	(SHN_LORESERVE + 1)	/* SHF_LINK_ORDER section flags. */

/* Section flags.  */

#define SHF_ORDERED		0x40000000	/* treat sh_link,sh_info specially */

/* Symbol types.  */

#define STT_REGISTER		13		/* global reg reserved to app. */

#include "elf/reloc-macros.h"

/* Relocation types.  */
START_RELOC_NUMBERS (elf_ajit_reloc_type)
  RELOC_NUMBER (R_AJIT_NONE, 0)
  RELOC_NUMBER (R_AJIT_8, 1)
  RELOC_NUMBER (R_AJIT_16, 2)
  RELOC_NUMBER (R_AJIT_32, 3)
  RELOC_NUMBER (R_AJIT_DISP8, 4)
  RELOC_NUMBER (R_AJIT_DISP16, 5)
  RELOC_NUMBER (R_AJIT_DISP32, 6)
  RELOC_NUMBER (R_AJIT_WDISP30, 7)
  RELOC_NUMBER (R_AJIT_WDISP22, 8)
  RELOC_NUMBER (R_AJIT_HI22, 9)
  RELOC_NUMBER (R_AJIT_22, 10)
  RELOC_NUMBER (R_AJIT_13, 11)
  RELOC_NUMBER (R_AJIT_LO10, 12)
  RELOC_NUMBER (R_AJIT_GOT10, 13)
  RELOC_NUMBER (R_AJIT_GOT13, 14)
  RELOC_NUMBER (R_AJIT_GOT22, 15)
  RELOC_NUMBER (R_AJIT_PC10, 16)
  RELOC_NUMBER (R_AJIT_PC22, 17)
  RELOC_NUMBER (R_AJIT_WPLT30, 18)
  RELOC_NUMBER (R_AJIT_COPY, 19)
  RELOC_NUMBER (R_AJIT_GLOB_DAT, 20)
  RELOC_NUMBER (R_AJIT_JMP_SLOT, 21)
  RELOC_NUMBER (R_AJIT_RELATIVE, 22)
  RELOC_NUMBER (R_AJIT_UA32, 23)

  /* ??? These 6 relocs are new but not currently used.  For binary
     compatibility in the ajit64-elf toolchain, we leave them out.
     A non-binary upward compatible change is expected for ajit64-elf.  */
#ifndef AJIT64_OLD_RELOCS
  /* ??? New relocs on the UltraAJIT.  Not sure what they're for yet.  */
  RELOC_NUMBER (R_AJIT_PLT32, 24)
  RELOC_NUMBER (R_AJIT_HIPLT22, 25)
  RELOC_NUMBER (R_AJIT_LOPLT10, 26)
  RELOC_NUMBER (R_AJIT_PCPLT32, 27)
  RELOC_NUMBER (R_AJIT_PCPLT22, 28)
  RELOC_NUMBER (R_AJIT_PCPLT10, 29)
#endif

  /* v9 relocs */
  RELOC_NUMBER (R_AJIT_10, 30)
  RELOC_NUMBER (R_AJIT_11, 31)
  RELOC_NUMBER (R_AJIT_64, 32)
  RELOC_NUMBER (R_AJIT_OLO10, 33)
  RELOC_NUMBER (R_AJIT_HH22, 34)
  RELOC_NUMBER (R_AJIT_HM10, 35)
  RELOC_NUMBER (R_AJIT_LM22, 36)
  RELOC_NUMBER (R_AJIT_PC_HH22, 37)
  RELOC_NUMBER (R_AJIT_PC_HM10, 38)
  RELOC_NUMBER (R_AJIT_PC_LM22, 39)
  RELOC_NUMBER (R_AJIT_WDISP16, 40)
  RELOC_NUMBER (R_AJIT_WDISP19, 41)
  RELOC_NUMBER (R_AJIT_UNUSED_42, 42)
  RELOC_NUMBER (R_AJIT_7, 43)
  RELOC_NUMBER (R_AJIT_5, 44)
  RELOC_NUMBER (R_AJIT_6, 45)
  RELOC_NUMBER (R_AJIT_DISP64, 46)
  RELOC_NUMBER (R_AJIT_PLT64, 47)
  RELOC_NUMBER (R_AJIT_HIX22, 48)
  RELOC_NUMBER (R_AJIT_LOX10, 49)
  RELOC_NUMBER (R_AJIT_H44, 50)
  RELOC_NUMBER (R_AJIT_M44, 51)
  RELOC_NUMBER (R_AJIT_L44, 52)
  RELOC_NUMBER (R_AJIT_REGISTER, 53)
  RELOC_NUMBER (R_AJIT_UA64, 54)
  RELOC_NUMBER (R_AJIT_UA16, 55)

  RELOC_NUMBER (R_AJIT_TLS_GD_HI22, 56)
  RELOC_NUMBER (R_AJIT_TLS_GD_LO10, 57)
  RELOC_NUMBER (R_AJIT_TLS_GD_ADD, 58)
  RELOC_NUMBER (R_AJIT_TLS_GD_CALL, 59)
  RELOC_NUMBER (R_AJIT_TLS_LDM_HI22, 60)
  RELOC_NUMBER (R_AJIT_TLS_LDM_LO10, 61)
  RELOC_NUMBER (R_AJIT_TLS_LDM_ADD, 62)
  RELOC_NUMBER (R_AJIT_TLS_LDM_CALL, 63)
  RELOC_NUMBER (R_AJIT_TLS_LDO_HIX22, 64)
  RELOC_NUMBER (R_AJIT_TLS_LDO_LOX10, 65)
  RELOC_NUMBER (R_AJIT_TLS_LDO_ADD, 66)
  RELOC_NUMBER (R_AJIT_TLS_IE_HI22, 67)
  RELOC_NUMBER (R_AJIT_TLS_IE_LO10, 68)
  RELOC_NUMBER (R_AJIT_TLS_IE_LD, 69)
  RELOC_NUMBER (R_AJIT_TLS_IE_LDX, 70)
  RELOC_NUMBER (R_AJIT_TLS_IE_ADD, 71)
  RELOC_NUMBER (R_AJIT_TLS_LE_HIX22, 72)
  RELOC_NUMBER (R_AJIT_TLS_LE_LOX10, 73)
  RELOC_NUMBER (R_AJIT_TLS_DTPMOD32, 74)
  RELOC_NUMBER (R_AJIT_TLS_DTPMOD64, 75)
  RELOC_NUMBER (R_AJIT_TLS_DTPOFF32, 76)
  RELOC_NUMBER (R_AJIT_TLS_DTPOFF64, 77)
  RELOC_NUMBER (R_AJIT_TLS_TPOFF32, 78)
  RELOC_NUMBER (R_AJIT_TLS_TPOFF64, 79)

  RELOC_NUMBER (R_AJIT_GOTDATA_HIX22, 80)
  RELOC_NUMBER (R_AJIT_GOTDATA_LOX10, 81)
  RELOC_NUMBER (R_AJIT_GOTDATA_OP_HIX22, 82)
  RELOC_NUMBER (R_AJIT_GOTDATA_OP_LOX10, 83)
  RELOC_NUMBER (R_AJIT_GOTDATA_OP, 84)

  RELOC_NUMBER (R_AJIT_H34, 85)
  RELOC_NUMBER (R_AJIT_SIZE32, 86)
  RELOC_NUMBER (R_AJIT_SIZE64, 87)
  
  EMPTY_RELOC  (R_AJIT_max_std)

  RELOC_NUMBER (R_AJIT_JMP_IREL, 248)
  RELOC_NUMBER (R_AJIT_IRELATIVE, 249)
  RELOC_NUMBER (R_AJIT_GNU_VTINHERIT, 250)
  RELOC_NUMBER (R_AJIT_GNU_VTENTRY, 251)
  RELOC_NUMBER (R_AJIT_REV32, 252)

END_RELOC_NUMBERS (R_AJIT_max)

/* Relocation macros.  */

#define ELF64_R_TYPE_DATA(info) \
  (((bfd_signed_vma)(ELF64_R_TYPE(info) >> 8) ^ 0x800000) - 0x800000)
#define ELF64_R_TYPE_ID(info) \
  ((info) & 0xff)
#define ELF64_R_TYPE_INFO(data, type) \
  (((bfd_vma) ((data) & 0xffffff) << 8) | (bfd_vma) (type))

/* Values for Elf64_Dyn.d_tag.  */

#define DT_AJIT_REGISTER	0x70000001

/* Object attribute tags.  */
enum
{
  /* 0-3 are generic.  */
  Tag_GNU_Ajit_HWCAPS = 4,
};

/* These values match the AV_AJIT_* hwcap bits defined under Solaris.  */
#define ELF_AJIT_HWCAP_MUL32	0x00000001 /* umul/umulcc/smul/smulcc insns */
#define ELF_AJIT_HWCAP_DIV32	0x00000002 /* udiv/udivcc/sdiv/sdivcc insns */
#define ELF_AJIT_HWCAP_FSMULD	0x00000004 /* 'fsmuld' insn */
#define ELF_AJIT_HWCAP_V8PLUS	0x00000008 /* v9 insns available to 32bit */
#define ELF_AJIT_HWCAP_POPC	0x00000010 /* 'popc' insn */
#define ELF_AJIT_HWCAP_VIS	0x00000020 /* VIS insns */
#define ELF_AJIT_HWCAP_VIS2	0x00000040 /* VIS2 insns */
#define ELF_AJIT_HWCAP_ASI_BLK_INIT	\
				0x00000080 /* block init ASIs */
#define ELF_AJIT_HWCAP_FMAF	0x00000100 /* fused multiply-add */
#define ELF_AJIT_HWCAP_VIS3	0x00000400 /* VIS3 insns */
#define ELF_AJIT_HWCAP_HPC	0x00000800 /* HPC insns */
#define ELF_AJIT_HWCAP_RANDOM	0x00001000 /* 'random' insn */
#define ELF_AJIT_HWCAP_TRANS	0x00002000 /* transaction insns */
#define ELF_AJIT_HWCAP_FJFMAU	0x00004000 /* unfused multiply-add */
#define ELF_AJIT_HWCAP_IMA	0x00008000 /* integer multiply-add */
#define ELF_AJIT_HWCAP_ASI_CACHE_SPARING \
				0x00010000 /* cache sparing ASIs */

#endif /* _ELF_AJIT_H */
