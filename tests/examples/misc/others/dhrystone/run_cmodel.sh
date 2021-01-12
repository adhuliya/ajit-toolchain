#!/bin/sh

# run AJIT C Model on the generated mmap file
MAIN=dhry_1
ajit_C_system_model -m ${MAIN}.mmap -w ${MAIN}.wtrace -d -r ${MAIN}.results -l ${MAIN}.log
