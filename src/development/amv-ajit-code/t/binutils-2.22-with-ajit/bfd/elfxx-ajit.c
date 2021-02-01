/* AJIT-specific support for ELF
   Copyright 2005, 2006, 2007, 2008, 2009, 2010, 2011
   Free Software Foundation, Inc.

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


/* This file handles functionality common to the different AJIT ABI's.  */

#include "sysdep.h"
#include "bfd.h"
#include "bfdlink.h"
#include "libbfd.h"
#include "libiberty.h"
#include "elf-bfd.h"
#include "elf/ajit.h"
#include "opcode/ajit.h"
#include "elfxx-ajit.h"
#include "elf-vxworks.h"
#include "objalloc.h"
#include "hashtab.h"

/* In case we're on a 32-bit machine, construct a 64-bit "-1" value.  */
#define MINUS_ONE (~ (bfd_vma) 0)

#define ABI_64_P(abfd) \
  (get_elf_backend_data (abfd)->s->elfclass == ELFCLASS64)

/* The relocation "howto" table.  */

/* Utility for performing the standard initial work of an instruction
   relocation.
   *PRELOCATION will contain the relocated item.
   *PINSN will contain the instruction from the input stream.
   If the result is `bfd_reloc_other' the caller can continue with
   performing the relocation.  Otherwise it must stop and return the
   value to its caller.  */

static bfd_reloc_status_type
init_insn_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
		 PTR data, asection *input_section, bfd *output_bfd,
		 bfd_vma *prelocation, bfd_vma *pinsn)
{
  bfd_vma relocation;
  reloc_howto_type *howto = reloc_entry->howto;

  if (output_bfd != (bfd *) NULL
      && (symbol->flags & BSF_SECTION_SYM) == 0
      && (! howto->partial_inplace
	  || reloc_entry->addend == 0))
    {
      reloc_entry->address += input_section->output_offset;
      return bfd_reloc_ok;
    }

  /* This works because partial_inplace is FALSE.  */
  if (output_bfd != NULL)
    return bfd_reloc_continue;

  if (reloc_entry->address > bfd_get_section_limit (abfd, input_section))
    return bfd_reloc_outofrange;

  relocation = (symbol->value
		+ symbol->section->output_section->vma
		+ symbol->section->output_offset);
  relocation += reloc_entry->addend;
  if (howto->pc_relative)
    {
      relocation -= (input_section->output_section->vma
		     + input_section->output_offset);
      relocation -= reloc_entry->address;
    }

  *prelocation = relocation;
  *pinsn = bfd_get_32 (abfd, (bfd_byte *) data + reloc_entry->address);
  return bfd_reloc_other;
}

/* For unsupported relocs.  */

static bfd_reloc_status_type
ajit_elf_notsup_reloc (bfd *abfd ATTRIBUTE_UNUSED,
			arelent *reloc_entry ATTRIBUTE_UNUSED,
			asymbol *symbol ATTRIBUTE_UNUSED,
			PTR data ATTRIBUTE_UNUSED,
			asection *input_section ATTRIBUTE_UNUSED,
			bfd *output_bfd ATTRIBUTE_UNUSED,
			char **error_message ATTRIBUTE_UNUSED)
{
  return bfd_reloc_notsupported;
}

/* Handle the WDISP16 reloc.  */

static bfd_reloc_status_type
ajit_elf_wdisp16_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
			 PTR data, asection *input_section, bfd *output_bfd,
			 char **error_message ATTRIBUTE_UNUSED)
{
  bfd_vma relocation;
  bfd_vma insn;
  bfd_reloc_status_type status;

  status = init_insn_reloc (abfd, reloc_entry, symbol, data,
			    input_section, output_bfd, &relocation, &insn);
  if (status != bfd_reloc_other)
    return status;

  insn &= ~ (bfd_vma) 0x303fff;
  insn |= (((relocation >> 2) & 0xc000) << 6) | ((relocation >> 2) & 0x3fff);
  bfd_put_32 (abfd, insn, (bfd_byte *) data + reloc_entry->address);

  if ((bfd_signed_vma) relocation < - 0x40000
      || (bfd_signed_vma) relocation > 0x3ffff)
    return bfd_reloc_overflow;
  else
    return bfd_reloc_ok;
}

/* Handle the HIX22 reloc.  */

static bfd_reloc_status_type
ajit_elf_hix22_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
		       PTR data, asection *input_section, bfd *output_bfd,
		       char **error_message ATTRIBUTE_UNUSED)
{
  bfd_vma relocation;
  bfd_vma insn;
  bfd_reloc_status_type status;

  status = init_insn_reloc (abfd, reloc_entry, symbol, data,
			    input_section, output_bfd, &relocation, &insn);
  if (status != bfd_reloc_other)
    return status;

  relocation ^= MINUS_ONE;
  insn = (insn &~ (bfd_vma) 0x3fffff) | ((relocation >> 10) & 0x3fffff);
  bfd_put_32 (abfd, insn, (bfd_byte *) data + reloc_entry->address);

  if ((relocation & ~ (bfd_vma) 0xffffffff) != 0)
    return bfd_reloc_overflow;
  else
    return bfd_reloc_ok;
}

/* Handle the LOX10 reloc.  */

static bfd_reloc_status_type
ajit_elf_lox10_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
		       PTR data, asection *input_section, bfd *output_bfd,
		       char **error_message ATTRIBUTE_UNUSED)
{
  bfd_vma relocation;
  bfd_vma insn;
  bfd_reloc_status_type status;

  status = init_insn_reloc (abfd, reloc_entry, symbol, data,
			    input_section, output_bfd, &relocation, &insn);
  if (status != bfd_reloc_other)
    return status;

  insn = (insn &~ (bfd_vma) 0x1fff) | 0x1c00 | (relocation & 0x3ff);
  bfd_put_32 (abfd, insn, (bfd_byte *) data + reloc_entry->address);

  return bfd_reloc_ok;
}

static reloc_howto_type _bfd_ajit_elf_howto_table[] =
{
  HOWTO(R_AJIT_NONE,      0,0, 0,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_NONE",    FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_8,         0,0, 8,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_8",       FALSE,0,0x000000ff,TRUE),
  HOWTO(R_AJIT_16,        0,1,16,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_16",      FALSE,0,0x0000ffff,TRUE),
  HOWTO(R_AJIT_32,        0,2,32,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_32",      FALSE,0,0xffffffff,TRUE),
  HOWTO(R_AJIT_DISP8,     0,0, 8,TRUE, 0,complain_overflow_signed,  bfd_elf_generic_reloc,  "R_AJIT_DISP8",   FALSE,0,0x000000ff,TRUE),
  HOWTO(R_AJIT_DISP16,    0,1,16,TRUE, 0,complain_overflow_signed,  bfd_elf_generic_reloc,  "R_AJIT_DISP16",  FALSE,0,0x0000ffff,TRUE),
  HOWTO(R_AJIT_DISP32,    0,2,32,TRUE, 0,complain_overflow_signed,  bfd_elf_generic_reloc,  "R_AJIT_DISP32",  FALSE,0,0xffffffff,TRUE),
  HOWTO(R_AJIT_WDISP30,   2,2,30,TRUE, 0,complain_overflow_signed,  bfd_elf_generic_reloc,  "R_AJIT_WDISP30", FALSE,0,0x3fffffff,TRUE),
  HOWTO(R_AJIT_WDISP22,   2,2,22,TRUE, 0,complain_overflow_signed,  bfd_elf_generic_reloc,  "R_AJIT_WDISP22", FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_HI22,     10,2,22,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_HI22",    FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_22,        0,2,22,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_22",      FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_13,        0,2,13,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_13",      FALSE,0,0x00001fff,TRUE),
  HOWTO(R_AJIT_LO10,      0,2,10,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_LO10",    FALSE,0,0x000003ff,TRUE),
  HOWTO(R_AJIT_GOT10,     0,2,10,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_GOT10",   FALSE,0,0x000003ff,TRUE),
  HOWTO(R_AJIT_GOT13,     0,2,13,FALSE,0,complain_overflow_signed,  bfd_elf_generic_reloc,  "R_AJIT_GOT13",   FALSE,0,0x00001fff,TRUE),
  HOWTO(R_AJIT_GOT22,    10,2,22,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_GOT22",   FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_PC10,      0,2,10,TRUE, 0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_PC10",    FALSE,0,0x000003ff,TRUE),
  HOWTO(R_AJIT_PC22,     10,2,22,TRUE, 0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_PC22",    FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_WPLT30,    2,2,30,TRUE, 0,complain_overflow_signed,  bfd_elf_generic_reloc,  "R_AJIT_WPLT30",  FALSE,0,0x3fffffff,TRUE),
  HOWTO(R_AJIT_COPY,      0,0,00,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_COPY",    FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_GLOB_DAT,  0,0,00,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_GLOB_DAT",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_JMP_SLOT,  0,0,00,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_JMP_SLOT",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_RELATIVE,  0,0,00,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_RELATIVE",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_UA32,      0,2,32,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_UA32",    FALSE,0,0xffffffff,TRUE),
  HOWTO(R_AJIT_PLT32,     0,2,32,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_PLT32",   FALSE,0,0xffffffff,TRUE),
  HOWTO(R_AJIT_HIPLT22,   0,0,00,FALSE,0,complain_overflow_dont,    ajit_elf_notsup_reloc, "R_AJIT_HIPLT22",  FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_LOPLT10,   0,0,00,FALSE,0,complain_overflow_dont,    ajit_elf_notsup_reloc, "R_AJIT_LOPLT10",  FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_PCPLT32,   0,0,00,FALSE,0,complain_overflow_dont,    ajit_elf_notsup_reloc, "R_AJIT_PCPLT32",  FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_PCPLT22,   0,0,00,FALSE,0,complain_overflow_dont,    ajit_elf_notsup_reloc, "R_AJIT_PCPLT22",  FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_PCPLT10,   0,0,00,FALSE,0,complain_overflow_dont,    ajit_elf_notsup_reloc, "R_AJIT_PCPLT10",  FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_10,        0,2,10,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_10",      FALSE,0,0x000003ff,TRUE),
  HOWTO(R_AJIT_11,        0,2,11,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_11",      FALSE,0,0x000007ff,TRUE),
  HOWTO(R_AJIT_64,        0,4,64,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_64",      FALSE,0,MINUS_ONE, TRUE),
  HOWTO(R_AJIT_OLO10,     0,2,13,FALSE,0,complain_overflow_signed,  ajit_elf_notsup_reloc, "R_AJIT_OLO10",   FALSE,0,0x00001fff,TRUE),
  HOWTO(R_AJIT_HH22,     42,2,22,FALSE,0,complain_overflow_unsigned,bfd_elf_generic_reloc,  "R_AJIT_HH22",    FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_HM10,     32,2,10,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_HM10",    FALSE,0,0x000003ff,TRUE),
  HOWTO(R_AJIT_LM22,     10,2,22,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_LM22",    FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_PC_HH22,  42,2,22,TRUE, 0,complain_overflow_unsigned,bfd_elf_generic_reloc,  "R_AJIT_PC_HH22",    FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_PC_HM10,  32,2,10,TRUE, 0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_PC_HM10",    FALSE,0,0x000003ff,TRUE),
  HOWTO(R_AJIT_PC_LM22,  10,2,22,TRUE, 0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_PC_LM22",    FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_WDISP16,   2,2,16,TRUE, 0,complain_overflow_signed,  ajit_elf_wdisp16_reloc,"R_AJIT_WDISP16", FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_WDISP19,   2,2,19,TRUE, 0,complain_overflow_signed,  bfd_elf_generic_reloc,  "R_AJIT_WDISP19", FALSE,0,0x0007ffff,TRUE),
  HOWTO(R_AJIT_UNUSED_42, 0,0, 0,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_UNUSED_42",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_7,         0,2, 7,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_7",       FALSE,0,0x0000007f,TRUE),
  HOWTO(R_AJIT_5,         0,2, 5,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_5",       FALSE,0,0x0000001f,TRUE),
  HOWTO(R_AJIT_6,         0,2, 6,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_6",       FALSE,0,0x0000003f,TRUE),
  HOWTO(R_AJIT_DISP64,    0,4,64,TRUE, 0,complain_overflow_signed,  bfd_elf_generic_reloc,  "R_AJIT_DISP64",  FALSE,0,MINUS_ONE, TRUE),
  HOWTO(R_AJIT_PLT64,     0,4,64,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_PLT64",   FALSE,0,MINUS_ONE, TRUE),
  HOWTO(R_AJIT_HIX22,     0,4, 0,FALSE,0,complain_overflow_bitfield,ajit_elf_hix22_reloc,  "R_AJIT_HIX22",   FALSE,0,MINUS_ONE, FALSE),
  HOWTO(R_AJIT_LOX10,     0,4, 0,FALSE,0,complain_overflow_dont,    ajit_elf_lox10_reloc,  "R_AJIT_LOX10",   FALSE,0,MINUS_ONE, FALSE),
  HOWTO(R_AJIT_H44,      22,2,22,FALSE,0,complain_overflow_unsigned,bfd_elf_generic_reloc,  "R_AJIT_H44",     FALSE,0,0x003fffff,FALSE),
  HOWTO(R_AJIT_M44,      12,2,10,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_M44",     FALSE,0,0x000003ff,FALSE),
  HOWTO(R_AJIT_L44,       0,2,13,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_L44",     FALSE,0,0x00000fff,FALSE),
  HOWTO(R_AJIT_REGISTER,  0,4, 0,FALSE,0,complain_overflow_bitfield,ajit_elf_notsup_reloc, "R_AJIT_REGISTER",FALSE,0,MINUS_ONE, FALSE),
  HOWTO(R_AJIT_UA64,        0,4,64,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_UA64",      FALSE,0,MINUS_ONE, TRUE),
  HOWTO(R_AJIT_UA16,        0,1,16,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,  "R_AJIT_UA16",      FALSE,0,0x0000ffff,TRUE),
  HOWTO(R_AJIT_TLS_GD_HI22,10,2,22,FALSE,0,complain_overflow_dont,  bfd_elf_generic_reloc,  "R_AJIT_TLS_GD_HI22",FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_TLS_GD_LO10,0,2,10,FALSE,0,complain_overflow_dont,   bfd_elf_generic_reloc,  "R_AJIT_TLS_GD_LO10",FALSE,0,0x000003ff,TRUE),
  HOWTO(R_AJIT_TLS_GD_ADD,0,0, 0,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_TLS_GD_ADD",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_TLS_GD_CALL,2,2,30,TRUE,0,complain_overflow_signed,  bfd_elf_generic_reloc,  "R_AJIT_TLS_GD_CALL",FALSE,0,0x3fffffff,TRUE),
  HOWTO(R_AJIT_TLS_LDM_HI22,10,2,22,FALSE,0,complain_overflow_dont, bfd_elf_generic_reloc,  "R_AJIT_TLS_LDM_HI22",FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_TLS_LDM_LO10,0,2,10,FALSE,0,complain_overflow_dont,  bfd_elf_generic_reloc,  "R_AJIT_TLS_LDM_LO10",FALSE,0,0x000003ff,TRUE),
  HOWTO(R_AJIT_TLS_LDM_ADD,0,0, 0,FALSE,0,complain_overflow_dont,   bfd_elf_generic_reloc,  "R_AJIT_TLS_LDM_ADD",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_TLS_LDM_CALL,2,2,30,TRUE,0,complain_overflow_signed, bfd_elf_generic_reloc,  "R_AJIT_TLS_LDM_CALL",FALSE,0,0x3fffffff,TRUE),
  HOWTO(R_AJIT_TLS_LDO_HIX22,0,2,0,FALSE,0,complain_overflow_bitfield,ajit_elf_hix22_reloc,"R_AJIT_TLS_LDO_HIX22",FALSE,0,0x003fffff, FALSE),
  HOWTO(R_AJIT_TLS_LDO_LOX10,0,2,0,FALSE,0,complain_overflow_dont,  ajit_elf_lox10_reloc,  "R_AJIT_TLS_LDO_LOX10",FALSE,0,0x000003ff, FALSE),
  HOWTO(R_AJIT_TLS_LDO_ADD,0,0, 0,FALSE,0,complain_overflow_dont,   bfd_elf_generic_reloc,  "R_AJIT_TLS_LDO_ADD",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_TLS_IE_HI22,10,2,22,FALSE,0,complain_overflow_dont,  bfd_elf_generic_reloc,  "R_AJIT_TLS_IE_HI22",FALSE,0,0x003fffff,TRUE),
  HOWTO(R_AJIT_TLS_IE_LO10,0,2,10,FALSE,0,complain_overflow_dont,   bfd_elf_generic_reloc,  "R_AJIT_TLS_IE_LO10",FALSE,0,0x000003ff,TRUE),
  HOWTO(R_AJIT_TLS_IE_LD,0,0, 0,FALSE,0,complain_overflow_dont,     bfd_elf_generic_reloc,  "R_AJIT_TLS_IE_LD",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_TLS_IE_LDX,0,0, 0,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_TLS_IE_LDX",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_TLS_IE_ADD,0,0, 0,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_TLS_IE_ADD",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_TLS_LE_HIX22,0,2,0,FALSE,0,complain_overflow_bitfield,ajit_elf_hix22_reloc, "R_AJIT_TLS_LE_HIX22",FALSE,0,0x003fffff, FALSE),
  HOWTO(R_AJIT_TLS_LE_LOX10,0,2,0,FALSE,0,complain_overflow_dont,   ajit_elf_lox10_reloc,  "R_AJIT_TLS_LE_LOX10",FALSE,0,0x000003ff, FALSE),
  HOWTO(R_AJIT_TLS_DTPMOD32,0,0, 0,FALSE,0,complain_overflow_dont,  bfd_elf_generic_reloc,  "R_AJIT_TLS_DTPMOD32",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_TLS_DTPMOD64,0,0, 0,FALSE,0,complain_overflow_dont,  bfd_elf_generic_reloc,  "R_AJIT_TLS_DTPMOD64",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_TLS_DTPOFF32,0,2,32,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,"R_AJIT_TLS_DTPOFF32",FALSE,0,0xffffffff,TRUE),
  HOWTO(R_AJIT_TLS_DTPOFF64,0,4,64,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc,"R_AJIT_TLS_DTPOFF64",FALSE,0,MINUS_ONE,TRUE),
  HOWTO(R_AJIT_TLS_TPOFF32,0,0, 0,FALSE,0,complain_overflow_dont,   bfd_elf_generic_reloc,  "R_AJIT_TLS_TPOFF32",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_TLS_TPOFF64,0,0, 0,FALSE,0,complain_overflow_dont,   bfd_elf_generic_reloc,  "R_AJIT_TLS_TPOFF64",FALSE,0,0x00000000,TRUE),
  HOWTO(R_AJIT_GOTDATA_HIX22,0,2,0,FALSE,0,complain_overflow_bitfield,ajit_elf_hix22_reloc,"R_AJIT_GOTDATA_HIX22",FALSE,0,0x003fffff, FALSE),
  HOWTO(R_AJIT_GOTDATA_LOX10,0,2,0,FALSE,0,complain_overflow_dont,  ajit_elf_lox10_reloc,  "R_AJIT_GOTDATA_LOX10",FALSE,0,0x000003ff, FALSE),
  HOWTO(R_AJIT_GOTDATA_OP_HIX22,0,2,0,FALSE,0,complain_overflow_bitfield,ajit_elf_hix22_reloc,"R_AJIT_GOTDATA_OP_HIX22",FALSE,0,0x003fffff, FALSE),
  HOWTO(R_AJIT_GOTDATA_OP_LOX10,0,2,0,FALSE,0,complain_overflow_dont,  ajit_elf_lox10_reloc,  "R_AJIT_GOTDATA_OP_LOX10",FALSE,0,0x000003ff, FALSE),
  HOWTO(R_AJIT_GOTDATA_OP,0,0, 0,FALSE,0,complain_overflow_dont,   bfd_elf_generic_reloc,  "R_AJIT_GOTDATA_OP",FALSE,0,0x00000000,TRUE),
};
static reloc_howto_type ajit_jmp_irel_howto =
  HOWTO(R_AJIT_JMP_IREL,  0,0,00,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_JMP_IREL",FALSE,0,0x00000000,TRUE);
static reloc_howto_type ajit_irelative_howto =
  HOWTO(R_AJIT_IRELATIVE,  0,0,00,FALSE,0,complain_overflow_dont,    bfd_elf_generic_reloc,  "R_AJIT_IRELATIVE",FALSE,0,0x00000000,TRUE);
static reloc_howto_type ajit_vtinherit_howto =
  HOWTO (R_AJIT_GNU_VTINHERIT, 0,2,0,FALSE,0,complain_overflow_dont, NULL, "R_AJIT_GNU_VTINHERIT", FALSE,0, 0, FALSE);
static reloc_howto_type ajit_vtentry_howto =
  HOWTO (R_AJIT_GNU_VTENTRY, 0,2,0,FALSE,0,complain_overflow_dont, _bfd_elf_rel_vtable_reloc_fn,"R_AJIT_GNU_VTENTRY", FALSE,0,0, FALSE);
static reloc_howto_type ajit_rev32_howto =
  HOWTO(R_AJIT_REV32, 0,2,32,FALSE,0,complain_overflow_bitfield,bfd_elf_generic_reloc, "R_AJIT_REV32", FALSE,0,0xffffffff,TRUE);

reloc_howto_type *
_bfd_ajit_elf_reloc_type_lookup (bfd *abfd ATTRIBUTE_UNUSED,
				  bfd_reloc_code_real_type code)
{
  /* We explicitly handle each relocation type in the switch
     instead of using a lookup table for efficiency.  */
  switch (code)
    {
    case BFD_RELOC_NONE:
      return &_bfd_ajit_elf_howto_table[R_AJIT_NONE];

    case BFD_RELOC_8:
      return &_bfd_ajit_elf_howto_table[R_AJIT_8];

    case BFD_RELOC_16:
      return &_bfd_ajit_elf_howto_table[R_AJIT_16];

    case BFD_RELOC_32:
      return &_bfd_ajit_elf_howto_table[R_AJIT_32];

    case BFD_RELOC_8_PCREL:
      return &_bfd_ajit_elf_howto_table[R_AJIT_DISP8];

    case BFD_RELOC_16_PCREL:
      return &_bfd_ajit_elf_howto_table[R_AJIT_DISP16];

    case BFD_RELOC_32_PCREL:
      return &_bfd_ajit_elf_howto_table[R_AJIT_DISP32];

    case BFD_RELOC_32_PCREL_S2:
      return &_bfd_ajit_elf_howto_table[R_AJIT_WDISP30];

    case BFD_RELOC_AJIT_WDISP22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_WDISP22];

    case BFD_RELOC_HI22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_HI22];

    case BFD_RELOC_AJIT22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_22];

    case BFD_RELOC_AJIT13:
      return &_bfd_ajit_elf_howto_table[R_AJIT_13];

    case BFD_RELOC_LO10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_LO10];

    case BFD_RELOC_AJIT_GOT10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_GOT10];

    case BFD_RELOC_AJIT_GOT13:
      return &_bfd_ajit_elf_howto_table[R_AJIT_GOT13];

    case BFD_RELOC_AJIT_GOT22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_GOT22];

    case BFD_RELOC_AJIT_PC10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_PC10];

    case BFD_RELOC_AJIT_PC22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_PC22];

    case BFD_RELOC_AJIT_WPLT30:
      return &_bfd_ajit_elf_howto_table[R_AJIT_WPLT30];

    case BFD_RELOC_AJIT_COPY:
      return &_bfd_ajit_elf_howto_table[R_AJIT_COPY];

    case BFD_RELOC_AJIT_GLOB_DAT:
      return &_bfd_ajit_elf_howto_table[R_AJIT_GLOB_DAT];

    case BFD_RELOC_AJIT_JMP_SLOT:
      return &_bfd_ajit_elf_howto_table[R_AJIT_JMP_SLOT];

    case BFD_RELOC_AJIT_RELATIVE:
      return &_bfd_ajit_elf_howto_table[R_AJIT_RELATIVE];

    case BFD_RELOC_AJIT_UA32:
      return &_bfd_ajit_elf_howto_table[R_AJIT_UA32];

    case BFD_RELOC_AJIT_PLT32:
      return &_bfd_ajit_elf_howto_table[R_AJIT_PLT32];

    case BFD_RELOC_AJIT_10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_10];

    case BFD_RELOC_AJIT_11:
      return &_bfd_ajit_elf_howto_table[R_AJIT_11];

    case BFD_RELOC_AJIT_64:
      return &_bfd_ajit_elf_howto_table[R_AJIT_64];

    case BFD_RELOC_AJIT_OLO10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_OLO10];

    case BFD_RELOC_AJIT_HH22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_HH22];

    case BFD_RELOC_AJIT_HM10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_HM10];

    case BFD_RELOC_AJIT_LM22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_LM22];

    case BFD_RELOC_AJIT_PC_HH22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_PC_HH22];

    case BFD_RELOC_AJIT_PC_HM10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_PC_HM10];

    case BFD_RELOC_AJIT_PC_LM22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_PC_LM22];

    case BFD_RELOC_AJIT_WDISP16:
      return &_bfd_ajit_elf_howto_table[R_AJIT_WDISP16];

    case BFD_RELOC_AJIT_WDISP19:
      return &_bfd_ajit_elf_howto_table[R_AJIT_WDISP19];

    case BFD_RELOC_AJIT_7:
      return &_bfd_ajit_elf_howto_table[R_AJIT_7];

    case BFD_RELOC_AJIT_5:
      return &_bfd_ajit_elf_howto_table[R_AJIT_5];

    case BFD_RELOC_AJIT_6:
      return &_bfd_ajit_elf_howto_table[R_AJIT_6];

    case BFD_RELOC_AJIT_DISP64:
      return &_bfd_ajit_elf_howto_table[R_AJIT_DISP64];

    case BFD_RELOC_AJIT_PLT64:
      return &_bfd_ajit_elf_howto_table[R_AJIT_PLT64];

    case BFD_RELOC_AJIT_HIX22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_HIX22];

    case BFD_RELOC_AJIT_LOX10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_LOX10];

    case BFD_RELOC_AJIT_H44:
      return &_bfd_ajit_elf_howto_table[R_AJIT_H44];

    case BFD_RELOC_AJIT_M44:
      return &_bfd_ajit_elf_howto_table[R_AJIT_M44];

    case BFD_RELOC_AJIT_L44:
      return &_bfd_ajit_elf_howto_table[R_AJIT_L44];

    case BFD_RELOC_AJIT_REGISTER:
      return &_bfd_ajit_elf_howto_table[R_AJIT_REGISTER];

    case BFD_RELOC_AJIT_UA64:
      return &_bfd_ajit_elf_howto_table[R_AJIT_UA64];

    case BFD_RELOC_AJIT_UA16:
      return &_bfd_ajit_elf_howto_table[R_AJIT_UA16];

    case BFD_RELOC_AJIT_TLS_GD_HI22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_GD_HI22];

    case BFD_RELOC_AJIT_TLS_GD_LO10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_GD_LO10];

    case BFD_RELOC_AJIT_TLS_GD_ADD:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_GD_ADD];

    case BFD_RELOC_AJIT_TLS_GD_CALL:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_GD_CALL];

    case BFD_RELOC_AJIT_TLS_LDM_HI22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_LDM_HI22];

    case BFD_RELOC_AJIT_TLS_LDM_LO10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_LDM_LO10];

    case BFD_RELOC_AJIT_TLS_LDM_ADD:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_LDM_ADD];

    case BFD_RELOC_AJIT_TLS_LDM_CALL:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_LDM_CALL];

    case BFD_RELOC_AJIT_TLS_LDO_HIX22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_LDO_HIX22];

    case BFD_RELOC_AJIT_TLS_LDO_LOX10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_LDO_LOX10];

    case BFD_RELOC_AJIT_TLS_LDO_ADD:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_LDO_ADD];

    case BFD_RELOC_AJIT_TLS_IE_HI22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_IE_HI22];

    case BFD_RELOC_AJIT_TLS_IE_LO10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_IE_LO10];

    case BFD_RELOC_AJIT_TLS_IE_LD:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_IE_LD];

    case BFD_RELOC_AJIT_TLS_IE_LDX:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_IE_LDX];

    case BFD_RELOC_AJIT_TLS_IE_ADD:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_IE_ADD];

    case BFD_RELOC_AJIT_TLS_LE_HIX22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_LE_HIX22];

    case BFD_RELOC_AJIT_TLS_LE_LOX10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_LE_LOX10];

    case BFD_RELOC_AJIT_TLS_DTPMOD32:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_DTPMOD32];

    case BFD_RELOC_AJIT_TLS_DTPMOD64:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_DTPMOD64];

    case BFD_RELOC_AJIT_TLS_DTPOFF32:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_DTPOFF32];

    case BFD_RELOC_AJIT_TLS_DTPOFF64:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_DTPOFF64];

    case BFD_RELOC_AJIT_TLS_TPOFF32:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_TPOFF32];

    case BFD_RELOC_AJIT_TLS_TPOFF64:
      return &_bfd_ajit_elf_howto_table[R_AJIT_TLS_TPOFF64];

    case BFD_RELOC_AJIT_GOTDATA_HIX22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_GOTDATA_HIX22];

    case BFD_RELOC_AJIT_GOTDATA_LOX10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_GOTDATA_LOX10];

    case BFD_RELOC_AJIT_GOTDATA_OP_HIX22:
      return &_bfd_ajit_elf_howto_table[R_AJIT_GOTDATA_OP_HIX22];

    case BFD_RELOC_AJIT_GOTDATA_OP_LOX10:
      return &_bfd_ajit_elf_howto_table[R_AJIT_GOTDATA_OP_LOX10];

    case BFD_RELOC_AJIT_GOTDATA_OP:
      return &_bfd_ajit_elf_howto_table[R_AJIT_GOTDATA_OP];

    case BFD_RELOC_AJIT_JMP_IREL:
      return &ajit_jmp_irel_howto;

    case BFD_RELOC_AJIT_IRELATIVE:
      return &ajit_irelative_howto;

    case BFD_RELOC_VTABLE_INHERIT:
      return &ajit_vtinherit_howto;

    case BFD_RELOC_VTABLE_ENTRY:
      return &ajit_vtentry_howto;

    case BFD_RELOC_AJIT_REV32:
      return &ajit_rev32_howto;

    default:
      break;
    }
    bfd_set_error (bfd_error_bad_value);
    return NULL;
}

