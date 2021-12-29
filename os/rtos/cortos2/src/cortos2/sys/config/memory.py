"""The configuration and layout of the system memory."""
import os
from typing import List, Optional as Opt, Dict, Tuple

from cortos2.common import util, consts
from cortos2.sys.config import program, queue, lock, bget, common


class Memory:
  """Holds information about the memory available"""
  def __init__(self,
      sizeInBytes: int = consts.DEFAULT_MEM_SIZE_IN_KB * 1024,
      startAddr: int = consts.DEFAULT_MEM_START_ADDR,
  ) -> None:
    self.sizeInBytes = sizeInBytes
    self.startAddr = startAddr


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
    self.scratchPad: Opt[common.MemoryRegion] = None

    # area to be initilized to zero
    self.initToZeroStartAddr = 0
    self.initToZeroNextToEndAddr = 0

    # memory layout is basically a sequence of regions
    self.regionSeq: List[common.MemoryRegion] = []


  def initLayout(self,
      prog: program.Program,
      queueSeq: queue.QueueSeq,
      locks: lock.Locks,
      bget: bget.Bget,
  ) -> None:
    vAddr = 0x0
    pAddr = self.memory.startAddr

    region = common.MemoryRegion(
      name="TextSection",
      oneLineDescription="All the .text sections of the code",
      sizeInBytes=prog.textSectionSizeInBytes,
      virtualAddr=vAddr,
      physicalAddr=pAddr,
      permissions=consts.PagePermissions.S_RX_U_RX.value,
    )
    self.regionSeq.append(region)
    prog.textRegion = region

    region = common.MemoryRegion(
      name="DataSection",
      oneLineDescription="All the .data/.bss sections of the code.",
      sizeInBytes=prog.dataSectionSizeInBytes,
      virtualAddr=region.getNextToLastByteAddr(useVirtualAddr=True),
      physicalAddr=region.getNextToLastByteAddr(useVirtualAddr=False),
      permissions=consts.PagePermissions.S_RWX_U_RWX.value,
    )
    self.regionSeq.append(region)
    prog.dataRegion = region

    region = common.MemoryRegion(
      name="ReservedSpace",
      oneLineDescription="Some reserved space.",
      sizeInBytes=consts.RESERVED_REGION_SIZE_IN_BYTES,
      virtualAddr=region.getNextToLastByteAddr(useVirtualAddr=True),
      physicalAddr=region.getNextToLastByteAddr(useVirtualAddr=False),
      permissions=consts.PagePermissions.S_RWX_U_RWX.value,
    )
    self.regionSeq.append(region)
    self.reserved = region
    self.initToZeroStartAddr = region.getFirstByteAddr()

    region = common.MemoryRegion(
      name="ScratchPadRegion",
      oneLineDescription="A small shared data area that any thread can access.",
      sizeInBytes=consts.SCRATCHPAD_MEMORY_REGION_SIZE_IN_BYTES,
      virtualAddr=region.getNextToLastByteAddr(useVirtualAddr=True),
      physicalAddr=region.getNextToLastByteAddr(useVirtualAddr=False),
      permissions=consts.PagePermissions.S_RWX_U_RWX.value,
    )
    self.regionSeq.append(region)
    self.scratchPad = region

    region = common.MemoryRegion(
      name="CacheableLocks",
      oneLineDescription="An exclusive area to store cacheable locks.",
      sizeInBytes=consts.CACHED_LOCKS_REGION_SIZE_IN_BYTES,
      virtualAddr=region.getNextToLastByteAddr(useVirtualAddr=True),
      physicalAddr=region.getNextToLastByteAddr(useVirtualAddr=False),
      permissions=consts.PagePermissions.S_RWX_U_RWX.value,
    )
    self.regionSeq.append(region)
    locks.setMemoryRegion(region, cacheable=True)

    region = common.MemoryRegion(
      name="NonCacheableLocks",
      oneLineDescription="An exclusive area to store non-cacheable locks.",
      sizeInBytes=consts.NON_CACHED_LOCKS_REGION_SIZE_IN_BYTES,
      virtualAddr=region.getNextToLastByteAddr(useVirtualAddr=True),
      physicalAddr=region.getNextToLastByteAddr(useVirtualAddr=False),
      cacheable=False,
      permissions=consts.PagePermissions.S_RWX_U_RWX.value,
    )
    self.regionSeq.append(region)
    locks.setMemoryRegion(region, cacheable=False)

    region = common.MemoryRegion(
      name="MessageQueues",
      oneLineDescription="All queues reside here.",
      sizeInBytes=consts.DEFAULT_QUEUE_REGION_SIZE_IN_BYTES,
      virtualAddr=region.getNextToLastByteAddr(useVirtualAddr=True),
      physicalAddr=region.getNextToLastByteAddr(useVirtualAddr=False),
      permissions=consts.PagePermissions.S_RWX_U_RWX.value,
    )
    self.regionSeq.append(region)
    queueSeq.setMemoryRegion(region)
    self.initToZeroNextToEndAddr = region.getNextToLastByteAddr(useVirtualAddr=True)

    region = common.MemoryRegion(
      name="MemoryAllocArea",
      oneLineDescription="Dynamic memory is allocated from here.",
      sizeInBytes=bget.sizeInBytes,
      virtualAddr=region.getNextToLastByteAddr(useVirtualAddr=True),
      physicalAddr=region.getNextToLastByteAddr(useVirtualAddr=False),
      permissions=consts.PagePermissions.S_RWX_U_RWX.value,
    )
    self.regionSeq.append(region)
    bget.setMemoryRegion(region)

    # create space for program stacks
    region = common.MemoryRegion(
      name="StackGuard",
      oneLineDescription="A guard page to check against stack underflow/overflow.",
      sizeInBytes=2 ** 12,  # 4KB
      virtualAddr=region.getNextToLastByteAddr(useVirtualAddr=True),
      physicalAddr=region.getNextToLastByteAddr(useVirtualAddr=False),
      permissions=consts.PagePermissions.S_X_U_X.value,
    )
    self.regionSeq.append(region)

    for i, progThread in enumerate(prog.programThreads):
      region = common.MemoryRegion(
        name=f"ProgramStack_{i}",
        oneLineDescription="Program Stack Area.",
        sizeInBytes=progThread.stackSizeInBytes,
        virtualAddr=region.getNextToLastByteAddr(useVirtualAddr=True),
        physicalAddr=region.getNextToLastByteAddr(useVirtualAddr=False),
        permissions=consts.PagePermissions.S_RWX_U_RWX.value,
      )
      self.regionSeq.append(region)
      progThread.setStackRegion(region)

      region = common.MemoryRegion(
        name=f"StackGuard_{i}",
        oneLineDescription="A guard page to check against stack underflow/overflow.",
        sizeInBytes=2 ** 12,  # 4KB
        virtualAddr=region.getNextToLastByteAddr(useVirtualAddr=True),
        physicalAddr=region.getNextToLastByteAddr(useVirtualAddr=False),
        permissions=consts.PagePermissions.S_X_U_X.value,
      )
      self.regionSeq.append(region)

    region = common.MemoryRegion(
      name="MemoryMappedIO",
      oneLineDescription="Reserved space for memory mapped IO.",
      sizeInBytes=2 ** 16,  # 64KB
      virtualAddr=0xFFFF0000,
      physicalAddr=0xFFFF0000,
      cacheable=False,
      permissions=consts.PagePermissions.S_RWX_U_RWX.value,
    )
    self.regionSeq.append(region)


def initConfig(
    userProvidedConfig: Dict,
    prog: program.Program,
    queueSeq: queue.QueueSeq,
    locks: lock.Locks,
    bgetObj: bget.Bget,
) -> MemoryLayout:
  """Takes a user given configuration and extracts the relevant bits. """

  memSizeInKB = (userProvidedConfig[consts.YML_MEM_SIZE_IN_KB]
                 if consts.YML_MEM_SIZE_IN_KB in userProvidedConfig
                 else consts.DEFAULT_MEM_SIZE_IN_KB)
  memSizeInBytes = memSizeInKB * 1024

  memStartAddr = (userProvidedConfig[consts.YML_MEM_START_ADDR]
                 if consts.YML_MEM_START_ADDR in userProvidedConfig
                 else consts.DEFAULT_MEM_START_ADDR)

  memory = Memory(
    sizeInBytes=memSizeInBytes,
    startAddr=memStartAddr
  )

  memoryLayout = MemoryLayout(memory)
  memoryLayout.initLayout(
    prog=prog,
    locks=locks,
    queueSeq=queueSeq,
    bget=bgetObj,
  )
  return memoryLayout

