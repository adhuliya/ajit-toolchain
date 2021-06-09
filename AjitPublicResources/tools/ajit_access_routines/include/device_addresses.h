#ifndef device_addresses_h___
#define device_addresses_h___

//
// These are mapped statically in the high memory region.
//   We suggest that 0xffff0000 to 0xffffffff be used to map
//   peripherals.
//
#define ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER 	0xFFFF3000 // AJIT default-interrupt-controller control register (word).
#define ADDR_TIMER_CONTROL_REGISTER 			0xFFFF3100 // AJIT default-countdown-timer control register (word).
#define ADDR_SERIAL_CONTROL_REGISTER 			0xFFFF3200 // AJIT default-serial-device control register (word).
// Note: the next two are byte accesses..
#define ADDR_SERIAL_TX_REGISTER      			0xFFFF3210 // AJIT default-serial-device transmit register (byte).
#define ADDR_SERIAL_RX_REGISTER      			0xFFFF3220 // AJIT default-serial-device receive register (byte).
#define ADDR_SPI_DATA_REGISTER_LOW                   	0xFFFF3300 // AJIT default-SPI-master data-register low (word).
#define ADDR_SPI_DATA_REGISTER_HIGH                  	0xFFFF3304 // AJIT default-SPI-master data-register high (word).
#define ADDR_SPI_COMMAND_STATUS_REGISTER             	0xFFFF3308 // AJIT default-SPI-command/status register (word).
#define ADDR_SPI_CONFIG_REGISTER                     	0xFFFF330c // AJIT default-SPI-config register (word).

#define ADDR_GPIO_DOUT_REGISTER                     	0xFFFF3400 // GPIO DOUT register address (word).
#define ADDR_GPIO_DIN_REGISTER                     	0xFFFF3404 // GPIO DIN register address (word).

#define ADDR_CONFIG_UART_BAUD_CONTROL_REGISTER		0xFFFF3408 // Baud-rate control word for UARTS in the system.


//
// trace logger peripheral added
//
#define ADDR_TRACE_LOGGER_CONTROL_REGISTER		0xFFFF3410
#define ADDR_TRACE_LOGGER_MIN_ADDR_REGISTER		0xFFFF3414
#define ADDR_TRACE_LOGGER_MAX_ADDR_REGISTER		0xFFFF3418
#define ADDR_TRACE_LOGGER_TRIGGER_REGISTER		0xFFFF341c
#define ADDR_TRACE_LOGGER_SAMPLE_COUNT_REGISTER		0xFFFF3420


#endif
