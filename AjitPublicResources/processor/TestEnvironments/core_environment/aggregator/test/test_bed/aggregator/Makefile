SYS=$(AJIT_PROJECT_HOME)/processor/Aa_v3/sys
CHIP=$(SYS)/chip
CORE=$(CHIP)/core
CPU=$(CORE)/cpu
TOPMODULES= -T aggregatorDaemon -T aggregatorListenOnDebugDaemon -T aggregatorListenOnSerialDaemon
AA2CPREFIX=sys_aggregator
AA2C_C_FILE=$(AA2CPREFIX)_aa_c_model.c
AA2CFILES=$(SYS)/pipes/pipes.aa $(CHIP)/pipes/pipes.aa $(SYS)/pipes/signals.aa $(SYS)/aggregator/aggregator.aa
AA2VHDLFILES= -A $(SYS)/pipes/pipes.aa -A $(CHIP)/pipes/pipes.aa -A $(SYS)/pipes/signals.aa  -A $(SYS)/aggregator/aggregator.aa 
          
all: vhdl/$(AA2CPREFIX)/aggregator.vhdl

vhdl/$(AA2CPREFIX)/aggregator.vhdl: $(AA2CFILES)
	buildFromSources.py -s ghdl $(DEBUG) $(GNUPTH) -U -a aggregator -W $(AA2CPREFIX) -E to_vhdl $(TOPMODULES) $(AA2VHDLFILES) 
	rm aa2c/*


clean:
	rm -rf vhdl/* aa2c/* *.c *.h *.txt .Aa .vC .objhw *.unformatted_vhdl *.hsys lib/*

PHONY: clean
