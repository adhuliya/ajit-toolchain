#include <stdint.h>
#include <stdio.h>
#include "ajit_access_routines.h"


//
// initialize all iu gp-registers to 0.
//
inline void __ajit_clear_all_gp_registers__()
{
	//Initialize all registers
	__asm__ __volatile__( "mov %g0, %g1 \n\t "); __asm__ __volatile__( "mov %g0, %g2 \n\t ");
	__asm__ __volatile__( "mov %g0, %g3 \n\t "); __asm__ __volatile__( "mov %g0, %g4 \n\t ");
	__asm__ __volatile__( "mov %g0, %g5 \n\t "); __asm__ __volatile__( "mov %g0, %g6 \n\t ");
	__asm__ __volatile__( "mov %g0, %g7 \n\t ");
	
	__asm__ __volatile__( "mov %g0, %i0 \n\t "); __asm__ __volatile__( "mov %g0, %i1 \n\t ");
	__asm__ __volatile__( "mov %g0, %i2 \n\t "); __asm__ __volatile__( "mov %g0, %i3 \n\t ");
	__asm__ __volatile__( "mov %g0, %i4 \n\t "); __asm__ __volatile__( "mov %g0, %i5 \n\t ");
	__asm__ __volatile__( "mov %g0, %i6 \n\t "); __asm__ __volatile__( "mov %g0, %i7 \n\t ");
	
	__asm__ __volatile__( "mov %g0, %l0 \n\t "); __asm__ __volatile__( "mov %g0, %l1 \n\t ");
	__asm__ __volatile__( "mov %g0, %l2 \n\t "); __asm__ __volatile__( "mov %g0, %l3 \n\t ");
	__asm__ __volatile__( "mov %g0, %l4 \n\t "); __asm__ __volatile__( "mov %g0, %l5 \n\t ");
	__asm__ __volatile__( "mov %g0, %l6 \n\t "); __asm__ __volatile__( "mov %g0, %l7 \n\t ");
	
	__asm__ __volatile__( "mov %g0, %o0 \n\t "); __asm__ __volatile__( "mov %g0, %o1 \n\t ");
	__asm__ __volatile__( "mov %g0, %o2 \n\t "); __asm__ __volatile__( "mov %g0, %o3 \n\t ");
	__asm__ __volatile__( "mov %g0, %o4 \n\t "); __asm__ __volatile__( "mov %g0, %o5 \n\t ");
	__asm__ __volatile__( "mov %g0, %o6 \n\t "); __asm__ __volatile__( "mov %g0, %o7 \n\t ");

	//initialize registers in other windows
	int window=0;
	for(window=0;window<7;window++)
	{
	__asm__ __volatile__( "save\n\t "); 
	
	__asm__ __volatile__( "mov %g0, %l0 \n\t "); __asm__ __volatile__( "mov %g0, %l1 \n\t ");
	__asm__ __volatile__( "mov %g0, %l2 \n\t "); __asm__ __volatile__( "mov %g0, %l3 \n\t ");
	__asm__ __volatile__( "mov %g0, %l4 \n\t "); __asm__ __volatile__( "mov %g0, %l5 \n\t ");
	__asm__ __volatile__( "mov %g0, %l6 \n\t "); __asm__ __volatile__( "mov %g0, %l7 \n\t ");
	
	__asm__ __volatile__( "mov %g0, %o0 \n\t "); __asm__ __volatile__( "mov %g0, %o1 \n\t ");
	__asm__ __volatile__( "mov %g0, %o2 \n\t "); __asm__ __volatile__( "mov %g0, %o3 \n\t ");
	__asm__ __volatile__( "mov %g0, %o4 \n\t "); __asm__ __volatile__( "mov %g0, %o5 \n\t ");
	__asm__ __volatile__( "mov %g0, %o6 \n\t "); __asm__ __volatile__( "mov %g0, %o7 \n\t ");
	
	}
	
	for(window=0;window<7;window++)
	{
		__asm__ __volatile__( "restore\n\t "); 
	}

	
}