reloc_howto_type *
_bfd_ajit_elf_reloc_name_lookup (bfd *abfd ATTRIBUTE_UNUSED,
				  const char *r_name)
{
  unsigned int i;

  for (i = 0;
       i < (sizeof (_bfd_ajit_elf_howto_table)
	    / sizeof (_bfd_ajit_elf_howto_table[0]));
       i++)
    if (_bfd_ajit_elf_howto_table[i].name != NULL
	&& strcasecmp (_bfd_ajit_elf_howto_table[i].name, r_name) == 0)
      return &_bfd_ajit_elf_howto_table[i];

  if (strcasecmp (ajit_vtinherit_howto.name, r_name) == 0)
    return &ajit_vtinherit_howto;
  if (strcasecmp (ajit_vtentry_howto.name, r_name) == 0)
    return &ajit_vtentry_howto;
  if (strcasecmp (ajit_rev32_howto.name, r_name) == 0)
    return &ajit_rev32_howto;

  return NULL;
}

reloc_howto_type *
_bfd_ajit_elf_info_to_howto_ptr (unsigned int r_type)
{
  switch (r_type)
    {
    case R_AJIT_JMP_IREL:
      return &ajit_jmp_irel_howto;

    case R_AJIT_IRELATIVE:
      return &ajit_irelative_howto;

    case R_AJIT_GNU_VTINHERIT:
      return &ajit_vtinherit_howto;

    case R_AJIT_GNU_VTENTRY:
      return &ajit_vtentry_howto;

    case R_AJIT_REV32:
      return &ajit_rev32_howto;

    default:
      if (r_type >= (unsigned int) R_AJIT_max_std)
	{
	  (*_bfd_error_handler) (_("invalid relocation type %d"),
				 (int) r_type);
	  r_type = R_AJIT_NONE;
	}
      return &_bfd_ajit_elf_howto_table[r_type];
    }
}

/* Both 32-bit and 64-bit ajit encode this in an identical manner,
   so just take advantage of that.  */
#define AJIT_ELF_R_TYPE(r_info)	\
	((r_info) & 0xff)

void
_bfd_ajit_elf_info_to_howto (bfd *abfd ATTRIBUTE_UNUSED, arelent *cache_ptr,
			      Elf_Internal_Rela *dst)
{
  unsigned int r_type = AJIT_ELF_R_TYPE (dst->r_info);

  cache_ptr->howto = _bfd_ajit_elf_info_to_howto_ptr (r_type);
}


/* The nop opcode we use.  */
#define AJIT_NOP 0x01000000

#define AJIT_INSN_BYTES	4

/* The AJIT linker needs to keep track of the number of relocs that it
   decides to copy as dynamic relocs in check_relocs for each symbol.
   This is so that it can later discard them if they are found to be
   unnecessary.  We store the information in a field extending the
   regular ELF linker hash table.  */

struct _bfd_ajit_elf_dyn_relocs
{
  struct _bfd_ajit_elf_dyn_relocs *next;

  /* The input section of the reloc.  */
  asection *sec;

  /* Total number of relocs copied for the input section.  */
  bfd_size_type count;

  /* Number of pc-relative relocs copied for the input section.  */
  bfd_size_type pc_count;
};

/* AJIT ELF linker hash entry.  */

struct _bfd_ajit_elf_link_hash_entry
{
  struct elf_link_hash_entry elf;

  /* Track dynamic relocs copied for this symbol.  */
  struct _bfd_ajit_elf_dyn_relocs *dyn_relocs;

#define GOT_UNKNOWN     0
#define GOT_NORMAL      1
#define GOT_TLS_GD      2
#define GOT_TLS_IE      3
  unsigned char tls_type;
};

#define _bfd_ajit_elf_hash_entry(ent) ((struct _bfd_ajit_elf_link_hash_entry *)(ent))

struct _bfd_ajit_elf_obj_tdata
{
  struct elf_obj_tdata root;

  /* tls_type for each local got entry.  */
  char *local_got_tls_type;

  /* TRUE if TLS GD relocs has been seen for this object.  */
  bfd_boolean has_tlsgd;
};

#define _bfd_ajit_elf_tdata(abfd) \
  ((struct _bfd_ajit_elf_obj_tdata *) (abfd)->tdata.any)

#define _bfd_ajit_elf_local_got_tls_type(abfd) \
  (_bfd_ajit_elf_tdata (abfd)->local_got_tls_type)

#define is_ajit_elf(bfd)				\
  (bfd_get_flavour (bfd) == bfd_target_elf_flavour	\
   && elf_tdata (bfd) != NULL				\
   && elf_object_id (bfd) == AJIT_ELF_DATA)

bfd_boolean
_bfd_ajit_elf_mkobject (bfd *abfd)
{
  return bfd_elf_allocate_object (abfd, sizeof (struct _bfd_ajit_elf_obj_tdata),
				  AJIT_ELF_DATA);
}

static void
ajit_put_word_32 (bfd *abfd, bfd_vma val, void *ptr)
{
  bfd_put_32 (abfd, val, ptr);
}

static void
ajit_put_word_64 (bfd *abfd, bfd_vma val, void *ptr)
{
  bfd_put_64 (abfd, val, ptr);
}

static void
ajit_elf_append_rela (bfd *abfd, asection *s, Elf_Internal_Rela *rel)
{
  const struct elf_backend_data *bed;
  bfd_byte *loc;

  bed = get_elf_backend_data (abfd);
  loc = s->contents + (s->reloc_count++ * bed->s->sizeof_rela);
  bed->s->swap_reloca_out (abfd, rel, loc);
}

static bfd_vma
ajit_elf_r_info_64 (Elf_Internal_Rela *in_rel ATTRIBUTE_UNUSED,
		     bfd_vma rel_index ATTRIBUTE_UNUSED,
		     bfd_vma type ATTRIBUTE_UNUSED)
{
  return ELF64_R_INFO (rel_index,
		       (in_rel ?
			ELF64_R_TYPE_INFO (ELF64_R_TYPE_DATA (in_rel->r_info),
					   type) : type));
}

static bfd_vma
ajit_elf_r_info_32 (Elf_Internal_Rela *in_rel ATTRIBUTE_UNUSED,
		     bfd_vma rel_index, bfd_vma type)
{
  return ELF32_R_INFO (rel_index, type);
}

static bfd_vma
ajit_elf_r_symndx_64 (bfd_vma r_info)
{
  bfd_vma r_symndx = ELF32_R_SYM (r_info);
  return (r_symndx >> 24);
}

static bfd_vma
ajit_elf_r_symndx_32 (bfd_vma r_info)
{
  return ELF32_R_SYM (r_info);
}

/* PLT/GOT stuff */

#define PLT32_ENTRY_SIZE 12
#define PLT32_HEADER_SIZE	(4 * PLT32_ENTRY_SIZE)

/* The first four entries in a 32-bit procedure linkage table are reserved,
   and the initial contents are unimportant (we zero them out).
   Subsequent entries look like this.  See the SVR4 ABI AJIT
   supplement to see how this works.  */

/* sethi %hi(.-.plt0),%g1.  We fill in the address later.  */
#define PLT32_ENTRY_WORD0 0x03000000
/* b,a .plt0.  We fill in the offset later.  */
#define PLT32_ENTRY_WORD1 0x30800000
/* nop.  */
#define PLT32_ENTRY_WORD2 AJIT_NOP

static int
ajit32_plt_entry_build (bfd *output_bfd, asection *splt, bfd_vma offset,
			 bfd_vma max ATTRIBUTE_UNUSED,
			 bfd_vma *r_offset)
{
      bfd_put_32 (output_bfd,
		  PLT32_ENTRY_WORD0 + offset,
		  splt->contents + offset);
      bfd_put_32 (output_bfd,
		  (PLT32_ENTRY_WORD1
		   + (((- (offset + 4)) >> 2) & 0x3fffff)),
		  splt->contents + offset + 4);
      bfd_put_32 (output_bfd, (bfd_vma) PLT32_ENTRY_WORD2,
		  splt->contents + offset + 8);

      *r_offset = offset;

      return offset / PLT32_ENTRY_SIZE - 4;
}

/* Both the headers and the entries are icache aligned.  */
#define PLT64_ENTRY_SIZE	32
#define PLT64_HEADER_SIZE	(4 * PLT64_ENTRY_SIZE)
#define PLT64_LARGE_THRESHOLD	32768

static int
ajit64_plt_entry_build (bfd *output_bfd, asection *splt, bfd_vma offset,
			 bfd_vma max, bfd_vma *r_offset)
{
  unsigned char *entry = splt->contents + offset;
  const unsigned int nop = AJIT_NOP;
  int plt_index;

  if (offset < (PLT64_LARGE_THRESHOLD * PLT64_ENTRY_SIZE))
    {
      unsigned int sethi, ba;

      *r_offset = offset;

      plt_index = (offset / PLT64_ENTRY_SIZE);

      sethi = 0x03000000 | (plt_index * PLT64_ENTRY_SIZE);
      ba = 0x30680000
	| (((splt->contents + PLT64_ENTRY_SIZE) - (entry + 4)) / 4 & 0x7ffff);

      bfd_put_32 (output_bfd, (bfd_vma) sethi, entry);
      bfd_put_32 (output_bfd, (bfd_vma) ba,    entry + 4);
      bfd_put_32 (output_bfd, (bfd_vma) nop,   entry + 8);
      bfd_put_32 (output_bfd, (bfd_vma) nop,   entry + 12);
      bfd_put_32 (output_bfd, (bfd_vma) nop,   entry + 16);
      bfd_put_32 (output_bfd, (bfd_vma) nop,   entry + 20);
      bfd_put_32 (output_bfd, (bfd_vma) nop,   entry + 24);
      bfd_put_32 (output_bfd, (bfd_vma) nop,   entry + 28);
    }
  else
    {
      unsigned char *ptr;
      unsigned int ldx;
      int block, last_block, ofs, last_ofs, chunks_this_block;
      const int insn_chunk_size = (6 * 4);
      const int ptr_chunk_size = (1 * 8);
      const int entries_per_block = 160;
      const int block_size = entries_per_block * (insn_chunk_size
						  + ptr_chunk_size);

      /* Entries 32768 and higher are grouped into blocks of 160.
	 The blocks are further subdivided into 160 sequences of
	 6 instructions and 160 pointers.  If a block does not require
	 the full 160 entries, let's say it requires N, then there
	 will be N sequences of 6 instructions and N pointers.  */

      offset -= (PLT64_LARGE_THRESHOLD * PLT64_ENTRY_SIZE);
      max -= (PLT64_LARGE_THRESHOLD * PLT64_ENTRY_SIZE);

      block = offset / block_size;
      last_block = max / block_size;
      if (block != last_block)
	{
	  chunks_this_block = 160;
	}
      else
	{
	  last_ofs = max % block_size;
	  chunks_this_block = last_ofs / (insn_chunk_size + ptr_chunk_size);
	}

      ofs = offset % block_size;

      plt_index = (PLT64_LARGE_THRESHOLD +
	       (block * 160) +
	       (ofs / insn_chunk_size));

      ptr = splt->contents
	+ (PLT64_LARGE_THRESHOLD * PLT64_ENTRY_SIZE)
	+ (block * block_size)
	+ (chunks_this_block * insn_chunk_size)
	+ (ofs / insn_chunk_size) * ptr_chunk_size;

      *r_offset = (bfd_vma) (ptr - splt->contents);

      ldx = 0xc25be000 | ((ptr - (entry+4)) & 0x1fff);

      /* mov %o7,%g5
	 call .+8
	 nop
	 ldx [%o7+P],%g1
	 jmpl %o7+%g1,%g1
	 mov %g5,%o7  */
      bfd_put_32 (output_bfd, (bfd_vma) 0x8a10000f, entry);
      bfd_put_32 (output_bfd, (bfd_vma) 0x40000002, entry + 4);
      bfd_put_32 (output_bfd, (bfd_vma) AJIT_NOP,  entry + 8);
      bfd_put_32 (output_bfd, (bfd_vma) ldx,        entry + 12);
      bfd_put_32 (output_bfd, (bfd_vma) 0x83c3c001, entry + 16);
      bfd_put_32 (output_bfd, (bfd_vma) 0x9e100005, entry + 20);

      bfd_put_64 (output_bfd, (bfd_vma) (splt->contents - (entry + 4)), ptr);
    }

  return plt_index - 4;
}

/* The format of the first PLT entry in a VxWorks executable.  */
static const bfd_vma ajit_vxworks_exec_plt0_entry[] =
  {
    0x05000000,	/* sethi  %hi(_GLOBAL_OFFSET_TABLE_+8), %g2 */
    0x8410a000,	/* or     %g2, %lo(_GLOBAL_OFFSET_TABLE_+8), %g2 */
    0xc4008000,	/* ld     [ %g2 ], %g2 */
    0x81c08000,	/* jmp    %g2 */
    0x01000000	/* nop */
  };

/* The format of subsequent PLT entries.  */
static const bfd_vma ajit_vxworks_exec_plt_entry[] =
  {
    0x03000000,	/* sethi  %hi(_GLOBAL_OFFSET_TABLE_+f@got), %g1 */
    0x82106000,	/* or     %g1, %lo(_GLOBAL_OFFSET_TABLE_+f@got), %g1 */
    0xc2004000,	/* ld     [ %g1 ], %g1 */
    0x81c04000,	/* jmp    %g1 */
    0x01000000,	/* nop */
    0x03000000,	/* sethi  %hi(f@pltindex), %g1 */
    0x10800000,	/* b      _PLT_resolve */
    0x82106000	/* or     %g1, %lo(f@pltindex), %g1 */
  };

/* The format of the first PLT entry in a VxWorks shared object.  */
static const bfd_vma ajit_vxworks_shared_plt0_entry[] =
  {
    0xc405e008,	/* ld     [ %l7 + 8 ], %g2 */
    0x81c08000,	/* jmp    %g2 */
    0x01000000	/* nop */
  };

/* The format of subsequent PLT entries.  */
static const bfd_vma ajit_vxworks_shared_plt_entry[] =
  {
    0x03000000,	/* sethi  %hi(f@got), %g1 */
    0x82106000,	/* or     %g1, %lo(f@got), %g1 */
    0xc205c001,	/* ld     [ %l7 + %g1 ], %g1 */
    0x81c04000,	/* jmp    %g1 */
    0x01000000,	/* nop */
    0x03000000,	/* sethi  %hi(f@pltindex), %g1 */
    0x10800000,	/* b      _PLT_resolve */
    0x82106000	/* or     %g1, %lo(f@pltindex), %g1 */
  };

#define AJIT_ELF_PUT_WORD(htab, bfd, val, ptr)	\
	htab->put_word(bfd, val, ptr)

#define AJIT_ELF_R_INFO(htab, in_rel, index, type)	\
	htab->r_info(in_rel, index, type)

#define AJIT_ELF_R_SYMNDX(htab, r_info)	\
	htab->r_symndx(r_info)

#define AJIT_ELF_WORD_BYTES(htab)	\
	htab->bytes_per_word

#define AJIT_ELF_RELA_BYTES(htab)	\
	htab->bytes_per_rela

#define AJIT_ELF_DTPOFF_RELOC(htab)	\
	htab->dtpoff_reloc

#define AJIT_ELF_DTPMOD_RELOC(htab)	\
	htab->dtpmod_reloc

#define AJIT_ELF_TPOFF_RELOC(htab)	\
	htab->tpoff_reloc

#define AJIT_ELF_BUILD_PLT_ENTRY(htab, obfd, splt, off, max, r_off) \
	htab->build_plt_entry (obfd, splt, off, max, r_off)

