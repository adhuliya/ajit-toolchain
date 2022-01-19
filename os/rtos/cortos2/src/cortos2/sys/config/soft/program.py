"""Details related to the user programs."""
from typing import List, Dict, Optional as Opt

from cortos2.common import consts, elf, util
from cortos2.sys.config import common
from cortos2.sys.config.hard import processor
from cortos2.sys.config.hard.processor import CoreThread, Processor


class ProgramThread:
  def __init__(self,
      coreThread: processor.CoreThread,
      stackSizeInBytes: int,
      initCallSeq: List[str],
      loopCallSeq: Opt[List[str]],
  ):
    self.coreThread = coreThread
    self.initCallSeq = initCallSeq
    self.loopCallSeq = loopCallSeq

    self.stackSizeInBytes = stackSizeInBytes

    self.stackRegion: Opt[common.MemoryRegion] = None


  def isThread00(self) -> bool:
    """Returns True if this program is running on Core 0, Thread 0."""
    return self.coreThread.isThread00()


  def __str__(self):
    return f"(Program (" \
           f"{consts.YML_PROG_THREAD}: {self.coreThread}" \
           f", {consts.YML_PROG_STACK_SIZE}: {self.stackSizeInBytes})" \
           f", stackStartAddr: {self.stackRegion.getLastByteAddr(virtualAddr=True)})" \
           f", {consts.YML_PROG_INIT_CALL_SEQ}: {self.initCallSeq})" \
           f", {consts.YML_PROG_LOOP_CALL_SEQ}: {self.loopCallSeq})"


  def __repr__(self):
    return str(self)


  def setStackRegion(self, region: common.MemoryRegion):
    self.stackRegion = region


  def getStackStartAddr(self):
    """Stack starts from high to low."""
    return self.stackRegion.getNextToLastByteAddr(virtualAddr=True)


  def getStackSizeInBytes(self):
    return self.stackRegion.getSizeInBytes()


  @staticmethod
  def generateObject(
      userProvidedConfig: Opt[Dict],
      coreThread: CoreThread,
      prevKeySeq: Opt[List] = None,
  ) -> 'ProgramThread':

    stackSizeConf = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["StackSize"],
      default=None,
    )
    stackSizeInBytes = util.getSizeInBytes(
      stackSizeConf,
      default=consts.DEFAULT_STACK_SIZE,
    )

    initCallSeq = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["CortosInitCalls"],
      default=["main"]
    )

    loopCallSeq = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["CortosLoopCalls"],
      default=[],
    )

    progThread = ProgramThread(
      coreThread=coreThread,
      stackSizeInBytes=stackSizeInBytes,
      initCallSeq=initCallSeq,
      loopCallSeq=loopCallSeq,
    )
    return progThread


class Program:
  """All the programs in the system."""

  def __init__(self,
      programThreads: List[ProgramThread],
  ) -> None:
    self.programThreads = programThreads

    # these are set later after the first build of the binary.
    self.textSectionSizeInBytes = consts.DEFAULT_TEXT_SECTION_SIZE_IN_BYTES
    self.dataSectionSizeInBytes = consts.DEFAULT_DATA_SECTION_SIZE_IN_BYTES
    self.bssSectionSizeInBytes = consts.DEFAULT_BSS_SECTION_SIZE_IN_BYTES

    self.textRegion: Opt[common.MemoryRegion] = None
    self.dataRegion: Opt[common.MemoryRegion] = None
    self.bssRegion: Opt[common.MemoryRegion] = None


  def computeBinarySize(self, elfFileName: str):
    textSize, dataSize, bssSize = elf.getTextDataBssSize(elfFileName)
    self.textSectionSizeInBytes = textSize
    self.dataSectionSizeInBytes = dataSize
    # don't let the bss section size be zero
    self.bssSectionSizeInBytes = bssSize if bssSize else 4096


  def getSizeOfProgram(self):
    """The total size of the program is equal to the total bytes
    till the end of the data region."""
    return self.dataRegion.getNextToLastByteAddr(virtualAddr=True)


  def getTextRegionStartAddr(self):
    return self.textRegion.getFirstByteAddr(virtualAddr=True)


  def getDataRegionStartAddr(self):
    return self.dataRegion.getFirstByteAddr(virtualAddr=True)


  def getBssRegionStartAddr(self):
    return self.bssRegion.getFirstByteAddr(virtualAddr=True)


  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      ajitCpu: Processor,
      prevKeySeq: Opt[List] = None,
  ) -> 'Program':
    keyName = "ProgramThreads"
    prevKeySeq.append(keyName)

    config: Opt[List] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=None,
    )
    assert config, f"At least one Program Thread must be specified."

    progThreads = []
    coreThread = ajitCpu.getThreadZero()
    for programThread in config:
      programThread = ProgramThread.generateObject(
        userProvidedConfig=programThread,
        coreThread=coreThread,
        prevKeySeq=prevKeySeq
      )
      progThreads.append(programThread)
      coreThread = ajitCpu.getNextThread(coreThread)

    program = Program(progThreads)
    prevKeySeq.pop()
    return program


def initConfig(
    userProvidedConfig: Dict,
    ajitCpu: processor.Processor,
) -> Program:
  """Takes a user given configuration and extracts the relevant bits."""
  programThreads: List[ProgramThread] = []

  coreThread = ajitCpu.getThreadZero()
  for progData in userProvidedConfig[consts.YML_PROG_THREADS]:
    if coreThread is None:
      print(f"CoRTOS: ERROR: programs are more than available h/w threads.")
      exit(1)

    stackSizeInBytes = progData[consts.YML_PROG_STACK_SIZE] \
      if consts.YML_PROG_STACK_SIZE in progData else consts.DEFAULT_STACK_SIZE
    initCallSeq = progData[consts.YML_PROG_INIT_CALL_SEQ] \
      if consts.YML_PROG_INIT_CALL_SEQ in progData else []
    loopCallSeq = progData[consts.YML_PROG_LOOP_CALL_SEQ] \
      if consts.YML_PROG_LOOP_CALL_SEQ in progData else []

    programThreads.append(
      ProgramThread(
        coreThread=coreThread,
        stackSizeInBytes=stackSizeInBytes,
        initCallSeq=initCallSeq,
        loopCallSeq=loopCallSeq,
      )
    )

    coreThread = ajitCpu.getNextThread(coreThread)

  # sorting not needed currently. Kept this line for reference.
  programThreads = sorted(programThreads, key=lambda x: x.coreThread)

  program = Program(programThreads)
  return program


