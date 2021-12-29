#!/usr/bin/env python3

# Author: Anshuman Dhuliya (AD) (anshumandhuliya@gmail.com)

"""
Routines to copy various xfiles.

All the routines assume that the current working directory is the destination.
"""
import os
import os.path as osp

from cortos2.sys.config import config
from cortos2.common import bottle as btl

from cortos2.common import consts, util


def copyTrapFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.TRAP_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_asms/{consts.TRAP_FILE_NAME}"))


def copyPageTableFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.PAGE_TABLE_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_asms/{consts.PAGE_TABLE_FILE_NAME}"))


def copyVmapFile(
    confObj: config.SystemConfig,
) -> None:
  """Automatically generate vmap file entries."""
  with open(consts.VMAP_FILE_NAME, "w") as f:
    for region in confObj.memoryLayout.regionSeq:
      for line in region.getVmapFileEntryLines():
        f.write(line)
    #OLD: f.write(btl.template(f"{consts.VMAP_FILE_NAME}"))


def copyCortosHeaderFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.CORTOS_HEADER_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.CORTOS_HEADER_FILE_NAME}",
                         confObj=confObj,
                         consts=consts,
                         LogLevel=consts.LogLevel,
                         cortosQueueLength=consts.DEFAULT_QUEUE_LEN,
                         cortosQueueMsgSize=consts.DEFAULT_QUEUE_MSG_SIZE_IN_BYTES,
                         cortosQueueHeaderSize=consts.QUEUE_HEADER_SIZE_IN_BYTES,
                         ))


def copyCortosInternalHeaderFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.CORTOS_INTERNAL_HEADER_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.CORTOS_INTERNAL_HEADER_FILE_NAME}",
                         confObj=confObj,
                         consts=consts,
                         LogLevel=consts.LogLevel,
                         cortosQueueLength=consts.DEFAULT_QUEUE_LEN,
                         cortosQueueMsgSize=consts.DEFAULT_QUEUE_MSG_SIZE_IN_BYTES,
                         cortosQueueHeaderSize=consts.QUEUE_HEADER_SIZE_IN_BYTES,
                         ))


def copyCortosAsmFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.CORTOS_ASM_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_asms/{consts.CORTOS_ASM_FILE_NAME}",
                         confObj=confObj))


def copyCortosCFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.CORTOS_C_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.CORTOS_C_FILE_NAME}",
                         confObj=confObj))


def copyCortosPrintfFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.CORTOS_PRINTF_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.CORTOS_PRINTF_FILE_NAME}",
                         confObj=confObj))

  with open(consts.CORTOS_PRINTF_CVT_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.CORTOS_PRINTF_CVT_FILE_NAME}",
                         confObj=confObj))


def copyLockFiles(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.LOCK_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.LOCK_FILE_NAME}", confObj=confObj))

  with open(consts.CACHEABLE_LOCK_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.CACHEABLE_LOCK_FILE_NAME}", confObj=confObj))

  with open(consts.RES_LOCK_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.RES_LOCK_FILE_NAME}", confObj=confObj))


def copyLinkerScriptFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.LINKER_SCRIPT_FILE_NAME, "w") as f:
    f.write(btl.template(f"linker_scripts/{consts.LINKER_SCRIPT_XX_FILE_NAME}", confObj=confObj))


def copyProjectFiles(
    confObj: config.SystemConfig,
) -> None:
  # copy all .c xfiles
  util.runCommand(f"cp {confObj.projectFiles.rootDir}/*.c .")
  # copy all .h xfiles
  util.runCommand(f"cp {confObj.projectFiles.rootDir}/*.h .", suppressError=True)
  # copy results file
  if confObj.projectFiles.resultsFile:
    util.runCommand(f"cp {confObj.projectFiles.rootDir}/{confObj.projectFiles.resultsFile} .")


def copyInitFile(
    confObj: config.SystemConfig,
) -> None:
  print(f"CoRTOS: AllocRegionSize: {confObj.memoryLayout.memory.sizeInBytes} bytes.")
  with open(consts.INIT_00_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_init/{consts.INIT_00_FILE_NAME}",
                         confObj=confObj))


def copyBuildshFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.FINAL_BUILD_SH_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_sh/{consts.FINAL_BUILD_SH_FILE_NAME}",
                           confObj=confObj))


def copyCleanshFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.CLEAN_SH_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_sh/{consts.CLEAN_SH_FILE_NAME}",
                         confObj=confObj))


def copyRunCModelFile(confObj: config.SystemConfig) -> None:
  with open(consts.RUN_CMODEL_FILE_NAME, "w") as f:
    f.write(btl.template(f"{consts.RUN_CMODEL_FILE_NAME}", confObj=confObj))
  util.runCommand(f"chmod +x {consts.RUN_CMODEL_FILE_NAME}")


def copyResultsFile(confObj: config.SystemConfig) -> None:
  # Get user defined results
  userResults = ""
  resFilePath = osp.join(confObj.projectFiles.rootDir, confObj.projectFiles.resultsFile)
  if osp.exists(resFilePath):
    userResults = f"{util.readFromFile(resFilePath).strip()}\n"

  # Add results to append
  appendResults = btl.template(f"{consts.DEFAULT_RESULTS_FILE_NAME}",
                               confObj=confObj)

  with open(consts.DEFAULT_RESULTS_FILE_NAME, "w") as f:
    f.write(userResults)
    f.write(appendResults)


def copyCortosQueueFiles(confObj: config.SystemConfig) -> None:
  with open(consts.QUEUE_C_FILE, "w") as f:
    f.write(btl.template(f"queue/{consts.QUEUE_C_FILE}", confObj=confObj))

  with open(consts.QUEUE_LOCK_FILE, "w") as f:
    f.write(btl.template(f"queue/{consts.QUEUE_LOCK_FILE}", confObj=confObj))


def copyCortosBgetFiles(confObj: config.SystemConfig) -> None:
  with open(consts.CORTOS_BGET_C_FILE, "w") as f:
    f.write(btl.template(f"bget/{consts.CORTOS_BGET_C_FILE}",
                         confObj=confObj,
                         bgetLockIndex=consts.BGET_RES_LOCK_INDEX))

  with open(consts.BGET_C_FILE, "w") as f:
    f.write(btl.template(f"bget/{consts.BGET_C_FILE}", confObj=confObj))

  with open(consts.BGET_H_FILE, "w") as f:
    f.write(btl.template(f"bget/{consts.BGET_H_FILE}", confObj=confObj))

