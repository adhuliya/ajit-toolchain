"""
User and system defined traps/interrupts.
"""
from typing import Dict, List, Optional as Opt

from cortos2.common import util


class TrapHandler:
  def __init__(self,
      trapCode: int,
      handlerFunc: str,
  ):
    self.trapCode = trapCode
    self.handlerFunc = handlerFunc

  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'TrapHandler':
    trapCode = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["TrapCode"],
      default=None,
    )

    funcName = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["Function"],
      default=None,
    )

    trapHandler = TrapHandler(
      trapCode=trapCode,
      handlerFunc=funcName,
    )
    return trapHandler

