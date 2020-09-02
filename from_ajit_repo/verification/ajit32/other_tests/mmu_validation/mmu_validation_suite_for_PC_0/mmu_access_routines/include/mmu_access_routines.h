// Routines for reading/writing to mmu registers
// Author: Neha Karanjkar


#include<stdint.h>

//Mmu asi constants
#define ASI_MMU_REGISTER 		0x04
#define ASI_MMU_FLUSH_PROBE	 	0x03
#define ASI_FLUSH_I_D_CONTEXT		0x13

//#define ASI_MMU_BYPASS		0x2f
//Addresses of MMU registers
#define MMU_REG_CONTROL			0x00000000
#define MMU_REG_CONTEXT_TABLE_PTR	0x00000100
#define MMU_REG_CONTEXT			0x00000200
#define MMU_REG_FSR			0x00000300
#define MMU_REG_FAR			0x00000400



//store word into mmu register
inline void store_word_mmureg(uint32_t value, uint32_t* addr);

//load word from mmu register
inline uint32_t load_word_mmureg(uint32_t* addr);


//Mmu flush
inline void mmu_flush(uint32_t value, uint32_t* addr);


//Mmu probe
inline uint32_t mmu_probe(uint32_t* addr);


//flush icache
inline void flush_icache(void);


//flush_dcache
inline void flush_dcache(void);



//context switch.
//make a switch to a particular context
inline void context_switch(uint32_t context_number);

//Routines required by convertPhyAddrToPTD
uint64_t getSlice64(uint64_t reg, uint8_t h, uint8_t l);
uint32_t setSlice32(uint32_t reg, uint8_t h, uint8_t l, uint32_t value);


//convert a physical address to a page table descriptor
uint32_t convertPhyAddrToPTD(uint64_t phy_addr);


