"""The locks used in the system."""
from typing import Dict, Optional as Opt, List

from cortos2.common import consts
from cortos2.sys.config import common
from cortos2.sys.config.soft.queue import QueueSeq


class Locks:
  """Contains cacheable and non-cacheable locks."""
  def __init__(self,
      totalLocks: int = consts.DEFAULT_LOCK_VARS,
  ) -> None:
    self.totalLocks = totalLocks

    # Populated during memory layout.
    self.cacheableRegion: Opt[common.MemoryRegion] = None
    self.nonCacheableRegion: Opt[common.MemoryRegion] = None

    # Populated during memory layout.
    self.locksStartAddr = 0
    self.locksStartAddrCacheable = 0


  def getSizeInBytes(self) -> int:
    return self.totalLocks * 2


  def setMemoryRegion(self,
       region: common.MemoryRegion,
  ) -> None:
    if region.cacheable:
      self.cacheableRegion = region
      self.locksStartAddrCacheable = region.getFirstByteAddr()
    else:
      self.nonCacheableRegion = region
      self.locksStartAddr = region.getFirstByteAddr()

    self.checkInvariants(cacheable=region.cacheable) # IMPORTANT


  def checkInvariants(self, cacheable=False) -> None:
    if cacheable:
      lastLockAddr = self.locksStartAddrCacheable + self.totalLocks - 1
      region = self.cacheableRegion
    else:
      lastLockAddr = self.locksStartAddr + self.totalLocks - 1
      region = self.nonCacheableRegion

    if lastLockAddr > region.getLastByteAddr(virtualAddr=True):
      print(f"ERROR: Total locks {self.getSizeInBytes()} exceeds"
            f" region size {region.sizeInBytes}.")
      exit(1)

  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'Locks':
    """Takes a user given configuration and extracts the Lock related configuration."""
    locks = Locks(
      totalLocks=consts.DEFAULT_LOCK_VARS,
    )
    return locks

