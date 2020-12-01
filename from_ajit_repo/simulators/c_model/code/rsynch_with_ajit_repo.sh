#!/bin/bash
# copy over everything.
rsync -r $AJIT_PROJECT_HOME/processor/64bit/C/ ./
# checkout the Scons related files which would have
# been overwritten by the rsync above.
git checkout ./SConscript
git checkout ./char_client_server/SConscript
git checkout ./cpu/SConscript
git checkout ./mmu/SConscript
git checkout ./debugger/SConscript
git checkout ./debugger/doval/SConscript
git checkout ./debugger/doval/grammar/SConscript
git checkout ./debugger/doval/antlr3Cruntime/SConscript
git checkout ./debugger/spi_common/SConscript
git checkout ./debugger/gpb/SConscript
git checkout ./debugger/hwServer/SConscript
git checkout ./monitorLogger/SConscript
git checkout ./cache/SConscript
git checkout ./cpu_interface/SConscript
git checkout ./common/SConscript
git checkout ./rlut/SConscript
git checkout ./testbench/SConscript
git checkout ./devices/SConscript
git checkout ./half_precision_float/SConscript
git checkout ./memory/SConscript
git checkout ./bridge/SConscript
git checkout ./console/SConscript
git checkout ./SConstruct
git checkout ./char_client_server/SConstruct
git checkout ./cpu/SConstruct
git checkout ./mmu/SConstruct
git checkout ./debugger/doval/SConstruct
git checkout ./debugger/doval/antlr3Cruntime/SConstruct
git checkout ./debugger/gpb/SConstruct
git checkout ./debugger/hwServer/SConstruct
git checkout ./monitorLogger/SConstruct
git checkout ./cache/SConstruct
git checkout ./cpu_interface/SConstruct
git checkout ./rlut/SConstruct
git checkout ./testbench/SConstruct
git checkout ./half_precision_float/SConstruct
git checkout ./bridge/SConstruct
git checkout ./console/SConstruct