//////////////////////////////////////////////////////////////////////////////////////////////
// scratch pad: 32x32 registers..
//////////////////////////////////////////////////////////////////////////////////////////////
uint32_t ajit_read_from_scratch_pad (uint32_t scratch_pad_index)
{
	uint32_t ret_val = 0;
	if(scratch_pad_index < 32)
	{
		uint32_t* base_ptr = (uint32_t*) ADDR_SCRATCH_PAD_MEMORY_MIN;
		ret_val = base_ptr[scratch_pad_index];
	}
	return(ret_val);
}

void ajit_write_to_scratch_pad (uint32_t scratch_pad_index, uint32_t write_value)
{
	if(scratch_pad_index < 32)
	{
		uint32_t* base_ptr = (uint32_t*) ADDR_SCRATCH_PAD_MEMORY_MIN;
		base_ptr[scratch_pad_index] = write_value;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
// i2c master.
//////////////////////////////////////////////////////////////////////////////////////////////
uint32_t ajit_configure_i2c_master (uint32_t clock_frequency, uint32_t i2c_clock_frequency)
{
	uint32_t div_value = ((clock_frequency / i2c_clock_frequency) >> 2);
	*((uint32_t*) ADDR_I2C_MASTER_CONFIG_REGISTER) = div_value;
}

uint32_t ajit_i2c_master_is_ready()
{
	uint32_t status = *((uint32_t*) ADDR_I2C_MASTER_STATUS_REGISTER);
	uint32_t ret_val = ((status & 0x400) != 0);
	return(ret_val);
}

void     ajit_i2c_master_write_command (uint32_t command)
{
	*((uint32_t*) ADDR_I2C_MASTER_COMMAND_REGISTER) = command;
}

uint32_t  ajit_i2c_master_read_status  ()
{
	uint32_t status = *((uint32_t*) ADDR_I2C_MASTER_STATUS_REGISTER);
	return(status);
}

uint8_t  ajit_i2c_master_access_slave_memory_device 
		(uint8_t device_id, uint8_t rwbar, uint8_t addr, uint8_t wdata)
{
	uint8_t ret_val = 0;
	uint32_t status;
	while(1)
	{
		status = *((uint32_t*) ADDR_I2C_MASTER_STATUS_REGISTER);
		if((status & 0x400) != 0)
			break;
	}

	uint32_t cmd = (rwbar << 31) | (3 << 29) | (device_id << 16) | (addr << 8) | wdata;
	*((uint32_t*) ADDR_I2C_MASTER_COMMAND_REGISTER) = cmd;

	if(rwbar)
	{
		while(1)
		{
			status = *((uint32_t*) ADDR_I2C_MASTER_STATUS_REGISTER);
			if((status & 0x400) != 0)
				break;
		}
		ret_val = status & 0xff;
	}

	return(ret_val);
}

//
// This reads the contents of ASR-29.  The four bytes in the
// return value are
//  MSB                     LSB
//  0x52  0x50  <core-id> <thread-id>
//
// If the first two bytes are not as indicated, this feature
// is not supported in the CPU/thread.
//
inline uint32_t __ajit_read_core_thread_id_word__()
{
        uint32_t retval;
        __asm__ __volatile__("rd %%asr29, %0 " :  "=r" (retval) : );
	return(retval);
}


//
// Important thread characteristics!
// 
void ajit_read_thread_descriptor (AjitHwThreadDescriptor* descr)
{
        uint32_t retval;
        __asm__ __volatile__("rd %%asr28, %0 " :  "=r" (retval) : );

	uint8_t tmp = 		(retval >> 30) & 0x3;   		// 31:30
	descr->l1_dcache_size_in_KB = ((tmp == 0x3) ? 32 : ((tmp == 0x2) ? 16 : ((tmp == 1) ? 8 : 4)));

	tmp = (retval >> 28) & 0x3;					// 29:28
	descr->l1_icache_size_in_KB = ((tmp == 0x3) ? 32 : ((tmp == 0x2) ? 16 : ((tmp == 1) ? 8 : 4)));

	descr->log_dcache_associativity = (retval >> 26) & 0x3;		// 27:26
	descr->log_icache_associativity = (retval >> 24) & 0x3;		// 25:24
	descr->l1_dcache_hit_latency = (retval >> 20) & 0xf;		// 23:20
	descr->l1_icache_hit_latency = (retval >> 16) & 0xf;		// 19:16
	descr->log_mmu_l3_tlb_size = (retval >> 12) & 0xf;		// 15:12
	descr->log_mmu_l2_tlb_size = (retval >> 9) & 0x7;		// 11:9
	descr->log_mmu_l1_tlb_size = (retval >> 7) & 0x3;		// 8:7
	descr->log_mmu_l0_tlb_size = (retval >> 5) & 0x3;		// 6:5
	descr->has_noncacheable_bypass_path = (retval >> 2) & 0x1;	// 2
	descr->has_two_threads = (retval >> 1) & 0x1;			// 1
	descr->implements_isa_64 = retval & 0x1;			// 0

}

//
//  returns core-id and thread-id of the current core.
//
void ajit_get_core_and_thread_id(uint8_t* core_id, uint8_t* thread_id)
{
	uint32_t rval = __ajit_read_core_thread_id_word__();
	*core_id = (rval >> 8) & 0xff;
	*thread_id = (rval & 0xff);	
}

//
// cycle_count_register is ASR30 && ASR31
//    (the processor has a 64-bit cycle counter which starts
//      at reset and increments every clock cycle.  The
//      following routines allow you to access the high and
//      low words in the counter).
//
inline uint32_t __ajit_read_cycle_count_register_high__()
{
        uint32_t retval;
        __asm__ __volatile__("rd %%asr30, %0 " :  "=r" (retval) : );
	return(retval);
}

inline uint32_t __ajit_read_cycle_count_register_low__()
{
        uint32_t retval;
        __asm__ __volatile__("rd %%asr31, %0 " :  "=r" (retval) : );
	return(retval);
}

inline uint64_t __ajit_get_clock_time()
{
	uint64_t ret_val;
	uint32_t v_l = __ajit_read_cycle_count_register_low__();
	uint32_t v_h = __ajit_read_cycle_count_register_high__();

	ret_val = v_h;
	ret_val = ret_val << 32;
	ret_val = ret_val | v_l;

	return(ret_val);
}

//
// Assumes that roll-over never happens.
//   I think that is a reasonable assumption.
//   Unless we send something on a deep space
//   probe.
//
void __ajit_sleep__(uint32_t clock_cycles)
{
	uint64_t curr_time = __ajit_get_clock_time();
	uint64_t end_time = curr_time + clock_cycles;

	while(curr_time < end_time)
	{
		curr_time = __ajit_get_clock_time();
	}
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//  MMU related stuff
///////////////////////////////////////////////////////////////////////////////////////////////

#define ASI_MMU_REGISTER 		0x04
#define ASI_MMU_FLUSH_PROBE	 	0x03
#define ASI_FLUSH_I_D_CONTEXT		0x13

//Addresses of MMU registers
#define MMU_REG_CONTROL			0x00000000
#define MMU_REG_CONTEXT_TABLE_PTR	0x00000100
#define MMU_REG_CONTEXT			0x00000200
#define MMU_REG_FSR			0x00000300
#define MMU_REG_FAR			0x00000400


//
// set default mmu cacheable bit to specified value.
//   (Sparc V8 ref manual specifies that when the MMU is
//    disabled, all returned lines to the caches are marked
//    as non-cacheable.  In AJIT, the nature of the cacheability
//    of the returned line is determined by a default-cacheable
//    bit, which is set/cleared by this function) 
//
//
//
//  pass dc_bit = 1 to set the default cacheable bit, 0 to clear it.
//
inline void __ajit_set_mmu_default_cacheable_bit__(uint8_t dc_bit)
{
	uint32_t value = ((dc_bit != 0) ? 0x100 : 0);
	uint32_t addr  = MMU_REG_CONTROL;
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
			     "i"(ASI_MMU_REGISTER) : "memory");
}



//
// store word into mmu register
//
inline void __ajit_store_word_mmu_reg__(uint32_t value, uint32_t addr)
{
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
			     "i"(ASI_MMU_REGISTER) : "memory");
}

inline void __ajit_store_word_mmu_bypass__(uint32_t value, uint32_t addr)
{
	//uint32_t asi = 0x20 | (highest_4_bits_of_phy_addr & 0xf);
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
			     "i"(ASI_MMU_BYPASS) : "memory");
}