/* Create an entry in an AJIT ELF linker hash table.  */

static struct bfd_hash_entry *
link_hash_newfunc (struct bfd_hash_entry *entry,
		   struct bfd_hash_table *table, const char *string)
{
  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (entry == NULL)
    {
      entry = bfd_hash_allocate (table,
				 sizeof (struct _bfd_ajit_elf_link_hash_entry));
      if (entry == NULL)
	return entry;
    }

  /* Call the allocation method of the superclass.  */
  entry = _bfd_elf_link_hash_newfunc (entry, table, string);
  if (entry != NULL)
    {
      struct _bfd_ajit_elf_link_hash_entry *eh;

      eh = (struct _bfd_ajit_elf_link_hash_entry *) entry;
      eh->dyn_relocs = NULL;
      eh->tls_type = GOT_UNKNOWN;
    }

  return entry;
}

/* The name of the dynamic interpreter.  This is put in the .interp
   section.  */

#define ELF32_DYNAMIC_INTERPRETER "/usr/lib/ld.so.1"
#define ELF64_DYNAMIC_INTERPRETER "/usr/lib/ajitv9/ld.so.1"

/* Compute a hash of a local hash entry.  We use elf_link_hash_entry
   for local symbol so that we can handle local STT_GNU_IFUNC symbols
   as global symbol.  We reuse indx and dynstr_index for local symbol
   hash since they aren't used by global symbols in this backend.  */

static hashval_t
elf_ajit_local_htab_hash (const void *ptr)
{
  struct elf_link_hash_entry *h
    = (struct elf_link_hash_entry *) ptr;
  return ELF_LOCAL_SYMBOL_HASH (h->indx, h->dynstr_index);
}

/* Compare local hash entries.  */

static int
elf_ajit_local_htab_eq (const void *ptr1, const void *ptr2)
{
  struct elf_link_hash_entry *h1
     = (struct elf_link_hash_entry *) ptr1;
  struct elf_link_hash_entry *h2
    = (struct elf_link_hash_entry *) ptr2;

  return h1->indx == h2->indx && h1->dynstr_index == h2->dynstr_index;
}

/* Find and/or create a hash entry for local symbol.  */

static struct elf_link_hash_entry *
elf_ajit_get_local_sym_hash (struct _bfd_ajit_elf_link_hash_table *htab,
			      bfd *abfd, const Elf_Internal_Rela *rel,
			      bfd_boolean create)
{
  struct _bfd_ajit_elf_link_hash_entry e, *ret;
  asection *sec = abfd->sections;
  unsigned long r_symndx;
  hashval_t h;
  void **slot;

  r_symndx = AJIT_ELF_R_SYMNDX (htab, rel->r_info);
  h = ELF_LOCAL_SYMBOL_HASH (sec->id, r_symndx);

  e.elf.indx = sec->id;
  e.elf.dynstr_index = r_symndx;
  slot = htab_find_slot_with_hash (htab->loc_hash_table, &e, h,
				   create ? INSERT : NO_INSERT);

  if (!slot)
    return NULL;

  if (*slot)
    {
      ret = (struct _bfd_ajit_elf_link_hash_entry *) *slot;
      return &ret->elf;
    }

  ret = (struct _bfd_ajit_elf_link_hash_entry *)
	objalloc_alloc ((struct objalloc *) htab->loc_hash_memory,
			sizeof (struct _bfd_ajit_elf_link_hash_entry));
  if (ret)
    {
      memset (ret, 0, sizeof (*ret));
      ret->elf.indx = sec->id;
      ret->elf.dynstr_index = r_symndx;
      ret->elf.dynindx = -1;
      ret->elf.plt.offset = (bfd_vma) -1;
      ret->elf.got.offset = (bfd_vma) -1;
      *slot = ret;
    }
  return &ret->elf;
}

/* Create a AJIT ELF linker hash table.  */

struct bfd_link_hash_table *
_bfd_ajit_elf_link_hash_table_create (bfd *abfd)
{
  struct _bfd_ajit_elf_link_hash_table *ret;
  bfd_size_type amt = sizeof (struct _bfd_ajit_elf_link_hash_table);

  ret = (struct _bfd_ajit_elf_link_hash_table *) bfd_zmalloc (amt);
  if (ret == NULL)
    return NULL;

  if (ABI_64_P (abfd))
    {
      ret->put_word = ajit_put_word_64;
      ret->r_info = ajit_elf_r_info_64;
      ret->r_symndx = ajit_elf_r_symndx_64;
      ret->dtpoff_reloc = R_AJIT_TLS_DTPOFF64;
      ret->dtpmod_reloc = R_AJIT_TLS_DTPMOD64;
      ret->tpoff_reloc = R_AJIT_TLS_TPOFF64;
      ret->word_align_power = 3;
      ret->align_power_max = 4;
      ret->bytes_per_word = 8;
      ret->bytes_per_rela = sizeof (Elf64_External_Rela);
      ret->dynamic_interpreter = ELF64_DYNAMIC_INTERPRETER;
      ret->dynamic_interpreter_size = sizeof ELF64_DYNAMIC_INTERPRETER;

      ret->build_plt_entry = ajit64_plt_entry_build;
      ret->plt_header_size = PLT64_HEADER_SIZE;
      ret->plt_entry_size = PLT64_ENTRY_SIZE;
    }
  else
    {
      ret->put_word = ajit_put_word_32;
      ret->r_info = ajit_elf_r_info_32;
      ret->r_symndx = ajit_elf_r_symndx_32;
      ret->dtpoff_reloc = R_AJIT_TLS_DTPOFF32;
      ret->dtpmod_reloc = R_AJIT_TLS_DTPMOD32;
      ret->tpoff_reloc = R_AJIT_TLS_TPOFF32;
      ret->word_align_power = 2;
      ret->align_power_max = 3;
      ret->bytes_per_word = 4;
      ret->bytes_per_rela = sizeof (Elf32_External_Rela);
      ret->dynamic_interpreter = ELF32_DYNAMIC_INTERPRETER;
      ret->dynamic_interpreter_size = sizeof ELF32_DYNAMIC_INTERPRETER;

      ret->build_plt_entry = ajit32_plt_entry_build;
      ret->plt_header_size = PLT32_HEADER_SIZE;
      ret->plt_entry_size = PLT32_ENTRY_SIZE;
    }

  if (!_bfd_elf_link_hash_table_init (&ret->elf, abfd, link_hash_newfunc,
				      sizeof (struct _bfd_ajit_elf_link_hash_entry),
				      AJIT_ELF_DATA))
    {
      free (ret);
      return NULL;
    }

  ret->loc_hash_table = htab_try_create (1024,
					 elf_ajit_local_htab_hash,
					 elf_ajit_local_htab_eq,
					 NULL);
  ret->loc_hash_memory = objalloc_create ();
  if (!ret->loc_hash_table || !ret->loc_hash_memory)
    {
      free (ret);
      return NULL;
    }

  return &ret->elf.root;
}

/* Destroy a AJIT ELF linker hash table.  */

void
_bfd_ajit_elf_link_hash_table_free (struct bfd_link_hash_table *hash)
{
  struct _bfd_ajit_elf_link_hash_table *htab
    = (struct _bfd_ajit_elf_link_hash_table *) hash;

  if (htab->loc_hash_table)
    htab_delete (htab->loc_hash_table);
  if (htab->loc_hash_memory)
    objalloc_free ((struct objalloc *) htab->loc_hash_memory);
  _bfd_generic_link_hash_table_free (hash);
}

/* Create .plt, .rela.plt, .got, .rela.got, .dynbss, and
   .rela.bss sections in DYNOBJ, and set up shortcuts to them in our
   hash table.  */

bfd_boolean
_bfd_ajit_elf_create_dynamic_sections (bfd *dynobj,
					struct bfd_link_info *info)
{
  struct _bfd_ajit_elf_link_hash_table *htab;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);

  if (!_bfd_elf_create_dynamic_sections (dynobj, info))
    return FALSE;

  htab->sdynbss = bfd_get_section_by_name (dynobj, ".dynbss");
  if (!info->shared)
    htab->srelbss = bfd_get_section_by_name (dynobj, ".rela.bss");

  if (htab->is_vxworks)
    {
      if (!elf_vxworks_create_dynamic_sections (dynobj, info, &htab->srelplt2))
	return FALSE;
      if (info->shared)
	{
	  htab->plt_header_size
	    = 4 * ARRAY_SIZE (ajit_vxworks_shared_plt0_entry);
	  htab->plt_entry_size
	    = 4 * ARRAY_SIZE (ajit_vxworks_shared_plt_entry);
	}
      else
	{
	  htab->plt_header_size
	    = 4 * ARRAY_SIZE (ajit_vxworks_exec_plt0_entry);
	  htab->plt_entry_size
	    = 4 * ARRAY_SIZE (ajit_vxworks_exec_plt_entry);
	}
    }

  if (!htab->elf.splt || !htab->elf.srelplt || !htab->sdynbss
      || (!info->shared && !htab->srelbss))
    abort ();

  return TRUE;
}

static bfd_boolean
create_ifunc_sections (bfd *abfd, struct bfd_link_info *info)
{
  const struct elf_backend_data *bed = get_elf_backend_data (abfd);
  struct elf_link_hash_table *htab = elf_hash_table (info);
  flagword flags, pltflags;
  asection *s;

  if (htab->irelifunc != NULL || htab->iplt != NULL)
    return TRUE;

  flags = bed->dynamic_sec_flags;
  pltflags = flags | SEC_ALLOC | SEC_CODE | SEC_LOAD;

  s = bfd_make_section_with_flags (abfd, ".iplt", pltflags);
  if (s == NULL
      || ! bfd_set_section_alignment (abfd, s, bed->plt_alignment))
    return FALSE;
  htab->iplt = s;

  s = bfd_make_section_with_flags (abfd, ".rela.iplt",
				   flags | SEC_READONLY);
  if (s == NULL
      || ! bfd_set_section_alignment (abfd, s,
				      bed->s->log_file_align))
    return FALSE;
  htab->irelplt = s;

  return TRUE;
}

/* Copy the extra info we tack onto an elf_link_hash_entry.  */

void
_bfd_ajit_elf_copy_indirect_symbol (struct bfd_link_info *info,
				     struct elf_link_hash_entry *dir,
				     struct elf_link_hash_entry *ind)
{
  struct _bfd_ajit_elf_link_hash_entry *edir, *eind;

  edir = (struct _bfd_ajit_elf_link_hash_entry *) dir;
  eind = (struct _bfd_ajit_elf_link_hash_entry *) ind;

  if (eind->dyn_relocs != NULL)
    {
      if (edir->dyn_relocs != NULL)
	{
	  struct _bfd_ajit_elf_dyn_relocs **pp;
	  struct _bfd_ajit_elf_dyn_relocs *p;

	  /* Add reloc counts against the indirect sym to the direct sym
	     list.  Merge any entries against the same section.  */
	  for (pp = &eind->dyn_relocs; (p = *pp) != NULL; )
	    {
	      struct _bfd_ajit_elf_dyn_relocs *q;

	      for (q = edir->dyn_relocs; q != NULL; q = q->next)
		if (q->sec == p->sec)
		  {
		    q->pc_count += p->pc_count;
		    q->count += p->count;
		    *pp = p->next;
		    break;
		  }
	      if (q == NULL)
		pp = &p->next;
	    }
	  *pp = edir->dyn_relocs;
	}

      edir->dyn_relocs = eind->dyn_relocs;
      eind->dyn_relocs = NULL;
    }

  if (ind->root.type == bfd_link_hash_indirect
      && dir->got.refcount <= 0)
    {
      edir->tls_type = eind->tls_type;
      eind->tls_type = GOT_UNKNOWN;
    }
  _bfd_elf_link_hash_copy_indirect (info, dir, ind);
}

static int
ajit_elf_tls_transition (struct bfd_link_info *info, bfd *abfd,
			  int r_type, int is_local)
{
  if (! ABI_64_P (abfd)
      && r_type == R_AJIT_TLS_GD_HI22
      && ! _bfd_ajit_elf_tdata (abfd)->has_tlsgd)
    r_type = R_AJIT_REV32;

  if (info->shared)
    return r_type;

  switch (r_type)
    {
    case R_AJIT_TLS_GD_HI22:
      if (is_local)
	return R_AJIT_TLS_LE_HIX22;
      return R_AJIT_TLS_IE_HI22;
    case R_AJIT_TLS_GD_LO10:
      if (is_local)
	return R_AJIT_TLS_LE_LOX10;
      return R_AJIT_TLS_IE_LO10;
    case R_AJIT_TLS_IE_HI22:
      if (is_local)
	return R_AJIT_TLS_LE_HIX22;
      return r_type;
    case R_AJIT_TLS_IE_LO10:
      if (is_local)
	return R_AJIT_TLS_LE_LOX10;
      return r_type;
    case R_AJIT_TLS_LDM_HI22:
      return R_AJIT_TLS_LE_HIX22;
    case R_AJIT_TLS_LDM_LO10:
      return R_AJIT_TLS_LE_LOX10;
    }

  return r_type;
}

/* Look through the relocs for a section during the first phase, and
   allocate space in the global offset table or procedure linkage
   table.  */

bfd_boolean
_bfd_ajit_elf_check_relocs (bfd *abfd, struct bfd_link_info *info,
			     asection *sec, const Elf_Internal_Rela *relocs)
{
  struct _bfd_ajit_elf_link_hash_table *htab;
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  const Elf_Internal_Rela *rel;
  const Elf_Internal_Rela *rel_end;
  asection *sreloc;
  int num_relocs;
  bfd_boolean checked_tlsgd = FALSE;

  if (info->relocatable)
    return TRUE;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);
  symtab_hdr = &elf_symtab_hdr (abfd);
  sym_hashes = elf_sym_hashes (abfd);

  sreloc = NULL;

  if (ABI_64_P (abfd))
    num_relocs = NUM_SHDR_ENTRIES (_bfd_elf_single_rel_hdr (sec));
  else
    num_relocs = sec->reloc_count;

  BFD_ASSERT (is_ajit_elf (abfd) || num_relocs == 0);

  if (htab->elf.dynobj == NULL)
    htab->elf.dynobj = abfd;
  if (!create_ifunc_sections (htab->elf.dynobj, info))
    return FALSE;

  rel_end = relocs + num_relocs;
  for (rel = relocs; rel < rel_end; rel++)
    {
      unsigned int r_type;
      unsigned long r_symndx;
      struct elf_link_hash_entry *h;
      Elf_Internal_Sym *isym;

      r_symndx = AJIT_ELF_R_SYMNDX (htab, rel->r_info);
      r_type = AJIT_ELF_R_TYPE (rel->r_info);

      if (r_symndx >= NUM_SHDR_ENTRIES (symtab_hdr))
	{
	  (*_bfd_error_handler) (_("%B: bad symbol index: %d"),
				 abfd, r_symndx);
	  return FALSE;
	}

      isym = NULL;
      if (r_symndx < symtab_hdr->sh_info)
	{
	  /* A local symbol.  */
	  isym = bfd_sym_from_r_symndx (&htab->sym_cache,
					abfd, r_symndx);
	  if (isym == NULL)
	    return FALSE;

	  /* Check relocation against local STT_GNU_IFUNC symbol.  */
	  if (ELF_ST_TYPE (isym->st_info) == STT_GNU_IFUNC)
	    {
	      h = elf_ajit_get_local_sym_hash (htab, abfd, rel,
						TRUE);
	      if (h == NULL)
		return FALSE;
	      
	      /* Fake a STT_GNU_IFUNC symbol.  */
	      h->type = STT_GNU_IFUNC;
	      h->def_regular = 1;
	      h->ref_regular = 1;
	      h->forced_local = 1;
	      h->root.type = bfd_link_hash_defined;
	    }
	  else
	    h = NULL;
	}
      else
	{
	  h = sym_hashes[r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct elf_link_hash_entry *) h->root.u.i.link;
	}

      if (h && h->type == STT_GNU_IFUNC)
	{
	  if (h->def_regular)
	    {
	      h->ref_regular = 1;
	      h->plt.refcount += 1;
	    }
	}

      /* Compatibility with old R_AJIT_REV32 reloc conflicting
	 with R_AJIT_TLS_GD_HI22.  */
      if (! ABI_64_P (abfd) && ! checked_tlsgd)
	switch (r_type)
	  {
	  case R_AJIT_TLS_GD_HI22:
	    {
	      const Elf_Internal_Rela *relt;

	      for (relt = rel + 1; relt < rel_end; relt++)
		if (ELF32_R_TYPE (relt->r_info) == R_AJIT_TLS_GD_LO10
		    || ELF32_R_TYPE (relt->r_info) == R_AJIT_TLS_GD_ADD
		    || ELF32_R_TYPE (relt->r_info) == R_AJIT_TLS_GD_CALL)
		  break;
	      checked_tlsgd = TRUE;
	      _bfd_ajit_elf_tdata (abfd)->has_tlsgd = relt < rel_end;
	    }
	    break;
	  case R_AJIT_TLS_GD_LO10:
	  case R_AJIT_TLS_GD_ADD:
	  case R_AJIT_TLS_GD_CALL:
	    checked_tlsgd = TRUE;
	    _bfd_ajit_elf_tdata (abfd)->has_tlsgd = TRUE;
	    break;
	  }

      r_type = ajit_elf_tls_transition (info, abfd, r_type, h == NULL);
      switch (r_type)
	{
	case R_AJIT_TLS_LDM_HI22:
	case R_AJIT_TLS_LDM_LO10:
	  htab->tls_ldm_got.refcount += 1;
	  break;

	case R_AJIT_TLS_LE_HIX22:
	case R_AJIT_TLS_LE_LOX10:
	  if (info->shared)
	    goto r_ajit_plt32;
	  break;

	case R_AJIT_TLS_IE_HI22:
	case R_AJIT_TLS_IE_LO10:
	  if (info->shared)
	    info->flags |= DF_STATIC_TLS;
	  /* Fall through */

	case R_AJIT_GOT10:
	case R_AJIT_GOT13:
	case R_AJIT_GOT22:
	case R_AJIT_GOTDATA_HIX22:
	case R_AJIT_GOTDATA_LOX10:
	case R_AJIT_GOTDATA_OP_HIX22:
	case R_AJIT_GOTDATA_OP_LOX10:
	case R_AJIT_TLS_GD_HI22:
	case R_AJIT_TLS_GD_LO10:
	  /* This symbol requires a global offset table entry.  */
	  {
	    int tls_type, old_tls_type;

	    switch (r_type)
	      {
	      default:
	      case R_AJIT_GOT10:
	      case R_AJIT_GOT13:
	      case R_AJIT_GOT22:
	      case R_AJIT_GOTDATA_OP_HIX22:
	      case R_AJIT_GOTDATA_OP_LOX10:
		tls_type = GOT_NORMAL;
		break;
	      case R_AJIT_TLS_GD_HI22:
	      case R_AJIT_TLS_GD_LO10:
		tls_type = GOT_TLS_GD;
		break;
	      case R_AJIT_TLS_IE_HI22:
	      case R_AJIT_TLS_IE_LO10:
		tls_type = GOT_TLS_IE;
		break;
	      }

	    if (h != NULL)
	      {
		h->got.refcount += 1;
		old_tls_type = _bfd_ajit_elf_hash_entry(h)->tls_type;
	      }
	    else
	      {
		bfd_signed_vma *local_got_refcounts;

		/* This is a global offset table entry for a local symbol.  */
		local_got_refcounts = elf_local_got_refcounts (abfd);
		if (local_got_refcounts == NULL)
		  {
		    bfd_size_type size;

		    size = symtab_hdr->sh_info;
		    size *= (sizeof (bfd_signed_vma) + sizeof(char));
		    local_got_refcounts = ((bfd_signed_vma *)
					   bfd_zalloc (abfd, size));
		    if (local_got_refcounts == NULL)
		      return FALSE;
		    elf_local_got_refcounts (abfd) = local_got_refcounts;
		    _bfd_ajit_elf_local_got_tls_type (abfd)
		      = (char *) (local_got_refcounts + symtab_hdr->sh_info);
		  }
		switch (r_type)
		  {
		  case R_AJIT_GOTDATA_OP_HIX22:
		  case R_AJIT_GOTDATA_OP_LOX10:
		    break;

		  default:
		    local_got_refcounts[r_symndx] += 1;
		    break;
		  }
		old_tls_type = _bfd_ajit_elf_local_got_tls_type (abfd) [r_symndx];
	      }

	    /* If a TLS symbol is accessed using IE at least once,
	       there is no point to use dynamic model for it.  */
	    if (old_tls_type != tls_type && old_tls_type != GOT_UNKNOWN
		&& (old_tls_type != GOT_TLS_GD
		    || tls_type != GOT_TLS_IE))
	      {
		if (old_tls_type == GOT_TLS_IE && tls_type == GOT_TLS_GD)
		  tls_type = old_tls_type;
		else
		  {
		    (*_bfd_error_handler)
		      (_("%B: `%s' accessed both as normal and thread local symbol"),
		       abfd, h ? h->root.root.string : "<local>");
		    return FALSE;
		  }
	      }

	    if (old_tls_type != tls_type)
	      {
		if (h != NULL)
		  _bfd_ajit_elf_hash_entry (h)->tls_type = tls_type;
		else
		  _bfd_ajit_elf_local_got_tls_type (abfd) [r_symndx] = tls_type;
	      }
	  }

	  if (htab->elf.sgot == NULL)
	    {
	      if (!_bfd_elf_create_got_section (htab->elf.dynobj, info))
		return FALSE;
	    }
	  break;

	case R_AJIT_TLS_GD_CALL:
	case R_AJIT_TLS_LDM_CALL:
	  if (info->shared)
	    {
	      /* These are basically R_AJIT_TLS_WPLT30 relocs against
		 __tls_get_addr.  */
	      struct bfd_link_hash_entry *bh = NULL;
	      if (! _bfd_generic_link_add_one_symbol (info, abfd,
						      "__tls_get_addr", 0,
						      bfd_und_section_ptr, 0,
						      NULL, FALSE, FALSE,
						      &bh))
		return FALSE;
	      h = (struct elf_link_hash_entry *) bh;
	    }
	  else
	    break;
	  /* Fall through */

	case R_AJIT_PLT32:
	case R_AJIT_WPLT30:
	case R_AJIT_HIPLT22:
	case R_AJIT_LOPLT10:
	case R_AJIT_PCPLT32:
	case R_AJIT_PCPLT22:
	case R_AJIT_PCPLT10:
	case R_AJIT_PLT64:
	  /* This symbol requires a procedure linkage table entry.  We
	     actually build the entry in adjust_dynamic_symbol,
	     because this might be a case of linking PIC code without
	     linking in any dynamic objects, in which case we don't
	     need to generate a procedure linkage table after all.  */

	  if (h == NULL)
	    {
	      if (! ABI_64_P (abfd))
		{
		  /* The Solaris native assembler will generate a WPLT30
		     reloc for a local symbol if you assemble a call from
		     one section to another when using -K pic.  We treat
		     it as WDISP30.  */
		  if (ELF32_R_TYPE (rel->r_info) == R_AJIT_PLT32)
		    goto r_ajit_plt32;
		  break;
		}
	      /* PR 7027: We need similar behaviour for 64-bit binaries.  */
	      else if (r_type == R_AJIT_WPLT30)
		break;

	      /* It does not make sense to have a procedure linkage
                 table entry for a local symbol.  */
	      bfd_set_error (bfd_error_bad_value);
	      return FALSE;
	    }

	  h->needs_plt = 1;

	  {
	    int this_r_type;

	    this_r_type = AJIT_ELF_R_TYPE (rel->r_info);
	    if (this_r_type == R_AJIT_PLT32
		|| this_r_type == R_AJIT_PLT64)
	      goto r_ajit_plt32;
	  }
	  h->plt.refcount += 1;
	  break;

	case R_AJIT_PC10:
	case R_AJIT_PC22:
	case R_AJIT_PC_HH22:
	case R_AJIT_PC_HM10:
	case R_AJIT_PC_LM22:
	  if (h != NULL)
	    h->non_got_ref = 1;

	  if (h != NULL
	      && strcmp (h->root.root.string, "_GLOBAL_OFFSET_TABLE_") == 0)
	    break;
	  /* Fall through.  */

	case R_AJIT_DISP8:
	case R_AJIT_DISP16:
	case R_AJIT_DISP32:
	case R_AJIT_DISP64:
	case R_AJIT_WDISP30:
	case R_AJIT_WDISP22:
	case R_AJIT_WDISP19:
	case R_AJIT_WDISP16:
	case R_AJIT_8:
	case R_AJIT_16:
	case R_AJIT_32:
	case R_AJIT_HI22:
	case R_AJIT_22:
	case R_AJIT_13:
	case R_AJIT_LO10:
	case R_AJIT_UA16:
	case R_AJIT_UA32:
	case R_AJIT_10:
	case R_AJIT_11:
	case R_AJIT_64:
	case R_AJIT_OLO10:
	case R_AJIT_HH22:
	case R_AJIT_HM10:
	case R_AJIT_LM22:
	case R_AJIT_7:
	case R_AJIT_5:
	case R_AJIT_6:
	case R_AJIT_HIX22:
	case R_AJIT_LOX10:
	case R_AJIT_H44:
	case R_AJIT_M44:
	case R_AJIT_L44:
	case R_AJIT_UA64:
	  if (h != NULL)
	    h->non_got_ref = 1;

	r_ajit_plt32:
	  if (h != NULL && !info->shared)
	    {
	      /* We may need a .plt entry if the function this reloc
		 refers to is in a shared lib.  */
	      h->plt.refcount += 1;
	    }

	  /* If we are creating a shared library, and this is a reloc
	     against a global symbol, or a non PC relative reloc
	     against a local symbol, then we need to copy the reloc
	     into the shared library.  However, if we are linking with
	     -Bsymbolic, we do not need to copy a reloc against a
	     global symbol which is defined in an object we are
	     including in the link (i.e., DEF_REGULAR is set).  At
	     this point we have not seen all the input files, so it is
	     possible that DEF_REGULAR is not set now but will be set
	     later (it is never cleared).  In case of a weak definition,
	     DEF_REGULAR may be cleared later by a strong definition in
	     a shared library.  We account for that possibility below by
	     storing information in the relocs_copied field of the hash
	     table entry.  A similar situation occurs when creating
	     shared libraries and symbol visibility changes render the
	     symbol local.

	     If on the other hand, we are creating an executable, we
	     may need to keep relocations for symbols satisfied by a
	     dynamic library if we manage to avoid copy relocs for the
	     symbol.  */
	  if ((info->shared
	       && (sec->flags & SEC_ALLOC) != 0
	       && (! _bfd_ajit_elf_howto_table[r_type].pc_relative
		   || (h != NULL
		       && (! SYMBOLIC_BIND (info, h)
			   || h->root.type == bfd_link_hash_defweak
			   || !h->def_regular))))
	      || (!info->shared
		  && (sec->flags & SEC_ALLOC) != 0
		  && h != NULL
		  && (h->root.type == bfd_link_hash_defweak
		      || !h->def_regular))
	      || (!info->shared
		  && h != NULL
		  && h->type == STT_GNU_IFUNC))
	    {
	      struct _bfd_ajit_elf_dyn_relocs *p;
	      struct _bfd_ajit_elf_dyn_relocs **head;

	      /* When creating a shared object, we must copy these
		 relocs into the output file.  We create a reloc
		 section in dynobj and make room for the reloc.  */
	      if (sreloc == NULL)
		{
		  sreloc = _bfd_elf_make_dynamic_reloc_section
		    (sec, htab->elf.dynobj, htab->word_align_power,
		     abfd, /*rela?*/ TRUE);

		  if (sreloc == NULL)
		    return FALSE;
		}

	      /* If this is a global symbol, we count the number of
		 relocations we need for this symbol.  */
	      if (h != NULL)
		head = &((struct _bfd_ajit_elf_link_hash_entry *) h)->dyn_relocs;
	      else
		{
		  /* Track dynamic relocs needed for local syms too.
		     We really need local syms available to do this
		     easily.  Oh well.  */
		  asection *s;
		  void *vpp;

		  BFD_ASSERT (isym != NULL);
		  s = bfd_section_from_elf_index (abfd, isym->st_shndx);
		  if (s == NULL)
		    s = sec;

		  vpp = &elf_section_data (s)->local_dynrel;
		  head = (struct _bfd_ajit_elf_dyn_relocs **) vpp;
		}

	      p = *head;
	      if (p == NULL || p->sec != sec)
		{
		  bfd_size_type amt = sizeof *p;
		  p = ((struct _bfd_ajit_elf_dyn_relocs *)
		       bfd_alloc (htab->elf.dynobj, amt));
		  if (p == NULL)
		    return FALSE;
		  p->next = *head;
		  *head = p;
		  p->sec = sec;
		  p->count = 0;
		  p->pc_count = 0;
		}

	      p->count += 1;
	      if (_bfd_ajit_elf_howto_table[r_type].pc_relative)
		p->pc_count += 1;
	    }

	  break;

	case R_AJIT_GNU_VTINHERIT:
	  if (!bfd_elf_gc_record_vtinherit (abfd, sec, h, rel->r_offset))
	    return FALSE;
	  break;

	case R_AJIT_GNU_VTENTRY:
	  BFD_ASSERT (h != NULL);
	  if (h != NULL
	      && !bfd_elf_gc_record_vtentry (abfd, sec, h, rel->r_addend))
	    return FALSE;
	  break;

	case R_AJIT_REGISTER:
	  /* Nothing to do.  */
	  break;

	default:
	  break;
	}
    }

  return TRUE;
}

