"""The configuration and layout of the system memory."""
from typing import List, Optional as Opt, Dict

from cortos2.common import util, consts
from cortos2.sys.config import common
from cortos2.sys.config.soft import bget, lock, queue, program
from cortos2.sys.config.common import MemoryRegion


class Memory:
  """Holds information about the memory available"""
  def __init__(self,
      flash: MemoryRegion,
      ram: MemoryRegion,
      ncram: MemoryRegion,
      mmio: MemoryRegion, # memory mapped io
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
    ncram = Memory.generateNcRamRegion(config, prevKeySeq)
    mmio = Memory.generateMmioRegion(config, prevKeySeq)

    prevKeySeq.pop()
    memory = Memory(flash, ram, ncram, mmio, physicalAddrWidth)
    return memory


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
  def generateNcRamRegion(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> MemoryRegion:
    keyName = "NCRAM"
    prevKeySeq.append(keyName)

    ncramConfig: Opt[Dict] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      prevKeySeq=prevKeySeq[:-1],
      fail=False,
    )

    if ncramConfig:
      ncram = MemoryRegion.generateObject(ncramConfig, prevKeySeq)
    else:
      ncram = MemoryRegion(
        virtualStartAddr=0x0,
        physicalStartAddr=0x0,
        sizeInBytes=0,
        cacheable=False,
      )
    ncram.name = "NCRAM"
    ncram.oneLineDescription = "Non-Cacheable Random Access Memory"

    prevKeySeq.pop()
    return ncram


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
  def generateMmioRegion(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> MemoryRegion:
    keyName = "MMIO"
    prevKeySeq.append(keyName)

    mmioConfig: Opt[Dict] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
    )

    if mmioConfig:
      io = MemoryRegion.generateObject(mmioConfig, prevKeySeq)
    else:
      io = MemoryRegion(
        name="MMIO",
        oneLineDescription="Memory Mapped IO.",
        virtualStartAddr=0xFFFF0000,
        physicalStartAddr=0xFFFF0000,
        sizeInBytes=2**16,
      )

    prevKeySeq.pop()
    return io


