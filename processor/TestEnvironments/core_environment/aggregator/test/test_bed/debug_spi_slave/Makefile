SYS=$(AJIT_PROJECT_HOME)/processor/Aa_v3/sys
CHIP=$(SYS)/chip
CORE=$(CHIP)/core
CPU=$(CORE)/cpu
PIPES=$(CHIP)/pipes/signals.aa $(CHIP)/pipes/pipes.aa

all: srcs 

srcs:vhdl/chip_debug_spi_slave/debug_spi_slave.vhdl


vhdl/chip_debug_spi_slave/debug_spi_slave.vhdl: debug_spi_slave.hsys $(PIPES) 
	buildHierarchicalModel.py -a chip_core -H  $(PIPES)
	rm -rf aa2c/*

clean:
	rm -rf lib/*.a objsw/*.o vhdl/*  aa2c/*.* *.c *.h *.txt *.log

PHONY: all clean tests
