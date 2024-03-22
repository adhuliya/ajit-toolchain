#ifndef _TlbNew_h___
#define _TlbNew_h___
#include <stdint.h>
#include "Mmu.h"
#include "tlbs.h"

#define TLB0_SIZE 2
#define TLB1_SIZE 8
#define TLB2_SIZE 16
#define TLB3_SIZE 64

void initializeTlbNew(MmuState* ms);
void writeTlbNewEntry(MmuState* ms, 
			int thread_id,
			uint32_t virtual_addr,
			uint32_t va_tag, uint32_t pte, uint8_t pte_level);
uint8_t isTlbNewHit(MmuState* ms, 
			int thread_id,
			uint32_t virtual_addr,
			uint32_t va_tag, uint32_t* pte, uint8_t*  pte_level);

#endif
