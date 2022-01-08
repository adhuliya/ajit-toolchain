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
from typing import List, Any, Optional as Opt, Tuple

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
    return None

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


def runCommandGetOutput(cmd: str) -> str:
  """Runs the given command without capturing the output."""
  print(f"CoRTOS: command: {cmd}")
  status, output = subp.getstatusoutput(cmd)
  print(f"CoRTOS: {'OK' if not status else 'ERROR'}:"
        f" command return code {status}")
  return output

