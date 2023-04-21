#!/bin/sh


# run AJIT C Model on the generated mmap file
_MAIN="main";
ajit_C_system_model \
  -R 123456 \
  -n 1 \
  -t 1 \
  -i 0x40000000 \
  -m ${_MAIN}.mmap.remapped \
  -w ${_MAIN}.wtrace \
  -r main.results \
  -l ${_MAIN}.log \
  -u 64 \
;
