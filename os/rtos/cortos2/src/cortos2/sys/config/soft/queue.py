"""Message passing queues in the system."""
from typing import List, Dict, Optional as Opt

from cortos2.common import consts, util
from cortos2.sys.config import common


class Queue:
  """A single queue and its details."""

  def __init__(self,
      qid: int, # A unique id of the queue
      length: int,
      msgSizeInBytes: int,
      name: Opt[str] = None,
  ) -> None:
    self.qid = qid
    self.length = length
    self.msgSizeInBytes = msgSizeInBytes
    self.name = name


  def getSizeInBytes(self) -> int:
    return self.msgSizeInBytes * self.length


  def getName(self) -> str:
    return self.name if self.name else f"{self.qid}"


  @staticmethod
  def generateObject(
      userProvidedConfig: Opt[Dict],
      prevKeySeq: Opt[List] = None,
  ) -> 'Queue':

    name: str = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["Name"],
      default=None,
      prevKeySeq=prevKeySeq,
    )

    msgSizeInBytes: int = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["MsgSizeInBytes"],
      default=None,
      prevKeySeq=prevKeySeq,
      fail=True,
    )

    length: int = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["Length"],
      default=None,
      prevKeySeq=prevKeySeq,
      fail=True,
    )

    queue = Queue(
      qid=0, # is set separately
      msgSizeInBytes=msgSizeInBytes,
      length=length,
      name=name,
    )
    return queue


class QueueSeq:
  """List of all the queues in the system."""

  def __init__(self,
      queueSeq: List[Queue],
  ):
    self.queueSeq: List[Queue] = queueSeq

    # Populated with the memory layout.
    self.region: Opt[common.MemoryRegion] = None
    self.headersStartAddr = 0
    self.msgStartAddr = 0


  def setMemoryRegion(self,
      region: common.MemoryRegion,
  ) -> None:
    self.region = region
    self.headersStartAddr = region.getFirstByteAddr(virtualAddr=True)
    self.msgStartAddr = self.headersStartAddr + self.getTotalQueueHeadersSizeInBytes()


  def checkInvariants(self):
    assert self.msgStartAddr + self.getTotalQueueSizeInBytes() <= \
           self.region.getNextToLastByteAddr(virtualAddr=True), f"Memory Layout Overflow!"


  def getTotalQueues(self) -> int:
    return len(self.queueSeq)


  def getTotalQueueHeadersSizeInBytes(self) -> int:
    return self.getTotalQueues() * consts.QUEUE_HEADER_SIZE_IN_BYTES


  def getTotalQueueSizeInBytes(self) -> int:
    sizeInBytes = 0
    for q in self.queueSeq:
      sizeInBytes += q.getSizeInBytes()
    return sizeInBytes


  def getHeadersEndAddr(self):
    """Return address of the last byte of the headers array."""
    return self.headersStartAddr + self.getTotalQueueHeadersSizeInBytes() - 1


  def getMsgEndAddr(self):
    """Returns address of the last byte of the message array."""
    return self.msgStartAddr + self.getTotalQueueSizeInBytes() - 1


  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
  ) -> 'QueueSeq':
    """Takes a user given configuration and extracts the Queue related configuration."""
    keyName = "Queues"
    prevKeySeq.append(keyName)

    queueConfigList: Opt[List] = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=[keyName],
      default=None,
      prevKeySeq=prevKeySeq[:-1],
    )

    if queueConfigList is None:
      prevKeySeq.pop()
      return QueueSeq([])

    queueList = []
    for i, queueConfig in enumerate(queueConfigList):
      prevKeySeq.append(i)
      queue = Queue.generateObject(queueConfig, prevKeySeq)
      queue.qid = i
      queueList.append(queue)
      prevKeySeq.pop()

    prevKeySeq.pop()
    return QueueSeq(queueList)


  def __len__(self):
    return len(self.queueSeq)


def initConfig(userProvidedConfig: Dict) -> QueueSeq:
  # TODO: add configuration options for queues.
  qSeq: List[Queue] = []
  for i in range(consts.DEFAULT_TOTAL_QUEUES):
    queue = Queue(
      qid=i,
      length=consts.DEFAULT_QUEUE_LEN,
      msgSizeInBytes=consts.DEFAULT_QUEUE_MSG_SIZE_IN_BYTES
    )
    qSeq.append(queue)

  queueSeq = QueueSeq(queueSeq=qSeq)
  return queueSeq
