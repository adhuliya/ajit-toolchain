#ifndef __alternate_device_addresses_h
#define __alternate_device_addresses_h

#define NMI_IRL		15
#define GNSS_IRL	14
#define SERIAL_IRL	12
#define TIMER_IRL       10
#define GNSS_AUX_0_IRL   9
#define GNSS_AUX_1_IRL   8
#define GNSS_AUX_2_IRL   7
#define GNSS_AUX_3_IRL   6

//
//
//    For SAC system.
//
//  TODO: need to figure out a good way to manage the device
//        peripheral addresses...  device tree?
//
#define ADDR_IO_MIN				0x80000000
#define ADDR_IO_MAX				(ADDR_IO_MIN + 0xffff)



// Devices will be allocated an address chunk of either
//     16/32/256/512/1024/.../1024*1024 bytes

//
//	Scratch-pad memory.
//	This is a zero-initialized 32x32 memory used for
//      bootup, stats across cores etc..
//           1KB of memory allocated to this block
//           (alignment!)
//
#define ADDR_SCRATCH_PAD_MEMORY_MIN 			(ADDR_IO_MIN  + 0x1000) 
#define ADDR_SCRATCH_PAD_MEMORY_MAX 			((ADDR_IO_MIN + 0x1000 + 0x400) - 0x1) 


//
//	Interrupt controller
//	The multi-core interrupt controller is assigned 32 bytes in the memory map.
//
#define ADDR_INTERRUPT_CONTROLLER_MIN 			(ADDR_IO_MIN + 0x200) // Base address
#define ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER 	(ADDR_IO_MIN + 0x200) 
#define ADDR_INTERRUPT_CONTROLLER_IPI_BASE              (ADDR_IO_MIN + 0x280) // IPI uses 76 bytes for now..
								   // offset-from-base    register
								   //   0                 ipi-intr-mask
								   //   4                 ipi-intr-vals
								   //   8 - 68            ipi-message-per-dest-cpu
								   //                         8 bytes each
								   //   76                ipi-lock
#define ADDR_INTERRUPT_CONTROLLER_MAX 			(ADDR_IO_MIN + 0x2ff) 


//	Timer
//		Each timer is assigned 16 bytes in the memory map.
//		Only register 0 is used.
//	Leave room for 16 timers...
#define ADDR_TIMER_MIN 					(ADDR_IO_MIN + 0x300) // AJIT default-countdown-timer control register (word).
#define ADDR_TIMER_CONTROL_REGISTER 			(ADDR_IO_MIN + 0x300) // AJIT default-countdown-timer control register (word).
#define ADDR_TIMER_MAX 					(ADDR_IO_MIN + 0x31c) // AJIT default-countdown-timer control register (word).

//
//	Serial
//		Each serial device is assigned 16 bytes in the memory map.
//		Register 0 is the control register.
//		Register 1 is the TX register.
//		Register 2 is the RX register.
//		Leave room for 64 serial devices.
#define ADDR_SERIAL_MIN 				(ADDR_IO_MIN + 0x100) // AJIT default-countdown-timer control register (word).
#define ADDR_SERIAL_CONTROL_REGISTER 			(ADDR_IO_MIN + 0x100) // AJIT default-serial-device control register (word).
// Note: the next two are byte accesses..
#define ADDR_SERIAL_TX_REGISTER      			(ADDR_IO_MIN + 0x104) // AJIT default-serial-device transmit register (byte).
#define ADDR_SERIAL_RX_REGISTER      			(ADDR_IO_MIN + 0x108) // AJIT default-serial-device receive register (byte).
#define ADDR_SERIAL_BAUD_CONTROL_REGISTER		(ADDR_IO_MIN + 0x10c) // AJIT default-serial-device control register
#define ADDR_SERIAL_BAUD_LIMIT_REGISTER			(ADDR_IO_MIN + 0x10c) //  baud-limit
#define ADDR_SERIAL_BAUD_FREQUENCY_REGISTER		(ADDR_IO_MIN + 0x110) //  baud-control
#define ADDR_SERIAL_MAX 				(ADDR_IO_MIN + 0x113) // Max serial address.

// second serial device
#define ADDR_SERIAL_1_MIN 				(ADDR_IO_MIN + 0x900) // AJIT default-countdown-timer control register (word).
#define ADDR_SERIAL_1_CONTROL_REGISTER 			(ADDR_IO_MIN + 0x900) // AJIT default-serial-device control register (word).
// Note: the next two are byte accesses..
#define ADDR_SERIAL_1_TX_REGISTER      			(ADDR_IO_MIN + 0x904) // AJIT default-serial-device transmit register (byte).
#define ADDR_SERIAL_1_RX_REGISTER      			(ADDR_IO_MIN + 0x908) // AJIT default-serial-device receive register (byte).
#define ADDR_SERIAL_1_BAUD_CONTROL_REGISTER		(ADDR_IO_MIN + 0x90c) // AJIT default-serial-device control register
#define ADDR_SERIAL_1_BAUD_LIMIT_REGISTER		(ADDR_IO_MIN + 0x90c) // baud-limit
#define ADDR_SERIAL_1_BAUD_FREQUENCY_REGISTER		(ADDR_IO_MIN + 0x910) // baud-frequency
#define ADDR_SERIAL_1_MAX 				(ADDR_IO_MIN + 0x213) // AJIT default-countdown-timer control register (word).

