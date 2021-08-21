#!/usr/bin/env python3

# Author: Anshuman Dhuliya (AD) (anshumandhuliya@gmail.com)

"""
Functionality to build the project for the Ajit processor.

All the logic to build is present here, or invoked from here.
"""
from io import StringIO
import os
import os.path as osp
from typing import List, Tuple, Optional as Opt

from cortos.common import consts, bottle as btl, elf
from cortos.common import util
import cortos.sys.config as config
import cortos.sys.copy as cpy


def buildProject(confObj: config.UserConfig) -> None:
  print("CoRTOS: build process started...")

  print(f"\nCoRTOS: START: cortos_build.")
  computeStackAddr(confObj) # FIXME: call it from some other place?
  prepareBuildDir(confObj)
  runBuildScript(confObj)
  # computeElfSize(confObj)
  # prepareFinalBuildDir(confObj)
  # runBuildScript(confObj)
  print(f"CoRTOS: END  : cortos_build.")


def prepareBuildDir(
    confObj: config.UserConfig,
) -> None:
  """Prepares a build directory for the initial build of a program."""
  # STEP 1: create the build directory
  util.createDir(confObj.buildDir)

  # STEP 2: copy necessary files
  copyBuildFiles(confObj)


def copyBuildFiles(
    confObj: config.UserConfig,
) -> None:
  # STEP 1: cd into the build directory
  cwd = os.getcwd()
  os.chdir(confObj.buildDir)

  # STEP 2: Copy files that the user is directly interested in.
  cpy.copyProjectFiles(confObj)
  cpy.copyInitFile(confObj)
  cpy.copyTrapFile(confObj)
  cpy.copyCortosHeaderFile(confObj)
  cpy.copyResultsFile(confObj)
  cpy.copyBuildshFile(confObj)
  cpy.copyRunCModelFile(confObj)

  # STEP 3: Copy files that the user might not need to look into.
  os.chdir(confObj.cortosSrcDir)

  cpy.copyPageTableFile(confObj)
  cpy.copyVmapFile(confObj)
  cpy.copyLinkerScriptFile(confObj)

  # copy cortos library support
  cpy.copyCortosAsmFile(confObj)
  cpy.copyCortosCFile(confObj)
  cpy.copyCortosPrintfFile(confObj)
  cpy.copyCortosQueueFiles(confObj)
  cpy.copyLockFiles(confObj)
  if confObj.addBget:
    cpy.copyCortosBgetFiles(confObj)

  # STEP 3: return back to the previous directory
  os.chdir(cwd)


def runBuildScript(confObj: config.UserConfig) -> None:
  """Run the `build.sh` script in the build dir."""
  # STEP 1: cd into the build directory
  cwd = os.getcwd()
  os.chdir(confObj.buildDir)
  print("CoRTOS: CWD:", os.getcwd())

  # STEP 2: execute the `build.sh` script
  util.runCommand(f"bash {consts.FINAL_BUILD_SH_FILE_NAME}")

  # STEP 3: return back to the previous directory
  os.chdir(cwd)


# def computeProgramSize(
#     confObj: config.UserConfig,
# ) -> None:
#   """Computes size of the elf file generated."""
#   # STEP 1: cd into the build directory
#   cwd = os.getcwd()
#   os.chdir(confObj.buildDir)
#
#   # STEP 2: compute and save the binary size
#   try:
#     sizeInBytes = elf.getPtLoadSectionsSize(consts.ELF_FILE_NAME)
#     print(f"CoRTOS: PROG_SIZE: {sizeInBytes} bytes.")
#   except FileNotFoundError as e:
#     sizeInBytes = consts.DEFAULT_PROG_ELF_SIZE
#     print(f"CoRTOS: ERROR: {consts.ELF_FILE_NAME} not generated.")
#
#   # STEP 3: cd back to the previous directory
#   os.chdir(cwd)


def computeStackAddr(confObj: config.UserConfig) -> None:
  """Compute the stack starting address of each program."""
  lastFreeAddr = consts.LOWER_STACK_BOUNDARY_ADDR

  for prog in confObj.programs:
    stackSize = prog.stackSizeInBytes if prog.stackSizeInBytes\
      else consts.DEFAULT_STACK_SIZE
    lastFreeAddr += stackSize
    lastFreeAddr = util.alignAddress(lastFreeAddr, align=4096)
    prog.stackStartAddr = lastFreeAddr


