"""Bget dynamic memory allocation configuration."""
from typing import Dict, Optional as Opt

from cortos2.common import consts
from cortos2.sys.config import common


class Bget:
  def __init__(self,
      enable: int = consts.DEFAULT_BGET_ENABLE,
      sizeInBytes: int = consts.DEFAULT_BGET_MEM_SIZE_IN_KB * 1024,
  ):
    self.enable = enable
    self.sizeInBytes = sizeInBytes

    self.region: Opt[common.MemoryRegion] = None


  def setMemoryRegion(self, region: common.MemoryRegion):
    self.region = region


  def getStartAddr(self):
    return self.region.getFirstByteAddr(useVirtualAddr=True)


  def getSizeInBytes(self):
    return self.sizeInBytes


  def getEndAddr(self):
    return self.region.getLastByteAddr(useVirtualAddr=True)


def initConfig(userProvidedConfig: Dict) -> Bget:
  enableBget = (True
                if consts.YML_BGET_MEM_SIZE_IN_KB in userProvidedConfig
                else consts.DEFAULT_BGET_ENABLE)
  memSizeInKb = (userProvidedConfig[consts.YML_BGET_MEM_SIZE_IN_KB]
                 if consts.YML_BGET_MEM_SIZE_IN_KB in userProvidedConfig
                 else consts.DEFAULT_BGET_MEM_SIZE_IN_KB)
  memSizeInBytes = memSizeInKb * 1024

  bget = Bget(
    enable=enableBget,
    sizeInBytes=memSizeInBytes,
  )

  return bget