asection *
_bfd_ajit_elf_gc_mark_hook (asection *sec,
			     struct bfd_link_info *info,
			     Elf_Internal_Rela *rel,
			     struct elf_link_hash_entry *h,
			     Elf_Internal_Sym *sym)
{
  if (h != NULL)
    switch (AJIT_ELF_R_TYPE (rel->r_info))
      {
      case R_AJIT_GNU_VTINHERIT:
      case R_AJIT_GNU_VTENTRY:
	return NULL;
      }

  return _bfd_elf_gc_mark_hook (sec, info, rel, h, sym);
}

static Elf_Internal_Rela *
ajit_elf_find_reloc_at_ofs (Elf_Internal_Rela *rel,
			     Elf_Internal_Rela *relend,
			     bfd_vma offset)
{
  while (rel < relend)
    {
      if (rel->r_offset == offset)
	return rel;
      rel++;
    }
  return NULL;
}

/* Update the got entry reference counts for the section being removed.  */
bfd_boolean
_bfd_ajit_elf_gc_sweep_hook (bfd *abfd, struct bfd_link_info *info,
			      asection *sec, const Elf_Internal_Rela *relocs)
{
  struct _bfd_ajit_elf_link_hash_table *htab;
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  bfd_signed_vma *local_got_refcounts;
  const Elf_Internal_Rela *rel, *relend;

  if (info->relocatable)
    return TRUE;

  BFD_ASSERT (is_ajit_elf (abfd) || sec->reloc_count == 0);

  elf_section_data (sec)->local_dynrel = NULL;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);
  symtab_hdr = &elf_symtab_hdr (abfd);
  sym_hashes = elf_sym_hashes (abfd);
  local_got_refcounts = elf_local_got_refcounts (abfd);

  relend = relocs + sec->reloc_count;
  for (rel = relocs; rel < relend; rel++)
    {
      unsigned long r_symndx;
      unsigned int r_type;
      struct elf_link_hash_entry *h = NULL;

      r_symndx = AJIT_ELF_R_SYMNDX (htab, rel->r_info);
      if (r_symndx >= symtab_hdr->sh_info)
	{
	  struct _bfd_ajit_elf_link_hash_entry *eh;
	  struct _bfd_ajit_elf_dyn_relocs **pp;
	  struct _bfd_ajit_elf_dyn_relocs *p;

	  h = sym_hashes[r_symndx - symtab_hdr->sh_info];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct elf_link_hash_entry *) h->root.u.i.link;
	  eh = (struct _bfd_ajit_elf_link_hash_entry *) h;
	  for (pp = &eh->dyn_relocs; (p = *pp) != NULL; pp = &p->next)
	    if (p->sec == sec)
	      {
		/* Everything must go for SEC.  */
		*pp = p->next;
		break;
	      }
	}

      r_type = AJIT_ELF_R_TYPE (rel->r_info);
      r_type = ajit_elf_tls_transition (info, abfd, r_type, h != NULL);
      switch (r_type)
	{
	case R_AJIT_TLS_LDM_HI22:
	case R_AJIT_TLS_LDM_LO10:
	  if (_bfd_ajit_elf_hash_table (info)->tls_ldm_got.refcount > 0)
	    _bfd_ajit_elf_hash_table (info)->tls_ldm_got.refcount -= 1;
	  break;

	case R_AJIT_TLS_GD_HI22:
	case R_AJIT_TLS_GD_LO10:
	case R_AJIT_TLS_IE_HI22:
	case R_AJIT_TLS_IE_LO10:
	case R_AJIT_GOT10:
	case R_AJIT_GOT13:
	case R_AJIT_GOT22:
	case R_AJIT_GOTDATA_HIX22:
	case R_AJIT_GOTDATA_LOX10:
	case R_AJIT_GOTDATA_OP_HIX22:
	case R_AJIT_GOTDATA_OP_LOX10:
	  if (h != NULL)
	    {
	      if (h->got.refcount > 0)
		h->got.refcount--;
	    }
	  else
	    {
	      switch (r_type)
		{
		case R_AJIT_GOTDATA_OP_HIX22:
		case R_AJIT_GOTDATA_OP_LOX10:
		  break;

		default:
		  if (local_got_refcounts[r_symndx] > 0)
		    local_got_refcounts[r_symndx]--;
		  break;
		}
	    }
	  break;

	case R_AJIT_PC10:
	case R_AJIT_PC22:
	case R_AJIT_PC_HH22:
	case R_AJIT_PC_HM10:
	case R_AJIT_PC_LM22:
	  if (h != NULL
	      && strcmp (h->root.root.string, "_GLOBAL_OFFSET_TABLE_") == 0)
	    break;
	  /* Fall through.  */

	case R_AJIT_DISP8:
	case R_AJIT_DISP16:
	case R_AJIT_DISP32:
	case R_AJIT_DISP64:
	case R_AJIT_WDISP30:
	case R_AJIT_WDISP22:
	case R_AJIT_WDISP19:
	case R_AJIT_WDISP16:
	case R_AJIT_8:
	case R_AJIT_16:
	case R_AJIT_32:
	case R_AJIT_HI22:
	case R_AJIT_22:
	case R_AJIT_13:
	case R_AJIT_LO10:
	case R_AJIT_UA16:
	case R_AJIT_UA32:
	case R_AJIT_PLT32:
	case R_AJIT_10:
	case R_AJIT_11:
	case R_AJIT_64:
	case R_AJIT_OLO10:
	case R_AJIT_HH22:
	case R_AJIT_HM10:
	case R_AJIT_LM22:
	case R_AJIT_7:
	case R_AJIT_5:
	case R_AJIT_6:
	case R_AJIT_HIX22:
	case R_AJIT_LOX10:
	case R_AJIT_H44:
	case R_AJIT_M44:
	case R_AJIT_L44:
	case R_AJIT_UA64:
	  if (info->shared)
	    break;
	  /* Fall through.  */

	case R_AJIT_WPLT30:
	  if (h != NULL)
	    {
	      if (h->plt.refcount > 0)
		h->plt.refcount--;
	    }
	  break;

	default:
	  break;
	}
    }

  return TRUE;
}

/* Adjust a symbol defined by a dynamic object and referenced by a
   regular object.  The current definition is in some section of the
   dynamic object, but we're not including those sections.  We have to
   change the definition to something the rest of the link can
   understand.  */

bfd_boolean
_bfd_ajit_elf_adjust_dynamic_symbol (struct bfd_link_info *info,
				     struct elf_link_hash_entry *h)
{
  struct _bfd_ajit_elf_link_hash_table *htab;
  struct _bfd_ajit_elf_link_hash_entry * eh;
  struct _bfd_ajit_elf_dyn_relocs *p;
  asection *s;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);

  /* Make sure we know what is going on here.  */
  BFD_ASSERT (htab->elf.dynobj != NULL
	      && (h->needs_plt
		  || h->type == STT_GNU_IFUNC
		  || h->u.weakdef != NULL
		  || (h->def_dynamic
		      && h->ref_regular
		      && !h->def_regular)));

  /* If this is a function, put it in the procedure linkage table.  We
     will fill in the contents of the procedure linkage table later
     (although we could actually do it here).  The STT_NOTYPE
     condition is a hack specifically for the Oracle libraries
     delivered for Solaris; for some inexplicable reason, they define
     some of their functions as STT_NOTYPE when they really should be
     STT_FUNC.  */
  if (h->type == STT_FUNC
      || h->type == STT_GNU_IFUNC
      || h->needs_plt
      || (h->type == STT_NOTYPE
	  && (h->root.type == bfd_link_hash_defined
	      || h->root.type == bfd_link_hash_defweak)
	  && (h->root.u.def.section->flags & SEC_CODE) != 0))
    {
      if (h->plt.refcount <= 0
	  || (h->type != STT_GNU_IFUNC
	      && (SYMBOL_CALLS_LOCAL (info, h)
		  || (ELF_ST_VISIBILITY (h->other) != STV_DEFAULT
		      && h->root.type == bfd_link_hash_undefweak))))
	{
	  /* This case can occur if we saw a WPLT30 reloc in an input
	     file, but the symbol was never referred to by a dynamic
	     object, or if all references were garbage collected.  In
	     such a case, we don't actually need to build a procedure
	     linkage table, and we can just do a WDISP30 reloc instead.  */
	  h->plt.offset = (bfd_vma) -1;
	  h->needs_plt = 0;
	}

      return TRUE;
    }
  else
    h->plt.offset = (bfd_vma) -1;

  /* If this is a weak symbol, and there is a real definition, the
     processor independent code will have arranged for us to see the
     real definition first, and we can just use the same value.  */
  if (h->u.weakdef != NULL)
    {
      BFD_ASSERT (h->u.weakdef->root.type == bfd_link_hash_defined
		  || h->u.weakdef->root.type == bfd_link_hash_defweak);
      h->root.u.def.section = h->u.weakdef->root.u.def.section;
      h->root.u.def.value = h->u.weakdef->root.u.def.value;
      return TRUE;
    }

  /* This is a reference to a symbol defined by a dynamic object which
     is not a function.  */

  /* If we are creating a shared library, we must presume that the
     only references to the symbol are via the global offset table.
     For such cases we need not do anything here; the relocations will
     be handled correctly by relocate_section.  */
  if (info->shared)
    return TRUE;

  /* If there are no references to this symbol that do not use the
     GOT, we don't need to generate a copy reloc.  */
  if (!h->non_got_ref)
    return TRUE;

  /* If -z nocopyreloc was given, we won't generate them either.  */
  if (info->nocopyreloc)
    {
      h->non_got_ref = 0;
      return TRUE;
    }

  eh = (struct _bfd_ajit_elf_link_hash_entry *) h;
  for (p = eh->dyn_relocs; p != NULL; p = p->next)
    {
      s = p->sec->output_section;
      if (s != NULL && (s->flags & SEC_READONLY) != 0)
	break;
    }

  /* If we didn't find any dynamic relocs in read-only sections, then
     we'll be keeping the dynamic relocs and avoiding the copy reloc.  */
  if (p == NULL)
    {
      h->non_got_ref = 0;
      return TRUE;
    }

  if (h->size == 0)
    {
      (*_bfd_error_handler) (_("dynamic variable `%s' is zero size"),
			     h->root.root.string);
      return TRUE;
    }

  /* We must allocate the symbol in our .dynbss section, which will
     become part of the .bss section of the executable.  There will be
     an entry for this symbol in the .dynsym section.  The dynamic
     object will contain position independent code, so all references
     from the dynamic object to this symbol will go through the global
     offset table.  The dynamic linker will use the .dynsym entry to
     determine the address it must put in the global offset table, so
     both the dynamic object and the regular object will refer to the
     same memory location for the variable.  */

  /* We must generate a R_AJIT_COPY reloc to tell the dynamic linker
     to copy the initial value out of the dynamic object and into the
     runtime process image.  We need to remember the offset into the
     .rel.bss section we are going to use.  */
  if ((h->root.u.def.section->flags & SEC_ALLOC) != 0)
    {
      htab->srelbss->size += AJIT_ELF_RELA_BYTES (htab);
      h->needs_copy = 1;
    }

  s = htab->sdynbss;

  return _bfd_elf_adjust_dynamic_copy (h, s);
}

/* Allocate space in .plt, .got and associated reloc sections for
   dynamic relocs.  */

static bfd_boolean
allocate_dynrelocs (struct elf_link_hash_entry *h, PTR inf)
{
  struct bfd_link_info *info;
  struct _bfd_ajit_elf_link_hash_table *htab;
  struct _bfd_ajit_elf_link_hash_entry *eh;
  struct _bfd_ajit_elf_dyn_relocs *p;

  if (h->root.type == bfd_link_hash_indirect)
    return TRUE;

  info = (struct bfd_link_info *) inf;
  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);

  if ((htab->elf.dynamic_sections_created
       && h->plt.refcount > 0)
      || (h->type == STT_GNU_IFUNC
	  && h->def_regular
	  && h->ref_regular))
    {
      /* Make sure this symbol is output as a dynamic symbol.
	 Undefined weak syms won't yet be marked as dynamic.  */
      if (h->dynindx == -1
	  && !h->forced_local)
	{
	  if (! bfd_elf_link_record_dynamic_symbol (info, h))
	    return FALSE;
	}

      if (WILL_CALL_FINISH_DYNAMIC_SYMBOL (1, info->shared, h)
	  || (h->type == STT_GNU_IFUNC
	      && h->def_regular))
	{
	  asection *s = htab->elf.splt;

	  if (s == NULL)
	    s = htab->elf.iplt;

	  /* Allocate room for the header.  */
	  if (s->size == 0)
	    {
	      s->size = htab->plt_header_size;

	      /* Allocate space for the .rela.plt.unloaded relocations.  */
	      if (htab->is_vxworks && !info->shared)
		htab->srelplt2->size = sizeof (Elf32_External_Rela) * 2;
	    }

	  /* The procedure linkage table size is bounded by the magnitude
	     of the offset we can describe in the entry.  */
	  if (s->size >= (AJIT_ELF_WORD_BYTES(htab) == 8 ?
			  (((bfd_vma)1 << 31) << 1) : 0x400000))
	    {
	      bfd_set_error (bfd_error_bad_value);
	      return FALSE;
	    }

	  if (AJIT_ELF_WORD_BYTES(htab) == 8
	      && s->size >= PLT64_LARGE_THRESHOLD * PLT64_ENTRY_SIZE)
	    {
	      bfd_vma off = s->size - PLT64_LARGE_THRESHOLD * PLT64_ENTRY_SIZE;


	      off = (off % (160 * PLT64_ENTRY_SIZE)) / PLT64_ENTRY_SIZE;

	      h->plt.offset = (s->size - (off * 8));
	    }
	  else
	    h->plt.offset = s->size;

	  /* If this symbol is not defined in a regular file, and we are
	     not generating a shared library, then set the symbol to this
	     location in the .plt.  This is required to make function
	     pointers compare as equal between the normal executable and
	     the shared library.  */
	  if (! info->shared
	      && !h->def_regular)
	    {
	      h->root.u.def.section = s;
	      h->root.u.def.value = h->plt.offset;
	    }

	  /* Make room for this entry.  */
	  s->size += htab->plt_entry_size;

	  /* We also need to make an entry in the .rela.plt section.  */
	  if (s == htab->elf.splt)
	    htab->elf.srelplt->size += AJIT_ELF_RELA_BYTES (htab);
	  else
	    htab->elf.irelplt->size += AJIT_ELF_RELA_BYTES (htab);

	  if (htab->is_vxworks)
	    {
	      /* Allocate space for the .got.plt entry.  */
	      htab->elf.sgotplt->size += 4;

	      /* ...and for the .rela.plt.unloaded relocations.  */
	      if (!info->shared)
		htab->srelplt2->size += sizeof (Elf32_External_Rela) * 3;
	    }
	}
      else
	{
	  h->plt.offset = (bfd_vma) -1;
	  h->needs_plt = 0;
	}
    }
  else
    {
      h->plt.offset = (bfd_vma) -1;
      h->needs_plt = 0;
    }

  /* If R_AJIT_TLS_IE_{HI22,LO10} symbol is now local to the binary,
     make it a R_AJIT_TLS_LE_{HI22,LO10} requiring no TLS entry.  */
  if (h->got.refcount > 0
      && !info->shared
      && h->dynindx == -1
      && _bfd_ajit_elf_hash_entry(h)->tls_type == GOT_TLS_IE)
    h->got.offset = (bfd_vma) -1;
  else if (h->got.refcount > 0)
    {
      asection *s;
      bfd_boolean dyn;
      int tls_type = _bfd_ajit_elf_hash_entry(h)->tls_type;

      /* Make sure this symbol is output as a dynamic symbol.
	 Undefined weak syms won't yet be marked as dynamic.  */
      if (h->dynindx == -1
	  && !h->forced_local)
	{
	  if (! bfd_elf_link_record_dynamic_symbol (info, h))
	    return FALSE;
	}

      s = htab->elf.sgot;
      h->got.offset = s->size;
      s->size += AJIT_ELF_WORD_BYTES (htab);
      /* R_AJIT_TLS_GD_HI{22,LO10} needs 2 consecutive GOT slots.  */
      if (tls_type == GOT_TLS_GD)
	s->size += AJIT_ELF_WORD_BYTES (htab);
      dyn = htab->elf.dynamic_sections_created;
      /* R_AJIT_TLS_IE_{HI22,LO10} needs one dynamic relocation,
	 R_AJIT_TLS_GD_{HI22,LO10} needs one if local symbol and two if
	 global.  */
      if ((tls_type == GOT_TLS_GD && h->dynindx == -1)
	  || tls_type == GOT_TLS_IE
	  || h->type == STT_GNU_IFUNC)
	htab->elf.srelgot->size += AJIT_ELF_RELA_BYTES (htab);
      else if (tls_type == GOT_TLS_GD)
	htab->elf.srelgot->size += 2 * AJIT_ELF_RELA_BYTES (htab);
      else if (WILL_CALL_FINISH_DYNAMIC_SYMBOL (dyn, info->shared, h))
	htab->elf.srelgot->size += AJIT_ELF_RELA_BYTES (htab);
    }
  else
    h->got.offset = (bfd_vma) -1;

  eh = (struct _bfd_ajit_elf_link_hash_entry *) h;
  if (eh->dyn_relocs == NULL)
    return TRUE;

  /* In the shared -Bsymbolic case, discard space allocated for
     dynamic pc-relative relocs against symbols which turn out to be
     defined in regular objects.  For the normal shared case, discard
     space for pc-relative relocs that have become local due to symbol
     visibility changes.  */

  if (info->shared)
    {
      if (SYMBOL_CALLS_LOCAL (info, h))
	{
	  struct _bfd_ajit_elf_dyn_relocs **pp;

	  for (pp = &eh->dyn_relocs; (p = *pp) != NULL; )
	    {
	      p->count -= p->pc_count;
	      p->pc_count = 0;
	      if (p->count == 0)
		*pp = p->next;
	      else
		pp = &p->next;
	    }
	}

      if (htab->is_vxworks)
	{
	  struct _bfd_ajit_elf_dyn_relocs **pp;

	  for (pp = &eh->dyn_relocs; (p = *pp) != NULL; )
	    {
	      if (strcmp (p->sec->output_section->name, ".tls_vars") == 0)
		*pp = p->next;
	      else
		pp = &p->next;
	    }
	}

      /* Also discard relocs on undefined weak syms with non-default
	 visibility.  */
      if (eh->dyn_relocs != NULL
	  && h->root.type == bfd_link_hash_undefweak)
	{
	  if (ELF_ST_VISIBILITY (h->other) != STV_DEFAULT)
	    eh->dyn_relocs = NULL;

	  /* Make sure undefined weak symbols are output as a dynamic
	     symbol in PIEs.  */
	  else if (h->dynindx == -1
		   && !h->forced_local)
	    {
	      if (! bfd_elf_link_record_dynamic_symbol (info, h))
		return FALSE;
	    }
	}
    }
  else
    {
      /* For the non-shared case, discard space for relocs against
	 symbols which turn out to need copy relocs or are not
	 dynamic.  */

      if (!h->non_got_ref
	  && ((h->def_dynamic
	       && !h->def_regular)
	      || (htab->elf.dynamic_sections_created
		  && (h->root.type == bfd_link_hash_undefweak
		      || h->root.type == bfd_link_hash_undefined))))
	{
	  /* Make sure this symbol is output as a dynamic symbol.
	     Undefined weak syms won't yet be marked as dynamic.  */
	  if (h->dynindx == -1
	      && !h->forced_local)
	    {
	      if (! bfd_elf_link_record_dynamic_symbol (info, h))
		return FALSE;
	    }

	  /* If that succeeded, we know we'll be keeping all the
	     relocs.  */
	  if (h->dynindx != -1)
	    goto keep;
	}

      eh->dyn_relocs = NULL;

    keep: ;
    }

  /* Finally, allocate space.  */
  for (p = eh->dyn_relocs; p != NULL; p = p->next)
    {
      asection *sreloc = elf_section_data (p->sec)->sreloc;
      sreloc->size += p->count * AJIT_ELF_RELA_BYTES (htab);
    }

  return TRUE;
}

