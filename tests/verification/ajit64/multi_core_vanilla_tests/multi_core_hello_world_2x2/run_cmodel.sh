#!/bin/sh

# run AJIT C Model on the generated mmap file
MAIN=mem_bw
ajit_C_system_model -n 2 -t 2 -m ${MAIN}.mmap -w ${MAIN}.wtrace -d -r ${MAIN}.results -l ${MAIN}.log

