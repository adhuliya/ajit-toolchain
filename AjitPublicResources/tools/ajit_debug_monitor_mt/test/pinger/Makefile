AA_COMMON=$(AJIT_PROJECT_HOME)/processor/Aa_v3/aa_common
TOPMODULES=-T ping_daemon_0_0 -T ping_daemon_0_1 -T ping_daemon_1_0 -T ping_daemon_1_1  -T ping_daemon_2_0 -T ping_daemon_2_1 -T ping_daemon_3_0 -T ping_daemon_3_1
VHDLLIB=adm_test_lib
AA2CPREFIX=$(VHDLLIB)_
AA2C_C_FILE=$(AA2CPREFIX)aa_c_model.c
AA2CFILES= pinger_base.aa pinger_incl.aa $(AA_COMMON)/sys_pipes.aa  ../debug_aggregator/Aa/pipes.aa 
AA2VHDLFILES= -A pinger.preprocessed.aa -A $(AA_COMMON)/sys_pipes.aa  -A ../debug_aggregator/Aa/pipes.aa

all: aa2c 

aa2c:aa2c/$(AA2C_C_FILE)
          
aa2c/adm_test_lib_aa_c_model.c: $(AA2CFILES)
	AaPreprocess -I ./ pinger_incl.aa -o pinger.preprocessed.aa 
	buildFromSources.py -B $(SIMULATOR) $(DEBUG) $(GNUPTH) -a pinger -W $(VHDLLIB) -E to_vhdl $(TOPMODULES) $(AA2VHDLFILES)

clean:
	rm -rf vhdl/* aa2c/* *.c *.h *.txt .Aa .vC  .objhw  .*.aa

PHONY: clean
