"""
User and system defined traps/interrupts.
"""
from typing import Dict, List, Optional as Opt

from cortos2.common import util

class Handler:
  def __init__(self,
      index: int,
      function: str,
  ):
    self.index = index
    self.function = function

  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'Handler':
    trapCode = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["Index"],
      default=None,
      prevKeySeq=prevKeySeq,
    )

    funcName = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["Function"],
      default=None,
      prevKeySeq=prevKeySeq,
    )

    handler = Handler(
      index=trapCode,
      function=funcName,
    )
    return handler


class Traps:
  def __init__(self,
      hw: List[Handler],
      sw: List[Handler],
  ):
    self.hw = hw
    self.sw = sw

  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'Traps':
    keyName = "Interrupts"
    prevKeySeq.append(keyName)
    config: Opt[List] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=[],
      prevKeySeq=prevKeySeq,
    )
    hw = Traps.generateHandlerList(config, prevKeySeq)
    prevKeySeq.pop()

    keyName = "Traps"
    prevKeySeq.append(keyName)
    config: Opt[List] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=[],
      prevKeySeq=prevKeySeq,
    )
    sw = Traps.generateHandlerList(config, prevKeySeq)
    prevKeySeq.pop()

    traps = Traps(hw=hw, sw=sw)
    return traps


  @staticmethod
  def generateHandlerList(
      userProvidedConfig: List,
      prevKeySeq: Opt[List] = None,
  ) -> List[Handler]:

    trapList = []
    for i, item in enumerate(userProvidedConfig):
      prevKeySeq.append(i)
      trapList.append(Handler.generateObject(item, prevKeySeq))
      prevKeySeq.pop()

    return trapList