inline void __ajit_store_word_to_physical_address__(uint32_t value, uint64_t physical_address)
{
	uint32_t la = physical_address;

	uint64_t ms = (physical_address >> 32) & 0xf;
	uint32_t tms = (ms & 0xf);
	switch(tms)
	{
		// Is there a less ugly way to do this?

		case 0:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(0,la,value);
			break;
		case 1:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(1,la,value);
			break;
		case 2:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(2,la,value);
			break;
		case 3:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(3,la,value);
			break;
		case 4:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(4,la,value);
			break;
		case 5:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(5,la,value);
			break;
		case 6:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(6,la,value);
			break;
		case 7:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(7,la,value);
			break;
		case 8:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(8,la,value);
			break;
		case 9:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(9,la,value);
			break;
		case 10:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(10,la,value);
			break;
		case 11:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(11,la,value);
			break;
		case 12:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(12,la,value);
			break;
		case 13:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(13,la,value);
			break;
		case 14:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(14,la,value);
			break;
		case 15:
			__AJIT_STORE_WORD_MMU_BYPASS_N__(15,la,value);
			break;
		default:
			break;
		
	}
}

inline uint32_t __ajit_load_word_from_physical_address__(uint64_t physical_address)
{
	uint32_t value = 0;
	uint64_t ms = (physical_address >> 32) & 0xf;
	uint32_t la = (physical_address & 0xffffffff);

	uint32_t tms = (ms & 0xf);
	switch(tms)
	{
		// Is there a less ugly way to do this?
		case 0:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(0,la,value);
			break;
		case 1:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(1,la,value);
			break;
		case 2:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(2,la,value);
			break;
		case 3:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(3,la,value);
			break;
		case 4:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(4,la,value);
			break;
		case 5:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(5,la,value);
			break;
		case 6:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(6,la,value);
			break;
		case 7:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(7,la,value);
			break;
		case 8:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(8,la,value);
			break;
		case 9:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(9,la,value);
			break;
		case 10:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(10,la,value);
			break;
		case 11:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(11,la,value);
			break;
		case 12:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(12,la,value);
			break;
		case 13:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(13,la,value);
			break;
		case 14:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(14,la,value);
			break;
		case 15:
			__AJIT_LOAD_WORD_MMU_BYPASS_N__(15,la,value);
			break;
		default:
			break;
		
	}
	return(value);
}




