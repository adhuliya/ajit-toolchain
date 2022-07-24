"""The configuration and layout of the system memory."""
from typing import List, Optional as Opt, Dict
import os

from cortos2.common import util, consts
from cortos2.sys.config import common
from cortos2.sys.config.soft import bget, lock, queue, program
from cortos2.sys.config.common import MemoryRegion


class Memory:
  """Holds information about the memory available"""
  def __init__(self,
      flash: MemoryRegion,
      ram: MemoryRegion,
      ncram: List[MemoryRegion],
      mmio: List[MemoryRegion], # memory mapped io
      maxPhysicalAddrBitWidth: int = 36,
   ) -> None:
    self.flash = flash
    self.ram = ram
    self.ncram = ncram
    self.mmio = mmio
    self.maxPhysicalAddrBitWidth = maxPhysicalAddrBitWidth

  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'Memory':
    """Extracts the Memory related info from the given configuration."""

    keyName = "Memory"
    prevKeySeq.append(keyName)

    config: Opt[Dict] = util.getConfigurationParameter(
      data = userProvidedConfig,
      keySeq = [keyName],
    )

    physicalAddrWidth = util.getConfigurationParameter(
      data = config,
      keySeq=["MaxPhysicalAddrBitWidth"],
      prevKeySeq=prevKeySeq,
      default=36,
    )

    flash = Memory.generateFlashRegion(config, prevKeySeq)
    ram = Memory.generateRamRegion(config, prevKeySeq)
    ncram = Memory.generateNcRamRegions(config, prevKeySeq)
    mmio = Memory.generateMmioRegions(config, prevKeySeq)

    regionSeq: List[MemoryRegion] = []
    regionSeq.append(flash)
    regionSeq.append(ram)
    regionSeq.extend(ncram)
    regionSeq.extend(mmio)
    Memory.checkMemoryLayout(regionSeq)

    prevKeySeq.pop()
    memory = Memory(flash, ram, ncram, mmio, physicalAddrWidth)
    return memory


  @staticmethod
  def checkMemoryLayout(regionSeq: List[MemoryRegion]):
    regionSeq.sort(key=lambda x: x.physicalStartAddr)

    overlap = False
    prev = None
    for region in regionSeq:
      if prev is None:
        prev = region
        continue
      if prev.sizeInBytes == 0 or region.sizeInBytes == 0:
        continue
      if prev.getLastByteAddr(False) >= region.getFirstByteAddr(False):
        util.printError(
        f"Region '{prev.name}' overlaps region '{region.name}'{os.linesep}"
        f"        {prev.name}: address range {prev.getRangeStr(False)}{os.linesep}"
        f"        {region.name}: address range {region.getRangeStr(False)}")
        overlap = True
      prev = region

    if overlap:
      util.exitWithError(f"Overlaps in hardware memory regions. See the prints above.")


  @staticmethod
  def generateFlashRegion(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> MemoryRegion:
    keyName = "Flash"
    prevKeySeq.append(keyName)

    flashConfig: Opt[Dict] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      prevKeySeq=prevKeySeq[:-1],
    )

    if flashConfig:
      flash = MemoryRegion.generateObject(flashConfig, prevKeySeq)
    else:
      flash = MemoryRegion(
        name="Flash",
        oneLineDescription="Flash Memory",
        sizeInBytes=0,
      )

    prevKeySeq.pop()
    return flash


  @staticmethod
  def generateNcRamRegions(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> List[MemoryRegion]:
    keyName = "NCRAM"
    prevKeySeq.append(keyName)

    ncramConfig: Opt[Dict] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      prevKeySeq=prevKeySeq[:-1],
      fail=False,
    )

    regions = Memory.readMemRegionSequence(ncramConfig, prevKeySeq,
      name="NCRAM",
      oneLineDescription = "Non-Cacheable Random Access Memory",
    )
    return regions


  @staticmethod
  def readMemRegionSequence(
      userProvidedConfig,  # a list or dict input
      prevKeySeq: Opt[List] = None,
      name : str = "",
      oneLineDescription : str = "",
  ) -> List[MemoryRegion]:
    regions : List[MemoryRegion] = []
    if userProvidedConfig:
      if isinstance(userProvidedConfig, List):
        total = len(userProvidedConfig)
        for i, ncr in enumerate(userProvidedConfig):
          prevKeySeq.append(i)
          reg = MemoryRegion.generateObject(ncr, prevKeySeq)
          reg.name = f"{name} ({i+1}/{total})"
          reg.oneLineDescription = oneLineDescription
          regions.append(reg)
          prevKeySeq.pop()
      else:
        assert isinstance(userProvidedConfig, Dict)
        reg = MemoryRegion.generateObject(userProvidedConfig, prevKeySeq)
        reg.name = name
        reg.oneLineDescription = oneLineDescription
        regions.append(reg)
    else:
      regions = [MemoryRegion(
        name=name,
        oneLineDescription=oneLineDescription,
        virtualStartAddr=0x0,
        physicalStartAddr=0x0,
        sizeInBytes=0,
        cacheable=False,
      )]

    prevKeySeq.pop()
    return regions


  @staticmethod
  def generateRamRegion(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> MemoryRegion:
    keyName = "RAM"
    prevKeySeq.append(keyName)

    ramConfig: Opt[Dict] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      prevKeySeq=prevKeySeq[:-1],
      fail=True,
    )

    if ramConfig:
      ram = MemoryRegion.generateObject(ramConfig, prevKeySeq)
    else:
      ram = MemoryRegion(
        name="RAM",
        oneLineDescription="Random Access Memory",
        virtualStartAddr=0x0,
        physicalStartAddr=0x0,
        sizeInBytes=0,
      )

    prevKeySeq.pop()
    return ram


  @staticmethod
  def generateMmioRegions(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> List[MemoryRegion]:
    keyName = "MMIO"
    prevKeySeq.append(keyName)

    mmioConfig: Opt[Dict] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
    )

    regions = Memory.readMemRegionSequence(mmioConfig, prevKeySeq,
      name = "MMIO",
      oneLineDescription = "Memory Mapped IO",
    )

    if len(regions) == 1 and regions[0].sizeInBytes == 0:
      regions[0] = MemoryRegion(
        name="MMIO",
        oneLineDescription="Memory Mapped IO.",
        virtualStartAddr=0,
        physicalStartAddr=0,
        sizeInBytes=0,
      )

    # if len(regions) == 1 and regions[0].sizeInBytes == 0:
    #   regions[0] = MemoryRegion(
    #     name="MMIO",
    #     oneLineDescription="Memory Mapped IO.",
    #     virtualStartAddr=0xFFFF0000,
    #     physicalStartAddr=0xFFFF0000,
    #     sizeInBytes=2 ** 16,
    #   )

    prevKeySeq.pop()
    return regions