//
//	SPI data registers 16 bytes per SPI master.
//		4 registers allocated per SPI master.
//			(leave room for 16 spi masters).
//
#define ADDR_SPI_MIN		                   	(ADDR_IO_MIN + 0xe00) // AJIT default-SPI-master data-register low (word).
#define ADDR_SPI_DATA_REGISTER_LOW                   	(ADDR_IO_MIN + 0xe00) // AJIT default-SPI-master data-register low (word).
#define ADDR_SPI_DATA_REGISTER_HIGH                  	(ADDR_IO_MIN + 0xe04) // AJIT default-SPI-master data-register high (word).
#define ADDR_SPI_COMMAND_STATUS_REGISTER             	(ADDR_IO_MIN + 0xe08) // AJIT default-SPI-command/status register (word).
#define ADDR_SPI_CONFIG_REGISTER                     	(ADDR_IO_MIN + 0xe0c) // AJIT default-SPI-config register (word).
#define ADDR_SPI_MAX		                   	(ADDR_IO_MIN + 0xe0f) // AJIT default-SPI-master data-register low (word).

// SPI Flash controller can be programmed using
// these registers..
#define ADDR_SPI_FLASH_PROGRAMMING_ADDR_MIN		(ADDR_IO_MIN + 0xf00)
#define ADDR_SPI_FLASH_PROGRAMMING_DATA_REG_LOW_ADDR	(ADDR_IO_MIN + 0xf00)
#define ADDR_SPI_FLASH_PROGRAMMING_DATA_REG_HIGH_ADDR	(ADDR_IO_MIN + 0xf04)
#define ADDR_SPI_FLASH_PROGRAMMING_COMMAND_STATUS_REG_ADDR	(ADDR_IO_MIN + 0xf08)
#define ADDR_SPI_FLASH_PROGRAMMING_CONFIG_REG_ADDR	(ADDR_IO_MIN + 0xf0c)
#define ADDR_SPI_FLASH_PROGRAMMING_ADDR_MAX		(ADDR_IO_MIN + 0xfff)


//
//	GPIO
//	16-bytes allocated.
//
#define ADDR_GPIO_MIN		                     	(ADDR_IO_MIN + 0xa00) 
#define ADDR_GPIO_DOUT_REGISTER                     	(ADDR_IO_MIN + 0xa00) // GPIO DOUT register address (word).
#define ADDR_GPIO_DIN_REGISTER                     	(ADDR_IO_MIN + 0xa04) // GPIO DIN register address (word).
#define ADDR_GPIO_DOUT_ENABLE_REGISTER			(ADDR_IO_MIN + 0xa08) // GPIO_DOUT_ENABLE  (word)
#define ADDR_GPIO_MAX		                     	(ADDR_IO_MIN + 0xa0b)


//
// trace logger 
//      32 bytes allocated to each trace logger.
//
#define ADDR_TRACE_LOGGER_MIN				(ADDR_IO_MIN + 0x500)
#define ADDR_TRACE_LOGGER_CONTROL_REGISTER		(ADDR_IO_MIN + 0x500)
#define ADDR_TRACE_LOGGER_MIN_ADDR_REGISTER		(ADDR_IO_MIN + 0x504)
#define ADDR_TRACE_LOGGER_MAX_ADDR_REGISTER		(ADDR_IO_MIN + 0x508)
#define ADDR_TRACE_LOGGER_TRIGGER_REGISTER		(ADDR_IO_MIN + 0x50c)
#define ADDR_TRACE_LOGGER_SAMPLE_COUNT_REGISTER		(ADDR_IO_MIN + 0x510)
#define ADDR_TRACE_LOGGER_MAX				(ADDR_IO_MIN + 0x51c)

//
// i2c master
//
#define ADDR_I2C_MASTER_MIN				(ADDR_IO_MIN + 0xb00)
#define ADDR_I2C_MASTER_CONFIG_REGISTER			(ADDR_IO_MIN + 0xb00)
#define ADDR_I2C_MASTER_COMMAND_REGISTER		(ADDR_IO_MIN + 0xb04)
#define ADDR_I2C_MASTER_STATUS_REGISTER			(ADDR_IO_MIN + 0xb08)
#define ADDR_I2C_MASTER_MAX				(ADDR_IO_MIN + 0xb0b)

// spi slave (a 256 B memory)
#define ADDR_SPI_SLAVE_MIN	 			(ADDR_IO_MIN  + 0x1400) 
#define ADDR_SPI_SLAVE_MAX 	 			((ADDR_IO_MIN + 0x1400 + 0x100) - 0x1) 

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
#define ADDR_PERF_COUNTERS_MIN				(ADDR_IO_MIN + 0x2000)
#define ADDR_PERF_COUNTERS_MAX				(ADDR_IO_MIN + 0x2FFF)

#endif
