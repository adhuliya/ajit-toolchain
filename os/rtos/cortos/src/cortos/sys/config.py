#!/usr/bin/env python3

# Author: Anshuman Dhuliya (AD) (anshumandhuliya@gmail.com)

"""
Read user configuration file.
"""
from typing import List, Optional as Opt, Any
import os
import yaml

import cortos.common.util as util
import os.path as osp

# Yaml key names
import cortos.common.consts as consts
import cortos.sys.compute as compute

YML_CORES = "Cores"
YML_THREADS = "ThreadsPerCore"
YML_PROG_THREADS = "ProgramThreads"

YML_PROG_DIR = "Dir"
YML_PROG_CORE = "Core"
YML_PROG_THREAD = "Thread"
YML_PROG_STACK_SIZE = "StackSizeInBytes"
YML_PROG_INIT_CALL_SEQ = "CortosInitCalls"
YML_PROG_LOOP_CALL_SEQ = "CortosLoopCalls"

YML_MEM_SIZE_IN_KB = "TotalMemoryInKB"
YML_STACK_MIN_ADDR = "LeastValidStackAddr"
YML_TOTAL_LOCK_VARS = "TotalLockVars"
YML_ADD_BGET = "AddBget"

YML_LOG_LEVEL = "LogLevel"


class CortosThread:
  def __init__(self,
      cid: int,
      tid: int,
  ) -> None:
    self.cid = cid
    self.tid = tid


  def isThread00(self) -> bool:
    """Returns True if this thread is 0,0"""
    return self.cid == 0 and self.tid == 0


  def genLabel(self,
      forSetup: bool = True, # forExec if False
      forStart: bool = False,
  ) -> str:
    """Generates an appropriate jump label for a thread."""

    if not forStart:
      labelPattern = consts.THREAD_SETUP_LABEL \
        if forSetup else consts.THREAD_EXEC_LABEL

      label = labelPattern.format(core=self.cid, thread=self.tid)
    else:
      label = consts.THREAD_START_LABEL.format(core=self.cid, thread=self.tid)

    return label


  def genLabelForCortosLoop(self) -> str:
    label = consts.THREAD_CORTOS_LOOP_LABEL.format(
      core=self.cid, thread=self.tid)

    return label


  def genIdHex(self) -> str:
    """Returns the hex code string representing the value
    of the register identifying the current core and thread id."""
    return consts.THREAD_ID_TEST_HEX_PATTERN.format(core=self.cid, thread=self.tid)


  def __lt__(self, other):
    if not isinstance(other, CortosThread):
      raise ValueError(f"{other}")

    return (self.cid <= other.cid
            or (self.cid == other.cid and self.tid <= other.tid))

  def __eq__(self, other):
    if not isinstance(other, CortosThread):
      raise ValueError(f"{other}")

    return self.cid == other.cid and self.tid == other.tid

  def __str__(self):
    return f"(Thread (cid={self.cid}, tid={self.tid}))"


