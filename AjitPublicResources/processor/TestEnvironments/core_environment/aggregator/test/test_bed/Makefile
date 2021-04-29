SYS=$(AJIT_PROJECT_HOME)/processor/Aa_v3/sys
CHIP=$(SYS)/chip
CORE=$(CHIP)/core
CPU=$(CORE)/cpu
TEU=$(CPU)/teu
PARAMETERS=$(SYS)/parameters/parameters.aa $(CHIP)/parameters/parameters.aa $(CORE)/parameters/parameters.aa $(CPU)/constants/cpu_parameters.aa   $(TEU)/constants/teu_parameters.aa  $(TEU)/iunit/constants/iunit_parameters.aa $(TEU)/fpunit/constants/fpunit_parameters.aa
PIPES=$(SYS)/pipes/pipes.aa $(SYS)/pipes/signals.aa $(SYS)/pipes/strange_signals.aa $(CHIP)/pipes/pipes.aa $(CORE)/pipes/core_pipes.aa  $(CPU)/pipes/cpu_pipes.aa  $(CPU)/teu/pipes/teu_pipes.aa $(CPU)/teu/iunit/pipes/pipes.aa $(CPU)/teu/fpunit/pipes/pipes.aa

all: srcs 

srcs:aa2c/sys_test_bed_test_bed.c


aa2c/sys_test_bed_test_bed.c: test_bed.hsys  $(PARAMETERS) $(PIPES) 
	buildHierarchicalModel.py -a sys_test_bed -H $(PARAMETERS) $(PIPES)
	indent aa2c/*.c
	indent aa2c/*.h
	rm aa2c/*~


clean:
	rm -rf lib/*.a objsw/*.o vhdl/*  aa2c/*.* *.c *.h *.txt *.log


PHONY: all clean tests
