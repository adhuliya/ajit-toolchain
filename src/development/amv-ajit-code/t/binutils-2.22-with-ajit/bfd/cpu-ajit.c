/* BFD support for the AJIT architecture.
   Copyright 1992, 1995, 1996, 1998, 2000, 2002, 2005, 2007
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

#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"

static const bfd_arch_info_type arch_info_struct[] =
{
  {
    32,	/* bits in a word */
    32,	/* bits in an address */
    8,	/* bits in a byte */
    bfd_arch_ajit,
    bfd_mach_ajit_ajitlet,
    "ajit",
    "ajit:ajitlet",
    3,
    FALSE,
    bfd_default_compatible,
    bfd_default_scan,
    &arch_info_struct[1],
  },
  {
    32,	/* bits in a word */
    32,	/* bits in an address */
    8,	/* bits in a byte */
    bfd_arch_ajit,
    bfd_mach_ajit_ajitlite,
    "ajit",
    "ajit:ajitlite",
    3,
    FALSE,
    bfd_default_compatible,
    bfd_default_scan,
    &arch_info_struct[2],
  },
  {
    32,	/* bits in a word */
    32,	/* bits in an address */
    8,	/* bits in a byte */
    bfd_arch_ajit,
    bfd_mach_ajit_v8plus,
    "ajit",
    "ajit:v8plus",
    3,
    FALSE,
    bfd_default_compatible,
    bfd_default_scan,
    &arch_info_struct[3],
  },
  {
    32,	/* bits in a word */
    32,	/* bits in an address */
    8,	/* bits in a byte */
    bfd_arch_ajit,
    bfd_mach_ajit_v8plusa,
    "ajit",
    "ajit:v8plusa",
    3,
    FALSE,
    bfd_default_compatible,
    bfd_default_scan,
    &arch_info_struct[4],
  },
  {
    32,	/* bits in a word */
    32,	/* bits in an address */
    8,	/* bits in a byte */
    bfd_arch_ajit,
    bfd_mach_ajit_ajitlite_le,
    "ajit",
    "ajit:ajitlite_le",
    3,
    FALSE,
    bfd_default_compatible,
    bfd_default_scan,
    &arch_info_struct[5],
  },
  {
    64,	/* bits in a word */
    64,	/* bits in an address */
    8,	/* bits in a byte */
    bfd_arch_ajit,
    bfd_mach_ajit_v9,
    "ajit",
    "ajit:v9",
    3,
    FALSE,
    bfd_default_compatible,
    bfd_default_scan,
    &arch_info_struct[6],
  },
  {
    64,	/* bits in a word */
    64,	/* bits in an address */
    8,	/* bits in a byte */
    bfd_arch_ajit,
    bfd_mach_ajit_v9a,
    "ajit",
    "ajit:v9a",
    3,
    FALSE,
    bfd_default_compatible,
    bfd_default_scan,
    &arch_info_struct[7],
  },
  {
    32,	/* bits in a word */
    32,	/* bits in an address */
    8,	/* bits in a byte */
    bfd_arch_ajit,
    bfd_mach_ajit_v8plusb,
    "ajit",
    "ajit:v8plusb",
    3,
    FALSE,
    bfd_default_compatible,
    bfd_default_scan,
    &arch_info_struct[8],
  },
  {
    64,	/* bits in a word */
    64,	/* bits in an address */
    8,	/* bits in a byte */
    bfd_arch_ajit,
    bfd_mach_ajit_v9b,
    "ajit",
    "ajit:v9b",
    3,
    FALSE,
    bfd_default_compatible,
    bfd_default_scan,
    0,
  }
};

const bfd_arch_info_type bfd_ajit_arch =
  {
    32,	/* bits in a word */
    32,	/* bits in an address */
    8,	/* bits in a byte */
    bfd_arch_ajit,
    bfd_mach_ajit,
    "ajit",
    "ajit",
    3,
    TRUE, /* the default */
    bfd_default_compatible,
    bfd_default_scan,
    &arch_info_struct[0],
  };
