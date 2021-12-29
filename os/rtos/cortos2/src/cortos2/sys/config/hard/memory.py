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
      mmio: MemoryRegion, # memory mapped io
   ) -> None:
    self.flash = flash
    self.ram = ram
    self.mmio = mmio

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

    flash = Memory.generateFlashRegion(config, prevKeySeq)
    ram = Memory.generateRamRegion(config, prevKeySeq)
    mmio = Memory.generateMmioRegion(config, prevKeySeq)

    prevKeySeq.pop()
    memory = Memory(flash, ram, mmio)
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
      keySeq=[keyName]
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
  def generateRamRegion(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> MemoryRegion:
    keyName = "RAM"
    prevKeySeq.append(keyName)

    ramConfig: Opt[Dict] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName]
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


