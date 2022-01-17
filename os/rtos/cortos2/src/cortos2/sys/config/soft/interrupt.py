"""
User defined interrupts.
"""
from typing import Dict, List, Optional as Opt

from cortos2.common import util


class InterruptHandler:
  def __init__(self,
      typeCode: int,
      funcName: str,
  ):
    self.typeCode = typeCode
    self.funcName = funcName

  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'InterruptHandler':
    typeCode = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["TypeCode"],
      default=None,
    )

    funcName = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["Function"],
      default=None,
    )

    intHandler = InterruptHandler(
      typeCode=typeCode,
      funcName=funcName,
    )
    return intHandler

