from typing import List, Optional as Opt

from cortos2.common import consts
from cortos2.common.consts import MemoryPermissions
from cortos2.sys.config import common
from cortos2.sys.config.hard.memory import Memory
from cortos2.sys.config.soft.bget import Bget
from cortos2.sys.config.soft.lock import Locks
from cortos2.sys.config.soft.program import Program
from cortos2.sys.config.soft.queue import QueueSeq
from cortos2.common import util


class MemoryLayout:
  """Defines the memory layout over the given memory."""
  def __init__(self,
      memory: Memory,
  ) -> None:
    """The initializations here are used in `init_allocate.s` file.

    Note: `init_allocate.s` is generated from `init_allocate.s.tpl` file.

    NOTE: All sizes must be a multiple of 8.
    """
    self.memory = memory

    # Total allocated space
    self.allocatedSizeInBytes = 0
    # Total padded bytes in the allocated space
    self.totalPaddedBytes = 0

    # special regions created
    self.reserved: Opt[common.MemoryRegion] = None

    # area to be initilized to zero
    self.initToZeroStartAddr = 0
    self.initToZeroNextToEndAddr = 0

    # memory layout is basically a sequence of regions
    self.regionSeq: List[common.MemoryRegion] = []

    # memory regions that have to be initialized to zero
    self.zeroRegionSeq: List[common.MemoryRegion] = []


  def checkAndAppendMemoryRegion(self, region: common.MemoryRegion, check: bool = True):
    if check and region.getLastByteAddr(False) > self.memory.ram.getLastByteAddr(False):
      for reg in self.regionSeq:
        print(f"Allocated Region: {reg.name}, SizeInBytes: {reg.sizeInBytes}")
      util.exitWithError(f"Memory overflow at region {region.name} sizeInBytes {region.getSizeInBytes()}.", status=1)
    else:
      self.regionSeq.append(region)


  def initLayout(self,
      prog: Program,
      # queueSeq: QueueSeq,
      locks: Locks,
      bgetObj: Bget,
      dummyLayout: bool = False, # first layout may be dummy
  ) -> None:
    """Creates a fresh memory layout, based on the given input."""
    self.regionSeq = []
    self.zeroRegionSeq = []

    vAddr = self.memory.ram.virtualStartAddr
    pAddr = self.memory.ram.physicalStartAddr

    region = common.MemoryRegion(
      name="TextSection",
      oneLineDescription="All the .text sections of the code",
      sizeInBytes=prog.textSectionSizeInBytes,
      virtualStartAddr=vAddr,
      physicalStartAddr=pAddr,
      permissions=MemoryPermissions.S_RX_U_RX,
    )
    self.checkAndAppendMemoryRegion(region, not dummyLayout)
    prog.textRegion = region

    region = common.MemoryRegion(
      name="DataSection",
      oneLineDescription="All the .data sections of the code.",
      sizeInBytes=prog.dataSectionSizeInBytes,
      virtualStartAddr=region.getNextToLastByteAddr(virtualAddr=True),
      physicalStartAddr=region.getNextToLastByteAddr(virtualAddr=False),
      permissions=MemoryPermissions.S_RWX_U_RWX,
    )
    self.checkAndAppendMemoryRegion(region, not dummyLayout)
    prog.dataRegion = region

    region = common.MemoryRegion(
      name="BssSection",
      oneLineDescription=".bss section of the code.",
      sizeInBytes=prog.bssSectionSizeInBytes,
      virtualStartAddr=region.getNextToLastByteAddr(virtualAddr=True),
      physicalStartAddr=region.getNextToLastByteAddr(virtualAddr=False),
      permissions=MemoryPermissions.S_RWX_U_RWX,
    )
    self.checkAndAppendMemoryRegion(region, not dummyLayout)
    self.zeroRegionSeq.append(region)
    prog.bssRegion = region

    region = common.MemoryRegion(
      name="CacheableLocks",
      oneLineDescription="An exclusive area to store cacheable locks.",
      sizeInBytes=locks.totalLocks,
      virtualStartAddr=region.getNextToLastByteAddr(virtualAddr=True),
      physicalStartAddr=region.getNextToLastByteAddr(virtualAddr=False),
      permissions=consts.MemoryPermissions.S_RWX_U_RWX,
      cacheable=True,
      initToZero=True,
    )
    self.checkAndAppendMemoryRegion(region, not dummyLayout)
    self.zeroRegionSeq.append(region)
    locks.setMemoryRegion(region)

    region = common.MemoryRegion(
      name="NonCacheableLocks",
      oneLineDescription="An exclusive area to store non-cacheable locks.",
      sizeInBytes=locks.totalLocks,
      virtualStartAddr=region.getNextToLastByteAddr(virtualAddr=True),
      physicalStartAddr=region.getNextToLastByteAddr(virtualAddr=False),
      cacheable=False,
      permissions=consts.MemoryPermissions.S_RWX_U_RWX,
      initToZero=True,
    )
    self.checkAndAppendMemoryRegion(region, not dummyLayout)
    self.zeroRegionSeq.append(region)
    locks.setMemoryRegion(region)

    if bgetObj.enable:
      region = common.MemoryRegion(
        name="MemoryAllocArea",
        oneLineDescription="Dynamic memory is allocated from here.",
        sizeInBytes=bgetObj.sizeInBytes,
        virtualStartAddr=region.getNextToLastByteAddr(virtualAddr=True),
        physicalStartAddr=region.getNextToLastByteAddr(virtualAddr=False),
        permissions=consts.MemoryPermissions.S_RWX_U_RWX,
      )
      self.checkAndAppendMemoryRegion(region, not dummyLayout)
      bgetObj.setMemoryRegion(region)

    # create space for program stacks
    region = common.MemoryRegion(
      name="StackGuard",
      oneLineDescription="A guard page to check against stack underflow/overflow.",
      sizeInBytes=2 ** 12,  # 4KB
      virtualStartAddr=region.getNextToLastByteAddr(virtualAddr=True),
      physicalStartAddr=region.getNextToLastByteAddr(virtualAddr=False),
      permissions=consts.MemoryPermissions.S_X_U_X,
    )
    self.checkAndAppendMemoryRegion(region, not dummyLayout)

    for i, progThread in enumerate(prog.programThreads):
      region = common.MemoryRegion(
        name=f"ProgramStack_{i}",
        oneLineDescription="Program Stack Area.",
        sizeInBytes=progThread.stackSizeInBytes,
        virtualStartAddr=region.getNextToLastByteAddr(virtualAddr=True),
        physicalStartAddr=region.getNextToLastByteAddr(virtualAddr=False),
        permissions=consts.MemoryPermissions.S_RWX_U_RWX,
      )
      self.checkAndAppendMemoryRegion(region, not dummyLayout)
      progThread.setStackRegion(region)

      region = common.MemoryRegion(
        name=f"StackGuard_{i}",
        oneLineDescription="A guard page to check against stack underflow/overflow.",
        sizeInBytes=2 ** 12,  # 4KB
        virtualStartAddr=region.getNextToLastByteAddr(virtualAddr=True),
        physicalStartAddr=region.getNextToLastByteAddr(virtualAddr=False),
        permissions=consts.MemoryPermissions.S_X_U_X,
      )
      self.checkAndAppendMemoryRegion(region, not dummyLayout)

    for ncrm in self.memory.ncram:
      if ncrm.getSizeInBytes():
        self.checkAndAppendMemoryRegion(ncrm, check=False)

    for mmio in self.memory.mmio:
      if mmio.getSizeInBytes():
        self.checkAndAppendMemoryRegion(mmio, check=False)

