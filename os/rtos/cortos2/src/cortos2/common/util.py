#!/usr/bin/env python3

# Author: Anshuman Dhuliya (AD) (anshumandhuliya@gmail.com)

"""
Utility module with project wide components.
"""
import io
import logging

_log = logging.getLogger(__name__)

import os
import os.path as osp
import subprocess as subp
from typing import List, Any, Optional as Opt, Tuple, Dict

globalCounter: int = 0
RelFilePathT = str  # a relative file path (could be absolute too)
AbsFilePathT = str  # an absolute file path
TEXT_CHARS = bytearray({7,8,9,10,12,13,27} | set(range(0x20, 0x100)) - {0x7f})

FileNameT = str
"""A file name or a file path."""
DirNameT = str
"""A directory name or a directory path."""
SizeInBytesT = int
"""Size of objects in bytes. """
MemoryAddrT = int
"""Memory Address"""



def genLabel(label: str):
  """Generates a label line for assembly file."""
  return f"{label}:{os.linesep}"


################################################
# BLOCK START: FileSystem_Related
################################################

def createDir(dirPath, existOk=True) -> str:
  """Creates dir. Relative paths use current directory.

  Args:
    dirPath: an absolute or relative path
    existOk: If True, don't throw error if dir already present.

  Returns:
    str: absolute path of the directory or None.
  """
  absPath = getAbolutePath(dirPath)
  _log.debug("Creating directory %s", absPath)

  try:
    os.makedirs(absPath, exist_ok=existOk)
  except Exception as e:
    _log.error("Error creating directory {},\n{}".format(absPath, e))
    exit(1)

  return absPath


def getAbolutePath(filePath: str):
  """Returns absolute path of the given file."""
  if osp.isabs(filePath):
    absPath = filePath
  else:
    cwd = os.getcwd()
    absPath = osp.join(cwd, filePath)
  return absPath


def readFromFile(fileName: str) -> str:
  """Returns the complete content of the given file."""
  with open(fileName) as f:
    return f.read()


def readResFile(resFilePath: str) -> str:
  """Returns the complete content of the given resource file."""
  absPath = getAbsolutePathFromScriptRelativeFilePath(resFilePath)
  return readFromFile(absPath)


def writeToFile(fileName: str, content: str):
  """Writes content to the given file."""
  with open(fileName, "w") as f:
    f.write(content)
  return None


def appendToFile(fileName: str, content: str):
  """Writes content to the given file."""
  with open(fileName, "a") as f:
    f.write(content)
  return None


def getAllFilePaths(directory: str) -> List[str]:
  """Returns the full file names of all the xfiles
  (recursively) withing the given directory."""
  for root, dirs, files in os.walk(directory):
    for d in dirs:
      path = osp.join(root, d)
      yield path
    for f in files:
      path = osp.join(root, f)
      yield path


def isEmptyDir(directory: str) -> bool:
  lst = os.listdir(directory)
  return len(lst) == 0


def isBinaryFile(filePath: RelFilePathT) -> bool:
  isBinaryString = lambda bytes: bool(bytes.translate(None, TEXT_CHARS))
  return isBinaryString(open(filePath, "rb").read(1024))


def getAbsolutePathFromScriptRelativeFilePath(relFileName: str) -> str:
  """Takes a relative file name (w.r.t. this script's location) and
  returns an absolute path.
  """
  if osp.isabs(relFileName):
    raise ValueError(f"ERROR: relative file name expected: {relFileName}")
  thisScriptPath = osp.realpath(__file__)
  thisScriptDir = osp.dirname(thisScriptPath)
  absFilePath = osp.join(thisScriptDir, relFileName)
  return absFilePath


def copyDirectoryContents(srcDir: RelFilePathT, destDir: RelFilePathT) -> None:
  """Copies the contents of the source directory
  into the destination directory.
  It assumes that the source and destination directories exist.
  """
  filePathList = os.listdir(srcDir)
  for filePath in filePathList:
    absFilePath = osp.join(srcDir, filePath)
    subp.run(f"cp -r {absFilePath} {destDir}", shell=True)


def copyFile(filePath: RelFilePathT, destDir: RelFilePathT) -> None:
  subp.run(f"cp -r {filePath} {destDir}", shell=True)


