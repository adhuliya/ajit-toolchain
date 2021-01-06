#!/bin/sh

MAIN=sat_pos
#ajit_C_system_model -m ${MAIN}.mmap.remapped -w ${MAIN}.wtrace -d -r ${MAIN}.results -l ${MAIN}.log
ajit_C_system_model -m ${MAIN}.mmap.remapped -w ${MAIN}.wtrace -l ${MAIN}.log
