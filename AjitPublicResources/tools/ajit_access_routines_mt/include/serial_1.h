#ifndef _serial_1_h____
#define _serial_1_h____

#include "device_addresses.h"

#define TX_ENABLE 	0x1 
#define RX_ENABLE 	0x2 
#define RX_INTR_ENABLE 	0x4 
#define TX_FULL   	0x8
#define RX_FULL   	0x10

uint32_t calculate_baud_control_word_for_uart (uint32_t baud_rate, uint32_t clock_frequency);

// Only via memory map for serial_1
inline void      __ajit_write_serial_1_control_register_via_vmap__(uint32_t val);
inline uint32_t  __ajit_read_serial_1_control_register_via_vmap__();
inline void      __ajit_write_serial_1_tx_register_via_vmap__(uint8_t val);
inline uint8_t   __ajit_read_serial_1_tx_register_via_vmap__();
inline uint8_t   __ajit_read_serial_1_rx_register_via_vmap__();

int   __ajit_serial_1_putchar_via_vmap__  (char c);
int   __ajit_serial_1_getchar_via_vmap__ ();
void  __ajit_serial_1_puts_via_vmap__ (char* s, uint32_t length);
void  __ajit_serial_1_gets_via_vmap__ (char* s, uint32_t length);
void  __ajit_serial_1_configure_via_vmap__ (uint8_t enable_tx, uint8_t enable_rx, uint8_t enable_intr);

#endif

