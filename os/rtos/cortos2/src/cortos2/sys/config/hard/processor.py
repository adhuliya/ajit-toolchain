from typing import List, Dict, Optional as Opt

from cortos2.common import consts, util


class CoreThread:
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
    if not isinstance(other, CoreThread):
      raise ValueError(f"{other}")

    return (self.cid <= other.cid
            or (self.cid == other.cid and self.tid <= other.tid))


  def __str__(self):
    return f"(Thread (cid={self.cid}, tid={self.tid}))"


class Core:
  """
  A core has one to two threads.
  It has a memory management unit.
  """
  def __init__(self,
      cid: int,
      threadCount: int = 1,
  ) -> None:
    self.cid = cid
    self.threadCount = threadCount

    self.threads: List[CoreThread] = []
    for tid in range(self.threadCount):
      thread = CoreThread(cid, tid)
      self.threads.append(thread)


  def yieldThreads(self):
    yield from self.threads


  def getThreadZero(self) -> CoreThread:
    """Returns the first thread in the core."""
    return self.threads[0]


  def getNextThread(self,
      thread: CoreThread,
  ) -> Opt[CoreThread]:
    """Returns the next thread with id `thread.tid+1` if it exists."""
    if thread.tid >= self.threadCount - 1:
      return None
    return self.threads[thread.tid + 1]


class Processor:
  """
  A processor has one or more Cores.
  """
  def __init__(self,
      coreCount: int = 1,
      threadsPerCoreCount: int = 1,
      isa: int = 32, # 32 or 64
  ) -> None:
    self.coreCount = coreCount
    self.threadsPerCoreCount = threadsPerCoreCount
    self.isa = isa

    self.cores: List[Core] = []
    for cid in range(self.coreCount):
      core = Core(cid, self.threadsPerCoreCount)
      self.cores.append(core)


  def totalThreads(self):
    """Returns the total threads in the system."""
    return sum(core.threadCount for core in self.cores)


  def yieldCores(self):
    yield from self.cores


  def getCoreZero(self) -> Core:
    """Returns the core zero in the CPU."""
    return self.cores[0]


  def getNextCore(self,
      core: Core,
  ) -> Opt[Core]:
    """Returns the next core with id `core.cid+1` if it exists."""
    if core.cid >= self.coreCount - 1:
      return None
    return self.cores[core.cid + 1]


  def getThreadZero(self) -> CoreThread:
    """Returns the thread (0,0)'s object."""
    return self.getCoreZero().getThreadZero()


  def getNextThread(self,
      thread: CoreThread,
  ) -> Opt[CoreThread]:
    """Returns the next thread in numeric sequence (cid, tid)."""
    core = self.cores[thread.cid]
    nextThread = core.getNextThread(thread)
    if nextThread:
      return nextThread
    else: # try the next core
      nextCore = self.getNextCore(core)
      if nextCore:
        return nextCore.getThreadZero()
    return None # No next thread available!


  def genNextThreadLabel(self,
      thread: CoreThread,
      forSetup: bool = True,
  ) -> str:
    """Returns the next thread label to jump to or the `consts.HALT_LABEL`."""
    nextThread = self.getNextThread(thread)
    if nextThread:
      return nextThread.genLabel(forSetup=forSetup)
    else:
      return consts.HALT_ERROR_LABEL

  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'Processor':
    """Takes a user given configuration and extracts the
     Processor related configuration."""

    keyName = "Processor"

    config: Opt[Dict] = util.getConfigurationParameter(
      data = userProvidedConfig,
      keySeq = [keyName],
      default = None,
    )

    coreCount: int = util.getConfigurationParameter(
      data = config,
      keySeq = ["Cores"],
      default = 1
    )

    threadsPerCoreCount: int = util.getConfigurationParameter(
      data = config,
      keySeq = ["ThreadsPerCore"],
      default = 1,
    )

    isa: int = util.getConfigurationParameter(
      data = config,
      keySeq = ["ISA"],
      default = 32,
    )

    cpu = Processor(coreCount, threadsPerCoreCount, isa)
    return cpu

