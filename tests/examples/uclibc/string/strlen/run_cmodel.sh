#!/bin/sh

# run AJIT C Model on the generated mmap file
MAIN=main
ajit_C_system_model -m ${MAIN}.mmap -w ${MAIN}.wtrace -d -r ${MAIN}.results -l ${MAIN}.log