/* Allocate space in .plt, .got and associated reloc sections for
   local dynamic relocs.  */

static bfd_boolean
allocate_local_dynrelocs (void **slot, void *inf)
{
  struct elf_link_hash_entry *h
    = (struct elf_link_hash_entry *) *slot;

  if (h->type != STT_GNU_IFUNC
      || !h->def_regular
      || !h->ref_regular
      || !h->forced_local
      || h->root.type != bfd_link_hash_defined)
    abort ();

  return allocate_dynrelocs (h, inf);
}

/* Find any dynamic relocs that apply to read-only sections.  */

static bfd_boolean
readonly_dynrelocs (struct elf_link_hash_entry *h, PTR inf)
{
  struct _bfd_ajit_elf_link_hash_entry *eh;
  struct _bfd_ajit_elf_dyn_relocs *p;

  eh = (struct _bfd_ajit_elf_link_hash_entry *) h;
  for (p = eh->dyn_relocs; p != NULL; p = p->next)
    {
      asection *s = p->sec->output_section;

      if (s != NULL && (s->flags & SEC_READONLY) != 0)
	{
	  struct bfd_link_info *info = (struct bfd_link_info *) inf;

	  info->flags |= DF_TEXTREL;

	  /* Not an error, just cut short the traversal.  */
	  return FALSE;
	}
    }
  return TRUE;
}

/* Return true if the dynamic symbol for a given section should be
   omitted when creating a shared library.  */

bfd_boolean
_bfd_ajit_elf_omit_section_dynsym (bfd *output_bfd,
				    struct bfd_link_info *info,
				    asection *p)
{
  /* We keep the .got section symbol so that explicit relocations
     against the _GLOBAL_OFFSET_TABLE_ symbol emitted in PIC mode
     can be turned into relocations against the .got symbol.  */
  if (strcmp (p->name, ".got") == 0)
    return FALSE;

  return _bfd_elf_link_omit_section_dynsym (output_bfd, info, p);
}

/* Set the sizes of the dynamic sections.  */

bfd_boolean
_bfd_ajit_elf_size_dynamic_sections (bfd *output_bfd,
				      struct bfd_link_info *info)
{
  struct _bfd_ajit_elf_link_hash_table *htab;
  bfd *dynobj;
  asection *s;
  bfd *ibfd;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);
  dynobj = htab->elf.dynobj;
  BFD_ASSERT (dynobj != NULL);

  if (elf_hash_table (info)->dynamic_sections_created)
    {
      /* Set the contents of the .interp section to the interpreter.  */
      if (info->executable)
	{
	  s = bfd_get_section_by_name (dynobj, ".interp");
	  BFD_ASSERT (s != NULL);
	  s->size = htab->dynamic_interpreter_size;
	  s->contents = (unsigned char *) htab->dynamic_interpreter;
	}
    }

  /* Set up .got offsets for local syms, and space for local dynamic
     relocs.  */
  for (ibfd = info->input_bfds; ibfd != NULL; ibfd = ibfd->link_next)
    {
      bfd_signed_vma *local_got;
      bfd_signed_vma *end_local_got;
      char *local_tls_type;
      bfd_size_type locsymcount;
      Elf_Internal_Shdr *symtab_hdr;
      asection *srel;

      if (! is_ajit_elf (ibfd))
	continue;

      for (s = ibfd->sections; s != NULL; s = s->next)
	{
	  struct _bfd_ajit_elf_dyn_relocs *p;

	  for (p = elf_section_data (s)->local_dynrel; p != NULL; p = p->next)
	    {
	      if (!bfd_is_abs_section (p->sec)
		  && bfd_is_abs_section (p->sec->output_section))
		{
		  /* Input section has been discarded, either because
		     it is a copy of a linkonce section or due to
		     linker script /DISCARD/, so we'll be discarding
		     the relocs too.  */
		}
	      else if (htab->is_vxworks
		       && strcmp (p->sec->output_section->name,
				  ".tls_vars") == 0)
		{
		  /* Relocations in vxworks .tls_vars sections are
		     handled specially by the loader.  */
		}
	      else if (p->count != 0)
		{
		  srel = elf_section_data (p->sec)->sreloc;
		  if (!htab->elf.dynamic_sections_created)
		    srel = htab->elf.irelplt;
		  srel->size += p->count * AJIT_ELF_RELA_BYTES (htab);
		  if ((p->sec->output_section->flags & SEC_READONLY) != 0)
		    info->flags |= DF_TEXTREL;
		}
	    }
	}

      local_got = elf_local_got_refcounts (ibfd);
      if (!local_got)
	continue;

      symtab_hdr = &elf_symtab_hdr (ibfd);
      locsymcount = symtab_hdr->sh_info;
      end_local_got = local_got + locsymcount;
      local_tls_type = _bfd_ajit_elf_local_got_tls_type (ibfd);
      s = htab->elf.sgot;
      srel = htab->elf.srelgot;
      for (; local_got < end_local_got; ++local_got, ++local_tls_type)
	{
	  if (*local_got > 0)
	    {
	      *local_got = s->size;
	      s->size += AJIT_ELF_WORD_BYTES (htab);
	      if (*local_tls_type == GOT_TLS_GD)
		s->size += AJIT_ELF_WORD_BYTES (htab);
	      if (info->shared
		  || *local_tls_type == GOT_TLS_GD
		  || *local_tls_type == GOT_TLS_IE)
		srel->size += AJIT_ELF_RELA_BYTES (htab);
	    }
	  else
	    *local_got = (bfd_vma) -1;
	}
    }

  if (htab->tls_ldm_got.refcount > 0)
    {
      /* Allocate 2 got entries and 1 dynamic reloc for
	 R_AJIT_TLS_LDM_{HI22,LO10} relocs.  */
      htab->tls_ldm_got.offset = htab->elf.sgot->size;
      htab->elf.sgot->size += (2 * AJIT_ELF_WORD_BYTES (htab));
      htab->elf.srelgot->size += AJIT_ELF_RELA_BYTES (htab);
    }
  else
    htab->tls_ldm_got.offset = -1;

  /* Allocate global sym .plt and .got entries, and space for global
     sym dynamic relocs.  */
  elf_link_hash_traverse (&htab->elf, allocate_dynrelocs, (PTR) info);

  /* Allocate .plt and .got entries, and space for local symbols.  */
  htab_traverse (htab->loc_hash_table, allocate_local_dynrelocs, info);

  if (! ABI_64_P (output_bfd)
      && !htab->is_vxworks
      && elf_hash_table (info)->dynamic_sections_created)
    {
      /* Make space for the trailing nop in .plt.  */
      if (htab->elf.splt->size > 0)
	htab->elf.splt->size += 1 * AJIT_INSN_BYTES;

      /* If the .got section is more than 0x1000 bytes, we add
	 0x1000 to the value of _GLOBAL_OFFSET_TABLE_, so that 13
	 bit relocations have a greater chance of working.

	 FIXME: Make this optimization work for 64-bit too.  */
      if (htab->elf.sgot->size >= 0x1000
	  && elf_hash_table (info)->hgot->root.u.def.value == 0)
	elf_hash_table (info)->hgot->root.u.def.value = 0x1000;
    }

  /* The check_relocs and adjust_dynamic_symbol entry points have
     determined the sizes of the various dynamic sections.  Allocate
     memory for them.  */
  for (s = dynobj->sections; s != NULL; s = s->next)
    {
      if ((s->flags & SEC_LINKER_CREATED) == 0)
	continue;

      if (s == htab->elf.splt
	  || s == htab->elf.sgot
	  || s == htab->sdynbss
	  || s == htab->elf.iplt
	  || s == htab->elf.sgotplt)
	{
	  /* Strip this section if we don't need it; see the
	     comment below.  */
	}
      else if (CONST_STRNEQ (s->name, ".rela"))
	{
	  if (s->size != 0)
	    {
	      /* We use the reloc_count field as a counter if we need
		 to copy relocs into the output file.  */
	      s->reloc_count = 0;
	    }
	}
      else
	{
	  /* It's not one of our sections.  */
	  continue;
	}

      if (s->size == 0)
	{
	  /* If we don't need this section, strip it from the
	     output file.  This is mostly to handle .rela.bss and
	     .rela.plt.  We must create both sections in
	     create_dynamic_sections, because they must be created
	     before the linker maps input sections to output
	     sections.  The linker does that before
	     adjust_dynamic_symbol is called, and it is that
	     function which decides whether anything needs to go
	     into these sections.  */
	  s->flags |= SEC_EXCLUDE;
	  continue;
	}

      if ((s->flags & SEC_HAS_CONTENTS) == 0)
	continue;

      /* Allocate memory for the section contents.  Zero the memory
	 for the benefit of .rela.plt, which has 4 unused entries
	 at the beginning, and we don't want garbage.  */
      s->contents = (bfd_byte *) bfd_zalloc (dynobj, s->size);
      if (s->contents == NULL)
	return FALSE;
    }

  if (elf_hash_table (info)->dynamic_sections_created)
    {
      /* Add some entries to the .dynamic section.  We fill in the
	 values later, in _bfd_ajit_elf_finish_dynamic_sections, but we
	 must add the entries now so that we get the correct size for
	 the .dynamic section.  The DT_DEBUG entry is filled in by the
	 dynamic linker and used by the debugger.  */
#define add_dynamic_entry(TAG, VAL) \
  _bfd_elf_add_dynamic_entry (info, TAG, VAL)

      if (info->executable)
	{
	  if (!add_dynamic_entry (DT_DEBUG, 0))
	    return FALSE;
	}

      if (htab->elf.srelplt->size != 0)
	{
	  if (!add_dynamic_entry (DT_PLTGOT, 0)
	      || !add_dynamic_entry (DT_PLTRELSZ, 0)
	      || !add_dynamic_entry (DT_PLTREL, DT_RELA)
	      || !add_dynamic_entry (DT_JMPREL, 0))
	    return FALSE;
	}

      if (!add_dynamic_entry (DT_RELA, 0)
	  || !add_dynamic_entry (DT_RELASZ, 0)
	  || !add_dynamic_entry (DT_RELAENT,
				 AJIT_ELF_RELA_BYTES (htab)))
	return FALSE;

      /* If any dynamic relocs apply to a read-only section,
	 then we need a DT_TEXTREL entry.  */
      if ((info->flags & DF_TEXTREL) == 0)
	elf_link_hash_traverse (&htab->elf, readonly_dynrelocs,
				(PTR) info);

      if (info->flags & DF_TEXTREL)
	{
	  if (!add_dynamic_entry (DT_TEXTREL, 0))
	    return FALSE;
	}

      if (ABI_64_P (output_bfd))
	{
	  int reg;
	  struct _bfd_ajit_elf_app_reg * app_regs;
	  struct elf_strtab_hash *dynstr;
	  struct elf_link_hash_table *eht = elf_hash_table (info);

	  /* Add dynamic STT_REGISTER symbols and corresponding DT_AJIT_REGISTER
	     entries if needed.  */
	  app_regs = _bfd_ajit_elf_hash_table (info)->app_regs;
	  dynstr = eht->dynstr;

	  for (reg = 0; reg < 4; reg++)
	    if (app_regs [reg].name != NULL)
	      {
		struct elf_link_local_dynamic_entry *entry, *e;

		if (!add_dynamic_entry (DT_AJIT_REGISTER, 0))
		  return FALSE;

		entry = (struct elf_link_local_dynamic_entry *)
		  bfd_hash_allocate (&info->hash->table, sizeof (*entry));
		if (entry == NULL)
		  return FALSE;

		/* We cheat here a little bit: the symbol will not be local, so we
		   put it at the end of the dynlocal linked list.  We will fix it
		   later on, as we have to fix other fields anyway.  */
		entry->isym.st_value = reg < 2 ? reg + 2 : reg + 4;
		entry->isym.st_size = 0;
		if (*app_regs [reg].name != '\0')
		  entry->isym.st_name
		    = _bfd_elf_strtab_add (dynstr, app_regs[reg].name, FALSE);
		else
		  entry->isym.st_name = 0;
		entry->isym.st_other = 0;
		entry->isym.st_info = ELF_ST_INFO (app_regs [reg].bind,
						   STT_REGISTER);
		entry->isym.st_shndx = app_regs [reg].shndx;
		entry->isym.st_target_internal = 0;
		entry->next = NULL;
		entry->input_bfd = output_bfd;
		entry->input_indx = -1;

		if (eht->dynlocal == NULL)
		  eht->dynlocal = entry;
		else
		  {
		    for (e = eht->dynlocal; e->next; e = e->next)
		      ;
		    e->next = entry;
		  }
		eht->dynsymcount++;
	      }
	}
      if (htab->is_vxworks
	  && !elf_vxworks_add_dynamic_entries (output_bfd, info))
	return FALSE;
    }
#undef add_dynamic_entry

  return TRUE;
}

bfd_boolean
_bfd_ajit_elf_new_section_hook (bfd *abfd, asection *sec)
{
  if (!sec->used_by_bfd)
    {
      struct _bfd_ajit_elf_section_data *sdata;
      bfd_size_type amt = sizeof (*sdata);

      sdata = bfd_zalloc (abfd, amt);
      if (sdata == NULL)
	return FALSE;
      sec->used_by_bfd = sdata;
    }

  return _bfd_elf_new_section_hook (abfd, sec);
}

bfd_boolean
_bfd_ajit_elf_relax_section (bfd *abfd ATTRIBUTE_UNUSED,
			      struct bfd_section *section,
			      struct bfd_link_info *link_info ATTRIBUTE_UNUSED,
			      bfd_boolean *again)
{
  if (link_info->relocatable)
    (*link_info->callbacks->einfo)
      (_("%P%F: --relax and -r may not be used together\n"));

  *again = FALSE;
  sec_do_relax (section) = 1;
  return TRUE;
}

/* Return the base VMA address which should be subtracted from real addresses
   when resolving @dtpoff relocation.
   This is PT_TLS segment p_vaddr.  */

static bfd_vma
dtpoff_base (struct bfd_link_info *info)
{
  /* If tls_sec is NULL, we should have signalled an error already.  */
  if (elf_hash_table (info)->tls_sec == NULL)
    return 0;
  return elf_hash_table (info)->tls_sec->vma;
}

/* Return the relocation value for @tpoff relocation
   if STT_TLS virtual address is ADDRESS.  */

static bfd_vma
tpoff (struct bfd_link_info *info, bfd_vma address)
{
  struct elf_link_hash_table *htab = elf_hash_table (info);
  const struct elf_backend_data *bed = get_elf_backend_data (info->output_bfd);
  bfd_vma static_tls_size;

  /* If tls_sec is NULL, we should have signalled an error already.  */
  if (htab->tls_sec == NULL)
    return 0;

  /* Consider special static TLS alignment requirements.  */
  static_tls_size = BFD_ALIGN (htab->tls_size, bed->static_tls_alignment);
  return address - static_tls_size - htab->tls_sec->vma;
}

/* Return the relocation value for a %gdop relocation.  */

static bfd_vma
gdopoff (struct bfd_link_info *info, bfd_vma address)
{
  struct elf_link_hash_table *htab = elf_hash_table (info);
  bfd_vma got_base;

  got_base = (htab->hgot->root.u.def.value
	      + htab->hgot->root.u.def.section->output_offset
	      + htab->hgot->root.u.def.section->output_section->vma);

  return address - got_base;
}

/* Relocate a AJIT ELF section.  */

