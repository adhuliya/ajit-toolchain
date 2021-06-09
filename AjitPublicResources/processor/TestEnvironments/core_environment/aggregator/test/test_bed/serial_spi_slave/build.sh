#!/bin/bash
# run this script to generate hierarchical model for the iunit.
# to generate debug messages in the vhdl simulation, use -D
buildHierarchicalModel.py -D -a chip_serial_spi_slave  -M -I$AHIR_RELEASE/include
make clean
make
