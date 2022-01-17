// Ajit_Device_Addresses.h
//
//
// Addresses used by the memory-mapped device registers
// in the Ajit processor platform.

//Interrupt controller (control register)
#define ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER 0xFFFF3000

//Timer
#define ADDR_TIMER_CONTROL_REGISTER 0xFFFF3100

//Serial device (UART)
//If set to 1, a thread modelling the serial device is started.

#define ADDR_SERIAL_CONTROL_REGISTER 0xFFFF3200
//Tx and Rx are 8-bit registers
//and must be accessed using byte-operations only.
#define ADDR_SERIAL_TX_REGISTER      0xFFFF3210
#define ADDR_SERIAL_RX_REGISTER      0xFFFF3220

