#!/usr/bin/env sh

# Cleans up the temporary build xfiles, output xfiles and log xfiles.

rm -rf \
  *.elf \
  *.hex \
  *.log \
  *.mmap* \
  *.objdump \
  *.vars \
  *.wtrace* \
  sparc-assembly \
  sparc-obj \
  __genvmap_setup_page_tables.s \
;