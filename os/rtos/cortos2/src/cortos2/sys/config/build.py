"""The build related configuration."""
from typing import Dict, Optional as Opt

from cortos2.common import consts


class Build:
  """Contains configurations that affect compilation and linking settings."""

  def __init__(self,
      debug: bool = consts.DEFAULT_DEBUG_BUILD,
      firstDebugPort: int = consts.DEFAULT_FIRST_DEBUG_PORT,
      optLevel: int = consts.DEFAULT_OPT_LEVEL,
      logLevel: consts.LogLevel = consts.DEFAULT_LOG_LEVEL,
      enableSerial: bool = consts.DEFAULT_ENABLE_SERIAL_DEVICE,
  ) -> None:
    self.debug = debug
    self.firstDebugPort = firstDebugPort
    self.optLevel = optLevel
    self.logLevel = logLevel
    self.enableSerial = enableSerial


  def setDebugParameter(self,
      debug: bool = consts.DEFAULT_DEBUG_BUILD,
      port: int = consts.DEFAULT_FIRST_DEBUG_PORT,
  ):
    self.debug = debug
    self.firstDebugPort = port


  def setOptLevel(self,
      optLevel0: bool = False,
      optLevel1: bool = False,
      optLevel2: bool = False,
  ) -> None:
    self.optLevel = 0 if optLevel0 else self.optLevel
    self.optLevel = 1 if optLevel1 else self.optLevel
    self.optLevel = 2 if optLevel2 else self.optLevel


  def setLogLevel(self, logLevelStr: str):
    self.logLevel = consts.LogLevel[logLevelStr.upper()] \
      if logLevelStr else consts.DEFAULT_LOG_LEVEL

    if self.logLevel != consts.LogLevel.NONE:
      self.enableSerial = True


def initConfig(
    userProvidedConfig: Dict,
) -> Build:
  build = Build()

  logLevelStr: Opt[str] = userProvidedConfig[consts.YML_LOG_LEVEL] \
    if consts.YML_LOG_LEVEL in userProvidedConfig else consts.LogLevel.NONE.name
  build.setLogLevel(logLevelStr)

  return build
