
# This is a bash script to build the cortos project.
# It generates a mmap file which is used in the `run_cmodel.sh`,
# to run the program on the C simulator.

_MAIN="main";
_CORTOS_SRC_DIR="cortos_src";

_CORTOS_VMAP="$_CORTOS_SRC_DIR/vmap.txt";
_LINKER_SCRIPT="$_CORTOS_SRC_DIR/LinkerScript.txt";

_PT="$AJIT_MINIMAL_PRINTF_TIMER";
_AAR_MT="$AJIT_ACCESS_ROUTINES_MT";
_AAR="$AJIT_ACCESS_ROUTINES";
_IEEE_SOFT_FLOAT_LIB="$AJIT_HOME/application_development/soft_float/ieeelib/"
# {{ confObj.software.build.debug }}
compileToSparcUclibc.py \
% if confObj.software.build.debug:
  -g \
% end
  -o {{ confObj.software.build.optLevel }} \
% if confObj.hardware.cpu.mmu:
  -V ${_CORTOS_VMAP} \
% end
  -I ${AJIT_UCLIBC_HEADERS_DIR} \
  -I ${AJIT_LIBGCC_INSTALL_DIR}/include \
  -I . \
  -I .. \
  -I ${_CORTOS_SRC_DIR} \
  -I ${_AAR_MT}/include \
  -I ${_PT}/include \
  -S .. \
  -S ${_CORTOS_SRC_DIR} \
  -C .. \
  -C ${_CORTOS_SRC_DIR} \
  -l .. \
  -N ${_MAIN} \
  -L ${_LINKER_SCRIPT} \
% if confObj.software.build.useLibAjit:
  -l ${_AAR_MT}/lib\
  % if  confObj.software.build.useDefaultLibAjit:
    -a ajit_default\
  % else:
    -a ajit_alt\
  % end
% else :
  -s ${_AAR_MT}/asm/clear_stack_pointers.s \
  -s ${_AAR_MT}/asm/generic_isr_mt.s \
  -s ${_AAR_MT}/asm/generic_sw_trap_mt.s \
  -s ${_AAR_MT}/asm/generic_sys_calls.s \
  -s ${_AAR_MT}/asm/mutexes.s \
  -C ${_AAR_MT}/src \
% end
  -D AJIT \
  -U \
  {{ confObj.software.build.buildArgs }};

#  -s ${_AAR_MT}/asm/clear_stack_pointers.s \
#  -s ${_AAR_MT}/asm/trap_handlers_for_rtos.s \
#  -s ${_AAR_MT}/asm/generic_isr_mt.s \
#  -s ${_AAR_MT}/asm/generic_sw_trap_mt.s \
#  -C ${_AAR}/src \
#  -S ${_AAR_MT}/asm \
