"""
Hardware description.
"""
from typing import Dict, Optional as Opt, List

from cortos2.common import util
from cortos2.sys.config.hard.device import Device
from cortos2.sys.config.hard.processor import Processor
from cortos2.sys.config.hard.memory import Memory


class Hardware:
  """
  Hardware Specification (CPU, Memory, ...).
  """
  def __init__(self,
      cpu: Processor,
      memory: Memory,
      devices: Dict[str, Device],
  ) -> None:
    self.cpu = cpu
    self.memory = memory
    self.devices = devices


  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'Hardware':
    """Takes a user given configuration and extracts the CPU related configuration."""

    keyName = "Hardware"
    config: Opt[Dict] = util.getConfigurationParameter(
      userProvidedConfig,
      [keyName],
    )

    cpu = Processor.generateObject(config, prevKeySeq=[keyName])
    memory = Memory.generateObject(config, prevKeySeq=[keyName])
    devices = Hardware.generateDevices(config, prevKeySeq=[keyName])

    hardware = Hardware(
      cpu=cpu,
      memory=memory,
      devices=devices,
    )
    return hardware


  @staticmethod
  def generateDevices(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> Dict[str, Device]:
    data = dict()
    keyName = "Devices"
    prevKeySeq.append(keyName)

    config: Opt[List] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=None,
    )

    if config: # must be a list
      for index, deviceConfig in enumerate(config):
        prevKeySeq.append(index)
        device = Device.generateObject(
          userProvidedConfig=deviceConfig,
          prevKeySeq=prevKeySeq,
        )
        data[device.name] = device
        prevKeySeq.pop()

    prevKeySeq.pop()
    return data

