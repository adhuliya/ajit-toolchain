// Common routines for all serial-device tests
// Author: Neha Karanjkar

#ifndef COMMON_SERIAL_ROUTINES_H
#define COMMON_SERIAL_ROUTINES_H

#include<stdint.h>
#include"Ajit_Hardware_Configuration.h"



//mmu-bypass load
uint32_t mmu_bypass_load(uint32_t* addr);

//mmu-bypass load byte
uint8_t mmu_bypass_load_byte(uint32_t* addr);
//mmu-bypass store
void mmu_bypass_store(uint32_t value, uint32_t* addr);
//mmu-bypass store-byte
void mmu_bypass_store_byte(uint8_t value, uint32_t* addr);


void enableTx();

void enableRx();

void enableRxWithInterrupts();


void writetoTx(uint8_t c);

	
uint8_t readFromRx();


//return the value of Tx_full bit
uint8_t getTxfull();

//return the value of Rx_full bit
uint8_t getRxfull();


void sendAChar(char c);

void sendAString(char* s);


char getAChar();


uint32_t getAUint();
void sendAUint(uint32_t u);

#endif