bfd_boolean
_bfd_ajit_elf_relocate_section (bfd *output_bfd,
				 struct bfd_link_info *info,
				 bfd *input_bfd,
				 asection *input_section,
				 bfd_byte *contents,
				 Elf_Internal_Rela *relocs,
				 Elf_Internal_Sym *local_syms,
				 asection **local_sections)
{
  struct _bfd_ajit_elf_link_hash_table *htab;
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  bfd_vma *local_got_offsets;
  bfd_vma got_base;
  asection *sreloc;
  Elf_Internal_Rela *rel;
  Elf_Internal_Rela *relend;
  int num_relocs;
  bfd_boolean is_vxworks_tls;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);
  symtab_hdr = &elf_symtab_hdr (input_bfd);
  sym_hashes = elf_sym_hashes (input_bfd);
  local_got_offsets = elf_local_got_offsets (input_bfd);

  if (elf_hash_table (info)->hgot == NULL)
    got_base = 0;
  else
    got_base = elf_hash_table (info)->hgot->root.u.def.value;

  sreloc = elf_section_data (input_section)->sreloc;
  /* We have to handle relocations in vxworks .tls_vars sections
     specially, because the dynamic loader is 'weird'.  */
  is_vxworks_tls = (htab->is_vxworks && info->shared
		    && !strcmp (input_section->output_section->name,
				".tls_vars"));

  rel = relocs;
  if (ABI_64_P (output_bfd))
    num_relocs = NUM_SHDR_ENTRIES (_bfd_elf_single_rel_hdr (input_section));
  else
    num_relocs = input_section->reloc_count;
  relend = relocs + num_relocs;
  for (; rel < relend; rel++)
    {
      int r_type, tls_type;
      reloc_howto_type *howto;
      unsigned long r_symndx;
      struct elf_link_hash_entry *h;
      Elf_Internal_Sym *sym;
      asection *sec;
      bfd_vma relocation, off;
      bfd_reloc_status_type r;
      bfd_boolean is_plt = FALSE;
      bfd_boolean unresolved_reloc;

      r_type = AJIT_ELF_R_TYPE (rel->r_info);
      if (r_type == R_AJIT_GNU_VTINHERIT
	  || r_type == R_AJIT_GNU_VTENTRY)
	continue;

      if (r_type < 0 || r_type >= (int) R_AJIT_max_std)
	{
	  bfd_set_error (bfd_error_bad_value);
	  return FALSE;
	}
      howto = _bfd_ajit_elf_howto_table + r_type;

      r_symndx = AJIT_ELF_R_SYMNDX (htab, rel->r_info);
      h = NULL;
      sym = NULL;
      sec = NULL;
      unresolved_reloc = FALSE;
      if (r_symndx < symtab_hdr->sh_info)
	{
	  sym = local_syms + r_symndx;
	  sec = local_sections[r_symndx];
	  relocation = _bfd_elf_rela_local_sym (output_bfd, sym, &sec, rel);

	  if (!info->relocatable
	      && ELF_ST_TYPE (sym->st_info) == STT_GNU_IFUNC)
	    {
	      /* Relocate against local STT_GNU_IFUNC symbol.  */
	      h = elf_ajit_get_local_sym_hash (htab, input_bfd,
						rel, FALSE);
	      if (h == NULL)
		abort ();

	      /* Set STT_GNU_IFUNC symbol value.  */ 
	      h->root.u.def.value = sym->st_value;
	      h->root.u.def.section = sec;
	    }
	}
      else
	{
	  bfd_boolean warned;

	  RELOC_FOR_GLOBAL_SYMBOL (info, input_bfd, input_section, rel,
				   r_symndx, symtab_hdr, sym_hashes,
				   h, sec, relocation,
				   unresolved_reloc, warned);
	  if (warned)
	    {
	      /* To avoid generating warning messages about truncated
		 relocations, set the relocation's address to be the same as
		 the start of this section.  */
	      if (input_section->output_section != NULL)
		relocation = input_section->output_section->vma;
	      else
		relocation = 0;
	    }
	}

      if (sec != NULL && elf_discarded_section (sec))
	RELOC_AGAINST_DISCARDED_SECTION (info, input_bfd, input_section,
					 rel, relend, howto, contents);

      if (info->relocatable)
	continue;

      if (h != NULL
	  && h->type == STT_GNU_IFUNC
	  && h->def_regular)
	{
	  asection *plt_sec;
	  const char *name;

	  if ((input_section->flags & SEC_ALLOC) == 0
	      || h->plt.offset == (bfd_vma) -1)
	    abort ();

	  plt_sec = htab->elf.splt;
	  if (! plt_sec)
	    plt_sec =htab->elf.iplt;

	  switch (r_type)
	    {
	    case R_AJIT_GOTDATA_OP:
	      continue;

	    case R_AJIT_GOTDATA_OP_HIX22:
	    case R_AJIT_GOTDATA_OP_LOX10:
	      r_type = (r_type == R_AJIT_GOTDATA_OP_HIX22
			? R_AJIT_GOT22
			: R_AJIT_GOT10);
	      howto = _bfd_ajit_elf_howto_table + r_type;
	      /* Fall through.  */

	    case R_AJIT_GOT10:
	    case R_AJIT_GOT13:
	    case R_AJIT_GOT22:
	      if (htab->elf.sgot == NULL)
		abort ();
	      off = h->got.offset;
	      if (off == (bfd_vma) -1)
		abort();
	      relocation = htab->elf.sgot->output_offset + off - got_base;
	      goto do_relocation;

	    case R_AJIT_WPLT30:
	    case R_AJIT_WDISP30:
	      relocation = (plt_sec->output_section->vma
			    + plt_sec->output_offset + h->plt.offset);
	      goto do_relocation;

	    case R_AJIT_32:
	    case R_AJIT_64:
	      if (info->shared && h->non_got_ref)
		{
		  Elf_Internal_Rela outrel;
		  bfd_vma offset;

		  offset = _bfd_elf_section_offset (output_bfd, info,
						    input_section,
						    rel->r_offset);
		  if (offset == (bfd_vma) -1
		      || offset == (bfd_vma) -2)
		    abort();

		  outrel.r_offset = (input_section->output_section->vma
				     + input_section->output_offset
				     + offset);

		  if (h->dynindx == -1
		      || h->forced_local
		      || info->executable)
		    {
		      outrel.r_info = AJIT_ELF_R_INFO (htab, NULL,
							0, R_AJIT_IRELATIVE);
		      outrel.r_addend = relocation + rel->r_addend;
		    }
		  else
		    {
		      if (h->dynindx == -1)
			abort();
		      outrel.r_info = AJIT_ELF_R_INFO (htab, rel, h->dynindx, r_type);
		      outrel.r_addend = rel->r_addend;
		    }

		  ajit_elf_append_rela (output_bfd, sreloc, &outrel);
		  continue;
		}

	      relocation = (plt_sec->output_section->vma
			    + plt_sec->output_offset + h->plt.offset);
	      goto do_relocation;

	    case R_AJIT_HI22:
	    case R_AJIT_LO10:
	      /* We should only see such relocs in static links.  */
	      if (info->shared)
		abort();
	      relocation = (plt_sec->output_section->vma
			    + plt_sec->output_offset + h->plt.offset);
	      goto do_relocation;

	    default:
	      if (h->root.root.string)
		name = h->root.root.string;
	      else
		name = bfd_elf_sym_name (input_bfd, symtab_hdr, sym,
					 NULL);
	      (*_bfd_error_handler)
		(_("%B: relocation %s against STT_GNU_IFUNC "
		   "symbol `%s' isn't handled by %s"), input_bfd,
		 _bfd_ajit_elf_howto_table[r_type].name,
		 name, __FUNCTION__);
	      bfd_set_error (bfd_error_bad_value);
	      return FALSE;
	    }
	}

      switch (r_type)
	{
	case R_AJIT_GOTDATA_OP_HIX22:
	case R_AJIT_GOTDATA_OP_LOX10:
	  if (SYMBOL_REFERENCES_LOCAL (info, h))
	    r_type = (r_type == R_AJIT_GOTDATA_OP_HIX22
		      ? R_AJIT_GOTDATA_HIX22
		      : R_AJIT_GOTDATA_LOX10);
	  else
	    r_type = (r_type == R_AJIT_GOTDATA_OP_HIX22
		      ? R_AJIT_GOT22
		      : R_AJIT_GOT10);
	  howto = _bfd_ajit_elf_howto_table + r_type;
	  break;

	case R_AJIT_GOTDATA_OP:
	  if (SYMBOL_REFERENCES_LOCAL (info, h))
	    {
	      bfd_vma insn = bfd_get_32 (input_bfd, contents + rel->r_offset);

	      /* {ld,ldx} [%rs1 + %rs2], %rd --> add %rs1, %rs2, %rd */
	      relocation = 0x80000000 | (insn & 0x3e07c01f);
	      bfd_put_32 (output_bfd, relocation, contents + rel->r_offset);
	    }
	  continue;
	}

      switch (r_type)
	{
	case R_AJIT_GOTDATA_HIX22:
	case R_AJIT_GOTDATA_LOX10:
	  relocation = gdopoff (info, relocation);
	  break;

	case R_AJIT_GOT10:
	case R_AJIT_GOT13:
	case R_AJIT_GOT22:
	  /* Relocation is to the entry for this symbol in the global
	     offset table.  */
	  if (htab->elf.sgot == NULL)
	    abort ();

	  if (h != NULL)
	    {
	      bfd_boolean dyn;

	      off = h->got.offset;
	      BFD_ASSERT (off != (bfd_vma) -1);
	      dyn = elf_hash_table (info)->dynamic_sections_created;

	      if (! WILL_CALL_FINISH_DYNAMIC_SYMBOL (dyn, info->shared, h)
		  || (info->shared
		      && SYMBOL_REFERENCES_LOCAL (info, h)))
		{
		  /* This is actually a static link, or it is a
		     -Bsymbolic link and the symbol is defined
		     locally, or the symbol was forced to be local
		     because of a version file.  We must initialize
		     this entry in the global offset table.  Since the
		     offset must always be a multiple of 8 for 64-bit
		     and 4 for 32-bit, we use the least significant bit
		     to record whether we have initialized it already.

		     When doing a dynamic link, we create a .rela.got
		     relocation entry to initialize the value.  This
		     is done in the finish_dynamic_symbol routine.  */
		  if ((off & 1) != 0)
		    off &= ~1;
		  else
		    {
		      AJIT_ELF_PUT_WORD (htab, output_bfd, relocation,
					  htab->elf.sgot->contents + off);
		      h->got.offset |= 1;
		    }
		}
	      else
		unresolved_reloc = FALSE;
	    }
	  else
	    {
	      BFD_ASSERT (local_got_offsets != NULL
			  && local_got_offsets[r_symndx] != (bfd_vma) -1);

	      off = local_got_offsets[r_symndx];

	      /* The offset must always be a multiple of 8 on 64-bit and
		 4 on 32-bit.  We use the least significant bit to record
		 whether we have already processed this entry.  */
	      if ((off & 1) != 0)
		off &= ~1;
	      else
		{

		  if (info->shared)
		    {
		      asection *s;
		      Elf_Internal_Rela outrel;

		      /* We need to generate a R_AJIT_RELATIVE reloc
			 for the dynamic linker.  */
		      s = htab->elf.srelgot;
		      BFD_ASSERT (s != NULL);

		      outrel.r_offset = (htab->elf.sgot->output_section->vma
					 + htab->elf.sgot->output_offset
					 + off);
		      outrel.r_info = AJIT_ELF_R_INFO (htab, NULL,
							0, R_AJIT_RELATIVE);
		      outrel.r_addend = relocation;
		      relocation = 0;
		      ajit_elf_append_rela (output_bfd, s, &outrel);
		    }

		  AJIT_ELF_PUT_WORD (htab, output_bfd, relocation,
				      htab->elf.sgot->contents + off);
		  local_got_offsets[r_symndx] |= 1;
		}
	    }
	  relocation = htab->elf.sgot->output_offset + off - got_base;
	  break;

	case R_AJIT_PLT32:
	case R_AJIT_PLT64:
	  if (h == NULL || h->plt.offset == (bfd_vma) -1)
	    {
	      r_type = (r_type == R_AJIT_PLT32) ? R_AJIT_32 : R_AJIT_64;
	      goto r_ajit_plt32;
	    }
	  /* Fall through.  */

	case R_AJIT_WPLT30:
	case R_AJIT_HIPLT22:
	case R_AJIT_LOPLT10:
	case R_AJIT_PCPLT32:
	case R_AJIT_PCPLT22:
	case R_AJIT_PCPLT10:
	r_ajit_wplt30:
	  /* Relocation is to the entry for this symbol in the
	     procedure linkage table.  */

	  if (! ABI_64_P (output_bfd))
	    {
	      /* The Solaris native assembler will generate a WPLT30 reloc
		 for a local symbol if you assemble a call from one
		 section to another when using -K pic.  We treat it as
		 WDISP30.  */
	      if (h == NULL)
		break;
	    }
	  /* PR 7027: We need similar behaviour for 64-bit binaries.  */ 
	  else if (r_type == R_AJIT_WPLT30 && h == NULL)
	    break;
	  else
	    {
	      BFD_ASSERT (h != NULL);
	    }

	  if (h->plt.offset == (bfd_vma) -1 || htab->elf.splt == NULL)
	    {
	      /* We didn't make a PLT entry for this symbol.  This
		 happens when statically linking PIC code, or when
		 using -Bsymbolic.  */
	      break;
	    }

	  relocation = (htab->elf.splt->output_section->vma
			+ htab->elf.splt->output_offset
			+ h->plt.offset);
	  unresolved_reloc = FALSE;
	  if (r_type == R_AJIT_PLT32 || r_type == R_AJIT_PLT64)
	    {
	      r_type = r_type == R_AJIT_PLT32 ? R_AJIT_32 : R_AJIT_64;
	      is_plt = TRUE;
	      goto r_ajit_plt32;
	    }
	  break;

	case R_AJIT_PC10:
	case R_AJIT_PC22:
	case R_AJIT_PC_HH22:
	case R_AJIT_PC_HM10:
	case R_AJIT_PC_LM22:
	  if (h != NULL
	      && strcmp (h->root.root.string, "_GLOBAL_OFFSET_TABLE_") == 0)
	    break;
	  /* Fall through.  */
	case R_AJIT_DISP8:
	case R_AJIT_DISP16:
	case R_AJIT_DISP32:
	case R_AJIT_DISP64:
	case R_AJIT_WDISP30:
	case R_AJIT_WDISP22:
	case R_AJIT_WDISP19:
	case R_AJIT_WDISP16:
	case R_AJIT_8:
	case R_AJIT_16:
	case R_AJIT_32:
	case R_AJIT_HI22:
	case R_AJIT_22:
	case R_AJIT_13:
	case R_AJIT_LO10:
	case R_AJIT_UA16:
	case R_AJIT_UA32:
	case R_AJIT_10:
	case R_AJIT_11:
	case R_AJIT_64:
	case R_AJIT_OLO10:
	case R_AJIT_HH22:
	case R_AJIT_HM10:
	case R_AJIT_LM22:
	case R_AJIT_7:
	case R_AJIT_5:
	case R_AJIT_6:
	case R_AJIT_HIX22:
	case R_AJIT_LOX10:
	case R_AJIT_H44:
	case R_AJIT_M44:
	case R_AJIT_L44:
	case R_AJIT_UA64:
	r_ajit_plt32:
	  if ((input_section->flags & SEC_ALLOC) == 0
	      || is_vxworks_tls)
	    break;

	  if ((info->shared
	       && (h == NULL
		   || ELF_ST_VISIBILITY (h->other) == STV_DEFAULT
		   || h->root.type != bfd_link_hash_undefweak)
	       && (! howto->pc_relative
		   || !SYMBOL_CALLS_LOCAL (info, h)))
	      || (!info->shared
		  && h != NULL
		  && h->dynindx != -1
		  && !h->non_got_ref
		  && ((h->def_dynamic
		       && !h->def_regular)
		      || h->root.type == bfd_link_hash_undefweak
		      || h->root.type == bfd_link_hash_undefined)))
	    {
	      Elf_Internal_Rela outrel;
	      bfd_boolean skip, relocate = FALSE;

	      /* When generating a shared object, these relocations
		 are copied into the output file to be resolved at run
		 time.  */

	      BFD_ASSERT (sreloc != NULL);

	      skip = FALSE;

	      outrel.r_offset =
		_bfd_elf_section_offset (output_bfd, info, input_section,
					 rel->r_offset);
	      if (outrel.r_offset == (bfd_vma) -1)
		skip = TRUE;
	      else if (outrel.r_offset == (bfd_vma) -2)
		skip = TRUE, relocate = TRUE;
	      outrel.r_offset += (input_section->output_section->vma
				  + input_section->output_offset);

	      /* Optimize unaligned reloc usage now that we know where
		 it finally resides.  */
	      switch (r_type)
		{
		case R_AJIT_16:
		  if (outrel.r_offset & 1)
		    r_type = R_AJIT_UA16;
		  break;
		case R_AJIT_UA16:
		  if (!(outrel.r_offset & 1))
		    r_type = R_AJIT_16;
		  break;
		case R_AJIT_32:
		  if (outrel.r_offset & 3)
		    r_type = R_AJIT_UA32;
		  break;
		case R_AJIT_UA32:
		  if (!(outrel.r_offset & 3))
		    r_type = R_AJIT_32;
		  break;
		case R_AJIT_64:
		  if (outrel.r_offset & 7)
		    r_type = R_AJIT_UA64;
		  break;
		case R_AJIT_UA64:
		  if (!(outrel.r_offset & 7))
		    r_type = R_AJIT_64;
		  break;
	  	case R_AJIT_DISP8:
		case R_AJIT_DISP16:
	  	case R_AJIT_DISP32:
	  	case R_AJIT_DISP64:
		  /* If the symbol is not dynamic, we should not keep
		     a dynamic relocation.  But an .rela.* slot has been
		     allocated for it, output R_AJIT_NONE.
		     FIXME: Add code tracking needed dynamic relocs as
		     e.g. i386 has.  */
		  if (h->dynindx == -1)
		    skip = TRUE, relocate = TRUE;
		  break;
		}

	      if (skip)
		memset (&outrel, 0, sizeof outrel);
	      /* h->dynindx may be -1 if the symbol was marked to
		 become local.  */
	      else if (h != NULL &&
		       h->dynindx != -1
		       && (! is_plt
			   || !info->shared
			   || !SYMBOLIC_BIND (info, h)
			   || !h->def_regular))
		{
		  BFD_ASSERT (h->dynindx != -1);
		  outrel.r_info = AJIT_ELF_R_INFO (htab, rel, h->dynindx, r_type);
		  outrel.r_addend = rel->r_addend;
		}
	      else
		{
		  if (r_type == R_AJIT_32 || r_type == R_AJIT_64)
		    {
		      outrel.r_info = AJIT_ELF_R_INFO (htab, NULL,
							0, R_AJIT_RELATIVE);
		      outrel.r_addend = relocation + rel->r_addend;
		    }
		  else
		    {
		      long indx;

		      outrel.r_addend = relocation + rel->r_addend;

		      if (is_plt)
			sec = htab->elf.splt;

		      if (bfd_is_abs_section (sec))
			indx = 0;
		      else if (sec == NULL || sec->owner == NULL)
			{
			  bfd_set_error (bfd_error_bad_value);
			  return FALSE;
			}
		      else
			{
			  asection *osec;

			  /* We are turning this relocation into one
			     against a section symbol.  It would be
			     proper to subtract the symbol's value,
			     osec->vma, from the emitted reloc addend,
			     but ld.so expects buggy relocs.  */
			  osec = sec->output_section;
			  indx = elf_section_data (osec)->dynindx;

			  if (indx == 0)
			    {
			      osec = htab->elf.text_index_section;
			      indx = elf_section_data (osec)->dynindx;
			    }

			  /* FIXME: we really should be able to link non-pic
			     shared libraries.  */
			  if (indx == 0)
			    {
			      BFD_FAIL ();
			      (*_bfd_error_handler)
				(_("%B: probably compiled without -fPIC?"),
				 input_bfd);
			      bfd_set_error (bfd_error_bad_value);
			      return FALSE;
			    }
			}

		      outrel.r_info = AJIT_ELF_R_INFO (htab, rel, indx,
							r_type);
		    }
		}

	      ajit_elf_append_rela (output_bfd, sreloc, &outrel);

	      /* This reloc will be computed at runtime, so there's no
		 need to do anything now.  */
	      if (! relocate)
		continue;
	    }
	  break;

	case R_AJIT_TLS_GD_HI22:
	  if (! ABI_64_P (input_bfd)
	      && ! _bfd_ajit_elf_tdata (input_bfd)->has_tlsgd)
	    {
	      /* R_AJIT_REV32 used the same reloc number as
		 R_AJIT_TLS_GD_HI22.  */
	      r_type = R_AJIT_REV32;
	      break;
	    }
	  /* Fall through */

	case R_AJIT_TLS_GD_LO10:
	case R_AJIT_TLS_IE_HI22:
	case R_AJIT_TLS_IE_LO10:
	  r_type = ajit_elf_tls_transition (info, input_bfd, r_type, h == NULL);
	  tls_type = GOT_UNKNOWN;
	  if (h == NULL && local_got_offsets)
	    tls_type = _bfd_ajit_elf_local_got_tls_type (input_bfd) [r_symndx];
	  else if (h != NULL)
	    {
	      tls_type = _bfd_ajit_elf_hash_entry(h)->tls_type;
	      if (!info->shared && h->dynindx == -1 && tls_type == GOT_TLS_IE)
		switch (AJIT_ELF_R_TYPE (rel->r_info))
		  {
		  case R_AJIT_TLS_GD_HI22:
		  case R_AJIT_TLS_IE_HI22:
		    r_type = R_AJIT_TLS_LE_HIX22;
		    break;
		  default:
		    r_type = R_AJIT_TLS_LE_LOX10;
		    break;
		  }
	    }
	  if (tls_type == GOT_TLS_IE)
	    switch (r_type)
	      {
	      case R_AJIT_TLS_GD_HI22:
		r_type = R_AJIT_TLS_IE_HI22;
		break;
	      case R_AJIT_TLS_GD_LO10:
		r_type = R_AJIT_TLS_IE_LO10;
		break;
	      }

	  if (r_type == R_AJIT_TLS_LE_HIX22)
	    {
	      relocation = tpoff (info, relocation);
	      break;
	    }
	  if (r_type == R_AJIT_TLS_LE_LOX10)
	    {
	      /* Change add into xor.  */
	      relocation = tpoff (info, relocation);
	      bfd_put_32 (output_bfd, (bfd_get_32 (input_bfd,
						   contents + rel->r_offset)
				       | 0x80182000), contents + rel->r_offset);
	      break;
	    }

	  if (h != NULL)
	    {
	      off = h->got.offset;
	      h->got.offset |= 1;
	    }
	  else
	    {
	      BFD_ASSERT (local_got_offsets != NULL);
	      off = local_got_offsets[r_symndx];
	      local_got_offsets[r_symndx] |= 1;
	    }

	r_ajit_tlsldm:
	  if (htab->elf.sgot == NULL)
	    abort ();

	  if ((off & 1) != 0)
	    off &= ~1;
	  else
	    {
	      Elf_Internal_Rela outrel;
	      int dr_type, indx;

	      if (htab->elf.srelgot == NULL)
		abort ();

	      AJIT_ELF_PUT_WORD (htab, output_bfd, 0,
				  htab->elf.sgot->contents + off);
	      outrel.r_offset = (htab->elf.sgot->output_section->vma
				 + htab->elf.sgot->output_offset + off);
	      indx = h && h->dynindx != -1 ? h->dynindx : 0;
	      if (r_type == R_AJIT_TLS_IE_HI22
		  || r_type == R_AJIT_TLS_IE_LO10)
		dr_type = AJIT_ELF_TPOFF_RELOC (htab);
	      else
		dr_type = AJIT_ELF_DTPMOD_RELOC (htab);
	      if (dr_type == AJIT_ELF_TPOFF_RELOC (htab) && indx == 0)
		outrel.r_addend = relocation - dtpoff_base (info);
	      else
		outrel.r_addend = 0;
	      outrel.r_info = AJIT_ELF_R_INFO (htab, NULL, indx, dr_type);
	      ajit_elf_append_rela (output_bfd, htab->elf.srelgot, &outrel);

	      if (r_type == R_AJIT_TLS_GD_HI22
		  || r_type == R_AJIT_TLS_GD_LO10)
		{
		  if (indx == 0)
		    {
	    	      BFD_ASSERT (! unresolved_reloc);
		      AJIT_ELF_PUT_WORD (htab, output_bfd,
					  relocation - dtpoff_base (info),
					  (htab->elf.sgot->contents + off
					   + AJIT_ELF_WORD_BYTES (htab)));
		    }
		  else
		    {
		      AJIT_ELF_PUT_WORD (htab, output_bfd, 0,
					  (htab->elf.sgot->contents + off
					   + AJIT_ELF_WORD_BYTES (htab)));
		      outrel.r_info = AJIT_ELF_R_INFO (htab, NULL, indx,
							AJIT_ELF_DTPOFF_RELOC (htab));
		      outrel.r_offset += AJIT_ELF_WORD_BYTES (htab);
		      ajit_elf_append_rela (output_bfd, htab->elf.srelgot,
					     &outrel);
		    }
		}
	      else if (dr_type == AJIT_ELF_DTPMOD_RELOC (htab))
		{
		  AJIT_ELF_PUT_WORD (htab, output_bfd, 0,
				      (htab->elf.sgot->contents + off
				       + AJIT_ELF_WORD_BYTES (htab)));
		}
	    }

	  if (off >= (bfd_vma) -2)
	    abort ();

	  relocation = htab->elf.sgot->output_offset + off - got_base;
	  unresolved_reloc = FALSE;
	  howto = _bfd_ajit_elf_howto_table + r_type;
	  break;

	case R_AJIT_TLS_LDM_HI22:
	case R_AJIT_TLS_LDM_LO10:
	  if (! info->shared)
	    {
	      bfd_put_32 (output_bfd, AJIT_NOP, contents + rel->r_offset);
	      continue;
	    }
	  off = htab->tls_ldm_got.offset;
	  htab->tls_ldm_got.offset |= 1;
	  goto r_ajit_tlsldm;

	case R_AJIT_TLS_LDO_HIX22:
	case R_AJIT_TLS_LDO_LOX10:
	  if (info->shared)
	    {
	      relocation -= dtpoff_base (info);
	      break;
	    }

	  r_type = (r_type == R_AJIT_TLS_LDO_HIX22
		    ? R_AJIT_TLS_LE_HIX22 : R_AJIT_TLS_LE_LOX10);
	  /* Fall through.  */

	case R_AJIT_TLS_LE_HIX22:
	case R_AJIT_TLS_LE_LOX10:
	  if (info->shared)
	    {
	      Elf_Internal_Rela outrel;
	      bfd_boolean skip;

	      BFD_ASSERT (sreloc != NULL);
	      skip = FALSE;
	      outrel.r_offset =
		_bfd_elf_section_offset (output_bfd, info, input_section,
					 rel->r_offset);
	      if (outrel.r_offset == (bfd_vma) -1)
		skip = TRUE;
	      else if (outrel.r_offset == (bfd_vma) -2)
		skip = TRUE;
	      outrel.r_offset += (input_section->output_section->vma
				  + input_section->output_offset);
	      if (skip)
		memset (&outrel, 0, sizeof outrel);
	      else
		{
		  outrel.r_info = AJIT_ELF_R_INFO (htab, NULL, 0, r_type);
		  outrel.r_addend = relocation - dtpoff_base (info)
				    + rel->r_addend;
		}

	      ajit_elf_append_rela (output_bfd, sreloc, &outrel);
	      continue;
	    }
	  relocation = tpoff (info, relocation);
	  break;

	case R_AJIT_TLS_LDM_CALL:
	  if (! info->shared)
	    {
	      /* mov %g0, %o0 */
	      bfd_put_32 (output_bfd, 0x90100000, contents + rel->r_offset);
	      continue;
	    }
	  /* Fall through */

	case R_AJIT_TLS_GD_CALL:
	  tls_type = GOT_UNKNOWN;
	  if (h == NULL && local_got_offsets)
	    tls_type = _bfd_ajit_elf_local_got_tls_type (input_bfd) [r_symndx];
	  else if (h != NULL)
	    tls_type = _bfd_ajit_elf_hash_entry(h)->tls_type;
	  if (! info->shared
	      || (r_type == R_AJIT_TLS_GD_CALL && tls_type == GOT_TLS_IE))
	    {
	      Elf_Internal_Rela *rel2;
	      bfd_vma insn;

	      if (!info->shared && (h == NULL || h->dynindx == -1))
		{
		  /* GD -> LE */
		  bfd_put_32 (output_bfd, AJIT_NOP, contents + rel->r_offset);
		  continue;
		}

	      /* GD -> IE */
	      if (rel + 1 < relend
		  && AJIT_ELF_R_TYPE (rel[1].r_info) == R_AJIT_TLS_GD_ADD
		  && rel[1].r_offset == rel->r_offset + 4
		  && AJIT_ELF_R_SYMNDX (htab, rel[1].r_info) == r_symndx
		  && (((insn = bfd_get_32 (input_bfd,
					   contents + rel[1].r_offset))
		       >> 25) & 0x1f) == 8)
		{
		  /* We have
		     call __tls_get_addr, %tgd_call(foo)
		      add %reg1, %reg2, %o0, %tgd_add(foo)
		     and change it into IE:
		     {ld,ldx} [%reg1 + %reg2], %o0, %tie_ldx(foo)
		     add %g7, %o0, %o0, %tie_add(foo).
		     add is 0x80000000 | (rd << 25) | (rs1 << 14) | rs2,
		     ld is 0xc0000000 | (rd << 25) | (rs1 << 14) | rs2,
		     ldx is 0xc0580000 | (rd << 25) | (rs1 << 14) | rs2.  */
		  bfd_put_32 (output_bfd, insn | (ABI_64_P (output_bfd) ? 0xc0580000 : 0xc0000000),
			      contents + rel->r_offset);
		  bfd_put_32 (output_bfd, 0x9001c008,
			      contents + rel->r_offset + 4);
		  rel++;
		  continue;
		}

	      /* We cannot just overwrite the delay slot instruction,
		 as it might be what puts the %o0 argument to
		 __tls_get_addr into place.  So we have to transpose
		 the delay slot with the add we patch in.  */
	      insn = bfd_get_32 (input_bfd, contents + rel->r_offset + 4);
	      bfd_put_32 (output_bfd, insn,
			  contents + rel->r_offset);
	      bfd_put_32 (output_bfd, 0x9001c008,
			  contents + rel->r_offset + 4);

	      rel2 = rel;
	      while ((rel2 = ajit_elf_find_reloc_at_ofs (rel2 + 1, relend,
							  rel->r_offset + 4))
		     != NULL)
		{
		  /* If the instruction we moved has a relocation attached to
		     it, adjust the offset so that it will apply to the correct
		     instruction.  */
		  rel2->r_offset -= 4;
		}
	      continue;
	    }

	  h = (struct elf_link_hash_entry *)
	      bfd_link_hash_lookup (info->hash, "__tls_get_addr", FALSE,
				    FALSE, TRUE);
	  BFD_ASSERT (h != NULL);
	  r_type = R_AJIT_WPLT30;
	  howto = _bfd_ajit_elf_howto_table + r_type;
	  goto r_ajit_wplt30;

	case R_AJIT_TLS_GD_ADD:
	  tls_type = GOT_UNKNOWN;
	  if (h == NULL && local_got_offsets)
	    tls_type = _bfd_ajit_elf_local_got_tls_type (input_bfd) [r_symndx];
	  else if (h != NULL)
	    tls_type = _bfd_ajit_elf_hash_entry(h)->tls_type;
	  if (! info->shared || tls_type == GOT_TLS_IE)
	    {
	      /* add %reg1, %reg2, %reg3, %tgd_add(foo)
		 changed into IE:
		 {ld,ldx} [%reg1 + %reg2], %reg3, %tie_ldx(foo)
		 or LE:
		 add %g7, %reg2, %reg3.  */
	      bfd_vma insn = bfd_get_32 (input_bfd, contents + rel->r_offset);
	      if ((h != NULL && h->dynindx != -1) || info->shared)
		relocation = insn | (ABI_64_P (output_bfd) ? 0xc0580000 : 0xc0000000);
	      else
		relocation = (insn & ~0x7c000) | 0x1c000;
	      bfd_put_32 (output_bfd, relocation, contents + rel->r_offset);
	    }
	  continue;

	case R_AJIT_TLS_LDM_ADD:
	  if (! info->shared)
	    bfd_put_32 (output_bfd, AJIT_NOP, contents + rel->r_offset);
	  continue;

	case R_AJIT_TLS_LDO_ADD:
	  if (! info->shared)
	    {
	      /* Change rs1 into %g7.  */
	      bfd_vma insn = bfd_get_32 (input_bfd, contents + rel->r_offset);
	      insn = (insn & ~0x7c000) | 0x1c000;
	      bfd_put_32 (output_bfd, insn, contents + rel->r_offset);
	    }
	  continue;

	case R_AJIT_TLS_IE_LD:
	case R_AJIT_TLS_IE_LDX:
	  if (! info->shared && (h == NULL || h->dynindx == -1))
	    {
	      bfd_vma insn = bfd_get_32 (input_bfd, contents + rel->r_offset);
	      int rs2 = insn & 0x1f;
	      int rd = (insn >> 25) & 0x1f;

	      if (rs2 == rd)
		relocation = AJIT_NOP;
	      else
		relocation = 0x80100000 | (insn & 0x3e00001f);
	      bfd_put_32 (output_bfd, relocation, contents + rel->r_offset);
	    }
	  continue;

	case R_AJIT_TLS_IE_ADD:
	  /* Totally useless relocation.  */
	  continue;

	case R_AJIT_TLS_DTPOFF32:
	case R_AJIT_TLS_DTPOFF64:
	  relocation -= dtpoff_base (info);
	  break;

	default:
	  break;
	}

      /* Dynamic relocs are not propagated for SEC_DEBUGGING sections
	 because such sections are not SEC_ALLOC and thus ld.so will
	 not process them.  */
      if (unresolved_reloc
	  && !((input_section->flags & SEC_DEBUGGING) != 0
	       && h->def_dynamic))
	(*_bfd_error_handler)
	  (_("%B(%A+0x%lx): unresolvable %s relocation against symbol `%s'"),
	   input_bfd,
	   input_section,
	   (long) rel->r_offset,
	   howto->name,
	   h->root.root.string);

      r = bfd_reloc_continue;
      if (r_type == R_AJIT_OLO10)
	{
	    bfd_vma x;

	    if (! ABI_64_P (output_bfd))
	      abort ();

	    relocation += rel->r_addend;
	    relocation = (relocation & 0x3ff) + ELF64_R_TYPE_DATA (rel->r_info);

	    x = bfd_get_32 (input_bfd, contents + rel->r_offset);
	    x = (x & ~(bfd_vma) 0x1fff) | (relocation & 0x1fff);
	    bfd_put_32 (input_bfd, x, contents + rel->r_offset);

	    r = bfd_check_overflow (howto->complain_on_overflow,
				    howto->bitsize, howto->rightshift,
				    bfd_arch_bits_per_address (input_bfd),
				    relocation);
	}
      else if (r_type == R_AJIT_WDISP16)
	{
	  bfd_vma x;

	  relocation += rel->r_addend;
	  relocation -= (input_section->output_section->vma
			 + input_section->output_offset);
	  relocation -= rel->r_offset;

	  x = bfd_get_32 (input_bfd, contents + rel->r_offset);
	  x |= ((((relocation >> 2) & 0xc000) << 6)
		| ((relocation >> 2) & 0x3fff));
	  bfd_put_32 (input_bfd, x, contents + rel->r_offset);

	  r = bfd_check_overflow (howto->complain_on_overflow,
				  howto->bitsize, howto->rightshift,
				  bfd_arch_bits_per_address (input_bfd),
				  relocation);
	}
      else if (r_type == R_AJIT_REV32)
	{
	  bfd_vma x;

	  relocation = relocation + rel->r_addend;

	  x = bfd_get_32 (input_bfd, contents + rel->r_offset);
	  x = x + relocation;
	  bfd_putl32 (/*input_bfd,*/ x, contents + rel->r_offset);
	  r = bfd_reloc_ok;
	}
      else if (r_type == R_AJIT_TLS_LDO_HIX22
	       || r_type == R_AJIT_TLS_LE_HIX22)
	{
	  bfd_vma x;

	  relocation += rel->r_addend;
	  if (r_type == R_AJIT_TLS_LE_HIX22)
	    relocation ^= MINUS_ONE;

	  x = bfd_get_32 (input_bfd, contents + rel->r_offset);
	  x = (x & ~(bfd_vma) 0x3fffff) | ((relocation >> 10) & 0x3fffff);
	  bfd_put_32 (input_bfd, x, contents + rel->r_offset);
	  r = bfd_reloc_ok;
	}
      else if (r_type == R_AJIT_TLS_LDO_LOX10
	       || r_type == R_AJIT_TLS_LE_LOX10)
	{
	  bfd_vma x;

	  relocation += rel->r_addend;
	  relocation &= 0x3ff;
	  if (r_type == R_AJIT_TLS_LE_LOX10)
	    relocation |= 0x1c00;

	  x = bfd_get_32 (input_bfd, contents + rel->r_offset);
	  x = (x & ~(bfd_vma) 0x1fff) | relocation;
	  bfd_put_32 (input_bfd, x, contents + rel->r_offset);

	  r = bfd_reloc_ok;
	}
      else if (r_type == R_AJIT_HIX22
	       || r_type == R_AJIT_GOTDATA_HIX22)
	{
	  bfd_vma x;

	  relocation += rel->r_addend;
	  if (r_type == R_AJIT_HIX22
	      || (bfd_signed_vma) relocation < 0)
	    relocation = relocation ^ MINUS_ONE;

	  x = bfd_get_32 (input_bfd, contents + rel->r_offset);
	  x = (x & ~(bfd_vma) 0x3fffff) | ((relocation >> 10) & 0x3fffff);
	  bfd_put_32 (input_bfd, x, contents + rel->r_offset);

	  r = bfd_check_overflow (howto->complain_on_overflow,
				  howto->bitsize, howto->rightshift,
				  bfd_arch_bits_per_address (input_bfd),
				  relocation);
	}
      else if (r_type == R_AJIT_LOX10
	       || r_type == R_AJIT_GOTDATA_LOX10)
	{
	  bfd_vma x;

	  relocation += rel->r_addend;
	  if (r_type == R_AJIT_LOX10
	      || (bfd_signed_vma) relocation < 0)
	    relocation = (relocation & 0x3ff) | 0x1c00;
	  else
	    relocation = (relocation & 0x3ff);

	  x = bfd_get_32 (input_bfd, contents + rel->r_offset);
	  x = (x & ~(bfd_vma) 0x1fff) | relocation;
	  bfd_put_32 (input_bfd, x, contents + rel->r_offset);

	  r = bfd_reloc_ok;
	}
      else if ((r_type == R_AJIT_WDISP30 || r_type == R_AJIT_WPLT30)
	       && sec_do_relax (input_section)
	       && rel->r_offset + 4 < input_section->size)
	{
#define G0		0
#define O7		15
#define XCC		(2 << 20)
#define COND(x)		(((x)&0xf)<<25)
#define CONDA		COND(0x8)
#define INSN_BPA	(F2(0,1) | CONDA | BPRED | XCC)
#define INSN_BA		(F2(0,2) | CONDA)
#define INSN_OR		F3(2, 0x2, 0)
#define INSN_NOP	F2(0,4)

	  bfd_vma x, y;

	  /* If the instruction is a call with either:
	     restore
	     arithmetic instruction with rd == %o7
	     where rs1 != %o7 and rs2 if it is register != %o7
	     then we can optimize if the call destination is near
	     by changing the call into a branch always.  */
	  x = bfd_get_32 (input_bfd, contents + rel->r_offset);
	  y = bfd_get_32 (input_bfd, contents + rel->r_offset + 4);
	  if ((x & OP(~0)) == OP(1) && (y & OP(~0)) == OP(2))
	    {
	      if (((y & OP3(~0)) == OP3(0x3d) /* restore */
		   || ((y & OP3(0x28)) == 0 /* arithmetic */
		       && (y & RD(~0)) == RD(O7)))
		  && (y & RS1(~0)) != RS1(O7)
		  && ((y & F3I(~0))
		      || (y & RS2(~0)) != RS2(O7)))
		{
		  bfd_vma reloc;

		  reloc = relocation + rel->r_addend - rel->r_offset;
		  reloc -= (input_section->output_section->vma
			    + input_section->output_offset);

		  /* Ensure the branch fits into simm22.  */
		  if ((reloc & 3) == 0
		      && ((reloc & ~(bfd_vma)0x7fffff) == 0
			  || ((reloc | 0x7fffff) == ~(bfd_vma)0)))
		    {
		      reloc >>= 2;

		      /* Check whether it fits into simm19.  */
		      if (((reloc & 0x3c0000) == 0
			   || (reloc & 0x3c0000) == 0x3c0000)
			  && (ABI_64_P (output_bfd)
			      || elf_elfheader (output_bfd)->e_flags & EF_AJIT_32PLUS))
			x = INSN_BPA | (reloc & 0x7ffff); /* ba,pt %xcc */
		      else
			x = INSN_BA | (reloc & 0x3fffff); /* ba */
		      bfd_put_32 (input_bfd, x, contents + rel->r_offset);
		      r = bfd_reloc_ok;
		      if (rel->r_offset >= 4
			  && (y & (0xffffffff ^ RS1(~0)))
			     == (INSN_OR | RD(O7) | RS2(G0)))
			{
			  bfd_vma z;
			  unsigned int reg;

			  z = bfd_get_32 (input_bfd,
					  contents + rel->r_offset - 4);
			  if ((z & (0xffffffff ^ RD(~0)))
			      != (INSN_OR | RS1(O7) | RS2(G0)))
			    break;

			  /* The sequence was
			     or %o7, %g0, %rN
			     call foo
			     or %rN, %g0, %o7

			     If call foo was replaced with ba, replace
			     or %rN, %g0, %o7 with nop.  */

			  reg = (y & RS1(~0)) >> 14;
			  if (reg != ((z & RD(~0)) >> 25)
			      || reg == G0 || reg == O7)
			    break;

			  bfd_put_32 (input_bfd, (bfd_vma) INSN_NOP,
				      contents + rel->r_offset + 4);
			}

		    }
		}
	    }
	}

      if (r == bfd_reloc_continue)
	{
do_relocation:
	  r = _bfd_final_link_relocate (howto, input_bfd, input_section,
					contents, rel->r_offset,
					relocation, rel->r_addend);
	}
      if (r != bfd_reloc_ok)
	{
	  switch (r)
	    {
	    default:
	    case bfd_reloc_outofrange:
	      abort ();
	    case bfd_reloc_overflow:
	      {
		const char *name;

		/* The Solaris native linker silently disregards overflows. 
		   We don't, but this breaks stabs debugging info, whose
		   relocations are only 32-bits wide.  Ignore overflows in
		   this case and also for discarded entries.  */
		if ((r_type == R_AJIT_32 || r_type == R_AJIT_DISP32)
		    && (((input_section->flags & SEC_DEBUGGING) != 0
			 && strcmp (bfd_section_name (input_bfd,
						      input_section),
				    ".stab") == 0)
			|| _bfd_elf_section_offset (output_bfd, info,
						    input_section,
						    rel->r_offset)
			     == (bfd_vma)-1))
		  break;

		if (h != NULL)
		  {
		    /* Assume this is a call protected by other code that
		       detect the symbol is undefined.  If this is the case,
		       we can safely ignore the overflow.  If not, the
		       program is hosed anyway, and a little warning isn't
		       going to help.  */
		    if (h->root.type == bfd_link_hash_undefweak
			&& howto->pc_relative)
		      break;

	            name = NULL;
		  }
		else
		  {
		    name = bfd_elf_string_from_elf_section (input_bfd,
							    symtab_hdr->sh_link,
							    sym->st_name);
		    if (name == NULL)
		      return FALSE;
		    if (*name == '\0')
		      name = bfd_section_name (input_bfd, sec);
		  }
		if (! ((*info->callbacks->reloc_overflow)
		       (info, (h ? &h->root : NULL), name, howto->name,
			(bfd_vma) 0, input_bfd, input_section,
			rel->r_offset)))
		  return FALSE;
	      }
	      break;
	    }
	}
    }

  return TRUE;
}

