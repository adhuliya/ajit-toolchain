#!/usr/bin/env python3

# Author: Anshuman Dhuliya (AD) (anshumandhuliya@gmail.com)

"""
Routines to copy various files.

All the routines assume that the current working directory is the destination.
"""

import os.path as osp

import cortos.sys.config as config
from cortos.common import bottle as btl

from cortos.common import consts, util


def copyTrapFile(
    confObj: config.UserConfig,
) -> None:
  with open(consts.TRAP_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_asms/{consts.TRAP_FILE_NAME}"))


def copyPageTableFile(
    confObj: config.UserConfig,
) -> None:
  with open(consts.PAGE_TABLE_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_asms/{consts.PAGE_TABLE_FILE_NAME}"))


def copyVmapFile(
    confObj: config.UserConfig,
) -> None:
  with open(consts.VMAP_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.VMAP_FILE_NAME}"))


def copyCortosHeaderFile(
    confObj: config.UserConfig,
) -> None:
  with open(consts.CORTOS_HEADER_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.CORTOS_HEADER_FILE_NAME}",
                         confObj=confObj,
                         consts=consts,
                         LogLevel=consts.LogLevel,
                         cortosQueueLength=consts.DEFAULT_QUEUE_LEN,
                         cortosQueueMsgSize=consts.DEFAULT_QUEUE_MSG_SIZE,
                         cortosQueueHeaderSize=consts.QUEUE_HEADER_SIZE,
                         ))


def copyCortosInternalHeaderFile(
    confObj: config.UserConfig,
) -> None:
  with open(consts.CORTOS_INTERNAL_HEADER_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.CORTOS_INTERNAL_HEADER_FILE_NAME}",
                         confObj=confObj,
                         consts=consts,
                         LogLevel=consts.LogLevel,
                         cortosQueueLength=consts.DEFAULT_QUEUE_LEN,
                         cortosQueueMsgSize=consts.DEFAULT_QUEUE_MSG_SIZE,
                         cortosQueueHeaderSize=consts.QUEUE_HEADER_SIZE,
                         ))


def copyCortosAsmFile(
    confObj: config.UserConfig,
) -> None:
  with open(consts.CORTOS_ASM_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_asms/{consts.CORTOS_ASM_FILE_NAME}",
                         confObj=confObj))


def copyCortosCFile(
    confObj: config.UserConfig,
) -> None:
  with open(consts.CORTOS_C_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.CORTOS_C_FILE_NAME}",
                         confObj=confObj))


def copyCortosPrintfFile(
    confObj: config.UserConfig,
) -> None:
  with open(consts.CORTOS_PRINTF_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.CORTOS_PRINTF_FILE_NAME}",
                         confObj=confObj))


def copyLockFiles(
    confObj: config.UserConfig,
) -> None:
  with open(consts.LOCK_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.LOCK_FILE_NAME}", confObj=confObj))

  with open(consts.RES_LOCK_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.RES_LOCK_FILE_NAME}", confObj=confObj))


def copyLinkerScriptFile(
    confObj: config.UserConfig,
) -> None:
  with open(consts.LINKER_SCRIPT_FILE_NAME, "w") as f:
    f.write(btl.template(f"linker_scripts/{consts.LINKER_SCRIPT_00_FILE_NAME}"))


def copyProjectFiles(
    confObj: config.UserConfig,
) -> None:
  # copy all .c files
  util.runCommand(f"cp {confObj.rootDir}/*.c .")
  # copy all .h files
  util.runCommand(f"cp {confObj.rootDir}/*.h .", suppressError=True)
  # copy results file
  if confObj.resultsFile:
    util.runCommand(f"cp {confObj.rootDir}/{confObj.resultsFile} .")


def copyInitFile(
    confObj: config.UserConfig,
) -> None:
  print(f"CoRTOS: AllocRegionSize: {confObj.reservedMem.sizeInBytes} bytes.")
  with open(consts.INIT_00_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_init/{consts.INIT_00_FILE_NAME}",
                         confObj=confObj))


def copyBuildshFile(
    confObj: config.UserConfig,
) -> None:
  with open(consts.FINAL_BUILD_SH_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_sh/{consts.FINAL_BUILD_SH_FILE_NAME}",
                           confObj=confObj))


def copyCleanshFile(
    confObj: config.UserConfig,
) -> None:
  with open(consts.CLEAN_SH_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_sh/{consts.CLEAN_SH_FILE_NAME}",
                         confObj=confObj))


def copyRunCModelFile(confObj: config.UserConfig) -> None:
  with open(consts.RUN_CMODEL_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.RUN_CMODEL_FILE_NAME}", confObj=confObj))
  util.runCommand(f"chmod +x {consts.RUN_CMODEL_FILE_NAME}")


def copyResultsFile(confObj: config.UserConfig) -> None:
  # Get user defined results
  userResults = ""
  resFilePath = osp.join(confObj.rootDir, confObj.resultsFile)
  if osp.exists(resFilePath):
    userResults = f"{util.readFromFile(resFilePath).strip()}\n"

  # Add results to append
  appendResults = btl.template(f"{consts.DEFAULT_RESULTS_FILE_NAME}",
                               confObj=confObj)

  with open(consts.DEFAULT_RESULTS_FILE_NAME, "w") as f:
    f.write(userResults)
    f.write(appendResults)


def copyCortosQueueFiles(confObj: config.UserConfig) -> None:
  with open(consts.QUEUE_C_FILE, "w") as f:
    f.write(btl.template(f"queue/{consts.QUEUE_C_FILE}", confObj=confObj))

  with open(consts.QUEUE_LOCK_FILE, "w") as f:
    f.write(btl.template(f"queue/{consts.QUEUE_LOCK_FILE}", confObj=confObj))


def copyCortosBgetFiles(confObj: config.UserConfig) -> None:
  with open(consts.CORTOS_BGET_C_FILE, "w") as f:
    f.write(btl.template(f"bget/{consts.CORTOS_BGET_C_FILE}",
                         confObj=confObj,
                         bgetLockIndex=consts.BGET_RES_LOCK_INDEX))

  with open(consts.BGET_C_FILE, "w") as f:
    f.write(btl.template(f"bget/{consts.BGET_C_FILE}", confObj=confObj))

  with open(consts.BGET_H_FILE, "w") as f:
    f.write(btl.template(f"bget/{consts.BGET_H_FILE}", confObj=confObj))

