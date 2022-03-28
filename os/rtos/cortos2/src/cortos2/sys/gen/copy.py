#!/usr/bin/env python3

# Author: Anshuman Dhuliya (AD) (anshumandhuliya@gmail.com)

"""
Routines to copy various xfiles.

All the routines assume that the current working directory is the destination.
"""
import os.path as osp

from cortos2.sys.config import config
from cortos2.common import bottle as btl

from cortos2.common import consts, util


def copyTrapFiles(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.TRAP_H_FILE_NAME, "w") as f:
    f.write(btl.template(f"traps/{consts.TRAP_H_FILE_NAME}"))
  with open(consts.TRAP_C_FILE_NAME, "w") as f:
    f.write(btl.template(f"traps/{consts.TRAP_C_FILE_NAME}",
      confObj=confObj,
    ))
  with open(consts.TRAP_ASM_FILE_NAME, "w") as f:
    f.write(btl.template(f"traps/{consts.TRAP_ASM_FILE_NAME}"))
  with open(consts.TRAP_RTOS_FILE_NAME, "w") as f:
    f.write(btl.template(f"traps/{consts.TRAP_RTOS_FILE_NAME}"))


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
    f.write(btl.template(f"api/{consts.CORTOS_HEADER_FILE_NAME}",
                         confObj=confObj,
                         consts=consts,
                         LogLevel=consts.LogLevel,
                         ))


def copyCortosUtilFiles(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.CORTOS_UTILS_H_FILE_NAME, "w") as f:
    f.write(btl.template(f"utils/{consts.CORTOS_UTILS_H_FILE_NAME}",
      confObj=confObj))

  with open(consts.CORTOS_UTILS_C_FILE_NAME, "w") as f:
    f.write(btl.template(f"utils/{consts.CORTOS_UTILS_C_FILE_NAME}",
      confObj=confObj))

  with open(consts.CORTOS_UTILS_ASM_FILE_NAME, "w") as f:
    f.write(btl.template(f"utils/{consts.CORTOS_UTILS_ASM_FILE_NAME}",
      confObj=confObj))

  with open(consts.CORTOS_PRINTF_FILE_NAME, "w") as f:
    f.write(btl.template(f"utils/{consts.CORTOS_PRINTF_FILE_NAME}",
                         confObj=confObj))

  with open(consts.CORTOS_PRINTF_CVT_FILE_NAME, "w") as f:
    f.write(btl.template(f"utils/{consts.CORTOS_PRINTF_CVT_FILE_NAME}",
                         confObj=confObj))


def copyLockFiles(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.LOCK_FILE_NAME, "w") as f:
    f.write(btl.template(f"locks/{consts.LOCK_FILE_NAME}", confObj=confObj))

  with open(consts.LOCKS_C_FILE, "w") as f:
    f.write(btl.template(f"locks/{consts.LOCKS_C_FILE}", confObj=confObj))

  with open(consts.LOCKS_HEADER_FILE, "w") as f:
    f.write(btl.template(f"locks/{consts.LOCKS_HEADER_FILE}", confObj=confObj))


def copyLinkerScriptFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.LINKER_SCRIPT_FILE_NAME, "w") as f:
    f.write(btl.template(f"linker/{consts.LINKER_SCRIPT_FILE_NAME}", confObj=confObj))


# def copyProjectFiles(
#     confObj: config.SystemConfig,
# ) -> None:
#   # copy all .c xfiles
#   util.runCommand(f"cp {confObj.software.projectFiles.rootDir}/*.c .")
#   # copy all .h xfiles
#   util.runCommand(f"cp {confObj.software.projectFiles.rootDir}/*.h .", suppressError=True)
#   # copy all .s xfiles
#   util.runCommand(f"cp {confObj.software.projectFiles.rootDir}/*.s .", suppressError=True)
#   # copy results file
#   if confObj.software.projectFiles.resultsFile:
#     util.runCommand(f"cp {confObj.software.projectFiles.rootDir}/{confObj.software.projectFiles.resultsFile} .")


def copyInitFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.INIT_FILE_NAME, "w") as f:
    f.write(btl.template(f"init/{consts.INIT_FILE_NAME}",
                         confObj=confObj))


def copyBuildshFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.BUILD_SH_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_sh/{consts.BUILD_SH_FILE_NAME}",
                           confObj=confObj))
  util.runCommand(f"chmod +x {consts.BUILD_SH_FILE_NAME}")


def copyCleanshFile(
    confObj: config.SystemConfig,
) -> None:
  with open(consts.CLEAN_SH_FILE_NAME, "w") as f:
    f.write(btl.template(f"build_sh/{consts.CLEAN_SH_FILE_NAME}",
                         confObj=confObj))
  util.runCommand(f"chmod +x {consts.CLEAN_SH_FILE_NAME}")


def copyRunCModelFile(confObj: config.SystemConfig) -> None:
  with open(consts.RUN_CMODEL_FILE_NAME, "w") as f:
    f.write(btl.template(f"run_sh/{consts.RUN_CMODEL_FILE_NAME}", confObj=confObj))
  util.runCommand(f"chmod +x {consts.RUN_CMODEL_FILE_NAME}")


def copyResultsFile(confObj: config.SystemConfig) -> None:
  # Get user defined results
  userResults = ""
  resFilePath = osp.join(confObj.software.projectFiles.rootDir, confObj.software.projectFiles.resultsFile)
  if osp.exists(resFilePath):
    userResults = f"{util.readFromFile(resFilePath).strip()}\n"

  # Add results to append
  appendResults = btl.template(f"{consts.DEFAULT_RESULTS_FILE_NAME}",
                               confObj=confObj)

  with open(consts.DEFAULT_RESULTS_FILE_NAME, "w") as f:
    f.write(userResults)
    f.write(appendResults)


def copyCortosQueueFiles(confObj: config.SystemConfig) -> None:
  with open(consts.QUEUE_H_FILE, "w") as f:
    f.write(btl.template(f"queue/{consts.QUEUE_H_FILE}", confObj=confObj))

  with open(consts.QUEUE_C_FILE, "w") as f:
    f.write(btl.template(f"queue/{consts.QUEUE_C_FILE}", confObj=confObj))


def copyCortosBgetFiles(confObj: config.SystemConfig) -> None:
  with open(consts.CORTOS_BGET_C_FILE, "w") as f:
    f.write(btl.template(f"bget/{consts.CORTOS_BGET_C_FILE}",
                         confObj=confObj,
                         bgetLockIndex=consts.BGET_RES_LOCK_INDEX))

  with open(consts.CORTOS_BGET_H_FILE, "w") as f:
    f.write(btl.template(f"bget/{consts.CORTOS_BGET_H_FILE}",
      confObj=confObj))

  with open(consts.BGET_C_FILE, "w") as f:
    f.write(btl.template(f"bget/{consts.BGET_C_FILE}", confObj=confObj))

  with open(consts.BGET_H_FILE, "w") as f:
    f.write(btl.template(f"bget/{consts.BGET_H_FILE}", confObj=confObj))

  with open(consts.BGET_C_FILE_NCRAM, "w") as f:
    f.write(btl.template(f"bget/{consts.BGET_C_FILE_NCRAM}", confObj=confObj))

  with open(consts.BGET_H_FILE_NCRAM, "w") as f:
    f.write(btl.template(f"bget/{consts.BGET_H_FILE_NCRAM}", confObj=confObj))


def copyCortosDeviceFiles(confObj: config.SystemConfig) -> None:
  with open(consts.CORTOS_DEVICE_C_FILE, "w") as f:
    f.write(btl.template(f"devices/{consts.CORTOS_DEVICE_C_FILE}",
      confObj=confObj))

  with open(consts.CORTOS_DEVICE_H_FILE, "w") as f:
    f.write(btl.template(f"devices/{consts.CORTOS_DEVICE_H_FILE}",
      confObj=confObj))


def copyCortosLoggingFiles(confObj: config.SystemConfig) -> None:
  with open(consts.CORTOS_LOGGING_C_FILE, "w") as f:
    f.write(btl.template(f"logging/{consts.CORTOS_LOGGING_C_FILE}",
      confObj=confObj))

  with open(consts.CORTOS_LOGGING_H_FILE, "w") as f:
    f.write(btl.template(f"logging/{consts.CORTOS_LOGGING_H_FILE}",
      confObj=confObj, consts=consts))

