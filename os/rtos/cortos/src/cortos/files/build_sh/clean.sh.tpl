#!/usr/bin/env sh

# Cleans up the temporary build files, output files and log files.

rm -rf \
  *.elf \
  *.hex \
  *.log \
  *.mmap* \
  *.objdump \
  *.vars \
  *.wtrace* \
  sparc-assembly \
  sparc-obj