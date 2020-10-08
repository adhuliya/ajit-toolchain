/* BFD support for the AJIT architecture.
   Copyright 1992, 1995, 1996, 1998, 2000, 2002, 2005, 2007
   Free Software Foundation, Inc.

   Copyright 2018, 2019, 2020 IIT Bombay.

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
    bfd_arch_ajit,	      /* One of enum bfd_architecture, defined
				 in   archures.c   and   provided   in
				 generated header files.  */
    bfd_mach_ajit,		/* Random BFD-internal number for this
				   machine,    similarly   listed   in
				   archures.c.     Not    emitted   in
				   output.  */
    "ajit",			/* The architecture name */
    "ajit",			/* Printable name */
    3,				/* Section alignment power; each section
				   is aligned to (only) 2^3 bytes.  */
    TRUE,			/* This is the default machine. */
    bfd_default_compatible,	/* A  function  for testing  "machine"
				   compatibility         of        two
				   bfd_arch_info_type.  */
    bfd_default_scan,		/* Check if  a bfd_arch_info_type is a
				   match.  */
    NULL		        /* Pointer  to next bfd_arch_info_type
				   in the same family.  */
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
    NULL,
  };
