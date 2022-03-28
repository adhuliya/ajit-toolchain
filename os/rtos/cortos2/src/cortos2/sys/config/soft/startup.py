"""The startup function to run on core 00"""
from typing import Dict, Optional as Opt, List

from cortos2.common import consts, util


class Startup:
  """Contains user/system provided startup initialization"""

  def __init__(self,
      startupFuncName: str = "",
  ) -> None:
    self.startupFuncName = startupFuncName


  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'Startup':
    keyName = "StartupFuncName"
    prevKeySeq.append(keyName)

    funcName: Opt[str] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default="",
      prevKeySeq=prevKeySeq[:-1],
    )

    prevKeySeq.pop()
    startup = Startup(
      startupFuncName=funcName,
    )
    return startup