//
// load word from mmu register
//
inline uint32_t __ajit_load_word_mmu_reg__(uint32_t addr)
{
        uint32_t retval;
        __asm__ __volatile__("lda [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(addr), "i"(ASI_MMU_REGISTER));
        return retval;
}


inline uint32_t __ajit_load_word_mmu_bypass__(uint32_t addr)
{
        uint32_t retval;
        __asm__ __volatile__("lda [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(addr), "i"(ASI_MMU_BYPASS));
        return retval;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//  Cache related stuff
///////////////////////////////////////////////////////////////////////////////////////////////

//
// flush icache
// 
inline void __ajit_flush_icache__(void)
{
	__asm__ __volatile__(" flush ");
}


//
// flush_dcache
//
inline void __ajit_flush_dcache__(void)
{
	__asm__ __volatile__("sta %%g0, [%%g0] %0\n\t" : :
			     "i"(ASI_FLUSH_I_D_CONTEXT) : "memory");
}



///////////////////////////////////////////////////////////////////////////////////////////////
//  Built-in peripherals
//     Timer, Serial, Interrupt-controller, Spi-master, Bootrom
///////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------
// Timer
//---------------------------------------------------------------------------------------------
inline void __ajit_write_timer_control_register__(uint32_t val)
{
	uint32_t addr = ADDR_TIMER_CONTROL_REGISTER;
	__ajit_store_word_mmu_bypass__(val,addr);
					
}

inline uint32_t __ajit_read_timer_control_register__()
{
	uint32_t ret_val = __ajit_load_word_mmu_bypass__(ADDR_TIMER_CONTROL_REGISTER);
	return(ret_val);
}

inline void __ajit_write_timer_control_register_via_vmap__(uint32_t val)
{
	*((uint32_t*) ADDR_TIMER_CONTROL_REGISTER) = val;
}

inline uint32_t __ajit_read_timer_control_register_via_vmap__()
{
	uint32_t ret_val = *((uint32_t*)ADDR_TIMER_CONTROL_REGISTER);
	return(ret_val);
}


//---------------------------------------------------------------------------------------------
// Serial
//---------------------------------------------------------------------------------------------
inline void __ajit_write_serial_control_register__(uint32_t val)
{
	uint32_t addr = ADDR_SERIAL_CONTROL_REGISTER;
	__AJIT_STORE_WORD_MMU_BYPASS__(addr,val);
}

inline void __ajit_serial_configure__ (uint8_t enable_tx, uint8_t enable_rx, uint8_t enable_intr)
{
	uint32_t cval = 0;
	__AJIT_READ_SERIAL_CONTROL_REGISTER__(cval);

	if(enable_tx)
	{
		cval = cval | 1;
	}
	else
	{
		cval = cval & (~1);
	}

	if(enable_rx) 
	{
		cval = cval | 2;
	}
	else
	{
		cval = cval & (~2);
	}

	if(enable_intr)
	{
		cval = cval | 4;
	}
	else
	{
		cval = cval & (~4);
	}
	__AJIT_WRITE_SERIAL_CONTROL_REGISTER__(cval);

}

void __ajit_serial_uart_reset__ ()
{
	__ajit_serial_uart_reset_inner__(0);
}

inline void __ajit_serial_set_baudrate__ (uint32_t baud_rate, uint32_t clock_frequency)
{
	__ajit_serial_set_baudrate_inner__ (0, baud_rate, clock_frequency);
}

inline void __ajit_serial_set_baudrate_via_vmap__ (uint32_t baud_rate, uint32_t clock_frequency)
{
	__ajit_serial_set_baudrate_inner__ (1, baud_rate, clock_frequency);
}

//
//  This is no longer used.  But the logic could be useful at some future point.
//  Given the clock freq and baud-rate, this computes the control word (baud-freq, baud-limit)
//  to be used for setting up the specific UART used in AJIT systems as of 2020.
//
// returns 0 on error.
uint32_t calculate_baud_control_word_for_uart (uint32_t baud_rate, uint32_t clock_frequency)
{
	uint32_t ret_val = 0;

	// GCD (clk_freq, 16*baud_rate);	
	uint32_t A = 16*baud_rate; 
	uint32_t B = clock_frequency;

	if((A > 0) && (A < B))
	{
		while(1) {

			uint32_t T = B - ((B/A)*A);
			B = A;
			A = T;

			if(T == 0)
				break;
		}

		// at this point GCD=B.
		uint32_t baud_freq = (16*baud_rate)/B;
		uint32_t baud_limit = (clock_frequency/B)-baud_freq;
		ret_val = ((baud_limit & 0xffff) << 16) | (baud_freq & 0xfff);
	}

	return(ret_val);
}


inline void __ajit_serial_set_baudrate_inner__ (uint8_t use_vmap, uint32_t baud_rate, uint32_t clock_frequency)
{
	uint32_t addr_brcw = ADDR_CONFIG_UART_BAUD_CONTROL_REGISTER;
	uint32_t baud_control_word = calculate_baud_control_word_for_uart (baud_rate, clock_frequency);

	if(use_vmap)
	{
		*((uint32_t*) addr_brcw) = baud_control_word;
	}
	else
	{
		__ajit_store_word_mmu_bypass__(baud_control_word, addr_brcw);
	}
}


inline uint32_t __ajit_read_serial_control_register__()
{
	uint32_t addr = ADDR_SERIAL_CONTROL_REGISTER;
	uint32_t ret_val = 0;
	__AJIT_LOAD_WORD_MMU_BYPASS__(addr, ret_val);
	return(ret_val);
}


inline void __ajit_write_serial_tx_register__(uint8_t val)
{
	uint32_t addr = ADDR_SERIAL_TX_REGISTER;
	__AJIT_STORE_UBYTE_MMU_BYPASS__(addr, val);
}

inline uint8_t __ajit_read_serial_tx_register__()
{
	uint32_t addr = ADDR_SERIAL_TX_REGISTER;
	uint8_t ret_val = 0;
	__AJIT_LOAD_UBYTE_MMU_BYPASS__(addr, ret_val);
	return(ret_val);
}

inline uint8_t __ajit_read_serial_rx_register__()
{
	uint32_t addr = ADDR_SERIAL_RX_REGISTER;
	uint8_t ret_val = 0;
	__AJIT_LOAD_UBYTE_MMU_BYPASS__(addr, ret_val);
	return(ret_val);
}


// returns 0 on failure (either serial is disabled or tx is full).
int __ajit_serial_putchar__(char c)
{
	uint32_t ctrl_reg =0;
	__AJIT_READ_SERIAL_CONTROL_REGISTER__(ctrl_reg);

	int ret_val = 0;
	if(ctrl_reg & TX_ENABLE)
	{	
		if(!(ctrl_reg & TX_FULL))
		{
			__AJIT_WRITE_SERIAL_TX_REGISTER__(c);

			ret_val =  ((int) c);
		}
	}
	return (ret_val);
}

// returns non-zero on success, 0 on failure.
//  (failure : either serial rx is disabled of rx is empty).
int  __ajit_serial_getchar__()
{
	int ret_val = 0;
	uint32_t ctrl_reg = __ajit_read_serial_control_register__();
	if(ctrl_reg & RX_ENABLE)
	{
		if (ctrl_reg & RX_FULL)
		{
			uint32_t rx_val = 0;
			__AJIT_READ_SERIAL_RX_REGISTER__(rx_val); 
			ret_val = (int) rx_val;
		}
	}
	return(ret_val);
}

void  __ajit_serial_puts__ (char* s, uint32_t length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		int rval = 0;
		while(rval == 0)
			rval =  __ajit_serial_putchar__ (s[i]);
	}
}

void  __ajit_serial_gets__ (char* s, uint32_t length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		int rval = 0;
		while(rval == 0)
		  rval = __ajit_serial_getchar__();

		s[i] = rval;
	}
}

void __ajit_write_serial_control_register_via_vmap__(uint32_t val)
{
	*((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER) = val;
}

uint32_t __ajit_read_serial_control_register_via_vmap__()
{
	uint32_t ret_val = *((uint8_t*) ADDR_SERIAL_CONTROL_REGISTER);
	return(ret_val);
}

void __ajit_write_serial_tx_register_via_vmap__(uint8_t val)
{
	*((uint8_t*) ADDR_SERIAL_TX_REGISTER) = val;
}
uint8_t __ajit_read_serial_tx_register_via_vmap__()
{
	uint8_t ret_val = *((uint8_t*) ADDR_SERIAL_TX_REGISTER);
	return(ret_val);
}
uint8_t __ajit_read_serial_rx_register_via_vmap__()
{
	uint8_t ret_val = *((uint8_t*) ADDR_SERIAL_RX_REGISTER);
	return(ret_val);
}


int   __ajit_serial_putchar_via_vmap__  (char c)
{
	uint32_t ctrl_reg =0;
	ctrl_reg = *((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER);
	int ret_val = 0;
	if(ctrl_reg & TX_ENABLE)
	{	
		if(!(ctrl_reg & TX_FULL))
		{
			*((uint8_t*) ADDR_SERIAL_TX_REGISTER) = c;
			ret_val =  ((int) c);
		}
	}
	return (ret_val);
}

int   __ajit_serial_getchar_via_vmap__ ()
{
	int ret_val = 0;
	uint32_t ctrl_reg = *((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER);
	if(ctrl_reg & RX_ENABLE)
	{
		if (ctrl_reg & RX_FULL)
		{
			uint32_t rx_val = 0;
			rx_val = *((uint8_t*) ADDR_SERIAL_RX_REGISTER);
			ret_val = (int) rx_val;
		}
	}
	return(ret_val);
}

void  __ajit_serial_puts_via_vmap__ (char* s, uint32_t length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		int rval = 0;
		while(rval == 0)
			rval =  __ajit_serial_putchar_via_vmap__ (s[i]);
	}
}
void  __ajit_serial_gets_via_vmap__ (char* s, uint32_t length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		int rval = 0;
		while(rval == 0)
		  rval = __ajit_serial_getchar_via_vmap__();

		s[i] = rval;
	}
}

void  __ajit_serial_configure_via_vmap__ (uint8_t enable_tx, uint8_t enable_rx, uint8_t enable_intr)
{
	uint32_t cval = *((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER);


	if(enable_tx)
	{
		cval = cval | 1;
	}
	else
	{
		cval = cval & (~1);
	}

	if(enable_rx) 
	{
		cval = cval | 2;
	}
	else
	{
		cval = cval & (~2);
	}

	if(enable_intr)
	{
		cval = cval | 4;
	}
	else
	{
		cval = cval & (~4);
	}
	*((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER) = cval;
}

void __ajit_serial_uart_reset_via_vmap__ ()
{
	__ajit_serial_uart_reset_inner__(1);
}

void __ajit_serial_uart_reset_inner__ (uint8_t use_vmap)
{
	// read old value of control register.
	uint32_t old_ctrl_register;
	uint32_t reset_val = (1 << 3); 
	if(use_vmap)
	{
		old_ctrl_register = __ajit_read_serial_control_register_via_vmap__();
		__ajit_write_serial_control_register_via_vmap__ (reset_val);
		__ajit_write_serial_control_register_via_vmap__ (old_ctrl_register);
	}
	else
	{
		old_ctrl_register = __ajit_read_serial_control_register__();
		__ajit_write_serial_control_register__ (reset_val);
		__ajit_write_serial_control_register__ (old_ctrl_register);
	}
}

//---------------------------------------------------------------------------------------------
// Interrupt-controller.
//---------------------------------------------------------------------------------------------
inline void __ajit_write_irc_control_register__(uint32_t val)
{
	uint32_t addr = ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER;
	__ajit_store_word_mmu_bypass__(val, addr);
}

inline uint32_t __ajit_read_irc_control_register__()
{
	uint32_t addr = ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER;
	uint32_t ret_val = __ajit_load_word_mmu_bypass__(addr);
	return(ret_val);
}

inline void __ajit_write_irc_control_register_via_vmap__(uint32_t val)
{
	*((uint32_t*) ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER) = val;
}

inline uint32_t __ajit_read_irc_control_register_via_vmap__()
{
	uint32_t ret_val = *((uint32_t*)ADDR_INTERRUPT_CONTROLLER_CONTROL_REGISTER);
	return(ret_val);
}


//---------------------------------------------------------------------------------------------
// Spi-master
//---------------------------------------------------------------------------------------------

//
// reg-id can be
//   0   data-reg-low
//   1   data-reg-high
//
//       These two registers (high concatenated with low) form a shift
//       register [15:0].  The MOSI output is either from bit 3/7/11/15 of
//       the 16-bit shifter register, depending on the transfer length 
//       set in the configure register (see below).
//
//   2   command (for write)/status (for read)
//
//       Command register format
//           unused spi-dev-addr  irq-en deselect-after-xfer  start-transfer
//              2        3             1             1             1
//   3   configure register
//   
//   	 Format
//   	   transfer_length clk_divide_count
//   	        2               4
//        The AJIT cpu clock is divided by using clk_divide_count: 
//               the clock-division is by (2**(clk_divide_count+1))
//        The transfer length ranges from 00-11 (4/8/12/16 bits)
//
inline void     __ajit_write_spi_master_register__(uint8_t reg_id, uint8_t reg_val)
{
	uint32_t addr = ADDR_SPI_DATA_REGISTER_LOW + (reg_id*4);
	__ajit_store_word_mmu_bypass__(reg_val, addr);
}

inline void     __ajit_write_spi_master_register_via_vmap__(uint8_t reg_id, uint8_t reg_val)
{
	uint32_t addr = ADDR_SPI_DATA_REGISTER_LOW + (reg_id*4);

	// NOTE: byte write.
	*((uint8_t*)addr) = reg_val;
}



// 
// use this to read the data-registers, status (command) register
// or the config register
//
// A status reg read returns 1 if the master is busy with the
// previous transfer and 0 else.
//
inline uint8_t  __ajit_read_spi_master_register__(uint8_t reg_id)
{
	uint32_t addr = ADDR_SPI_DATA_REGISTER_LOW + (reg_id*4);
	uint32_t ret_val = __ajit_load_word_mmu_bypass__(addr);
	return(ret_val);
}

inline uint8_t  __ajit_read_spi_master_register_via_vmap__(uint8_t reg_id)
{
	uint32_t addr = ADDR_SPI_DATA_REGISTER_LOW + (reg_id*4);

	// NOTE: byte read.
	uint32_t ret_val = *((uint8_t*) addr);

	return(ret_val);
}


//---------------------------------------------------------------------------------------------
// GPIO!
//---------------------------------------------------------------------------------------------
// write gpio-out to GPIO_OUT pins and read back GPIO_IN pins.
inline uint32_t __ajit_gpio_xfer__(uint8_t gpio_out)
{
	
	int retry_limit;

	uint32_t ret_val = 0;
	uint32_t status_reg = 1;

	// write data-l in master.
	__ajit_write_spi_master_register__(0, gpio_out);

	// master-command
	// spi-dev-id = 1, deselect = 1, start-xfer = 1.
	uint8_t cmd_to_master = ((1 << 4) | 0x3);

	// write master-command
	__ajit_write_spi_master_register__(2, cmd_to_master);

	// check status-reg..
	retry_limit = 256;
	while(status_reg & (retry_limit > 0))
	{
		status_reg = __ajit_read_spi_master_register__(2);
		retry_limit--;
	}

	// read back data-l
	ret_val = __ajit_read_spi_master_register__(0);
	return(ret_val);
}

inline uint32_t __ajit_gpio_xfer_via_vmap__(uint8_t gpio_out)
{
	
	int retry_limit;

	uint32_t ret_val = 0;
	uint32_t status_reg = 1;

	// write data-l in master.
	__ajit_write_spi_master_register_via_vmap__(0, gpio_out);

	// master-command
	// spi-dev-id = 1, deselect = 1, start-xfer = 1.
	uint8_t cmd_to_master = ((1 << 4) | 0x3);

	// write master-command
	__ajit_write_spi_master_register_via_vmap__(2, cmd_to_master);

	// check status-reg..
	retry_limit = 256;
	while(status_reg & (retry_limit > 0))
	{
		status_reg = __ajit_read_spi_master_register_via_vmap__(2);
		retry_limit--;
	}

	// read back data-l
	ret_val = __ajit_read_spi_master_register_via_vmap__(0);
	return(ret_val);
}

inline void __ajit_ta_0__ ()
{
	__asm__ __volatile__("ta 0; nop; nop;");
}

inline void __ajit_fsqrtd__ (uint32_t a, uint32_t b)
{
        __asm__ __volatile__ ( "ldd [%0], %%f0; fsqrtd %%f0, %%f2; std %%f2, [%1];" : : "r" (a), "r" (b):);
}

inline void __ajit_fsqrts__ (uint32_t a, uint32_t b)
{
        __asm__ __volatile__ ( "ld [%0], %%f0; fsqrts %%f0, %%f1; st %%f1, [%1];" : : "r" (a), "r" (b):);
}

inline void __ajit_fitod__ (uint32_t a, uint32_t b)
{
        __asm__ __volatile__ ( "ld [%0], %%f0; fitod %%f0, %%f2; std %%f2, [%1];" : : "r" (a), "r" (b):);
}

inline void __ajit_fitos__ (uint32_t a, uint32_t b)
{
        __asm__ __volatile__ ( "ld [%0], %%f0; fitos %%f0, %%f1; st %%f1, [%1];" : : "r" (a), "r" (b):);
}

inline void __ajit_fdtoi__ (uint32_t a, uint32_t b)
{
        __asm__ __volatile__ ( "ldd [%0], %%f0; fdtoi %%f0, %%f2; st %%f2, [%1];" : : "r" (a), "r" (b):);
}

inline void __ajit_fstoi__ (uint32_t a, uint32_t b)
{
        __asm__ __volatile__ ( "ld [%0], %%f0; fstoi %%f0, %%f1; st %%f1, [%1];" : : "r" (a), "r" (b):);
}
