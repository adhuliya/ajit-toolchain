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

#define ADDR_SDHC_BASE_REGISTER                 0xFFFF3000

#define ADDR_SDHC_ARG_2                         0xFFFF3000      // 4 BYTES WIDE
#define ADDR_SDHC_BLOCK_SIZE                    0xFFFF3004      // 2 BYTES WIDE
#define ADDR_SDHC_BLOCK_COUNT                   0xFFFF3006      // 2 BYTES WIDE
#define ADDR_SDHC_ARG_1                         0xFFFF3008      // 4 BYTES WIDE
#define ADDR_SDHC_TRANSFER_MODE                 0xFFFF300C      // 2 BYTES WIDE
#define ADDR_SDHC_REGISTER_COMMAND              0xFFFF300E      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE                      0xFFFF3010      // 16 BYTES WIDE
#define ADDR_SDHC_BUFFER_DATA_PORT              0xFFFF3020      // 4 BYTES WIDE
#define ADDR_SDHC_PRESENT_STATE                 0xFFFF3024      // 4 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROL_1                0xFFFF3028      // 1 BYTES WIDE
#define ADDR_SDHC_POWER_CONTROL                 0xFFFF3029      // 1 BYTES WIDE
#define ADDR_SDHC_BLOCK_GAP_CONTROL             0xFFFF302A      // 1 BYTES WIDE
#define ADDR_SDHC_WAKEUP_CONTROL                0xFFFF302B      // 1 BYTES WIDE
#define ADDR_SDHC_CLOCK_CONTROL                 0xFFFF302C      // 2 BYTES WIDE
#define ADDR_SDHC_TIMEOUT_CONTROL               0xFFFF302E      // 1 BYTES WIDE
#define ADDR_SDHC_SOFTWARE_RESET                0xFFFF302F      // 1 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_STATUS            0xFFFF3030      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_STATUS             0xFFFF3032      // 2 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_STATUS_EN         0xFFFF3034      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_STATUS_EN          0xFFFF3036      // 2 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_SIGNAL_EN         0xFFFF3038      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_SIGNAL_EN          0xFFFF303A      // 2 BYTES WIDE
#define ADDR_SDHC_AUTO_CMD_ERROR_STATUS         0xFFFF303C      // 2 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROL_2                0xFFFF303E      // 2 BYTES WIDE
#define ADDR_SDHC_CAPS                          0xFFFF3040      // 8 BYTES WIDE
#define ADDR_SDHC_MAX_CURRENT_CAPS              0xFFFF3048      // 4 BYTES WIDE
#define ADDR_SDHC_HOST_PRESET_VALUES            0xFFFF3060      // 16 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROLLER_VERSION       0xFFFF30FE      // 2 BYTES WIDE