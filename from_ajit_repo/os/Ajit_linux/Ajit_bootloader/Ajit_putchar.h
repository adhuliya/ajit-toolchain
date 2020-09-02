//Ajit_putchar.h

#ifndef AJIT_PUTCHAR_H
#define AJIT_PUTCHAR_H

#include "Ajit_Device_Addresses.h"
#include<stdint.h>
//an implementation of putchar that uses the serial device.
//NOTE: the serial device's addresses have to be in sync 
//with those used by the processor model
//(specified in  Ajit_Hardware_Configuration.h)


#define ASI_MMU_BYPASS 0x20

//mmu-bypass load
static inline uint32_t  __attribute__((optimize("O0")))mmu_bypass_load(uint32_t* addr)
{
        uint32_t retval;
        __asm__ __volatile__("lda [%1] %2, %0\n\t" : "=r"(retval) : "r"(addr), "i"(ASI_MMU_BYPASS));
        return retval;
}

//mmu-bypass load byte
static inline uint8_t  __attribute__((optimize("O0")))mmu_bypass_load_byte(uint32_t* addr)
{
        uint8_t retval;
        __asm__ __volatile__("lduba [%1] %2, %0\n\t" : "=r"(retval) : "r"(addr), "i"(ASI_MMU_BYPASS));
        return retval;
}

//mmu-bypass store
static inline void __attribute__((optimize("O0")))mmu_bypass_store(uint32_t value, uint32_t* addr)
{
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
			     "i"(ASI_MMU_BYPASS) : "memory");
}

//mmu-bypass store-byte
static inline void __attribute__((optimize("O0")))mmu_bypass_store_byte(uint8_t value, uint32_t* addr)
{
	__asm__ __volatile__("stuba %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
			     "i"(ASI_MMU_BYPASS) : "memory");
}



static inline void  __attribute__((optimize("O0")))enableTx(void)
{
	//read the serial device's control register 
	//(use mmu bypassing)
	uint32_t control_word = mmu_bypass_load((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER);
	//set Tx_enable bit (bit 0)
	control_word = control_word | 0x00000001;
	//write the control word
	mmu_bypass_store(control_word, (uint32_t*)ADDR_SERIAL_CONTROL_REGISTER);
}



static inline void  __attribute__((optimize("O0")))writetoTx(char c)
{
	//write a character into the Tx register
	mmu_bypass_store_byte(c, (uint32_t*)ADDR_SERIAL_TX_REGISTER);
}
	

//return the value of Tx_full bit
static inline uint8_t  __attribute__((optimize("O0"))) getTxfull(void)
{
	//read the serial device's control register 
	//(use mmu bypassing)
	uint32_t control_word = mmu_bypass_load((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER);
	//read the Tx_full bit (bit 3)
	control_word = control_word & 0x00000008;
	if(control_word) return 1;
	else return 0;
}

static int inline  __attribute__((optimize("O0"))) pv_nbputchar(int ch)
{
	enableTx();
	//write a character into Tx register
	writetoTx((char)ch);
	
	//wait until Tx_full=0
	while(1)
	{
		if(getTxfull()==0)
			break;
	}
	return 1;
}

static int inline __attribute__((optimize("O0"))) ajit_putstring(const char* ch)
{
	int i=0;
	while(1)
	{
		pv_nbputchar(*(ch+i));
		if(*(ch+i) =='\0') break;
		i++;
	}
	return 0;
}

		
#endif
