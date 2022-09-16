"""Some common definitions to circumvent circular dependencies."""
import os
from typing import List, Tuple, Dict, Optional as Opt

from cortos2.common import util, consts
from cortos2.common.consts import MemoryPermissions


class MemoryRegion(util.PrettyStr):
  """It represents a single contiguous memory region."""

  def __init__(self,
      name: str = "UnnamedRegion",
      oneLineDescription: str = "Unnamed Region",
      sizeInBytes: util.SizeInBytesT = 0,
      context: int = 0,
      virtualStartAddr: int = 0,  # the start address
      physicalStartAddr: int = 0,
      cacheable: bool = True,
      permissions: MemoryPermissions = 0x1,  # read,write for data
      regionType: str = consts.SOFT,
      initToZero: bool = False,
      initPageTableLevels: bool = True,
  ):
    self.name = name
    self.oneLineDescription = oneLineDescription
    self.sizeInBytes = sizeInBytes
    self.pageTableLevels: List[Tuple[consts.PageTableLevel, int]] = []
    self.context = context
    self.virtualStartAddr = virtualStartAddr
    self.physicalStartAddr = physicalStartAddr
    self.cacheable = cacheable
    self.permissions = permissions
    self.regionType = regionType
    self.initToZero = initToZero
    # Stores the extra space allocated to this region while allocating pages
    self.unusedSizeInBytes = 0

    if initPageTableLevels and self.sizeInBytes > 0:
      self.initPageTableLevels()


  @staticmethod
  def generateObject(
      userProvidedConfig: Dict,
      prevKeySeq: Opt[List] = None,
      initPageTableLevels: bool = True,
  ) -> 'MemoryRegion':
    """Takes a user given configuration and extracts the data into an object."""

    startAddr: int = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["StartAddr"],
      prevKeySeq=prevKeySeq,
      fail=True,
    )

    sizeInBytes = util.getSizeInBytes(
      data=userProvidedConfig,
      startAddr=startAddr,
      prevKeySeq=prevKeySeq,
      fail=True,
    )

    permissions: str = util.getConfigurationParameter(
      data=userProvidedConfig,
      keySeq=["Permissions"],
      default="RWXC",
      prevKeySeq=prevKeySeq,
    )

    memoryRegion = MemoryRegion(
      virtualStartAddr=startAddr,
      physicalStartAddr=startAddr,
      sizeInBytes=sizeInBytes,
      cacheable="C" in permissions.upper(),
      permissions=consts.getPagePermission(permissions),
      initPageTableLevels=initPageTableLevels,
    )
    return memoryRegion


  def getRangeStr(self, virtualAddr=True):
    if virtualAddr:
      return f"({hex(self.virtualStartAddr)}, {hex(self.getLastByteAddr(True))})"
    else:
      return f"({hex(self.physicalStartAddr)}, {hex(self.getLastByteAddr(False))})"


  def initPageTableLevels(self):
    """Determine the number of pages and their levels needed for this region.
    It tries to minimize space wastage and also minimize the number of
    page table entries.
    """
    self.pageTableLevels = []
    firstPageSizeInBytes = None

    firstAddress = self.physicalStartAddr
    sizeInBytes = self.sizeInBytes
    levels = sorted((x for x in consts.PageTableLevel), key=lambda x: x.value)
    while sizeInBytes >= 2 ** 12:
      numOfPages = pageSizeInBytes = 0
      for level in levels:
        pageSizeInBytes = consts.PAGE_TABLE_LEVELS_TO_PAGE_SIZE[level]
        if firstAddress % pageSizeInBytes == 0:
          ratio = sizeInBytes / pageSizeInBytes
          if ratio >= 0.9:
            numOfPages = 1
            if ratio < 1:
              self.unusedSizeInBytes = int(pageSizeInBytes * (1 - ratio))
            break
          continue
      assert(numOfPages == 1 and pageSizeInBytes, f"{self.name}: {numOfPages}, {pageSizeInBytes}")
      if firstPageSizeInBytes is None:
        firstPageSizeInBytes = pageSizeInBytes if numOfPages else None
      self.pageTableLevels.append((level, numOfPages))
      sizeInBytes -= numOfPages * pageSizeInBytes
      firstAddress += pageSizeInBytes

    # fit the size left in a 4KB page
    if sizeInBytes > 0:
      pageSizeInBytes4KB = consts.PAGE_TABLE_LEVELS_TO_PAGE_SIZE[consts.PageTableLevel.LEVEL3]
      assert sizeInBytes < pageSizeInBytes4KB, f"{sizeInBytes} should be lower than 4KB."
      self.unusedSizeInBytes = pageSizeInBytes4KB - sizeInBytes
      if firstPageSizeInBytes is None:
        firstPageSizeInBytes = pageSizeInBytes4KB
      self.pageTableLevels.append((consts.PageTableLevel.LEVEL3, 1))

    assert firstPageSizeInBytes is not None, f"{self.name}, {self.sizeInBytes}"
    self.virtualStartAddr = util.alignAddress(self.virtualStartAddr, firstPageSizeInBytes)
    self.physicalStartAddr = util.alignAddress(self.physicalStartAddr, firstPageSizeInBytes)


  def getFirstByteAddr(self, virtualAddr: bool = True) -> int:
    return self.virtualStartAddr if virtualAddr else self.physicalStartAddr


  def getLastByteAddr(self, virtualAddr: bool = True):
    return self.getNextToLastByteAddr(virtualAddr=virtualAddr) - 1


  def getSizeInBytes(self):
    return self.getLastByteAddr() - self.getFirstByteAddr()


  def totalPagesUsed(self) -> int:
    """Returns the number of pages used."""
    totalPages = 0
    for level, count in self.pageTableLevels:
      totalPages += count
    return totalPages


  def pagedSizeInBytes(self) -> int:
    """Returns the size occupied by all the pages."""
    pagedSizeInBytes = 0
    for level, count in self.pageTableLevels:
      pageLevelSizeInBytes = consts.PAGE_TABLE_LEVELS_TO_PAGE_SIZE[level]
      pagedSizeInBytes += pageLevelSizeInBytes * count
    return pagedSizeInBytes


  def getNextToLastByteAddr(self,
      virtualAddr: bool = True,  # set False to use physical address
  ) -> int:
    """Returns the address of the first byte just after the allocated space."""
    baseAddr = self.virtualStartAddr if virtualAddr else self.physicalStartAddr
    nextToLastByteAddr = baseAddr + self.pagedSizeInBytes()
    return nextToLastByteAddr


  @staticmethod
  def getVmapFileEntryLine(
      context: int = 0,
      virtualAddr: int = 0,
      physicalAddr: int = 0,
      pageTableLevel: int = 0,
      cacheable: bool = True,
      permissions: int = 0x1,  # read,write for data
  ):
    return f"{hex(context)} {hex(virtualAddr)} {hex(physicalAddr)}" \
           f" {hex(pageTableLevel)} {hex(cacheable)} {hex(permissions)}" \
           f"{os.linesep}"


  def getVmapFileEntryLines(self) -> List[str]:
    """Returns the entry lines to be put in a vmap file."""
    entryLines: List[str] = []
    pagedSizeStr = util.getSizeStr(self.pagedSizeInBytes())
    entryLines.append(f"!{self.name}: {self.oneLineDescription}{os.linesep}")
    entryLines.append(f"! {pagedSizeStr} : Virtual {hex(self.virtualStartAddr)}"
                      f" to {hex(self.getLastByteAddr(True))}{os.linesep}")

    virtualAddr = self.virtualStartAddr
    physicalAddr = self.physicalStartAddr
    for level, count in self.pageTableLevels:
      page_size = consts.PAGE_TABLE_LEVELS_TO_PAGE_SIZE[level]
      for i in range(count):
        entryLine = self.getVmapFileEntryLine(
          context=self.context,
          virtualAddr=virtualAddr + page_size * i,
          physicalAddr=physicalAddr + page_size * i,
          pageTableLevel=level.value,
          cacheable=self.cacheable,
          permissions=self.permissions.value,
        )
        entryLines.append(entryLine)

      virtualAddr += page_size * count
      physicalAddr += page_size * count

    return entryLines


