SYS=$(AJIT_PROJECT_HOME)/processor/Aa_v3/sys
CHIP=$(SYS)/chip
CORE=$(CHIP)/core
CPU=$(CORE)/cpu
TEU=$(CPU)/teu
TOPMODULES=-T icache_interface_daemon -T dcache_interface_daemon
VHDLLIB=cache_c_interface_
AA2CPREFIX=$(VHDLLIB)_
AA2C_C_FILE=$(AA2CPREFIX)aa_c_model.c
AA2CFILES=$(CORE)/constants/core_constants.aa cache_c_interface.aa
AA2VHDLFILES= -A $(CORE)/constants/core_constants.aa -A  cache_c_interface.aa

all:aa2c/cache_c_interface_aa_c_model.c
          
aa2c/cache_c_interface_aa_c_model.c: $(AA2CFILES)
	buildFromSources.py  $(SIMULATOR) $(DEBUG) $(GNUPTH) -U -a cache_c_interface -W $(VHDLLIB) -E to_vhdl $(TOPMODULES) $(AA2VHDLFILES)


clean:
	rm -rf vhdl/* aa2c/* *.c *.h *.txt .Aa .vC

PHONY: clean
