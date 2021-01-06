// Common routines for all serial-device tests
// Author: Neha Karanjkar

#include"sparc_stdio.h"
#include<stdint.h>
#include"Ajit_Hardware_Configuration.h"
#include"CommonSerialRoutines.h"



//mmu-bypass load
uint32_t mmu_bypass_load(uint32_t* addr)
{
        uint32_t retval;
        __asm__ __volatile__("lda [%1] %2, %0\n\t" : "=r"(retval) : "r"(addr), "i"(AJIT_ASI_MMU_BYPASS));
        return retval;
}

//mmu-bypass load byte
uint8_t mmu_bypass_load_byte(uint32_t* addr)
{
        uint8_t retval;
        __asm__ __volatile__("lduba [%1] %2, %0\n\t" : "=r"(retval) : "r"(addr), "i"(AJIT_ASI_MMU_BYPASS));
        return retval;
}

//mmu-bypass store
void mmu_bypass_store(uint32_t value, uint32_t* addr)
{
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
			     "i"(AJIT_ASI_MMU_BYPASS) : "memory");
}

//mmu-bypass store-byte
void mmu_bypass_store_byte(uint8_t value, uint32_t* addr)
{
	__asm__ __volatile__("stuba %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
			     "i"(AJIT_ASI_MMU_BYPASS) : "memory");
}



void enableTx()
{
	//read the serial device's control register 
	//(use mmu bypassing)
	uint32_t control_word = mmu_bypass_load((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER);
	//set Tx_enable bit (bit 0)
	control_word = control_word | 0x00000001;
	//write the control word
	mmu_bypass_store(control_word, (uint32_t*)ADDR_SERIAL_CONTROL_REGISTER);
}

void enableRx()
{
	//read the serial device's control register 
	//(use mmu bypassing)
	uint32_t control_word = mmu_bypass_load((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER);
	//set Rx_enable bit (bit 1)
	control_word = control_word | 0x00000002;
	//write the control word
	mmu_bypass_store(control_word, (uint32_t*)ADDR_SERIAL_CONTROL_REGISTER);
}

void enableRxWithInterrupts()
{
	//read the serial device's control register 
	//(use mmu bypassing)
	uint32_t control_word = mmu_bypass_load((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER);
	//set Rx_enable bit (bit 1) and Rx_int_enable bit (bit2)
	control_word = control_word | 0x00000006;
	//write the control word
	mmu_bypass_store(control_word, (uint32_t*)ADDR_SERIAL_CONTROL_REGISTER);
}


void writetoTx(uint8_t c)
{
	//write a character into the Tx register
	mmu_bypass_store_byte(c, (uint32_t*)ADDR_SERIAL_TX_REGISTER);
}
	
uint8_t readFromRx()
{
	uint8_t c;
	//read a byte from Rx register
	c=mmu_bypass_load_byte((uint32_t*)ADDR_SERIAL_RX_REGISTER);
	return c;
}

//return the value of Tx_full bit
uint8_t getTxfull()
{
	//read the serial device's control register 
	//(use mmu bypassing)
	uint32_t control_word = mmu_bypass_load((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER);
	//read the Tx_full bit (bit 3)
	control_word = control_word & 0x00000008;
	if(control_word) return 1;
	else return 0;
}

//return the value of Rx_full bit
uint8_t getRxfull()
{
	//read the serial device's control register 
	//(use mmu bypassing)
	uint32_t control_word = mmu_bypass_load((uint32_t*) ADDR_SERIAL_CONTROL_REGISTER);
	//read the Rx_full bit (bit 4)
	control_word = control_word & 0x00000010;
	if(control_word) return 1;
	else return 0;
}




void sendAChar(char c)
{
	uint8_t n = *((uint8_t*)&c); //interpret as uint8_t
	
	//write a character into Tx register
	writetoTx(n);
	
	//wait until Tx_full=0
	while(1)
	{
		if(getTxfull()==0)
			break;
	}
}


void sendAString(char* s)
{
	while(*s!='\0')
	{
		sendAChar(s[0]);
		s++;
	}
}


char getAChar()
{
	uint8_t n;
	char c;
	

	//wait until Rx_full==1
	while(1)
	{
		if(getRxfull()) break;
	}

	//read the Rx register
	n = readFromRx();
	//interpret as char
	c = *((char*)&n);
	//return the character read from Rx
	return (char)c;
}



uint32_t getAUint()
{
	uint8_t c0 = getAChar();
	uint8_t c1 = getAChar();
	uint8_t c2 = getAChar();
	uint8_t c3 = getAChar();
	uint32_t ret_val = c0;
	ret_val = (ret_val << 8) | c1;
	ret_val = (ret_val << 8) | c2;
	ret_val = (ret_val << 8) | c3;
	
	return(ret_val);
}

void sendAUint(uint32_t u)
{
	uint8_t c3 = u & 0xff;
	uint8_t c2 = (u >> 8) & 0xff;
	uint8_t c1 = (u >> 16) & 0xff;
	uint8_t c0 = (u >> 24) & 0xff;

	sendAChar(c0);
	sendAChar(c1);
	sendAChar(c2);
	sendAChar(c3);
}

