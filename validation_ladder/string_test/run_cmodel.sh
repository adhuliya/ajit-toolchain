#!/bin/sh


# run AJIT C Model on the generated mmap file
_MAIN="main";
ajit_C_system_model \
  -R 123456 \
  -n 1 \
  -t 1 \
  -i 0x40000000 \
  -m cortos_build/${_MAIN}.mmap.remapped \
  -w cortos_build/${_MAIN}.wtrace \
  -r cortos_build/main.results \
  -l cortos_build/${_MAIN}.log \
  -u 64 \
;
