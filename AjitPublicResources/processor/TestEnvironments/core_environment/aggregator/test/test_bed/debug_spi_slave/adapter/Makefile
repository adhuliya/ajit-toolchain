SYS=$(AJIT_PROJECT_HOME)/processor/Aa_v3/sys
CHIP=$(SYS)/chip/
CORE=$(CHIP)/core
CPU=$(CORE)/cpu
TOPMODULES= -T debugAdapterDaemon
AA2CPREFIX=debug_spi_slave_adapter
AA2C_C_FILE=$(AA2CPREFIX)_aa_c_model.c
AA2CFILES=$(CHIP)/pipes/pipes.aa $(CHIP)/utilities/utilities.aa debug_adapter.aa
AA2VHDLFILES= -A $(CHIP)/pipes/pipes.aa -A $(CHIP)/utilities/utilities.aa -A debug_adapter.aa 
          
all: aa2c/$(AA2CPREFIX)_aa_c_model.c

aa2c/$(AA2C_C_FILE): $(AA2CFILES)
	buildFromSources.py -s ghdl $(DEBUG) $(GNUPTH) -U -a debug_adapter -W $(AA2CPREFIX) -E to_vhdl $(TOPMODULES) $(AA2VHDLFILES) 


clean:
	rm -rf vhdl/* aa2c/* *.c *.h *.txt .Aa .vC .objhw *.unformatted_vhdl *.hsys lib/*

PHONY: clean
