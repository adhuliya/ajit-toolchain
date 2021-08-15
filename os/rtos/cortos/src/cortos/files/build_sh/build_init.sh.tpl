#!/bin/sh

_MAIN="main";
_CORTOS_VMAP="vmap.txt";
_CORTOS_ASM="cortos_asm.s";
_CORTOS_C="cortos.c";
_CORTOS_PRINTF="cortos_printf.c";
_CORTOS_LOCK_UNLOCK="./cortos_lock_unlock.s";
_CORTOS_RES_LOCK_UNLOCK="./cortos_res_lock_unlock.s";
_CORTOS_Q_LOCK_UNLOCK="./cortos_q_lock_unlock.s";
_CORTOS_MSG_QUEUE="./cortos_msg_queue.c";
_CORTOS_INIT_00="./init_00.s";
_CORTOS_PG_TABLES="./setup_page_tables.s";
_CORTOS_TRAP_HANDLER="./trap_handlers.s";
_LINKER_SCRIPT="./LinkerScript.txt";

_PT="$AJIT_MINIMAL_PRINTF_TIMER";
_AAR_MT="$AJIT_PROJECT_HOME/tools/ajit_access_routines_mt";
_AAR="$AJIT_ACCESS_ROUTINES";

% if confObj.addBget:
_CORTOS_BGET="./cortos_bget.c";
_BGET="./bget.c";
% end


# genVmapAsm ${_CORTOS_VMAP} ${_CORTOS_PG_TABLES};
#  -s $_CORTOS_PG_TABLES \

# NOTE: the use of `-U` to enable uclibc
compileToSparcUclibc.py \
% if confObj.debugBuild:
  -g \
% end
  -V ${_CORTOS_VMAP} \
  -I ${AJIT_UCLIBC_HEADERS_DIR} \
  -I ${AJIT_LIBGCC_INSTALL_DIR}/include \
  -I . \
  -I ${_AAR}/include \
  -I ${_PT}/include \
  -s ${_CORTOS_INIT_00} \
  -s ${_CORTOS_ASM} \
  -s ${_CORTOS_TRAP_HANDLER} \
  -s ${_CORTOS_LOCK_UNLOCK} \
  -s ${_CORTOS_RES_LOCK_UNLOCK} \
  -s ${_CORTOS_Q_LOCK_UNLOCK} \
% for fileName in confObj.cFileNames:
  -c {{fileName}} \
% end
  -c ${_CORTOS_MSG_QUEUE} \
  -c ${_CORTOS_C} \
  -c ${_CORTOS_PRINTF} \
  -C ${_AAR}/src \
% if False: # FIXME: to remove ee_printf
  -C ${_PT}/src \
% end
% if confObj.addBget:
  -c ${_CORTOS_BGET} \
  -c ${_BGET} \
% end
  -N ${_MAIN} \
  -L ${_LINKER_SCRIPT} \
  -D AJIT \
  -U;

