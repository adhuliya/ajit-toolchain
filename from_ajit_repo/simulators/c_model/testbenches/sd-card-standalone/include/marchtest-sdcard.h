
#define SDBase 0xff3300

#define Argument2 0x00
#define BlockSize 0x04
#define BlockCount 0x06
#define Argument1 0x08
#define Transfer 0x0c
#define Command 0x0e
#define Response0 0x10
#define Response1 0x12
#define Response2 0x14
#define Response3 0x16
#define Response4 0x18
#define Response5 0x1a
#define Response6 0x1c
#define Response7 0x1e
#define BufferDataPort 0x20
#define PresentState 0x24
#define HostControl 0x28
#define PowerControl 0x29
#define BlockGapControl 0x2A
#define WakeupControl 0x2B
#define ClockControl 0x2C
#define TimeoutControl 0x2E
#define SoftwareReset 0x2F
#define NormalInterruptStatus 0x30
#define ErrorInterruptStatus 0x32
#define NormalInterruptStatusEnable 0x34
#define ErrorInterruptStatusEnable 0x36
#define NormalInterruptSignalEnable 0x38
#define ErrorInterruptSignalEnable 0x3A
#define AutoCmdError 0x3C
#define HostControl2 0x3E
#define Capabilities 0x40

//takes the address of the register and writes the data
//in it, and reads it afterwards, prints messages for the same
int marchTest(long int addr, uint32_t data, char *regName, long int byte_mask);