# def patchCortosCalls(confObj: config.UserConfig):
#   # STEP 1: cd into the cortos build directory
#   cwd = os.getcwd()
#   os.chdir(consts.CORTOS_BUILD_DIR_NAME)
#   print("CoRTOS: CWD:", os.getcwd())
#
#   # STEP 2: create an empty mmap file
#   newFileLines = []
#   count, status, capturedLines, = 1, 0, []
#   with open(consts.MMAP_FILE_NAME) as f:
#     for line in f:
#       if not line.strip():
#         continue # neglect empty lines
#       status = captureLine(line, capturedLines, status)
#       if status == 0: # not captured
#         newFileLines.append(line)
#       elif status == 1: # partially captured
#         pass
#       elif status == 2: # flush partially captured lines to file
#         newFileLines.extend(capturedLines)
#         capturedLines.clear()
#       elif status == 3: # patch fully captured lines
#         print(f"CoRTOS: PatchingCall: Original Lines: {capturedLines}")
#         patchedLines = patchLines(capturedLines, count, confObj)
#         print(f"CoRTOS: PatchingCall: Patched Lines : {patchedLines}")
#         newFileLines.extend(patchedLines)
#         capturedLines.clear()
#
#   # STEP 3: write the modified file
#   with open(consts.MMAP_FILE_NAME, "w") as f:
#     f.write("".join(newFileLines))
#
#   # STEP 4: revert cwd
#   os.chdir(cwd)
#   print("CoRTOS: CWD:", os.getcwd())
#
#
# def captureLine(
#     line: str,
#     capturedLines: List[str],
#     status: int,
# ) -> int:
#   """This modifies `capturedLines` parameter."""
#   match = consts.MMAP_LINE_REGEX_COMPILED.search(line)
#   if not match:
#     return 2 # i.e. put captured lines back
#
#   byteValue = int(f"0x{match.group('byte')}", 16)
#
#   if len(capturedLines) == 0:
#     if byteValue == 0x40:
#       capturedLines.append(line)
#       return 1 # partially captured line sequence
#   elif len(capturedLines) == 1:
#     if byteValue == 0x0:
#       capturedLines.append(line)
#       return 1 # partially captured line sequence
#   elif len(capturedLines) == 2:
#     if byteValue == 0x0:
#       capturedLines.append(line)
#       return 1 # partially captured line sequence
#   elif len(capturedLines) == 3:
#     if byteValue == 0x2:
#       capturedLines.append(line)
#       return 3 # fully captured line sequence
#
#   return 0 if len(capturedLines) == 0 else 2
#
#
# def patchLines(
#     capturedLines: List[str],
#     count: int,
#     confObj: config.UserConfig,
# ) -> List[str]:
#   patchedLines = []
#
#   prog = confObj.programs[count]
#
#   match = consts.MMAP_LINE_REGEX_COMPILED.search(capturedLines[0])
#   callInsnAddr = int(f"0x{match.group('address')}", 16)
#
#   relativeProgAddr = prog.startAddr - callInsnAddr
#   print(f"CoRTOS: PatchingCall: AbsProgAddr = {prog.startAddr},"
#         f" CallInsnAddr: {callInsnAddr}, RelProgAddr = {relativeProgAddr}.")
#
#   hexBytes = breakAddrIntoFourHexBytes(relativeProgAddr)
#   print(f"CoRTOS: PatchingCall: RelProgAddrHex: {hexBytes}")
#
#   for hexByte in hexBytes:
#     match = consts.MMAP_LINE_REGEX_COMPILED.search(capturedLines[0])
#     address: str = match.group("address")
#     patchedLines.append(f"{address}\t{hexByte}\n")
#
#   return patchedLines
#
#
# def breakAddrIntoFourHexBytes(
#     relativeProgAddr: int
# ) -> List[str]:
#   """Returns 4 hex byte strings for the call instruction."""
#   bytes = []
#   correctedAddr = relativeProgAddr >> 2  # since addr aligned to 4 byte boundary
#
#   addr = correctedAddr
#   for i in range(4):
#     bytes.append(addr & 0xFF)
#     addr = addr >> 8
#   bytes.reverse()
#
#   bytes[0] = bytes[0] | 0x40  # call instruction opcode
#   bytesHexStr = [f"{hex(b)[2:]}" for b in bytes]
#   return bytesHexStr


# def concatenateMmapFiles(confObj: config.UserConfig):
#   """concatenate the final mmap files for each program."""
#   # STEP 1: cd into the cortos build directory
#   cwd = os.getcwd()
#   os.chdir(consts.CORTOS_BUILD_DIR_NAME)
#   print("CoRTOS: CWD:", os.getcwd())
#
#   # STEP 2: create an empty mmap file
#   with open(consts.MMAP_FILE_NAME, "w") as f:
#     f.truncate(0)
#
#   # STEP 3: concatenate
#   for prog in confObj.programs:
#     progMmapFile = osp.join(prog.finalBuildDir, consts.MMAP_FILE_NAME)
#     with open(consts.MMAP_FILE_NAME, "a") as f:
#       f.write(util.readFromFile(progMmapFile))
#
#   # STEP 4: revert cwd
#   os.chdir(cwd)
#   print("CoRTOS: CWD:", os.getcwd())

