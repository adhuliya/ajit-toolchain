#include <stdio.h>
#include <stdint.h>

#include "ajit_access_routines.h"
#include "sdhc_access.h"

inline uint16_t __ajit_load_uhword_mmu_bypass__(uint32_t addr)
{
        uint16_t retval;
        __asm__ __volatile__("lduha [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(addr), "i"(ASI_MMU_BYPASS));
        return retval;
}
inline void __ajit_store_uhword_mmu_bypass__(uint16_t value, uint32_t addr)
{
	//uint32_t asi = 0x20 | (highest_4_bits_of_phy_addr & 0xf);
	__asm__ __volatile__("stuha %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
			     "i"(ASI_MMU_BYPASS) : "memory");
}

inline void __ajit_store_ubyte_mmu_bypass__(uint8_t value, uint32_t addr)
{
	//uint32_t asi = 0x20 | (highest_4_bits_of_phy_addr & 0xf);
	__asm__ __volatile__("stuba %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
			     "i"(ASI_MMU_BYPASS) : "memory");
}
inline uint8_t __ajit_load_ubyte_mmu_bypass__(uint32_t addr)
{
        uint8_t retval;
        __asm__ __volatile__("lduba [%1] %2, %0\n\t" :
                             "=r"(retval) : "r"(addr), "i"(ASI_MMU_BYPASS));
        return retval;
}

/* writes: byte, hword and word */
inline void __ajit_write_sdhc_reg_byte_bypass(uint32_t addr, uint8_t val)
{
        // __ajit_store_ubyte_mmu_bypass__(val, addr);
        __AJIT_STORE_UBYTE_MMU_BYPASS__(addr, val);
}

inline void __ajit_write_sdhc_reg_hword_bypass(uint32_t addr, uint16_t val)
{

        // __ajit_store_uhword_mmu_bypass__(val, addr);
        __AJIT_STORE_UHWORD_MMU_BYPASS__(addr, val);
}

inline void __ajit_write_sdhc_reg_word_bypass(uint32_t addr, uint32_t val)
{
        // __ajit_store_word_mmu_bypass__(val, addr);
        __AJIT_STORE_WORD_MMU_BYPASS__(addr, val);
}

/* read: byte, hword and word */
inline uint8_t __ajit_read_sdhc_reg_byte_bypass(uint32_t addr)
{
        uint8_t ret_val = 0;
        // ret_val = __ajit_load_ubyte_mmu_bypass__(addr);
        __AJIT_LOAD_UBYTE_MMU_BYPASS__(addr, ret_val);
        return ret_val;
}

inline uint16_t __ajit_read_sdhc_reg_hword_bypass(uint32_t addr)
{
        uint16_t ret_val = 0;
        // ret_val = __ajit_load_uhword_mmu_bypass__(addr);
        __AJIT_LOAD_UHWORD_MMU_BYPASS__(addr, ret_val);
        return ret_val;
}

inline uint32_t __ajit_read_sdhc_reg_word_bypass(uint32_t addr)
{
        uint32_t ret_val = 0;
        // ret_val = __ajit_load_word_mmu_bypass__(addr);
        __AJIT_LOAD_WORD_MMU_BYPASS__(addr, ret_val);
        return ret_val;
}