/* Build a VxWorks PLT entry.  PLT_INDEX is the index of the PLT entry
   and PLT_OFFSET is the byte offset from the start of .plt.  GOT_OFFSET
   is the offset of the associated .got.plt entry from
   _GLOBAL_OFFSET_TABLE_.  */

static void
ajit_vxworks_build_plt_entry (bfd *output_bfd, struct bfd_link_info *info,
			       bfd_vma plt_offset, bfd_vma plt_index,
			       bfd_vma got_offset)
{
  bfd_vma got_base;
  const bfd_vma *plt_entry;
  struct _bfd_ajit_elf_link_hash_table *htab;
  bfd_byte *loc;
  Elf_Internal_Rela rela;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);

  if (info->shared)
    {
      plt_entry = ajit_vxworks_shared_plt_entry;
      got_base = 0;
    }
  else
    {
      plt_entry = ajit_vxworks_exec_plt_entry;
      got_base = (htab->elf.hgot->root.u.def.value
		  + htab->elf.hgot->root.u.def.section->output_offset
		  + htab->elf.hgot->root.u.def.section->output_section->vma);
    }

  /* Fill in the entry in the procedure linkage table.  */
  bfd_put_32 (output_bfd, plt_entry[0] + ((got_base + got_offset) >> 10),
	      htab->elf.splt->contents + plt_offset);
  bfd_put_32 (output_bfd, plt_entry[1] + ((got_base + got_offset) & 0x3ff),
	      htab->elf.splt->contents + plt_offset + 4);
  bfd_put_32 (output_bfd, plt_entry[2],
	      htab->elf.splt->contents + plt_offset + 8);
  bfd_put_32 (output_bfd, plt_entry[3],
	      htab->elf.splt->contents + plt_offset + 12);
  bfd_put_32 (output_bfd, plt_entry[4],
	      htab->elf.splt->contents + plt_offset + 16);
  bfd_put_32 (output_bfd, plt_entry[5] + (plt_index >> 10),
	      htab->elf.splt->contents + plt_offset + 20);
  /* PC-relative displacement for a branch to the start of
     the PLT section.  */
  bfd_put_32 (output_bfd, plt_entry[6] + (((-plt_offset - 24) >> 2)
					  & 0x003fffff),
	      htab->elf.splt->contents + plt_offset + 24);
  bfd_put_32 (output_bfd, plt_entry[7] + (plt_index & 0x3ff),
	      htab->elf.splt->contents + plt_offset + 28);

  /* Fill in the .got.plt entry, pointing initially at the
     second half of the PLT entry.  */
  BFD_ASSERT (htab->elf.sgotplt != NULL);
  bfd_put_32 (output_bfd,
	      htab->elf.splt->output_section->vma
	      + htab->elf.splt->output_offset
	      + plt_offset + 20,
	      htab->elf.sgotplt->contents + got_offset);

  /* Add relocations to .rela.plt.unloaded.  */
  if (!info->shared)
    {
      loc = (htab->srelplt2->contents
	     + (2 + 3 * plt_index) * sizeof (Elf32_External_Rela));

      /* Relocate the initial sethi.  */
      rela.r_offset = (htab->elf.splt->output_section->vma
		       + htab->elf.splt->output_offset
		       + plt_offset);
      rela.r_info = ELF32_R_INFO (htab->elf.hgot->indx, R_AJIT_HI22);
      rela.r_addend = got_offset;
      bfd_elf32_swap_reloca_out (output_bfd, &rela, loc);
      loc += sizeof (Elf32_External_Rela);

      /* Likewise the following or.  */
      rela.r_offset += 4;
      rela.r_info = ELF32_R_INFO (htab->elf.hgot->indx, R_AJIT_LO10);
      bfd_elf32_swap_reloca_out (output_bfd, &rela, loc);
      loc += sizeof (Elf32_External_Rela);

      /* Relocate the .got.plt entry.  */
      rela.r_offset = (htab->elf.sgotplt->output_section->vma
		       + htab->elf.sgotplt->output_offset
		       + got_offset);
      rela.r_info = ELF32_R_INFO (htab->elf.hplt->indx, R_AJIT_32);
      rela.r_addend = plt_offset + 20;
      bfd_elf32_swap_reloca_out (output_bfd, &rela, loc);
    }
}

/* Finish up dynamic symbol handling.  We set the contents of various
   dynamic sections here.  */

