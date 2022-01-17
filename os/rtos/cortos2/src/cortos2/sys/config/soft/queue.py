"""Message passing queues in the system."""
from typing import List, Dict, Optional as Opt

from cortos2.common import consts
from cortos2.sys.config import common


class Queue:
  """A single queue and its details."""

  def __init__(self,
      qid: int, # A unique id of the queue
      length: int = consts.DEFAULT_QUEUE_LEN,
      msgSizeInBytes: int = consts.DEFAULT_QUEUE_MSG_SIZE_IN_BYTES,
  ) -> None:
    self.qid = qid
    self.length = length
    self.msgSizeInBytes = msgSizeInBytes


  def getSizeInBytes(self) -> int:
    return self.msgSizeInBytes * self.length


class QueueSeq:
  """List of all the queues in the system."""

  def __init__(self,
      queueSeq: List[Queue],
  ):
    self.queueSeq: List[Queue] = queueSeq

    self.queueHeaderSizeInBytes: int = consts.QUEUE_HEADER_SIZE_IN_BYTES
    self.queueMsgSizeInBytes = consts.DEFAULT_QUEUE_MSG_SIZE_IN_BYTES
    self.elementsPerQueue = consts.DEFAULT_QUEUE_LEN

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
    # TODO
    return initConfig(userProvidedConfig)


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
