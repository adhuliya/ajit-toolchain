#ifndef _serial_1_h____
#define _serial_1_h____
#include "device_addresses.h"

#define TX_ENABLE 	0x1 
#define RX_ENABLE 	0x2 
#define RX_INTR_ENABLE 	0x4 
#define TX_FULL   	0x8
#define RX_FULL   	0x10


//--------------------------------------------------------------------------------
// bypass.
//--------------------------------------------------------------------------------
void      __ajit_write_serial_1_control_register_via_bypass__(uint32_t val);
uint32_t  __ajit_read_serial_1_control_register_via_bypass__();
void      __ajit_write_serial_1_tx_register_via_bypass__(uint8_t val);
uint8_t   __ajit_read_serial_1_tx_register_via_bypass__();
uint8_t   __ajit_read_serial_1_rx_register_via_bypass__();


int   		__ajit_serial_1_putchar_via_bypass__  (char c);
int   		__ajit_serial_1_getchar_via_bypass__ ();
void  		__ajit_serial_1_puts_via_bypass__ (char* s, uint32_t length);
void  		__ajit_serial_1_gets_via_bypass__ (char* s, uint32_t length);
void  		__ajit_serial_1_configure_via_bypass__ (uint8_t enable_tx, uint8_t enable_rx, uint8_t enable_intr);
uint32_t    	__ajit_read_serial_1_baud_limit_register_via_bypass__();
void        	__ajit_write_serial_1_baud_limit_register_via_bypass__(uint32_t bcv);
uint32_t    	__ajit_read_serial_1_baud_frequency_register_via_bypass__();
void        	__ajit_write_serial_1_baud_frequency_register_via_bypass__(uint32_t bcv);

// baud rate and reset.
void 		__ajit_serial_1_set_baudrate_via_bypass__ (uint32_t baud_rate, uint32_t clock_frequency);
void  		__ajit_serial_1_set_uart_reset_via_bypass__ (uint8_t reset_value);


//--------------------------------------------------------------------------------
// Via vmap.
//--------------------------------------------------------------------------------
void      __ajit_write_serial_1_control_register_via_vmap__(uint32_t val);
uint32_t  __ajit_read_serial_1_control_register_via_vmap__();
void      __ajit_write_serial_1_tx_register_via_vmap__(uint8_t val);
uint8_t   __ajit_read_serial_1_tx_register_via_vmap__();
uint8_t   __ajit_read_serial_1_rx_register_via_vmap__();


int   		__ajit_serial_1_putchar_via_vmap__  (char c);
int   		__ajit_serial_1_getchar_via_vmap__ ();
void  		__ajit_serial_1_puts_via_vmap__ (char* s, uint32_t length);
void  		__ajit_serial_1_gets_via_vmap__ (char* s, uint32_t length);
void  		__ajit_serial_1_configure_via_vmap__ (uint8_t enable_tx, uint8_t enable_rx, uint8_t enable_intr);
uint32_t    	__ajit_read_serial_1_baud_limit_register_via_vmap__();
void        	__ajit_write_serial_1_baud_limit_register_via_vmap__(uint32_t bcv);
uint32_t    	__ajit_read_serial_1_baud_frequency_register_via_vmap__();
void        	__ajit_write_serial_1_baud_frequency_register_via_vmap__(uint32_t bcv);

// baud rate and reset.
void 		__ajit_serial_1_set_baudrate_via_vmap__ (uint32_t baud_rate, uint32_t clock_frequency);
void  		__ajit_serial_1_set_uart_reset_via_vmap__ (uint8_t reset_value);

#ifdef USE_VMAP
#define 	__ajit_write_serial_1_control_register__ __ajit_write_serial_1_control_register_via_vmap__
#define		__ajit_read_serial_1_control_register__  __ajit_read_serial_1_control_register_via_vmap__
#define 	__ajit_write_serial_1_tx_register__      __ajit_write_serial_1_tx_register_via_vmap__
#define		__ajit_read_serial_1_tx_register__       __ajit_read_serial_1_tx_register_via_vmap__
#define 	__ajit_read_serial_1_rx_register__       __ajit_read_serial_1_rx_register_via_vmap__
#define     	__ajit_write_serial_1_baud_limit_register__ 	__ajit_write_serial_1_baud_limit_register_via_vmap__
#define 	__ajit_read_serial_1_baud_limit_register__  	__ajit_read_serial_1_baud_limit_register_via_vmap__
#define     	__ajit_write_serial_1_baud_frequency_register__	__ajit_write_serial_1_baud_frequency_register_via_vmap__
#define 	__ajit_read_serial_1_baud_frequency_register__	__ajit_read_serial_1_baud_frequency_register_via_vmap__
#define	 	__ajit_serial_1_configure__	 __ajit_serial_1_configure_via_vmap__
#define		__ajit_serial_1_set_baudrate__	 __ajit_serial_1_set_baudrate_via_vmap__
#define    	__ajit_serial_1_set_uart_reset__ 	 __ajit_serial_1_set_uart_reset_via_vmap__
#define 	__ajit_serial_1_putchar__  	__ajit_serial_1_putchar_via_vmap__
#define		__ajit_serial_1_getchar__ 	__ajit_serial_1_getchar_via_vmap__
#define		__ajit_serial_1_puts__ 		__ajit_serial_1_puts_via_vmap__
#define 	__ajit_serial_1_gets__ 		__ajit_serial_1_gets_via_vmap__
#else
#define 	__ajit_write_serial_1_control_register__ __ajit_write_serial_1_control_register_via_bypass__
#define		__ajit_read_serial_1_control_register__  __ajit_read_serial_1_control_register_via_bypass__
#define 	__ajit_write_serial_1_tx_register__      __ajit_write_serial_1_tx_register_via_bypass__
#define		__ajit_read_serial_1_tx_register__       __ajit_read_serial_1_tx_register_via_bypass__
#define 	__ajit_read_serial_1_rx_register__       __ajit_read_serial_1_rx_register_via_bypass__
#define     	__ajit_write_serial_1_baud_limit_register__ 	__ajit_write_serial_1_baud_limit_register_via_bypass__
#define 	__ajit_read_serial_1_baud_limit_register__  	__ajit_read_serial_1_baud_limit_register_via_bypass__
#define     	__ajit_write_serial_1_baud_frequency_register__	__ajit_write_serial_1_baud_frequency_register_via_bypass__
#define 	__ajit_read_serial_1_baud_frequency_register__	__ajit_read_serial_1_baud_frequency_register_via_bypass__
#define	 	__ajit_serial_1_configure__	 __ajit_serial_1_configure_via_bypass__
#define		__ajit_serial_1_set_baudrate__	 __ajit_serial_1_set_baudrate_via_bypass__
#define    	__ajit_serial_1_set_uart_reset__ 	 __ajit_serial_1_set_uart_reset_via_bypass__
#define 	__ajit_serial_1_putchar__  	__ajit_serial_1_putchar_via_bypass__
#define		__ajit_serial_1_getchar__ 	__ajit_serial_1_getchar_via_bypass__
#define		__ajit_serial_1_puts__ 		__ajit_serial_1_puts_via_bypass__
#define 	__ajit_serial_1_gets__ 		__ajit_serial_1_gets_via_bypass__
#endif
#endif

