#!/bin/bash
# run this script to generate hierarchical model for the iunit.
# to generate debug messages in the vhdl simulation, use -D
buildHierarchicalModel.py -a adm_test_setup  -M -I$AHIR_RELEASE/include
make clean
make
