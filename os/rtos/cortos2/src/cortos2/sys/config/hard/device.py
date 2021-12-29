"""
Device configurations useful in AJIT.
"""
from typing import Dict, List, Optional as Opt

from cortos2.common import util
from cortos2.sys.config.common import MemoryRegion


class Device:
  def __init__(self,
      name: str,
      memoryRegion: MemoryRegion,
      namedRegisters: Dict[str, int],
  ):
    self.name = name
    self.memoryRegion = memoryRegion
    self.namedRegisters = namedRegisters

  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'Device':
    keyName = "Name"
    name: str = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default="Unknown",
    )

    memoryRegion = Device.generateMemoryRegionObject(
      userProvidedConfig=userProvidedConfig,
      prevKeySeq=prevKeySeq,
    )

    namedRegisters = Device.generateNamedRegisters(
      userProvidedConfig=userProvidedConfig,
      prevKeySeq=prevKeySeq,
    )

    device = Device(name, memoryRegion, namedRegisters)
    return device


  @staticmethod
  def generateMemoryRegionObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> MemoryRegion:
    keyName = "MemoryRegion"
    prevKeySeq.append(keyName)

    config: Opt[Dict] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName]
    )
    memoryRegion = MemoryRegion.generateObject(
      userProvidedConfig=config,
      prevKeySeq=prevKeySeq,
    )
    prevKeySeq.pop()

    return memoryRegion


  @staticmethod
  def generateNamedRegisters(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> Dict[str, int]:
    keyName = "NamedRegisters"
    prevKeySeq.append(keyName)

    namedRegisters: Dict = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=dict(),
    ).copy()  # shallow copy the content of the dictionary

    prevKeySeq.pop()
    return namedRegisters