def prepareDestinationDirectory(
    srcDirPath: RelFilePathT,
    destDirPath: RelFilePathT,
) -> None:
  """
  It tries to copy the contents of source directory to the
  destination directory without overwriting.
  Assumption: source directory exists.
  """
  # STEP 0: get absolute paths (optional)
  absDestDirPath: AbsFilePathT \
    = getAbolutePath(destDirPath)
  absSrcDirPath: AbsFilePathT \
    = getAbolutePath(srcDirPath)

  # STEP 1: create the destination dir if doesn't exist
  createDir(absDestDirPath)

  # STEP 2: Systematically copy the contents of source dir to destination dir
  if isEmptyDir(absDestDirPath):
    # STEP 3.1: If destination dir is empty copy the whole source dir
    copyDirectoryContents(absSrcDirPath, absDestDirPath)
  else:
    # STEP 3.2:
    # Selectively copy xfiles if they don't exist in the destination dir
    prefixLen = len(absSrcDirPath) + 1
    for absSrcFilePath in getAllFilePaths(absSrcDirPath):
      relFilePath = absSrcFilePath[prefixLen:] # remove prefix
      relDirPath = osp.dirname(relFilePath)
      absFilePath = osp.join(absDestDirPath, relFilePath)
      absDirPath = osp.join(absDestDirPath, relDirPath)

      if not osp.exists(absDirPath):
        createDir(absDestDirPath)

      if not osp.exists(absFilePath):
        copyFile(absSrcFilePath, absDirPath)


def getFileModTimeInNanoSecs(filePath: str) -> int:
  stat = os.stat(filePath, follow_symlinks=True)
  return stat.st_mtime_ns


def commandExists(progName: str) -> bool:
  """Returns True if the given command exists."""
  cmd = f"which {progName}"
  completed = subp.run(cmd, shell=True)
  if completed.returncode != 0:
    return False
  return True

################################################
# BLOCK END  : FileSystem_Related
################################################


def adjustSizeToAlign(
    sizeInBytes: int,
    align: int = 8,
) -> int:
  rem = sizeInBytes % align
  if rem == 0:
    return sizeInBytes
  else:
    return sizeInBytes + (align - rem)


def convertKbToBytes(
    sizeInKb: int,
) -> int:
  return sizeInKb * 1024


_PRETTY_INDENT=2
def prettyPrint(
    obj: Any,
    indent: int = _PRETTY_INDENT, # multiples of 2
) -> str:
  """
  A recursive function to pretty print a python object.
  :param obj: a python object
  :param indent: space indentation quantity needed
  :return: a pretty string representation of the object
  """
  sio = io.StringIO()
  indent1 = " " * (indent-_PRETTY_INDENT)
  indent2 = " " * indent
  if isinstance(obj, dict):
    sio.write(f"{indent1}{{{os.linesep}")
    for key, val in obj.items():
      sio.write(f"{indent2}'{key}':"
                f" {prettyPrint(val, indent+_PRETTY_INDENT)},{os.linesep}")
    sio.write(f"{indent1}}}{os.linesep}")
  elif isinstance(obj, (str, int, float, list, set, tuple)):
    sio.write(f"{indent2}{obj}")
  else:
    # if here, could be a custom user objet
    sio.write(f"{indent2}{prettyPrint(obj.__dict__)}")

  return sio.getvalue()


class PrettyStr:
  """Pretty string of an object."""

  def __str__(self):
    return f"{self.__class__.__name__}({prettyPrint(self)})"


  def __repr__(self):
    return str(self)


def alignAddress(addr: int, align: int = 4096) -> int:
  """Pad `addr` to comply with some alignment"""
  rem = addr % align
  if rem == 0:
    return addr
  else:
    padding = align - rem
    return addr + padding


def runCommand(
    cmd: str,
    shell: bool = True,
    suppressError: bool = False,
) -> int:
  """Runs the given command without capturing the output."""
  print(f"CoRTOS: command: {cmd}")
  completed = subp.run(cmd, shell=shell)
  if not suppressError:
    print(f"CoRTOS: {'OK' if not completed.returncode else 'ERROR'}:"
          f" command return code {completed.returncode}")
  return completed.returncode


def runCommandGetOutput(cmd: str) -> Tuple[int, str]:
  """Runs the given command without capturing the output."""
  print(f"CoRTOS: command: {cmd}")
  status, output = subp.getstatusoutput(cmd)
  print(f"CoRTOS: {'OK' if not status else 'ERROR'}:"
        f" command return code {status}")
  return status, output

