SYS=$(AJIT_PROJECT_HOME)/processor/Aa_v3/sys
CHIP=$(SYS)/chip
CORE=$(CHIP)/core
CPU=$(CORE)/cpu
TOPMODULES= -T consoleDaemon -T debugDaemon
AA2CPREFIX=sys_chip_stub
AA2C_C_FILE=$(AA2CPREFIX)_aa_c_model.c
AA2CFILES=$(SYS)/pipes/pipes.aa $(CHIP)/pipes/pipes.aa $(CORE)/pipes/core_pipes.aa $(SYS)/pipes/signals.aa chip_stub.aa
AA2VHDLFILES= -A $(SYS)/pipes/pipes.aa -A $(CHIP)/pipes/pipes.aa -A $(CORE)/pipes/core_pipes.aa -A $(SYS)/pipes/signals.aa  -A chip_stub.aa 
          
all: vhdl/$(AA2CPREFIX)/chip_stub.vhdl

vhdl/$(AA2CPREFIX)/chip_stub.vhdl: $(AA2CFILES)
	buildFromSources.py -s ghdl $(DEBUG) $(GNUPTH) -U -a chip_stub -W $(AA2CPREFIX) -E to_vhdl $(TOPMODULES) $(AA2VHDLFILES) 
	rm aa2c/*


clean:
	rm -rf vhdl/* aa2c/* *.c *.h *.txt .Aa .vC .objhw *.unformatted_vhdl *.hsys lib/*

PHONY: clean
