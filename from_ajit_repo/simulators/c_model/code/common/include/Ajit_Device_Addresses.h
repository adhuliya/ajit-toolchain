// Ajit_Device_Addresses.h
//
//
// Addresses used by the memory-mapped device registers
// in the Ajit processor platform.
//
// Note: ALL ADDRESSES MUST BE DOUBLE WORD ALIGNED.
//

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

//sdhc registers
#define ADDR_SDHC_ARG_2                 0xFFFF4000      // 4 BYTES WIDE
#define ADDR_SDHC_BLOCK_SIZE            0xFFFF4004      // 2 BYTES WIDE
#define ADDR_SDHC_BLOCK_COUNT           0xFFFF4006      // 2 BYTES WIDE
#define ADDR_SDHC_ARG_1                 0xFFFF4008      // 4 BYTES WIDE
#define ADDR_SDHC_TRANSFER_MODE         0xFFFF400C      // 2 BYTES WIDE
#define ADDR_SDHC_REGISTER_COMMAND      0xFFFF400E      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE              0xFFFF4010      // 16 BYTES WIDE
#define ADDR_SDHC_BUFFER_DATA_PORT      0xFFFF4020      // 4 BYTES WIDE
#define ADDR_SDHC_PRESENT_STATE         0xFFFF4024      // 4 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROL_1        0xFFFF4028      // 1 BYTES WIDE
#define ADDR_SDHC_POWER_CONTROL         0xFFFF4029      // 1 BYTES WIDE
#define ADDR_SDHC_BLOCK_GAP_CONTROL     0xFFFF402A      // 1 BYTES WIDE
#define ADDR_SDHC_WAKEUP_CONTROL        0xFFFF402B      // 1 BYTES WIDE
#define ADDR_SDHC_CLOCK_CONTROL         0xFFFF402C      // 2 BYTES WIDE
#define ADDR_SDHC_TIMEOUT_CONTROL       0xFFFF402E      // 1 BYTES WIDE
#define ADDR_SDHC_SOFTWARE_RESET        0xFFFF402F      // 1 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_STATUS    0xFFFF4030      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_STATUS     0xFFFF4032      // 2 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_STATUS_EN 0xFFFF4034      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_STATUS_EN  0xFFFF4036      // 2 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_SIGNAL_EN 0xFFFF4038      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_SIGNAL_EN  0xFFFF403A      // 2 BYTES WIDE
#define ADDR_SDHC_AUTO_CMD_ERROR_STATUS 0xFFFF403C      // 2 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROL_2        0xFFFF403E      // 2 BYTES WIDE
#define ADDR_SDHC_CAPS                  0xFFFF4040      // 8 BYTES WIDE
#define ADDR_SDHC_MAX_CURRENT_CAPS      0xFFFF4048      // 4 BYTES WIDE
#define ADDR_SDHC_HOST_PRESET_VALUES    0xFFFF4060      // 16 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROLLER_VERSION       0xFFFF40FE      // 2 BYTES WIDE

#define ADDR_SD_REGISTERS   0xFFFF4100 //sd regs
//
// TODO: assign addresses to the SD card host controller
//     For example you could start from 0xffff4000 for
//     the SD card registers.
//
