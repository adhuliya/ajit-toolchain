#ifndef __device_addresses_h
#define __device_addresses_h
//
// These are mapped statically in the high memory region.
//   We suggest that 0xffff0000 to 0xffffffff be used to map
//   peripherals for now.  That is 64KB.
//
#define ADDR_IO_MIN				0xFFFF0000
#define ADDR_IO_MAX				0xFFFFFFFF



// Devices will be allocated an address chunk of either
//     16/32/256/512/1024/.../1024*1024 bytes

//
//	Scratch-pad memory.
//	This is a zero-initialized 32x32 memory used for
//      bootup, stats across cores etc..
//           1KB of memory allocated to this block
//           (alignment!)
//
#define ADDR_SCRATCH_PAD_MEMORY_MIN 			0xFFFF2c00 
#define ADDR_SCRATCH_PAD_MEMORY_MAX 			0xFFFF2ffc 


//
//	Interrupt controller
//	The multi-core interrupt controller is assigned 32 bytes in the memory map.
//
#define ADDR_INTERRUPT_CONTROLLER_MIN 			0xFFFF3000 // Base address
#define ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER 	0xFFFF3000 
#define ADDR_INTERRUPT_CONTROLLER_MAX 			0xFFFF301c // Base address + 28


//	Timer
//		Each timer is assigned 16 bytes in the memory map.
//		Only register 0 is used.
//	Leave room for 16 timers...
#define ADDR_TIMER_MIN 					0xFFFF3100 // AJIT default-countdown-timer control register (word).
#define ADDR_TIMER_CONTROL_REGISTER 			0xFFFF3100 // AJIT default-countdown-timer control register (word).
#define ADDR_TIMER_MAX 					0xFFFF311c // AJIT default-countdown-timer control register (word).

//
//	Serial
//		Each serial device is assigned 16 bytes in the memory map.
//		Register 0 is the control register.
//		Register 1 is the TX register.
//		Register 2 is the RX register.
//		Leave room for 64 serial devices.
#define ADDR_SERIAL_MIN 				0xFFFF3200 // AJIT default-countdown-timer control register (word).
#define ADDR_SERIAL_CONTROL_REGISTER 			0xFFFF3200 // AJIT default-serial-device control register (word).
// Note: the next two are byte accesses..
#define ADDR_SERIAL_TX_REGISTER      			0xFFFF3204 // AJIT default-serial-device transmit register (byte).
#define ADDR_SERIAL_RX_REGISTER      			0xFFFF3208 // AJIT default-serial-device receive register (byte).
#define ADDR_SERIAL_MAX 				0xFFFF323c // AJIT default-countdown-timer control register (word).

//
//	SPI data registers 16 bytes per SPI master.
//		4 registers allocated per SPI master.
//			(leave room for 16 spi masters).
//
#define ADDR_SPI_MIN		                   	0xFFFF3300 // AJIT default-SPI-master data-register low (word).
#define ADDR_SPI_DATA_REGISTER_LOW                   	0xFFFF3300 // AJIT default-SPI-master data-register low (word).
#define ADDR_SPI_DATA_REGISTER_HIGH                  	0xFFFF3304 // AJIT default-SPI-master data-register high (word).
#define ADDR_SPI_COMMAND_STATUS_REGISTER             	0xFFFF3308 // AJIT default-SPI-command/status register (word).
#define ADDR_SPI_CONFIG_REGISTER                     	0xFFFF330c // AJIT default-SPI-config register (word).
#define ADDR_SPI_MAX		                   	0xFFFF330c // AJIT default-SPI-master data-register low (word).

//
//	GPIO
//	16-bytes allocated.
//
#define ADDR_GPIO_MIN		                     	0xFFFF3400 
#define ADDR_GPIO_DOUT_REGISTER                     	0xFFFF3400 // GPIO DOUT register address (word).
#define ADDR_GPIO_DIN_REGISTER                     	0xFFFF3404 // GPIO DIN register address (word).
#define ADDR_CONFIG_UART_BAUD_CONTROL_REGISTER		0xFFFF3408 // Baud-rate control word for UARTS in the system.
#define ADDR_GPIO_MAX		                     	0xFFFF340c


//
// trace logger 
//      32 bytes allocated to each trace logger.
//
#define ADDR_TRACE_LOGGER_MIN				0xFFFF3500
#define ADDR_TRACE_LOGGER_CONTROL_REGISTER		0xFFFF3500
#define ADDR_TRACE_LOGGER_MIN_ADDR_REGISTER		0xFFFF3504
#define ADDR_TRACE_LOGGER_MAX_ADDR_REGISTER		0xFFFF3508
#define ADDR_TRACE_LOGGER_TRIGGER_REGISTER		0xFFFF350c
#define ADDR_TRACE_LOGGER_SAMPLE_COUNT_REGISTER		0xFFFF3510
#define ADDR_TRACE_LOGGER_MAX				0xFFFF351c

//
// i2c master
//
#define ADDR_I2C_MASTER_MIN				0xFFFF3600
#define ADDR_I2C_MASTER_CONFIG_REGISTER			0xFFFF3600
#define ADDR_I2C_MASTER_COMMAND_REGISTER		0xFFFF3604
#define ADDR_I2C_MASTER_STATUS_REGISTER			0xFFFF3608
#define ADDR_I2C_MASTER_MAX				0xFFFF3608

#endif
