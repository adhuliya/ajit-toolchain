#!/bin/sh

# run AJIT C Model on the generated mmap file
_MAIN="main";
ajit_C_system_model \
  -n 1 \
  -t 2 \
  -m ${_MAIN}.mmap \
  -w ${_MAIN}.wtrace \
  -d \
  -r ${_MAIN}.results \
  -l ${_MAIN}.log;