class UserConfig:
  """Configuration specified by the user (like a yaml file)."""
  def __init__(self,
      data,
      ramStartAddr = 0x0,
  ):
    self.data = data

    self.rootDir = os.getcwd()
    self.buildDir = osp.join(self.rootDir, consts.CORTOS_BUILD_DIR_NAME)
    self.cortosSrcDir = osp.join(self.buildDir, consts.CORTOS_SRC_DIR_NAME)
    self.cFileNames: List[str] = []
    self.resultsFile: str = consts.DEFAULT_RESULTS_FILE_NAME

    self.coreCount = 1
    self.threadsPerCoreCount = 1
    self.programs: List[ProgramThread] = []
    self.memSizeInKB = consts.DEFAULT_MEM_SIZE_IN_KB
    self.totalLockVars = consts.DEFAULT_LOCK_VARS
    self.totalResLockVars = consts.DEFAULT_RES_LOCK_VARS

    self.totalQueues = consts.DEFAULT_TOTAL_QUEUES
    self.elementsPerQueue = consts.DEFAULT_QUEUE_LEN
    self.queueMsgSize = consts.DEFAULT_QUEUE_MSG_SIZE_IN_BYTES
    self.queueSizeInBytes = consts.DEFAULT_QUEUE_SIZE_IN_BYTES
    self.totalQueueHeadersSize = (self.totalQueues
                                  * consts.QUEUE_HEADER_SIZE_IN_BYTES)

    self.leastValidStackAddr = consts.LOWER_STACK_BOUNDARY_ADDR_4MB
    self.bgetMemSizeInBytes = consts.DEFAULT_BGET_MEM_SIZE_IN_BYTES
    self.totalSharedIntVars = consts.TOTAL_SHARED_INT_VARS
    self.reservedMem: Opt[DataMemoryRegions] = None

    self.addBget: bool = False
    self.logLevel: consts.LogLevel = consts.DEFAULT_LOG_LEVEL
    self.enableSerial: bool = consts.DEFAULT_ENABLE_SERIAL_DEVICE

    self.debugBuild: bool = consts.DEFAULT_DEBUG_BUILD
    self.optLevel: int = consts.DEFAULT_OPT_LEVEL  # 0, 1 or 2
    # the starting debug port sequence (one for each thread)
    self.startingDebugPort: int = consts.DEFAULT_FIRST_DEBUG_PORT

    self.ramStartAddr = ramStartAddr # start address of the ram

    self.initialize()
    print("CoRTOS: Initialized user configuration details.")
    self.verify()
    print("CoRTOS: Verified user configuration details.")


  def initialize(self):
    self.coreCount = self.data[YML_CORES]\
      if YML_CORES in self.data else 1
    self.threadsPerCoreCount = self.data[YML_THREADS]\
      if YML_THREADS in self.data else 1

    self.programs = []
    thread: Opt[CortosThread] = CortosThread(0, 0)
    for progData in self.data[YML_PROG_THREADS]:
      if thread is None:
        print(f"CoRTOS: ERROR: programs are more than available h/w threads.")
        exit(1)
      self.programs.append(ProgramThread(progData, thread))
      thread = self.getNextThread(thread)
    print("PROGRAMS_THREADS (before sort): ", [p.thread for p in self.programs])
    #print("PROGRAMS: ", len(self.programs), f"{self.programs[0].thread < self.programs[1].thread}")
    self.programs = list(sorted(self.programs, key=lambda x: (x.thread.cid, x.thread.tid)))
    print("PROGRAMS_THREADS (after sort): ", [p.thread for p in self.programs])

    self.memSizeInKB = (self.data[YML_MEM_SIZE_IN_KB]
                        if YML_MEM_SIZE_IN_KB in self.data
                        else consts.DEFAULT_MEM_SIZE_IN_KB)
    self.totalLockVars = (self.data[YML_TOTAL_LOCK_VARS]
                          if YML_TOTAL_LOCK_VARS in self.data
                          else consts.DEFAULT_LOCK_VARS)

    self.leastValidStackAddr = (self.data[YML_STACK_MIN_ADDR]
                                if YML_STACK_MIN_ADDR in self.data
                                else consts.LOWER_STACK_BOUNDARY_ADDR_4MB)

    self.reservedMem = DataMemoryRegions(self)

    self.readProjectFiles()

    self.addBget = True if YML_ADD_BGET in self.data else False

    logLevelStr: Opt[str] = self.data[YML_LOG_LEVEL] \
      if YML_LOG_LEVEL in self.data else None
    self.logLevel = consts.LogLevel[logLevelStr.upper()] \
      if logLevelStr else consts.DEFAULT_LOG_LEVEL

    # TODO: add queue related configuration.


  def readProjectFiles(self):
    files = os.listdir(self.rootDir)
    for fName in files:
      if fName.endswith(".c") and osp.isfile(fName):
        self.cFileNames.append(fName)
      elif fName.endswith(".results"):
        self.resultsFile = fName


  def verify(self) -> 'UserConfig':
    """Verify this object's values"""
    assert self.coreCount <= consts.MAX_CORES, \
      f"Ajit supports at most 4 cores. Given {self.coreCount}."
    assert self.threadsPerCoreCount <= consts.MAX_THREADS_PER_CORE, \
      f"Ajit supports at most 2 threads/core. Given {self.threadsPerCoreCount}."

    if len(self.programs) != self.totalThreads():
      print(f"CoRTOS: ERROR: H/W Threads: {self.totalThreads()},"
            f" User Programs: {len(self.programs)}. (Must be equal)")
      exit(1)

    if len(self.cFileNames) == 0:
      print(f"CoRTOS: ERROR: No C files present in the project.")
      exit(1)

    return self


  def totalThreads(self):
    return self.coreCount * self.threadsPerCoreCount


  def nextThreadExists(self,
      thread: CortosThread,
  ) -> bool:
    """Given a `Thread` object, it returns True if there is another
    thread in the sequence.

    For example in a 2x2 system,

    * for (0,0), (0,1), (1,0) it returns True
    * and for (1,1) it return False
    """
    if thread.cid == self.coreCount - 1\
        and thread.tid == self.threadsPerCoreCount - 1:
      return False
    else:
      return True


  def getNextThread(self,
      thread: CortosThread,
  ) -> Opt[CortosThread]:
    tid = (thread.tid + 1) % self.threadsPerCoreCount
    if tid != 0:
      return CortosThread(thread.cid, tid) # next thread in the same core
    else:
      cid = (thread.cid + 1) % self.coreCount
      if cid != 0:
        return CortosThread(cid, 0) # thread 0 in the next higher core
    return None


  def genNextThreadLabel(self,
      thread: CortosThread,
      forSetup: bool = True,
  ) -> str:
    """Returns the next thread label to jump to or the `consts.HALT_LABEL`."""
    nextThread = self.getNextThread(thread)
    if nextThread:
      return nextThread.genLabel(forSetup=forSetup)
    else:
      return consts.HALT_ERROR_LABEL


  def addDebugSupport(self,
      debug: bool = consts.DEFAULT_DEBUG_BUILD,
      port: int = consts.DEFAULT_FIRST_DEBUG_PORT,
  ):
    self.debugBuild = debug
    self.startingDebugPort = port


  def addOptLevel(self,
      optLevel0: bool = False,
      optLevel1: bool = False,
      optLevel2: bool = False,
  ) -> None:
    self.optLevel = 0 if optLevel0 else self.optLevel
    self.optLevel = 1 if optLevel1 else self.optLevel
    self.optLevel = 2 if optLevel2 else self.optLevel


  def __str__(self):
    return (
      f"UserConfiguration:\n"
      f"  {YML_CORES}: {self.coreCount}\n"
      f"  {YML_THREADS}: {self.threadsPerCoreCount}\n"
      f"  {YML_PROG_THREADS}: {self.programs}\n"
      f"  {YML_MEM_SIZE_IN_KB}: {self.memSizeInKB}\n"
      f"  {YML_TOTAL_LOCK_VARS}: {self.totalLockVars}\n"
    )


  def __repr__(self):
    return str(self)


