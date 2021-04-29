#!/bin/bash
# run this script to generate hierarchical model for the iunit.
# to generate debug messages in the vhdl simulation, use -D
buildHierarchicalModel.py -s ghdl -a sys_test_bed  -M -I$AHIR_RELEASE/include
make clean
make
buildGhdlSimulationModel.py -o ghdl/ghdl.do -t vhdl/testbench/test_bed_test_bench.vhdl
cd ghdl
. ghdl.do
cd -
