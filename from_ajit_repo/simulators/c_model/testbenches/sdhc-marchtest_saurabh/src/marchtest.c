#include<stdio.h>
#include<stdint.h>
#include"Ajit_Device_Addresses.h"
#include"Sdhc.h"
#include"Pipes.h"
#include"Ancillary.h"
#include"marchtest.h"

int ReadWriteSDHCRegister(long int rwbar, long int bytemask, long int phyAdd, uint32_t data)
{
  /*Bit 63: rwbar
    Bit 62-59: bytemask
    Bits 58-56: Unused
    Bits 55-32: Physical address
    Bits 31- 0: data*/
  uint64_t writeData;
  uint32_t readData;
  int returnData;
  writeData = (rwbar << 63) | (bytemask << 59) | (phyAdd << 32) | data;
  write_uint64("peripheral_bridge_to_sdhc_request", writeData);
//  fprintf(stderr,"data written in peri_to_sdhc pipe is\r\n rwbar=0x%x\r\n, byte-mask=0x%x\r\n, addr=0x%x\r\n, data=0x%x\r\n, writeData=0x%lx\r\n",
//	rwbar, bytemask, phyAdd, data, writeData);
  readData = read_uint32("sdhc_to_peripheral_bridge_response");
  return readData;
}

int marchTest(long int addr, uint32_t data, char *registerName, long int byte_mask)
{
  long int rwbar=0;
  long int phyAdd=(SDBase+addr);
  fprintf(stderr,"\r\n#\r\nRegister under test: %s, data written is 0x%x\r\n",registerName,data);  
  int writeAck=ReadWriteSDHCRegister(0, byte_mask, phyAdd, data);
  fprintf(stderr, "write acknowledgment for %s register is %d\r\n",registerName, writeAck);
  int readData=ReadWriteSDHCRegister(1, byte_mask, phyAdd, 0);
  fprintf(stderr, "data read from %s register is 0x%x\r\n", registerName,readData);
}

int main()
{
startSdhcThreads();
marchTest(Argument2,0x12345678,"Argument 2",0xF);
marchTest(BlockCount,0x1234,"Block Count",0x3);
marchTest(BlockSize,0x2345,"Block Size",0x3);
marchTest(Argument1,0x23456789,"Argument 1",0xF);
marchTest(Transfer,0x3456,"Transfer Control",0x3);
marchTest(Command,0x4567,"Command",0x3);
marchTest(Response0,0x5678,"Response 0",0x3);
marchTest(Response1,0x6789,"Response 1",0x3);
marchTest(Response2,0x7890,"Response 2",0x3);
marchTest(Response3,0x89ab,"Response 3",0x3);
marchTest(Response4,0x9abc,"Response 4",0x3);
marchTest(Response5,0xabcd,"Response 5",0x3);
marchTest(Response6,0xbcde,"Response 6",0x3);
marchTest(Response7,0xcdef,"Response 7",0x3);
marchTest(BufferDataPort,0xfedcba98,"Buffer Data Port",0xF);
marchTest(PresentState,0xfeedbacc,"Present State",0xF);
marchTest(HostControl,0xab,"Host Control 1",0x1);
marchTest(PowerControl,0xbc,"Power Control",0x1);
marchTest(BlockGapControl,0xdb,"Block Gap Control",0x1);
marchTest(WakeupControl,0xcc,"Wake-up Control",0x1);
marchTest(ClockControl,0xdef1,"Clock Control",0x3);
marchTest(TimeoutControl,0xfa,"Timeout Control",0x1);
marchTest(SoftwareReset,0xef,"Software Reset",0x1);
marchTest(NormalInterruptStatus,0xf123,"Normal Interrupt Status",0x3);
marchTest(NormalInterruptStatus,0x1234,"Error Interrupt Status",0x3);
marchTest(NormalInterruptStatusEnable,0x2345,"Normal Interrupt Status Enable",0x3);
marchTest(ErrorInterruptStatusEnable,0x3456,"Error Interrupt Status Enable",0x3);
marchTest(NormalInterruptSignalEnable,0x4567,"Normal Interrupt Signal Enable",0x3);
marchTest(ErrorInterruptSignalEnable,0x5678,"Error Interrupt Signal Enable",0x3);
marchTest(AutoCmdError,0x6789,"Auto CMD Error",0x3);
marchTest(HostControl2,0x789A,"Host Control 2",0x3);
marchTest(Capabilities,0xfeedbacc,"Capabilities",0xF);
}