class ProgramThread:
  def __init__(self,
      data: Any,
      thread: CortosThread,
  ):
    self.data = data
    self.thread = thread
    self.initCallSeq = []
    self.loopCallSeq = []

    self.stackSizeInBytes = 0
    self.stackStartAddr = 0

    self.initialize()


  def initialize(self):
    # self.thread = Thread(self.data[YML_PROG_CORE], self.data[YML_PROG_THREAD])
    self.stackSizeInBytes = self.data[YML_PROG_STACK_SIZE] \
      if YML_PROG_STACK_SIZE in self.data else consts.DEFAULT_STACK_SIZE

    self.initCallSeq = self.data[YML_PROG_INIT_CALL_SEQ] \
      if YML_PROG_INIT_CALL_SEQ in self.data else []

    self.loopCallSeq = self.data[YML_PROG_LOOP_CALL_SEQ] \
      if YML_PROG_LOOP_CALL_SEQ in self.data else []

    if not self.initCallSeq and not self.loopCallSeq:
      print("CoRTOS: ERROR: No function to call.")
      exit(1)


  def isThread00(self) -> bool:
    """Returns True if this program is running on Core 0, Thread 0."""
    return self.thread.isThread00()


  def __str__(self):
    return f"(Program (" \
           f"{YML_PROG_THREAD}: {self.thread}" \
           f", {YML_PROG_STACK_SIZE}: {self.stackSizeInBytes})" \
           f", stackStartAddr: {self.stackStartAddr})" \
           f", {YML_PROG_INIT_CALL_SEQ}: {self.initCallSeq})" \
           f", {YML_PROG_LOOP_CALL_SEQ}: {self.loopCallSeq})"


  def __repr__(self):
    return str(self)


