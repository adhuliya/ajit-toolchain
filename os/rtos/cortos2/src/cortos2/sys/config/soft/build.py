"""The build related configuration."""
import os
from typing import Dict, Optional as Opt, List

from cortos2.common import consts, util


class Build:
  """Contains configurations that affect compilation and linking settings."""

  def __init__(self,
      debug: bool = consts.DEFAULT_DEBUG_BUILD,
      firstDebugPort: int = consts.DEFAULT_FIRST_DEBUG_PORT,
      optLevel: int = consts.DEFAULT_OPT_LEVEL,
      logLevel: consts.LogLevel = consts.DEFAULT_LOG_LEVEL,
      useLibAjit: bool = consts.DEFAULT_USE_LIB_AJIT,
      useDefaultLibAjit: bool = consts.DEFAULT_USE_DEFAULT_LIB_AJIT,
      buildArgs: str = "",
  ) -> None:
    self.debug = debug
    self.firstDebugPort = firstDebugPort
    self.optLevel = optLevel
    self.logLevel = logLevel
    self.useLibAjit = useLibAjit
    self.useDefaultLibAjit = useDefaultLibAjit
    self.buildArgs = buildArgs


  def setDebugParameter(self,
      debug: bool = consts.DEFAULT_DEBUG_BUILD,
      port: int = consts.DEFAULT_FIRST_DEBUG_PORT,
  ):
    self.debug = (debug or self.debug)
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
      self.useLibAjit = True

  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'Build':
    keyName = "BuildAndExecute"
    prevKeySeq.append(keyName)

    config: Opt[Dict] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=None,
      prevKeySeq=prevKeySeq[:-1],
    )

    debug = Build.generateDebugParam(config, prevKeySeq)
    debugPort = Build.generateFirstDebugPortParam(config, prevKeySeq)
    optLevel = Build.generateOptLevelParam(config, prevKeySeq)
    logLevel = Build.generateLogLevelParam(config, prevKeySeq)
    useLibAjit = Build.generateUseLibAjitParam(config, prevKeySeq)
    useDefaultLibAjit = Build.generateUseDefaultLibAjitParam(config, prevKeySeq)
    buildArgs = Build.generateBuildArgsParam(config, prevKeySeq)

    prevKeySeq.pop()
    build = Build(
      debug=debug,
      firstDebugPort=debugPort,
      optLevel=optLevel,
      logLevel=logLevel,
      useLibAjit=useLibAjit,
      useDefaultLibAjit=useDefaultLibAjit,
      buildArgs=buildArgs,
    )
    return build


  @staticmethod
  def generateDebugParam(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> bool:
    keyName = "Debug"

    debugFlag: bool = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=consts.DEFAULT_DEBUG_BUILD,
      prevKeySeq=prevKeySeq,
    )
    debug = debugFlag

    return debug

  @staticmethod
  def generateOptLevelParam(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> int:
    keyName = "OptimizationLevel"

    optLevel: int = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=consts.DEFAULT_OPT_LEVEL,
      prevKeySeq=prevKeySeq,
    )
    if not 0 <= optLevel <= 2:
      optLevel = consts.DEFAULT_OPT_LEVEL

    return optLevel


  @staticmethod
  def generateLogLevelParam(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> consts.LogLevel:
    keyName = "LogLevel"

    logLevelStr: str = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=consts.DEFAULT_LOG_LEVEL.name,
      prevKeySeq=prevKeySeq,
    )

    return Build.getLogLevel(logLevelStr)


  @staticmethod
  def getLogLevel(logLevelStr: str) -> consts.LogLevel:
    return consts.LogLevel[logLevelStr.upper()] \
      if logLevelStr else consts.DEFAULT_LOG_LEVEL


  @staticmethod
  def generateUseDefaultLibAjitParam(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> bool:
    keyName = "UseDefaultLibAjit"

    useDefaultLibAjit: bool = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default= consts.DEFAULT_USE_DEFAULT_LIB_AJIT,
      prevKeySeq=prevKeySeq,
    )

    return useDefaultLibAjit


  @staticmethod
  def generateUseLibAjitParam(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> bool:
    keyName = "UseLibAjit"

    useLibAjit: bool = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default= consts.DEFAULT_USE_LIB_AJIT,
      prevKeySeq=prevKeySeq,
    )
    useLibAjitBool = useLibAjit

    return useLibAjitBool


  @staticmethod
  def generateFirstDebugPortParam(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> int:
    keyName = "FirstDebugPort"

    firstDebugPort: int = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=consts.DEFAULT_FIRST_DEBUG_PORT,
      prevKeySeq=prevKeySeq,
    )

    return int(firstDebugPort)


  @staticmethod
  def generateBuildArgsParam(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> str:
    keyName = "BuildArgs"

    buildArgs: str = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default="",
      prevKeySeq=prevKeySeq,
    )

    prevKeySeq.append(keyName)
    buildArgs = Build.checkBuildArgs(buildArgs, prevKeySeq)
    prevKeySeq.pop()

    return buildArgs


  @staticmethod
  def checkBuildArgs(
      buildArgs : str,
      prevKeySeq: Opt[List] = None,
  ) -> str:
    buildArgs2 = buildArgs.replace('\n', '\\\n')
    if '\n' != os.linesep and '\n' not in os.linesep:
      buildArgs2 = buildArgs2.replace(f'{os.linesep}', f'\\{os.linesep}')
    if len(buildArgs2) != len(buildArgs):
      print(f"Escaped newlines in {util.createKeySeqStr(prevKeySeq)}.")
    return buildArgs


def initConfig(
    userProvidedConfig: Dict,
) -> Build:
  build = Build()

  logLevelStr: Opt[str] = userProvidedConfig[consts.YML_LOG_LEVEL] \
    if consts.YML_LOG_LEVEL in userProvidedConfig else consts.LogLevel.NONE.name
  build.setLogLevel(logLevelStr)

  return build
