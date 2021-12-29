"""The locks used in the system."""
from typing import Dict, Optional as Opt

from cortos2.common import consts
from cortos2.sys.config import common


class Locks:
  """Contains cacheable and non-cacheable locks."""
  def __init__(self,
      userLocks: int = consts.DEFAULT_LOCK_VARS,
      resLocks: int = consts.DEFAULT_CACHED_RES_LOCK_VARS,
      queueLocks: int = consts.DEFAULT_TOTAL_QUEUES,
  ) -> None:
    self.userLocks = userLocks
    self.resLocks = resLocks
    self.queueLocks = queueLocks

    # Populated during memory layout.
    self.cacheableRegion: Opt[common.MemoryRegion] = None
    self.nonCacheableRegion: Opt[common.MemoryRegion] = None

    # Populated during memory layout.
    self.userLocksStartAddr = 0
    self.resLocksStartAddr = 0
    self.queueLocksStartAddr = 0

    # Populated during memory layout.
    self.userLocksStartAddrCacheable = 0
    self.resLocksStartAddrCacheable = 0
    self.queueLocksStartAddrCacheable = 0


  def getSizeInBytes(self) -> int:
    return self.userLocks + self.resLocks + self.queueLocks


  def setMemoryRegion(self,
       region: common.MemoryRegion,
       cacheable=False,
  ) -> None:
    if cacheable:
      self.cacheableRegion = region
      self.resLocksStartAddrCacheable = region.getFirstByteAddr()
      self.userLocksStartAddrCacheable = self.resLocksStartAddrCacheable + self.resLocks
      self.queueLocksStartAddrCacheable = self.userLocksStartAddrCacheable + self.userLocks
    else:
      self.nonCacheableRegion = region
      self.resLocksStartAddr = region.getFirstByteAddr()
      self.userLocksStartAddr = self.resLocksStartAddr + self.resLocks
      self.queueLocksStartAddr = self.userLocksStartAddr + self.userLocks

    self.checkInvariants(cacheable=cacheable) # IMPORTANT


  def checkInvariants(self, cacheable=False) -> None:
    if cacheable:
      lastLockAddr = self.queueLocksStartAddrCacheable + self.queueLocks - 1
      region = self.cacheableRegion
    else:
      lastLockAddr = self.queueLocksStartAddr + self.queueLocks - 1
      region = self.nonCacheableRegion

    if lastLockAddr > region.getLastByteAddr(useVirtualAddr=True):
      print(f"ERROR: Total locks {self.getSizeInBytes()} exceeds region size {region.sizeInBytes}.")
      exit(1)



def initConfig(userProvidedConfig: Dict) -> Locks:
  locks = Locks()
  return locks