bfd_boolean
_bfd_ajit_elf_finish_dynamic_symbol (bfd *output_bfd,
				      struct bfd_link_info *info,
				      struct elf_link_hash_entry *h,
				      Elf_Internal_Sym *sym)
{
  struct _bfd_ajit_elf_link_hash_table *htab;
  const struct elf_backend_data *bed;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);
  bed = get_elf_backend_data (output_bfd);

  if (h->plt.offset != (bfd_vma) -1)
    {
      asection *splt;
      asection *srela;
      Elf_Internal_Rela rela;
      bfd_byte *loc;
      bfd_vma r_offset, got_offset;
      int rela_index;

      /* When building a static executable, use .iplt and
	 .rela.iplt sections for STT_GNU_IFUNC symbols.  */
      if (htab->elf.splt != NULL)
	{
	  splt = htab->elf.splt;
	  srela = htab->elf.srelplt;
	}
      else
	{
	  splt = htab->elf.iplt;
	  srela = htab->elf.irelplt;
	}

      if (splt == NULL || srela == NULL)
	abort ();

      /* Fill in the entry in the .rela.plt section.  */
      if (htab->is_vxworks)
	{
	  /* Work out the index of this PLT entry.  */
	  rela_index = ((h->plt.offset - htab->plt_header_size)
			/ htab->plt_entry_size);

	  /* Calculate the offset of the associated .got.plt entry.
	     The first three entries are reserved.  */
	  got_offset = (rela_index + 3) * 4;

	  ajit_vxworks_build_plt_entry (output_bfd, info, h->plt.offset,
					 rela_index, got_offset);


	  /* On VxWorks, the relocation points to the .got.plt entry,
	     not the .plt entry.  */
	  rela.r_offset = (htab->elf.sgotplt->output_section->vma
			   + htab->elf.sgotplt->output_offset
			   + got_offset);
	  rela.r_addend = 0;
	  rela.r_info = AJIT_ELF_R_INFO (htab, NULL, h->dynindx,
					  R_AJIT_JMP_SLOT);
	}
      else
	{
	  bfd_boolean ifunc = FALSE;

	  /* Fill in the entry in the procedure linkage table.  */
	  rela_index = AJIT_ELF_BUILD_PLT_ENTRY (htab, output_bfd, splt,
						  h->plt.offset, splt->size,
						  &r_offset);

	  if (h == NULL
	      || h->dynindx == -1
	      || ((info->executable
		   || ELF_ST_VISIBILITY (h->other) != STV_DEFAULT)
		  && h->def_regular
		  && h->type == STT_GNU_IFUNC))
	    {
	      ifunc = TRUE;
	      BFD_ASSERT (h == NULL
			  || (h->type == STT_GNU_IFUNC
			      && h->def_regular
			      && (h->root.type == bfd_link_hash_defined
				  || h->root.type == bfd_link_hash_defweak)));
	    }

	  rela.r_offset = r_offset
	    + (splt->output_section->vma + splt->output_offset);
	  if (ABI_64_P (output_bfd)
	      && h->plt.offset >= (PLT64_LARGE_THRESHOLD * PLT64_ENTRY_SIZE))
	    {
	      if (ifunc)
		{
		  rela.r_addend = (h->root.u.def.section->output_section->vma
				   + h->root.u.def.section->output_offset
				   + h->root.u.def.value);
		  rela.r_info = AJIT_ELF_R_INFO (htab, NULL, 0,
						  R_AJIT_IRELATIVE);
		}
	      else
		{
		  rela.r_addend = (-(h->plt.offset + 4)
				   - splt->output_section->vma
				   - splt->output_offset);
		  rela.r_info = AJIT_ELF_R_INFO (htab, NULL, h->dynindx,
						  R_AJIT_JMP_SLOT);
		}
	    }
	  else
	    {
	      if (ifunc)
		{
		  rela.r_addend = (h->root.u.def.section->output_section->vma
				   + h->root.u.def.section->output_offset
				   + h->root.u.def.value);
		  rela.r_info = AJIT_ELF_R_INFO (htab, NULL, 0,
						  R_AJIT_JMP_IREL);
		}
	      else
		{
		  rela.r_addend = 0;
		  rela.r_info = AJIT_ELF_R_INFO (htab, NULL, h->dynindx,
						  R_AJIT_JMP_SLOT);
		}
	    }
	}

      /* Adjust for the first 4 reserved elements in the .plt section
	 when setting the offset in the .rela.plt section.
	 Sun forgot to read their own ABI and copied elf32-ajit behaviour,
	 thus .plt[4] has corresponding .rela.plt[0] and so on.  */

      loc = srela->contents;
      loc += rela_index * bed->s->sizeof_rela;
      bed->s->swap_reloca_out (output_bfd, &rela, loc);

      if (!h->def_regular)
	{
	  /* Mark the symbol as undefined, rather than as defined in
	     the .plt section.  Leave the value alone.  */
	  sym->st_shndx = SHN_UNDEF;
	  /* If the symbol is weak, we do need to clear the value.
	     Otherwise, the PLT entry would provide a definition for
	     the symbol even if the symbol wasn't defined anywhere,
	     and so the symbol would never be NULL.  */
	  if (!h->ref_regular_nonweak)
	    sym->st_value = 0;
	}
    }

  if (h->got.offset != (bfd_vma) -1
      && _bfd_ajit_elf_hash_entry(h)->tls_type != GOT_TLS_GD
      && _bfd_ajit_elf_hash_entry(h)->tls_type != GOT_TLS_IE)
    {
      asection *sgot;
      asection *srela;
      Elf_Internal_Rela rela;

      /* This symbol has an entry in the GOT.  Set it up.  */

      sgot = htab->elf.sgot;
      srela = htab->elf.srelgot;
      BFD_ASSERT (sgot != NULL && srela != NULL);

      rela.r_offset = (sgot->output_section->vma
		       + sgot->output_offset
		       + (h->got.offset &~ (bfd_vma) 1));

      /* If this is a -Bsymbolic link, and the symbol is defined
	 locally, we just want to emit a RELATIVE reloc.  Likewise if
	 the symbol was forced to be local because of a version file.
	 The entry in the global offset table will already have been
	 initialized in the relocate_section function.  */
      if (! info->shared
	  && h->type == STT_GNU_IFUNC
	  && h->def_regular)
	{
	  asection *plt;

	  /* We load the GOT entry with the PLT entry.  */
	  plt = htab->elf.splt ? htab->elf.splt : htab->elf.iplt;
	  AJIT_ELF_PUT_WORD (htab, output_bfd,
			      (plt->output_section->vma
			       + plt->output_offset + h->plt.offset),
			      htab->elf.sgot->contents
			      + (h->got.offset & ~(bfd_vma) 1));
	  return TRUE;
	}
      else if (info->shared
	       && SYMBOL_REFERENCES_LOCAL (info, h))
	{
	  asection *sec = h->root.u.def.section;
	  if (h->type == STT_GNU_IFUNC)
	    rela.r_info = AJIT_ELF_R_INFO (htab, NULL, 0, R_AJIT_IRELATIVE);
	  else
	    rela.r_info = AJIT_ELF_R_INFO (htab, NULL, 0, R_AJIT_RELATIVE);
	  rela.r_addend = (h->root.u.def.value
			   + sec->output_section->vma
			   + sec->output_offset);
	}
      else
	{
	  rela.r_info = AJIT_ELF_R_INFO (htab, NULL, h->dynindx, R_AJIT_GLOB_DAT);
	  rela.r_addend = 0;
	}

      AJIT_ELF_PUT_WORD (htab, output_bfd, 0,
			  sgot->contents + (h->got.offset & ~(bfd_vma) 1));
      ajit_elf_append_rela (output_bfd, srela, &rela);
    }

  if (h->needs_copy)
    {
      asection *s;
      Elf_Internal_Rela rela;

      /* This symbols needs a copy reloc.  Set it up.  */
      BFD_ASSERT (h->dynindx != -1);

      s = bfd_get_section_by_name (h->root.u.def.section->owner,
				   ".rela.bss");
      BFD_ASSERT (s != NULL);

      rela.r_offset = (h->root.u.def.value
		       + h->root.u.def.section->output_section->vma
		       + h->root.u.def.section->output_offset);
      rela.r_info = AJIT_ELF_R_INFO (htab, NULL, h->dynindx, R_AJIT_COPY);
      rela.r_addend = 0;
      ajit_elf_append_rela (output_bfd, s, &rela);
    }

  /* Mark some specially defined symbols as absolute.  On VxWorks,
     _GLOBAL_OFFSET_TABLE_ is not absolute: it is relative to the
     ".got" section.  Likewise _PROCEDURE_LINKAGE_TABLE_ and ".plt".  */
  if (sym != NULL
      && (strcmp (h->root.root.string, "_DYNAMIC") == 0
	  || (!htab->is_vxworks
	      && (h == htab->elf.hgot || h == htab->elf.hplt))))
    sym->st_shndx = SHN_ABS;

  return TRUE;
}

/* Finish up the dynamic sections.  */

static bfd_boolean
ajit_finish_dyn (bfd *output_bfd, struct bfd_link_info *info,
		  bfd *dynobj, asection *sdyn,
		  asection *splt ATTRIBUTE_UNUSED)
{
  struct _bfd_ajit_elf_link_hash_table *htab;
  const struct elf_backend_data *bed;
  bfd_byte *dyncon, *dynconend;
  size_t dynsize;
  int stt_regidx = -1;
  bfd_boolean abi_64_p;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);
  bed = get_elf_backend_data (output_bfd);
  dynsize = bed->s->sizeof_dyn;
  dynconend = sdyn->contents + sdyn->size;
  abi_64_p = ABI_64_P (output_bfd);
  for (dyncon = sdyn->contents; dyncon < dynconend; dyncon += dynsize)
    {
      Elf_Internal_Dyn dyn;
      const char *name;
      bfd_boolean size;

      bed->s->swap_dyn_in (dynobj, dyncon, &dyn);

      if (htab->is_vxworks && dyn.d_tag == DT_RELASZ)
	{
	  /* On VxWorks, DT_RELASZ should not include the relocations
	     in .rela.plt.  */
	  if (htab->elf.srelplt)
	    {
	      dyn.d_un.d_val -= htab->elf.srelplt->size;
	      bed->s->swap_dyn_out (output_bfd, &dyn, dyncon);
	    }
	}
      else if (htab->is_vxworks && dyn.d_tag == DT_PLTGOT)
	{
	  /* On VxWorks, DT_PLTGOT should point to the start of the GOT,
	     not to the start of the PLT.  */
	  if (htab->elf.sgotplt)
	    {
	      dyn.d_un.d_val = (htab->elf.sgotplt->output_section->vma
				+ htab->elf.sgotplt->output_offset);
	      bed->s->swap_dyn_out (output_bfd, &dyn, dyncon);
	    }
	}
      else if (htab->is_vxworks
	       && elf_vxworks_finish_dynamic_entry (output_bfd, &dyn))
	bed->s->swap_dyn_out (output_bfd, &dyn, dyncon);
      else if (abi_64_p && dyn.d_tag == DT_AJIT_REGISTER)
	{
	  if (stt_regidx == -1)
	    {
	      stt_regidx =
		_bfd_elf_link_lookup_local_dynindx (info, output_bfd, -1);
	      if (stt_regidx == -1)
		return FALSE;
	    }
	  dyn.d_un.d_val = stt_regidx++;
	  bed->s->swap_dyn_out (output_bfd, &dyn, dyncon);
	}
      else
	{
	  switch (dyn.d_tag)
	    {
	    case DT_PLTGOT:   name = ".plt"; size = FALSE; break;
	    case DT_PLTRELSZ: name = ".rela.plt"; size = TRUE; break;
	    case DT_JMPREL:   name = ".rela.plt"; size = FALSE; break;
	    default:	      name = NULL; size = FALSE; break;
	    }

	  if (name != NULL)
	    {
	      asection *s;

	      s = bfd_get_section_by_name (output_bfd, name);
	      if (s == NULL)
		dyn.d_un.d_val = 0;
	      else
		{
		  if (! size)
		    dyn.d_un.d_ptr = s->vma;
		  else
		    dyn.d_un.d_val = s->size;
		}
	      bed->s->swap_dyn_out (output_bfd, &dyn, dyncon);
	    }
	}
    }
  return TRUE;
}

/* Install the first PLT entry in a VxWorks executable and make sure that
   .rela.plt.unloaded relocations have the correct symbol indexes.  */

static void
ajit_vxworks_finish_exec_plt (bfd *output_bfd, struct bfd_link_info *info)
{
  struct _bfd_ajit_elf_link_hash_table *htab;
  Elf_Internal_Rela rela;
  bfd_vma got_base;
  bfd_byte *loc;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);

  /* Calculate the absolute value of _GLOBAL_OFFSET_TABLE_.  */
  got_base = (htab->elf.hgot->root.u.def.section->output_section->vma
	      + htab->elf.hgot->root.u.def.section->output_offset
	      + htab->elf.hgot->root.u.def.value);

  /* Install the initial PLT entry.  */
  bfd_put_32 (output_bfd,
	      ajit_vxworks_exec_plt0_entry[0] + ((got_base + 8) >> 10),
	      htab->elf.splt->contents);
  bfd_put_32 (output_bfd,
	      ajit_vxworks_exec_plt0_entry[1] + ((got_base + 8) & 0x3ff),
	      htab->elf.splt->contents + 4);
  bfd_put_32 (output_bfd,
	      ajit_vxworks_exec_plt0_entry[2],
	      htab->elf.splt->contents + 8);
  bfd_put_32 (output_bfd,
	      ajit_vxworks_exec_plt0_entry[3],
	      htab->elf.splt->contents + 12);
  bfd_put_32 (output_bfd,
	      ajit_vxworks_exec_plt0_entry[4],
	      htab->elf.splt->contents + 16);

  loc = htab->srelplt2->contents;

  /* Add an unloaded relocation for the initial entry's "sethi".  */
  rela.r_offset = (htab->elf.splt->output_section->vma
		   + htab->elf.splt->output_offset);
  rela.r_info = ELF32_R_INFO (htab->elf.hgot->indx, R_AJIT_HI22);
  rela.r_addend = 8;
  bfd_elf32_swap_reloca_out (output_bfd, &rela, loc);
  loc += sizeof (Elf32_External_Rela);

  /* Likewise the following "or".  */
  rela.r_offset += 4;
  rela.r_info = ELF32_R_INFO (htab->elf.hgot->indx, R_AJIT_LO10);
  bfd_elf32_swap_reloca_out (output_bfd, &rela, loc);
  loc += sizeof (Elf32_External_Rela);

  /* Fix up the remaining .rela.plt.unloaded relocations.  They may have
     the wrong symbol index for _G_O_T_ or _P_L_T_ depending on the order
     in which symbols were output.  */
  while (loc < htab->srelplt2->contents + htab->srelplt2->size)
    {
      Elf_Internal_Rela rel;

      /* The entry's initial "sethi" (against _G_O_T_).  */
      bfd_elf32_swap_reloc_in (output_bfd, loc, &rel);
      rel.r_info = ELF32_R_INFO (htab->elf.hgot->indx, R_AJIT_HI22);
      bfd_elf32_swap_reloc_out (output_bfd, &rel, loc);
      loc += sizeof (Elf32_External_Rela);

      /* The following "or" (also against _G_O_T_).  */
      bfd_elf32_swap_reloc_in (output_bfd, loc, &rel);
      rel.r_info = ELF32_R_INFO (htab->elf.hgot->indx, R_AJIT_LO10);
      bfd_elf32_swap_reloc_out (output_bfd, &rel, loc);
      loc += sizeof (Elf32_External_Rela);

      /* The .got.plt entry (against _P_L_T_).  */
      bfd_elf32_swap_reloc_in (output_bfd, loc, &rel);
      rel.r_info = ELF32_R_INFO (htab->elf.hplt->indx, R_AJIT_32);
      bfd_elf32_swap_reloc_out (output_bfd, &rel, loc);
      loc += sizeof (Elf32_External_Rela);
    }
}

/* Install the first PLT entry in a VxWorks shared object.  */

static void
ajit_vxworks_finish_shared_plt (bfd *output_bfd, struct bfd_link_info *info)
{
  struct _bfd_ajit_elf_link_hash_table *htab;
  unsigned int i;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);

  for (i = 0; i < ARRAY_SIZE (ajit_vxworks_shared_plt0_entry); i++)
    bfd_put_32 (output_bfd, ajit_vxworks_shared_plt0_entry[i],
		htab->elf.splt->contents + i * 4);
}

/* Finish up local dynamic symbol handling.  We set the contents of
   various dynamic sections here.  */

static bfd_boolean
finish_local_dynamic_symbol (void **slot, void *inf)
{
  struct elf_link_hash_entry *h
    = (struct elf_link_hash_entry *) *slot;
  struct bfd_link_info *info
    = (struct bfd_link_info *) inf; 

  return _bfd_ajit_elf_finish_dynamic_symbol (info->output_bfd, info,
					       h, NULL);
}

bfd_boolean
_bfd_ajit_elf_finish_dynamic_sections (bfd *output_bfd, struct bfd_link_info *info)
{
  bfd *dynobj;
  asection *sdyn;
  struct _bfd_ajit_elf_link_hash_table *htab;

  htab = _bfd_ajit_elf_hash_table (info);
  BFD_ASSERT (htab != NULL);
  dynobj = htab->elf.dynobj;

  sdyn = bfd_get_section_by_name (dynobj, ".dynamic");

  if (elf_hash_table (info)->dynamic_sections_created)
    {
      asection *splt;

      splt = bfd_get_section_by_name (dynobj, ".plt");
      BFD_ASSERT (splt != NULL && sdyn != NULL);

      if (!ajit_finish_dyn (output_bfd, info, dynobj, sdyn, splt))
	return FALSE;

      /* Initialize the contents of the .plt section.  */
      if (splt->size > 0)
	{
	  if (htab->is_vxworks)
	    {
	      if (info->shared)
		ajit_vxworks_finish_shared_plt (output_bfd, info);
	      else
		ajit_vxworks_finish_exec_plt (output_bfd, info);
	    }
	  else
	    {
	      memset (splt->contents, 0, htab->plt_header_size);
	      if (!ABI_64_P (output_bfd))
		bfd_put_32 (output_bfd, (bfd_vma) AJIT_NOP,
			    splt->contents + splt->size - 4);
	    }
	}

      elf_section_data (splt->output_section)->this_hdr.sh_entsize
	= (htab->is_vxworks || !ABI_64_P (output_bfd))
	  ? 0 : htab->plt_entry_size;
    }

  /* Set the first entry in the global offset table to the address of
     the dynamic section.  */
  if (htab->elf.sgot && htab->elf.sgot->size > 0)
    {
      bfd_vma val = (sdyn ?
		     sdyn->output_section->vma + sdyn->output_offset :
		     0);

      AJIT_ELF_PUT_WORD (htab, output_bfd, val, htab->elf.sgot->contents);
    }

  if (htab->elf.sgot)
    elf_section_data (htab->elf.sgot->output_section)->this_hdr.sh_entsize =
      AJIT_ELF_WORD_BYTES (htab);

  /* Fill PLT and GOT entries for local STT_GNU_IFUNC symbols.  */
  htab_traverse (htab->loc_hash_table, finish_local_dynamic_symbol, info);

  return TRUE;
}


/* Set the right machine number for a AJIT ELF file.  */
/* AJIT is  not 64  bit yet.  So  no need  to do the  detailed machine
   checks like the SPARC! */
bfd_boolean
_bfd_ajit_elf_object_p (bfd *abfd)
{
  /* if (ABI_64_P (abfd)) */
  /*   { */
  /*     unsigned long mach = bfd_mach_ajit_v9; */

  /*     if (elf_elfheader (abfd)->e_flags & EF_AJIT_SUN_US3) */
  /* 	mach = bfd_mach_ajit_v9b; */
  /*     else if (elf_elfheader (abfd)->e_flags & EF_AJIT_SUN_US1) */
  /* 	mach = bfd_mach_ajit_v9a; */
  /*     return bfd_default_set_arch_mach (abfd, bfd_arch_ajit, mach); */
  /*   } */
  /* else */
  /*   { */
  /*     if (elf_elfheader (abfd)->e_machine == EM_AJIT32PLUS) */
  /* 	{ */
  /* 	  if (elf_elfheader (abfd)->e_flags & EF_AJIT_SUN_US3) */
  /* 	    return bfd_default_set_arch_mach (abfd, bfd_arch_ajit, */
  /* 					      bfd_mach_ajit_v8plusb); */
  /* 	  else if (elf_elfheader (abfd)->e_flags & EF_AJIT_SUN_US1) */
  /* 	    return bfd_default_set_arch_mach (abfd, bfd_arch_ajit, */
  /* 					      bfd_mach_ajit_v8plusa); */
  /* 	  else if (elf_elfheader (abfd)->e_flags & EF_AJIT_32PLUS) */
  /* 	    return bfd_default_set_arch_mach (abfd, bfd_arch_ajit, */
  /* 					      bfd_mach_ajit_v8plus); */
  /* 	  else */
  /* 	    return FALSE; */
  /* 	} */
  /*     else if (elf_elfheader (abfd)->e_flags & EF_AJIT_LEDATA) */
  /* 	return bfd_default_set_arch_mach (abfd, bfd_arch_ajit, */
  /* 					  bfd_mach_ajit_ajitlite_le); */
  /*     else */
  /* 	return bfd_default_set_arch_mach (abfd, bfd_arch_ajit, bfd_mach_ajit); */
  /*   } */

  return bfd_default_set_arch_mach (abfd, bfd_arch_ajit, bfd_mach_ajit);
}

/* Return address for Ith PLT stub in section PLT, for relocation REL
   or (bfd_vma) -1 if it should not be included.  */

bfd_vma
_bfd_ajit_elf_plt_sym_val (bfd_vma i, const asection *plt, const arelent *rel)
{
  if (ABI_64_P (plt->owner))
    {
      bfd_vma j;

      i += PLT64_HEADER_SIZE / PLT64_ENTRY_SIZE;
      if (i < PLT64_LARGE_THRESHOLD)
	return plt->vma + i * PLT64_ENTRY_SIZE;

      j = (i - PLT64_LARGE_THRESHOLD) % 160;
      i -= j;
      return plt->vma + i * PLT64_ENTRY_SIZE + j * 4 * 6;
    }
  else
    return rel->address;
}

/* Merge backend specific data from an object file to the output
   object file when linking.  */

bfd_boolean
_bfd_ajit_elf_merge_private_bfd_data (bfd *ibfd, bfd *obfd)
{
  obj_attribute *in_attr, *in_attrs;
  obj_attribute *out_attr, *out_attrs;

  if (!elf_known_obj_attributes_proc (obfd)[0].i)
    {
      /* This is the first object.  Copy the attributes.  */
      _bfd_elf_copy_obj_attributes (ibfd, obfd);

      /* Use the Tag_null value to indicate the attributes have been
	 initialized.  */
      elf_known_obj_attributes_proc (obfd)[0].i = 1;

      return TRUE;
    }

  in_attrs = elf_known_obj_attributes (ibfd)[OBJ_ATTR_GNU];
  out_attrs = elf_known_obj_attributes (obfd)[OBJ_ATTR_GNU];

  in_attr = &in_attrs[Tag_GNU_Ajit_HWCAPS];
  out_attr = &out_attrs[Tag_GNU_Ajit_HWCAPS];

  out_attr->i |= in_attr->i;

  /* Merge Tag_compatibility attributes and any common GNU ones.  */
  _bfd_elf_merge_object_attributes (ibfd, obfd);

  return TRUE;
}
