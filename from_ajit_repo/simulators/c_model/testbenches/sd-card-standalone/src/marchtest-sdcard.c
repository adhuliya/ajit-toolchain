#include<stdio.h>
#include<stdint.h>
#include"Ajit_Device_Addresses.h"
#include"Pipes.h"
#include"Ancillary.h"
#include"marchtest-sdcard.h"

struct sdCardFrameData frameData={NULL};

void generateCommandForSDCard(uint8_t commandNumber)
{
//extracting command index value to be inserted in bits 40:45
	uint8_t cmd_index = getSlice16(internal_reg_view->command_reg,13,8);
	uint8_t crc7=7;//dummy value for now, will be updated with crc7 function's
							//return value later
	uint64_t frame_data=0;
	frame_data|=0UL<<47;//start bit
	frame_data|=1UL<<46;//tx bit
	frame_data|=(uint64_t)cmd_index<<40;
	frame_data|=<<8;
	frame_data|=crc7<<1;
	frame_data|=0UL<<0;
	write_uint64("sdhc_to_sdcard_request",frame_data);
}

void readResponseFromSdcard()
{

}

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
startSdCardThreads();
}