def getSizeStr(sizeInBytes : int) -> str:
  """e.g. converts 4100 bytes to 4KB + 4B, etc. Only GB, MB, KB supported."""
  sizeStr = ""

  multiple = sizeInBytes // (2**30) # for megabytes
  add = " + " if sizeStr else ""
  if multiple: sizeStr = f"{sizeStr}{add}{multiple}GB"
  sizeInBytes -= multiple * (2**30)

  multiple = sizeInBytes // (2**20) # for megabytes
  add = " + " if sizeStr else ""
  if multiple: sizeStr = f"{sizeStr}{add}{multiple}MB"
  sizeInBytes -= multiple * (2**20)

  multiple = sizeInBytes // (2**10) # for kilobyte
  add = " + " if sizeStr else ""
  if multiple: sizeStr = f"{sizeStr}{add}{multiple}KB"
  sizeInBytes -= multiple * (2**10)

  add = " + " if sizeStr else ""
  if sizeInBytes: sizeStr = f"{sizeStr}{add}{sizeInBytes}B"

  return sizeStr



def getConfigurationParameter(
    data: Dict,
    keySeq: Opt[List],
    default = None,
    prevKeySeq: Opt[List] = None,
    printInfo: bool = True,
    fail: bool = False,
):
  """Reads a sequence of keys from the dictionary if present, else returns default.

  e.g. if keySeq = ['A','B',3,'C'], then the return is data['A']['B'][3]['C'],
  if present else default is returned.
  """
  keySeqFound = True

  if (
    not data
    or not isinstance(data, dict)
    or not keySeq
  ):
    keySeqFound = False
  else:
    for key in keySeq:
      if isinstance(key, int): # assumes list access
        data = data[key]
      elif key in data:
        data = data[key]
      else:
        keySeqFound = False
        break

  if not keySeqFound and printInfo:
    fullKeySeq = list(prevKeySeq) if prevKeySeq else []
    fullKeySeq.extend(keySeq)
    printKeySeqMessage(fullKeySeq, default)
    if fail:
      exitWithError(f"required: {createKeySeqStr(fullKeySeq)}")

  return data if keySeqFound else default


def getSizeInBytes(
    data: Opt[Dict],
    startAddr: Opt[int] = None,
    default: int = 8192, # 8 KB
    prevKeySeq: Opt[List] = None,
    fail: bool = False,
) -> Opt[int]:
  if not data:
    return default

  sizeInBytes = None

  # read the size in order of preference.
  if startAddr:
    endAddr = getConfigurationParameter(data, ["EndAddr"],
      default=None, prevKeySeq=prevKeySeq, printInfo=False)
    if isinstance(endAddr, int):
      sizeInBytes = endAddr - startAddr + 1

  if sizeInBytes is None:
    sizeInBytes = getConfigurationParameter(data, ["SizeInBytes"],
      default=None, prevKeySeq=prevKeySeq, printInfo=False)

  if sizeInBytes is None:
    sizeInKiloBytes = getConfigurationParameter(data, ["SizeInKiloBytes"],
      default=None, prevKeySeq=prevKeySeq, printInfo=False)
    sizeInBytes = None if sizeInKiloBytes is None else sizeInKiloBytes * 1024

  if sizeInBytes is None:
    sizeInMegaBytes = getConfigurationParameter(data, ["SizeInMegaBytes"],
      default=None, prevKeySeq=prevKeySeq, printInfo=False)
    sizeInBytes = None if sizeInMegaBytes is None else sizeInMegaBytes * 1024 * 1024

  if sizeInBytes is None:
    printKeySeqMessage(prevKeySeq, default=default,
      message="Size not specified.")
    if fail:
      exitWithError(f"required: size of {createKeySeqStr(prevKeySeq)}")

  return sizeInBytes


def configInfo(
    keySeq: List[str],
    message: str,
) -> None:
  keySeqStr = ".".join(keySeq)
  print(f"Config key: {keySeqStr}\n  {message}")

def configError(
    keySeq: List[str],
    message: str,
) -> None:
  configInfo(keySeq, f"error: {message}")

def createKeySeqStr(keySeq: List):
  """Puts integers in the sequence into square brackets '[]'
  and returns a single dot separated string which can be used for printing."""
  newKeySeq = []
  for key in keySeq:
    newKeySeq.append(f"[{key}]" if isinstance(key, int) else key)
  return '.'.join(newKeySeq)


def printKeySeqMessage(
    keySeq: List,
    default: Any = None,
    message: str = "",
):
  print(f"CoRTOS: Config not found: '{createKeySeqStr(keySeq)}'"
        f" Default value {default}. {message}")


def exitWithError(message: str, status: int = 1):
  printError(message)
  exit(status)

def printError(message: str):
  print(f"CoRTOS: ERROR: {message}")
