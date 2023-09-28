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
#define ADDR_INTERRUPT_CONTROLLER_IPI_BASE              0xFFFF3080 // IPI uses 76 bytes for now..
								   // offset-from-base    register
								   //   0                 ipi-intr-mask
								   //   4                 ipi-intr-vals
								   //   8 - 68            ipi-message-per-dest-cpu
								   //                         8 bytes each
								   //   76                ipi-lock
#define ADDR_INTERRUPT_CONTROLLER_MAX 			0xFFFF30FF 


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
#define ADDR_SERIAL_BAUD_CONTROL_REGISTER		0xFFFF320c // AJIT default-serial-device control register
#define ADDR_SERIAL_BAUD_LIMIT_REGISTER			0xFFFF320c //  baud-limit
#define ADDR_SERIAL_BAUD_FREQUENCY_REGISTER		0xFFFF3210 //  baud-control
#define ADDR_SERIAL_MAX 				0xFFFF3213 // Max serial address.

// second serial device
#define ADDR_SERIAL_1_MIN 				0xFFFF3240 // AJIT default-countdown-timer control register (word).
#define ADDR_SERIAL_1_CONTROL_REGISTER 			0xFFFF3240 // AJIT default-serial-device control register (word).
// Note: the next two are byte accesses..
#define ADDR_SERIAL_1_TX_REGISTER      			0xFFFF3244 // AJIT default-serial-device transmit register (byte).
#define ADDR_SERIAL_1_RX_REGISTER      			0xFFFF3248 // AJIT default-serial-device receive register (byte).
#define ADDR_SERIAL_1_BAUD_CONTROL_REGISTER		0xFFFF324c // AJIT default-serial-device control register
#define ADDR_SERIAL_1_BAUD_LIMIT_REGISTER		0xFFFF324c // baud-limit
#define ADDR_SERIAL_1_BAUD_FREQUENCY_REGISTER		0xFFFF3250 // baud-frequency
#define ADDR_SERIAL_1_MAX 				0xFFFF3253 // AJIT default-countdown-timer control register (word).

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

// performance counters..
//
// We keep 256 bytes per thread, and there 
// are 8-threads supported for now.
// 
// The performance counters are 64-bit values
// which are described below.
//
// Thread-wise address allocation is as follows:
// base to base + 255 is for thread 00
// base+256 to base+511 is for thread 01
//  etc. for threads 10 11 20 21 30 31
//
// Within each set of counters word addresses
// are used to access the registers.
// reg-addr    register
//  0          executed-instr-count [63:32]
//  4          executed-instr-count [31:0]
//  8          skipped-instr-count  [63:32]
//  12         skipped-instr-count  [31:0]
//  16         load-count           [63:32]
//  20         load-count           [31:0]
//  24         load-miss-count      [63:32]
//  28         load-miss-count      [31:0]
//  32         store-count          [63:32]
//  36         store-count          [31:0]
//  40         store-miss-count     [63:32]
//  44         store-miss-count     [31:0]
//  48         cti-mispredict-count [63:32]
//  52         cti-mispredict-count [31:0]
//  56         trap-count           [63:32]
//  60         trap-count           [31:0]
//  64         icache-access-count  [63:32]
//  68         icache-access-count  [31:0]
//  72         icache-miss-count    [63:32]
//  76         icache-miss-count    [31:0]
//  rest up to 255 unused for now.
#define ADDR_PERF_COUNTERS_MIN				0xFFFF4000
#define ADDR_PERF_COUNTERS_MAX				0xFFFF47FF

#endif
