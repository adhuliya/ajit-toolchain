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


// sdhc registers; actual values range from 0xFFFF3300 - 0xFFFF33FF
// values modified for easy processing as 24 bits. 



#define ADDR_SDHC_ARG_2                         0xFF3300      // 4 BYTES WIDE
#define ADDR_SDHC_BLOCK_SIZE                    0xFF3304      // 2 BYTES WIDE
#define ADDR_SDHC_BLOCK_COUNT                   0xFF3306      // 2 BYTES WIDE
#define ADDR_SDHC_ARG_1                         0xFF3308      // 4 BYTES WIDE
#define ADDR_SDHC_TRANSFER_MODE                 0xFF330C      // 2 BYTES WIDE
#define ADDR_SDHC_REGISTER_COMMAND              0xFF330E      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE0                     0xFF3310      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE1                     0xFF3312      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE2                     0xFF3314      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE3                     0xFF3316      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE4                     0xFF3318      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE5                     0xFF331A      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE6                     0xFF331C      // 2 BYTES WIDE
#define ADDR_SDHC_RESPONSE7                     0xFF331E      // 2 BYTES WIDE
#define ADDR_SDHC_BUFFER_DATA_PORT              0xFF3320      // 4 BYTES WIDE
#define ADDR_SDHC_PRESENT_STATE                 0xFF3324      // 4 BYTES WIDE
#define ADDR_SDHC_POWER_CONTROL                 0xFF3328      // 1 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROL_1                0xFF3329      // 1 BYTES WIDE
#define ADDR_SDHC_WAKEUP_CONTROL                0xFF332A      // 1 BYTES WIDE
#define ADDR_SDHC_BLOCK_GAP_CONTROL             0xFF332B      // 1 BYTES WIDE
#define ADDR_SDHC_CLOCK_CONTROL                 0xFF332C      // 2 BYTES WIDE
#define ADDR_SDHC_SOFTWARE_RESET                0xFF332E      // 1 BYTES WIDE
#define ADDR_SDHC_TIMEOUT_CONTROL               0xFF332F      // 1 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_STATUS            0xFF3330      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_STATUS             0xFF3332      // 2 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_STATUS_EN         0xFF3334      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_STATUS_EN          0xFF3336      // 2 BYTES WIDE
#define ADDR_SDHC_NORMAL_INTR_SIGNAL_EN         0xFF3338      // 2 BYTES WIDE
#define ADDR_SDHC_ERROR_INTR_SIGNAL_EN          0xFF333A      // 2 BYTES WIDE
#define ADDR_SDHC_AUTO_CMD_ERROR_STATUS         0xFF333C      // 2 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROL_2                0xFF333E      // 2 BYTES WIDE
#define ADDR_SDHC_CAPS                          0xFF3340      // 8 BYTES WIDE
#define ADDR_SDHC_MAX_CURRENT_CAPS              0xFF3348      // 4 BYTES WIDE
#define ADDR_SDHC_MAX_CURRENT_CAPS_RES          0xFF334C      // 4 BYTES WIDE
#define ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT   0xFF3350      // 2 BYTES WIDE
#define ADDR_SDHC_FORCE_EVENT_AUTOCMD_ERRSTAT_R 0xFF3352      // 2 BYTES WIDE
#define ADDR_SDHC_ADMA_ERR_STAT                 0xFF3355      // 1 BYTE WIDE
#define ADDR_SDHC_ADMA_SYSTEM_ADDR              0xFF3358      // 8 BYTES WIDE
#define ADDR_SDHC_HOST_PRESET_VALUES            0xFF3360      // 16 BYTES WIDE
#define ADDR_SDHC_SHARED_BUS_CTRL               0xFF33E0      // 2 BYTES WIDE
#define ADDR_SDHC_SLOT_INTR_STATUS              0xFF33FC      // 2 BYTES WIDE
#define ADDR_SDHC_HOST_CONTROLLER_VERSION       0xFF33FE      // 2 BYTES WIDE


