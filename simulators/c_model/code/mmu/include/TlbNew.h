#ifndef _TlbNew_h___
#define _TlbNew_h___
#include <stdint.h>
#include "Mmu.h"
#include "tlbs.h"

void initializeTlbNew(MmuState* ms);
void writeTlbNewEntry(MmuState* ms, 
			uint32_t virtual_addr,
			uint32_t va_tag, uint32_t pte, uint8_t pte_level);
uint8_t isTlbNewHit(MmuState* ms, 
			uint32_t virtual_addr,
			uint32_t va_tag, uint32_t* pte, uint8_t*  pte_level);

#endif
