#!/bin/bash
# run this script to generate hierarchical model for the iunit.
# to generate debug messages in the vhdl simulation, use -D
buildHierarchicalModel.py  -R -a acb_test_setup
make clean
rm -f ghdl/*.o ghdl/*.cf ghdl/*.ghw ghdl/acb_*_test_bench
