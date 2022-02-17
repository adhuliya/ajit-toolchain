from typing import Dict, List, Optional as Opt

from cortos2.common import util
from cortos2.sys.config.hard.hardware import Hardware
from cortos2.sys.config.soft.bget import Bget
from cortos2.sys.config.soft.build import Build
from cortos2.sys.config.soft.lock import Locks
from cortos2.sys.config.soft.program import Program
from cortos2.sys.config.soft.projectfiles import ProjectFiles
from cortos2.sys.config.soft.queue import QueueSeq


class Software:
  def __init__(self,
      projectFiles: ProjectFiles,
      program: Program,
      build: Build,
      bget: Bget,
      locks: Locks,
      queueSeq: QueueSeq,
  ):
    self.projectFiles = projectFiles
    self.program = program
    self.build = build
    self.bget = bget
    self.locks = locks
    self.queueSeq = queueSeq

  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      hardware: Hardware,
      prevKeySeq: Opt[List] = None,
  ) -> 'Software':
    """Takes a user given configuration and extracts the CPU related configuration."""

    keyName = "Software"
    prevKeySeq.append(keyName)

    config: Opt[Dict] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=None,
      prevKeySeq=prevKeySeq[:-1],
      fail=True,
    )

    build = Build.generateObject(
      userProvidedConfig=config,
      prevKeySeq=prevKeySeq,
    )

    projectFiles = ProjectFiles()
    projectFiles.readProjectFiles()

    program = Program.generateObject(
      userProvidedConfig=config,
      ajitCpu=hardware.cpu,
      prevKeySeq=prevKeySeq,
    )

    bget = Bget.generateObject(
      userProvidedConfig=config,
      prevKeySeq=prevKeySeq,
    )

    queueSeq = QueueSeq.generateObject(
      userProvidedConfig=config,
      prevKeySeq=prevKeySeq,
    )

    locks = Locks.generateObject(
      userProvidedConfig=config,
      queueSeq=queueSeq,
      prevKeySeq=prevKeySeq,
    )

    prevKeySeq.pop()
    software = Software(
      projectFiles=projectFiles,
      program=program,
      build=build,
      bget=bget,
      locks=locks,
      queueSeq=queueSeq,
    )
    return software
