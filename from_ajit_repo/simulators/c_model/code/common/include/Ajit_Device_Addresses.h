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


#define ADDR_SDHC_ARG_2                         0xFFFF3300      // 4 BYTES WIDE
#define ADDR_SDHC_BLOCK_SIZE                    0xFFFF3304      // 2 BYTES WIDE
#define ADDR_SDHC_BLOCK_COUNT                   0xFFFF3306      // 2 BYTES WIDE
#define ADDR_SDHC_ARG_1                         0xFFFF3308      // 4 BYTES WIDE
#define ADDR_SDHC_TRANSFER_MODE                 0xFFFF330C      // 2 BYTES WIDE
#define ADDR_SDHC_REGISTER_COMMAND              0xFFFF330E      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE                      0xFFFF3310      // 16 BYTES WIDE
#define ADDR_SDHC_BUFFER_DATA_PORT              0xFFFF3320      // 4 BYTES WIDE
#define ADDR_SDHC_PRESENT_STATE                 0xFFFF3324      // 4 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROL_1                0xFFFF3328      // 1 BYTES WIDE
#define ADDR_SDHC_POWER_CONTROL                 0xFFFF3329      // 1 BYTES WIDE
#define ADDR_SDHC_BLOCK_GAP_CONTROL             0xFFFF332A      // 1 BYTES WIDE
#define ADDR_SDHC_WAKEUP_CONTROL                0xFFFF332B      // 1 BYTES WIDE
#define ADDR_SDHC_CLOCK_CONTROL                 0xFFFF332C      // 2 BYTES WIDE
#define ADDR_SDHC_TIMEOUT_CONTROL               0xFFFF332E      // 1 BYTES WIDE
#define ADDR_SDHC_SOFTWARE_RESET                0xFFFF332F      // 1 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_STATUS            0xFFFF3330      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_STATUS             0xFFFF3332      // 2 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_STATUS_EN         0xFFFF3334      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_STATUS_EN          0xFFFF3336      // 2 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_SIGNAL_EN         0xFFFF3338      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_SIGNAL_EN          0xFFFF333A      // 2 BYTES WIDE
#define ADDR_SDHC_AUTO_CMD_ERROR_STATUS         0xFFFF333C      // 2 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROL_2                0xFFFF333E      // 2 BYTES WIDE
#define ADDR_SDHC_CAPS                          0xFFFF3340      // 8 BYTES WIDE
#define ADDR_SDHC_MAX_CURRENT_CAPS              0xFFFF3348      // 4 BYTES WIDE
#define ADDR_SDHC_HOST_PRESET_VALUES            0xFFFF3360      // 16 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROLLER_VERSION       0xFFFF33FE      // 2 BYTES WIDE