class MemoryRegion(util.PrettyStr):
  def __init__(self,
      startAddr: util.MemoryAddrT = 0,
      sizeInBytes: util.SizeInBytesT = 0,
      name: str = "UnnamedRegion",
  ):
    self.startAddr = startAddr
    self.sizeInBytes = sizeInBytes
    self.name = name


  def getNextToLastByteAddr(self):
    return self.startAddr + self.sizeInBytes


  def getLastByteAddr(self):
    return self.getNextToLastByteAddr() - 1


class DataMemoryRegions:
  def __init__(self,
      confObj: UserConfig,
  ) -> None:
    """The initializations here are used in `init_allocate.s` file.

    Note: `init_allocate.s` is generated from `init_allocate.s.tpl` file.

    NOTE: All sizes must be a multiple of 8.
    """
    self.sizeInBytes = 0
    startAddr = util.alignAddress(
      compute.computeInitHeaderSizeInBytes() + confObj.ramStartAddr,
      8,
    )

    self.cortosReserved = MemoryRegion(
      startAddr,
      consts.RESERVED_REGION_SIZE_IN_BYTES
    )
    self.sizeInBytes += self.cortosReserved.sizeInBytes

    startAddr = self.cortosReserved.getNextToLastByteAddr()
    regionSize = confObj.totalSharedIntVars * 4
    self.cortosSharedIntVars = MemoryRegion(startAddr, regionSize)
    self.sizeInBytes += self.cortosSharedIntVars.sizeInBytes

    startAddr = self.cortosSharedIntVars.getNextToLastByteAddr()
    regionSize = confObj.totalResLockVars * 4
    self.cortosResLockVars = MemoryRegion(startAddr, regionSize)
    self.sizeInBytes += self.cortosResLockVars.sizeInBytes

    startAddr = self.cortosResLockVars.getNextToLastByteAddr()
    regionSize = confObj.totalLockVars * 4
    self.cortosLockVars = MemoryRegion(startAddr, regionSize)
    self.sizeInBytes += self.cortosLockVars.sizeInBytes

    startAddr = self.cortosLockVars.getNextToLastByteAddr()
    regionSize = confObj.totalQueues * 4
    self.cortosQueueLockVars = MemoryRegion(startAddr, regionSize)
    self.sizeInBytes += self.cortosQueueLockVars.sizeInBytes

    startAddr = self.cortosQueueLockVars.getNextToLastByteAddr()
    regionSize = confObj.totalQueueHeadersSize
    self.cortosQueueHeaders = MemoryRegion(startAddr, regionSize)
    self.sizeInBytes += self.cortosQueueHeaders.sizeInBytes

    startAddr = self.cortosQueueHeaders.getNextToLastByteAddr()
    regionSize = confObj.queueSizeInBytes * confObj.totalQueues
    self.cortosQueues = MemoryRegion(startAddr, regionSize)
    self.sizeInBytes += self.cortosQueues.sizeInBytes

    # a separate bget area
    startAddr = self.cortosQueues.getNextToLastByteAddr()
    regionSize = confObj.bgetMemSizeInBytes
    self.cortosBgetMemory = MemoryRegion(startAddr, regionSize)
    self.sizeInBytes += self.cortosBgetMemory.sizeInBytes


def readYamlConfig(
    yamlFileName: util.FileNameT,
    ramStartAddr: int,
    cmdLineLogLevel: consts.LogLevel = consts.LogLevel.NONE,
) -> UserConfig:
  """Reads the given yaml configuration file."""
  with open(yamlFileName) as f:
    conf = yaml.load(f)
    return UserConfig(conf, ramStartAddr)


