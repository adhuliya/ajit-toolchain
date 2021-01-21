#include <stdio.h>
#include <stdint.h>

#include "ajit_access_routines.h"
#include "sdhc_access.h"

/* writes: byte, word and double-word */
void __ajit_bypass_write_sdhc_reg_byte(uint32_t addr, uint8_t val)
{
        // __AJIT_STORE_UBYTE_MMU_BYPASS__(addr, val);
        __ajit_bypass_write_sdhc_reg_dword(addr, (uint32_t)val);
}

void __ajit_bypass_write_sdhc_reg_word(uint32_t addr, uint16_t val)
{
        // uint8_t i = 0;
        // uint16_t temp = 0;
        // temp = val;
        // for (i = 0; i < 2; addr++)
        // {
        //         if (i=0)
        //         __ajit_bypass_write_sdhc_reg_byte(addr, val<<7);
        //         else
        //         __ajit_bypass_write_sdhc_reg_byte(addr, (uint8_t)temp);
        // }

        __ajit_bypass_write_sdhc_reg_dword(addr, (uint32_t)val);
}

void __ajit_bypass_write_sdhc_reg_dword(uint32_t addr, uint32_t val)
{
        __ajit_store_word_mmu_bypass__(val, addr);
}

/* read: byte, word and double-word */
uint32_t __ajit_bypass_read_sdhc_reg_byte(uint32_t addr)
{
        uint32_t ret_val = 0;
        ret_val = __ajit_bypass_read_sdhc_reg_dword(addr);
        ret_val = ret_val & 0x000000FF;
        return(ret_val);
}

uint32_t __ajit_bypass_read_sdhc_reg_word(uint32_t addr)
{
        uint32_t ret_val = 0;
        ret_val = __ajit_bypass_read_sdhc_reg_dword(addr);
        ret_val = ret_val & 0x00000FFFF;
        return ret_val;
}

uint32_t __ajit_bypass_read_sdhc_reg_dword(uint32_t addr)
{
        uint32_t ret_val = 0;
        ret_val = __ajit_load_word_mmu_bypass__(addr);
        return(ret_val);
}
