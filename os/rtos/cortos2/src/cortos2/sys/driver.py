#!/usr/bin/env python3

# Author: Anshuman Dhuliya (AD) (anshumandhuliya@gmail.com)

"""
Driver program for the project.
This is invoked by main.py and the test routines.
"""

import argparse

from cortos2.common import consts, util
from cortos2.sys.config import config
from cortos2.sys.gen import build
from cortos2.common.util import FileNameT
from cortos2.common import bottle as btl

#mainentry
def main():
  """Call this function to start the driver for CoRTOS."""
  init() #IMPORTANT
  parser = getParser()
  args = parser.parse_args()  # parse command line
  args.func(args)             # take action


def init():
  """Misc initializations in the project."""
  templatesPath = util.getAbsolutePathFromScriptRelativeFilePath("../xfiles")
  btl.TEMPLATE_PATH.clear()
  btl.TEMPLATE_PATH.append(templatesPath)


def printDetail(args: argparse.Namespace) -> None:
  objName = args.object
  configFileName = args.configFileName

  if objName == "config":
    printConfigFile(configFileName)
  elif objName == "init":
    print("TODO_INIT")
  else:
    raise ValueError(f"Unknown object to print: {objName}")


def printConfigFile(configFileName: FileNameT) -> None:
  """Prints parsed config file to the output."""
  conf = config.readYamlConfig(configFileName)
  print("ConfigFileData: Original:")
  print(conf.userProvidedConfig)

  print("#" * 64)
  conf = config.SystemConfig(conf.userProvidedConfig)
  print("ConfigFileData: Processed:")
  print(conf)


def buildProject(args: argparse.Namespace) -> None:
  """Builds the project for Ajit Processor/CoRTOS.
  It creates a configuration object and starts the build process
  which uses the object.
  """
  configFileName = args.configFileName
  confObj = config.readYamlConfig(configFileName)
  confObj.software.build.setDebugParameter(args.debug, args.port)
  confObj.software.build.setOptLevel(args.O0, args.O1, args.O2)
  build.buildProject(confObj)


def getParser() -> argparse.ArgumentParser:
  # process the command line arguments
  parser = argparse.ArgumentParser(description="CoRTOS")
  subParser = parser.add_subparsers(title="subcommands", dest="subcommand",
                                    help="use ... <subcommand> -h     for more help")
  subParser.required = True

  # subcommand: build
  subpar = subParser.add_parser("build", help="Build a project.")
  subpar.set_defaults(func=buildProject)
  # subpar.add_argument('-l', '--logging', action='count', default=0)
  subpar.add_argument('-g', '--debug', action='store_true', default=False,
                      help="Enable debug build. If enabled, optimization level is set to 0.")
  subpar.add_argument('-p', '--port', type=int, default=8888,
                      help="Starting debug server port sequence.")
  subpar.add_argument('-O0', '--O0', action='store_true', default=False,
                      help="Optimization level 0 (O0).")
  subpar.add_argument('-O1', '--O1', action='store_true', default=False,
                      help="Optimization level 1 (O1).")
  subpar.add_argument('-O2', '--O2', action='store_true', default=False,
                      help="Optimization level 2 (O2).")
  subpar.add_argument("configFileName",
                      nargs="?",
                      default=consts.CONFIG_FILE_DEFAULT_NAME,
                      help=f"{consts.CONFIG_FILE_DEFAULT_NAME} file path.")

  # subcommand: print
  subpar = subParser.add_parser("show", help="Show a specific detail")
  subpar.set_defaults(func=printDetail)
  # subpar.add_argument('-l', '--logging', action='count', default=0)
  subpar.add_argument("object",
                      choices=["config", "init", "header"],
                      help="Object to print.")
  subpar.add_argument("configFileName",
                      nargs="?",
                      default=consts.CONFIG_FILE_DEFAULT_NAME,
                      help="Config file path.")

  return parser
