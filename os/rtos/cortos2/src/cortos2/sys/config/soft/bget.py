"""Bget dynamic memory allocation configuration."""
from typing import Dict, Optional as Opt, List

from cortos2.common import consts, util
from cortos2.sys.config import common


class Bget:
  def __init__(self,
      sizeInBytes: int = consts.DEFAULT_BGET_MEM_SIZE_IN_KB * 1024,
  ):
    self.sizeInBytes = 4 * 1024 if not sizeInBytes else sizeInBytes

    self.region: Opt[common.MemoryRegion] = None

    self.enable = (self.sizeInBytes > 0)


  def setMemoryRegion(self, region: common.MemoryRegion):
    self.region = region


  def getStartAddr(self):
    return self.region.getFirstByteAddr(virtualAddr=True)


  def getSizeInBytes(self):
    return self.sizeInBytes


  def getEndAddr(self):
    return self.region.getLastByteAddr(virtualAddr=True)


  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'Bget':
    keyName = "DynamicMemory"
    prevKeySeq.append(keyName)

    config: Opt[Dict] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=None,
      prevKeySeq=prevKeySeq[:-1],
    )

    if config:
      sizeInBytes = util.getSizeInBytes(
        config,
        default=consts.DEFAULT_BGET_MEM_SIZE_IN_KB * 1024,
        prevKeySeq=prevKeySeq,
      )
    else:
      sizeInBytes = 0

    bget = Bget(
      sizeInBytes=sizeInBytes,
    )
    prevKeySeq.pop()
    return bget


