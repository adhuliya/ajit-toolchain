COMMON=$(AJIT_PROJECT_HOME)/processor/Aa_v3/aa_common
PIPES=$(COMMON)/sys_pipes.aa  debug_aggregator/Aa/pipes.aa 

all: srcs 

srcs:aa2c/adm_test_lib_adm_test_setup.c


aa2c/adm_test_lib_adm_test_setup.c: adm_test_setup.hsys  $(PARAMETERS) $(PIPES) 
	buildHierarchicalModel.py -s ghdl -a adm_test_setup -D -I$(AHIR_RELEASE)/include -H $(PARAMETERS) $(PIPES)


clean:
	rm -rf lib/*.a objsw/*.o vhdl/*  aa2c/*.* *.c *.h *.txt *.log


PHONY: all clean tests
